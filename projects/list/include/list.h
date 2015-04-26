#include <stdio.h>

struct list_item{
    int data;
    struct list_item *next;
};


extern struct list_item *list_new_item(int data);
extern int list_show(struct list_item *origin);
extern int list_insert(struct list_item *new_item,struct list_item *insert_point,int offset);
extern int list_delete(struct list_item *delete_point,int offset);
extern int list_reverse(struct list_item *head);