#ifndef LINKLIST_H_
#define LINKLIST_H_
#include <stdio.h>
#include <stdlib.h>

//链表模板
//根据实际情况
//修改宏开关
//修改dataType
//修改list_node_compare函数
//修改list_node_equal函数
//修改printList里的输出控制

#define OVERFLOW_CHECK //溢出检查开关
#define LIST_CAPACITY 1000  //表容量限制开关
#ifdef LIST_CAPACITY
    #define LIST_SIZE
#elif
    #define LIST_SIZE   //表长度
#endif

typedef int dataType;
typedef struct Lnode {
    dataType data;
    struct Lnode *next;
}Lnode, *pLnode;

typedef struct Linklist{
    pLnode head, tail;
#ifdef LIST_SIZE
    int size;
#endif
}Linklist, *pLinklist;

int list_node_compare(dataType, dataType);
int list_node_equal(dataType, dataType);
//溢出检查
int isOverFlow(pLnode);
//初始化头指针、尾指针
int initList(pLinklist);
//头插
int listHeadInsert(pLinklist, dataType);
//尾插
int listTailInsert(pLinklist, dataType);
//有序插入，由compare函数决定链表递增顺序，newdata对应插入量，data对应原始量
int listSortInsert(pLinklist, dataType, int(*compare)(dataType, dataType));
//删除，根据目标关键字，删除结点
int listDeleteByKey(pLinklist, dataType, int(*equal)(dataType, dataType));
//删除，删除一定数量的结点
int listDeleteByNum(pLinklist, int num);
//删除目标结点的下一个结点
void deleteNode(pLnode *p);
//根据关键字找结点并返回节点
pLnode findNodeByKey(pLinklist, dataType, int(*equal)(dataType, dataType));
//根据数目查找对应节点
pLnode findNodeByNum(pLinklist, int num);
//打印
void printList(pLinklist);
//清空链表节点，头尾指针保留
int clearList(pLinklist);
//删除整个链表，包括头尾指针
void deleteList(pLinklist);
#endif
