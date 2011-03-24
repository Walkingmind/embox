/**
 * @file
 * @brief Tests methods of util/list.
 *
 * @date 12.03.11
 * @author Eldar Abusalimov
 */

#include <embox/test.h>

#include <string.h>
#include <util/array.h>

#include <util/list.h>

EMBOX_TEST_SUITE("util/list test");

TEST_SETUP(setup);

struct element {
	int some_stuff;
	struct list_link lnk;
};

static struct element x, y, z;
static struct list m, n;

static struct element * const xyz[] = { &x, &y, &z, NULL };
static struct element * const xy[] = { &x, &y, NULL };
static struct element * const yz[] = { &y, &z, NULL };
static struct element * const xz[] = { &x, &z, NULL };

/**
 * Fills a @a list with the contents of an @a array.
 *
 * @param array
 *   @a NULL terminated array.
 * @param list
 *   The list to fill in.
 * @return
 *   The given @a list.
 */
static struct list *fill_in_from(struct element * const array[],
		struct list *list);

/**
 * Compares a @a list with the pattern @a array. The list becomes empty after
 * the comparison.
 *
 * @param array
 *   @a NULL terminated array with the expected pattern.
 * @param list
 *   The list to check.
 * @return
 *   The given @a list.
 */
static struct list *compare_with(struct element * const array[],
		struct list *list);

TEST_CASE("list_link_element should cast link member out to its container") {
	struct list_link *link = &x.lnk;
	test_assert_equal(list_link_element(link, struct element, lnk), &x);
}

TEST_CASE("list_init should return its argument") {
	struct list l;
	test_assert_equal(list_init(&l), &l);
}

TEST_CASE("list_link_init should return its argument") {
	struct element e;
	test_assert_equal(list_link_init(&e.lnk), &e.lnk);
}

TEST_CASE("list_init should have the same effect as static initializer") {
	struct list l = LIST_INIT(&l);
	char buff[sizeof(l)];
	memcpy(buff, &l, sizeof(l));
	memset(&l, 0xA5, sizeof(l)); /* poison. */

	test_assert_zero(memcmp(buff, list_init(&l), sizeof(l)));
}

TEST_CASE("list_link_init should have the same effect as static initializer") {
	struct element e = { .lnk = LIST_LINK_INIT(&e.lnk), .some_stuff = 42, };
	char buff[sizeof(e.lnk)];
	memcpy(buff, &e.lnk, sizeof(e.lnk));
	memset(&e.lnk, 0xA5, sizeof(e.lnk)); /* poison. */

	test_assert_zero(memcmp(buff, list_link_init(&e.lnk), sizeof(e.lnk)));
}

TEST_CASE("list_empty should return true for just created list") {
	test_assert_true(list_empty(&m));
}

TEST_CASE("list_alone_link should return true for just initialized link") {
	test_assert_true(list_alone_link(&x.lnk));
}

TEST_CASE("list_alone should return true for just initialized element") {
	test_assert_true(list_alone(&x, lnk));
}

TEST_CASE("list_first should return null for empty list") {
	test_assert_null(list_first(&m, struct element, lnk));
}

TEST_CASE("list_last should return null for empty list") {
	test_assert_null(list_last(&m, struct element, lnk));
}

TEST_CASE("list_first_link should return null for empty list") {
	test_assert_null(list_first_link(&m));
}

TEST_CASE("list_last_link should return null for empty list") {
	test_assert_null(list_last_link(&m));
}

TEST_CASE("list_add_first should make the list non empty "
		"and the element not alone") {
	list_add_first(&x, &m, lnk);

	test_assert_false(list_empty(&m));
	test_assert_false(list_alone(&x, lnk));
}

TEST_CASE("list_add_last should make the list non empty "
		"and the element not alone") {
	list_add_last(&x, &m, lnk);

	test_assert_false(list_empty(&m));
	test_assert_false(list_alone(&x, lnk));
}

TEST_CASE("list_add_first_link should make the list non empty "
		"and the element's link not alone") {
	list_add_first_link(&x.lnk, &m);

	test_assert_false(list_empty(&m));
	test_assert_false(list_alone_link(&x.lnk));
}

