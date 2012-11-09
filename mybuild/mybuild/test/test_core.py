"""
Tests for Mybuild core.
"""

import unittest
from unittest import TestCase
# from mock import Mock, patch

from mybuild.core import module
from mybuild.core import Constraints
# from mybuild.constraints import Constraints
from mybuild.context import Context


class ModuleTestCase(TestCase):
    """High-level tests for @module deco."""

    def test_without_options(self):
        @module
        def m(self):
            pass
        self.assertEqual(tuple(m._options), ())

    def test_with_options(self):
        @module
        def m(self, foo, bar):
            pass
        self.assertEqual(tuple(m._options), ('foo', 'bar'))

    def test_func_with_starargs(self):
        """Module function must not declare neither *args nor **kwargs."""

        with self.assertRaises(TypeError):
            @module
            def m(self, *args):
                pass

        with self.assertRaises(TypeError):
            @module
            def m(self, **kwargs):
                pass

    def test_options_with_leading_underscore(self):
        """Module options must not start with an underscore."""

        with self.assertRaises(TypeError):
            @module
            def m(self, _foo):
                pass

class ConstraintsTestCase(TestCase):
    """Tests for Constraints and friends."""

    def test_no_forks(self):
        @module
        def m(self, foo, bar):
            pass

        c = Constraints()

        self.assertIsNone(c.check(m))
        self.assertIsNone(c.check(m, 'foo', 42))
        self.assertIsNone(c.check(m, 'foo', 17))

        c.constrain(m, 'foo', 17, negated=True)

        self.assertIsNone(c.check(m))
        self.assertIsNone(c.check(m, 'foo', 42))
        self.assertFalse(c.check(m, 'foo', 17))

        c.constrain(m, 'foo', 42)

        self.assertTrue(c.check(m))
        self.assertTrue(c.check(m, 'foo', 42))
        self.assertFalse(c.check(m, 'foo', 17))



###############################################################################

import mybuild.logs as log


log.zones = {'mybuild'}
log.verbose = True
log.init_log()


@module
def conf(mod, z=None):
    mod._build_ctx.consider(m0(o=42))
    mod.constrain(m0(o=42))

@module
def m0(mod, o):
    mod1 = mod.ask(m1)
    t = "with m1" if mod1 else "no m1"
    log.debug("mybuild: <m0> o=%s, %s, m1.x=%r" % (o, t, mod1.x))

@module
def m1(mod, x=11):
    mod0 = mod.ask(m0)
    if mod0.o < 43:
        mod._build_ctx.consider(m0(o=mod0.o + 1))
    log.debug("myconstrain: <m1> x=%s, m0.o=%d" % (x, mod0.o))



if __name__ == '__main__':

    ctx = Context()
    ctx.consider(conf())

    unittest.main()

