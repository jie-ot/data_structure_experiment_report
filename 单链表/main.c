#define _CRT_SECURE_NO_WARNINGS

#include"functions.h"

int main()
{
    system("color F0");
    LinkList singleL = NULL;  // 单链表操作用的变量
    MultiList ml;             // 多链表管理子系统
    InitMultiList(&ml);       // 初始化多链表管理器

    int choice;
    char listNames[MAX_LISTS][30] = { 0 };

    do {
        PrintMenu();

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');  // 清除输入缓冲区
            continue;
        }

        switch (choice)
        {
        case 0:
            printf("退出系统。\n");
            break;
        case 1: {  // 初始化单链表（带可选数据输入）
            if (singleL != NULL) {
                int confirm;
                printf("单链表已存在，重新初始化将销毁当前链表。是否继续？(1-是, 0-否): ");
                scanf("%d", &confirm);
                if (confirm == 1) {
                    if (DestroyList(&singleL) == OK)
                        printf("原有单链表已销毁。\n");
                    else
                        printf("销毁失败！\n");
                }
                else {
                    printf("操作取消。\n");
                    break;
                }
            }
            if (InitList(&singleL) == OK)
                printf("单链表初始化成功！\n");
            else
                printf("单链表初始化失败！\n");
            break;
        }
        case 2: {  // 销毁当前单链表
            if (singleL == NULL)
                printf("当前无单链表存在！\n");
            else {
                if (DestroyList(&singleL) == OK)
                    printf("单链表销毁成功！\n");
                else
                    printf("销毁失败！\n");
            }
            break;
        }
        case 3: {  // 清空当前单链表（保留头结点）
            if (singleL == NULL)
                printf("当前无单链表存在！\n");
            else {
                if (ClearList(&singleL) == OK)
                    printf("单链表已清空！\n");
                else
                    printf("清空失败！\n");
            }
            break;
        }
        case 4: {  // 判断是否为空
            if (singleL == NULL)
                printf("当前无单链表存在！\n");
            else {
                status ret = ListEmpty(singleL);
                if (ret == TRUE)
                    printf("单链表为空！\n");
                else if (ret == FALSE)
                    printf("单链表不为空！\n");
                else
                    printf("操作失败！\n");
            }
            break;
        }
        case 5: {  // 获取长度
            if (singleL == NULL)
                printf("当前无单链表存在！\n");
            else {
                int len = ListLength(singleL);
                if (len == INFEASIBLE)
                    printf("操作失败！\n");
                else
                    printf("单链表长度为：%d\n", len);
            }
            break;
        }
        case 6: {  // 获得第 i 个元素
            if (singleL == NULL) {
                printf("当前无单链表存在！\n");
            }
            else {
                int i;
                ElemType e;
                printf("请输入要获取的元素序号i: ");
                scanf("%d", &i);
                if (GetElem(singleL, i, &e) == OK)
                    printf("单链表第 %d 个元素的值为：%d\n", i, e);
                if(GetElem(singleL, i, &e) == INFEASIBLE)
                    printf("当前无单链表存在！\n");
                if (GetElem(singleL, i, &e) == ERROR)
                    printf("位置不合法！\n");
            }
            break;
        }
        case 7: {  // 查找元素 e 的位置
            if (singleL == NULL) {
                printf("当前无单链表存在！\n");
            }
            else {
                ElemType e;
                printf("请输入要查找的元素e: ");
                scanf("%d", &e);
                int pos = LocateElem(singleL, e);
                if (pos == INFEASIBLE)
                    printf("操作失败！\n");
                else if (pos == ERROR)
                    printf("未找到元素 %d！\n", e);
                else
                    printf("元素 %d 在单链表中的位置为：%d\n", e, pos);
            }
            break;
        }
        case 8: {  // 获得元素 e 的前驱
            if (singleL == NULL) {
                printf("当前无单链表存在！\n");
            }
            else {
                ElemType e, pre;
                printf("请输入要查询其前驱的元素e: ");
                scanf("%d", &e);
                if (PriorElem(singleL, e, &pre) == OK)
                    printf("元素 %d 的前驱为：%d\n", e, pre);
                if(PriorElem(singleL, e, &pre) == ERROR)
                    printf("没有找到该元素或该元素为第一个！\n");
                if (PriorElem(singleL, e, &pre) == INFEASIBLE)
                    printf("单链表不存在或单链表为空！\n");
            }
            break;
        }
        case 9: {  // 获得元素 e 的后继
            if (singleL == NULL) {
                printf("当前无单链表存在！\n");
            }
            else {
                ElemType e, next;
                printf("请输入要查询其后继的元素e: ");
                scanf("%d", &e);
                if (NextElem(singleL, e, &next) == OK)
                    printf("元素 %d 的后继为：%d\n", e, next);
                if (NextElem(singleL, e, &next) == ERROR)
                    printf("没有找到后继或该元素为最后一个！\n");
                if (NextElem(singleL, e, &next) == INFEASIBLE)
                    printf("单链表不存在或单链表为空！\n");
            }
            break;
        }
        case 10: { // 在单链表中插入元素
            if (singleL == NULL) {
                printf("当前无单链表存在，请先初始化！\n");
            }
            else {
                int pos;
                ElemType e;
                printf("请输入插入位置i: ");
                scanf("%d", &pos);
                printf("请输入要插入的元素e: ");
                scanf("%d", &e);
                if (ListInsert(&singleL, pos, e) == OK)
                    printf("插入成功！\n");
                else
                    printf("插入失败！\n");
            }
            break;
        }
        case 11: { // 删除单链表中的元素
            if (singleL == NULL) {
                printf("当前无单链表存在，请先初始化！\n");
            }
            else {
                int pos;
                ElemType e;
                printf("请输入要删除的元素的位置i: ");
                scanf("%d", &pos);
                if (ListDelete(&singleL, pos, &e) == OK)
                    printf("删除成功，删除的元素为：%d\n", e);
                if (ListDelete(&singleL, pos, &e) == ERROR)
                    printf("位置不合法，删除失败！\n");
                if (ListDelete(&singleL, pos, &e) == INFEASIBLE)
                    printf("单链表不存在！\n");
            }
            break;
        }
        case 12: { // 遍历单链表
            if (singleL == NULL) {
                printf("当前无单链表存在！\n");
            }
            else {
                printf("单链表中的元素为：");
                if (ListTraverse(singleL) != OK)
                    printf("遍历失败！\n");
            }
            break;
        }
        case 13: { // 翻转单链表
            if (singleL == NULL) {
                printf("当前无单链表存在！\n");
            }
            else {
                if (reverseList(singleL) == OK)
                    printf("链表翻转成功！\n");
                else
                    printf("翻转失败！\n");
            }
            break;
        }
        case 14: { // 删除倒数第 n 个结点
            if (singleL == NULL) {
                printf("当前无单链表存在！\n");
            }
            else {
                int n;
                printf("请输入删除倒数第n个结点的n值: ");
                scanf("%d", &n);
                if (RemoveNthFromEnd(singleL, n) == OK)
                    printf("删除成功！\n");
                else
                    printf("删除失败！\n");
            }
            break;
        }
        case 15: { // 对单链表进行排序
            if (singleL == NULL) {
                printf("当前无单链表存在！\n");
            }
            else {
                if (sortList(singleL) == OK)
                    printf("排序成功！\n");
                else
                    printf("排序失败！\n");
            }
            break;
        }
        case 16: { // 保存单链表到文件
            if (singleL == NULL) {
                printf("当前无单链表存在！\n");
            }
            else {
                char filename[100];
                printf("请输入保存文件的文件名: ");
                scanf("%s", filename);
                if (SaveList(singleL, filename) == OK)
                    printf("保存成功！\n");
                else
                    printf("保存失败！\n");
            }
            break;
        }
        case 17: { // 从文件加载单链表
            if (singleL != NULL) {
                printf("当前已有单链表，请先销毁后再加载文件。\n");
            }
            else {
                char filename[100];
                printf("请输入加载文件的文件名: ");
                scanf("%s", filename);
                if (LoadList(&singleL, filename) == OK)
                    printf("加载成功！\n");
                else
                    printf("加载失败！\n");
            }
            break;
        }
        case 18: {
            /* --- 多线性表管理子系统 --- */
            int subChoice;
            do {
                PrintSubMenu();
                int ret = scanf("%d", &subChoice);
                if (ret != 1) {
                    // 清空缓冲
                    while (getchar() != '\n');
                    printf("无效选择，请重新输入！\n");
                    continue; // 重新进入循环
                }
                switch (subChoice)
                {
                case 0:
                    printf("返回主菜单。\n");
                    break;
                case 1: {
                    // 创建新的单链表，并允许用户为该链表起名字
                    char tempName[30];
                    printf("请输入新链表的名字: ");
                    scanf("%s", tempName);
                    if (CreateNewList(&ml) == OK) {
                        // 新链表在数组中的下标为 ml.count - 1
                        strcpy(listNames[ml.count - 1], tempName);
                        printf("创建新链表成功, 链表名字为 \"%s\".\n", tempName);
                    }
                    else {
                        printf("创建链表失败！\n");
                    }
                    break;
                }
                case 2: {
                    //删除某个单链表
                    char listname[30];
                    printf("请输入要删除的链表的名字：");
                    scanf("%s", listname);
                    RemoveList(&ml, listNames, listname);
                }
                case 3: {
                    // 显示所有单链表状态：包括名字、所有元素、表长
                    if (ml.count == 0)
                        printf("当前无链表存在！\n");
                    else {
                        printf("\n所有链表状态：\n");
                        for (int j = 0; j < ml.count; j++) {
                            int len = ListLength(ml.lists[j]);
                            printf("链表名字: \"%s\", 长度: %d, 元素: ", listNames[j], len);
                            ListTraverse(ml.lists[j]);
                        }
                    }
                    break;
                }
                case 4: {
                    // 操作其中某个单链表：根据输入的链表名字查找
                    char searchName[30];
                    printf("请输入要操作的链表名字: ");
                    scanf("%s", searchName);
                    int foundIndex = -1;
                    for (int j = 0; j < ml.count; j++) {
                        if (strcmp(listNames[j], searchName) == 0) {
                            foundIndex = j;
                            break;
                        }
                    }
                    if (foundIndex == -1) {
                        printf("未找到单链表！\n");
                    }
                    else {
                        int op;
                        do {
                            PrintSubSubMenu(searchName);
                            int ret = scanf("%d", &op);
                            if (ret != 1) {
                                // 清空缓冲
                                while (getchar() != '\n');
                                printf("无效选择，请重新输入！\n");
                                continue; // 重新进入循环
                            }
                            switch (op)
                            {
                            case 0:
                                printf("返回多链表管理子系统。\n");
                                break;
                            case 1: {
                                if (DestroyList(&ml.lists[foundIndex]) == OK) {
                                    printf("链表 \"%s\" 已销毁！\n", searchName);
                                    // 删除该链表：将后续记录前移
                                    for (int k = foundIndex; k < ml.count - 1; k++) {
                                        ml.lists[k] = ml.lists[k + 1];
                                        strcpy(listNames[k], listNames[k + 1]);
                                    }
                                    ml.lists[ml.count - 1] = NULL;
                                    ml.count--;
                                    op = 0;  // 返回至子菜单
                                }
                                else {
                                    printf("销毁失败！\n");
                                }
                            } break;
                            case 2: {
                                if (ClearList(&ml.lists[foundIndex]) == OK)
                                    printf("链表 \"%s\" 清空成功！\n", searchName);
                                else
                                    printf("清空操作失败！\n");
                            } break;
                            case 3: {
                                status ret = ListEmpty(ml.lists[foundIndex]);
                                if (ret == TRUE)
                                    printf("链表 \"%s\" 为空！\n", searchName);
                                else if (ret == FALSE)
                                    printf("链表 \"%s\" 不为空！\n", searchName);
                                else
                                    printf("操作失败！\n");
                            } break;
                            case 4: {
                                int len = ListLength(ml.lists[foundIndex]);
                                if (len == INFEASIBLE)
                                    printf("操作失败！\n");
                                else
                                    printf("链表 \"%s\" 的长度为：%d\n", searchName, len);
                            } break;
                            case 5: {
                                int pos;
                                ElemType e;
                                printf("请输入要获取的元素位置: ");
                                scanf("%d", &pos);
                                if (GetElem(ml.lists[foundIndex], pos, &e) == OK)
                                    printf("链表 \"%s\" 的第 %d 个元素为：%d\n", searchName, pos, e);
                                else
                                    printf("操作失败！\n");
                            } break;
                            case 6: {
                                ElemType e;
                                printf("请输入要查找的元素: ");
                                scanf("%d", &e);
                                int pos = LocateElem(ml.lists[foundIndex], e);
                                if (pos == ERROR)
                                    printf("未找到元素 %d！\n", e);
                                else if (pos == INFEASIBLE)
                                    printf("操作失败！\n");
                                else
                                    printf("元素 %d 在链表 \"%s\" 中的位置为：%d\n", e, searchName, pos);
                            } break;
                            case 7: {
                                ElemType e, pre;
                                printf("请输入要查询前驱的元素: ");
                                scanf("%d", &e);
                                if (PriorElem(ml.lists[foundIndex], e, &pre) == OK)
                                    printf("元素 %d 的前驱为：%d\n", e, pre);
                                else
                                    printf("操作失败！\n");
                            } break;
                            case 8: {
                                ElemType e, next;
                                printf("请输入要查询后继的元素: ");
                                scanf("%d", &e);
                                if (NextElem(ml.lists[foundIndex], e, &next) == OK)
                                    printf("元素 %d 的后继为：%d\n", e, next);
                                else
                                    printf("操作失败！\n");
                            } break;
                            case 9: {
                                int pos;
                                ElemType e;
                                printf("请输入插入位置: ");
                                scanf("%d", &pos);
                                printf("请输入要插入的元素: ");
                                scanf("%d", &e);
                                if (ListInsert(&ml.lists[foundIndex], pos, e) == OK)
                                    printf("插入成功！\n");
                                else
                                    printf("插入失败！\n");
                            } break;
                            case 10: {
                                int pos;
                                ElemType e;
                                printf("请输入删除位置: ");
                                scanf("%d", &pos);
                                if (ListDelete(&ml.lists[foundIndex], pos, &e) == OK)
                                    printf("删除成功，删除的元素为：%d\n", e);
                                else
                                    printf("删除失败！\n");
                            } break;
                            case 11: {
                                printf("链表 \"%s\" 的元素: ", searchName);
                                if (ListTraverse(ml.lists[foundIndex]) != OK)
                                    printf("操作失败！\n");
                            } break;
                            case 12: {
                                if (reverseList(ml.lists[foundIndex]) == OK)
                                    printf("链表 \"%s\" 翻转成功！\n", searchName);
                                else
                                    printf("翻转失败！\n");
                            } break;
                            case 13: {
                                int n;
                                printf("请输入删除倒数第 n 个结点的 n 值: ");
                                scanf("%d", &n);
                                if (RemoveNthFromEnd(ml.lists[foundIndex], n) == OK)
                                    printf("删除成功！\n");
                                else
                                    printf("删除失败！\n");
                            } break;
                            case 14: {
                                if (sortList(ml.lists[foundIndex]) == OK)
                                    printf("链表 \"%s\" 排序成功！\n", searchName);
                                else
                                    printf("排序失败！\n");
                            } break;
                            case 15: {
                                char filename[100];
                                printf("请输入保存文件的文件名: ");
                                scanf("%s", filename);
                                if (SaveList(ml.lists[foundIndex], filename) == OK)
                                    printf("保存成功！\n");
                                else
                                    printf("保存失败！\n");
                            } break;
                            default:
                                printf("无效选择，请重新输入！\n");
                            } // end switch (op)
                        } while (op != 0);
                    }
                } break;
                default:
                    printf("无效选择，请重新输入！\n");
                }
            } while (subChoice != 0);
        } break;
        default:
            printf("无效选择，请重新输入！\n");
        }
    } while (choice != 0);

    // 退出前释放单链表及多链表管理中所有链表所占的内存
    if (singleL != NULL)
        DestroyList(&singleL);
    for (int i = 0; i < ml.count; i++) {
        DestroyList(&ml.lists[i]);
    }
    printf("程序已退出。\n");
    return 0;
}