TEST_CASE("list_add_last_link should make the list non empty "
		"and the element's link not alone") {
	list_add_last_link(&x.lnk, &m);

	test_assert_false(list_empty(&m));
	test_assert_false(list_alone_link(&x.lnk));
}

TEST_CASE("list_first_link and list_last_link on a single element list "
		"constructed using list_add_first should return the element's link") {
	list_add_first(&x, &m, lnk);

	test_assert_equal(list_first_link(&m), &x.lnk);
	test_assert_equal(list_last_link(&m), &x.lnk);
}

TEST_CASE("list_first_link and list_last_link on a single element list "
		"constructed using list_add_last should return the element's link") {
	list_add_last(&x, &m, lnk);

	test_assert_equal(list_first_link(&m), &x.lnk);
	test_assert_equal(list_last_link(&m), &x.lnk);
}

TEST_CASE("list_first_link and list_last_link should return a new and an old "
		"element accordingly after adding a new one with list_add_first") {
	test_assert_not_equal(&x, &y);

	list_add_first(&x, &m, lnk);
	list_add_first(&y, &m, lnk);

	test_assert_equal(list_first_link(&m), &y.lnk);
	test_assert_equal(list_last_link(&m), &x.lnk);
}

TEST_CASE("list_first_link and list_last_link should return a new and an old "
		"element accordingly after adding a new one with list_add_last") {
	test_assert_not_equal(&x, &y);

	list_add_last(&x, &m, lnk);
	list_add_last(&y, &m, lnk);

	test_assert_equal(list_first_link(&m), &x.lnk);
	test_assert_equal(list_last_link(&m), &y.lnk);
}

TEST_CASE("list_remove on a single element list should make the list empty "
		"and element alone again") {
	list_add_first(&x, &m, lnk);

	list_remove(&x, lnk);

	test_assert_true(list_empty(&m));
	test_assert_true(list_alone(&x, lnk));
}

TEST_CASE("single list_remove and subsequent list_add_first to another list "
		"should make the first list empty but an element not alone") {
	test_assert_not_equal(&m, &n);

	list_add_first(&x, &m, lnk);

	list_remove(&x, lnk);
	list_add_first(&x, &n, lnk);

	test_assert_true(list_empty(&m));
	test_assert_false(list_empty(&n));
	test_assert_false(list_alone(&x, lnk));
}

TEST_CASE("multiple list_remove and subsequent list_add_first to another list "
		"should make the first list empty but elements not alone") {
	fill_in_from(xyz, &m);

	list_remove(&x, lnk);
	list_remove(&z, lnk);
	list_remove(&y, lnk);

	fill_in_from(xyz, &n);

	test_assert_true(list_empty(&m));
	test_assert_false(list_empty(&n));
	test_assert_false(list_alone(&x, lnk));
	test_assert_false(list_alone(&y, lnk));
	test_assert_false(list_alone(&z, lnk));

	test_assert_equal(list_first_link(&n), &x.lnk);
	test_assert_equal(list_last_link(&n), &z.lnk);
}

TEST_CASE("list_remove_first should return null for empty list") {
	test_assert_null(list_remove_first(&m, struct element, lnk));
}

TEST_CASE("list_remove_last should return null for empty list") {
	test_assert_null(list_remove_last(&m, struct element, lnk));
}

TEST_CASE("list_remove_first on a single element list should return the "
		"element and make the list empty and element alone again") {
	list_add_first(&x, &m, lnk);

	test_assert_equal(list_remove_first(&m, struct element, lnk), &x);

	test_assert_true(list_empty(&m));
	test_assert_true(list_alone(&x, lnk));
}

TEST_CASE("list_remove_last on a single element list should return the "
		"element and make the list empty and element alone again") {
	list_add_first(&x, &m, lnk);

	test_assert_equal(list_remove_last(&m, struct element, lnk), &x);

	test_assert_true(list_empty(&m));
	test_assert_true(list_alone(&x, lnk));
}

