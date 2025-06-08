#define _CRT_SECURE_NO_WARNINGS

#include"functions.h"

status CreateGraph(ALGraph* G, VertexType V[], KeyType VR[][2])
/*����V��VR����ͼT������OK�����V��VR����ȷ������ERROR,�������ͬ�Ĺؼ��֣�����ERROR*/
{
    int vexnum = 0;
    int flag = 0;

    for (; vexnum < MAX_VERTEX_NUM + 1; vexnum++) {   //ѭ��ȷ���������vexnum
        if (V[vexnum].key == -1) {
            flag = 1;
            break;
        }
    }
    //if (vexnum <= 0 || (vexnum < MAX_VERTEX_NUM && flag == 0)) return ERROR;
    if (vexnum <= 0 || flag == 0) {
        printf("������������Ҫ��\n");
        return ERROR;
    }

    for (int i = 0; i < vexnum; i++) {  //ѭ�����ؼ����Ƿ��ظ�
        for (int j = i + 1; j < vexnum; j++)
        {
            if (V[i].key == V[j].key)
            {
                printf("�ؼ����ظ���\n");
                return ERROR;
            }
        }
    }

    G->vexnum = vexnum;
    G->arcnum = 0;
    G->kind = UDG; 
    for (int i = 0; i < vexnum; i++) {  //��ʼ���������飺���ƶ�����Ϣ��ͬʱ���ڽ�����ͷ��Ϊ NULL
        G->vertices[i].data = V[i];
        G->vertices[i].firstarc = NULL;
    }

    int k = 0;
    int edgeCount = 0; // ��¼����
    while (1) {
        if (VR[k][0] == -1 && VR[k][1] == -1) break;

        int key_u = VR[k][0];
        int key_v = VR[k][1];
        int idx_u = -1, idx_v = -1; //�ֱ�Ϊkey_u��key_v��ͼ�ж�Ӧ���±�

        /* ���ҹؼ��� key_u �� key_v ��ͼ�ж�Ӧ���±� */
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
            printf("�ߵ��ڵ�ؼ����������\n");
            return ERROR;
        }

        //�� idx_u ������ڽ���������Ƿ��Ѵ���ָ�� idx_v �ı�
        ArcNode* p = G->vertices[idx_u].firstarc; //p��ָ���±�Ϊidx_u�ĵ�ĵ�һ���ڱ�
        int duplicate = 0; //0��ʾ������ָ�� idx_v �ıߣ�1��ʾ����ָ�� idx_v �ı�
        while (p) {
            if (p->adjvex == idx_v) {
                duplicate = 1;
                break;
            }
            p = p->nextarc;
        }
        if (!duplicate) {
            //�����ײ巨�� idx_u ���ڽ���������µı߽��
            ArcNode* newNode = (ArcNode*)malloc(sizeof(ArcNode));
            if (!newNode) exit(OVERFLOW);
            newNode->adjvex = idx_v;
            newNode->nextarc = G->vertices[idx_u].firstarc;     //ע����õ����ײ巨������Ч������
            G->vertices[idx_u].firstarc = newNode;
        }

        //�� idx_v ������ڽ�����ͬ������Ƿ��Ѵ���ָ�� idx_u �ı�
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
            newNode->nextarc = G->vertices[idx_v].firstarc;   //ע����õ����ײ巨������
            G->vertices[idx_v].firstarc = newNode;
            edgeCount++;  //���������δ����ʱ����һ��������
        }
        k++;
    }
    G->arcnum = edgeCount;
    return OK;
}
status DestroyGraph(ALGraph* G)
/*��������ͼG,ɾ��G��ȫ������ͱ�*/
{
    if (G == NULL || G->vertices == NULL) return ERROR;

    ArcNode* p, * temp;
    for (int i = 0; i < G->vexnum; i++) {  //����ÿ�����㣬�ͷ��ڽ����������ж�̬����ı߽��
        p = G->vertices[i].firstarc;
        while (p != NULL) {
            temp = p;
            p = p->nextarc;
            free(temp);
        }
        //����ǰ������ڽ�����ͷ��Ϊ��
        G->vertices[i].firstarc = NULL;
    }
    //���ٺ󣬽��������ͻ�����Ϊ0
    G->vexnum = 0;
    G->arcnum = 0;

    return OK;
}
int LocateVex(ALGraph G, KeyType u)
//����u��ͼG�в��Ҷ��㣬���ҳɹ�����λ�򣬷��򷵻�-1��
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

    // ����¹ؼ����Ƿ��ѱ���һ������ʹ��
    for (int i = 0; i < G->vexnum; i++) {
        if (i == target_idx) continue;  // ����Ŀ�궥������
        if (G->vertices[i].data.key == value.key)
            return ERROR;  // �¹ؼ����Ѵ���
    }

    G->vertices[target_idx].data = value;
    return OK;
}
int FirstAdjVex(ALGraph G, KeyType u)
//u�Ǻ�G�ж���ؼ���������ͬ�ĸ���ֵ�����عؼ���Ϊu�Ķ����һ���ڽӶ���λ����ţ����λ�򣩣����򷵻�-1
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
//v��ӦG��һ������,w��Ӧv���ڽӶ��㣻��������Ƿ���v�ģ������w����һ���ڽӶ����λ�����w�����һ���ڽӶ��㣬��v��w��Ӧ���㲻���ڣ��򷵻�-1��
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
//��ͼG�в����¹ؼ���Ϊv�Ķ��㣨Ҫ��ؼ��־���Ψһ�ԣ�ע���ж϶�������Ƿ����������ɹ�����OK�����򷵻�ERROR��
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
//v�Ǻ�G�ж���ؼ���������ͬ�ĸ���ֵ�������������ͼG��ɾ���ؼ���v��Ӧ�Ķ����Լ���صĻ����ɹ�����OK�����򷵻�ERROR��
{
    if (G == NULL) return ERROR;

    int v_pos = -1; //���ҹؼ���Ϊv�Ķ����ڶ��������е�λ��
    for (int i = 0; i < G->vexnum; i++) {
        if (G->vertices[i].data.key == v) {
            v_pos = i;
            break;
        }
    }
    if (v_pos == -1) return ERROR;

    //ɾ���������������ڽӱ���ָ��ɾ������Ļ������������д洢��λ��
    for (int i = 0; i < G->vexnum; i++) {
        if (i == v_pos) continue;  // ��ɾ�������Լ����ڽӱ����浥������

        ArcNode* p = G->vertices[i].firstarc;
        ArcNode* prev = NULL;
        while (p != NULL) {
            if (p->adjvex == v_pos) {
                // �ҵ�ָ���ɾ������Ļ�����ɾ����
                ArcNode* temp = p;
                if (prev == NULL) {
                    // p Ϊ����ͷ���
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
                // ����û���adjvex����delIndex�����ڶ������齫����1��λ�ã������Ҫ��1
                if (p->adjvex > v_pos) p->adjvex--;
                prev = p;
                p = p->nextarc;
            }
        }
    }

    //ɾ����ɾ�����������ڽӱ��е����л�
    //����������ͼ��һ���߻ᱻ��������������¼����ǰ��ɾ���ߵ�ʱ���Ѿ�G.arcnum--�ˣ��������ﲻ���ټ���
    ArcNode* p_del = G->vertices[v_pos].firstarc;
    while (p_del != NULL) {
        ArcNode* temp = p_del;
        p_del = p_del->nextarc;
        free(temp);
    }

    // 4. ����ɾ�������ڶ���������֮��Ķ���������ǰ�ƶ�
    for (int i = v_pos; i < G->vexnum - 1; i++) {
        G->vertices[i] = G->vertices[i + 1];
    }
    G->vexnum--;

    return OK;
}
status InsertArc(ALGraph* G, KeyType v, KeyType w)
//v��w�Ǻ�G�ж���ؼ���������ͬ�ĸ���ֵ�������������ͼG�����ӻ�<v,w>���ɹ�����OK�����򷵻�ERROR��
{
    if (G == NULL) return ERROR;
    int v_pos = -1, w_pos = -1;
    // ���Ҷ��� v �� w ��ͼ�е��±�
    for (int i = 0; i < G->vexnum; i++) {
        if (G->vertices[i].data.key == v) {
            v_pos = i;
        }
        if (G->vertices[i].data.key == w) {
            w_pos = i;
        }
    }
    if (v_pos == -1 || w_pos == -1) return ERROR;

    // ����Ƿ��Ѿ�����<v, w>�����ߣ������ظ�����
    ArcNode* p = G->vertices[v_pos].firstarc;
    while (p != NULL) {
        if (p->adjvex == w_pos) return ERROR;
        p = p->nextarc;
    }

    // ʹ��ͷ�巨�� v ���ڽӱ��в���һ�ڵ�����<v, w>
    ArcNode* newarc_vw = (ArcNode*)malloc(sizeof(ArcNode));
    if (newarc_vw == NULL) return OVERFLOW;
    newarc_vw->adjvex = w_pos;
    newarc_vw->nextarc = G->vertices[v_pos].firstarc;
    G->vertices[v_pos].firstarc = newarc_vw;

    // ͬ���� w ���ڽӱ��в���һ�ڵ�����<w, v>
    ArcNode* newarc_wv = (ArcNode*)malloc(sizeof(ArcNode));
    if (newarc_wv == NULL) {
        // �ͷ��Ѿ������ v ���½ڵ㣬��ֹ�ڴ�й©
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
//v��w�Ǻ�G�ж���ؼ���������ͬ�ĸ���ֵ�������������ͼG��ɾ����<v,w>���ɹ�����OK�����򷵻�ERROR��
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
            if (prev1 == NULL) G->vertices[v_pos].firstarc = p1->nextarc; //ɾ��ͷ��㣬Ҫ��������
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
            if (prev2 == NULL) G->vertices[w_pos].firstarc = p2->nextarc; //ɾ��ͷ��㣬Ҫ��������
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
/*���������������*/
void visit(VertexType v){
    printf(" %d %s ", v.key, v.others);
}
void DFS(ALGraph* G, int i, int visited[], void (*visit)(VertexType)) 
// �����ݹ麯�����Ӷ��� i �������������������
{
    // ��ǵ�ǰ�����ѷ��ʣ�������visit�������ʸö��������
    visited[i] = TRUE;
    visit(G->vertices[i].data);

    // �������� i ���ڽӱ���������δ���ʵ��ٽӶ������DFS
    ArcNode* p = G->vertices[i].firstarc;
    while (p != NULL) {
        if (!visited[p->adjvex])
            DFS(G, p->adjvex, visited, visit);
        p = p->nextarc;
    }
}
status DFSTraverse(ALGraph* G, void (*visit)(VertexType)) 
// ����������ͼ G �������������������
{
    int visited[MAX_VERTEX_NUM];

    // ��ʼ�����ж���Ϊδ����
    for (int i = 0; i < G->vexnum; i++) {
        visited[i] = FALSE;
    }

    // ���ζ�ÿ��δ�����ʵĶ������ DFS���������ͨͼ��
    for (int i = 0; i < G->vexnum; i++) {
        if (!visited[i])
            DFS(G, i, visited, visit);
    }
    return OK;
}
/*���������������*/
status BFSTraverse(ALGraph* G, void (*visit)(VertexType)) 
{
    int visited[MAX_VERTEX_NUM];
    for (int i = 0; i < G->vexnum; i++) {
        visited[i] = FALSE;
    }

    int queue[MAX_VERTEX_NUM];
    int front = 0, rear = 0; // ��ͷ����βָ��

    for (int i = 0; i < G->vexnum; i++) {
        if (!visited[i]) {
            // ��δ���ʵĶ�����ӣ������Ϊ�ѷ���
            visited[i] = TRUE;
            visit(G->vertices[i].data);
            queue[rear++] = i;

            // �����в���ʱ����������ͷ���ӣ������������ڽӶ���
            while (front < rear) {
                int cur = queue[front++];
                // ������ǰ���� cur �������ڽӵ�
                ArcNode* p = G->vertices[cur].firstarc;
                while (p != NULL) {
                    if (!visited[p->adjvex]) {
                        // ���ʲ����
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

//����С��k�Ķ��㼯�ϣ�����BFS��¼�Ӷ���v���������������̾��룬ֻ�о���С��k�Ķ��㱻������
int* VerticesSetLessThanK(ALGraph* G, int v, int k, int* pSize) {
    if (G == NULL || v < 0 || v >= G->vexnum || pSize == NULL)
        return NULL;

    //��̬�������鱣������㵽v����̾���
    int* dist = (int*)malloc(G->vexnum * sizeof(int));
    if (dist == NULL) return NULL;
    for (int i = 0; i < G->vexnum; i++)
        dist[i] = INF;
    dist[v] = 0;

    //ʹ�ö���ʵ��BFS
    int queue[MAX_VERTEX_NUM];
    int front = 0, rear = 0;
    queue[rear++] = v;

    while (front < rear) {
        int cur = queue[front++];
        //����ǰ�������ﵽk-1ʱ������չ����������ܴﵽk�������ƽ�����
        if (dist[cur] >= k - 1)
            continue;

        ArcNode* p = G->vertices[cur].firstarc;
        while (p) {
            int adj = p->adjvex;
            if (dist[adj] == INF) {  //����δ��ǹ�
                dist[adj] = dist[cur] + 1;
                if (dist[adj] < k)
                    queue[rear++] = adj;
            }
            p = p->nextarc;
        }
    }

    //ͳ�����о��� < k �Ķ�����
    int count = 0;
    for (int i = 0; i < G->vexnum; i++) {
        if (dist[i] < k)
            count++;
    }

    //�������鱣�������洢��������������±�
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
//��������·���ͳ���
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
    return -1;  //�޷�����w
}
//ͼ����ͨ������
void dummyVisit(VertexType v) {} //��visit���� 
int ConnectedComponentsNums(ALGraph* G)
{
    if (G == NULL)
        return -1;
    int visited[MAX_VERTEX_NUM] = { 0 };
    int count = 0;
    for (int i = 0; i < G->vexnum; i++) {
        if (!visited[i]) {
            /* ����ͨ���������ж������ DFS��ʹ�� dummyVisit ����ӡ�������� */
            DFS(G, i, visited, dummyVisit);
            count++;
        }
    }
    return count;
}
/*������ͼ������д���ļ���*/
status SaveGraph(ALGraph G, char FileName[]) 
{
    FILE* fp = fopen(FileName, "w");
    if (fp == NULL)
        return ERROR;

    // ��ÿ������дһ�У���д�������ݣ�Ȼ������д�����ڽӱ��и������� adjvex ֵ
    for (int i = 0; i < G.vexnum; i++) {
        // ���������ؼ��ֺ���������
        fprintf(fp, "%d %s", G.vertices[i].data.key, G.vertices[i].data.others);

        // ���ö����ڽ������еĽ�� adjvex ֵ�ȴ�����ʱ������
        int tempArr[MAX_VERTEX_NUM];
        int count = 0;
        ArcNode* p = G.vertices[i].firstarc;
        while (p != NULL) {
            tempArr[count++] = p->adjvex;
            p = p->nextarc;
        }

        // ���ڲ����ײ巨�������е�˳��������ģ�Ϊ��֤���ʱ��Ԥ��һ�£����������ʱ����
        for (int j = count - 1; j >= 0; j--) {
            fprintf(fp, " %d", tempArr[j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
    return OK;
}
/*�����ļ��еĽ�����ݴ�������ͼ���ڽӱ�*/
status LoadGraph(ALGraph* G, char FileName[]) {
    FILE* fp = fopen(FileName, "r");
    if (fp == NULL)
        return ERROR;

    char line[256];
    int vertexCount = 0;
    int totalAdjCount = 0;
    // ���ж�ȡ�ļ�����������ȷ���������
    while (fgets(line, sizeof(line), fp) != NULL) {
        if (strlen(line) <= 1) continue; // ���������Ϊ�գ�������

        char* token = strtok(line, " \n");
        if (token == NULL) continue;
        int key = atoi(token);// ��һ����ǣ�����ؼ���

        token = strtok(NULL, " \n");
        if (token == NULL) continue;
        char others[20];
        strcpy(others, token);

        // ���������ݴ��붥������
        G->vertices[vertexCount].data.key = key;
        strcpy(G->vertices[vertexCount].data.others, others);
        G->vertices[vertexCount].firstarc = NULL;

        // �������ÿ��Ϊ�ڽӽ����±꣨��������ȡ��
        token = strtok(NULL, " \n");
        while (token != NULL) {
            int adjIndex = atoi(token);
            // �����ײ巨��������
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
    G->arcnum = totalAdjCount / 2; // ������ͼ��ÿ���ߴ洢����
    G->kind = UDG;
    fclose(fp);
    return OK;
}

/*���ͼ����*/
void InitGraphManager(GraphManager* gm) 
{
    if (gm == NULL) return;
    gm->count = 0;
    // ��ʼ�������ַ���Ϊ��
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
    gm->names[gm->count][NAME_LEN - 1] = '\0';  // ȷ���ַ�����ֹ
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
        printf("δ�ҵ�ͼ��%s\n", name);
        return ERROR;
    }
    if (DestroyGraph(gm->graphs[index]) != OK) {
        return ERROR;
    }
    free(gm->graphs[index]);  // �ͷ�ͼ�ṹ���ڴ�
    // ������ͼ������ǰ�Ƹ���ɾ����ͼ
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
    printf("��ǰ�����ͼ������%d\n", gm->count);
    for (int i = 0; i < gm->count; i++) {
        printf("��ţ�%d, ���ƣ�%s\n", i + 1, gm->names[i]);
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

/*�˵�����*/
void PrintMenu()
{
    printf("\n  -------ͼ���ڽӱ���ʾϵͳ-------  \n");
    printf("**************************************\n");
    printf("  0.�˳���ʾϵͳ\n");
    printf("  1.��������ͼ\n");
    printf("  2.���ٵ�ǰͼ\n");
    printf("  3.���Ҷ���\n");
    printf("  4.���㸳ֵ\n");
    printf("  5.��õ�һ�ڽӵ�\n");
    printf("  6.�����һ�ڽӵ�\n");
    printf("  7.���붥��\n");
    printf("  8.ɾ������\n");
    printf("  9.���뻡\n");
    printf(" 10.ɾ����\n");
    printf(" 11.���������������\n");
    printf(" 12.���������������\n");
    printf(" 13.���ӹ���1�������С��k�Ķ��㼯��\n");
    printf(" 14.���ӹ���2���󶥵�����·���ͳ���\n");
    printf(" 15.���ӹ���3����ͼ����ͨ������\n");
    printf(" 16.���ӹ���4��ʵ��ͼ���ļ���ʽ����\n");
    printf(" 17.���ӹ���5�����ļ����ش���ͼ\n");
    printf(" 18.���ӹ���6����ͼ����\n");
    printf("**************************************\n");
    printf("���������ѡ��: ");
}
void PrintSubMenu()
{
    printf("\n--- ��ͼ������ϵͳ ---\n");
    printf("  1.�����µ�ͼ\n");
    printf("  2.��ʾ����ͼ״̬\n");
    printf("  3.ɾ��ĳ��ͼ\n");
    printf("  4.��������ĳ��ͼ\n");
    printf("  0.�������˵�\n");
    printf("���������ѡ��: ");
}
void PrintSubSubMenu(char* listname)
{
    printf("\n-----����ͼ \"%s\" -----\n", listname);
    printf("  0.�����Ӳ˵�\n");
    printf("  1.���ٵ�ǰͼ\n");
    printf("  2.���Ҷ���\n");
    printf("  3.���㸳ֵ\n");
    printf("  4.��õ�һ�ڽӵ�\n");
    printf("  5.�����һ�ڽӵ�\n");
    printf("  6.���붥��\n");
    printf("  7.ɾ������\n");
    printf("  8.���뻡\n");
    printf("  9.ɾ����\n");
    printf(" 10.���������������\n");
    printf(" 11.���������������\n");
    printf(" 12.���ӹ���1�������С��k�Ķ��㼯��\n");
    printf(" 13.���ӹ���2���󶥵�����·���ͳ���\n");
    printf(" 14.���ӹ���3����ͼ����ͨ������\n");
    printf(" 15.���ӹ���4��ʵ��ͼ���ļ���ʽ����\n");
    printf(" 16.���ӹ���5�����ļ����ش���ͼ\n");
    printf("����������ѡ��\n");
}