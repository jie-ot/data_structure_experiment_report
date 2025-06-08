#define _CRT_SECURE_NO_WARNINGS

#include"functions.h"

//�涨���к��������Ǵ�ͷ��������

status InitList(LinkList* L)
{
    if (*L != NULL) return INFEASIBLE;  // �Ѿ���ʼ����
    *L = (LinkList)malloc(sizeof(LNode));
    if (*L == NULL) {
        return OVERFLOW;
    }
    (*L)->next = NULL;

    // ѯ���Ƿ�������ݳ�ʼ��
    int choice;
    printf("�Ƿ��ڳ�ʼ��ʱ�������ݣ�(1-�ǣ�0-��): ");
    scanf("%d", &choice);
    if (choice == 1) {
        int n, data;
        printf("������Ҫ��ʼ����Ԫ�ظ���: ");
        scanf("%d", &n);
        LinkList tail = *L;
        for (int i = 0; i < n; i++) {
            LinkList newNode = (LinkList)malloc(sizeof(LNode));
            if (newNode == NULL) return OVERFLOW;
            printf("������� %d ��Ԫ�ص�ֵ: ", i + 1);
            scanf("%d", &data);
            newNode->data = data;
            newNode->next = NULL;
            tail->next = newNode;
            tail = newNode;
        }
    }
    return OK;
}
status DestroyList(LinkList* L)
/*��ȫ�������Ա�����Ҫ�ͷ����Ա�����������Ԫ�ؽڵ���ڴ棬��Ҫ�ͷ�ͷ�ڵ���ڴ棬
���������Ա�ص�δ��ʼ����״̬��Ҳ������ָ�����Ա��ָ���Ϊ NULL*/
{
    if (*L == NULL) return INFEASIBLE;
    LinkList current = *L;
    LinkList temp;
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
    *L = NULL;
    return OK;
}
status ClearList(LinkList* L)
/*������Ա��е�����Ԫ�أ�Ҳ�����ͷų�ͷ�ڵ��������������Ԫ�ؽڵ���ڴ棬
���ᱣ��ͷ�ڵ㣬ʹ�����Ա���Ȼ�����ѳ�ʼ����״̬��ֻ������û������Ԫ�ء�*/
{
    if (*L == NULL) return INFEASIBLE;
    LinkList current = (*L)->next;
    LinkList temp;
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
    (*L)->next = NULL;
    return OK;
}
status ListEmpty(LinkList L)
{
    if(L==NULL) return INFEASIBLE;
    if(L->next == NULL) return TRUE;
    return FALSE;
}
int ListLength(LinkList L)
// ������Ա�L���ڣ��������Ա�L�ĳ��ȣ����򷵻�INFEASIBLE��
{
    if (L == NULL) return INFEASIBLE;
    int length = 0;
    LinkList temp = L->next;
    while (temp != NULL) {
        temp = temp->next;
        length++;
    }
    return length;
}
status GetElem(LinkList L, int i, ElemType* e)
// ������Ա�L���ڣ���ȡ���Ա�L�ĵ�i��Ԫ�أ�������e�У�����OK�����i���Ϸ�������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    if (L == NULL) return INFEASIBLE;
    if (i<1 || i>ListLength(L)) return ERROR;
    LinkList temp = L;
    for (int j = 1; j <= i; j++) {
        temp = temp->next;
    }
    *e = temp->data;
    return OK;
}
int LocateElem(LinkList L, ElemType e)
// ������Ա�L���ڣ�����Ԫ��e�����Ա�L�е�λ����ţ����e�����ڣ�����ERROR�������Ա�L������ʱ������INFEASIBLE��
{
    if (L == NULL) return INFEASIBLE;
    int position = 0, flag = 0;
    LinkList temp = L->next;
    while (temp != NULL) {
        position++;
        if (temp->data == e) {
            flag = 1;
            break;
        }
        temp = temp->next;
    }
    if (flag == 0) return ERROR;
    else return position;
}
status PriorElem(LinkList L, ElemType e, ElemType* pre)
// ������Ա�L���ڣ���ȡ���Ա�L��Ԫ��e��ǰ����������pre�У�����OK�����û��ǰ��������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    if (L == NULL) return INFEASIBLE;
    if (L->next == NULL) return INFEASIBLE;
    if (L->next->data == e) return ERROR; // �����һ��Ԫ�ؾ���Ŀ��e����eû��ǰ��
    
    // ��������ָ�룺prevָ��ǰ����currָ��ǰ�ڵ�
    LinkList prev = L->next;      // ��һ����Ч�ڵ�
    LinkList curr = prev->next;     // �ӵڶ�����Ч�ڵ㿪ʼ

    while (curr != NULL) {
        // ����ҵ���Ŀ��Ԫ�أ�prev��������ǰ��
        if (curr->data == e) {
            *pre = prev->data;
            return OK;
        }
        prev = curr;
        curr = curr->next;
    }
    return ERROR; // ������������δ�ҵ�Ԫ��e
}
status NextElem(LinkList L, ElemType e, ElemType* next)
// ������Ա�L���ڣ���ȡ���Ա�LԪ��e�ĺ�̣�������next�У�����OK�����û�к�̣�����ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    if (L == NULL) return INFEASIBLE;
    if (L->next == NULL) return INFEASIBLE;
    LinkList currnode = L->next;
    LinkList nextnode = currnode->next;

    while (nextnode != NULL) {
        if (currnode->data == e) {
            *next = nextnode->data;
            return OK;
        }
        currnode = nextnode;
        nextnode = nextnode->next;
    }
    return ERROR;
}
status ListInsert(LinkList* L, int i, ElemType e)
// ������Ա�L���ڣ���Ԫ��e���뵽���Ա�L�ĵ�i��Ԫ��֮ǰ������OK��������λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    if (L == NULL) return INFEASIBLE;
    LinkList head = *L;
    if (head == NULL) return INFEASIBLE;
    int length = 0;
    LinkList temp = head->next;
    while (temp != NULL) {
        temp = temp->next;
        length++;
    }
    if (i<1 || i>length + 1) return ERROR;
    LinkList current, p;
    current = head;
    p = (LinkList)malloc(sizeof(LinkList));
    p->data = e;
    for (int j = 1; j < i; j++) {
        current = current->next;
    }
    p->next = current->next;
    current->next = p;
    return OK;
}
status ListDelete(LinkList* L, int i, ElemType* e)
// ������Ա�L���ڣ�ɾ�����Ա�L�ĵ�i��Ԫ�أ���������e�У�����OK����ɾ��λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    if (L == NULL || *L == NULL) return INFEASIBLE;
    LinkList head = *L;
    int length = 0;
    LinkList temp = head->next;
    while (temp != NULL) {
        temp = temp->next;
        length++;
    }
    if (i<1 || i>length) return ERROR;

    LinkList current = head;
    for (int j = 1; j < i; j++) {
        current = current->next;
    }
    *e = current->next->data;
    LinkList p = current->next;
    current->next = current->next->next;
    free(p);
    return OK;
}
status ListTraverse(LinkList L)
// ������Ա�L���ڣ�������ʾ���Ա��е�Ԫ�أ�ÿ��Ԫ�ؼ��һ�񣬷���OK��������Ա�L�����ڣ�����INFEASIBLE��
{
    if (L == NULL) return INFEASIBLE;
    LinkList current = L->next;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
    return OK;
}
status reverseList(LinkList L)
//���ӹ���1������ת�����������ڻ�Ϊ���򷵻�INFEASIBLE
{
    if (L == NULL || L->next == NULL) return INFEASIBLE;
    LNode* prev = NULL;
    LNode* curr = L->next;
    while (curr) {
        LNode* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    L->next = prev;
    return OK;
}
status RemoveNthFromEnd(LinkList L, int n)
//���ӹ��� 2��ɾ������ĵ����� n ����㣨˫ָ�뷨��ʹ������ͷ��㣩
{
    if (L == NULL || L->next == NULL) return INFEASIBLE;
    LNode dummy;
    dummy.next = L->next;
    LNode* fast = &dummy;
    LNode* slow = &dummy;
    int i;
    for (i = 0; i <= n; i++) {
        if (fast == NULL)
            return ERROR;
        fast = fast->next;
    }
    while (fast) {
        fast = fast->next;
        slow = slow->next;
    }
    LNode* toDelete = slow->next;
    if (toDelete == NULL)
        return ERROR;
    slow->next = toDelete->next;
    free(toDelete);
    L->next = dummy.next;
    return OK;
}
status sortList(LinkList L)
//���ӹ���3���������򣨱�������
{
    if (L == NULL || L->next == NULL) return INFEASIBLE;
    for (LNode* p = L->next; p != NULL; p = p->next) {
        for (LNode* q = p->next; q != NULL; q = q->next) {
            if (p->data > q->data) {
                int temp = p->data;
                p->data = q->data;
                q->data = temp;
            }
        }
    }
    return OK;
}
status SaveList(LinkList L, char filename[])
// ���ӹ���4���Զ����Ʒ�ʽ�������浽�ļ�
{
    if (L == NULL) return INFEASIBLE;
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("�޷����ļ����б��棡\n");
        return ERROR;
    }
    int len = ListLength(L);
    fprintf(fp, "%d\n", len);
    LNode* p = L->next;
    while (p) {
        fprintf(fp, "%d ", p->data);
        p = p->next;
    }
    fclose(fp);
    return OK;
}
status LoadList(LinkList* L, char filename[])
// ������Ա�L�����ڣ���FileName�ļ��е����ݶ��뵽���Ա�L�У�����OK�����򷵻�INFEASIBLE��
{
    // ��������Ѵ��ڣ��򷵻� INFEASIBLE
    if (*L != NULL) return INFEASIBLE;

    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("�޷����ļ����м��أ�\n");
        return ERROR;
    }

    int count;
    if (fscanf(fp, "%d", &count) != 1) {
        fclose(fp);
        return ERROR;
    }

    LinkList head = (LinkList)malloc(sizeof(LNode));
    if (head == NULL) {
        fclose(fp);
        return OVERFLOW;
    }
    head->next = NULL;
    LinkList tail = head;

    for (int i = 0; i < count; i++) {
        int value;
        if (fscanf(fp, "%d", &value) != 1) {
            // ���ֶ�ȡ�������ͷ��ѷ���Ľ��
            LinkList temp;
            while (head != NULL) {
                temp = head;
                head = head->next;
                free(temp);
            }
            fclose(fp);
            return ERROR;
        }

        // �����½��
        LinkList newNode = (LinkList)malloc(sizeof(LNode));
        if (newNode == NULL) {
            // �ڴ����ʧ�ܣ��ͷ������ѷ���Ľ��
            LinkList temp;
            while (head != NULL) {
                temp = head;
                head = head->next;
                free(temp);
            }
            fclose(fp);
            return OVERFLOW;
        }

        newNode->data = value;
        newNode->next = NULL;

        tail->next = newNode;
        tail = newNode;
    }

    fclose(fp);
    *L = head;
    return OK;
}

