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
            printf("�˳�ϵͳ��\n");
            exit(0);
            break;
        case 1:
        {
            // ��������ͼ
            if (currentGraph != NULL)
            {
                printf("��ǰ����ͼ,�����ٴ���ͼ��!\n");
                break;
            }
            int n, m;
            printf("�����붥����� (<= %d): ", MAX_VERTEX_NUM);
            scanf("%d", &n);
            if (n <= 0 || n > MAX_VERTEX_NUM) {
                printf("��������Ƿ���\n");
                break;
            }
            VertexType V[MAX_VERTEX_NUM + 1];
            for (int i = 0; i < n; i++) {
                printf("�������%d������Ĺؼ��֣���������������Ϣ(�ַ���): ", i + 1);
                scanf("%d %s", &V[i].key, V[i].others);
            }
            // �����ڱ�����ʶ�����������
            V[n].key = -1;

            printf("���������: ");
            scanf("%d", &m);
            KeyType VR[MAX_VERTEX_NUM + 1][2];
            for (int i = 0; i < m; i++) {
                printf("�������%d���������ڵ�Ĺؼ���: ", i + 1);
                scanf("%d %d", &VR[i][0], &VR[i][1]);
            }
            VR[m][0] = -1; VR[m][1] = -1;

            currentGraph = (ALGraph*)malloc(sizeof(ALGraph));
            if (currentGraph == NULL) {
                printf("�ڴ����ʧ�ܣ�\n");
                break;
            }
            if (CreateGraph(currentGraph, V, VR) == OK)
                printf("ͼ�����ɹ���\n");
            else {
                printf("ͼ����ʧ�ܣ�\n");
                free(currentGraph);
                currentGraph = NULL;
            }
        }
        break;
        case 2:
        {
            // ���ٵ�ǰ��ͼ
            if (currentGraph == NULL) {
                printf("��ǰû��ͼ��\n");
                break;
            }
            if (DestroyGraph(currentGraph) == OK) {
                free(currentGraph);
                currentGraph = NULL;
                printf("ͼ���ٳɹ���\n");
            }
            else {
                printf("ͼ����ʧ�ܣ�\n");
            }
        }
        break;
        case 3:
        {
            // ���Ҷ���
            if (currentGraph == NULL) {
                printf("��ǰû��ͼ��\n");
                break;
            }
            int key;
            printf("����������ҵĶ���ؼ���: ");
            scanf("%d", &key);
            int pos = LocateVex(*currentGraph, key);
            if (pos != -1)
                printf("�ҵ��ؼ���Ϊ%d�Ķ��㣬���±�Ϊ%d\n", key, pos);
            else
                printf("δ�ҵ��ö��㣡\n");
        }
        break;
        case 4:
        {
            // ���㸳ֵ
            if (currentGraph == NULL) {
                printf("��ǰû��ͼ��\n");
                break;
            }
            int key;
            VertexType value;
            printf("������Ҫ��ֵ�Ķ���ؼ��֣����������µ�������Ϣ���ַ�����: ");
            scanf("%d %s", &key, value.others);
            value.key = key;
            if (PutVex(currentGraph, key, value) == OK)
                printf("���㸳ֵ�ɹ���\n");
            else
                printf("���㸳ֵʧ�ܣ�\n");
        }
        break;
        case 5:
        {
            // ��õ�һ�ڽӵ�
            if (currentGraph == NULL) {
                printf("��ǰû��ͼ��\n");
                break;
            }
            int key;
            printf("��������󶥵�Ĺؼ��֣�");
            scanf("%d", &key);
            int first = FirstAdjVex(*currentGraph, key);
            if (first != -1) {
                printf("����%d�ĵ�һ�ڽӵ��±�Ϊ%d��", key, first);
                printf("������ϢΪ��%d %s\n", currentGraph->vertices[first].data.key, currentGraph->vertices[first].data.others);
            }
            else
                printf("δ�ҵ�����%d���ڽӵ㣡\n", key);
        }
        break;
        case 6:
        {
            // �����һ�ڽӵ�
            if (currentGraph == NULL) {
                printf("��ǰû��ͼ��\n");
                break;
            }
            int v, w;
            printf("�����붥��v����֪�ڽӶ���w�Ĺؼ���: ");
            scanf("%d %d", &v, &w);
            int next = NextAdjVex(*currentGraph, v, w);
            if (next != -1) {
                printf("����%d�ڶ���%d֮����ڽӵ��±�Ϊ%d��", v, w, next);
                printf("������ϢΪ��%d %s\n", currentGraph->vertices[next].data.key, currentGraph->vertices[next].data.others);
            }
            else
                printf("δ�ҵ������������ڽӵ㣡\n");
        }
        break;
        case 7:
        {
            // ���붥��
            if (currentGraph == NULL) {
                printf("��ǰû��ͼ��\n");
                break;
            }
            VertexType newV;
            printf("������Ҫ���붥��Ĺؼ��֣���������������Ϣ���ַ�����:");
            scanf("%d %s", &newV.key, newV.others);
            if (InsertVex(currentGraph, newV) == OK)
                printf("�������ɹ���\n");
            else
                printf("�������ʧ�ܣ�\n");
        }
        break;
        case 8:
        {
            // ɾ������
            if (currentGraph == NULL) {
                printf("��ǰû��ͼ��\n");
                break;
            }
            int key;
            printf("������Ҫɾ���Ķ���Ĺؼ���: ");
            scanf("%d", &key);
            if (DeleteVex(currentGraph, key) == OK)
                printf("����ɾ���ɹ���\n");
            else
                printf("����ɾ��ʧ�ܣ�\n");
        }
        break;
        case 9:
        {
            // ���뻡
            if (currentGraph == NULL) {
                printf("��ǰû��ͼ��\n");
                break;
            }
            int v, w;
            printf("������Ҫ���뻡�������ڵ�Ĺؼ���: ");
            scanf("%d %d", &v, &w);
            if (InsertArc(currentGraph, v, w) == OK)
                printf("���뻡�ɹ���\n");
            else
                printf("���뻡ʧ�ܣ�\n");
        }
        break;
        case 10:
        {
            // ɾ����
            if (currentGraph == NULL) {
                printf("��ǰû��ͼ��\n");
                break;
            }
            int v, w;
            printf("������Ҫɾ�����������ڵ�Ĺؼ���: ");
            scanf("%d %d", &v, &w);
            if (DeleteArc(currentGraph, v, w) == OK)
                printf("ɾ�����ɹ���\n");
            else
                printf("ɾ����ʧ�ܣ�\n");
        }
        break;
        case 11:
        {
            // ���������������
            if (currentGraph == NULL) {
                printf("��ǰû��ͼ��\n");
                break;
            }
            printf("������������������:\n");
            if (DFSTraverse(currentGraph, visit) == OK)
                printf("\n�����������������ɣ�\n");
            else
                printf("\n���������������ʧ�ܣ�\n");
        }
        break;
        case 12:
        {
            // ���������������
            if (currentGraph == NULL) {
                printf("��ǰû��ͼ��\n");
                break;
            }
            printf("������������������:\n");
            if (BFSTraverse(currentGraph, visit) == OK)
                printf("\n���������������������ɣ�\n");
            else
                printf("\n�������������������ʧ�ܣ�\n");
        }
        break;
        case 13:
        {
            // ���ӹ���1�������С��k�Ķ��㼯��
            if (currentGraph == NULL) {
                printf("��ǰû��ͼ��\n");
                break;
            }
            int v, k, pSize;
            printf("��������ʼ�����±�v�;���k: ");
            scanf("%d %d", &v, &k);
            int* set = VerticesSetLessThanK(currentGraph, v, k, &pSize);
            if (set != NULL) {
                printf("����С��%d�Ķ����±꼯��Ϊ��", k);
                for (int i = 0; i < pSize; i++) {
                    printf("%d ", set[i]);
                }
                printf("\n");
                free(set);
            }
            else {
                printf("����ʧ�ܻ������������Ķ��㣡\n");
            }
        }
        break;
        case 14:
        {
            // ���ӹ���2���󶥵�����·���ͳ���
            if (currentGraph == NULL) {
                printf("��ǰû��ͼ��\n");
                break;
            }
            int v, w;
            printf("��������ʼ�����±����ֹ�����±�: ");
            scanf("%d %d", &v, &w);
            int length = ShortestPathLength(currentGraph, v, w);
            if (length != -1)
                printf("����%d������%d�����·������Ϊ%d\n", v, w, length);
            else
                printf("��������֮����·����\n");
        }
        break;
        case 15:
        {
            // ���ӹ���3����ͼ����ͨ������
            if (currentGraph == NULL) {
                printf("��ǰû��ͼ��\n");
                break;
            }
            int comps = ConnectedComponentsNums(currentGraph);
            printf("��ͼ����ͨ������Ϊ %d\n", comps);
        }
        break;
        case 16:
        {
            // ���ӹ���4��ͼ���ļ���ʽ����
            if (currentGraph == NULL) {
                printf("��ǰû��ͼ��\n");
                break;
            }
            char fileName[100];
            printf("�����뱣��ͼ���ļ���: ");
            scanf("%s", fileName);
            if (SaveGraph(*currentGraph, fileName) == OK)
                printf("ͼ����ɹ���\n");
            else
                printf("ͼ����ʧ�ܣ�\n");
        }
        break;
        case 17:
        {
            // ���ӹ���5�����ļ����ش���ͼ
            if (currentGraph == NULL) {
                printf("��ǰû��ͼ��\n");
                break;
            }
            char fileName[100];
            printf("���������ͼ���ļ���: ");
            scanf("%s", fileName);
            if (LoadGraph(currentGraph, fileName) == OK)
                printf("ͼ���سɹ���\n");
            else
                printf("ͼ����ʧ�ܣ�\n");
        }
        break;
        case 18:
        {
            // �����ͼ������ϵͳ
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
                    // �����µ�ͼ����ͼ����
                    char name[NAME_LEN];
                    int createOption;
                    printf("��������ͼ����: ");
                    scanf("%s", name);
                    printf("��ѡ�񴴽���ʽ��1.����ʼ��  2.��ʼ��+��������: ");
                    scanf("%d", &createOption);
                    ALGraph* newGraph = (ALGraph*)malloc(sizeof(ALGraph));
                    if (newGraph == NULL) {
                        printf("�ڴ����ʧ�ܣ�\n");
                        break;
                    }
                    if (createOption == 1) {
                        // ����ʼ���������ö�����Ϊ0������Ϊ0
                        newGraph->vexnum = 0;
                        newGraph->arcnum = 0;
                        newGraph->kind = UDG;
                        printf("ͼ�ѳ�ʼ����\n");
                    }
                    else if (createOption == 2) {
                        // ��ʼ������������
                        int n, m;
                        printf("�����붥����� (<= %d): ", MAX_VERTEX_NUM);
                        scanf("%d", &n);
                        if (n <= 0 || n > MAX_VERTEX_NUM) {
                            printf("��������Ƿ���\n");
                            free(newGraph);
                            break;
                        }
                        VertexType V[MAX_VERTEX_NUM + 1]; //Ϊ�����ڱ������ռ�
                        for (int i = 0; i < n; i++) {
                            printf("�������%d������Ĺؼ��֣���������������Ϣ(�ַ���): ", i + 1);
                            scanf("%d %s", &V[i].key, V[i].others);
                        }
                        // �����ڱ�����ʶ�����������
                        V[n].key = -1;

                        printf("���������: ");
                        scanf("%d", &m);
                        KeyType VR[MAX_VERTEX_NUM + 1][2];
                        for (int i = 0; i < m; i++) {
                            printf("�������%d���ߵ���������Ĺؼ���: ", i + 1);
                            scanf("%d %d", &VR[i][0], &VR[i][1]);
                        }
                        VR[m][0] = -1; VR[m][1] = -1;

                        if (CreateGraph(newGraph, V, VR) == OK)
                            printf("ͼ�����ɹ���\n");
                        else {
                            printf("ͼ����ʧ�ܣ�\n");
                            free(newGraph);
                            break;
                        }
                    }
                    else {
                        printf("��Ч��ѡ�\n");
                        free(newGraph);
                        break;
                    }
                    if (AddGraph(&gm, newGraph, name) == OK)
                        printf("ͼ '%s' ����ӵ���ͼ�������У�\n", name);
                    else {
                        printf("���ʧ�ܣ�\n");
                        free(newGraph);
                    }
                }
                break;
                case 2:
                {
                    // ��ʾ����ͼ״̬
                    DisplayGraphManager(&gm);
                }
                break;
                case 3:
                {
                    // ɾ��ͼ
                    char delName[NAME_LEN];
                    printf("������Ҫɾ����ͼ����: ");
                    scanf("%s", delName);
                    if (DeleteGraph(&gm, delName) == OK)
                        printf("ͼ '%s' ɾ���ɹ���\n", delName);
                    else
                        printf("ɾ��ʧ�ܣ�\n");
                }
                break;
                case 4:
                {
                    char opName[NAME_LEN];
                    printf("������Ҫ������ͼ����: ");
                    scanf("%s", opName);
                    ALGraph* opGraph = GetGraphByName(&gm, opName);
                    if (opGraph == NULL) {
                        printf("δ�ҵ�ͼ '%s'��\n", opName);
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
                            // ���ض�ͼ������ϵͳ
                            printf("���ض�ͼ������ϵͳ��\n");
                            break;
                        case 1:
                            // ���ٵ�ǰͼ
                            if (DeleteGraph(&gm, opName) == OK)
                                printf("ͼ '%s' �����ٲ��ӹ���ϵͳ��ɾ����\n", opName);
                            else
                                printf("ͼ '%s' ����ʧ�ܣ�\n", opName);
                            // �˳����Ӳ˵�����Ϊ������ͼ�Ѳ�����
                            subSubChoice = 0;
                            break;
                        case 2:
                        {
                            int key;
                            printf("����������ҵĶ���ؼ���: ");
                            scanf("%d", &key);
                            int pos = LocateVex(*opGraph, key);
                            if (pos != -1)
                                printf("�ҵ��ؼ���Ϊ%d�Ķ��㣬�±�Ϊ%d\n", key, pos);
                            else
                                printf("δ�ҵ��ö��㣡\n");
                        }
                        break;
                        case 3: {
                            int oldKey, newKey;
                            VertexType value;
                            printf("������ԭ����ؼ���: ");
                            scanf("%d", &oldKey);
                            printf("�������µĶ���ؼ��֣����������µ�������Ϣ���ַ�������");
                            scanf("%d %s", &newKey, value.others);
                            value.key = newKey;
                            if (PutVex(opGraph, oldKey, value) == OK)
                                printf("���㸳ֵ�ɹ���\n");
                            else
                                printf("���㸳ֵʧ�ܣ�\n");
                            break;
                        }
                        case 4:
                        {
                            int key;
                            printf("��������󶥵�Ĺؼ���: ");
                            scanf("%d", &key);
                            int first = FirstAdjVex(*opGraph, key);
                            if (first != -1) {
                                   printf("����%d�ĵ�һ�ڽӵ��±�Ϊ%d��", key, first);
                                   printf("������ϢΪ��%d %s\n", opGraph->vertices[first].data.key, opGraph->vertices[first].data.others);
                            }
                            else
                                printf("δ�ҵ�����%d�ĵ�һ�ڽӵ㣡\n", key);
                        }
                        break;
                        case 5:
                        {
                            int v, w;
                            printf("�����붥��v����֪�ڽӶ���w�Ĺؼ���: ");
                            scanf("%d %d", &v, &w);
                            int next = NextAdjVex(*opGraph, v, w);
                            if (next != -1) {
                                printf("����%d�ڶ���%d֮����ڽӵ��±�Ϊ%d��", v, w, next);
                                printf("������ϢΪ��%d %s\n", opGraph->vertices[next].data.key, opGraph->vertices[next].data.others);
                            }
                            else
                                printf("δ�ҵ������������ڽӵ㣡\n");
                        }
                        break;
                        case 6:
                        {
                            VertexType newV;
                            printf("�������¶���Ĺؼ��֣���������������Ϣ���ַ�����: ");
                            scanf("%d %s", &newV.key, newV.others);
                            if (InsertVex(opGraph, newV) == OK)
                                printf("�������ɹ���\n");
                            else
                                printf("�������ʧ�ܣ�\n");
                        }
                        break;
                        case 7:
                        {
                            int key;
                            printf("������Ҫɾ���Ķ���Ĺؼ���: ");
                            scanf("%d", &key);
                            if (DeleteVex(opGraph, key) == OK)
                                printf("����ɾ���ɹ���\n");
                            else
                                printf("����ɾ��ʧ�ܣ�\n");
                        }
                        break;
                        case 8:
                        {
                            int v, w;
                            printf("������Ҫ���뻡�������ڵ�Ĺؼ���: ");
                            scanf("%d %d", &v, &w);
                            if (InsertArc(opGraph, v, w) == OK)
                                printf("���뻡�ɹ���\n");
                            else
                                printf("���뻡ʧ�ܣ�\n");
                        }
                        break;
                        case 9:
                        {
                            int v, w;
                            printf("������Ҫɾ�����������ڵ�ؼ���: ");
                            scanf("%d %d", &v, &w);
                            if (DeleteArc(opGraph, v, w) == OK)
                                printf("ɾ�����ɹ���\n");
                            else
                                printf("ɾ����ʧ�ܣ�\n");
                        }
                        break;
                        case 10:
                        {
                            printf("������������������:\n");
                            if (DFSTraverse(opGraph, visit) == OK)
                                printf("\n�����������������ɣ�\n");
                            else
                                printf("\n���������������ʧ�ܣ�\n");
                        }
                        break;
                        case 11:
                        {
                            printf("������������������:\n");
                            if (BFSTraverse(opGraph, visit) == OK)
                                printf("\n�����������������ɣ�\n");
                            else
                                printf("\n���������������ʧ�ܣ�\n");
                        }
                        break;
                        case 12:
                        {
                            int v, k, pSize;
                            printf("��������ʼ�����±�v�;���k: ");
                            scanf("%d %d", &v, &k);
                            int* set = VerticesSetLessThanK(opGraph, v, k, &pSize);
                            if (set != NULL) {
                                printf("����С��%d�Ķ����±꼯��Ϊ��", k);
                                for (int i = 0; i < pSize; i++) {
                                    printf("%d ", set[i]);
                                }
                                printf("\n");
                                free(set);
                            }
                            else {
                                printf("����ʧ�ܻ��޶�������������\n");
                            }
                        }
                        break;
                        case 13:
                        {
                            int v, w;
                            printf("��������ʼ�����±����ֹ�����±�: ");
                            scanf("%d %d", &v, &w);
                            int length = ShortestPathLength(opGraph, v, w);
                            if (length != -1)
                                printf("����%d������%d�����·������Ϊ%d\n", v, w, length);
                            else
                                printf("��������֮����·����\n");
                        }
                        break;
                        case 14:
                        {
                            int comps = ConnectedComponentsNums(opGraph);
                            printf("��ͼ����ͨ������Ϊ%d\n", comps);
                        }
                        break;
                        case 15:
                        {
                            char fileName[100];
                            printf("�����뱣��ͼ���ļ���: ");
                            scanf("%s", fileName);
                            if (SaveGraph(*opGraph, fileName) == OK)
                                printf("ͼ����ɹ���\n");
                            else
                                printf("ͼ����ʧ�ܣ�\n");
                        }
                        break;
                        case 16:
                        {
                            char fileName[100];
                            printf("���������ͼ���ļ���: ");
                            scanf("%s", fileName);
                            if (LoadGraph(opGraph, fileName) == OK)
                                printf("ͼ���ݼ��سɹ���\n");
                            else
                                printf("ͼ���ݼ���ʧ�ܣ�\n");
                        }
                        break;
                        default:
                            printf("��������ȷ��ѡ�\n");
                        } // end switch subSubChoice

                        if (subSubChoice == 0)
                            break;
                    } // end while sub-sub�˵�
                    break;
                }
                default:
                    printf("��������ȷ��ѡ�\n");
                }
            } 
        }
        break;
        default:
            printf("��������ȷ��ѡ�\n");
        } 
    } 
    return 0;
}