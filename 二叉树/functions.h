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
	KeyType  key;   //结点关键字
	char others[20];
} TElemType; //二叉树结点类型定义

typedef struct BiTNode {  //二叉链表结点的定义
	TElemType  data;
	struct BiTNode* lchild, * rchild;
} BiTNode, * BiTree;

// 单个二叉树管理项，包含二叉树名称和二叉树指针
typedef struct {
	char name[50];  // 二叉树名称
	BiTree tree;    // 指向二叉树根节点的指针
} BiTreeItem;

// 多二叉树管理结构：顺序表
typedef struct {
	BiTreeItem items[MAX_BTREES]; // 存放多个二叉树管理项的数组
	int count;                    // 当前管理的二叉树个数
} BiTreeManager;

status CreateBiTree_Recursive(BiTree* T, TElemType definition[], int* index); //带空子树的二叉树前序遍历序列创建二叉树辅助函数
status CreateBiTree_PreIn(BiTree* T, TElemType pre[], TElemType in[], int n); //前序+中序创建二叉树辅助函数
status CreateBiTree_PostIn(BiTree* T, TElemType post[], TElemType in[], int n); //后序+中序创建二叉树辅助函数
status CreateBiTree(BiTree* T, TElemType definition[], int choice); //函数1：创建二叉树

status InitBiTree(BiTree* T); //初始化二叉树
status DestroyBiTree(BiTree* T); //函数2：销毁二叉树
status ClearBiTree(BiTree* T); //函数3：清空二叉树
status BiTreeEmpty(BiTree T); //函数4：二叉树判空
int BiTreeDepth(BiTree T); //函数5：求二叉树的深度
BiTNode* LocateNode(BiTree T, KeyType e); //函数6：查找结点
status Assign(BiTree* T, KeyType e, TElemType value); //函数7：结点赋值
BiTNode* GetSibling(BiTree T, KeyType e); //函数8：获得兄弟结点
status InsertNode(BiTree* T, KeyType e, int LR, TElemType c); //函数9：插入结点
BiTNode* FindNodeWithParent(BiTree T, KeyType e, BiTNode* parent, BiTNode** outParent); //删除结点辅助函数，返回待删除结点的双亲结点
status DeleteNode(BiTree* T, KeyType e); //函数10：删除结点
void visit(BiTree);
status PreOrderTraverse(BiTree T, void (*visit)(BiTree)); //函数11：先序遍历
status InOrderTraverse(BiTree T, void (*visit)(BiTree)); //函数12（1）：中序遍历
status InOderTraverse_nonrecursive(BiTree T, void (*visit)(BiTree)); //函数12（2）：中序遍历的非递归实现
status PostOrderTraverse(BiTree T, void (*visit)(BiTree)); //函数13：后序遍历
status LevelOrderTraverse(BiTree T, void (*visit)(BiTree)); //函数14：层序遍历

int MaxPathSum(BiTree T); //附加功能1：最大路径和
BiTNode* LowestCommonAncestor(BiTree T, KeyType e1, KeyType e2); //附加功能2：最近公共祖先求解
void InvertTree(BiTree T); //附加功能3：翻转二叉树
void SaveBiTree_PreOrder(BiTree T, FILE* fp); //二叉树保存至文件辅助函数
status SaveBiTree(BiTree T, char FileName[]); //附加功能4：二叉树的文件形式保存
status LoadBiTree(BiTree* T, char FileName[]); //附加功能4：文件加载创建二叉树
/*附加功能5：多二叉树管理*/
status InitBiTreeManager(BiTreeManager* manager);
status AddBiTree(BiTreeManager* manager, char name[], BiTree tree);
status RemoveBiTree(BiTreeManager* manager, char name[]);
void ListBiTrees(BiTreeManager* manager);
BiTree GetBiTree(BiTreeManager* manager, char name[]);

/*菜单函数*/
void PrintMenu();
void PrintSubMenu();
void PrintSubSubMenu(char* listname);