/* ==================== �����Ա�������ӹ���5�� ==================== */

/* ��ʼ������������� */
void InitMultiList(MultiList* ml) 
{
    ml->count = 0;
    ml->current = -1;
    for (int i = 0; i < MAX_LISTS; i++) {
        ml->lists[i] = NULL;
    }
}

/* �����µĵ�������������� */
status CreateNewList(MultiList* ml) 
{
    if (ml->count >= MAX_LISTS) {
        printf("�Ѵﵽ�����������������\n");
        return ERROR;
    }
    LinkList p = NULL;
    if (InitList(&p) != OK)
        return ERROR;
    ml->lists[ml->count] = p;
    ml->current = ml->count;  // �´����������Զ���Ϊ�����
    ml->count++;
    //printf("����������ɹ�����ǰ�������ţ�%d\n", ml->current);
    return OK;
}

/* ɾ����������ָ�������ĵ����� */
status RemoveList(MultiList* ml, char listNames[][30], const char* targetName)
{
    int index = -1;
    // �����������в���Ŀ���������ƶ�Ӧ������
    for (int i = 0; i < ml->count; i++) {
        if (strcmp(listNames[i], targetName) == 0) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("�������ڣ�\n");
        return ERROR;
    }
    // ��������
    if (DestroyList(&ml->lists[index]) != OK) {
        printf("��������ʧ�ܣ�\n");
        return ERROR;
    }
    // �����������ָ�����������ǰ��
    for (int i = index; i < ml->count - 1; i++) {
        ml->lists[i] = ml->lists[i + 1];
        strcpy(listNames[i], listNames[i + 1]);
    }
    ml->lists[ml->count - 1] = NULL;
    listNames[ml->count - 1][0] = '\0';  // ������һ������
    ml->count--;
    if (ml->count == 0)
        ml->current = -1;
    else if (ml->current >= ml->count)
        ml->current = ml->count - 1;
    printf("���� \"%s\" ɾ���ɹ���\n", targetName);
    return OK;
}

