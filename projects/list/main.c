#include <stdio.h>
#include "include/list.h"

int main()
{
    int i;
    struct list_item *head;
    head = list_new_item(0);
    list_show(head);
    printf("\n");
    
    for(i=0;i<10;i++){
        list_insert(list_new_item(i+1),head,0);
    }
    list_show(head);
    
    list_reverse(head);
    list_show(head);

    while(head->next != NULL)
        list_delete(head,0);
    list_show(head);

    return 0;
}
