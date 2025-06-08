#define _CRT_SECURE_NO_WARNINGS

#include"functions.h"

int main()
{
    system("color F0");
    int choice = 0;
    BiTree currentTree = NULL;      // 当前使用的单棵二叉树
    BiTreeManager manager;          // 多二叉树管理器
    InitBiTreeManager(&manager);    // 初始化多二叉树管理器

    while (1)
    {
        PrintMenu();
        scanf("%d", &choice);
        switch (choice)
        {
        case 0:
            printf("退出演示系统。\n");
            exit(0);
            break;
        case 1:
        {
            int choice_;
            printf("请选择创建二叉树的方式：\n");
            printf(" 1. 带空子树标记的先序遍历序列\n");
            printf(" 2. 前序和中序遍历序列\n");
            printf(" 3. 后序和中序遍历序列\n");
            printf("请输入您的选择（1/2/3）：");
            scanf("%d", &choice_);

            if (choice_ == 1)
            {
                TElemType def[MAX_TREE_SIZE];
                int count = 0;
                printf("请输入带空子树标记的先序遍历序列的数据（格式：key others）：\n");
                printf("当输入key为-1时表示结束，输入0表示空结点。\n");
                while (1)
                {
                    printf("请输入结点%d的数据: ", count + 1);
                    scanf("%d %s", &def[count].key, def[count].others);
                    if (def[count].key == -1) // 终止标记
                        break;
                    count++;
                    if (count >= MAX_TREE_SIZE)
                    {
                        printf("已达最大输入个数，停止输入！\n");
                        break;
                    }
                }
                if (CreateBiTree(&currentTree, def, 1) == OK)
                    printf("二叉树初始化成功。\n");
                else
                    printf("二叉树初始化失败！\n");
            }
            else if (choice_ == 2)
            {
                int n;
                printf("请输入非空结点总数 n：");
                scanf("%d", &n);
                TElemType *def=(TElemType*)malloc((1+2*n)*sizeof(TElemType)); // 总长度为1+2*n
                def[0].key = n; // 保存结点数，others字段可以忽略或设为空
                printf("请输入前序遍历序列（%d 个结点）：\n", n);
                for (int i = 0; i < n; i++)
                {
                    printf("前序序列第 %d 个结点(key others): ", i + 1);
                    scanf("%d %s", &def[1 + i].key, def[1 + i].others);
                }
                printf("请输入中序遍历序列（%d 个结点）：\n", n);
                for (int i = 0; i < n; i++)
                {
                    printf("中序序列第 %d 个结点(key others): ", i + 1);
                    scanf("%d %s", &def[1 + n + i].key, def[1 + n + i].others);
                }
                if (CreateBiTree(&currentTree, def, 2) == OK)
                    printf("二叉树初始化成功。\n");
                else
                    printf("二叉树初始化失败！\n");
                free(def);
            }
            else if (choice_ == 3)
            {
                int n;
                printf("请输入非空结点总数 n：");
                scanf("%d", &n);
                TElemType* def = (TElemType*)malloc((1 + 2 * n) * sizeof(TElemType)); // 总长度为1+2*n
                def[0].key = n;
                printf("请输入后序遍历序列（%d 个结点）：\n", n);
                for (int i = 0; i < n; i++)
                {
                    printf("后序序列第 %d 个结点(key others): ", i + 1);
                    scanf("%d %s", &def[1 + i].key, def[1 + i].others);
                }
                printf("请输入中序遍历序列（%d 个结点）：\n", n);
                for (int i = 0; i < n; i++)
                {
                    printf("中序序列第 %d 个结点(key others): ", i + 1);
                    scanf("%d %s", &def[1 + n + i].key, def[1 + n + i].others);
                }
                if (CreateBiTree(&currentTree, def, 3) == OK)
                    printf("二叉树初始化成功。\n");
                else
                    printf("二叉树初始化失败！\n");
                free(def);
            }
            else
            {
                printf("创建方式输入错误！\n");
            }
        }
        break;
        case 2:
            // 销毁当前二叉树
            if (DestroyBiTree(&currentTree) == OK)
                printf("二叉树销毁成功。\n");
            else
                printf("二叉树销毁失败！\n");
            break;
        case 3:
            // 清空当前二叉树
            if (ClearBiTree(&currentTree) == OK)
                printf("二叉树已清空。\n");
            else
                printf("清空二叉树失败！\n");
            break;
        case 4:
            // 判断当前二叉树是否为空
            if (BiTreeEmpty(currentTree))
                printf("当前二叉树为空。\n");
            else
                printf("当前二叉树不为空。\n");
            break;
        case 5:
            // 获取当前二叉树深度
            printf("当前二叉树深度为：%d\n", BiTreeDepth(currentTree));
            break;
        case 6:
        {
            // 查找关键字为 e 的结点
            KeyType key;
            printf("请输入要查找的关键字: ");
            scanf("%d", &key);
            BiTNode* node = LocateNode(currentTree, key);
            if (node != NULL)
                printf("找到关键字为 %d 的结点。\n", key);
            else
                printf("未找到关键字为 %d 的结点！\n", key);
        }
        break;
        case 7:
        {
            // 给关键字为 e 的结点赋值
            KeyType key;
            TElemType newVal;
            printf("请输入目标结点关键字 e: ");
            scanf("%d", &key);
            printf("请输入新关键字key（整数）: ");
            scanf("%d", &newVal.key);
            printf("请输入其他信息others（字符串）: ");
            scanf("%s", newVal.others);
            if (Assign(&currentTree, key, newVal) == OK)
                printf("结点赋值成功。\n");
            else
                printf("结点赋值失败！\n");
        }
        break;
        case 8:
        {
            // 获得关键字为 e 的结点的兄弟结点
            KeyType key;
            printf("请输入要查找兄弟结点的关键字e: ");
            scanf("%d", &key);
            BiTNode* sibling = GetSibling(currentTree, key);
            if (sibling != NULL)
                printf("找到兄弟结点，关键字为: %d\n", sibling->data.key);
            else
                printf("查找兄弟结点出错！\n");
        }
        break;
        case 9:
        {
            // 插入结点
            KeyType key;
            TElemType c;
            int lr;
            printf("请输入要插入位置的父结点关键字 e: ");
            scanf("%d", &key);
            printf("请输入要插入结点的关键字key（整数）: ");
            scanf("%d", &c.key);
            printf("请输入要插入结点的其他信息others（字符串）: ");
            scanf("%s", c.others);
            printf("请输入插入方向（0表示左子树；1表示右子树；-1表示根节点）: ");
            scanf("%d", &lr);
            if (InsertNode(&currentTree, key, lr, c) == OK)
                printf("插入结点成功。\n");
            else
                printf("插入结点失败！\n");
        }
        break;
        case 10:
        {
            // 删除结点
            KeyType key;
            printf("请输入要删除的结点关键字: ");
            scanf("%d", &key);
            if (DeleteNode(&currentTree, key) == OK)
                printf("删除结点成功。\n");
            else
                printf("删除结点失败！\n");
        }
        break;
        case 11:
            // 前序遍历
            printf("前序遍历结果：\n");
            PreOrderTraverse(currentTree, visit);
            printf("\n");
            break;
        case 12:
            // 中序遍历
            printf("中序遍历结果：\n");
            InOrderTraverse(currentTree, visit);
            printf("\n");
            break;
        case 13:
            // 后序遍历
            printf("后序遍历结果：\n");
            PostOrderTraverse(currentTree, visit);
            printf("\n");
            break;
        case 14:
            // 层序遍历
            printf("层序遍历结果：\n");
            LevelOrderTraverse(currentTree, visit);
            printf("\n");
            break;
        case 15:
            // 附加功能1：求最大路径和
            printf("最大路径和为：%d\n", MaxPathSum(currentTree));
            break;
        case 16:
        {
            // 附加功能2：求最近公共祖先
            KeyType e1, e2;
            printf("请输入两个结点的关键字：");
            scanf("%d %d", &e1, &e2);
            BiTNode* lca = LowestCommonAncestor(currentTree, e1, e2);
            if (lca != NULL)
                printf("最近公共祖先的关键字为：%d\n", lca->data.key);
            else
                printf("未找到最近公共祖先！\n");
        }
        break;
        case 17:
            // 附加功能3：翻转二叉树
            InvertTree(currentTree);
            printf("二叉树已翻转。\n");
            break;
        case 18:
        {
            // 附加功能4：实现线性表的文件形式保存
            char filename[100];
            printf("请输入保存文件名: ");
            scanf("%s", filename);
            if (SaveBiTree(currentTree, filename) == OK)
                printf("保存成功。\n");
            else
                printf("保存失败！\n");
        }
        break;
        case 19:
        {
            // 附加功能5：从文件加载创建二叉树
            char filename[100];
            printf("请输入加载文件名: ");
            scanf("%s", filename);
            if (LoadBiTree(&currentTree, filename) == OK)
                printf("加载成功。\n");
            else
                printf("加载失败！\n");
        }
        break;
        case 20:
        {
            // 附加功能6：多二叉树管理子系统
            int subChoice = 0;
            do
            {
                PrintSubMenu();
                scanf("%d", &subChoice);
                switch (subChoice)
                {
                case 0:
                    printf("返回主菜单...\n");
                    break;
                case 1:
                {
                    // 创建新的二叉树并添加到管理器
                    int createChoice;
                    printf("请选择创建二叉树的方式：\n");
                    printf(" 1. 带空子树标记的先序遍历序列\n");
                    printf(" 2. 前序和中序遍历序列\n");
                    printf(" 3. 后序和中序遍历序列\n");
                    printf(" 4. 仅初始化\n");
                    printf("请输入您的选择（1/2/3/4）：");
                    scanf("%d", &createChoice);

                    BiTree newTree = NULL;
                    if (createChoice == 1)
                    {
                        TElemType def[MAX_TREE_SIZE];
                        int count = 0;
                        printf("请输入带空子树标记的先序遍历序列的数据（格式：key others），\n");
                        printf("输入key为0表示空结点，输入key为-1表示序列结束。\n");
                        while (1)
                        {
                            printf("请输入结点 %d 的数据: ", count + 1);
                            scanf("%d %s", &def[count].key, def[count].others);
                            if (def[count].key == -1)
                                break;
                            count++;
                            if (count >= MAX_TREE_SIZE)
                            {
                                printf("已达最大输入个数，停止输入！\n");
                                break;
                            }
                        }
                        if (CreateBiTree(&newTree, def, 1) == OK)
                            printf("二叉树创建成功。\n");
                        else
                            printf("二叉树创建失败！\n");
                    }
                    else if (createChoice == 2)
                    {
                        int n;
                        printf("请输入非空结点的总数n: ");
                        scanf("%d", &n);
                        TElemType* def = (TElemType*)malloc((1 + 2 * n) * sizeof(TElemType)); // 总长度为1+2*n
                        def[0].key = n;  // 保存结点数（others可忽略）
                        printf("请输入前序遍历序列的 %d 个结点数据 (key others):\n", n);
                        for (int i = 0; i < n; i++)
                        {
                            printf("前序序列第 %d 个结点: ", i + 1);
                            scanf("%d %s", &def[1 + i].key, def[1 + i].others);
                        }
                        printf("请输入中序遍历序列的 %d 个结点数据 (key others):\n", n);
                        for (int i = 0; i < n; i++)
                        {
                            printf("中序序列第 %d 个结点: ", i + 1);
                            scanf("%d %s", &def[1 + n + i].key, def[1 + n + i].others);
                        }
                        if (CreateBiTree(&newTree, def, 2) == OK)
                            printf("二叉树创建成功。\n");
                        else
                            printf("二叉树创建失败！\n");
                        free(def);
                    }
                    else if (createChoice == 3)
                    {
                        int n;
                        printf("请输入非空结点的总数 n: ");
                        scanf("%d", &n);
                        TElemType* def = (TElemType*)malloc((1 + 2 * n) * sizeof(TElemType)); // 总长度为1+2*n
                        def[0].key = n;
                        printf("请输入后序遍历序列的 %d 个结点数据 (key others):\n", n);
                        for (int i = 0; i < n; i++)
                        {
                            printf("后序序列第 %d 个结点: ", i + 1);
                            scanf("%d %s", &def[1 + i].key, def[1 + i].others);
                        }
                        printf("请输入中序遍历序列的 %d 个结点数据 (key others):\n", n);
                        for (int i = 0; i < n; i++)
                        {
                            printf("中序序列第 %d 个结点: ", i + 1);
                            scanf("%d %s", &def[1 + n + i].key, def[1 + n + i].others);
                        }
                        if (CreateBiTree(&newTree, def, 3) == OK)
                            printf("二叉树创建成功。\n");
                        else
                            printf("二叉树创建失败！\n");
                        free(def);
                    }
                    else if (createChoice == 4) 
                    {
                        if (InitBiTree(&newTree) == OK)
                            printf("初始化二叉树成功\n");
                        else
                            printf("初始化二叉树失败！\n");
                    }
                    else
                    {
                        printf("创建方式输入错误！\n");
                        break;
                    }
                    // 完成新二叉树的创建后，询问用户为该二叉树命名，然后添加到管理器中
                    char name[50];
                    printf("请输入新二叉树的名称: ");
                    scanf("%s", name);
                    if (AddBiTree(&manager, name, newTree) == OK)
                        printf("二叉树添加到管理器成功。\n");
                    else
                        printf("二叉树添加失败，可能存在重名或管理器已满。\n");
                }
                break;
                case 2:
                    // 显示管理器中所有二叉树的状态
                    ListBiTrees(&manager);
                    break;
                case 3:
                {
                    //删除某个二叉树
                    char delName[50];
                    printf("请输入要删除的二叉树名称: ");
                    scanf("%s", delName);
                    if (RemoveBiTree(&manager, delName) == OK)
                        printf("删除成功！\n");
                    else
                        printf("删除失败！\n");
                    break;
                }
                case 4:
                {
                    // 选择某个二叉树进行操作
                    char targetName[50];
                    printf("请输入要操作的二叉树名称: ");
                    scanf("%s", targetName);
                    BiTree targetTree = GetBiTree(&manager, targetName);
                    if (targetTree == NULL)
                    {
                        printf("二叉树不存在！\n");
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
                                printf("返回多二叉树管理子菜单...\n");
                                break;
                            case 1:
                                if (DestroyBiTree(&targetTree) == OK)
                                    printf("销毁二叉树成功。\n");
                                else
                                    printf("销毁失败！\n");
                                break;
                            case 2:
                                if (ClearBiTree(&targetTree) == OK)
                                    printf("清空二叉树成功。\n");
                                else
                                    printf("清空失败！\n");
                                break;
                            case 3:
                                if (BiTreeEmpty(targetTree))
                                    printf("二叉树为空。\n");
                                else
                                    printf("二叉树不为空。\n");
                                break;
                            case 4:
                                printf("二叉树深度为：%d\n", BiTreeDepth(targetTree));
                                break;
                            case 5:
                            {
                                KeyType key;
                                printf("请输入查找结点的关键字: ");
                                scanf("%d", &key);
                                BiTNode* res = LocateNode(targetTree, key);
                                if (res)
                                    printf("找到关键字为 %d 的结点\n", res->data.key);
                                else
                                    printf("未找到该结点！\n");
                            }
                            break;
                            case 6:
                            {
                                KeyType key;
                                TElemType newVal;
                                printf("请输入结点关键字 e: ");
                                scanf("%d", &key);
                                printf("请输入新关键字key（整数）: ");
                                scanf("%d", &newVal.key);
                                printf("请输入其他信息others（字符串）: ");
                                scanf("%s", newVal.others);
                                if (Assign(&targetTree, key, newVal) == OK)
                                    printf("赋值成功。\n");
                                else
                                    printf("赋值失败！\n");
                            }
                            break;
                            case 7:
                            {
                                KeyType key;
                                printf("请输入查找兄弟结点的关键字 e: ");
                                scanf("%d", &key);
                                BiTNode* sib = GetSibling(targetTree, key);
                                if (sib)
                                    printf("兄弟结点关键字为：%d\n", sib->data.key);
                                else
                                    printf("查找兄弟结点出错！\n");
                            }
                            break;
                            case 8:
                            {
                                KeyType key;
                                TElemType nodeVal;
                                int lr;
                                printf("请输入要插入位置的父结点关键字 e: ");
                                scanf("%d", &key);
                                printf("请输入要插入结点的关键字key（整数）: ");
                                scanf("%d", &nodeVal.key);
                                printf("请输入要插入结点的其他信息others（字符串）: ");
                                scanf("%s", nodeVal.others);
                                printf("请输入插入方向（0表示左子树；1表示右子树；-1表示根节点）: ");
                                scanf("%d", &lr);
                                if (InsertNode(&targetTree, key, lr, nodeVal) == OK)
                                    printf("插入成功。\n");
                                else
                                    printf("插入失败！\n");
                            }
                            break;
                            case 9:
                            {
                                KeyType key;
                                printf("请输入要删除结点的关键字: ");
                                scanf("%d", &key);
                                if (DeleteNode(&targetTree, key) == OK)
                                    printf("删除成功。\n");
                                else
                                    printf("删除失败！\n");
                            }
                            break;
                            case 10:
                                printf("前序遍历结果：\n");
                                PreOrderTraverse(targetTree, visit);
                                printf("\n");
                                break;
                            case 11:
                                printf("中序遍历结果：\n");
                                InOrderTraverse(targetTree, visit);
                                printf("\n");
                                break;
                            case 12:
                                printf("后序遍历结果：\n");
                                PostOrderTraverse(targetTree, visit);
                                printf("\n");
                                break;
                            case 13:
                                printf("层序遍历结果：\n");
                                LevelOrderTraverse(targetTree, visit);
                                printf("\n");
                                break;
                            case 14:
                                printf("最大路径和为：%d\n", MaxPathSum(targetTree));
                                break;
                            case 15:
                            {
                                KeyType a, b;
                                printf("请输入两个结点的关键字：");
                                scanf("%d %d", &a, &b);
                                BiTNode* lca = LowestCommonAncestor(targetTree, a, b);
                                if (lca)
                                    printf("最近公共祖先为：%d\n", lca->data.key);
                                else
                                    printf("未找到最近公共祖先！\n");
                            }
                            break;
                            case 16:
                                InvertTree(targetTree);
                                printf("二叉树已翻转。\n");
                                break;
                            case 17:
                            {
                                char fname[100];
                                printf("请输入保存文件名: ");
                                scanf("%s", fname);
                                if (SaveBiTree(targetTree, fname) == OK)
                                    printf("保存成功。\n");
                                else
                                    printf("保存失败！\n");
                            }
                            break;
                            case 18:
                            {
                                char fname[100];
                                printf("请输入加载文件名: ");
                                scanf("%s", fname);
                                if (LoadBiTree(&targetTree, fname) == OK)
                                    printf("加载成功。\n");
                                else
                                    printf("加载失败！\n");
                            }
                            break;
                            default:
                                printf("无效选择，请输入正确的选项！\n");
                                break;
                            }
                        } while (subSubChoice != 0);
                    }
                }
                break;
                default:
                    printf("无效选择，请输入正确的选项！\n");
                    break;
                }
            } while (subChoice != 0);
        }
        break;
        default:
            printf("无效选择，请输入正确的选项！\n");
            break;
        }
    }
    return 0;
}