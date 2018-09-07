#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "LinkList.h"
//测试用文件
int main()
{
	srand(time(NULL));
	Linklist list;
	initList(&list);
	int i;
	int num;
	int data;
	for(i = 0; i < 50; i++)
	{
		num = rand()%101 + 1;
		listSortInsert(&list, num, list_node_compare);
	}
	if(NULL != findNodeByKey(&list, 78, list_node_compare))
	{
		printf("find 78\n");
	}else{
		printf("not find 78 \n");
	}
	listDeleteByNum(&list, 25);
	if(listDeleteByKey(&list, 40, list_node_equal))
	{
		printf("delete ok");
	}else{
		printf("delete failure");
	}
	data = findNodeByNum(&list, 20)->data;
	printf("data = %d", data);
	printList(&list);
	printf("\n");
	printf("%d\n", list.size);
	return 0;
}