/* �л���ǰ����� */
status SwitchCurrentList(MultiList* ml, int index) 
{
    if (index < 0 || index >= ml->count) {
        printf("�����ڸ���ŵ�����\n");
        return ERROR;
    }
    ml->current = index;
    printf("��ǰ������л�����ţ�%d\n", ml->current);
    return OK;
}

/* ��ʾ������������������������ʾ��ż��������ȣ�����ǰ��������� */
void ListAllLists(MultiList* ml) 
{
    if (ml->count == 0) {
        printf("��ǰû�й����κ�����\n");
        return;
    }
    printf("�����������Ϣ��\n");
    for (int i = 0; i < ml->count; i++) {
        int len = ListLength(ml->lists[i]);
        printf("��� %d: ������ = %d", i, len);
        if (i == ml->current)
            printf("  [��ǰ�����]");
        printf("\n");
    }
}

void PrintMenu()
{
    printf("\n  -------��������ʾϵͳ-------  \n");
    printf("**************************************\n");
    printf("  0.�˳���ʾϵͳ\n");
    printf("  1.��ʼ������������\n");
    printf("  2.���ٵ�ǰ������\n");
    printf("  3.��յ�ǰ����\n");
    printf("  4.�жϵ�ǰ�����Ƿ�Ϊ��\n");
    printf("  5.��ȡ��ǰ������\n");
    printf("  6.��õ�ǰ�����i��Ԫ��\n");
    printf("  7.����Ԫ��e��λ��\n");
    printf("  8.���Ԫ��e��ǰ��\n");
    printf("  9.���Ԫ��e�ĺ��\n");
    printf(" 10.�ڵ�ǰ�����в���Ԫ��\n");
    printf(" 11.ɾ����ǰ�����е�Ԫ��\n");
    printf(" 12.������ǰ����\n");
    printf(" 13.���ӹ���1����ת��ǰ����\n");
    printf(" 14.���ӹ���2��ɾ����ǰ����ĵ����� n �����\n");
    printf(" 15.���ӹ���3���Ե�ǰ�����С��������\n");
    printf(" 16.���ӹ���4�����浱ǰ�����ļ�\n");
    printf(" 17.���ӹ���5�����ļ����ص�ǰ����\n");
    printf(" 18.���ӹ���6�������Ա����\n");
    printf("**************************************\n");
    printf("���������ѡ��: ");
}

