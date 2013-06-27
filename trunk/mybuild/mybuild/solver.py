"""
Pgraph solver.
"""

__author__ = "Eldar Abusalimov"
__date__ = "2012-11-30"

__all__ = [
    "solve",
    "SolveError",
]


from collections import defaultdict
from collections import namedtuple
from itertools import combinations
from itertools import product
import operator

from compat import *
from pgraph import *

from util import pop_iter

import logs as log


class Solution(object):
    """
    Solution backed by sets of nodes and their literals.
    """

    @property
    def valid(self):
        return len(self.nodes) == len(self.literals)

    @property
    def cost(self):
        return sum(literal.cost for literal in self.literals)

    def __init__(self):
        super(Solution, self).__init__()

        self.nodes    = set()
        self.literals = set()
        self.reasons  = set()

    def copy(self):
        cls = type(self)
        new = cls.__new__(cls)

        new.nodes    = self.nodes    .copy()
        new.literals = self.literals .copy()
        new.reasons  = self.reasons  .copy()

        return new

    def __len__(self):
        return len(self.literals)

    def __ior__(self, other):
        self.nodes    |= other.nodes
        self.literals |= other.literals
        self.reasons  |= other.reasons

        return self

    def __or__(self, other):
        ret = self.copy()
        ret |= other
        return ret

    def __isub__(self, other):
        self.nodes    -= other.nodes
        self.literals -= other.literals
        self.reasons  -= other.reasons

        return self

    def clear(self):
        self.nodes    .clear()
        self.literals .clear()
        self.reasons  .clear()

    def dispose(self):
        del self.nodes
        del self.literals
        del self.reasons

    def update(self, other, check=True):
        self |= other

        if check and not self.valid:
            raise SolutionError(self)

    def difference_update(self, other, check=True):
        self -= other

        if check and not self.valid:
            raise SolutionError(self)

    def add_literal(self, literal, reason=None):
        self.literals .add(literal)
        self.nodes    .add(literal.node)
        if reason is not None:
            self.reasons.add(reason)


class TrunkSolution(Solution):
    """docstring for TrunkSolution"""

    def __init__(self):
        super(TrunkSolution, self).__init__()

        self.branchmap = dict()  # maps gen literals to branches
        self.neglefts = dict()   # neglasts to sets of left literals

    def copy(self):
        raise NotImplementedError

    def __ior__(self, branch):
        if self is not branch.trunk:
            raise ValueError('Branch must belong to this trunk')

        for neglast, negexcl in iteritems(branch.negexcls):
            self.neglefts[neglast] -= negexcl

        return super(TrunkSolution, self).__ior__(branch)

    def __isub__(self, other):
        return NotImplemented

    def branchset(self):
        return set(itervalues(self.branchmap))


