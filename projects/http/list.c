/*
 * list.c 
 * 链表相关操作
 */

#include "global.h"

struct request * list_init(void)
{
	struct request *head;
	head = (struct request *)malloc(sizeof(struct request));
	head->next = NULL;
	return head;
}

struct request * list_push(struct request *head,struct request *new)
{
	new->next = head->next;
	head->next = new;
	return new;
}

struct request * list_pop(struct request *head)
{
	struct request *out;
	out = head->next;
	head->next = out->next;
	return out;
}