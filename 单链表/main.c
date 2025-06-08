#define _CRT_SECURE_NO_WARNINGS

#include"functions.h"

int main()
{
    system("color F0");
    LinkList singleL = NULL;  // ����������õı���
    MultiList ml;             // �����������ϵͳ
    InitMultiList(&ml);       // ��ʼ�������������

    int choice;
    char listNames[MAX_LISTS][30] = { 0 };

    do {
        PrintMenu();

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');  // ������뻺����
            continue;
        }

        switch (choice)
        {
        case 0:
            printf("�˳�ϵͳ��\n");
            break;
        case 1: {  // ��ʼ������������ѡ�������룩
            if (singleL != NULL) {
                int confirm;
                printf("�������Ѵ��ڣ����³�ʼ�������ٵ�ǰ�����Ƿ������(1-��, 0-��): ");
                scanf("%d", &confirm);
                if (confirm == 1) {
                    if (DestroyList(&singleL) == OK)
                        printf("ԭ�е����������١�\n");
                    else
                        printf("����ʧ�ܣ�\n");
                }
                else {
                    printf("����ȡ����\n");
                    break;
                }
            }
            if (InitList(&singleL) == OK)
                printf("�������ʼ���ɹ���\n");
            else
                printf("�������ʼ��ʧ�ܣ�\n");
            break;
        }
        case 2: {  // ���ٵ�ǰ������
            if (singleL == NULL)
                printf("��ǰ�޵�������ڣ�\n");
            else {
                if (DestroyList(&singleL) == OK)
                    printf("���������ٳɹ���\n");
                else
                    printf("����ʧ�ܣ�\n");
            }
            break;
        }
        case 3: {  // ��յ�ǰ����������ͷ��㣩
            if (singleL == NULL)
                printf("��ǰ�޵�������ڣ�\n");
            else {
                if (ClearList(&singleL) == OK)
                    printf("����������գ�\n");
                else
                    printf("���ʧ�ܣ�\n");
            }
            break;
        }
        case 4: {  // �ж��Ƿ�Ϊ��
            if (singleL == NULL)
                printf("��ǰ�޵�������ڣ�\n");
            else {
                status ret = ListEmpty(singleL);
                if (ret == TRUE)
                    printf("������Ϊ�գ�\n");
                else if (ret == FALSE)
                    printf("������Ϊ�գ�\n");
                else
                    printf("����ʧ�ܣ�\n");
            }
            break;
        }
        case 5: {  // ��ȡ����
            if (singleL == NULL)
                printf("��ǰ�޵�������ڣ�\n");
            else {
                int len = ListLength(singleL);
                if (len == INFEASIBLE)
                    printf("����ʧ�ܣ�\n");
                else
                    printf("��������Ϊ��%d\n", len);
            }
            break;
        }
        case 6: {  // ��õ� i ��Ԫ��
            if (singleL == NULL) {
                printf("��ǰ�޵�������ڣ�\n");
            }
            else {
                int i;
                ElemType e;
                printf("������Ҫ��ȡ��Ԫ�����i: ");
                scanf("%d", &i);
                if (GetElem(singleL, i, &e) == OK)
                    printf("������� %d ��Ԫ�ص�ֵΪ��%d\n", i, e);
                if(GetElem(singleL, i, &e) == INFEASIBLE)
                    printf("��ǰ�޵�������ڣ�\n");
                if (GetElem(singleL, i, &e) == ERROR)
                    printf("λ�ò��Ϸ���\n");
            }
            break;
        }
        case 7: {  // ����Ԫ�� e ��λ��
            if (singleL == NULL) {
                printf("��ǰ�޵�������ڣ�\n");
            }
            else {
                ElemType e;
                printf("������Ҫ���ҵ�Ԫ��e: ");
                scanf("%d", &e);
                int pos = LocateElem(singleL, e);
                if (pos == INFEASIBLE)
                    printf("����ʧ�ܣ�\n");
                else if (pos == ERROR)
                    printf("δ�ҵ�Ԫ�� %d��\n", e);
                else
                    printf("Ԫ�� %d �ڵ������е�λ��Ϊ��%d\n", e, pos);
            }
            break;
        }
        case 8: {  // ���Ԫ�� e ��ǰ��
            if (singleL == NULL) {
                printf("��ǰ�޵�������ڣ�\n");
            }
            else {
                ElemType e, pre;
                printf("������Ҫ��ѯ��ǰ����Ԫ��e: ");
                scanf("%d", &e);
                if (PriorElem(singleL, e, &pre) == OK)
                    printf("Ԫ�� %d ��ǰ��Ϊ��%d\n", e, pre);
                if(PriorElem(singleL, e, &pre) == ERROR)
                    printf("û���ҵ���Ԫ�ػ��Ԫ��Ϊ��һ����\n");
                if (PriorElem(singleL, e, &pre) == INFEASIBLE)
                    printf("���������ڻ�����Ϊ�գ�\n");
            }
            break;
        }
        case 9: {  // ���Ԫ�� e �ĺ��
            if (singleL == NULL) {
                printf("��ǰ�޵�������ڣ�\n");
            }
            else {
                ElemType e, next;
                printf("������Ҫ��ѯ���̵�Ԫ��e: ");
                scanf("%d", &e);
                if (NextElem(singleL, e, &next) == OK)
                    printf("Ԫ�� %d �ĺ��Ϊ��%d\n", e, next);
                if (NextElem(singleL, e, &next) == ERROR)
                    printf("û���ҵ���̻��Ԫ��Ϊ���һ����\n");
                if (NextElem(singleL, e, &next) == INFEASIBLE)
                    printf("���������ڻ�����Ϊ�գ�\n");
            }
            break;
        }
        case 10: { // �ڵ������в���Ԫ��
            if (singleL == NULL) {
                printf("��ǰ�޵�������ڣ����ȳ�ʼ����\n");
            }
            else {
                int pos;
                ElemType e;
                printf("���������λ��i: ");
                scanf("%d", &pos);
                printf("������Ҫ�����Ԫ��e: ");
                scanf("%d", &e);
                if (ListInsert(&singleL, pos, e) == OK)
                    printf("����ɹ���\n");
                else
                    printf("����ʧ�ܣ�\n");
            }
            break;
        }
        case 11: { // ɾ���������е�Ԫ��
            if (singleL == NULL) {
                printf("��ǰ�޵�������ڣ����ȳ�ʼ����\n");
            }
            else {
                int pos;
                ElemType e;
                printf("������Ҫɾ����Ԫ�ص�λ��i: ");
                scanf("%d", &pos);
                if (ListDelete(&singleL, pos, &e) == OK)
                    printf("ɾ���ɹ���ɾ����Ԫ��Ϊ��%d\n", e);
                if (ListDelete(&singleL, pos, &e) == ERROR)
                    printf("λ�ò��Ϸ���ɾ��ʧ�ܣ�\n");
                if (ListDelete(&singleL, pos, &e) == INFEASIBLE)
                    printf("���������ڣ�\n");
            }
            break;
        }
        case 12: { // ����������
            if (singleL == NULL) {
                printf("��ǰ�޵�������ڣ�\n");
            }
            else {
                printf("�������е�Ԫ��Ϊ��");
                if (ListTraverse(singleL) != OK)
                    printf("����ʧ�ܣ�\n");
            }
            break;
        }
        case 13: { // ��ת������
            if (singleL == NULL) {
                printf("��ǰ�޵�������ڣ�\n");
            }
            else {
                if (reverseList(singleL) == OK)
                    printf("����ת�ɹ���\n");
                else
                    printf("��תʧ�ܣ�\n");
            }
            break;
        }
        case 14: { // ɾ�������� n �����
            if (singleL == NULL) {
                printf("��ǰ�޵�������ڣ�\n");
            }
            else {
                int n;
                printf("������ɾ��������n������nֵ: ");
                scanf("%d", &n);
                if (RemoveNthFromEnd(singleL, n) == OK)
                    printf("ɾ���ɹ���\n");
                else
                    printf("ɾ��ʧ�ܣ�\n");
            }
            break;
        }
        case 15: { // �Ե������������
            if (singleL == NULL) {
                printf("��ǰ�޵�������ڣ�\n");
            }
            else {
                if (sortList(singleL) == OK)
                    printf("����ɹ���\n");
                else
                    printf("����ʧ�ܣ�\n");
            }
            break;
        }
        case 16: { // ���浥�����ļ�
            if (singleL == NULL) {
                printf("��ǰ�޵�������ڣ�\n");
            }
            else {
                char filename[100];
                printf("�����뱣���ļ����ļ���: ");
                scanf("%s", filename);
                if (SaveList(singleL, filename) == OK)
                    printf("����ɹ���\n");
                else
                    printf("����ʧ�ܣ�\n");
            }
            break;
        }
        case 17: { // ���ļ����ص�����
            if (singleL != NULL) {
                printf("��ǰ���е������������ٺ��ټ����ļ���\n");
            }
            else {
                char filename[100];
                printf("����������ļ����ļ���: ");
                scanf("%s", filename);
                if (LoadList(&singleL, filename) == OK)
                    printf("���سɹ���\n");
                else
                    printf("����ʧ�ܣ�\n");
            }
            break;
        }
        case 18: {
            /* --- �����Ա������ϵͳ --- */
            int subChoice;
            do {
                PrintSubMenu();
                int ret = scanf("%d", &subChoice);
                if (ret != 1) {
                    // ��ջ���
                    while (getchar() != '\n');
                    printf("��Чѡ�����������룡\n");
                    continue; // ���½���ѭ��
                }
                switch (subChoice)
                {
                case 0:
                    printf("�������˵���\n");
                    break;
                case 1: {
                    // �����µĵ������������û�Ϊ������������
                    char tempName[30];
                    printf("�����������������: ");
                    scanf("%s", tempName);
                    if (CreateNewList(&ml) == OK) {
                        // �������������е��±�Ϊ ml.count - 1
                        strcpy(listNames[ml.count - 1], tempName);
                        printf("����������ɹ�, ��������Ϊ \"%s\".\n", tempName);
                    }
                    else {
                        printf("��������ʧ�ܣ�\n");
                    }
                    break;
                }
                case 2: {
                    //ɾ��ĳ��������
                    char listname[30];
                    printf("������Ҫɾ������������֣�");
                    scanf("%s", listname);
                    RemoveList(&ml, listNames, listname);
                }
                case 3: {
                    // ��ʾ���е�����״̬���������֡�����Ԫ�ء���
                    if (ml.count == 0)
                        printf("��ǰ��������ڣ�\n");
                    else {
                        printf("\n��������״̬��\n");
                        for (int j = 0; j < ml.count; j++) {
                            int len = ListLength(ml.lists[j]);
                            printf("��������: \"%s\", ����: %d, Ԫ��: ", listNames[j], len);
                            ListTraverse(ml.lists[j]);
                        }
                    }
                    break;
                }
                case 4: {
                    // ��������ĳ������������������������ֲ���
                    char searchName[30];
                    printf("������Ҫ��������������: ");
                    scanf("%s", searchName);
                    int foundIndex = -1;
                    for (int j = 0; j < ml.count; j++) {
                        if (strcmp(listNames[j], searchName) == 0) {
                            foundIndex = j;
                            break;
                        }
                    }
                    if (foundIndex == -1) {
                        printf("δ�ҵ�������\n");
                    }
                    else {
                        int op;
                        do {
                            PrintSubSubMenu(searchName);
                            int ret = scanf("%d", &op);
                            if (ret != 1) {
                                // ��ջ���
                                while (getchar() != '\n');
                                printf("��Чѡ�����������룡\n");
                                continue; // ���½���ѭ��
                            }
                            switch (op)
                            {
                            case 0:
                                printf("���ض����������ϵͳ��\n");
                                break;
                            case 1: {
                                if (DestroyList(&ml.lists[foundIndex]) == OK) {
                                    printf("���� \"%s\" �����٣�\n", searchName);
                                    // ɾ����������������¼ǰ��
                                    for (int k = foundIndex; k < ml.count - 1; k++) {
                                        ml.lists[k] = ml.lists[k + 1];
                                        strcpy(listNames[k], listNames[k + 1]);
                                    }
                                    ml.lists[ml.count - 1] = NULL;
                                    ml.count--;
                                    op = 0;  // �������Ӳ˵�
                                }
                                else {
                                    printf("����ʧ�ܣ�\n");
                                }
                            } break;
                            case 2: {
                                if (ClearList(&ml.lists[foundIndex]) == OK)
                                    printf("���� \"%s\" ��ճɹ���\n", searchName);
                                else
                                    printf("��ղ���ʧ�ܣ�\n");
                            } break;
                            case 3: {
                                status ret = ListEmpty(ml.lists[foundIndex]);
                                if (ret == TRUE)
                                    printf("���� \"%s\" Ϊ�գ�\n", searchName);
                                else if (ret == FALSE)
                                    printf("���� \"%s\" ��Ϊ�գ�\n", searchName);
                                else
                                    printf("����ʧ�ܣ�\n");
                            } break;
                            case 4: {
                                int len = ListLength(ml.lists[foundIndex]);
                                if (len == INFEASIBLE)
                                    printf("����ʧ�ܣ�\n");
                                else
                                    printf("���� \"%s\" �ĳ���Ϊ��%d\n", searchName, len);
                            } break;
                            case 5: {
                                int pos;
                                ElemType e;
                                printf("������Ҫ��ȡ��Ԫ��λ��: ");
                                scanf("%d", &pos);
                                if (GetElem(ml.lists[foundIndex], pos, &e) == OK)
                                    printf("���� \"%s\" �ĵ� %d ��Ԫ��Ϊ��%d\n", searchName, pos, e);
                                else
                                    printf("����ʧ�ܣ�\n");
                            } break;
                            case 6: {
                                ElemType e;
                                printf("������Ҫ���ҵ�Ԫ��: ");
                                scanf("%d", &e);
                                int pos = LocateElem(ml.lists[foundIndex], e);
                                if (pos == ERROR)
                                    printf("δ�ҵ�Ԫ�� %d��\n", e);
                                else if (pos == INFEASIBLE)
                                    printf("����ʧ�ܣ�\n");
                                else
                                    printf("Ԫ�� %d ������ \"%s\" �е�λ��Ϊ��%d\n", e, searchName, pos);
                            } break;
                            case 7: {
                                ElemType e, pre;
                                printf("������Ҫ��ѯǰ����Ԫ��: ");
                                scanf("%d", &e);
                                if (PriorElem(ml.lists[foundIndex], e, &pre) == OK)
                                    printf("Ԫ�� %d ��ǰ��Ϊ��%d\n", e, pre);
                                else
                                    printf("����ʧ�ܣ�\n");
                            } break;
                            case 8: {
                                ElemType e, next;
                                printf("������Ҫ��ѯ��̵�Ԫ��: ");
                                scanf("%d", &e);
                                if (NextElem(ml.lists[foundIndex], e, &next) == OK)
                                    printf("Ԫ�� %d �ĺ��Ϊ��%d\n", e, next);
                                else
                                    printf("����ʧ�ܣ�\n");
                            } break;
                            case 9: {
                                int pos;
                                ElemType e;
                                printf("���������λ��: ");
                                scanf("%d", &pos);
                                printf("������Ҫ�����Ԫ��: ");
                                scanf("%d", &e);
                                if (ListInsert(&ml.lists[foundIndex], pos, e) == OK)
                                    printf("����ɹ���\n");
                                else
                                    printf("����ʧ�ܣ�\n");
                            } break;
                            case 10: {
                                int pos;
                                ElemType e;
                                printf("������ɾ��λ��: ");
                                scanf("%d", &pos);
                                if (ListDelete(&ml.lists[foundIndex], pos, &e) == OK)
                                    printf("ɾ���ɹ���ɾ����Ԫ��Ϊ��%d\n", e);
                                else
                                    printf("ɾ��ʧ�ܣ�\n");
                            } break;
                            case 11: {
                                printf("���� \"%s\" ��Ԫ��: ", searchName);
                                if (ListTraverse(ml.lists[foundIndex]) != OK)
                                    printf("����ʧ�ܣ�\n");
                            } break;
                            case 12: {
                                if (reverseList(ml.lists[foundIndex]) == OK)
                                    printf("���� \"%s\" ��ת�ɹ���\n", searchName);
                                else
                                    printf("��תʧ�ܣ�\n");
                            } break;
                            case 13: {
                                int n;
                                printf("������ɾ�������� n ������ n ֵ: ");
                                scanf("%d", &n);
                                if (RemoveNthFromEnd(ml.lists[foundIndex], n) == OK)
                                    printf("ɾ���ɹ���\n");
                                else
                                    printf("ɾ��ʧ�ܣ�\n");
                            } break;
                            case 14: {
                                if (sortList(ml.lists[foundIndex]) == OK)
                                    printf("���� \"%s\" ����ɹ���\n", searchName);
                                else
                                    printf("����ʧ�ܣ�\n");
                            } break;
                            case 15: {
                                char filename[100];
                                printf("�����뱣���ļ����ļ���: ");
                                scanf("%s", filename);
                                if (SaveList(ml.lists[foundIndex], filename) == OK)
                                    printf("����ɹ���\n");
                                else
                                    printf("����ʧ�ܣ�\n");
                            } break;
                            default:
                                printf("��Чѡ�����������룡\n");
                            } // end switch (op)
                        } while (op != 0);
                    }
                } break;
                default:
                    printf("��Чѡ�����������룡\n");
                }
            } while (subChoice != 0);
        } break;
        default:
            printf("��Чѡ�����������룡\n");
        }
    } while (choice != 0);

    // �˳�ǰ�ͷŵ��������������������������ռ���ڴ�
    if (singleL != NULL)
        DestroyList(&singleL);
    for (int i = 0; i < ml.count; i++) {
        DestroyList(&ml.lists[i]);
    }
    printf("�������˳���\n");
    return 0;
}