class BranchSolutionBase(Solution):
    """docstring for BranchSolutionBase"""

    def __init__(self, trunk):
        super(BranchSolutionBase, self).__init__()

        self.trunk        = trunk
        self.gen_literals = set()  # literals

        self.todo         = set()  # literals
        self.negexcls     = defaultdict(set)  # {neglast: literals...}

    def copy(self):
        new = super(BranchSolutionBase, self).copy()

        new.trunk         = self.trunk
        new.gen_literals = set()  # this is not copied

        new.todo = self.todo.copy()
        negexcls = new.negexcls = defaultdict(set)
        for neglast, negexcl in iteritems(self.negexcls):
            negexcls[neglast] = negexcl.copy()

        return new

    def __invert__(self):
        try:
            any_gen = next(iter(self.gen_literals))
            inv_branch = self.trunk.branchmap[~any_gen]
        except (StopIteration, KeyError):
            assert False, 'should not happen'
        else:
            assert (not self.valid or not inv_branch.valid or
                    self.gen_literals == set(map(operator.__invert__,
                                                 inv_branch.gen_literals)))

        return inv_branch

    def __ior__(self, other):
        if self.trunk is not other.trunk:
            raise ValueError('Both branches must belong to the same trunk')
        if other.todo:
            raise NotImplementedError('Other is not ready')

        if self.literals >= other.gen_literals:
            assert self.nodes    >= other.nodes
            assert self.literals >= other.literals
            assert self.reasons  >= other.reasons
            assert self.todo     >= other.todo
            for neglast, negexcl in iteritems(other.negexcls):
                assert self.negexcls[neglast] >= negexcl
            return self

        for neglast, negexcl in iteritems(other.negexcls):
            self.__do_neglast(neglast, operator.__ior__, negexcl)

        return super(BranchSolutionBase, self).__ior__(other)

    def __isub__(self, other):
        if self.trunk is not other.trunk:
            raise ValueError('Both branches must belong to the same trunk')
        if other.todo:
            raise NotImplementedError('Other is not ready')

        for neglast, negexcl in iteritems(other.negexcls):
            self.__do_neglast(neglast, operator.__isub__, negexcl)

        return super(BranchSolutionBase, self).__isub__(other)

    def update(self, other, check=True, handle_todos=False):
        super(BranchSolutionBase, self).update(other, check)
        if handle_todos:
            self.handle_todos()

    def difference_update(self, other, check=True, handle_todos=False):
        super(BranchSolutionBase, self).difference_update(other, check)
        if handle_todos:
            self.handle_todos()

    def substitute_with(self, other):
        """
        Upon replacement, this branch is disposed and must not be used anymore.
        """
        other.gen_literals |= self.gen_literals

        # Fixup any references to this one.
        for gen_literal in self.gen_literals:
            self.trunk.branchmap[gen_literal] = other

        self.dispose()  # make gc happy

    def clear(self):
        self.todo     .clear()
        self.negexcls .clear()
        super(BranchSolutionBase, self).clear()

    def dispose(self):
        del self.todo
        del self.negexcls
        super(BranchSolutionBase, self).dispose()

    def add_literal(self, literal, reason=None):
        for neglast in literal.neglasts:
            self.__do_neglast(neglast, operator.methodcaller('add', literal))

        super(BranchSolutionBase, self).add_literal(literal, reason)

    def __do_neglast(self, neglast, op, *args):
        negleft = self.trunk.neglefts[neglast]
        negexcl = self.negexcls[neglast]

        op(negexcl, *args)  # TODO don't like this

        left = len(negleft) - len(negexcl)
        if left <= 1:
            neg_literal, neg_reason = neglast.neg_reason_for(
                last_literal=(negleft-negexcl).pop() if left else None)

            self.reasons.add(neg_reason)
            self.todo.add(neg_literal)

    def iter_todo_away(self):
        trunk = self.trunk

        for literal in pop_iter(self.todo):
            if literal in self.literals:
                continue  # already handled

            try:
                implied = trunk.branchmap[literal]

            except KeyError:
                if literal in trunk.literals:
                    continue  # included in the trunk, i.e. unconditionally

                assert ~literal in trunk.literals
                raise SolutionError(self)

            yield literal, implied

    def handle_todos(self):
        """
        Must only be called when all branches in trunk.branchmap are
        completely initialized.
        """
        for literal, implied in self.iter_todo_away():
            if self.gen_literals <= implied.literals:
                self.substitute_with(implied)
                break

            self.update(implied)

    def __repr__(self):
        return '<%s %s>' % (type(self).__name__,
                            ' & '.join(repr(literal).join('()')
                                       for literal in self.gen_literals))


class BranchSolution(BranchSolutionBase):
    """docstring for BranchSolution"""

    @property
    def valid(self):
        return self.error is None and len(self.nodes) == len(self.literals)

    @property
    def initialized(self):
        return not self.todo

    def __init__(self, trunk, gen_literal):
        super(BranchSolution, self).__init__(trunk)

        self.error = None
        self.gen_literals.add(gen_literal)

        self.add_literal(gen_literal)

        self.reasons.update(gen_literal.imply_reasons)
        self.todo |= gen_literal.implies

    def copy(self):
        new = super(BranchSolution, self).copy()
        new.error = None
        return new


