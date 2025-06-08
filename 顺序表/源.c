#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

/* ��������Ԫ�����Ͷ��� */
typedef int status;
typedef int ElemType;

/* ˳���˳��ṹ���Ķ��� */
typedef struct {
    ElemType* elem;
    int length;
    int listsize;
} SqList;

/* �����Ա����Ķ��� */
typedef struct {
    struct {
        char name[30];
        SqList L;
    } elem[10];
    int length;
} LISTS;

LISTS Lists;  // �����Ա�ȫ�ֹ������

SqList L;
int choice;         // ���˵�ѡ��
int pre, next;      // �洢ǰ�������
ElemType e, k;      // ���ڴ洢����

/* ����1������˳��� */
status InitList(SqList* L) {
    if (L->elem == NULL) {  // �������򴴽�
        L->elem = (ElemType*)malloc(sizeof(ElemType) * LIST_INIT_SIZE);
        if (!L->elem)
            return ERROR;
        L->length = 0;
        L->listsize = LIST_INIT_SIZE;
        printf("�ɹ�����������1д�����ݣ�����0��������¼�룺\n");
        int numIn;
        scanf("%d", &numIn);
        if (numIn == 1) {
            int count;
            printf("������д��Ԫ�صĸ�����������%d����\n", LIST_INIT_SIZE);
            scanf("%d", &count);
            if (count > LIST_INIT_SIZE) {
                ElemType* newbase = (ElemType*)realloc(L->elem, count * sizeof(ElemType));
                if (!newbase) {
                    printf("���·���ռ�ʧ��\n");
                    return ERROR;
                }
                L->elem = newbase;
                L->listsize = count;
            }
            L->length = count;
            printf("��д��%d�����ݣ�\n", count);
            for (int i = 0; i < count; i++) {
                scanf("%d", &L->elem[i]);
            }
        }
        return OK;
    }
    return INFEASIBLE;
}

/* ����2������˳��� */
status DestroyList(SqList* L) {
    if (L->elem == NULL)
        return INFEASIBLE;
    free(L->elem);
    L->elem = NULL;
    L->length = 0;
    L->listsize = 0;
    return OK;
}

/* ����3�����˳��� */
status ClearList(SqList* L) {
    if (L->elem == NULL)
        return INFEASIBLE;
    for (int i = 0; i < L->length; i++)
        L->elem[i] = 0;
    L->length = 0;
    return OK;
}

/* ����4���ж����Ա��Ƿ�Ϊ�� */
status ListEmpty(SqList L) {
    if (L.elem == NULL)
        return INFEASIBLE;
    return (L.length == 0) ? TRUE : FALSE;
}

/* ����5���������Ա��� */
status ListLength(SqList L) {
    if (L.elem == NULL)
        return INFEASIBLE;
    return L.length;
}

/* ����6����ȡ��i��Ԫ�� */
status GetElem(SqList L, int i, ElemType* e) {
    if (L.elem == NULL)
        return INFEASIBLE;
    if (i >= 1 && i <= L.length) {
        *e = L.elem[i - 1];
        return OK;
    }
    else {
        return ERROR;
    }
}

/* ����7������ָ��Ԫ�أ�����1-basedλ�ã� */
int LocateElem(SqList L, ElemType e) {
    if (L.elem == NULL)
        return -1;
    for (int i = 0; i < L.length; i++) {
        if (L.elem[i] == e)
            return i + 1;
    }
    return 0;
}

/* ����8����ȡָ��Ԫ�ص�ǰ�� */
status PriorElem(SqList L, ElemType e, int* pre) {
    if (L.elem == NULL)
        return INFEASIBLE;
    for (int i = 0; i < L.length; i++) {
        if (L.elem[i] == e) {
            if (i == 0)
                return ERROR;
            *pre = L.elem[i - 1];
            return OK;
        }
    }
    return ERROR;
}

