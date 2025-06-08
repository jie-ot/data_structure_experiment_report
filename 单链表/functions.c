#define _CRT_SECURE_NO_WARNINGS

#include"functions.h"

//规定所有函数处理都是带头结点的链表

status InitList(LinkList* L)
{
    if (*L != NULL) return INFEASIBLE;  // 已经初始化过
    *L = (LinkList)malloc(sizeof(LNode));
    if (*L == NULL) {
        return OVERFLOW;
    }
    (*L)->next = NULL;

    // 询问是否进行数据初始化
    int choice;
    printf("是否在初始化时输入数据？(1-是，0-否): ");
    scanf("%d", &choice);
    if (choice == 1) {
        int n, data;
        printf("请输入要初始化的元素个数: ");
        scanf("%d", &n);
        LinkList tail = *L;
        for (int i = 0; i < n; i++) {
            LinkList newNode = (LinkList)malloc(sizeof(LNode));
            if (newNode == NULL) return OVERFLOW;
            printf("请输入第 %d 个元素的值: ", i + 1);
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
/*完全销毁线性表，不仅要释放线性表中所有数据元素节点的内存，还要释放头节点的内存，
最终让线性表回到未初始化的状态，也就是让指向线性表的指针变为 NULL*/
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
/*清空线性表中的数据元素，也就是释放除头节点以外的所有数据元素节点的内存，
但会保留头节点，使得线性表仍然处于已初始化的状态，只是其中没有数据元素。*/
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
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
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
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
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
// 如果线性表L存在，查找元素e在线性表L中的位置序号；如果e不存在，返回ERROR；当线性表L不存在时，返回INFEASIBLE。
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
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if (L == NULL) return INFEASIBLE;
    if (L->next == NULL) return INFEASIBLE;
    if (L->next->data == e) return ERROR; // 如果第一个元素就是目标e，则e没有前驱
    
    // 定义两个指针：prev指向前驱，curr指向当前节点
    LinkList prev = L->next;      // 第一个有效节点
    LinkList curr = prev->next;     // 从第二个有效节点开始

    while (curr != NULL) {
        // 如果找到了目标元素，prev就是它的前驱
        if (curr->data == e) {
            *pre = prev->data;
            return OK;
        }
        prev = curr;
        curr = curr->next;
    }
    return ERROR; // 遍历完链表仍未找到元素e
}
status NextElem(LinkList L, ElemType e, ElemType* next)
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
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
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
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
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
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
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
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
//附加功能1：链表翻转，若链表不存在或为空则返回INFEASIBLE
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
//附加功能 2：删除链表的倒数第 n 个结点（双指针法，使用虚拟头结点）
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
//附加功能3：链表排序（暴力法）
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
// 附加功能4：以二进制方式将链表保存到文件
{
    if (L == NULL) return INFEASIBLE;
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("无法打开文件进行保存！\n");
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
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
    // 如果链表已存在，则返回 INFEASIBLE
    if (*L != NULL) return INFEASIBLE;

    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("无法打开文件进行加载！\n");
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
            // 出现读取错误，先释放已分配的结点
            LinkList temp;
            while (head != NULL) {
                temp = head;
                head = head->next;
                free(temp);
            }
            fclose(fp);
            return ERROR;
        }

        // 分配新结点
        LinkList newNode = (LinkList)malloc(sizeof(LNode));
        if (newNode == NULL) {
            // 内存分配失败，释放所有已分配的结点
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

/* ==================== 多线性表管理（附加功能5） ==================== */

/* 初始化多链表管理器 */
void InitMultiList(MultiList* ml) 
{
    ml->count = 0;
    ml->current = -1;
    for (int i = 0; i < MAX_LISTS; i++) {
        ml->lists[i] = NULL;
    }
}

/* 创建新的单链表并加入管理器 */
status CreateNewList(MultiList* ml) 
{
    if (ml->count >= MAX_LISTS) {
        printf("已达到管理的最大链表个数！\n");
        return ERROR;
    }
    LinkList p = NULL;
    if (InitList(&p) != OK)
        return ERROR;
    ml->lists[ml->count] = p;
    ml->current = ml->count;  // 新创建的链表自动成为活动链表
    ml->count++;
    //printf("创建新链表成功！当前活动链表序号：%d\n", ml->current);
    return OK;
}

/* 删除管理器中指定索引的单链表 */
status RemoveList(MultiList* ml, char listNames[][30], const char* targetName)
{
    int index = -1;
    // 在名称数组中查找目标链表名称对应的索引
    for (int i = 0; i < ml->count; i++) {
        if (strcmp(listNames[i], targetName) == 0) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("链表不存在！\n");
        return ERROR;
    }
    // 销毁链表
    if (DestroyList(&ml->lists[index]) != OK) {
        printf("销毁链表失败！\n");
        return ERROR;
    }
    // 将后面的链表指针和名称整体前移
    for (int i = index; i < ml->count - 1; i++) {
        ml->lists[i] = ml->lists[i + 1];
        strcpy(listNames[i], listNames[i + 1]);
    }
    ml->lists[ml->count - 1] = NULL;
    listNames[ml->count - 1][0] = '\0';  // 清空最后一个名称
    ml->count--;
    if (ml->count == 0)
        ml->current = -1;
    else if (ml->current >= ml->count)
        ml->current = ml->count - 1;
    printf("链表 \"%s\" 删除成功！\n", targetName);
    return OK;
}

/* 切换当前活动链表 */
status SwitchCurrentList(MultiList* ml, int index) 
{
    if (index < 0 || index >= ml->count) {
        printf("不存在该序号的链表！\n");
        return ERROR;
    }
    ml->current = index;
    printf("当前活动链表切换到序号：%d\n", ml->current);
    return OK;
}

/* 显示管理器中所有链表的情况（显示序号及各链表长度），当前链表做标记 */
void ListAllLists(MultiList* ml) 
{
    if (ml->count == 0) {
        printf("当前没有管理任何链表！\n");
        return;
    }
    printf("多链表管理信息：\n");
    for (int i = 0; i < ml->count; i++) {
        int len = ListLength(ml->lists[i]);
        printf("序号 %d: 链表长度 = %d", i, len);
        if (i == ml->current)
            printf("  [当前活动链表]");
        printf("\n");
    }
}

void PrintMenu()
{
    printf("\n  -------单链表演示系统-------  \n");
    printf("**************************************\n");
    printf("  0.退出演示系统\n");
    printf("  1.初始化单个单链表\n");
    printf("  2.销毁当前单链表\n");
    printf("  3.清空当前链表\n");
    printf("  4.判断当前链表是否为空\n");
    printf("  5.获取当前链表长度\n");
    printf("  6.获得当前链表第i个元素\n");
    printf("  7.查找元素e的位置\n");
    printf("  8.获得元素e的前驱\n");
    printf("  9.获得元素e的后继\n");
    printf(" 10.在当前链表中插入元素\n");
    printf(" 11.删除当前链表中的元素\n");
    printf(" 12.遍历当前链表\n");
    printf(" 13.附加功能1：翻转当前链表\n");
    printf(" 14.附加功能2：删除当前链表的倒数第 n 个结点\n");
    printf(" 15.附加功能3：对当前链表从小到大排序\n");
    printf(" 16.附加功能4：保存当前链表到文件\n");
    printf(" 17.附加功能5：从文件加载当前链表\n");
    printf(" 18.附加功能6：多线性表管理\n");
    printf("**************************************\n");
    printf("请输入你的选择: ");
}

void PrintSubMenu()
{
    printf("\n--- 多链表管理子系统 ---\n");
    printf("  1.创建新的单链表\n");
    printf("  2.删除某个单链表\n");
    printf("  3.显示所有单链表状态\n");
    printf("  4.操作其中某个单链表\n");
    printf("  0.返回主菜单\n");
    printf("请输入你的选择: ");
}

void PrintSubSubMenu(char* listname)
{
    printf("\n-----操作单链表 \"%s\" -----\n", listname);
    printf("  0.返回子菜单\n");
    printf("  1.销毁单链表\n");
    printf("  2.清空单链表\n");
    printf("  3.单链表判空\n");
    printf("  4.获取线性表长度\n");
    printf("  5.获取指定位置元素\n");
    printf("  6.查找指定元素的位置\n");
    printf("  7.获取指定元素的前驱\n");
    printf("  8.获取指定元素的后继\n");
    printf("  9.插入元素至指定位置\n");
    printf(" 10.删除指定位置元素\n");
    printf(" 11.遍历单链表\n");
    printf(" 12.附加功能1：翻转当前链表\n");
    printf(" 13.附加功能2：删除当前链表的倒数第 n 个结点\n");
    printf(" 14.附加功能3：对单链表从小到大排序\n");
    printf(" 15.附加功能4：保存单链表到文件\n");
    printf("请输入您的选择：\n");
}