def create_trunk(pgraph, initial_literals=[]):
    trunk = TrunkSolution()

    nodes    = trunk.nodes
    literals = trunk.literals
    reasons  = trunk.reasons
    neglefts = trunk.neglefts

    neglasts_todo = list()

    for node in pgraph.nodes:
        for literal in node:
            for neglast in literal.neglasts:
                negleft = neglefts[neglast] = set(neglast.literals)

                if len(negleft) <= 1:  # will not happen, generally speaking
                    neglasts_todo.append(neglast)

    # During the loop below we admit possible violation of the main context
    # invariant, i.e. len(nodes) may become less than len(literals).
    #
    # A difference between implication closures of conflicting literals is
    # accumulated in order to be able to produce better error reporting
    # because of keeping more reason chains for all literals.
    todo = to_lset(initial_literals)
    todo.update(pgraph.const_literals)

    literals |= todo

    while todo:
        literal = todo.pop()

        assert literal in literals, "must has already been added"
        nodes.add(literal.node)

        reasons.update(literal.imply_reasons)

        for neglast in literal.neglasts:
            negleft = neglefts[neglast]
            negleft.remove(literal)  # must be still there, raises otherwise

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

                reasons.add(neg_reason)

            del neglasts_todo[:]

        literals |= newly_seen
        todo     |= newly_seen

    if not trunk.valid:
        raise SolutionError(trunk)

    return trunk


def prepare_branches(trunk, unresolved_nodes):
    """
    Non-recursive DFS.
    """
    for node in unresolved_nodes:
        for literal in node:
            branch = trunk.branchmap[literal] = BranchSolution(trunk, literal)
            branch.todo_it = None

    assert len(trunk.branchmap) == 2*len(unresolved_nodes)

    stack = list()

    def stack_push(branch):
        assert branch.todo_it is None
        branch.todo_it = branch.iter_todo_away()
        stack.append(branch)

    def stack_pop():
        branch = stack.pop()
        del branch.todo_it
        return branch

    todo_branches = trunk.branchset()

    while stack or todo_branches:
        if not stack:
            stack_push(todo_branches.pop())

        branch = stack[-1]
        # print ' .' * len(stack), 'branch %r for:' % \
        #   (id(stack[-1]) % 37), sorted(branch.gen_literals)

        try:
            # Can't use branch.handle_todos since some branches are in an
            # intermediate state. Manual iteration also makes it possible to
            # check for mutual implication more efficiently.
            literal, implied = next(branch.todo_it)
            # print ' ' * 60, id(branch) % 37, '->', id(implied) % 37, \
            #  '\t', literal

            if not implied.valid:
                branch.todo.add(literal)
                raise SolutionError(branch)

            if implied.initialized:
                branch.update(implied)
                continue

            if implied.todo_it is not None:  # Equivalent (mutual implication).
                implied.todo |= branch.todo
                branch.todo.clear()

                implied.update(branch)
                branch.substitute_with(implied)

                raise StopIteration  # forget about this branch

        except SolutionError as error:
            # print ' .' * len(stack), 'branch %r dies' % (id(branch) % 37)
            # unwind implication stack
            for implicant in pop_iter(stack, pop=stack_pop):
                implicant.error = error
                error = SolutionError(implicant, error)

        except StopIteration:
            # print ' .' * len(stack), 'branch %r done' % (id(branch) % 37)
            # no more implications, or the branch was merged into an equivalent
            stack_pop()

        else:  # defer until a branch is initialized
            #
            # During initialization of the implied branch it may have been
            # replaced by an implicant (appears upper on the stack).
            #
            # Example:
            #   A => B => C => A
            #           ^- assuming we're handling this implication now
            #
            # Upon returning back to handling the implication, a branch
            # initially created for C gets replaced by A and should not be
            # used anymore.
            #
            # So the best thing we can do here is to restart handling the
            # literal from the beginning.
            branch.todo.add(literal)

            todo_branches.remove(implied)
            stack_push(implied)