/* ����9����ȡָ��Ԫ�صĺ�� */
status NextElem(SqList L, ElemType e, int* next) {
    if (L.elem == NULL)
        return INFEASIBLE;
    for (int i = 0; i < L.length; i++) {
        if (L.elem[i] == e) {
            if (i == L.length - 1)
                return ERROR;
            *next = L.elem[i + 1];
            return OK;
        }
    }
    return ERROR;
}

/* ����10����ָ��λ�ò���Ԫ�� */
status ListInsert(SqList* L, int i, ElemType e) {
    if (L->elem == NULL)
        return INFEASIBLE;
    if (i < 1 || i > L->length + 1)
        return ERROR;
    if (L->length >= L->listsize) {
        ElemType* newbase = (ElemType*)realloc(L->elem, (L->listsize + LISTINCREMENT) * sizeof(ElemType));
        if (newbase == NULL)
            return ERROR;
        L->elem = newbase;
        L->listsize += LISTINCREMENT;
    }
    for (int j = L->length; j >= i; j--) {
        L->elem[j] = L->elem[j - 1];
    }
    L->elem[i - 1] = e;
    L->length++;
    return OK;
}

/* ����11��ɾ��ָ��λ��Ԫ�� */
status ListDelete(SqList* L, int i, ElemType* e) {
    if (L->elem == NULL)
        return INFEASIBLE;
    if (i < 1 || i > L->length)
        return ERROR;
    *e = L->elem[i - 1];
    for (int j = i - 1; j < L->length - 1; j++)
        L->elem[j] = L->elem[j + 1];
    L->length--;
    return OK;
}

/* ����12������˳��� */
status ListTraverse(SqList L) {
    if (L.elem == NULL)
        return INFEASIBLE;
    for (int i = 0; i < L.length; i++) {
        printf("%d", L.elem[i]);
        if (i != L.length - 1)
            printf(" ");
    }
    return OK;
}

/* ����13������������������ */
status MaxSubArray(SqList L) {
    int res = 0, now = 0;
    for (int i = 0; i < L.length; i++) {
        now = 0;
        for (int j = i; j < L.length; j++) {
            now += L.elem[j];
            if (now > res)
                res = now;
        }
    }
    return res;
}

/* ����14�����Ϊk��������������������� */
status SubArrayNum(SqList L, ElemType k) {
    int num = 0;
    for (int i = 0; i < L.length; i++) {
        int now = 0;
        for (int j = i; j < L.length; j++) {
            now += L.elem[j];
            if (now == k)
                num++;
        }
    }
    return num;
}

/* ����15����С��������ð������ */
void SortList(SqList* L) {
    for (int i = 0; i < L->length; i++) {
        for (int j = 0; j < L->length - 1 - i; j++) {
            if (L->elem[j] > L->elem[j + 1]) {
                int temp = L->elem[j];
                L->elem[j] = L->elem[j + 1];
                L->elem[j + 1] = temp;
            }
        }
    }
}

/* ����16���Զ����Ʒ�ʽ�������Ա��ļ� */
status SaveInFile(SqList L, char* filename) {
    FILE* fp = fopen(filename, "wb");
    if (fp == NULL) {
        perror("�ļ���ʧ��");
        return ERROR;
    }
    fwrite(&L.length, sizeof(int), 1, fp);
    for (int i = 0; i < L.length; i++)
        fwrite(&L.elem[i], sizeof(int), 1, fp);
    fclose(fp);
    return OK;
}

/* ʹ���ı���ʽ�������Ա��ļ� */
status saveListToFile(SqList L, char* filename) {
    FILE* fp = fopen(filename, "w");
    if (fp == NULL)
        return INFEASIBLE;
    for (int i = 0; i < L.length; i++)
        fprintf(fp, "%d ", L.elem[i]);
    fclose(fp);
    return OK;
}

/* ���������ļ��������Ա����ı���ʽ��ȡ�� */
status loadListFromFile(SqList* L, char* filename) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL)
        return INFEASIBLE;
    ClearList(L);
    ElemType data;
    while (fscanf(fp, "%d", &data) != EOF) {
        ListInsert(L, ListLength(*L) + 1, data);
    }
    ListTraverse(*L);
    fclose(fp);
    return OK;
}

