/*
 * list.c 
 * 链表相关操作
 */

#include "global.h"

struct list_node * list_init(void)
{
	struct list_node *head;
	head = (struct list_node *)malloc(sizeof(struct list_node));
	head->next = NULL;
	return head;
}

struct list_node * list_push(struct list_node *head)
{
	struct list_node *new;
	new = list_init();
	new->next = head->next;
	head->next = new;
	return new;
}

struct list_node * list_pop(struct list_node *head)
{
	struct list_node *out;
	out = head->next;
	head->next = out->next;
	return out;
}