#define _CRT_SECURE_NO_WARNINGS

#include"functions.h"

status CreateGraph(ALGraph* G, VertexType V[], KeyType VR[][2])
/*根据V和VR构造图T并返回OK，如果V和VR不正确，返回ERROR,如果有相同的关键字，返回ERROR*/
{
    int vexnum = 0;
    int flag = 0;

    for (; vexnum < MAX_VERTEX_NUM + 1; vexnum++) {   //循环确定顶点个数vexnum
        if (V[vexnum].key == -1) {
            flag = 1;
            break;
        }
    }
    //if (vexnum <= 0 || (vexnum < MAX_VERTEX_NUM && flag == 0)) return ERROR;
    if (vexnum <= 0 || flag == 0) {
        printf("顶点数不符合要求！\n");
        return ERROR;
    }

    for (int i = 0; i < vexnum; i++) {  //循环检查关键字是否重复
        for (int j = i + 1; j < vexnum; j++)
        {
            if (V[i].key == V[j].key)
            {
                printf("关键字重复！\n");
                return ERROR;
            }
        }
    }

    G->vexnum = vexnum;
    G->arcnum = 0;
    G->kind = UDG; 
    for (int i = 0; i < vexnum; i++) {  //初始化顶点数组：复制顶点信息，同时将邻接链表头置为 NULL
        G->vertices[i].data = V[i];
        G->vertices[i].firstarc = NULL;
    }

    int k = 0;
    int edgeCount = 0; // 记录边数
    while (1) {
        if (VR[k][0] == -1 && VR[k][1] == -1) break;

        int key_u = VR[k][0];
        int key_v = VR[k][1];
        int idx_u = -1, idx_v = -1; //分别为key_u和key_v在图中对应的下标

        /* 查找关键字 key_u 和 key_v 在图中对应的下标 */
        for (int i = 0; i < vexnum; i++){
            if (G->vertices[i].data.key == key_u) {
                idx_u = i;
                break;
            }
        }
        for (int i = 0; i < vexnum; i++){
            if (G->vertices[i].data.key == key_v){
                idx_v = i;
                break;
            }
        }
        if (idx_u == -1 || idx_v == -1) {
            printf("边的邻点关键字输入错误！\n");
            return ERROR;
        }

        //对 idx_u 顶点的邻接链表，检查是否已存在指向 idx_v 的边
        ArcNode* p = G->vertices[idx_u].firstarc; //p是指向下标为idx_u的点的第一条邻边
        int duplicate = 0; //0表示不存在指向 idx_v 的边，1表示存在指向 idx_v 的边
        while (p) {
            if (p->adjvex == idx_v) {
                duplicate = 1;
                break;
            }
            p = p->nextarc;
        }
        if (!duplicate) {
            //采用首插法在 idx_u 的邻接链表插入新的边结点
            ArcNode* newNode = (ArcNode*)malloc(sizeof(ArcNode));
            if (!newNode) exit(OVERFLOW);
            newNode->adjvex = idx_v;
            newNode->nextarc = G->vertices[idx_u].firstarc;     //注意采用的是首插法，更高效！！！
            G->vertices[idx_u].firstarc = newNode;
        }

        //对 idx_v 顶点的邻接链表，同样检查是否已存在指向 idx_u 的边
        duplicate = 0;
        p = G->vertices[idx_v].firstarc;
        while (p){
            if (p->adjvex == idx_u){
                duplicate = 1;
                break;
            }
            p = p->nextarc;
        }
        if (!duplicate) {
            ArcNode* newNode = (ArcNode*)malloc(sizeof(ArcNode));
            if (!newNode) exit(OVERFLOW);
            newNode->adjvex = idx_u;
            newNode->nextarc = G->vertices[idx_v].firstarc;   //注意采用的是首插法！！！
            G->vertices[idx_v].firstarc = newNode;
            edgeCount++;  //仅当两侧均未插入时计数一次这条边
        }
        k++;
    }
    G->arcnum = edgeCount;
    return OK;
}
status DestroyGraph(ALGraph* G)
/*销毁无向图G,删除G的全部顶点和边*/
{
    if (G == NULL || G->vertices == NULL) return ERROR;

    ArcNode* p, * temp;
    for (int i = 0; i < G->vexnum; i++) {  //遍历每个顶点，释放邻接链表中所有动态分配的边结点
        p = G->vertices[i].firstarc;
        while (p != NULL) {
            temp = p;
            p = p->nextarc;
            free(temp);
        }
        //将当前顶点的邻接链表头置为空
        G->vertices[i].firstarc = NULL;
    }
    //销毁后，将顶点数和弧数置为0
    G->vexnum = 0;
    G->arcnum = 0;

    return OK;
}
int LocateVex(ALGraph G, KeyType u)
//根据u在图G中查找顶点，查找成功返回位序，否则返回-1；
{
    if (G.vertices == NULL) return INFEASIBLE;
    int location = -1;
    for (int i = 0; i < G.vexnum; i++) {
        if (G.vertices[i].data.key == u) {
            location = i;
            break;
        }
    }
    return location;
}
status PutVex(ALGraph* G, KeyType oldKey, VertexType value)
{
    if (G == NULL || G->vertices == NULL) return ERROR;

    int count_u = 0;   
    int target_idx = -1; 

    for (int i = 0; i < G->vexnum; i++) {
        if (G->vertices[i].data.key == oldKey) {
            count_u++;
            target_idx = i;
        }
    }
    if (count_u != 1) return ERROR; 

    // 检查新关键字是否已被另一个顶点使用
    for (int i = 0; i < G->vexnum; i++) {
        if (i == target_idx) continue;  // 跳过目标顶点自身
        if (G->vertices[i].data.key == value.key)
            return ERROR;  // 新关键字已存在
    }

    G->vertices[target_idx].data = value;
    return OK;
}
int FirstAdjVex(ALGraph G, KeyType u)
//u是和G中顶点关键字类型相同的给定值。返回关键字为u的顶点第一个邻接顶点位置序号（简称位序），否则返回-1
{
    if (G.vertices == NULL) return -1;
    for (int i = 0; i < G.vexnum; i++) {
        if (G.vertices[i].data.key == u) {
            if (G.vertices[i].firstarc != NULL) {
                return G.vertices[i].firstarc->adjvex;
            }
            else return -1;
        }
    }
    return -1;
}
int NextAdjVex(ALGraph G, KeyType v, KeyType w)
//v对应G的一个顶点,w对应v的邻接顶点；操作结果是返回v的（相对于w）下一个邻接顶点的位序；如果w是最后一个邻接顶点，或v、w对应顶点不存在，则返回-1。
{
    if (G.vertices == NULL) return -1;
    for (int i = 0; i < G.vexnum; i++) {
        if (G.vertices[i].data.key == v) {
            ArcNode* p = G.vertices[i].firstarc;
            while (p != NULL) {
                if (G.vertices[p->adjvex].data.key == w) {
                    if (p->nextarc != NULL) return p->nextarc->adjvex;
                    else return -1;
                }
                p = p->nextarc;
            }
        }
    }
    return -1;
}
status InsertVex(ALGraph* G, VertexType v)
//在图G中插入新关键字为v的顶点（要求关键字具有唯一性，注意判断顶点个数是否已满）。成功返回OK，否则返回ERROR。
{
    if (G == NULL || G->vexnum == MAX_VERTEX_NUM) return ERROR;
    for (int i = 0; i < G->vexnum; i++) {
        if (G->vertices[i].data.key == v.key) return ERROR;
    }
    G->vertices[G->vexnum].data = v;
    G->vertices[G->vexnum].firstarc = NULL;
    G->vexnum++;
    return OK;
}
status DeleteVex(ALGraph* G, KeyType v)
//v是和G中顶点关键字类型相同的给定值；操作结果是在图G中删除关键字v对应的顶点以及相关的弧。成功返回OK，否则返回ERROR。
{
    if (G == NULL) return ERROR;

    int v_pos = -1; //查找关键字为v的顶点在顶点数组中的位置
    for (int i = 0; i < G->vexnum; i++) {
        if (G->vertices[i].data.key == v) {
            v_pos = i;
            break;
        }
    }
    if (v_pos == -1) return ERROR;

    //删除所有其他顶点邻接表中指向被删除顶点的弧，并调整弧中存储的位序
    for (int i = 0; i < G->vexnum; i++) {
        if (i == v_pos) continue;  // 待删除顶点自己的邻接表，后面单独处理

        ArcNode* p = G->vertices[i].firstarc;
        ArcNode* prev = NULL;
        while (p != NULL) {
            if (p->adjvex == v_pos) {
                // 找到指向待删除顶点的弧，则删除它
                ArcNode* temp = p;
                if (prev == NULL) {
                    // p 为链表头结点
                    G->vertices[i].firstarc = p->nextarc;
                }
                else {
                    prev->nextarc = p->nextarc;
                }
                p = p->nextarc;
                free(temp);
                G->arcnum--;
            }
            else {
                // 如果该弧的adjvex大于delIndex，由于顶点数组将左移1个位置，因此需要减1
                if (p->adjvex > v_pos) p->adjvex--;
                prev = p;
                p = p->nextarc;
            }
        }
    }

    //删除待删除顶点自身邻接表中的所有弧
    //由于是无向图，一条边会被两个单链表所记录，故前面删除边的时候已经G.arcnum--了，所以这里不用再减了
    ArcNode* p_del = G->vertices[v_pos].firstarc;
    while (p_del != NULL) {
        ArcNode* temp = p_del;
        p_del = p_del->nextarc;
        free(temp);
    }

    // 4. 将待删除顶点在顶点数组中之后的顶点整体向前移动
    for (int i = v_pos; i < G->vexnum - 1; i++) {
        G->vertices[i] = G->vertices[i + 1];
    }
    G->vexnum--;

    return OK;
}
status InsertArc(ALGraph* G, KeyType v, KeyType w)
//v、w是和G中顶点关键字类型相同的给定值；操作结果是在图G中增加弧<v,w>。成功返回OK，否则返回ERROR。
{
    if (G == NULL) return ERROR;
    int v_pos = -1, w_pos = -1;
    // 查找顶点 v 和 w 在图中的下标
    for (int i = 0; i < G->vexnum; i++) {
        if (G->vertices[i].data.key == v) {
            v_pos = i;
        }
        if (G->vertices[i].data.key == w) {
            w_pos = i;
        }
    }
    if (v_pos == -1 || w_pos == -1) return ERROR;

    // 检查是否已经存在<v, w>这条边，避免重复插入
    ArcNode* p = G->vertices[v_pos].firstarc;
    while (p != NULL) {
        if (p->adjvex == w_pos) return ERROR;
        p = p->nextarc;
    }

    // 使用头插法在 v 的邻接表中插入一节点代表边<v, w>
    ArcNode* newarc_vw = (ArcNode*)malloc(sizeof(ArcNode));
    if (newarc_vw == NULL) return OVERFLOW;
    newarc_vw->adjvex = w_pos;
    newarc_vw->nextarc = G->vertices[v_pos].firstarc;
    G->vertices[v_pos].firstarc = newarc_vw;

    // 同样在 w 的邻接表中插入一节点代表边<w, v>
    ArcNode* newarc_wv = (ArcNode*)malloc(sizeof(ArcNode));
    if (newarc_wv == NULL) {
        // 释放已经分配给 v 的新节点，防止内存泄漏
        free(newarc_vw);
        return OVERFLOW;
    }
    newarc_wv->adjvex = v_pos;
    newarc_wv->nextarc = G->vertices[w_pos].firstarc;
    G->vertices[w_pos].firstarc = newarc_wv;

    G->arcnum++;
    return OK;
}
status DeleteArc(ALGraph* G, KeyType v, KeyType w)
//v、w是和G中顶点关键字类型相同的给定值；操作结果是在图G中删除弧<v,w>。成功返回OK，否则返回ERROR。
{
    if (G == NULL) return ERROR;
    int v_pos = -1, w_pos = -1;
    int flag1 = 0, flag2 = 0;
    for (int i = 0; i < G->vexnum; i++) {
        if (G->vertices[i].data.key == v) v_pos = i;
        if (G->vertices[i].data.key == w) w_pos = i;
    }
    if (v_pos == -1 || w_pos == -1) return ERROR;

    ArcNode* p1 = G->vertices[v_pos].firstarc;
    ArcNode* prev1 = NULL;
    while (p1 != NULL) {
        if (p1->adjvex == w_pos) {
            flag1 = 1;
            if (prev1 == NULL) G->vertices[v_pos].firstarc = p1->nextarc; //删除头结点，要单独讨论
            else prev1->nextarc = p1->nextarc;
            free(p1);
            break;
        }
        prev1 = p1;
        p1 = p1->nextarc;
    }
    ArcNode* p2 = G->vertices[w_pos].firstarc;
    ArcNode* prev2 = NULL;
    while (p2 != NULL) {
        if (p2->adjvex == v_pos) {
            flag2 = 1;
            if (prev2 == NULL) G->vertices[w_pos].firstarc = p2->nextarc; //删除头结点，要单独讨论
            else prev2->nextarc = p2->nextarc;
            free(p2);
            break;
        }
        prev2 = p2;
        p2 = p2->nextarc;
    }
    if (flag1 == 0 || flag2 == 0) return ERROR;

    G->arcnum--;
    return OK;
}
/*深度优先搜索遍历*/
void visit(VertexType v){
    printf(" %d %s ", v.key, v.others);
}
void DFS(ALGraph* G, int i, int visited[], void (*visit)(VertexType)) 
// 辅助递归函数：从顶点 i 出发进行深度优先搜索
{
    // 标记当前顶点已访问，并调用visit函数访问该顶点的数据
    visited[i] = TRUE;
    visit(G->vertices[i].data);

    // 遍历顶点 i 的邻接表，对所有尚未访问的临接顶点调用DFS
    ArcNode* p = G->vertices[i].firstarc;
    while (p != NULL) {
        if (!visited[p->adjvex])
            DFS(G, p->adjvex, visited, visit);
        p = p->nextarc;
    }
}
status DFSTraverse(ALGraph* G, void (*visit)(VertexType)) 
// 主函数：对图 G 进行深度优先搜索遍历
{
    int visited[MAX_VERTEX_NUM];

    // 初始化所有顶点为未访问
    for (int i = 0; i < G->vexnum; i++) {
        visited[i] = FALSE;
    }

    // 依次对每个未被访问的顶点调用 DFS（处理非连通图）
    for (int i = 0; i < G->vexnum; i++) {
        if (!visited[i])
            DFS(G, i, visited, visit);
    }
    return OK;
}
/*广度优先搜索遍历*/
status BFSTraverse(ALGraph* G, void (*visit)(VertexType)) 
{
    int visited[MAX_VERTEX_NUM];
    for (int i = 0; i < G->vexnum; i++) {
        visited[i] = FALSE;
    }

    int queue[MAX_VERTEX_NUM];
    int front = 0, rear = 0; // 队头、队尾指针

    for (int i = 0; i < G->vexnum; i++) {
        if (!visited[i]) {
            // 将未访问的顶点入队，并标记为已访问
            visited[i] = TRUE;
            visit(G->vertices[i].data);
            queue[rear++] = i;

            // 当队列不空时，持续将队头出队，访问其所有邻接顶点
            while (front < rear) {
                int cur = queue[front++];
                // 遍历当前顶点 cur 的所有邻接点
                ArcNode* p = G->vertices[cur].firstarc;
                while (p != NULL) {
                    if (!visited[p->adjvex]) {
                        // 访问并入队
                        visited[p->adjvex] = TRUE;
                        visit(G->vertices[p->adjvex].data);
                        queue[rear++] = p->adjvex;
                    }
                    p = p->nextarc;
                }
            }
        }
    }
    return OK;
}

