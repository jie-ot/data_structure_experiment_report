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
#define INF 1000000    //定义的无穷大
#define MAX_GRAPHS 20
#define NAME_LEN 50    // 每个图的名称最多 50 个字符

typedef int status;
typedef int KeyType;
typedef enum { DG, DN, UDG, UDN } GraphKind; //有向图，有向网，无向图，无向网

typedef struct {                 //顶点类型定义
	KeyType key;                 //顶点关键字
	char others[20];
} VertexType; 

typedef struct ArcNode {         //表结点类型定义
	int adjvex;                  //顶点位置编号，通过这个索引可以找到某点的关键字 
	struct ArcNode* nextarc;	 //下一个表结点指针
} ArcNode;

typedef struct VNode {			 //头结点及其数组类型定义
	VertexType data;       	     //顶点信息
	ArcNode* firstarc;      	 //指向第一条弧
} VNode, AdjList[MAX_VERTEX_NUM];

typedef struct {               //邻接表的类型定义
	AdjList vertices;           //头结点数组
	int vexnum, arcnum;         //顶点数、弧数
	GraphKind  kind;            //图的类型
} ALGraph;

typedef struct {
	ALGraph* graphs[MAX_GRAPHS];  //存放多个图的指针
	char names[MAX_GRAPHS][NAME_LEN];
	int count;                    //当前图的数量
} GraphManager;

status CreateGraph(ALGraph* G, VertexType V[], KeyType VR[][2]); //函数1：创建无向图
status DestroyGraph(ALGraph* G); //函数2：销毁图
int LocateVex(ALGraph G, KeyType u); //函数3：查找顶点
status PutVex(ALGraph* G, KeyType u, VertexType value); //函数4：顶点赋值
int FirstAdjVex(ALGraph G, KeyType u); //函数5：获得第一邻接点
int NextAdjVex(ALGraph G, KeyType v, KeyType w); //函数6：获得下一邻接点
status InsertVex(ALGraph* G, VertexType v); //函数7：插入顶点
status DeleteVex(ALGraph* G, KeyType v); //函数8：删除顶点
status InsertArc(ALGraph* G, KeyType v, KeyType w); //函数9：插入弧
status DeleteArc(ALGraph* G, KeyType v, KeyType w); //函数10：删除弧
void visit(VertexType); //访问函数
void DFS(ALGraph* G, int i, int visited[], void (*visit)(VertexType)); //深度优先搜索遍历辅助函数
status DFSTraverse(ALGraph* G, void (*visit)(VertexType)); //函数11：深度优先搜索遍历
status BFSTraverse(ALGraph* G, void (*visit)(VertexType)); //函数12：广度优先搜索遍历

int* VerticesSetLessThanK(ALGraph* G, int v, int k, int* pSize); //附加功能1：求距离小于k的顶点集合
int ShortestPathLength(ALGraph* G, int v, int w); //附加功能2：求顶点间最短路径和长度
void dummyVisit(VertexType v);
int ConnectedComponentsNums(ALGraph* G); //附加功能3：求图的连通分量
status SaveGraph(ALGraph G, char FileName[]); //附加功能4：实现图的文件形式保存（？）
status LoadGraph(ALGraph* G, char FileName[]); //读入文件中的结点数据创建无向图的邻接表

/*附加功能5：多个图管理*/
void InitGraphManager(GraphManager* gm); //初始化多图管理器
status AddGraph(GraphManager* gm, ALGraph* G, const char name[]); //加入新的图
status DeleteGraph(GraphManager* gm, const char name[]);  //删除图
void DisplayGraphManager(GraphManager* gm); //显示所有图的状态
ALGraph* GetGraphByName(GraphManager* gm, const char name[]); //选择某个图操作

/*菜单函数*/
void PrintMenu();
void PrintSubMenu();
void PrintSubSubMenu(char* listname);