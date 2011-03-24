/**
 * @file
 * @brief TODO documentation for list.h -- Eldar Abusalimov
 *
 * @date Feb 27, 2011
 * @author Eldar Abusalimov
 */

#ifndef UTIL_LIST_H_
#define UTIL_LIST_H_

#include __impl_x(util/list_impl.h)

struct list;

struct list_link;

#define LIST_INIT(list) \
	  __LIST_INIT(list)

#define LIST_LINK_INIT(link) \
	  __LIST_LINK_INIT(link)

extern struct list *list_init(struct list *list);
extern struct list_link *list_link_init(struct list_link *link);

extern int list_empty(struct list *list);

#define list_alone(element, link_member) \
	  __list_alone(element, link_member)

#define list_foreach(element, list, link_member) \
	  __list_foreach(element, list, link_member)

#define list_first(list, element_type, link_member) \
	  __list_first(list, element_type, link_member)

#define list_last(list, element_type, link_member) \
	  __list_last(list, element_type, link_member)

#define list_add_first(element, list, link_member) \
	  __list_add_first(element, list, link_member)

#define list_add_last(element, list, link_member) \
	  __list_add_last(element, list, link_member)

#define list_insert_before(element, before_element, link_member) \
	  __list_insert_before(element, before_element, link_member)

#define list_insert_after(element, after_element, link_member) \
	  __list_insert_after(element, after_element, link_member)

#define list_remove_first(list, element_type, link_member) \
	  __list_remove_first(list, element_type, link_member)

#define list_remove_last(list, element_type, link_member) \
	  __list_remove_last(list, element_type, link_member)

#define list_remove(element, link_member) \
	  __list_remove(element, link_member)

extern void list_bulk_add_first(struct list *from_list, struct list *to_list);

extern void list_bulk_add_last(struct list *from_list, struct list *to_list);

#define list_bulk_insert_before(from_list, before_element, link_member) \
	  __list_bulk_insert_before(from_list, before_element, link_member)

#define list_bulk_insert_after(from_list, after_element, link_member) \
	  __list_bulk_insert_after(from_list, after_element, link_member)

#define list_link_element(link, element_type, link_member) \
	  __list_link_element(link, element_type, link_member)

extern int list_alone_link(struct list_link *link);

#define list_foreach_link(link, list) \
	  __list_foreach_link(link, list)

extern struct list_link *list_first_link(struct list *list);
extern struct list_link *list_last_link(struct list *list);

extern void list_add_first_link(struct list_link *new_link, struct list *list);
extern void list_add_last_link(struct list_link *new_link, struct list *list);

extern void list_insert_before_link(struct list_link *new_link,
		struct list_link *link);
extern void list_insert_after_link(struct list_link *new_link,
		struct list_link *link);

extern struct list_link *list_remove_first_link(struct list *list);
extern struct list_link *list_remove_last_link(struct list *list);

extern void list_remove_link(struct list_link *link);

extern void list_bulk_insert_before_link(struct list *from_list,
		struct list_link *link);
extern void list_bulk_insert_after_link(struct list *from_list,
		struct list_link *link);

#endif /* UTIL_LIST_H_ */
