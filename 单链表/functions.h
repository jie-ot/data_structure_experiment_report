#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_LISTS 10    // 多链表管理中最多保存 MAX_LISTS 个链表

typedef int status;
typedef int ElemType;

// 单链表结点的定义（带头结点）
typedef struct LNode {
    ElemType data;
    struct LNode* next;
} LNode, * LinkList;

// 定义一个用于管理多个单链表的结构体
typedef struct {
    LinkList lists[MAX_LISTS]; // 保存多个链表
    int count;                 // 当前拥有的链表个数
    int current;               // 当前活动链表的索引
} MultiList;

//函数1：初始化单链表
status InitList(LinkList* L); 

 //函数2：销毁单链表
status DestroyList(LinkList* L);

//函数3：清空单链表
status ClearList(LinkList* L); 

//函数4：判断单链表是否为空
status ListEmpty(LinkList L); 

//函数5：返回单链表的长度
int ListLength(LinkList L); 

//函数6：获取单链表的第i个元素
status GetElem(LinkList L, int i, ElemType* e);

//函数7：查找元素e在单链表中的位置序号
int LocateElem(LinkList L, ElemType e); 

//函数8：获取单链表中元素e的前驱
status PriorElem(LinkList L, ElemType e, ElemType* pre); 

//函数9：获取单链表中元素e的后继
status NextElem(LinkList L, ElemType e, ElemType* next); 

//函数10：单链表插入元素
status ListInsert(LinkList* L, int i, ElemType e); 

//函数11：单链表删除元素
status ListDelete(LinkList* L, int i, ElemType* e); 

//函数12：遍历打印单链表
status ListTraverse(LinkList L); 

//附加功能1：链表翻转
status reverseList(LinkList L);

//附加功能2：删除链表的倒数第 n 个结点
status RemoveNthFromEnd(LinkList L, int n);

//附加功能3：链表排序
status sortList(LinkList L);

//附加功能4：将链表保存到文件
status SaveList(LinkList L, char filename[]);

//附加功能 4：从文件加载链表
status LoadList(LinkList* L, const char* filename);

//附加功能5：多链表管理

/* 初始化多链表管理器 */
void InitMultiList(MultiList* ml);

/* 创建新的单链表并加入管理器 */
status CreateNewList(MultiList* ml);

/* 删除管理器中指定索引的单链表 */
status RemoveList(MultiList* ml, char listNames[][30], const char* targetName);

/* 切换当前活动链表 */
status SwitchCurrentList(MultiList* ml, int index);

/* 显示管理器中所有链表的情况（显示序号及各链表长度），当前链表做标记 */
void ListAllLists(MultiList* ml);

//菜单打印函数
void PrintMenu();
void PrintSubMenu();
void PrintSubSubMenu(char* listname);

