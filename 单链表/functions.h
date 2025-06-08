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
#define MAX_LISTS 10    // �������������ౣ�� MAX_LISTS ������

typedef int status;
typedef int ElemType;

// ��������Ķ��壨��ͷ��㣩
typedef struct LNode {
    ElemType data;
    struct LNode* next;
} LNode, * LinkList;

// ����һ�����ڹ�����������Ľṹ��
typedef struct {
    LinkList lists[MAX_LISTS]; // ����������
    int count;                 // ��ǰӵ�е��������
    int current;               // ��ǰ����������
} MultiList;

//����1����ʼ��������
status InitList(LinkList* L); 

 //����2�����ٵ�����
status DestroyList(LinkList* L);

//����3����յ�����
status ClearList(LinkList* L); 

//����4���жϵ������Ƿ�Ϊ��
status ListEmpty(LinkList L); 

//����5�����ص�����ĳ���
int ListLength(LinkList L); 

//����6����ȡ������ĵ�i��Ԫ��
status GetElem(LinkList L, int i, ElemType* e);

//����7������Ԫ��e�ڵ������е�λ�����
int LocateElem(LinkList L, ElemType e); 

//����8����ȡ��������Ԫ��e��ǰ��
status PriorElem(LinkList L, ElemType e, ElemType* pre); 

//����9����ȡ��������Ԫ��e�ĺ��
status NextElem(LinkList L, ElemType e, ElemType* next); 

//����10�����������Ԫ��
status ListInsert(LinkList* L, int i, ElemType e); 

//����11��������ɾ��Ԫ��
status ListDelete(LinkList* L, int i, ElemType* e); 

//����12��������ӡ������
status ListTraverse(LinkList L); 

//���ӹ���1������ת
status reverseList(LinkList L);

//���ӹ���2��ɾ������ĵ����� n �����
status RemoveNthFromEnd(LinkList L, int n);

//���ӹ���3����������
status sortList(LinkList L);

//���ӹ���4���������浽�ļ�
status SaveList(LinkList L, char filename[]);

//���ӹ��� 4�����ļ���������
status LoadList(LinkList* L, const char* filename);

//���ӹ���5�����������

/* ��ʼ������������� */
void InitMultiList(MultiList* ml);

/* �����µĵ�������������� */
status CreateNewList(MultiList* ml);

/* ɾ����������ָ�������ĵ����� */
status RemoveList(MultiList* ml, char listNames[][30], const char* targetName);

/* �л���ǰ����� */
status SwitchCurrentList(MultiList* ml, int index);

/* ��ʾ������������������������ʾ��ż��������ȣ�����ǰ��������� */
void ListAllLists(MultiList* ml);

//�˵���ӡ����
void PrintMenu();
void PrintSubMenu();
void PrintSubSubMenu(char* listname);