void PrintSubMenu()
{
    printf("\n--- �����������ϵͳ ---\n");
    printf("  1.�����µĵ�����\n");
    printf("  2.ɾ��ĳ��������\n");
    printf("  3.��ʾ���е�����״̬\n");
    printf("  4.��������ĳ��������\n");
    printf("  0.�������˵�\n");
    printf("���������ѡ��: ");
}

void PrintSubSubMenu(char* listname)
{
    printf("\n-----���������� \"%s\" -----\n", listname);
    printf("  0.�����Ӳ˵�\n");
    printf("  1.���ٵ�����\n");
    printf("  2.��յ�����\n");
    printf("  3.�������п�\n");
    printf("  4.��ȡ���Ա���\n");
    printf("  5.��ȡָ��λ��Ԫ��\n");
    printf("  6.����ָ��Ԫ�ص�λ��\n");
    printf("  7.��ȡָ��Ԫ�ص�ǰ��\n");
    printf("  8.��ȡָ��Ԫ�صĺ��\n");
    printf("  9.����Ԫ����ָ��λ��\n");
    printf(" 10.ɾ��ָ��λ��Ԫ��\n");
    printf(" 11.����������\n");
    printf(" 12.���ӹ���1����ת��ǰ����\n");
    printf(" 13.���ӹ���2��ɾ����ǰ����ĵ����� n �����\n");
    printf(" 14.���ӹ���3���Ե������С��������\n");
    printf(" 15.���ӹ���4�����浥�����ļ�\n");
    printf("����������ѡ��\n");
}