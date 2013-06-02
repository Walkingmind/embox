"""
Pgraph solver.
"""

__author__ = "Eldar Abusalimov"
__date__ = "2012-11-30"

__all__ = [
    "solve",
]


from collections import defaultdict
from collections import namedtuple
from itertools import izip
from itertools import repeat
from operator import attrgetter
from operator import methodcaller

from compat import *
from pgraph import *

from util import bools
from util import filter_bypass
from util import map_bypass
from util import pop_iter

import logs as log


class Context(namedtuple('_Context', 'nodes, literals, reasons')):
    """
    Context backed by sets of nodes and their literals.
    """

    @property
    def valid(self):
        return len(self.nodes) == len(self.literals)

    def __new__(cls, *args, **kwargs):
        return super(Context, cls).__new__(cls,
            nodes    = set(),
            literals = set(),
            reasons  = list())

    def __init__(self):
        super(Context, self).__init__()


class TrunkContext(Context):
    """docstring for TrunkContext"""

    def __init__(self):
        super(TrunkContext, self).__init__()

        self.branchmap = dict()  # maps gen literals to branches
        self.neglefts = dict()   # neglasts to sets of left literals

    def branch_for(self, literal):
        """
        Returns branch, which effectively is an implication closure of given
        literal.
        """

        if literal in self.literals:
            return None

        if literal.node in self.nodes:
            raise ContextError(self)

        try:
            branch = self.branchmap[literal]
        except KeyError:
            branch = self.branchmap[literal] = BranchContext(literal)

        return branch


class BranchContext(Context):
    """docstring for BranchContext"""

    @property
    def valid(self):
        return self.error is None and len(self.nodes) == len(self.literals)

    @property
    def initialized(self):
        return bool(self.literals)

    def __init__(self, gen_literal):
        super(BranchContext, self).__init__()

        # self.trunk = trunk
        self.gen_literals = set([gen_literal])

        self.negexcls = defaultdict(set)
        self.init_task = None
        self.error = None


def create_trunk(pgraph, initial_literals=[]):
    (nodes, literals, reasons) = trunk = TrunkContext()
    neglefts = trunk.neglefts

    neglasts_todo = list()

    for node in pgraph.nodes:
        for literal in node:
            for neglast in literal.neglasts:
                negleft = neglefts[neglast] = set(neglast.literals)

                if len(negleft) <= 1:
                    neglasts_todo.append(neglast)

    # During the loop below we admit possible violation of the main context
    # invariant, i.e. len(nodes) may become less than len(literals).
    #
    # A difference between implication closures of conflicting literals is
    # accumulated in order to be able to produce better error reporting
    # because of keeping more reason chains for all literals.

    todo = to_lset(initial_literals)
    literals |= todo

    while todo:
        literal = todo.pop()

        nodes.add(literal.node)
        reasons.extend(literal.imply_reasons)

        for neglast in literal.neglasts:
            negleft = neglefts[neglast]
            negleft.remove(literal)  # must be still there

            if len(negleft) == 1:
                # defer negating the last literal,
                # cause it still may be excluded.
                neglasts_todo.append(neglast)

        newly_seen = literal.implies - literals

        if not todo and not newly_seen:
            # no more direct implications, flush neglasts_todo
            for neglast in neglasts_todo:
                neg_literal, neg_reason = neglast.neg_reason_for(
                        # at most one literal is contained in a negleft
                        *neglefts[neglast])

                if neg_literal not in literals:
                    newly_seen.add(neg_literal)

                reasons.append(neg_reason)

            del neglasts_todo[:]

        literals |= newly_seen
        todo     |= newly_seen

    if not trunk.valid:
        raise ContextError(trunk)

    return trunk


def initialize_branch(trunk, branch):
    """
    Merges all implied branches into this one. Note the reentrancy of this
    routine (called recursively on implied branches).
    """
    assert branch.init_task is None

    if branch.initialized:
        return

    branch.init_task = branch_init_task(trunk, branch)
    stack = [branch]

    while stack:
        try:
            implied = stack[-1].init_task.next()

        except StopIteration:
            stack.pop().init_task = None

        else:
            if isinstance(implied, ContextError):
                error = implied

                # unwind branch stack
                for implicant in reversed(stack):
                    implicant.error = error
                    error = ContextError(implicant, error)

                raise error

            assert not implied.initialized and implied.init_task is None

            implied.init_task = branch_init_task(trunk, implied)
            stack.append(implied)


