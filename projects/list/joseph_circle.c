#include <stdio.h>
#include <stdlib.h>
#include <include/list.h>

int main()
{
	int i,n=8,k=3,m=4;
	struct list_item *head,*tmp;
	head = list_new_item(1);

	//create the circle
	for(i=2;i<=n;i++)
		list_insert(list_new_item(i),head,0);
	list_reverse(head);
	list_show(head);
	tmp = head;
	while(tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = head;	//首尾相连形成环

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
            printf("%d ",head->data);
            break;
        }
		tmp = head->next;
        head->next = head->next->next;
        free(tmp);
        head = head->next;
	}
	printf("\n");

	return 0;
}
