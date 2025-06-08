#define _CRT_SECURE_NO_WARNINGS

#include"functions.h"

int main()
{
    system("color F0");
    int choice = 0;
    BiTree currentTree = NULL;      // ��ǰʹ�õĵ��ö�����
    BiTreeManager manager;          // �������������
    InitBiTreeManager(&manager);    // ��ʼ���������������

    while (1)
    {
        PrintMenu();
        scanf("%d", &choice);
        switch (choice)
        {
        case 0:
            printf("�˳���ʾϵͳ��\n");
            exit(0);
            break;
        case 1:
        {
            int choice_;
            printf("��ѡ�񴴽��������ķ�ʽ��\n");
            printf(" 1. ����������ǵ������������\n");
            printf(" 2. ǰ��������������\n");
            printf(" 3. ����������������\n");
            printf("����������ѡ��1/2/3����");
            scanf("%d", &choice_);

            if (choice_ == 1)
            {
                TElemType def[MAX_TREE_SIZE];
                int count = 0;
                printf("���������������ǵ�����������е����ݣ���ʽ��key others����\n");
                printf("������keyΪ-1ʱ��ʾ����������0��ʾ�ս�㡣\n");
                while (1)
                {
                    printf("��������%d������: ", count + 1);
                    scanf("%d %s", &def[count].key, def[count].others);
                    if (def[count].key == -1) // ��ֹ���
                        break;
                    count++;
                    if (count >= MAX_TREE_SIZE)
                    {
                        printf("�Ѵ�������������ֹͣ���룡\n");
                        break;
                    }
                }
                if (CreateBiTree(&currentTree, def, 1) == OK)
                    printf("��������ʼ���ɹ���\n");
                else
                    printf("��������ʼ��ʧ�ܣ�\n");
            }
            else if (choice_ == 2)
            {
                int n;
                printf("������ǿս������ n��");
                scanf("%d", &n);
                TElemType *def=(TElemType*)malloc((1+2*n)*sizeof(TElemType)); // �ܳ���Ϊ1+2*n
                def[0].key = n; // ����������others�ֶο��Ժ��Ի���Ϊ��
                printf("������ǰ��������У�%d ����㣩��\n", n);
                for (int i = 0; i < n; i++)
                {
                    printf("ǰ�����е� %d �����(key others): ", i + 1);
                    scanf("%d %s", &def[1 + i].key, def[1 + i].others);
                }
                printf("����������������У�%d ����㣩��\n", n);
                for (int i = 0; i < n; i++)
                {
                    printf("�������е� %d �����(key others): ", i + 1);
                    scanf("%d %s", &def[1 + n + i].key, def[1 + n + i].others);
                }
                if (CreateBiTree(&currentTree, def, 2) == OK)
                    printf("��������ʼ���ɹ���\n");
                else
                    printf("��������ʼ��ʧ�ܣ�\n");
                free(def);
            }
            else if (choice_ == 3)
            {
                int n;
                printf("������ǿս������ n��");
                scanf("%d", &n);
                TElemType* def = (TElemType*)malloc((1 + 2 * n) * sizeof(TElemType)); // �ܳ���Ϊ1+2*n
                def[0].key = n;
                printf("���������������У�%d ����㣩��\n", n);
                for (int i = 0; i < n; i++)
                {
                    printf("�������е� %d �����(key others): ", i + 1);
                    scanf("%d %s", &def[1 + i].key, def[1 + i].others);
                }
                printf("����������������У�%d ����㣩��\n", n);
                for (int i = 0; i < n; i++)
                {
                    printf("�������е� %d �����(key others): ", i + 1);
                    scanf("%d %s", &def[1 + n + i].key, def[1 + n + i].others);
                }
                if (CreateBiTree(&currentTree, def, 3) == OK)
                    printf("��������ʼ���ɹ���\n");
                else
                    printf("��������ʼ��ʧ�ܣ�\n");
                free(def);
            }
            else
            {
                printf("������ʽ�������\n");
            }
        }
        break;
        case 2:
            // ���ٵ�ǰ������
            if (DestroyBiTree(&currentTree) == OK)
                printf("���������ٳɹ���\n");
            else
                printf("����������ʧ�ܣ�\n");
            break;
        case 3:
            // ��յ�ǰ������
            if (ClearBiTree(&currentTree) == OK)
                printf("����������ա�\n");
            else
                printf("��ն�����ʧ�ܣ�\n");
            break;
        case 4:
            // �жϵ�ǰ�������Ƿ�Ϊ��
            if (BiTreeEmpty(currentTree))
                printf("��ǰ������Ϊ�ա�\n");
            else
                printf("��ǰ��������Ϊ�ա�\n");
            break;
        case 5:
            // ��ȡ��ǰ���������
            printf("��ǰ���������Ϊ��%d\n", BiTreeDepth(currentTree));
            break;
        case 6:
        {
            // ���ҹؼ���Ϊ e �Ľ��
            KeyType key;
            printf("������Ҫ���ҵĹؼ���: ");
            scanf("%d", &key);
            BiTNode* node = LocateNode(currentTree, key);
            if (node != NULL)
                printf("�ҵ��ؼ���Ϊ %d �Ľ�㡣\n", key);
            else
                printf("δ�ҵ��ؼ���Ϊ %d �Ľ�㣡\n", key);
        }
        break;
        case 7:
        {
            // ���ؼ���Ϊ e �Ľ�㸳ֵ
            KeyType key;
            TElemType newVal;
            printf("������Ŀ����ؼ��� e: ");
            scanf("%d", &key);
            printf("�������¹ؼ���key��������: ");
            scanf("%d", &newVal.key);
            printf("������������Ϣothers���ַ�����: ");
            scanf("%s", newVal.others);
            if (Assign(&currentTree, key, newVal) == OK)
                printf("��㸳ֵ�ɹ���\n");
            else
                printf("��㸳ֵʧ�ܣ�\n");
        }
        break;
        case 8:
        {
            // ��ùؼ���Ϊ e �Ľ����ֵܽ��
            KeyType key;
            printf("������Ҫ�����ֵܽ��Ĺؼ���e: ");
            scanf("%d", &key);
            BiTNode* sibling = GetSibling(currentTree, key);
            if (sibling != NULL)
                printf("�ҵ��ֵܽ�㣬�ؼ���Ϊ: %d\n", sibling->data.key);
            else
                printf("�����ֵܽ�����\n");
        }
        break;
        case 9:
        {
            // ������
            KeyType key;
            TElemType c;
            int lr;
            printf("������Ҫ����λ�õĸ����ؼ��� e: ");
            scanf("%d", &key);
            printf("������Ҫ������Ĺؼ���key��������: ");
            scanf("%d", &c.key);
            printf("������Ҫ�������������Ϣothers���ַ�����: ");
            scanf("%s", c.others);
            printf("��������뷽��0��ʾ��������1��ʾ��������-1��ʾ���ڵ㣩: ");
            scanf("%d", &lr);
            if (InsertNode(&currentTree, key, lr, c) == OK)
                printf("������ɹ���\n");
            else
                printf("������ʧ�ܣ�\n");
        }
        break;
        case 10:
        {
            // ɾ�����
            KeyType key;
            printf("������Ҫɾ���Ľ��ؼ���: ");
            scanf("%d", &key);
            if (DeleteNode(&currentTree, key) == OK)
                printf("ɾ�����ɹ���\n");
            else
                printf("ɾ�����ʧ�ܣ�\n");
        }
        break;
        case 11:
            // ǰ�����
            printf("ǰ����������\n");
            PreOrderTraverse(currentTree, visit);
            printf("\n");
            break;
        case 12:
            // �������
            printf("������������\n");
            InOrderTraverse(currentTree, visit);
            printf("\n");
            break;
        case 13:
            // �������
            printf("������������\n");
            PostOrderTraverse(currentTree, visit);
            printf("\n");
            break;
        case 14:
            // �������
            printf("������������\n");
            LevelOrderTraverse(currentTree, visit);
            printf("\n");
            break;
        case 15:
            // ���ӹ���1�������·����
            printf("���·����Ϊ��%d\n", MaxPathSum(currentTree));
            break;
        case 16:
        {
            // ���ӹ���2���������������
            KeyType e1, e2;
            printf("�������������Ĺؼ��֣�");
            scanf("%d %d", &e1, &e2);
            BiTNode* lca = LowestCommonAncestor(currentTree, e1, e2);
            if (lca != NULL)
                printf("����������ȵĹؼ���Ϊ��%d\n", lca->data.key);
            else
                printf("δ�ҵ�����������ȣ�\n");
        }
        break;
        case 17:
            // ���ӹ���3����ת������
            InvertTree(currentTree);
            printf("�������ѷ�ת��\n");
            break;
        case 18:
        {
            // ���ӹ���4��ʵ�����Ա���ļ���ʽ����
            char filename[100];
            printf("�����뱣���ļ���: ");
            scanf("%s", filename);
            if (SaveBiTree(currentTree, filename) == OK)
                printf("����ɹ���\n");
            else
                printf("����ʧ�ܣ�\n");
        }
        break;
        case 19:
        {
            // ���ӹ���5�����ļ����ش���������
            char filename[100];
            printf("����������ļ���: ");
            scanf("%s", filename);
            if (LoadBiTree(&currentTree, filename) == OK)
                printf("���سɹ���\n");
            else
                printf("����ʧ�ܣ�\n");
        }
        break;
        case 20:
        {
            // ���ӹ���6���������������ϵͳ
            int subChoice = 0;
            do
            {
                PrintSubMenu();
                scanf("%d", &subChoice);
                switch (subChoice)
                {
                case 0:
                    printf("�������˵�...\n");
                    break;
                case 1:
                {
                    // �����µĶ���������ӵ�������
                    int createChoice;
                    printf("��ѡ�񴴽��������ķ�ʽ��\n");
                    printf(" 1. ����������ǵ������������\n");
                    printf(" 2. ǰ��������������\n");
                    printf(" 3. ����������������\n");
                    printf(" 4. ����ʼ��\n");
                    printf("����������ѡ��1/2/3/4����");
                    scanf("%d", &createChoice);

                    BiTree newTree = NULL;
                    if (createChoice == 1)
                    {
                        TElemType def[MAX_TREE_SIZE];
                        int count = 0;
                        printf("���������������ǵ�����������е����ݣ���ʽ��key others����\n");
                        printf("����keyΪ0��ʾ�ս�㣬����keyΪ-1��ʾ���н�����\n");
                        while (1)
                        {
                            printf("�������� %d ������: ", count + 1);
                            scanf("%d %s", &def[count].key, def[count].others);
                            if (def[count].key == -1)
                                break;
                            count++;
                            if (count >= MAX_TREE_SIZE)
                            {
                                printf("�Ѵ�������������ֹͣ���룡\n");
                                break;
                            }
                        }
                        if (CreateBiTree(&newTree, def, 1) == OK)
                            printf("�����������ɹ���\n");
                        else
                            printf("����������ʧ�ܣ�\n");
                    }
                    else if (createChoice == 2)
                    {
                        int n;
                        printf("������ǿս�������n: ");
                        scanf("%d", &n);
                        TElemType* def = (TElemType*)malloc((1 + 2 * n) * sizeof(TElemType)); // �ܳ���Ϊ1+2*n
                        def[0].key = n;  // ����������others�ɺ��ԣ�
                        printf("������ǰ��������е� %d ��������� (key others):\n", n);
                        for (int i = 0; i < n; i++)
                        {
                            printf("ǰ�����е� %d �����: ", i + 1);
                            scanf("%d %s", &def[1 + i].key, def[1 + i].others);
                        }
                        printf("����������������е� %d ��������� (key others):\n", n);
                        for (int i = 0; i < n; i++)
                        {
                            printf("�������е� %d �����: ", i + 1);
                            scanf("%d %s", &def[1 + n + i].key, def[1 + n + i].others);
                        }
                        if (CreateBiTree(&newTree, def, 2) == OK)
                            printf("�����������ɹ���\n");
                        else
                            printf("����������ʧ�ܣ�\n");
                        free(def);
                    }
                    else if (createChoice == 3)
                    {
                        int n;
                        printf("������ǿս������� n: ");
                        scanf("%d", &n);
                        TElemType* def = (TElemType*)malloc((1 + 2 * n) * sizeof(TElemType)); // �ܳ���Ϊ1+2*n
                        def[0].key = n;
                        printf("���������������е� %d ��������� (key others):\n", n);
                        for (int i = 0; i < n; i++)
                        {
                            printf("�������е� %d �����: ", i + 1);
                            scanf("%d %s", &def[1 + i].key, def[1 + i].others);
                        }
                        printf("����������������е� %d ��������� (key others):\n", n);
                        for (int i = 0; i < n; i++)
                        {
                            printf("�������е� %d �����: ", i + 1);
                            scanf("%d %s", &def[1 + n + i].key, def[1 + n + i].others);
                        }
                        if (CreateBiTree(&newTree, def, 3) == OK)
                            printf("�����������ɹ���\n");
                        else
                            printf("����������ʧ�ܣ�\n");
                        free(def);
                    }
                    else if (createChoice == 4) 
                    {
                        if (InitBiTree(&newTree) == OK)
                            printf("��ʼ���������ɹ�\n");
                        else
                            printf("��ʼ��������ʧ�ܣ�\n");
                    }
                    else
                    {
                        printf("������ʽ�������\n");
                        break;
                    }
                    // ����¶������Ĵ�����ѯ���û�Ϊ�ö�����������Ȼ����ӵ���������
                    char name[50];
                    printf("�������¶�����������: ");
                    scanf("%s", name);
                    if (AddBiTree(&manager, name, newTree) == OK)
                        printf("��������ӵ��������ɹ���\n");
                    else
                        printf("���������ʧ�ܣ����ܴ��������������������\n");
                }
                break;
                case 2:
                    // ��ʾ�����������ж�������״̬
                    ListBiTrees(&manager);
                    break;
                case 3:
                {
                    //ɾ��ĳ��������
                    char delName[50];
                    printf("������Ҫɾ���Ķ���������: ");
                    scanf("%s", delName);
                    if (RemoveBiTree(&manager, delName) == OK)
                        printf("ɾ���ɹ���\n");
                    else
                        printf("ɾ��ʧ�ܣ�\n");
                    break;
                }
                case 4:
                {
                    // ѡ��ĳ�����������в���
                    char targetName[50];
                    printf("������Ҫ�����Ķ���������: ");
                    scanf("%s", targetName);
                    BiTree targetTree = GetBiTree(&manager, targetName);
                    if (targetTree == NULL)
                    {
                        printf("�����������ڣ�\n");
                    }
                    else
                    {
                        int subSubChoice = 0;
                        do
                        {
                            PrintSubSubMenu(targetName);
                            scanf("%d", &subSubChoice);
                            switch (subSubChoice)
                            {
                            case 0:
                                printf("���ض�����������Ӳ˵�...\n");
                                break;
                            case 1:
                                if (DestroyBiTree(&targetTree) == OK)
                                    printf("���ٶ������ɹ���\n");
                                else
                                    printf("����ʧ�ܣ�\n");
                                break;
                            case 2:
                                if (ClearBiTree(&targetTree) == OK)
                                    printf("��ն������ɹ���\n");
                                else
                                    printf("���ʧ�ܣ�\n");
                                break;
                            case 3:
                                if (BiTreeEmpty(targetTree))
                                    printf("������Ϊ�ա�\n");
                                else
                                    printf("��������Ϊ�ա�\n");
                                break;
                            case 4:
                                printf("���������Ϊ��%d\n", BiTreeDepth(targetTree));
                                break;
                            case 5:
                            {
                                KeyType key;
                                printf("��������ҽ��Ĺؼ���: ");
                                scanf("%d", &key);
                                BiTNode* res = LocateNode(targetTree, key);
                                if (res)
                                    printf("�ҵ��ؼ���Ϊ %d �Ľ��\n", res->data.key);
                                else
                                    printf("δ�ҵ��ý�㣡\n");
                            }
                            break;
                            case 6:
                            {
                                KeyType key;
                                TElemType newVal;
                                printf("��������ؼ��� e: ");
                                scanf("%d", &key);
                                printf("�������¹ؼ���key��������: ");
                                scanf("%d", &newVal.key);
                                printf("������������Ϣothers���ַ�����: ");
                                scanf("%s", newVal.others);
                                if (Assign(&targetTree, key, newVal) == OK)
                                    printf("��ֵ�ɹ���\n");
                                else
                                    printf("��ֵʧ�ܣ�\n");
                            }
                            break;
                            case 7:
                            {
                                KeyType key;
                                printf("����������ֵܽ��Ĺؼ��� e: ");
                                scanf("%d", &key);
                                BiTNode* sib = GetSibling(targetTree, key);
                                if (sib)
                                    printf("�ֵܽ��ؼ���Ϊ��%d\n", sib->data.key);
                                else
                                    printf("�����ֵܽ�����\n");
                            }
                            break;
                            case 8:
                            {
                                KeyType key;
                                TElemType nodeVal;
                                int lr;
                                printf("������Ҫ����λ�õĸ����ؼ��� e: ");
                                scanf("%d", &key);
                                printf("������Ҫ������Ĺؼ���key��������: ");
                                scanf("%d", &nodeVal.key);
                                printf("������Ҫ�������������Ϣothers���ַ�����: ");
                                scanf("%s", nodeVal.others);
                                printf("��������뷽��0��ʾ��������1��ʾ��������-1��ʾ���ڵ㣩: ");
                                scanf("%d", &lr);
                                if (InsertNode(&targetTree, key, lr, nodeVal) == OK)
                                    printf("����ɹ���\n");
                                else
                                    printf("����ʧ�ܣ�\n");
                            }
                            break;
                            case 9:
                            {
                                KeyType key;
                                printf("������Ҫɾ�����Ĺؼ���: ");
                                scanf("%d", &key);
                                if (DeleteNode(&targetTree, key) == OK)
                                    printf("ɾ���ɹ���\n");
                                else
                                    printf("ɾ��ʧ�ܣ�\n");
                            }
                            break;
                            case 10:
                                printf("ǰ����������\n");
                                PreOrderTraverse(targetTree, visit);
                                printf("\n");
                                break;
                            case 11:
                                printf("������������\n");
                                InOrderTraverse(targetTree, visit);
                                printf("\n");
                                break;
                            case 12:
                                printf("������������\n");
                                PostOrderTraverse(targetTree, visit);
                                printf("\n");
                                break;
                            case 13:
                                printf("������������\n");
                                LevelOrderTraverse(targetTree, visit);
                                printf("\n");
                                break;
                            case 14:
                                printf("���·����Ϊ��%d\n", MaxPathSum(targetTree));
                                break;
                            case 15:
                            {
                                KeyType a, b;
                                printf("�������������Ĺؼ��֣�");
                                scanf("%d %d", &a, &b);
                                BiTNode* lca = LowestCommonAncestor(targetTree, a, b);
                                if (lca)
                                    printf("�����������Ϊ��%d\n", lca->data.key);
                                else
                                    printf("δ�ҵ�����������ȣ�\n");
                            }
                            break;
                            case 16:
                                InvertTree(targetTree);
                                printf("�������ѷ�ת��\n");
                                break;
                            case 17:
                            {
                                char fname[100];
                                printf("�����뱣���ļ���: ");
                                scanf("%s", fname);
                                if (SaveBiTree(targetTree, fname) == OK)
                                    printf("����ɹ���\n");
                                else
                                    printf("����ʧ�ܣ�\n");
                            }
                            break;
                            case 18:
                            {
                                char fname[100];
                                printf("����������ļ���: ");
                                scanf("%s", fname);
                                if (LoadBiTree(&targetTree, fname) == OK)
                                    printf("���سɹ���\n");
                                else
                                    printf("����ʧ�ܣ�\n");
                            }
                            break;
                            default:
                                printf("��Чѡ����������ȷ��ѡ�\n");
                                break;
                            }
                        } while (subSubChoice != 0);
                    }
                }
                break;
                default:
                    printf("��Чѡ����������ȷ��ѡ�\n");
                    break;
                }
            } while (subChoice != 0);
        }
        break;
        default:
            printf("��Чѡ����������ȷ��ѡ�\n");
            break;
        }
    }
    return 0;
}