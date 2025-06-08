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

/* 特殊数据元素类型定义 */
typedef int status;
typedef int ElemType;

/* 顺序表（顺序结构）的定义 */
typedef struct {
    ElemType* elem;
    int length;
    int listsize;
} SqList;

/* 多线性表管理的定义 */
typedef struct {
    struct {
        char name[30];
        SqList L;
    } elem[10];
    int length;
} LISTS;

LISTS Lists;  // 多线性表全局管理变量

SqList L;
int choice;         // 主菜单选择
int pre, next;      // 存储前驱、后继
ElemType e, k;      // 用于存储数据

/* 函数1：创建顺序表 */
status InitList(SqList* L) {
    if (L->elem == NULL) {  // 不存在则创建
        L->elem = (ElemType*)malloc(sizeof(ElemType) * LIST_INIT_SIZE);
        if (!L->elem)
            return ERROR;
        L->length = 0;
        L->listsize = LIST_INIT_SIZE;
        printf("成功创建，输入1写入数据，输入0跳过数据录入：\n");
        int numIn;
        scanf("%d", &numIn);
        if (numIn == 1) {
            int count;
            printf("请输入写入元素的个数（不超过%d）：\n", LIST_INIT_SIZE);
            scanf("%d", &count);
            if (count > LIST_INIT_SIZE) {
                ElemType* newbase = (ElemType*)realloc(L->elem, count * sizeof(ElemType));
                if (!newbase) {
                    printf("重新分配空间失败\n");
                    return ERROR;
                }
                L->elem = newbase;
                L->listsize = count;
            }
            L->length = count;
            printf("请写入%d个数据：\n", count);
            for (int i = 0; i < count; i++) {
                scanf("%d", &L->elem[i]);
            }
        }
        return OK;
    }
    return INFEASIBLE;
}

/* 函数2：销毁顺序表 */
status DestroyList(SqList* L) {
    if (L->elem == NULL)
        return INFEASIBLE;
    free(L->elem);
    L->elem = NULL;
    L->length = 0;
    L->listsize = 0;
    return OK;
}

/* 函数3：清空顺序表 */
status ClearList(SqList* L) {
    if (L->elem == NULL)
        return INFEASIBLE;
    for (int i = 0; i < L->length; i++)
        L->elem[i] = 0;
    L->length = 0;
    return OK;
}

/* 函数4：判断线性表是否为空 */
status ListEmpty(SqList L) {
    if (L.elem == NULL)
        return INFEASIBLE;
    return (L.length == 0) ? TRUE : FALSE;
}

/* 函数5：返回线性表长度 */
status ListLength(SqList L) {
    if (L.elem == NULL)
        return INFEASIBLE;
    return L.length;
}

/* 函数6：获取第i个元素 */
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

/* 函数7：查找指定元素（返回1-based位置） */
int LocateElem(SqList L, ElemType e) {
    if (L.elem == NULL)
        return -1;
    for (int i = 0; i < L.length; i++) {
        if (L.elem[i] == e)
            return i + 1;
    }
    return 0;
}

/* 函数8：获取指定元素的前驱 */
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

/* 函数9：获取指定元素的后继 */
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

/* 函数10：在指定位置插入元素 */
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

/* 函数11：删除指定位置元素 */
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

/* 函数12：遍历顺序表 */
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

/* 函数13：求最大连续子数组和 */
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

/* 函数14：求和为k的子数组个数（暴力法） */
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

/* 函数15：从小到大排序（冒泡排序） */
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

/* 函数16：以二进制方式保存线性表到文件 */
status SaveInFile(SqList L, char* filename) {
    FILE* fp = fopen(filename, "wb");
    if (fp == NULL) {
        perror("文件打开失败");
        return ERROR;
    }
    fwrite(&L.length, sizeof(int), 1, fp);
    for (int i = 0; i < L.length; i++)
        fwrite(&L.elem[i], sizeof(int), 1, fp);
    fclose(fp);
    return OK;
}

/* 使用文本方式保存线性表到文件 */
status saveListToFile(SqList L, char* filename) {
    FILE* fp = fopen(filename, "w");
    if (fp == NULL)
        return INFEASIBLE;
    for (int i = 0; i < L.length; i++)
        fprintf(fp, "%d ", L.elem[i]);
    fclose(fp);
    return OK;
}

/* 函数：从文件加载线性表（以文本方式读取） */
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

/* 多线性表管理函数 */
/* 增加一个线性表：将一个名称为ListName的空顺序表加入Lists */
status AddList(LISTS* Lists, char ListName[]) {
    if (Lists->length >= 10)
        return ERROR;  // 超出容量限制
    strcpy(Lists->elem[Lists->length].name, ListName);
    Lists->elem[Lists->length].L.elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (Lists->elem[Lists->length].L.elem == NULL)
        return ERROR;
    Lists->elem[Lists->length].L.length = 0;
    Lists->elem[Lists->length].L.listsize = LIST_INIT_SIZE;
    Lists->length++;
    return OK;
}