TEST_CASE("list_insert_before on a single element list should make "
		"a new element the first one in the list") {
	list_add_first(&x, &m, lnk);

	list_insert_before(&y, &x, lnk);

	test_assert_equal(list_last_link(&m), &x.lnk);
	test_assert_equal(list_first_link(&m), &y.lnk);
}

TEST_CASE("list_insert_after on a single element list should make "
		"a new element the last one in the list") {
	list_add_first(&x, &m, lnk);

	list_insert_after(&y, &x, lnk);

	test_assert_equal(list_first_link(&m), &x.lnk);
	test_assert_equal(list_last_link(&m), &y.lnk);
}

TEST_CASE("list_insert_before: inserting a new element before the last one "
		"in a list of two elements should insert a new one between them") {
	list_add_first(&x, &m, lnk);
	list_add_last(&z, &m, lnk);

	list_insert_before(&y, &z, lnk);

	test_assert_equal(list_remove_first_link(&m), &x.lnk);
	test_assert_equal(list_remove_last_link(&m), &z.lnk);

	test_assert_equal(list_first_link(&m), &y.lnk);
	test_assert_equal(list_last_link(&m), &y.lnk);
}

TEST_CASE("list_insert_after: inserting a new element after the first one "
		"in a list of two elements should insert a new one between them") {
	list_add_first(&x, &m, lnk);
	list_add_last(&z, &m, lnk);

	list_insert_after(&y, &x, lnk);

	test_assert_equal(list_remove_first_link(&m), &x.lnk);
	test_assert_equal(list_remove_last_link(&m), &z.lnk);

	test_assert_equal(list_first_link(&m), &y.lnk);
	test_assert_equal(list_last_link(&m), &y.lnk);
}

TEST_CASE("list_insert_before and list_insert_after on a single element list"
		"should make new elements the first and the last accordingly") {
	list_add_first(&y, &m, lnk);

	list_insert_before(&x, &y, lnk);
	list_insert_after(&z, &y, lnk);

	test_assert_equal(list_first_link(&m), &x.lnk);
	test_assert_equal(list_last_link(&m), &z.lnk);
}

TEST_CASE("list_bulk_add_first shouldn't modify a destination list "
		"if a source list is empty") {
	fill_in_from(xyz, &n);

	list_bulk_add_first(&m, &n);

	test_assert_true(list_empty(&m));
	compare_with(xyz, &n);
}

TEST_CASE("list_bulk_add_last shouldn't modify a destination list "
		"if a source list is empty") {
	fill_in_from(xyz, &n);

	list_bulk_add_first(&m, &n);

	test_assert_true(list_empty(&m));
	compare_with(xyz, &n);
}

TEST_CASE("list_bulk_add_first should move all the elements from a source "
		"list to the beginning of a destination and make the source empty") {
	fill_in_from(xy, &m);
	list_add_last(&z, &n, lnk);

	list_bulk_add_first(&m, &n);

	test_assert_true(list_empty(&m));
	compare_with(xyz, &n);
}

TEST_CASE("list_bulk_add_last should move all the elements from a source "
		"list to the end of a destination and make the source empty") {
	list_add_first(&x, &n, lnk);
	fill_in_from(yz, &m);

	list_bulk_add_last(&m, &n);

	test_assert_true(list_empty(&m));
	compare_with(xyz, &n);
}

static struct list *fill_in_from(struct element * const array[],
		struct list *list) {
	struct element *e;

	test_assert_true(list_empty(list));
	array_nullterm_foreach(e, array) {
		test_assert_true(list_alone(e, lnk));
		list_add_last(e, list, lnk);
	}
	test_assert_false(list_empty(list));

	return list;
}

static struct list *compare_with(struct element * const array[],
		struct list *list) {
	struct element *e;

	array_nullterm_foreach(e, array) {
		test_assert_equal(list_remove_first(list, typeof(*e), lnk), e);
	}
	test_assert_true(list_empty(list));

	return list;
}

static int setup(void) {
	list_init(&m);
	list_init(&n);
	list_link_init(&x.lnk);
	list_link_init(&y.lnk);
	list_link_init(&z.lnk);
	return 0;
}
