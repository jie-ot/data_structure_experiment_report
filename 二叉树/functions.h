#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_TREE_SIZE 100
#define MAX_BTREES 100

typedef int status;
typedef int KeyType;
typedef struct {
	KeyType  key;   //���ؼ���
	char others[20];
} TElemType; //������������Ͷ���

typedef struct BiTNode {  //����������Ķ���
	TElemType  data;
	struct BiTNode* lchild, * rchild;
} BiTNode, * BiTree;

// ����������������������������ƺͶ�����ָ��
typedef struct {
	char name[50];  // ����������
	BiTree tree;    // ָ����������ڵ��ָ��
} BiTreeItem;

// �����������ṹ��˳���
typedef struct {
	BiTreeItem items[MAX_BTREES]; // ��Ŷ�������������������
	int count;                    // ��ǰ����Ķ���������
} BiTreeManager;

status CreateBiTree_Recursive(BiTree* T, TElemType definition[], int* index); //���������Ķ�����ǰ��������д�����������������
status CreateBiTree_PreIn(BiTree* T, TElemType pre[], TElemType in[], int n); //ǰ��+���򴴽���������������
status CreateBiTree_PostIn(BiTree* T, TElemType post[], TElemType in[], int n); //����+���򴴽���������������
status CreateBiTree(BiTree* T, TElemType definition[], int choice); //����1������������

status InitBiTree(BiTree* T); //��ʼ��������
status DestroyBiTree(BiTree* T); //����2�����ٶ�����
status ClearBiTree(BiTree* T); //����3����ն�����
status BiTreeEmpty(BiTree T); //����4���������п�
int BiTreeDepth(BiTree T); //����5��������������
BiTNode* LocateNode(BiTree T, KeyType e); //����6�����ҽ��
status Assign(BiTree* T, KeyType e, TElemType value); //����7����㸳ֵ
BiTNode* GetSibling(BiTree T, KeyType e); //����8������ֵܽ��
status InsertNode(BiTree* T, KeyType e, int LR, TElemType c); //����9��������
BiTNode* FindNodeWithParent(BiTree T, KeyType e, BiTNode* parent, BiTNode** outParent); //ɾ����㸨�����������ش�ɾ������˫�׽��
status DeleteNode(BiTree* T, KeyType e); //����10��ɾ�����
void visit(BiTree);
status PreOrderTraverse(BiTree T, void (*visit)(BiTree)); //����11���������
status InOrderTraverse(BiTree T, void (*visit)(BiTree)); //����12��1�����������
status InOderTraverse_nonrecursive(BiTree T, void (*visit)(BiTree)); //����12��2������������ķǵݹ�ʵ��
status PostOrderTraverse(BiTree T, void (*visit)(BiTree)); //����13���������
status LevelOrderTraverse(BiTree T, void (*visit)(BiTree)); //����14���������

int MaxPathSum(BiTree T); //���ӹ���1�����·����
BiTNode* LowestCommonAncestor(BiTree T, KeyType e1, KeyType e2); //���ӹ���2����������������
void InvertTree(BiTree T); //���ӹ���3����ת������
void SaveBiTree_PreOrder(BiTree T, FILE* fp); //�������������ļ���������
status SaveBiTree(BiTree T, char FileName[]); //���ӹ���4�����������ļ���ʽ����
status LoadBiTree(BiTree* T, char FileName[]); //���ӹ���4���ļ����ش���������
/*���ӹ���5�������������*/
status InitBiTreeManager(BiTreeManager* manager);
status AddBiTree(BiTreeManager* manager, char name[], BiTree tree);
status RemoveBiTree(BiTreeManager* manager, char name[]);
void ListBiTrees(BiTreeManager* manager);
BiTree GetBiTree(BiTreeManager* manager, char name[]);

/*�˵�����*/
void PrintMenu();
void PrintSubMenu();
void PrintSubSubMenu(char* listname);