//距离小于k的顶点集合，利用BFS记录从顶点v到其它各顶点的最短距离，只有距离小于k的顶点被保留。
int* VerticesSetLessThanK(ALGraph* G, int v, int k, int* pSize) {
    if (G == NULL || v < 0 || v >= G->vexnum || pSize == NULL)
        return NULL;

    //动态分配数组保存各顶点到v的最短距离
    int* dist = (int*)malloc(G->vexnum * sizeof(int));
    if (dist == NULL) return NULL;
    for (int i = 0; i < G->vexnum; i++)
        dist[i] = INF;
    dist[v] = 0;

    //使用队列实现BFS
    int queue[MAX_VERTEX_NUM];
    int front = 0, rear = 0;
    queue[rear++] = v;

    while (front < rear) {
        int cur = queue[front++];
        //当当前顶点距离达到k-1时，若扩展后续顶点可能达到k，不再推进队列
        if (dist[cur] >= k - 1)
            continue;

        ArcNode* p = G->vertices[cur].firstarc;
        while (p) {
            int adj = p->adjvex;
            if (dist[adj] == INF) {  //若尚未标记过
                dist[adj] = dist[cur] + 1;
                if (dist[adj] < k)
                    queue[rear++] = adj;
            }
            p = p->nextarc;
        }
    }

    //统计所有距离 < k 的顶点数
    int count = 0;
    for (int i = 0; i < G->vexnum; i++) {
        if (dist[i] < k)
            count++;
    }

    //分配数组保存结果，存储满足条件顶点的下标
    int* result = (int*)malloc(count * sizeof(int));
    if (result == NULL) {
        free(dist);
        return NULL;
    }
    int index = 0;
    for (int i = 0; i < G->vexnum; i++) {
        if (dist[i] < k)
            result[index++] = i;
    }
    *pSize = count;
    free(dist);
    return result;
}
//顶点间最短路径和长度
int ShortestPathLength(ALGraph* G, int v, int w)
{
    if (G == NULL || v < 0 || w < 0 || v >= G->vexnum || w >= G->vexnum)
        return -1;

    int distance[MAX_VERTEX_NUM];
    for (int i = 0; i < G->vexnum; i++)
        distance[i] = INF;
    distance[v] = 0;

    int queue[MAX_VERTEX_NUM];
    int front = 0, rear = 0;
    queue[rear++] = v;

    while (front < rear)
    {
        int cur = queue[front++];
        if (cur == w)
            return distance[w];
        ArcNode* p = G->vertices[cur].firstarc;
        while (p)
        {
            int adj = p->adjvex;
            if (distance[adj] == INF)
            {
                distance[adj] = distance[cur] + 1;
                queue[rear++] = adj;
            }
            p = p->nextarc;
        }
    }
    return -1;  //无法到达w
}
//图的连通分量数
void dummyVisit(VertexType v) {} //空visit函数 
int ConnectedComponentsNums(ALGraph* G)
{
    if (G == NULL)
        return -1;
    int visited[MAX_VERTEX_NUM] = { 0 };
    int count = 0;
    for (int i = 0; i < G->vexnum; i++) {
        if (!visited[i]) {
            /* 对连通分量中所有顶点调用 DFS，使用 dummyVisit 不打印或处理数据 */
            DFS(G, i, visited, dummyVisit);
            count++;
        }
    }
    return count;
}
/*将无向图的数据写到文件中*/
status SaveGraph(ALGraph G, char FileName[]) 
{
    FILE* fp = fopen(FileName, "w");
    if (fp == NULL)
        return ERROR;

    // 对每个顶点写一行：先写顶点数据，然后逆序写出它邻接表中各弧结点的 adjvex 值
    for (int i = 0; i < G.vexnum; i++) {
        // 先输出顶点关键字和其他数据
        fprintf(fp, "%d %s", G.vertices[i].data.key, G.vertices[i].data.others);

        // 将该顶点邻接链表中的结点 adjvex 值先存入临时数组中
        int tempArr[MAX_VERTEX_NUM];
        int count = 0;
        ArcNode* p = G.vertices[i].firstarc;
        while (p != NULL) {
            tempArr[count++] = p->adjvex;
            p = p->nextarc;
        }

        // 由于采用首插法，链表中的顺序是逆序的，为保证输出时和预期一致，逆序输出临时数组
        for (int j = count - 1; j >= 0; j--) {
            fprintf(fp, " %d", tempArr[j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
    return OK;
}
/*读入文件中的结点数据创建无向图的邻接表*/
status LoadGraph(ALGraph* G, char FileName[]) {
    FILE* fp = fopen(FileName, "r");
    if (fp == NULL)
        return ERROR;

    char line[256];
    int vertexCount = 0;
    int totalAdjCount = 0;
    // 逐行读取文件，依据行数确定顶点个数
    while (fgets(line, sizeof(line), fp) != NULL) {
        if (strlen(line) <= 1) continue; // 如果行内容为空，则跳过

        char* token = strtok(line, " \n");
        if (token == NULL) continue;
        int key = atoi(token);// 第一个标记：顶点关键字

        token = strtok(NULL, " \n");
        if (token == NULL) continue;
        char others[20];
        strcpy(others, token);

        // 将读入数据存入顶点数组
        G->vertices[vertexCount].data.key = key;
        strcpy(G->vertices[vertexCount].data.others, others);
        G->vertices[vertexCount].firstarc = NULL;

        // 后续标记每个为邻接结点的下标（以整数读取）
        token = strtok(NULL, " \n");
        while (token != NULL) {
            int adjIndex = atoi(token);
            // 采用首插法建立链表
            ArcNode* p = (ArcNode*)malloc(sizeof(ArcNode));
            if (p == NULL) {
                fclose(fp);
                return OVERFLOW;
            }
            p->adjvex = adjIndex;
            p->nextarc = G->vertices[vertexCount].firstarc;
            G->vertices[vertexCount].firstarc = p;
            totalAdjCount++;
            token = strtok(NULL, " \n");
        }
        vertexCount++;
    }
    G->vexnum = vertexCount;
    G->arcnum = totalAdjCount / 2; // 对无向图，每条边存储两次
    G->kind = UDG;
    fclose(fp);
    return OK;
}

/*多个图管理*/
void InitGraphManager(GraphManager* gm) 
{
    if (gm == NULL) return;
    gm->count = 0;
    // 初始化名字字符串为空
    for (int i = 0; i < MAX_GRAPHS; i++) {
        gm->names[i][0] = '\0';
        gm->graphs[i] = NULL;
    }
}
status AddGraph(GraphManager* gm, ALGraph* G, const char name[]) 
{
    if (gm == NULL || G == NULL || name == NULL)
        return ERROR;
    if (gm->count >= MAX_GRAPHS)
        return ERROR;
    gm->graphs[gm->count] = G;
    strncpy(gm->names[gm->count], name, NAME_LEN - 1);
    gm->names[gm->count][NAME_LEN - 1] = '\0';  // 确保字符串终止
    gm->count++;
    return OK;
}
status DeleteGraph(GraphManager* gm, const char name[]) 
{
    if (gm == NULL || name == NULL)
        return ERROR;
    int index = -1;
    for (int i = 0; i < gm->count; i++) {
        if (strcmp(gm->names[i], name) == 0) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("未找到图：%s\n", name);
        return ERROR;
    }
    if (DestroyGraph(gm->graphs[index]) != OK) {
        return ERROR;
    }
    free(gm->graphs[index]);  // 释放图结构体内存
    // 将后续图和名称前移覆盖删除的图
    for (int i = index; i < gm->count - 1; i++) {
        gm->graphs[i] = gm->graphs[i + 1];
        strcpy(gm->names[i], gm->names[i + 1]);
    }
    gm->graphs[gm->count - 1] = NULL;
    gm->names[gm->count - 1][0] = '\0';
    gm->count--;
    return OK;
}
void DisplayGraphManager(GraphManager* gm) 
{
    if (gm == NULL) return;
    printf("当前管理的图数量：%d\n", gm->count);
    for (int i = 0; i < gm->count; i++) {
        printf("序号：%d, 名称：%s\n", i + 1, gm->names[i]);
    }
}
ALGraph* GetGraphByName(GraphManager* gm, const char name[])
{
    if (gm == NULL || name == NULL)
        return NULL;
    for (int i = 0; i < gm->count; i++) {
        if (strcmp(gm->names[i], name) == 0)
            return gm->graphs[i];
    }
    return NULL;
}

/*菜单函数*/
void PrintMenu()
{
    printf("\n  -------图（邻接表）演示系统-------  \n");
    printf("**************************************\n");
    printf("  0.退出演示系统\n");
    printf("  1.创建单个图\n");
    printf("  2.销毁当前图\n");
    printf("  3.查找顶点\n");
    printf("  4.顶点赋值\n");
    printf("  5.获得第一邻接点\n");
    printf("  6.获得下一邻接点\n");
    printf("  7.插入顶点\n");
    printf("  8.删除顶点\n");
    printf("  9.插入弧\n");
    printf(" 10.删除弧\n");
    printf(" 11.深度优先搜索遍历\n");
    printf(" 12.广度优先搜索遍历\n");
    printf(" 13.附加功能1：求距离小于k的顶点集合\n");
    printf(" 14.附加功能2：求顶点间最短路径和长度\n");
    printf(" 15.附加功能3：求图的连通分量数\n");
    printf(" 16.附加功能4：实现图的文件形式保存\n");
    printf(" 17.附加功能5：从文件加载创建图\n");
    printf(" 18.附加功能6：多图管理\n");
    printf("**************************************\n");
    printf("请输入你的选择: ");
}
void PrintSubMenu()
{
    printf("\n--- 多图管理子系统 ---\n");
    printf("  1.创建新的图\n");
    printf("  2.显示所有图状态\n");
    printf("  3.删除某个图\n");
    printf("  4.操作其中某个图\n");
    printf("  0.返回主菜单\n");
    printf("请输入你的选择: ");
}
void PrintSubSubMenu(char* listname)
{
    printf("\n-----操作图 \"%s\" -----\n", listname);
    printf("  0.返回子菜单\n");
    printf("  1.销毁当前图\n");
    printf("  2.查找顶点\n");
    printf("  3.顶点赋值\n");
    printf("  4.获得第一邻接点\n");
    printf("  5.获得下一邻接点\n");
    printf("  6.插入顶点\n");
    printf("  7.删除顶点\n");
    printf("  8.插入弧\n");
    printf("  9.删除弧\n");
    printf(" 10.深度优先搜索遍历\n");
    printf(" 11.广度优先搜索遍历\n");
    printf(" 12.附加功能1：求距离小于k的顶点集合\n");
    printf(" 13.附加功能2：求顶点间最短路径和长度\n");
    printf(" 14.附加功能3：求图的连通分量数\n");
    printf(" 15.附加功能4：实现图的文件形式保存\n");
    printf(" 16.附加功能5：从文件加载创建图\n");
    printf("请输入您的选择：\n");
}