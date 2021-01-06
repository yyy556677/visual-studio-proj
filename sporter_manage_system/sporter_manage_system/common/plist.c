#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "plist.h"



#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name) \
	struct list_head name = LIST_HEAD_INIT(name)

#define INIT_LIST_HEAD(ptr) do { \
	(ptr)->next = (ptr); (ptr)->prev = (ptr); \
} while (0)

static void __list_init(struct list_head *head)
{
	head->next = head;
	head->prev = head;
}

static  void __list_add(struct list_head *new,
	struct list_head *prev,
	struct list_head *next)
{
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
}


/**
* list_add - add a new entry
* @new: new entry to be added
* @head: list head to add it after
*
* Insert a new entry after the specified head.
* This is good for implementing stacks.
*/
static  void list_add(struct list_head *new, struct list_head *head)
{
	__list_add(new, head, head->next);
}


/**
* list_add_tail - add a new entry
* @new: new entry to be added
* @head: list head to add it before
*
* Insert a new entry before the specified head.
* This is useful for implementing queues.
*/
static  void list_add_tail(struct list_head *new, struct list_head *head)
{
	__list_add(new, head->prev, head);
}

/*
* Delete a list entry by making the prev/next entries
* point to each other.
*
* This is only for internal list manipulation where we know
* the prev/next entries already!
*/
static  void __list_del(struct list_head *prev, struct list_head *next)
{
	next->prev = prev;
	prev->next = next;
}


/**
* list_del_init - deletes entry from list and reinitialize it.
* @entry: the element to delete from the list.
*/
static  void list_del_init(struct list_head *entry)
{
	__list_del(entry->prev, entry->next);
	INIT_LIST_HEAD(entry);
}

/**
* list_move - delete from one list and add as another's head
* @list: the entry to move
* @head: the head that will precede our entry
*/
static  void list_move(struct list_head *list, struct list_head *head)
{
	__list_del(list->prev, list->next);
	list_add(list, head);
}


/**
* list_move_tail - delete from one list and add as another's tail
* @list: the entry to move
* @head: the head that will follow our entry
*/
static  void list_move_tail(struct list_head *list,
	struct list_head *head)
{
	__list_del(list->prev, list->next);
	list_add_tail(list, head);
}

/**
* list_empty - tests whether a list is empty
* @head: the list to test.
*/
static  int list_empty(struct list_head *head)
{
	return head->next == head;
}


static  void __list_splice(struct list_head *list,
	struct list_head *head)
{
	struct list_head *first = list->next;
	struct list_head *last = list->prev;
	struct list_head *at = head->next;

	first->prev = head;
	head->next = first;

	last->next = at;
	at->prev = last;
}


/**
* list_splice - join two lists
* @list: the new list to add.
* @head: the place to add it in the first list.
*/
static  void list_splice(struct list_head *list, struct list_head *head)
{
	if (!list_empty(list))
		__list_splice(list, head);
}

/**
* list_splice_init - join two lists and reinitialise the emptied list.
* @list: the new list to add.
* @head: the place to add it in the first list.
*
* The list at @list is reinitialised
*/
static  void list_splice_init(struct list_head *list,
	struct list_head *head)
{
	if (!list_empty(list)) {
		__list_splice(list, head);
		INIT_LIST_HEAD(list);
	}
}


int16 init_list(struct list_head *head)
{
	if (NULL == head)
	{
		return DRV_ERR;
	}
	__list_init(head);
	return DRV_OK;
}

int16 add_list_node(void *data, Uint16 len,struct list_head *head)
{
	if (NULL == data || NULL == head)
	{
		return DRV_ERR;
	}
	st_list *_node = (st_list *)malloc(sizeof(st_list));
	if (NULL == _node)
	{
		return DRV_ERR_1;
	}
	if (0 == find_list_node(data, len, head))
	{
		return DRV_ERR_1;
	}
	_node->p_data = (int8 *)malloc(sizeof(Uint8)*len);
	memcpy(_node->p_data, (int8 *)data, sizeof(Uint8)*len);
	list_add(&(_node->list), head);
	return DRV_OK;
}

int16 delete_list_node(void *data, Uint16 len,struct list_head *head)
{
	struct list_head *pos = NULL;
	struct list_head *n = NULL;
	st_list *_node = NULL;
	if (NULL == data || NULL == head)
	{
		return DRV_ERR;
	}
	list_for_each_safe(pos,n,head)
	{
		_node = list_entry(pos,st_list,list);
		if (!memcmp(data,_node->p_data, sizeof(Uint8)*len))
		{
			__list_del(pos->prev,pos->next);
			free(_node->p_data);
			free(_node);
			return DRV_OK;
		}
	}
	return DRV_ERR_1;
}

int16 free_list(struct list_head *head)
{
	struct list_head *pos = NULL;
	struct list_head *n = NULL;
	st_list *_node = NULL;
	if (NULL == head)
	{
		return DRV_ERR;
	}
	list_for_each_safe(pos, n, head)
	{
		_node = list_entry(pos, st_list, list);
		__list_del(pos->prev, pos->next);
		free(_node->p_data);
		free(_node);
	}
	return DRV_OK;
}

int16 find_list_node(void *data, Uint16 len, struct list_head *p_head)
{
	struct list_head *pos = NULL;
	struct list_head *n = NULL;
	st_list *_node = NULL;
	if (NULL == data || NULL == p_head)
	{
		return DRV_ERR;
	}
	list_for_each_safe(pos, n, p_head)
	{
		_node = list_entry(pos, st_list, list);
		if (!memcmp(data, _node->p_data, sizeof(Uint8)*len))
		{
			return DRV_OK;
		}
	}
	return DRV_ERR_1;
}
