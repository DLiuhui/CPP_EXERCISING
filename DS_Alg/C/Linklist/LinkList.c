#include "LinkList.h"

int list_node_compare(dataType newdata, dataType data){
	return (newdata > data) ? 1 : 0;
}

int list_node_equal(dataType key, dataType data){
	return (key == data) ? 1 : 0;
}

//溢出检查
int isOverFlow(pLnode p){
    if(p)
        return 0;
    else
        return 1;
}
//初始化头指针、尾指针
int initList(pLinklist list){
    list->head = (pLnode)calloc(1, sizeof(Lnode));
	#ifdef OVERFLOW_CHECK
    	if(isOverFlow(list->head)){
        	printf("init overflow.\n");
			return 0;
    	}
	#endif
    list->tail = list->head;
	#ifdef LIST_CAPACITY
		list->size = 0;
	#endif
    return 1;
}
//头插
int listHeadInsert(pLinklist list, dataType data){
	#ifdef LIST_CAPACITY
		if(list->size == LIST_CAPACITY){
			printf("can't insert more nodes\n");
			return 0;
		}else{
			list->size++;
		}
	#endif
    pLnode p = (pLnode)calloc(1, sizeof(Lnode));
	#ifdef OVERFLOW_CHECK
		if(isOverFlow(p)){
			printf("new node overflow.\n");
			return 0;
		}
	#endif
	p->data = data;
    if(list->head == list->tail){  //假如链表为空
        list->tail = p;
    }
    p->next = list->head->next;
    list->head->next = p;
    return 1;
}
//尾插
int listTailInsert(pLinklist list, dataType data){
	#ifdef LIST_CAPACITY
		if(list->size == LIST_CAPACITY){
			printf("can't insert more nodes\n");
			return 0;
		}else{
			list->size++;
		}
	#endif
    pLnode p = (pLnode)calloc(1, sizeof(Lnode));
	#ifdef OVERFLOW_CHECK
		if(isOverFlow(p)){
			printf("new node overflow.\n");
			return 0;
		}
	#endif
	p->data = data;
    if(list->head == list->tail){ //假如链表为空
        list->head->next = p;
    }
    list->tail->next = p;
    list->tail = p;
    return 1;
}
//有序插入，由compare函数决定链表递增顺序，newdata对应插入量，data对应原始量
int listSortInsert(pLinklist list, dataType data, int (*compare)(dataType newdata, dataType data)) {
	#ifdef LIST_CAPACITY
		if(list->size == LIST_CAPACITY){
			printf("can't insert more nodes\n");
			return 0;
		}else{
			list->size++;
		}
	#endif
	pLnode p = (pLnode)calloc(1, sizeof(Lnode));
	#ifdef OVERFLOW_CHECK
		if(isOverFlow(p)){
			printf("new node overflow.\n");
			return 0;
		}
	#endif
	p->data = data;
	if (list->head == list->tail) {
		list->head->next = p;
		list->tail = p;
		return 1;
	}
	pLnode q = list->head;
	while (q->next) {
		if ((*compare)(p->data, q->next->data)) {	//插入
			p->next = q->next;
			q->next = p;
			return 1;
		}
		else
			q = q->next;
	}
	if (q == list->tail) {	//遍历到底
		list->tail->next = p;
		list->tail = p;
	}
	return 1;
}
//删除，根据目标关键字，删除结点
int listDeleteByKey(pLinklist list, dataType key, int (*equal)(dataType key, dataType data)) {
	pLnode p = list->head;
	while (p->next) {
		if ((*equal)(key, p->next->data)) {
			deleteNode(&p);
			//printf("Delete the node.\n");
			#ifdef LIST_SIZE
				list->size--;
			#endif
			if(p->next == NULL){	//最后一个结点
				list->tail = p;
			}
			return 1;
		}
		p = p->next;
	}
	//printf("Not found! Delete fail.\n");
	return 0;
}
//删除，删除一定数量的结点
int listDeleteByNum(pLinklist list, int num) {
	pLnode p = list->head;
	#ifdef LIST_SIZE
		if(num >= list->size){	//删除结点数目大于队列长度
			clearList(list);
		}else{
			list->size -= num;
			while (num != 0 && p->next) {
				deleteNode(&p);
				num--;
			}
		}
	#else
		while (num != 0 && p->next) {
			deleteNode(&p);
			num--;
		}
		if (p->next == NULL) {	//链表被清空
			list->tail = list->head;
			//printf("List is clear.\n");
		}
	#endif
	return 1;
}
//删除目标结点的下一个结点
void deleteNode(pLnode *p) {
	if ((*p)->next) {
		pLnode q = (*p)->next;
		(*p)->next = q->next;
		free(q);
	}
}
//根据关键字找结点并返回节点
pLnode findNodeByKey(pLinklist list, dataType key, int(*equal)(dataType key, dataType data)) {
	pLnode p = list->head;
	while (p->next) {
		if ((*equal)(p->next->data, key))
			return p->next;
		p = p->next;
	}
	//未找到
	//printf("Not found!\n");
	return NULL;
}
//根据数目查找对应节点
pLnode findNodeByNum(pLinklist list, int num) {
	#ifdef LIST_SIZE
		if(list->size < num){
			//printf("There is not so much nodes.\n");
			return NULL;
		}
	#endif
	pLnode p = list->head;
	while (num != 0 && p->next) {
		p = p->next;
		num--;
	}
	if(num == 0) {
		return p;
	}
	//节点数不足
	//printf("There is not so much nodes.\n");
	return NULL;
}
//打印表结点
void printList(pLinklist list){
    int count = 0;
    pLnode p = list->head;
    while(p->next){
        p = p->next;
        printf("%d", p->data);
        //输出控制
        count++;
        if(count == 25){
            printf("\n");
            count = 0;
        }
        else
            printf(" ");
    }
}
//清空链表节点，头尾指针保留
int clearList(pLinklist list){
    pLnode p = list->head;
    pLnode q;
    while(p->next){
        q = p->next;
        p->next = q->next;
        free(q);
    }
    list->tail = list->head;
    return 1;
}
//删除整个链表，包括头尾指针
void deleteList(pLinklist list){
	clearList(list);	//清空链表后头指针与尾指针已经重合
    free(list->head);	//free头指针后，尾指针指向空间已经清空
}
