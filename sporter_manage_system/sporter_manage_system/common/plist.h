#ifndef _PLIST_H
#define _PLIST_H
#include "common.h"



/**
* list_entry - get the struct for this entry
* @ptr:	the &struct list_head pointer.
* @type:	the type of the struct this is embedded in.
* @member:	the name of the list_struct within the struct.
*/
#define list_entry(ptr, type, member) \
	((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))

/**
* list_for_each	-	iterate over a list
* @pos:	the &struct list_head to use as a loop counter.
* @head:	the head for your list.
*/
#define list_for_each(pos, head) \
	for (pos = (head)->next, prefetch(pos->next); pos != (head); \
        	pos = pos->next, prefetch(pos->next))
/**
* list_for_each_prev	-	iterate over a list backwards
* @pos:	the &struct list_head to use as a loop counter.
* @head:	the head for your list.
*/
#define list_for_each_prev(pos, head) \
	for (pos = (head)->prev, prefetch(pos->prev); pos != (head); \
        	pos = pos->prev, prefetch(pos->prev))

/**
* list_for_each_safe	-	iterate over a list safe against removal of list entry
* @pos:	the &struct list_head to use as a loop counter.
* @n:		another &struct list_head to use as temporary storage
* @head:	the head for your list.
*/
#define list_for_each_safe(pos, n, head) \
	for (pos = (head)->next, n = pos->next; pos != (head); \
		pos = n, n = pos->next)

/**
* list_for_each_entry	-	iterate over list of given type
* @pos:	the type * to use as a loop counter.
* @head:	the head for your list.
* @member:	the name of the list_struct within the struct.
*/
#define list_for_each_entry(pos, head, member)				\
	for (pos = list_entry((head)->next, typeof(*pos), member),	\
		     prefetch(pos->member.next);			\
	     &pos->member != (head); 					\
	     pos = list_entry(pos->member.next, typeof(*pos), member),	\
		     prefetch(pos->member.next))

/**
* list_for_each_entry_safe - iterate over list of given type safe against removal of list entry
* @pos:	the type * to use as a loop counter.
* @n:		another type * to use as temporary storage
* @head:	the head for your list.
* @member:	the name of the list_struct within the struct.
*/
#define list_for_each_entry_safe(pos, n, head, member)			\
	for (pos = list_entry((head)->next, typeof(*pos), member),	\
		n = list_entry(pos->member.next, typeof(*pos), member);	\
	     &pos->member != (head); 					\
	     pos = n, n = list_entry(n->member.next, typeof(*n), member))

/**
* list_for_each_entry_continue -       iterate over list of given type
*                      continuing after existing point
* @pos:        the type * to use as a loop counter.
* @head:       the head for your list.
* @member:     the name of the list_struct within the struct.
*/
#define list_for_each_entry_continue(pos, head, member)			\
	for (pos = list_entry(pos->member.next, typeof(*pos), member),	\
		     prefetch(pos->member.next);			\
	     &pos->member != (head);					\
	     pos = list_entry(pos->member.next, typeof(*pos), member),	\
		     prefetch(pos->member.next))

//#endif /* __KERNEL__ || _LVM_H_INCLUDE */

#define list_node_len(member,node)\
	(&(node->member) - node)

struct list_head {
	struct list_head *next;
	struct list_head *prev;
};

typedef struct _list {
	struct list_head list;
	void *p_data;
}st_list;



extern int16 init_list(struct list_head *p_head);
extern int16 add_list_node(void *data, Uint16 len, struct list_head *head);
extern int16 delete_list_node(void *data, Uint16 len, struct list_head *p_head);
extern int16 find_list_node(void *data, Uint16 len, struct list_head *p_head);
extern int16 free_list(struct list_head *p_head);

#endif