def resolve_branches(trunk):
    resolved = BranchSolutionBase(trunk)

    for branch in trunk.branchset():
        if not branch.valid:
            resolved.update(~branch)

    while resolved:
        trunk.update(resolved)

        for literal in resolved.literals:
            for each in literal.node:  # remove both literal and ~literal
                del trunk.branchmap[each]

        next_resolved = BranchSolutionBase(trunk)

        for branch in trunk.branchset():
            assert branch.valid, 'only valid branches must have left'

            try:
                branch.difference_update(resolved, handle_todos=True)

            except SolutionError:
                next_resolved.update(~branch)  # may raise as well

        resolved = next_resolved


def combine_branches(trunk):
    all_branches = sorted(trunk.branchset(),
            key=lambda branch: len(branch) / float(branch.cost+1),
            reverse=True)  # bigger and cheaper go first

    assert all(branch.valid for branch in all_branches)

    unionmap = dict()
    branches = list()
    skipset  = set()

    for branch in all_branches:
        branch.components = frozenset(trunk.branchmap[literal]
                                      for literal in branch.literals)
        assert branch.components not in unionmap
        unionmap[branch.components] = branch

        if branch in skipset:
            continue

        branches.append(branch)
        skipset.add(~branch)

    assert len(all_branches) == 2*len(branches)

    for pair in combinations(branches, 2):
        # pairs = (~a|~b, ~a|b, a|~b, a|b)
        pairs = tuple(product(*((~each, each) for each in pair)))
        assert pair[::-1] not in pairs

        branch_unions = list()
        for pair in pairs:
            components = pair[0].components | pair[1].components
            if components in unionmap:
                continue

            branch = unionmap[components] = pair[0] | pair[1]
            branch.components = components

            if not branch.valid:
                for n, each in enumerate(pair):
                    each.update(~pair[not n])
                for each in pair:
                    each.handle_todos()

            branch_unions.append(branch)

        valid_flags = tuple(bool(branch.valid) for branch in branch_unions)
        sum_valid = sum(valid_flags)

        if not sum_valid:
            raise SolutionError
        elif sum_valid == 1:
            print 'Yay!!!'
        elif sum_valid == 2:
            valid_mask = reduce(lambda x, nb: x | (nb[1]<<nb[0]),
                                enumerate(valid_flags), 0)

            if valid_mask == int('1001', 2) or valid_mask == int('0110', 2):
                print 'Douh!', bin(valid_mask)
                continue

            print 'Yay!', bin(valid_mask)

    # unresolved_nodes = set(literal.node for literal in trunk.branchmap)
    # branch_pairs = [] for node in unresolved_nodes

    from pprint import pprint
    pprint([(len(branch), float(branch.cost+1), branch)
            for branch in branches])
    pprint(dict((k, (v, v.valid)) for k,v in iteritems(unionmap)))


def solve(pgraph, initial_values):
    nodes = pgraph.nodes

    trunk = create_trunk(pgraph, initial_values)
    # for literal in trunk.literals:
    #     print 'trunk', literal

    prepare_branches(trunk, nodes-trunk.nodes)
    resolve_branches(trunk)
    # combine_branches(trunk)

    ret = dict.fromkeys(nodes)
    ret.update(trunk.literals)
    return ret


class SolveError(Exception):
    """docstring for SolveError"""

class SolutionError(SolveError):
    """docstring for SolutionError"""

    def __init__(self, context, cause=None):
        super(SolutionError, self).__init__()
        self.context = context
        self.cause = cause

