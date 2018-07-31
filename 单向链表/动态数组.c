#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dynamicArray 
{
	int size;
	int capacity1;
	void** arrd;
};
struct person
{
	char name[64];
	int age;
};
struct dynamicArray * init_dynamicArray(int capacity)//初始化数组 初始化的容量
{
	struct dynamicArray* arr = malloc(sizeof(struct dynamicArray));
	if (arr == NULL)
	{
		return NULL;
	}
	arr->arrd = malloc(sizeof(void*)*capacity);
	if (arr->arrd == NULL)
		return NULL;
	arr->capacity1 = capacity;
	arr->size = 0;
	return arr;
}

void insert_dynamicArray(struct dynamicArray* arr, int pos, void *data)
{
	if (arr == NULL)
		return;
	if (data == NULL)
		return;
	if (pos < 0 || pos >arr->size)
	{
		pos = arr->size;
	}
	if ( arr->size>=arr->capacity1)
	{
		int newspacesize = arr->capacity1 * 2;
		void** newspace = malloc(sizeof(void*)*newspacesize);

		memcpy(newspace, arr->arrd, sizeof(void*)*arr->capacity1);
		free(arr->arrd);
		arr->arrd = NULL;	

		arr->arrd = newspace;

		arr->capacity1 = newspacesize;
	}

	for (int i=arr->size-1;i>=pos;i--)
	{
		arr->arrd[i + 1] = arr->arrd[i];
	}
	arr->arrd[pos] = data;
	arr->size++;
}

void  mypersonprint(void* data)
{
	struct person *p = data;
	printf("name:%s age: %d\n", p->name, p->age);
}
//int myprintf(void* data1, void* data2)
//{
//	struct person* p1 = data1;
//	struct person* p2 = data2;
//	return strcmp(p1->name, p2->name) == 0 && p1->age == p2->age;
//}
void foreach_dynamicArray(struct dynamicArray* arr, void (*myprint)(void*))
{
	if (arr == NULL)
		return;
	if (myprint == NULL)
		return;
	for (int i = 0; i < arr->size; i++)
	{
		myprint(arr->arrd[i]);
	}
}
//insert_dynamicArray(arr, 2, &p1);
void remove_dynamicArray(struct dynamicArray* arr, int pos)//按位置删除
{
	if (arr == NULL)
		return;
	if (pos > arr->size-1 || pos < 0)
		return; 
	for (int i = pos; i < arr->size - 1; i++)
	{
		arr->arrd[i] = arr->arrd[i+1];
	}
	arr->size--;
}
int  mymove(void* data1, void* data2)
{
	struct person *p1 = data1;
	struct person *p2 = data2;
	 

	return strcmp(p1->name, p2->name) == 0 && p1->age == p2->age;

}
//oid removeByValue_dynamicArray( struct dynamicArray * arr , void * data  , int(*myCompare)(void * ,void *  )  )
void removen_dynamicArray(struct dynamicArray* arr, void* data,int(*mymove)(void*,void*))
{
	if (arr == NULL)
		return;
	if (data ==NULL)
		return;
	for (int i = 0; i < arr->size; i++)
	{
		if (mymove(arr->arrd[i], data))
		{
			remove_dynamicArray(arr, i);
			break;
		}
	}
}
void destroy(struct dynamicArray*arr)
{
	if (arr == NULL)
		return;
	if (arr->arrd != NULL)
	{
		free(arr->arrd);
		arr->arrd = NULL;
	}
	free(arr);
	arr = NULL;
}
int main()
{
	struct dynamicArray *arr= init_dynamicArray(5);
	struct person p1 = { "鸣人",20 };
	struct person p2 = { "鼬",25 };
	struct person p3 = { "迈特凯",35 };
	struct person p4 = { "鬼鲛",30 };
	struct person p5 = { "佐助",21 }; 
	struct person p6 = { "雏田",23 };
	printf("插入前数组容量大小为：capacity= %d\n", arr->capacity1);
	printf("插入前数组大小为：camicity= %d\n", arr->size);
	insert_dynamicArray(arr, 2, &p1);
	insert_dynamicArray(arr, 3, &p2);
	insert_dynamicArray(arr, 2, &p3);
	insert_dynamicArray(arr, 2, &p4);
	insert_dynamicArray(arr, 2, &p5);
	insert_dynamicArray(arr, 2, &p6);
	printf("插入后数组容量大小为：capacity= %d\n", arr->capacity1);
	printf("插入后数组大小为：camicity= %d\n", arr->size);

	printf("遍历后的结果为：\n");
	foreach_dynamicArray(arr, mypersonprint);
	

	remove_dynamicArray(arr, 3);
	printf("删除后的结果为：\n");
	foreach_dynamicArray(arr, mypersonprint);

	struct person p= { "鬼鲛",30 };
	removen_dynamicArray(arr, &p, mymove);

	foreach_dynamicArray(arr, mypersonprint);

	destroy(arr);	
	arr = NULL;
	printf("删除后的结果为：\n");
	foreach_dynamicArray(arr, mypersonprint);

	system("pause");
	return EXIT_SUCCESS;
}//