/* �����Ա������ */
/* ����һ�����Ա���һ������ΪListName�Ŀ�˳������Lists */
status AddList(LISTS* Lists, char ListName[]) {
    if (Lists->length >= 10)
        return ERROR;  // ������������
    strcpy(Lists->elem[Lists->length].name, ListName);
    Lists->elem[Lists->length].L.elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (Lists->elem[Lists->length].L.elem == NULL)
        return ERROR;
    Lists->elem[Lists->length].L.length = 0;
    Lists->elem[Lists->length].L.listsize = LIST_INIT_SIZE;
    Lists->length++;
    return OK;
}

/* ɾ��һ�����Ա� */
status RemoveList(LISTS* Lists, char ListName[]) {
    for (int i = 0; i < Lists->length; i++) {
        if (strcmp(Lists->elem[i].name, ListName) == 0) {
            free(Lists->elem[i].L.elem);
            for (int k = i; k < Lists->length - 1; k++) {
                Lists->elem[k] = Lists->elem[k + 1];
            }
            Lists->length--;
            return OK;
        }
    }
    return ERROR;
}

/* �������Ա��ɹ�����1-basedλ�ã�ʧ�ܷ���0 */
int LocateList(LISTS Lists, char ListName[]) {
    for (int i = 0; i < Lists.length; i++) {
        if (strcmp(Lists.elem[i].name, ListName) == 0)
            return i + 1;
    }
    return 0;
}

