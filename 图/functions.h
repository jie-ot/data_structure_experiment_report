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
#define MAX_VERTEX_NUM 20
#define INF 1000000    //����������
#define MAX_GRAPHS 20
#define NAME_LEN 50    // ÿ��ͼ��������� 50 ���ַ�

typedef int status;
typedef int KeyType;
typedef enum { DG, DN, UDG, UDN } GraphKind; //����ͼ��������������ͼ��������

typedef struct {                 //�������Ͷ���
	KeyType key;                 //����ؼ���
	char others[20];
} VertexType; 

typedef struct ArcNode {         //�������Ͷ���
	int adjvex;                  //����λ�ñ�ţ�ͨ��������������ҵ�ĳ��Ĺؼ��� 
	struct ArcNode* nextarc;	 //��һ������ָ��
} ArcNode;

typedef struct VNode {			 //ͷ��㼰���������Ͷ���
	VertexType data;       	     //������Ϣ
	ArcNode* firstarc;      	 //ָ���һ����
} VNode, AdjList[MAX_VERTEX_NUM];

typedef struct {               //�ڽӱ�����Ͷ���
	AdjList vertices;           //ͷ�������
	int vexnum, arcnum;         //������������
	GraphKind  kind;            //ͼ������
} ALGraph;

typedef struct {
	ALGraph* graphs[MAX_GRAPHS];  //��Ŷ��ͼ��ָ��
	char names[MAX_GRAPHS][NAME_LEN];
	int count;                    //��ǰͼ������
} GraphManager;

status CreateGraph(ALGraph* G, VertexType V[], KeyType VR[][2]); //����1����������ͼ
status DestroyGraph(ALGraph* G); //����2������ͼ
int LocateVex(ALGraph G, KeyType u); //����3�����Ҷ���
status PutVex(ALGraph* G, KeyType u, VertexType value); //����4�����㸳ֵ
int FirstAdjVex(ALGraph G, KeyType u); //����5����õ�һ�ڽӵ�
int NextAdjVex(ALGraph G, KeyType v, KeyType w); //����6�������һ�ڽӵ�
status InsertVex(ALGraph* G, VertexType v); //����7�����붥��
status DeleteVex(ALGraph* G, KeyType v); //����8��ɾ������
status InsertArc(ALGraph* G, KeyType v, KeyType w); //����9�����뻡
status DeleteArc(ALGraph* G, KeyType v, KeyType w); //����10��ɾ����
void visit(VertexType); //���ʺ���
void DFS(ALGraph* G, int i, int visited[], void (*visit)(VertexType)); //�����������������������
status DFSTraverse(ALGraph* G, void (*visit)(VertexType)); //����11�����������������
status BFSTraverse(ALGraph* G, void (*visit)(VertexType)); //����12�����������������

int* VerticesSetLessThanK(ALGraph* G, int v, int k, int* pSize); //���ӹ���1�������С��k�Ķ��㼯��
int ShortestPathLength(ALGraph* G, int v, int w); //���ӹ���2���󶥵�����·���ͳ���
void dummyVisit(VertexType v);
int ConnectedComponentsNums(ALGraph* G); //���ӹ���3����ͼ����ͨ����
status SaveGraph(ALGraph G, char FileName[]); //���ӹ���4��ʵ��ͼ���ļ���ʽ���棨����
status LoadGraph(ALGraph* G, char FileName[]); //�����ļ��еĽ�����ݴ�������ͼ���ڽӱ�

/*���ӹ���5�����ͼ����*/
void InitGraphManager(GraphManager* gm); //��ʼ����ͼ������
status AddGraph(GraphManager* gm, ALGraph* G, const char name[]); //�����µ�ͼ
status DeleteGraph(GraphManager* gm, const char name[]);  //ɾ��ͼ
void DisplayGraphManager(GraphManager* gm); //��ʾ����ͼ��״̬
ALGraph* GetGraphByName(GraphManager* gm, const char name[]); //ѡ��ĳ��ͼ����

/*�˵�����*/
void PrintMenu();
void PrintSubMenu();
void PrintSubSubMenu(char* listname);