def branch_init_task(trunk, branch):
    init_literal, = branch.gen_literals  # assumed to be singular

    branch.literals.add(init_literal)
    branch.nodes.add(init_literal.node)

    # TODO add a Reason for init_literal
    branch.reasons.extend(init_literal.imply_reasons)

    todo = set(init_literal.implies)
    while todo:
        literal = todo.pop()
        if literal in branch.literals:
            continue  # already handled

        try:
            other = trunk.branch_for(literal)
            if other is None:
                continue  # included in the trunk, i.e. unconditionally

            if not other.initialized:
                yield other  # defer until a branch is initialized

            if not other.valid:
                raise ContextError(branch)

            if other.init_task is not None:  # equivalent (mutual implication)
                # Forget about this branch, switch to the implicant one.
                branch, other = swap_branches(trunk, branch, other)

            merge_branches(trunk, branch, other, todo)

        except ContextError as e:
            yield e


def swap_branches(trunk, branch, other):
    # Fixup any references to an old branch.
    for gen_literal in branch.gen_literals:
        assert trunk.branchmap[gen_literal] is branch
        trunk.branchmap[gen_literal] = other

    other.gen_literals |= branch.gen_literals

    return other, branch


def merge_branches(trunk, branch, other, todo):
    assert other.initialized

    branch.nodes    |= other.nodes
    branch.literals |= other.literals
    branch.reasons  += other.reasons

    for neglast, other_negexcl in iteritems(other.negexcls):
        negleft = trunk.neglefts[neglast]

        negexcl = branch.negexcls[neglast]
        negexcl |= other_negexcl

        left = len(negleft) - len(negexcl)
        if left > 1:
            continue

        neg_literal, neg_reason = neglast.neg_reason_for(
            last_literal=(negleft-negexcl).pop() if left else None)

        if neg_literal not in branch.literals: # XXX trunk?
            todo.add(neg_literal)

        branch.reasons.append(neg_reason)

    if not branch.valid:
        raise ContextError(branch)


def merge_into_trunk(trunk, branch):
    trunk.nodes    |= branch.nodes
    trunk.literals |= branch.literals
    trunk.reasons  += branch.reasons

    for neglast, negexcl in iteritems(branch.negexcls):
        trunk.neglefts[neglast] -= negexcl

    for other in itervalues(trunk.branchmap):
        pass


def revert_changes(trunk, branch, other):
    pass


def create_branch(trunk, literal):
    branch = trunk.branch_for(literal)

    try:
        initialize_branch(trunk, branch)
    except ContextError:
        return

    return branch


def n_valid(pair):
    return sum(branch.valid for branch in pair)
def single_valid(pair):
    if n_valid(pair) == 1:
        return pair[pair[True].valid]

def prepare_branches(trunk, unresolved_nodes):
    if not unresolved_nodes:
        return

    for node in unresolved_nodes:
        for literal in node:
            create_branch(literal)

    assert len(trunk.branchmap) == 2*len(unresolved_nodes)

    branch_pairs = list(node._map_with(trunk.branchmap.get)
                        for node in unresolved_nodes)
    branch_pairs.sort(key=n_valid)

    for pair in branch_pairs:
        if not n_valid(pair):
            raise ContextError

        branch = single_valid(pair)
        if branch is None:
            continue


def solve(pgraph, initial_values):
    nodes = pgraph.nodes

    trunk = create_trunk(pgraph, initial_values)

    prepare_branches(trunk, nodes-trunk.nodes)

    ret = dict.fromkeys(nodes)
    ret.update(root._dict)
    return ret


class ContextError(Exception):
    """docstring for ContextError"""

    def __init__(self, context):
        super(ContextError, self).__init__()
        self.context = context

