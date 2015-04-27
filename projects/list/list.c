#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "include/list.h"

//新建数据为data的链表项
struct list_item *list_new_item(int data)
{
    struct list_item *new_item;
    new_item = (struct list_item *)malloc(sizeof(struct list_item));
    if(!new_item){
        fprintf(stderr,"list_init failed\n");
        exit(-1);
    }
    new_item->data = data;
    new_item->next = NULL;
    
    return new_item;
}

//显示从输入的链表地址开始直到链表结束的每一项信息
int list_show(struct list_item *origin)
{
    while(origin != NULL){
        printf("%p data: %d next: %p \n",origin,origin->data,origin->next);
        origin = origin->next;
    }
    
    return 0;
}

//把new_item插入到距离insert_point偏移offset的链表项后面
int list_insert(struct list_item *new_item,struct list_item *insert_point,int offset)
{
    if((insert_point == NULL) || (new_item == insert_point)){
        fprintf(stderr,"insert_point is invalid\n");
        exit(-1);
    }

    while((insert_point->next != NULL) && (offset > 0)){
        insert_point = insert_point->next;
        offset--;
    }
    if(offset){
        fprintf(stderr,"offset is invalid\n");
        exit(-1);
    }
    
    new_item->next = insert_point->next;
    insert_point->next = new_item;
    
    return 0;
}

//输入地址偏移offset后删除delete_point->next
int list_delete(struct list_item *delete_point,int offset)
{
    struct list_item *tmp;
    if(!delete_point){
        fprintf(stderr,"delete_point is invalid\n");
        exit(-1);
    }
    
    while((delete_point->next != NULL) && (offset > 0)){
        delete_point = delete_point->next;
        offset--;
    }
    if(offset){
        fprintf(stderr,"offset is invalid\n");
        exit(-1);
    }
    
    tmp = delete_point->next;
    delete_point->next = delete_point->next->next;
    free(tmp);

    return 0;
}

//测量链表长度(不包含head)
int list_len(struct list_item *head)
{
    int len = 0;
    struct list_item *tmp;
    
    tmp = head;
    while((tmp->next != NULL)){
        tmp = tmp->next;
        len++;
    }
    
    return len;
}

//翻转链表
int list_reverse(struct list_item *head)
{
    int i,len = list_len(head);
    struct list_item *tmp;
    
    for(i=0;i<len-1;i++){   //因为i从0开始，所以用len-1判断链表终结
        tmp = head->next->next;
        list_insert(head->next,head,len-i);
        head->next = tmp;
    }

    return 0;
}

//按data升序排列链表
int list_data_ascending(struct list_item *head)
{
    struct list_item *min,*tmp;
    
    while(head->next != NULL){
        min = head;
        tmp = min->next;
        
        while(tmp->next != NULL){
            if(min->next->data > tmp->next->data)
                min = tmp;
            tmp = tmp->next;
        }
        if(min != head){
            tmp = min->next->next;
            list_insert(min->next,head,0);
            min->next = tmp;
        }
        head = head->next;
    }
    
    return 0;
}