/* 删除一个线性表 */
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

/* 查找线性表，成功返回1-based位置，失败返回0 */
int LocateList(LISTS Lists, char ListName[]) {
    for (int i = 0; i < Lists.length; i++) {
        if (strcmp(Lists.elem[i].name, ListName) == 0)
            return i + 1;
    }
    return 0;
}

/* 主函数 */
int main() {
    /* 初始化全局变量 */
    L.elem = NULL;
    L.length = 0;
    L.listsize = 0;
    Lists.length = 0;

    while (1) {
        printf("\n-----顺序表演示系统-----\n");
        printf("0. 退出演示系统\n");
        printf("1. 创建单个顺序表\n");
        printf("2. 销毁单个顺序表\n");
        printf("3. 清空单个顺序表\n");
        printf("4. 判断单个顺序表是否为空\n");
        printf("5. 输出单个顺序表长度\n");
        printf("6. 获取单个顺序表指定位置元素\n");
        printf("7. 查找元素在单个顺序表中的位置\n");
        printf("8. 获取单个顺序表指定元素的前驱\n");
        printf("9. 获取单个顺序表指定元素的后继\n");
        printf("10. 在单个顺序表中指定位置插入元素\n");
        printf("11. 删除单个顺序表指定位置元素\n");
        printf("12. 遍历单个顺序表\n");
        printf("13. 附加功能1：求最大连续子数组和\n");
        printf("14. 附加功能2：求和为k的子数组个数\n");
        printf("15. 附加功能3：从小到大排序\n");
        printf("16. 附加功能4：保存单个顺序表到文件\n");
        printf("17. 附加功能5：多线性表管理\n");
        printf("18. 附加功能6：从文件读取单个顺序表\n");
        printf("请输入您的选择：");
        scanf("%d", &choice);

        int res, pos, tempPos, element;
        char filename[30];

        switch (choice) {
        case 0:
            printf("您已结束使用\n");
            return 0;
        case 1:
            if (InitList(&L) == OK)
                printf("创建顺序表成功，数据已录入\n");
            else
                printf("顺序表创建失败或已存在\n");
            break;
        case 2:
            if (DestroyList(&L) == OK)
                printf("销毁顺序表成功\n");
            else
                printf("顺序表不存在，销毁失败\n");
            break;
        case 3:
            if (ClearList(&L) == OK)
                printf("清空顺序表成功\n");
            else
                printf("顺序表不存在，无法清空\n");
            break;
        case 4: {
            int emptyResult = ListEmpty(L);
            if (emptyResult == INFEASIBLE)
                printf("顺序表不存在\n");
            else if (emptyResult == TRUE)
                printf("顺序表为空\n");
            else
                printf("顺序表不为空\n");
            break;
        }
        case 5:
        {
            int length = ListLength(L);
            if (length == -1) printf("顺序表不存在！\n");
            else
                printf("顺序表长度为：%d\n", length);
            break;
        }
        case 6:
            printf("请输入要获取元素的位置：\n");
            scanf("%d", &tempPos);
            switch (GetElem(L, tempPos, &element)) {
            case OK:
                printf("第%d个元素为：%d\n", tempPos, element);
                break;
            case ERROR:
                printf("位置不合法\n");
                break;
            case INFEASIBLE:
                printf("顺序表不存在\n");
                break;
            }
            break;
        case 7:
            printf("请输入要查找的元素：\n");
            scanf("%d", &element);
            pos = LocateElem(L, element);
            if (pos == -1)
                printf("顺序表不存在\n");
            else if (pos == 0)
                printf("找不到该元素\n");
            else
                printf("该元素位于第%d个位置\n", pos);
            break;
        case 8:
            printf("请输入查找前驱的目标元素：\n");
            scanf("%d", &element);
            switch (PriorElem(L, element, &pre)) {
            case INFEASIBLE:
                printf("顺序表不存在\n");
                break;
            case ERROR:
                printf("该元素没有前驱\n");
                break;
            case OK:
                printf("该元素的前驱为：%d\n", pre);
                break;
            }
            break;
        case 9:
            printf("请输入查找后继的目标元素：\n");
            scanf("%d", &element);
            switch (NextElem(L, element, &next)) {
            case INFEASIBLE:
                printf("顺序表不存在\n");
                break;
            case ERROR:
                printf("该元素没有后继\n");
                break;
            case OK:
                printf("该元素的后继为：%d\n", next);
                break;
            }
            break;
        case 10:
            printf("请输入插入的位置和元素：\n");
            scanf("%d %d", &tempPos, &element);
            switch (ListInsert(&L, tempPos, element)) {
            case INFEASIBLE:
                printf("顺序表不存在\n");
                break;
            case ERROR:
                printf("插入位置不合法\n");
                break;
            case OK:
                printf("插入成功\n");
                break;
            }
            break;
        case 11:
            printf("请输入删除元素的位置：\n");
            scanf("%d", &tempPos);
            switch (ListDelete(&L, tempPos, &element)) {
            case INFEASIBLE:
                printf("顺序表不存在\n");
                break;
            case ERROR:
                printf("删除位置错误或无元素\n");
                break;
            case OK:
                printf("删除成功，被删元素为：%d\n", element);
                break;
            }
            break;
        case 12:
            ListTraverse(L);
            printf("\n");
            break;
        case 13:
            printf("最大连续子数组的和为：%d\n", MaxSubArray(L));
            break;
        case 14:
            printf("请输入目标值k：\n");
            scanf("%d", &k);
            printf("满足条件的子数组个数为：%d\n", SubArrayNum(L, k));
            break;
        case 15:
            SortList(&L);
            printf("排序完成\n");
            break;
        case 16:
            printf("请输入保存文件名：\n");
            scanf("%s", filename);
            res = SaveInFile(L, filename);
            if (res == OK)
                printf("保存成功\n");
            else
                printf("保存失败\n");
            break;
        case 17: {
            /* 多线性表管理子菜单 */
            int multiChoice;
            printf("请选择操作：\n");
            printf("1. 增加一个新线性表\n");
            printf("2. 删除一个线性表\n");
            printf("3. 查找线性表\n");
            printf("4. 操作其中某个线性表\n");
            scanf("%d", &multiChoice);
            char listName[30];
            printf("请输入线性表名：\n");
            scanf("%s", listName);
            if (multiChoice == 1) {
                if (AddList(&Lists, listName) == OK)
                    printf("增加成功！\n");
                else
                    printf("增加失败，可能已满或内存申请失败\n");
            }
            else if (multiChoice == 2) {
                if (RemoveList(&Lists, listName) == OK)
                    printf("删除成功！\n");
                else
                    printf("删除失败，未找到该线性表\n");
            }
            else if (multiChoice == 3) {
                int posFound = LocateList(Lists, listName);
                if (posFound == 0)
                    printf("线性表不存在\n");
                else
                    printf("线性表存在，位置为：%d\n", posFound);
            }
            else if (multiChoice == 4) {
                int posFound = LocateList(Lists, listName);
                if (posFound == 0) {
                    printf("线性表不存在\n");
                    break;
                }
                int listIndex = posFound - 1;
                printf("找到线性表 \"%s\" ，进入操作子菜单...\n", listName);
                int op = 0;
                do {
                    printf("\n-----操作线性表 \"%s\" -----\n", listName);
                    printf("0. 返回主菜单\n");
                    printf("1. 创建线性表\n");
                    printf("2. 销毁线性表\n");
                    printf("3. 清空线性表\n");
                    printf("4. 线性表判空\n");
                    printf("5. 线性表长度\n");
                    printf("6. 获取指定位置元素\n");
                    printf("7. 查找指定元素的位置\n");
                    printf("8. 获取指定元素的前驱\n");
                    printf("9. 获取指定元素的后继\n");
                    printf("10. 插入元素至指定位置\n");
                    printf("11. 删除指定位置元素\n");
                    printf("12. 遍历线性表\n");
                    printf("13. 附加功能1：求最大连续子数组和\n");
                    printf("14. 附加功能2：求和为k的子数组个数\n");
                    printf("15. 附加功能3：从小到大排序\n");
                    printf("16. 附加功能4：保存线性表到文件\n");
                    printf("请输入您的选择：\n");
                    scanf("%d", &op);
                    int posInput, opElem;
                    switch (op) {
                    case 0:
                        printf("退出当前操作子菜单\n");
                        break;
                    case 1:
                        if (InitList(&Lists.elem[listIndex].L) == OK)
                            printf("创建成功，数据已录入\n");
                        else
                            printf("顺序表已存在或创建失败\n");
                        break;
                    case 2:
                        if (DestroyList(&Lists.elem[listIndex].L) == OK)
                            printf("销毁成功\n");
                        else
                            printf("顺序表不存在，销毁失败\n");
                        break;
                    case 3:
                        if (ClearList(&Lists.elem[listIndex].L) == OK)
                            printf("清空成功\n");
                        else
                            printf("清空失败，顺序表不存在\n");
                        break;
                    case 4: {
                        int emptyRes = ListEmpty(Lists.elem[listIndex].L);
                        if (emptyRes == INFEASIBLE)
                            printf("顺序表不存在\n");
                        else if (emptyRes == TRUE)
                            printf("顺序表为空\n");
                        else
                            printf("顺序表不为空\n");
                    }
                          break;
                    case 5:
                    {
                        int length = ListLength(Lists.elem[listIndex].L);
                        if (length == -1) printf("顺序表不存在！\n");
                        else
                            printf("顺序表长度为：%d\n", length);
                        break;
                    }
                    case 6:
                        printf("请输入要获取元素的位置：\n");
                        scanf("%d", &posInput);
                        switch (GetElem(Lists.elem[listIndex].L, posInput, &opElem)) {
                        case OK:
                            printf("第%d个元素为：%d\n", posInput, opElem);
                            break;
                        case ERROR:
                            printf("位置不合法\n");
                            break;
                        case INFEASIBLE:
                            printf("顺序表不存在\n");
                            break;
                        }
                        break;
                    case 7:
                        printf("请输入要查找的元素：\n");
                        scanf("%d", &opElem);
                        pos = LocateElem(Lists.elem[listIndex].L, opElem);
                        if (pos == -1)
                            printf("顺序表不存在\n");
                        else if (pos == 0)
                            printf("找不到该元素\n");
                        else
                            printf("该元素位于第%d个位置\n", pos);
                        break;
                    case 8:
                        printf("请输入查找前驱的目标元素：\n");
                        scanf("%d", &opElem);
                        switch (PriorElem(Lists.elem[listIndex].L, opElem, &pre)) {
                        case INFEASIBLE:
                            printf("顺序表不存在\n");
                            break;
                        case ERROR:
                            printf("该元素没有前驱\n");
                            break;
                        case OK:
                            printf("该元素的前驱为：%d\n", pre);
                            break;
                        }
                        break;
                    case 9:
                        printf("请输入查找后继的目标元素：\n");
                        scanf("%d", &opElem);
                        switch (NextElem(Lists.elem[listIndex].L, opElem, &next)) {
                        case INFEASIBLE:
                            printf("顺序表不存在\n");
                            break;
                        case ERROR:
                            printf("该元素没有后继\n");
                            break;
                        case OK:
                            printf("该元素的后继为：%d\n", next);
                            break;
                        }
                        break;
                    case 10:
                        printf("请输入插入的位置和元素：\n");
                        scanf("%d %d", &posInput, &opElem);
                        switch (ListInsert(&Lists.elem[listIndex].L, posInput, opElem)) {
                        case INFEASIBLE:
                            printf("顺序表不存在\n");
                            break;
                        case ERROR:
                            printf("插入位置不合法\n");
                            break;
                        case OK:
                            printf("插入成功\n");
                            break;
                        }
                        break;
                    case 11:
                        printf("请输入删除元素的位置：\n");
                        scanf("%d", &posInput);
                        switch (ListDelete(&Lists.elem[listIndex].L, posInput, &opElem)) {
                        case INFEASIBLE:
                            printf("顺序表不存在\n");
                            break;
                        case ERROR:
                            printf("删除位置错误或无元素\n");
                            break;
                        case OK:
                            printf("删除成功，被删元素为：%d\n", opElem);
                            break;
                        }
                        break;
                    case 12:
                        ListTraverse(Lists.elem[listIndex].L);
                        printf("\n");
                        break;
                    case 13:
                        printf("最大连续子数组的和为：%d\n", MaxSubArray(Lists.elem[listIndex].L));
                        break;
                    case 14:
                        printf("请输入目标值k：\n");
                        scanf("%d", &k);
                        printf("满足条件的子数组个数为：%d\n", SubArrayNum(Lists.elem[listIndex].L, k));
                        break;
                    case 15:
                        SortList(&Lists.elem[listIndex].L);
                        printf("排序完成\n");
                        break;
                    case 16:
                        printf("请输入保存文件名：\n");
                        scanf("%s", filename);
                        res = saveListToFile(Lists.elem[listIndex].L, filename);
                        if (res == OK)
                            printf("保存成功\n");
                        else
                            printf("保存失败\n");
                        break;
                    default:
                        printf("输入错误，请重新选择\n");
                        break;
                    }
                } while (op != 0);
            }
            break;
        }
        case 18:
            printf("请输入加载文件的文件名：\n");
            scanf("%s", filename);
            res = loadListFromFile(&L, filename);
            printf("\n");
            if (res == OK)
                printf("加载成功\n");
            else
                printf("加载失败\n");
            break;
        default:
            printf("输入选项错误，请重新选择\n");
            break;
        }
    }
    return 0;
}