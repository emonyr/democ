#include <stdio.h>
#include "include/list.h"

int main()
{
	int i;
	struct list_item *head1,*head2,*tmp;
	head1 = list_new_item(0);
	head2 = list_new_item(0);
	list_show(head1);
	list_show(head2);
	printf("\n");
    
	printf("list_new_item\n");
	for(i=1;i<=5;i++){
		list_insert(list_new_item(i),head1,0);
	}
	list_show(head1);
    
    	for(i=6;i<=10;i++){
        	list_insert(list_new_item(i),head2,0);
    	}
    	list_show(head2);

    	printf("list_reverse\n");
    	list_reverse(head1);
    	list_show(head1);
    
    	printf("list_reverse\n");
    	list_reverse(head1);
    	list_show(head1);
    
    	printf("list_data_ascending\n");
    	list_data_ascending(head1);
    	list_show(head1);
    
	printf("merge head1 & head2\n");
	tmp = head1;
	while(tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = head2->next;
	list_data_ascending(head1);
	list_show(head1);

    	printf("list_delete\n");
    	while(head1->next != NULL)
        	list_delete(head1,0);
    	list_show(head1);

    	return 0;
}
