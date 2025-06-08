#define _CRT_SECURE_NO_WARNINGS

#include"functions.h"

int main(void)
{
    int choice;
    ALGraph* currentGraph = NULL;
    GraphManager gm;
    InitGraphManager(&gm);

    while (1)
    {
        PrintMenu();
        scanf("%d", &choice);
        switch (choice)
        {
        case 0:
            printf("退出系统！\n");
            exit(0);
            break;
        case 1:
        {
            // 创建单个图
            if (currentGraph != NULL)
            {
                printf("当前已有图,不能再创建图！!\n");
                break;
            }
            int n, m;
            printf("请输入顶点个数 (<= %d): ", MAX_VERTEX_NUM);
            scanf("%d", &n);
            if (n <= 0 || n > MAX_VERTEX_NUM) {
                printf("顶点个数非法！\n");
                break;
            }
            VertexType V[MAX_VERTEX_NUM + 1];
            for (int i = 0; i < n; i++) {
                printf("请输入第%d个顶点的关键字（整数）和其他信息(字符串): ", i + 1);
                scanf("%d %s", &V[i].key, V[i].others);
            }
            // 设置哨兵，标识顶点输入结束
            V[n].key = -1;

            printf("请输入边数: ");
            scanf("%d", &m);
            KeyType VR[MAX_VERTEX_NUM + 1][2];
            for (int i = 0; i < m; i++) {
                printf("请输入第%d条边两个邻点的关键字: ", i + 1);
                scanf("%d %d", &VR[i][0], &VR[i][1]);
            }
            VR[m][0] = -1; VR[m][1] = -1;

            currentGraph = (ALGraph*)malloc(sizeof(ALGraph));
            if (currentGraph == NULL) {
                printf("内存分配失败！\n");
                break;
            }
            if (CreateGraph(currentGraph, V, VR) == OK)
                printf("图创建成功！\n");
            else {
                printf("图创建失败！\n");
                free(currentGraph);
                currentGraph = NULL;
            }
        }
        break;
        case 2:
        {
            // 销毁当前单图
            if (currentGraph == NULL) {
                printf("当前没有图！\n");
                break;
            }
            if (DestroyGraph(currentGraph) == OK) {
                free(currentGraph);
                currentGraph = NULL;
                printf("图销毁成功！\n");
            }
            else {
                printf("图销毁失败！\n");
            }
        }
        break;
        case 3:
        {
            // 查找顶点
            if (currentGraph == NULL) {
                printf("当前没有图！\n");
                break;
            }
            int key;
            printf("请输入待查找的顶点关键字: ");
            scanf("%d", &key);
            int pos = LocateVex(*currentGraph, key);
            if (pos != -1)
                printf("找到关键字为%d的顶点，其下标为%d\n", key, pos);
            else
                printf("未找到该顶点！\n");
        }
        break;
        case 4:
        {
            // 顶点赋值
            if (currentGraph == NULL) {
                printf("当前没有图！\n");
                break;
            }
            int key;
            VertexType value;
            printf("请输入要赋值的顶点关键字（整数）和新的其他信息（字符串）: ");
            scanf("%d %s", &key, value.others);
            value.key = key;
            if (PutVex(currentGraph, key, value) == OK)
                printf("顶点赋值成功！\n");
            else
                printf("顶点赋值失败！\n");
        }
        break;
        case 5:
        {
            // 获得第一邻接点
            if (currentGraph == NULL) {
                printf("当前没有图！\n");
                break;
            }
            int key;
            printf("请输入待求顶点的关键字：");
            scanf("%d", &key);
            int first = FirstAdjVex(*currentGraph, key);
            if (first != -1) {
                printf("顶点%d的第一邻接点下标为%d，", key, first);
                printf("顶点信息为：%d %s\n", currentGraph->vertices[first].data.key, currentGraph->vertices[first].data.others);
            }
            else
                printf("未找到顶点%d的邻接点！\n", key);
        }
        break;
        case 6:
        {
            // 获得下一邻接点
            if (currentGraph == NULL) {
                printf("当前没有图！\n");
                break;
            }
            int v, w;
            printf("请输入顶点v和已知邻接顶点w的关键字: ");
            scanf("%d %d", &v, &w);
            int next = NextAdjVex(*currentGraph, v, w);
            if (next != -1) {
                printf("顶点%d在顶点%d之后的邻接点下标为%d，", v, w, next);
                printf("顶点信息为：%d %s\n", currentGraph->vertices[next].data.key, currentGraph->vertices[next].data.others);
            }
            else
                printf("未找到满足条件的邻接点！\n");
        }
        break;
        case 7:
        {
            // 插入顶点
            if (currentGraph == NULL) {
                printf("当前没有图！\n");
                break;
            }
            VertexType newV;
            printf("请输入要插入顶点的关键字（整数）和其它信息（字符串）:");
            scanf("%d %s", &newV.key, newV.others);
            if (InsertVex(currentGraph, newV) == OK)
                printf("顶点插入成功！\n");
            else
                printf("顶点插入失败！\n");
        }
        break;
        case 8:
        {
            // 删除顶点
            if (currentGraph == NULL) {
                printf("当前没有图！\n");
                break;
            }
            int key;
            printf("请输入要删除的顶点的关键字: ");
            scanf("%d", &key);
            if (DeleteVex(currentGraph, key) == OK)
                printf("顶点删除成功！\n");
            else
                printf("顶点删除失败！\n");
        }
        break;
        case 9:
        {
            // 插入弧
            if (currentGraph == NULL) {
                printf("当前没有图！\n");
                break;
            }
            int v, w;
            printf("请输入要插入弧的两个邻点的关键字: ");
            scanf("%d %d", &v, &w);
            if (InsertArc(currentGraph, v, w) == OK)
                printf("插入弧成功！\n");
            else
                printf("插入弧失败！\n");
        }
        break;
        case 10:
        {
            // 删除弧
            if (currentGraph == NULL) {
                printf("当前没有图！\n");
                break;
            }
            int v, w;
            printf("请输入要删除弧的两个邻点的关键字: ");
            scanf("%d %d", &v, &w);
            if (DeleteArc(currentGraph, v, w) == OK)
                printf("删除弧成功！\n");
            else
                printf("删除弧失败！\n");
        }
        break;
        case 11:
        {
            // 深度优先搜索遍历
            if (currentGraph == NULL) {
                printf("当前没有图！\n");
                break;
            }
            printf("深度优先搜索遍历结果:\n");
            if (DFSTraverse(currentGraph, visit) == OK)
                printf("\n深度优先搜索遍历完成！\n");
            else
                printf("\n深度优先搜索遍历失败！\n");
        }
        break;
        case 12:
        {
            // 广度优先搜索遍历
            if (currentGraph == NULL) {
                printf("当前没有图！\n");
                break;
            }
            printf("广度优先搜索遍历结果:\n");
            if (BFSTraverse(currentGraph, visit) == OK)
                printf("\n广度优先搜索遍历遍历完成！\n");
            else
                printf("\n广度优先搜索遍历遍历失败！\n");
        }
        break;
        case 13:
        {
            // 附加功能1：求距离小于k的顶点集合
            if (currentGraph == NULL) {
                printf("当前没有图！\n");
                break;
            }
            int v, k, pSize;
            printf("请输入起始顶点下标v和距离k: ");
            scanf("%d %d", &v, &k);
            int* set = VerticesSetLessThanK(currentGraph, v, k, &pSize);
            if (set != NULL) {
                printf("距离小于%d的顶点下标集合为：", k);
                for (int i = 0; i < pSize; i++) {
                    printf("%d ", set[i]);
                }
                printf("\n");
                free(set);
            }
            else {
                printf("操作失败或无满足条件的顶点！\n");
            }
        }
        break;
        case 14:
        {
            // 附加功能2：求顶点间最短路径和长度
            if (currentGraph == NULL) {
                printf("当前没有图！\n");
                break;
            }
            int v, w;
            printf("请输入起始顶点下标和终止顶点下标: ");
            scanf("%d %d", &v, &w);
            int length = ShortestPathLength(currentGraph, v, w);
            if (length != -1)
                printf("顶点%d到顶点%d的最短路径长度为%d\n", v, w, length);
            else
                printf("两个顶点之间无路径！\n");
        }
        break;
        case 15:
        {
            // 附加功能3：求图的连通分量数
            if (currentGraph == NULL) {
                printf("当前没有图！\n");
                break;
            }
            int comps = ConnectedComponentsNums(currentGraph);
            printf("该图的连通分量数为 %d\n", comps);
        }
        break;
        case 16:
        {
            // 附加功能4：图的文件形式保存
            if (currentGraph == NULL) {
                printf("当前没有图！\n");
                break;
            }
            char fileName[100];
            printf("请输入保存图的文件名: ");
            scanf("%s", fileName);
            if (SaveGraph(*currentGraph, fileName) == OK)
                printf("图保存成功！\n");
            else
                printf("图保存失败！\n");
        }
        break;
        case 17:
        {
            // 附加功能5：从文件加载创建图
            if (currentGraph == NULL) {
                printf("当前没有图！\n");
                break;
            }
            char fileName[100];
            printf("请输入加载图的文件名: ");
            scanf("%s", fileName);
            if (LoadGraph(currentGraph, fileName) == OK)
                printf("图加载成功！\n");
            else
                printf("图加载失败！\n");
        }
        break;
        case 18:
        {
            // 进入多图管理子系统
            int subChoice;
            while (1)
            {
                PrintSubMenu();
                scanf("%d", &subChoice);
                if (subChoice == 0)
                    break;
                switch (subChoice)
                {
                case 1:
                {
                    // 创建新的图（多图管理）
                    char name[NAME_LEN];
                    int createOption;
                    printf("请输入新图名称: ");
                    scanf("%s", name);
                    printf("请选择创建方式：1.仅初始化  2.初始化+输入数据: ");
                    scanf("%d", &createOption);
                    ALGraph* newGraph = (ALGraph*)malloc(sizeof(ALGraph));
                    if (newGraph == NULL) {
                        printf("内存分配失败！\n");
                        break;
                    }
                    if (createOption == 1) {
                        // 仅初始化：简单设置顶点数为0，弧数为0
                        newGraph->vexnum = 0;
                        newGraph->arcnum = 0;
                        newGraph->kind = UDG;
                        printf("图已初始化。\n");
                    }
                    else if (createOption == 2) {
                        // 初始化并输入数据
                        int n, m;
                        printf("请输入顶点个数 (<= %d): ", MAX_VERTEX_NUM);
                        scanf("%d", &n);
                        if (n <= 0 || n > MAX_VERTEX_NUM) {
                            printf("顶点个数非法！\n");
                            free(newGraph);
                            break;
                        }
                        VertexType V[MAX_VERTEX_NUM + 1]; //为结束哨兵流出空间
                        for (int i = 0; i < n; i++) {
                            printf("请输入第%d个顶点的关键字（整数）和其他信息(字符串): ", i + 1);
                            scanf("%d %s", &V[i].key, V[i].others);
                        }
                        // 设置哨兵，标识顶点输入结束
                        V[n].key = -1;

                        printf("请输入边数: ");
                        scanf("%d", &m);
                        KeyType VR[MAX_VERTEX_NUM + 1][2];
                        for (int i = 0; i < m; i++) {
                            printf("请输入第%d条边的两个顶点的关键字: ", i + 1);
                            scanf("%d %d", &VR[i][0], &VR[i][1]);
                        }
                        VR[m][0] = -1; VR[m][1] = -1;

                        if (CreateGraph(newGraph, V, VR) == OK)
                            printf("图创建成功！\n");
                        else {
                            printf("图创建失败！\n");
                            free(newGraph);
                            break;
                        }
                    }
                    else {
                        printf("无效的选项！\n");
                        free(newGraph);
                        break;
                    }
                    if (AddGraph(&gm, newGraph, name) == OK)
                        printf("图 '%s' 已添加到多图管理器中！\n", name);
                    else {
                        printf("添加失败！\n");
                        free(newGraph);
                    }
                }
                break;
                case 2:
                {
                    // 显示所有图状态
                    DisplayGraphManager(&gm);
                }
                break;
                case 3:
                {
                    // 删除图
                    char delName[NAME_LEN];
                    printf("请输入要删除的图名称: ");
                    scanf("%s", delName);
                    if (DeleteGraph(&gm, delName) == OK)
                        printf("图 '%s' 删除成功！\n", delName);
                    else
                        printf("删除失败！\n");
                }
                break;
                case 4:
                {
                    char opName[NAME_LEN];
                    printf("请输入要操作的图名称: ");
                    scanf("%s", opName);
                    ALGraph* opGraph = GetGraphByName(&gm, opName);
                    if (opGraph == NULL) {
                        printf("未找到图 '%s'！\n", opName);
                        break;
                    }
                    int subSubChoice;
                    while (1)
                    {
                        PrintSubSubMenu(opName);
                        scanf("%d", &subSubChoice);
                        switch (subSubChoice)
                        {
                        case 0:
                            // 返回多图管理子系统
                            printf("返回多图管理子系统。\n");
                            break;
                        case 1:
                            // 销毁当前图
                            if (DeleteGraph(&gm, opName) == OK)
                                printf("图 '%s' 已销毁并从管理系统中删除！\n", opName);
                            else
                                printf("图 '%s' 销毁失败！\n", opName);
                            // 退出子子菜单，因为所操作图已不存在
                            subSubChoice = 0;
                            break;
                        case 2:
                        {
                            int key;
                            printf("请输入待查找的顶点关键字: ");
                            scanf("%d", &key);
                            int pos = LocateVex(*opGraph, key);
                            if (pos != -1)
                                printf("找到关键字为%d的顶点，下标为%d\n", key, pos);
                            else
                                printf("未找到该顶点！\n");
                        }
                        break;
                        case 3: {
                            int oldKey, newKey;
                            VertexType value;
                            printf("请输入原顶点关键字: ");
                            scanf("%d", &oldKey);
                            printf("请输入新的顶点关键字（整数）和新的其他信息（字符串）：");
                            scanf("%d %s", &newKey, value.others);
                            value.key = newKey;
                            if (PutVex(opGraph, oldKey, value) == OK)
                                printf("顶点赋值成功！\n");
                            else
                                printf("顶点赋值失败！\n");
                            break;
                        }
                        case 4:
                        {
                            int key;
                            printf("请输入待求顶点的关键字: ");
                            scanf("%d", &key);
                            int first = FirstAdjVex(*opGraph, key);
                            if (first != -1) {
                                   printf("顶点%d的第一邻接点下标为%d，", key, first);
                                   printf("顶点信息为：%d %s\n", opGraph->vertices[first].data.key, opGraph->vertices[first].data.others);
                            }
                            else
                                printf("未找到顶点%d的第一邻接点！\n", key);
                        }
                        break;
                        case 5:
                        {
                            int v, w;
                            printf("请输入顶点v和已知邻接顶点w的关键字: ");
                            scanf("%d %d", &v, &w);
                            int next = NextAdjVex(*opGraph, v, w);
                            if (next != -1) {
                                printf("顶点%d在顶点%d之后的邻接点下标为%d，", v, w, next);
                                printf("顶点信息为：%d %s\n", opGraph->vertices[next].data.key, opGraph->vertices[next].data.others);
                            }
                            else
                                printf("未找到满足条件的邻接点！\n");
                        }
                        break;
                        case 6:
                        {
                            VertexType newV;
                            printf("请输入新顶点的关键字（整数）和其他信息（字符串）: ");
                            scanf("%d %s", &newV.key, newV.others);
                            if (InsertVex(opGraph, newV) == OK)
                                printf("顶点插入成功！\n");
                            else
                                printf("顶点插入失败！\n");
                        }
                        break;
                        case 7:
                        {
                            int key;
                            printf("请输入要删除的顶点的关键字: ");
                            scanf("%d", &key);
                            if (DeleteVex(opGraph, key) == OK)
                                printf("顶点删除成功！\n");
                            else
                                printf("顶点删除失败！\n");
                        }
                        break;
                        case 8:
                        {
                            int v, w;
                            printf("请输入要插入弧的两个邻点的关键字: ");
                            scanf("%d %d", &v, &w);
                            if (InsertArc(opGraph, v, w) == OK)
                                printf("插入弧成功！\n");
                            else
                                printf("插入弧失败！\n");
                        }
                        break;
                        case 9:
                        {
                            int v, w;
                            printf("请输入要删除弧的两个邻点关键字: ");
                            scanf("%d %d", &v, &w);
                            if (DeleteArc(opGraph, v, w) == OK)
                                printf("删除弧成功！\n");
                            else
                                printf("删除弧失败！\n");
                        }
                        break;
                        case 10:
                        {
                            printf("深度优先搜索遍历结果:\n");
                            if (DFSTraverse(opGraph, visit) == OK)
                                printf("\n深度优先搜索遍历完成！\n");
                            else
                                printf("\n深度优先搜索遍历失败！\n");
                        }
                        break;
                        case 11:
                        {
                            printf("广度优先搜索遍历结果:\n");
                            if (BFSTraverse(opGraph, visit) == OK)
                                printf("\n广度优先搜索遍历完成！\n");
                            else
                                printf("\n广度优先搜索遍历失败！\n");
                        }
                        break;
                        case 12:
                        {
                            int v, k, pSize;
                            printf("请输入起始顶点下标v和距离k: ");
                            scanf("%d %d", &v, &k);
                            int* set = VerticesSetLessThanK(opGraph, v, k, &pSize);
                            if (set != NULL) {
                                printf("距离小于%d的顶点下标集合为：", k);
                                for (int i = 0; i < pSize; i++) {
                                    printf("%d ", set[i]);
                                }
                                printf("\n");
                                free(set);
                            }
                            else {
                                printf("操作失败或无顶点满足条件。\n");
                            }
                        }
                        break;
                        case 13:
                        {
                            int v, w;
                            printf("请输入起始顶点下标和终止顶点下标: ");
                            scanf("%d %d", &v, &w);
                            int length = ShortestPathLength(opGraph, v, w);
                            if (length != -1)
                                printf("顶点%d到顶点%d的最短路径长度为%d\n", v, w, length);
                            else
                                printf("两个顶点之间无路径！\n");
                        }
                        break;
                        case 14:
                        {
                            int comps = ConnectedComponentsNums(opGraph);
                            printf("该图的连通分量数为%d\n", comps);
                        }
                        break;
                        case 15:
                        {
                            char fileName[100];
                            printf("请输入保存图的文件名: ");
                            scanf("%s", fileName);
                            if (SaveGraph(*opGraph, fileName) == OK)
                                printf("图保存成功！\n");
                            else
                                printf("图保存失败！\n");
                        }
                        break;
                        case 16:
                        {
                            char fileName[100];
                            printf("请输入加载图的文件名: ");
                            scanf("%s", fileName);
                            if (LoadGraph(opGraph, fileName) == OK)
                                printf("图数据加载成功！\n");
                            else
                                printf("图数据加载失败！\n");
                        }
                        break;
                        default:
                            printf("请输入正确的选项！\n");
                        } // end switch subSubChoice

                        if (subSubChoice == 0)
                            break;
                    } // end while sub-sub菜单
                    break;
                }
                default:
                    printf("请输入正确的选项！\n");
                }
            } 
        }
        break;
        default:
            printf("请输入正确的选项！\n");
        } 
    } 
    return 0;
}