/* ������ */
int main() {
    /* ��ʼ��ȫ�ֱ��� */
    L.elem = NULL;
    L.length = 0;
    L.listsize = 0;
    Lists.length = 0;

    while (1) {
        printf("\n-----˳�����ʾϵͳ-----\n");
        printf("0. �˳���ʾϵͳ\n");
        printf("1. ��������˳���\n");
        printf("2. ���ٵ���˳���\n");
        printf("3. ��յ���˳���\n");
        printf("4. �жϵ���˳����Ƿ�Ϊ��\n");
        printf("5. �������˳�����\n");
        printf("6. ��ȡ����˳���ָ��λ��Ԫ��\n");
        printf("7. ����Ԫ���ڵ���˳����е�λ��\n");
        printf("8. ��ȡ����˳���ָ��Ԫ�ص�ǰ��\n");
        printf("9. ��ȡ����˳���ָ��Ԫ�صĺ��\n");
        printf("10. �ڵ���˳�����ָ��λ�ò���Ԫ��\n");
        printf("11. ɾ������˳���ָ��λ��Ԫ��\n");
        printf("12. ��������˳���\n");
        printf("13. ���ӹ���1������������������\n");
        printf("14. ���ӹ���2�����Ϊk�����������\n");
        printf("15. ���ӹ���3����С��������\n");
        printf("16. ���ӹ���4�����浥��˳����ļ�\n");
        printf("17. ���ӹ���5�������Ա����\n");
        printf("18. ���ӹ���6�����ļ���ȡ����˳���\n");
        printf("����������ѡ��");
        scanf("%d", &choice);

        int res, pos, tempPos, element;
        char filename[30];

        switch (choice) {
        case 0:
            printf("���ѽ���ʹ��\n");
            return 0;
        case 1:
            if (InitList(&L) == OK)
                printf("����˳���ɹ���������¼��\n");
            else
                printf("˳�����ʧ�ܻ��Ѵ���\n");
            break;
        case 2:
            if (DestroyList(&L) == OK)
                printf("����˳���ɹ�\n");
            else
                printf("˳������ڣ�����ʧ��\n");
            break;
        case 3:
            if (ClearList(&L) == OK)
                printf("���˳���ɹ�\n");
            else
                printf("˳������ڣ��޷����\n");
            break;
        case 4: {
            int emptyResult = ListEmpty(L);
            if (emptyResult == INFEASIBLE)
                printf("˳�������\n");
            else if (emptyResult == TRUE)
                printf("˳���Ϊ��\n");
            else
                printf("˳���Ϊ��\n");
            break;
        }
        case 5:
        {
            int length = ListLength(L);
            if (length == -1) printf("˳������ڣ�\n");
            else
                printf("˳�����Ϊ��%d\n", length);
            break;
        }
        case 6:
            printf("������Ҫ��ȡԪ�ص�λ�ã�\n");
            scanf("%d", &tempPos);
            switch (GetElem(L, tempPos, &element)) {
            case OK:
                printf("��%d��Ԫ��Ϊ��%d\n", tempPos, element);
                break;
            case ERROR:
                printf("λ�ò��Ϸ�\n");
                break;
            case INFEASIBLE:
                printf("˳�������\n");
                break;
            }
            break;
        case 7:
            printf("������Ҫ���ҵ�Ԫ�أ�\n");
            scanf("%d", &element);
            pos = LocateElem(L, element);
            if (pos == -1)
                printf("˳�������\n");
            else if (pos == 0)
                printf("�Ҳ�����Ԫ��\n");
            else
                printf("��Ԫ��λ�ڵ�%d��λ��\n", pos);
            break;
        case 8:
            printf("���������ǰ����Ŀ��Ԫ�أ�\n");
            scanf("%d", &element);
            switch (PriorElem(L, element, &pre)) {
            case INFEASIBLE:
                printf("˳�������\n");
                break;
            case ERROR:
                printf("��Ԫ��û��ǰ��\n");
                break;
            case OK:
                printf("��Ԫ�ص�ǰ��Ϊ��%d\n", pre);
                break;
            }
            break;
        case 9:
            printf("��������Һ�̵�Ŀ��Ԫ�أ�\n");
            scanf("%d", &element);
            switch (NextElem(L, element, &next)) {
            case INFEASIBLE:
                printf("˳�������\n");
                break;
            case ERROR:
                printf("��Ԫ��û�к��\n");
                break;
            case OK:
                printf("��Ԫ�صĺ��Ϊ��%d\n", next);
                break;
            }
            break;
        case 10:
            printf("����������λ�ú�Ԫ�أ�\n");
            scanf("%d %d", &tempPos, &element);
            switch (ListInsert(&L, tempPos, element)) {
            case INFEASIBLE:
                printf("˳�������\n");
                break;
            case ERROR:
                printf("����λ�ò��Ϸ�\n");
                break;
            case OK:
                printf("����ɹ�\n");
                break;
            }
            break;
        case 11:
            printf("������ɾ��Ԫ�ص�λ�ã�\n");
            scanf("%d", &tempPos);
            switch (ListDelete(&L, tempPos, &element)) {
            case INFEASIBLE:
                printf("˳�������\n");
                break;
            case ERROR:
                printf("ɾ��λ�ô������Ԫ��\n");
                break;
            case OK:
                printf("ɾ���ɹ�����ɾԪ��Ϊ��%d\n", element);
                break;
            }
            break;
        case 12:
            ListTraverse(L);
            printf("\n");
            break;
        case 13:
            printf("�������������ĺ�Ϊ��%d\n", MaxSubArray(L));
            break;
        case 14:
            printf("������Ŀ��ֵk��\n");
            scanf("%d", &k);
            printf("�������������������Ϊ��%d\n", SubArrayNum(L, k));
            break;
        case 15:
            SortList(&L);
            printf("�������\n");
            break;
        case 16:
            printf("�����뱣���ļ�����\n");
            scanf("%s", filename);
            res = SaveInFile(L, filename);
            if (res == OK)
                printf("����ɹ�\n");
            else
                printf("����ʧ��\n");
            break;
        case 17: {
            /* �����Ա�����Ӳ˵� */
            int multiChoice;
            printf("��ѡ�������\n");
            printf("1. ����һ�������Ա�\n");
            printf("2. ɾ��һ�����Ա�\n");
            printf("3. �������Ա�\n");
            printf("4. ��������ĳ�����Ա�\n");
            scanf("%d", &multiChoice);
            char listName[30];
            printf("���������Ա�����\n");
            scanf("%s", listName);
            if (multiChoice == 1) {
                if (AddList(&Lists, listName) == OK)
                    printf("���ӳɹ���\n");
                else
                    printf("����ʧ�ܣ������������ڴ�����ʧ��\n");
            }
            else if (multiChoice == 2) {
                if (RemoveList(&Lists, listName) == OK)
                    printf("ɾ���ɹ���\n");
                else
                    printf("ɾ��ʧ�ܣ�δ�ҵ������Ա�\n");
            }
            else if (multiChoice == 3) {
                int posFound = LocateList(Lists, listName);
                if (posFound == 0)
                    printf("���Ա�����\n");
                else
                    printf("���Ա���ڣ�λ��Ϊ��%d\n", posFound);
            }
            else if (multiChoice == 4) {
                int posFound = LocateList(Lists, listName);
                if (posFound == 0) {
                    printf("���Ա�����\n");
                    break;
                }
                int listIndex = posFound - 1;
                printf("�ҵ����Ա� \"%s\" ����������Ӳ˵�...\n", listName);
                int op = 0;
                do {
                    printf("\n-----�������Ա� \"%s\" -----\n", listName);
                    printf("0. �������˵�\n");
                    printf("1. �������Ա�\n");
                    printf("2. �������Ա�\n");
                    printf("3. ������Ա�\n");
                    printf("4. ���Ա��п�\n");
                    printf("5. ���Ա���\n");
                    printf("6. ��ȡָ��λ��Ԫ��\n");
                    printf("7. ����ָ��Ԫ�ص�λ��\n");
                    printf("8. ��ȡָ��Ԫ�ص�ǰ��\n");
                    printf("9. ��ȡָ��Ԫ�صĺ��\n");
                    printf("10. ����Ԫ����ָ��λ��\n");
                    printf("11. ɾ��ָ��λ��Ԫ��\n");
                    printf("12. �������Ա�\n");
                    printf("13. ���ӹ���1������������������\n");
                    printf("14. ���ӹ���2�����Ϊk�����������\n");
                    printf("15. ���ӹ���3����С��������\n");
                    printf("16. ���ӹ���4���������Ա��ļ�\n");
                    printf("����������ѡ��\n");
                    scanf("%d", &op);
                    int posInput, opElem;
                    switch (op) {
                    case 0:
                        printf("�˳���ǰ�����Ӳ˵�\n");
                        break;
                    case 1:
                        if (InitList(&Lists.elem[listIndex].L) == OK)
                            printf("�����ɹ���������¼��\n");
                        else
                            printf("˳����Ѵ��ڻ򴴽�ʧ��\n");
                        break;
                    case 2:
                        if (DestroyList(&Lists.elem[listIndex].L) == OK)
                            printf("���ٳɹ�\n");
                        else
                            printf("˳������ڣ�����ʧ��\n");
                        break;
                    case 3:
                        if (ClearList(&Lists.elem[listIndex].L) == OK)
                            printf("��ճɹ�\n");
                        else
                            printf("���ʧ�ܣ�˳�������\n");
                        break;
                    case 4: {
                        int emptyRes = ListEmpty(Lists.elem[listIndex].L);
                        if (emptyRes == INFEASIBLE)
                            printf("˳�������\n");
                        else if (emptyRes == TRUE)
                            printf("˳���Ϊ��\n");
                        else
                            printf("˳���Ϊ��\n");
                    }
                          break;
                    case 5:
                    {
                        int length = ListLength(Lists.elem[listIndex].L);
                        if (length == -1) printf("˳������ڣ�\n");
                        else
                            printf("˳�����Ϊ��%d\n", length);
                        break;
                    }
                    case 6:
                        printf("������Ҫ��ȡԪ�ص�λ�ã�\n");
                        scanf("%d", &posInput);
                        switch (GetElem(Lists.elem[listIndex].L, posInput, &opElem)) {
                        case OK:
                            printf("��%d��Ԫ��Ϊ��%d\n", posInput, opElem);
                            break;
                        case ERROR:
                            printf("λ�ò��Ϸ�\n");
                            break;
                        case INFEASIBLE:
                            printf("˳�������\n");
                            break;
                        }
                        break;
                    case 7:
                        printf("������Ҫ���ҵ�Ԫ�أ�\n");
                        scanf("%d", &opElem);
                        pos = LocateElem(Lists.elem[listIndex].L, opElem);
                        if (pos == -1)
                            printf("˳�������\n");
                        else if (pos == 0)
                            printf("�Ҳ�����Ԫ��\n");
                        else
                            printf("��Ԫ��λ�ڵ�%d��λ��\n", pos);
                        break;
                    case 8:
                        printf("���������ǰ����Ŀ��Ԫ�أ�\n");
                        scanf("%d", &opElem);
                        switch (PriorElem(Lists.elem[listIndex].L, opElem, &pre)) {
                        case INFEASIBLE:
                            printf("˳�������\n");
                            break;
                        case ERROR:
                            printf("��Ԫ��û��ǰ��\n");
                            break;
                        case OK:
                            printf("��Ԫ�ص�ǰ��Ϊ��%d\n", pre);
                            break;
                        }
                        break;
                    case 9:
                        printf("��������Һ�̵�Ŀ��Ԫ�أ�\n");
                        scanf("%d", &opElem);
                        switch (NextElem(Lists.elem[listIndex].L, opElem, &next)) {
                        case INFEASIBLE:
                            printf("˳�������\n");
                            break;
                        case ERROR:
                            printf("��Ԫ��û�к��\n");
                            break;
                        case OK:
                            printf("��Ԫ�صĺ��Ϊ��%d\n", next);
                            break;
                        }
                        break;
                    case 10:
                        printf("����������λ�ú�Ԫ�أ�\n");
                        scanf("%d %d", &posInput, &opElem);
                        switch (ListInsert(&Lists.elem[listIndex].L, posInput, opElem)) {
                        case INFEASIBLE:
                            printf("˳�������\n");
                            break;
                        case ERROR:
                            printf("����λ�ò��Ϸ�\n");
                            break;
                        case OK:
                            printf("����ɹ�\n");
                            break;
                        }
                        break;
                    case 11:
                        printf("������ɾ��Ԫ�ص�λ�ã�\n");
                        scanf("%d", &posInput);
                        switch (ListDelete(&Lists.elem[listIndex].L, posInput, &opElem)) {
                        case INFEASIBLE:
                            printf("˳�������\n");
                            break;
                        case ERROR:
                            printf("ɾ��λ�ô������Ԫ��\n");
                            break;
                        case OK:
                            printf("ɾ���ɹ�����ɾԪ��Ϊ��%d\n", opElem);
                            break;
                        }
                        break;
                    case 12:
                        ListTraverse(Lists.elem[listIndex].L);
                        printf("\n");
                        break;
                    case 13:
                        printf("�������������ĺ�Ϊ��%d\n", MaxSubArray(Lists.elem[listIndex].L));
                        break;
                    case 14:
                        printf("������Ŀ��ֵk��\n");
                        scanf("%d", &k);
                        printf("�������������������Ϊ��%d\n", SubArrayNum(Lists.elem[listIndex].L, k));
                        break;
                    case 15:
                        SortList(&Lists.elem[listIndex].L);
                        printf("�������\n");
                        break;
                    case 16:
                        printf("�����뱣���ļ�����\n");
                        scanf("%s", filename);
                        res = saveListToFile(Lists.elem[listIndex].L, filename);
                        if (res == OK)
                            printf("����ɹ�\n");
                        else
                            printf("����ʧ��\n");
                        break;
                    default:
                        printf("�������������ѡ��\n");
                        break;
                    }
                } while (op != 0);
            }
            break;
        }
        case 18:
            printf("����������ļ����ļ�����\n");
            scanf("%s", filename);
            res = loadListFromFile(&L, filename);
            printf("\n");
            if (res == OK)
                printf("���سɹ�\n");
            else
                printf("����ʧ��\n");
            break;
        default:
            printf("����ѡ�����������ѡ��\n");
            break;
        }
    }
    return 0;
}