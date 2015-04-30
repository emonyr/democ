#include <stdio.h>
#include <stdlib.h>
#include <include/list.h>

int main()
{
	int i,n=8,k=3,m=4;
	struct list_item *head;

	//create the circle
	head = list_new_item(1);
	head->next = head;
	for(i=2;i<=n;i++)
		list_insert(list_new_item(i),head,i-2);


	//把head移动到第k项
	for(i=1;i<k;i++)
		head = head->next;
	//数到m的人出列
	printf("out list: ");
	while(head != NULL){
		for(i=1;i<m-1;i++)
			head = head->next;
        if(head != head->next->next){
			printf("%d ",head->next->data);
        }
        else{
            printf("%d ",head->next->data);
			free(head->next);
			printf("%d ",head->data);
			free(head);
            break;
        }
		list_delete(head,0);
        head = head->next;
	}
	printf("\n");

	return 0;
}
