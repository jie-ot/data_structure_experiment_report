#define _CRT_SECURE_NO_WARNINGS
#include"functions.h"


status InitBiTree(BiTree* T)
{
	*T = (BiTree)malloc(sizeof(BiTNode));
	if (*T == NULL) {
		return OVERFLOW;  // 内存分配失败
	}
	// 初始化头结点数据
	(*T)->data.key = 0; 
	strcpy((*T)->data.others, "head");
	(*T)->lchild = NULL;
	(*T)->rchild = NULL;
	return OK;
}
void visit(BiTree T)
{
	printf(" %d,%s", T->data.key, T->data.others);
}
status PreOrderTraverse(BiTree T, void (*visit)(BiTree))
{
	if (T != NULL) {
		visit(T);
		PreOrderTraverse(T->lchild, visit);
		PreOrderTraverse(T->rchild, visit);
	}
	return OK;
}
status InOrderTraverse(BiTree T, void (*visit)(BiTree))
{
	if (T != NULL) {
		InOrderTraverse(T->lchild, visit);
		visit(T);
		InOrderTraverse(T->rchild, visit);
	}
	return OK;
}
status PostOrderTraverse(BiTree T, void (*visit)(BiTree))
{
	if (T != NULL) {
		PostOrderTraverse(T->lchild, visit);
		PostOrderTraverse(T->rchild, visit);
		visit(T);
	}
	return OK;
}
status InOderTraverse_nonrecursive(BiTree T, void (*visit)(BiTree))
//借鉴中序遍历递归算法执行过程中递归工作栈的原理，非递归算法可以设置一个指针栈暂存搜索路径中的结点指针。
{
	BiTree stack[MAX_TREE_SIZE];  //定义指针栈
	int top = 0; //初始化顺序栈
	stack[top++] = T; //根指针进栈
	BiTree temp;
	while (top) {
		temp = stack[top - 1]; //读取栈顶指针
		while (temp) {
			temp = temp->lchild; //向左走到尽头
			stack[top++] = temp; //最左侧指针依次进栈
		}
		top--; //空指针NULL退栈，现在top为栈顶元素的上一个
		if (top != 0) {
			temp = stack[--top]; //路径上最左侧结点退栈并访问
			visit(T);
			stack[top++] = temp->rchild; //右孩子指针进栈
		}
	}
	return OK;

	//改进算法：
	/*
	BiTree stack[MAX_TREE_SIZE];
	int top = 0;
	BiTree cur = T;
	while (cur != NULL || top > 0) {
		while (cur != NULL) {
			stack[top++] = cur;
			cur = cur->lchild;
		}
		cur = stack[--top];
		visit(T);
		cur = cur->rchild;
	}
	return OK;
	*/
}
status LevelOrderTraverse(BiTree T, void (*visit)(BiTree))
//层序遍历中先访问的结点其左右孩子也要先访问，队列先进先出的特性能满足这一要求。
{
	BiTree Queue[MAX_TREE_SIZE];
	int front = 0, rear = 0;
	BiTree cur = T;
	if (cur) Queue[rear++] = cur; //根指针非空，则进队
	while (front != rear) {
		cur = Queue[front++]; //队首结点出队
		visit(cur);
		if (cur->lchild) Queue[rear++] = cur->lchild;
		if (cur->rchild) Queue[rear++] = cur->rchild;
	}
	return OK;
}

/* 辅助函数：带空子树标记的先序构造二叉树（choice==1）
   说明：
   - 当 definition[*index].key == -1 时，表示输入结束（该标记不构造成结点）。
   - 当 definition[*index].key == 0 时，表示空子树，将 *T 置为 NULL。 */
status CreateBiTree_Recursive(BiTree* T, TElemType definition[], int* index) {
	if (definition[*index].key == -1) {  // 终止标记
		(*index)++;
		return OK;
	}
	if (definition[*index].key == 0) {   // 空子树标记
		*T = NULL;
		(*index)++;
		return OK;
	}
	*T = (BiTree)malloc(sizeof(BiTNode));
	if (*T == NULL) {
		return OVERFLOW;
	}
	(*T)->data = definition[*index];
	(*index)++;
	CreateBiTree_Recursive(&((*T)->lchild), definition, index);
	CreateBiTree_Recursive(&((*T)->rchild), definition, index);
	return OK;
}

/* 辅助函数：根据前序和中序序列构造二叉树（choice==2）
   参数：
	   pre   : 前序序列（长度为 n）
	   in    : 中序序列（长度为 n）
	   n     : 序列中结点数量
 */
status CreateBiTree_PreIn(BiTree* T, TElemType pre[], TElemType in[], int n) {
	if (n <= 0) {
		*T = NULL;
		return OK;
	}
	int i;
	*T = (BiTree)malloc(sizeof(BiTNode));
	if (*T == NULL)
		return OVERFLOW;
	(*T)->data = pre[0];
	// 在中序序列中查找根结点位置
	for (i = 0; i < n; i++) {
		if (in[i].key == pre[0].key) break;
	}
	if (i == n) return ERROR;  // 没有找到，数据错误
	// i 为左子树结点数，n-i-1 为右子树结点数
	CreateBiTree_PreIn(&((*T)->lchild), pre + 1, in, i);
	CreateBiTree_PreIn(&((*T)->rchild), pre + 1 + i, in + i + 1, n - i - 1);
	return OK;
}

/* 辅助函数：根据后序和中序序列构造二叉树（choice==3）
   参数：
	   post  : 后序序列（长度为 n）
	   in    : 中序序列（长度为 n）
	   n     : 序列中结点数量
 */
status CreateBiTree_PostIn(BiTree* T, TElemType post[], TElemType in[], int n) {
	if (n <= 0) {
		*T = NULL;
		return OK;
	}
	int i;
	*T = (BiTree)malloc(sizeof(BiTNode));
	if (*T == NULL)
		return OVERFLOW;
	// 后序序列最后一个结点为根
	(*T)->data = post[n - 1];
	// 在中序序列中查找根的位置
	for (i = 0; i < n; i++) {
		if (in[i].key == post[n - 1].key)
			break;
	}
	if (i == n) return ERROR;  // 数据错误
	// 左子树大小为 i，右子树大小为 n - i - 1
	CreateBiTree_PostIn(&((*T)->lchild), post, in, i);
	CreateBiTree_PostIn(&((*T)->rchild), post + i, in + i + 1, n - i - 1);
	return OK;
}

/* 主创建二叉树函数，根据 choice 的值调用相应创建方法
   choice==1: 根据带空子树标记的先序遍历序列创建二叉树，
			 此时 definition 数组的格式中包含空子树标记（key==0）和终止标记（key==-1）。
   choice==2: 根据前序+中序序列建立二叉树，
			 定义约定：definition[0].key 保存结点数 n，
			 接下来连续 n 个元素为前序序列，
			 紧跟着 n 个元素为中序序列。
   choice==3: 根据后序+中序序列建立二叉树，
			 定义约定同上，只不过前一部分为后序序列。
*/
status CreateBiTree(BiTree* T, TElemType definition[], int choice) {
	if (choice == 1) {
		int index = 0;
		return CreateBiTree_Recursive(T, definition, &index);
	}
	else if (choice == 2) {
		// 按约定，definition[0].key 为结点数 n，
		// 后续前 n 个为前序序列，紧跟着 n 个为中序序列
		int n = definition[0].key;
		return CreateBiTree_PreIn(T, &definition[1], &definition[1 + n], n);
	}
	else if (choice == 3) {
		// 同样，definition[0].key 为结点数 n，
		// 后续前 n 个为后序序列，紧跟着 n 个为中序序列
		int n = definition[0].key;
		return CreateBiTree_PostIn(T, &definition[1], &definition[1 + n], n);
	}
	else {
		return ERROR;  // 不支持的输入方式
	}
}

status ClearBiTree(BiTree* T)
//将二叉树T置空，并释放所有结点的空间
{
	// 如果T本身为NULL，则返回错误
	if (T == NULL)
		return ERROR;

	// 如果二叉树不为空，递归清空左、右子树
	if (*T != NULL) {
		ClearBiTree(&((*T)->lchild));  // 清空左子树
		ClearBiTree(&((*T)->rchild));  // 清空右子树

		free(*T); // 释放当前节点的内存，并置空指针，避免野指针风险
		*T = NULL;
	}
	return OK;
}
int BiTreeDepth(BiTree T)
//求二叉树T深度并返回深度值
{
	if (T == NULL) return 0;
	else {
		int left_depth = BiTreeDepth(T->lchild);
		int right_depth = BiTreeDepth(T->rchild);
		// 当前树的深度为左右子树中较大者+1
		return (left_depth > right_depth ? left_depth : right_depth) + 1;
	}
}
BiTNode* LocateNode(BiTree T, KeyType e)
//e是和T中结点关键字类型相同的给定值；根据e查找符合条件的结点，返回该结点指针，如无关键字为e的结点，返回NULL。
{
	if (T == NULL) return NULL;
	if (T->data.key == e) return T;
	BiTNode* p = LocateNode(T->lchild, e);// 先在左子树中查找
	if (p != NULL)
		return p;  // 找到则返回
	
	return LocateNode(T->rchild, e); // 若左子树中未找到，则继续在右子树中查找
}
status Assign(BiTree* T, KeyType e, TElemType value)
/*e是和T中结点关键字类型相同的给定值；查找结点关键字等于e的结点，将该结点值修改成value，
返回OK（要求结点关键字保持唯一性）。如果查找失败，返回ERROR。*/
{
	BiTNode* p = LocateNode(*T, e);
	if (p == NULL) return ERROR;
	// 如果欲更改的关键字不等于原来的关键字，则需检查树中是否已存在该新关键字
	if (value.key != p->data.key) {
		BiTNode* q = LocateNode(*T, value.key);
		// 如果找到的结点不是 p 本身，说明新关键字已存在
		if (q != NULL)
			return ERROR;
	}
	p->data = value;
	return OK;
}
BiTNode* GetSibling(BiTree T, KeyType e)
/*e是和T中结点关键字类型相同的给定值；查找结点关键字等于e的结点的兄弟结点，返回其兄弟结点指针。如果查找失败，返回NULL。*/
{
	if (T == NULL) return NULL;

	// 如果左子树中的结点满足条件，则返回右子树指针
	if (T->lchild != NULL && T->lchild->data.key == e)
		return T->rchild;  // 若无右子树则返回NULL

	// 如果右子树中的结点满足条件，则返回左子树指针
	if (T->rchild != NULL && T->rchild->data.key == e)
		return T->lchild;  // 若无左子树则返回NULL

	// 先在左子树中递归查找
	BiTNode* sibling = GetSibling(T->lchild, e);
	if (sibling != NULL)
		return sibling;

	// 若左子树没有，再在右子树中递归查找
	return GetSibling(T->rchild, e);
}
status InsertNode(BiTree* T, KeyType e, int LR, TElemType c)
/*e是和T中结点关键字类型相同的给定值，LR为0或1，c是待插入结点；根据LR为0或者1，插入结点c到T中，
作为关键字为e的结点的左或右孩子结点，结点e的原有左子树或右子树则为结点c的右子树，返回OK。如果插
入失败，返回ERROR。 特别地，当LR为-1时，作为根结点插入，原根结点作为c的右子树。*/
{
	if (T == NULL) return ERROR;

	/* 在整个树中查找是否已存在待插入结点c的关键字，关键字必须唯一 */
	if (LocateNode(*T, c.key) != NULL) {
		return ERROR;  // 重复关键字，插入失败
	}

	// 特别地，LR 为 -1 时作为根结点插入，新结点的右子树挂原根
	if (LR == -1) {
		BiTNode* newNode = (BiTNode*)malloc(sizeof(BiTNode));
		if (newNode == NULL)
			return ERROR;
		newNode->data = c;
		newNode->lchild = NULL;
		newNode->rchild = *T;  // 原根结点作为新结点的右子树
		*T = newNode;          // 修改根指针
		return OK;
	}

	// LR 为 0 或 1 的情况：先查找关键字为 e 的结点
	BiTNode* parent = LocateNode(*T, e);
	if (parent == NULL)
		return ERROR;

	BiTNode* newNode = (BiTNode*)malloc(sizeof(BiTNode));
	if (newNode == NULL)
		return ERROR;
	newNode->data = c;
	newNode->lchild = NULL;   // 默认新结点的左子树为空

	if (LR == 0) {
		// 将新结点插入为 parent 的左孩子，新结点的右子树挂上原来的左子树
		newNode->rchild = parent->lchild;
		parent->lchild = newNode;
	}
	else if (LR == 1) {
		// 将新结点插入为 parent 的右孩子，新结点的右子树挂上原来的右子树
		newNode->rchild = parent->rchild;
		parent->rchild = newNode;
	}
	else {
		// 如果 LR 不是 -1、0 或 1，视为非法参数
		free(newNode);
		return ERROR;
	}
	return OK;
}
BiTNode* FindNodeWithParent(BiTree T, KeyType e, BiTNode* parent, BiTNode** outParent)
/*辅助函数：查找关键字为 e 的结点，同时返回该结点的父结点。
 *参数说明：
 *   T        : 当前子树的根结点
 *   e        : 要查找的关键字
 *   parent   : 当前结点的父结点（在递归调用中传入）
 *   outParent: 输出参数，用来返回找到结点的父结点（若结点为根则置为NULL）
 */
{
	if (T == NULL) return NULL;
	if (T->data.key == e) {
		*outParent = parent;
		return T;
	}
	BiTNode* found = FindNodeWithParent(T->lchild, e, T, outParent);  //依旧是先在左子树里面找，找不到再到右子树里面找
	if (found != NULL) return found;
	return FindNodeWithParent(T->rchild, e, T, outParent);
}
status DeleteNode(BiTree* T, KeyType e)
/*e是和T中结点关键字类型相同的给定值。删除T中关键字为e的结点；同时，根据该被删结点的度进行讨论：
	1.如关键字为e的结点度为0，删除即可；
	2.如关键字为e的结点度为1，用关键字为e的结点孩子代替被删除的e位置；
	3.如关键字为e的结点度为2，用e的左子树（简称为LC）代替被删除的e位置，将e的右子树（简称为RC）作为LC中最右节点的右子树。
成功删除结点后返回OK，否则返回ERROR。*/
{
	if (T == NULL || *T == NULL) return ERROR;

	BiTNode* parent = NULL;
	BiTNode* p = FindNodeWithParent(*T, e, NULL, &parent);
	if (p == NULL) return ERROR; //未找到关键字为e的结点

	if (p->lchild == NULL && p->rchild == NULL) {  //情况1：被删结点为叶结点（度为0）
		if (parent == NULL) *T = NULL; //被删结点为根结点
		else {
			if (parent->lchild == p) parent->lchild = NULL;
			else parent->rchild = NULL;
		}
		free(p);
		return OK;
	}
	else if (p->lchild == NULL || p->rchild == NULL) {  //情况2：被删结点度为1
		BiTNode* child = (p->lchild != NULL) ? p->lchild : p->rchild;
		if (parent == NULL) *T = child; //被删结点为根结点
		else {
			if (parent->lchild == p) parent->lchild = child;
			else parent->rchild = child;
		}
		free(p);
		return OK;
	}
	else {  //情况3：被删结点度为2
		// 令 LC 为 p 的左子树，RC 为 p 的右子树
		BiTNode* LC = p->lchild;
		BiTNode* RC = p->rchild;
		// 在 LC 中找到最右侧的结点
		BiTNode* mostright = LC;
		while (mostright->rchild != NULL)
			mostright = mostright->rchild;
		// 将 RC 接到 mostright 的右孩子上
		mostright->rchild = RC;
		// 用 LC 代替 p 在父结点处的位置
		if (parent == NULL) {  // p 为根结点
			*T = LC;
		}
		else {
			if (parent->lchild == p)
				parent->lchild = LC;
			else
				parent->rchild = LC;
		}
		free(p);
		return OK;
	}
}
status DestroyBiTree(BiTree* T)
{
	if (T == NULL) return ERROR;  // 如果传入的是空指针，则返回错误

	if (*T != NULL) {
		// 先销毁左子树和右子树，采用后序遍历
		DestroyBiTree(&((*T)->lchild));
		DestroyBiTree(&((*T)->rchild));
		// 释放当前结点
		free(*T);
		*T = NULL;  // 防止悬挂指针
	}
	return OK;
}
status BiTreeEmpty(BiTree T) 
//二叉树判空
{
	return (T == NULL) ? TRUE : FALSE;
}

int MaxPathSum(BiTree T) 
//该函数返回从根节点出发到任一叶子结点的路径中，各结点 data.key 值之和的最大值。
{
	if (T == NULL) return ERROR;

	// 如果是叶子节点，直接返回该结点的 key 值
	if (T->lchild == NULL && T->rchild == NULL) return T->data.key;

	// 如果只有一边子树存在，则必经该分支
	if (T->lchild == NULL)
		return T->data.key + MaxPathSum(T->rchild);
	if (T->rchild == NULL)
		return T->data.key + MaxPathSum(T->lchild);

	// 两边都存在，取最大者
	int leftSum = MaxPathSum(T->lchild);
	int rightSum = MaxPathSum(T->rchild);
	return T->data.key + (leftSum > rightSum ? leftSum : rightSum);
}
BiTNode* LowestCommonAncestor(BiTree T, KeyType e1, KeyType e2)
//最近公共祖先：求解二叉树中两个给定关键字（e1 和 e2）所在结点的最近公共祖先。
{
	if (T == NULL) return NULL;

	if (LocateNode(T, e1) == NULL || LocateNode(T, e2) == NULL) return NULL;

	// 若当前结点已是 e1 或 e2，则返回当前结点
	if (T->data.key == e1 || T->data.key == e2) return T;

	BiTree left = LowestCommonAncestor(T->lchild, e1, e2); 
	BiTree right = LowestCommonAncestor(T->rchild, e1, e2);
	/*
	场景 1：目标节点均不在对应的子树中
			如果T->lchild的子树中既没有e1也没有e2：递归搜索会一路走到底，发现空子树后，如果T==NULL则立刻返回NULL。因此left返回NULL。
		类似地，如果T->rchild的子树中既没有e1也没有e2：则right也返回NULL。
	场景 2：仅一侧子树找到目标节点（或该侧已经计算出该子树内的最近公共祖先）
		   例如：在T的左子树中找到了e1或e2，或即使在左子树中同时出现了两目标，但它们的最近公共祖先就在左子树中（例如后续返回的结点），
		那么left将返回该非空指针。而如果在右子树中未找到目标，则right == NULL。反之：若右子树中找到了目标（或其某一侧已经形成了局部公
		共祖先），而左子树找不到，则right返回非空，而left == NULL。
	场景 3：两侧子树均找到了目标
		   当T的左子树中搜索到e1而右子树中搜索到e2（或者相反），此时left != NULL且right != NULL。说明e1和e2分别位于当前节点T的左右
		两个不同方向，那么当前节点T就是这两个目标的最近公共祖先。(此时递归调用分别返回的是目标节点本身，或已经在某个子树中由递归判断出
		的局部祖先。）
	*/

	// 如果左右子树均找到了目标，则当前结点即为最近公共祖先
	if (left != NULL && right != NULL) return T;

	// 否则将非空的一侧向上回传，对于叶子结点，左右都为NULL，所有返回NULL
	return left != NULL ? left : right;
}
void InvertTree(BiTree T) 
//二叉树翻转：将树中所有结点的左右子树互换
{
	if (T == NULL) return;

	// 交换左右子树
	BiTree temp = T->lchild;
	T->lchild = T->rchild;
	T->rchild = temp;

	// 递归翻转左右子树
	InvertTree(T->lchild);
	InvertTree(T->rchild);
}
// 辅助函数：先序遍历写入（按照标准格式输出：有效节点输出 key 和 others，空子树输出 "0 null"）
void SaveBiTree_PreOrder(BiTree T, FILE* fp)
{
	if (T == NULL) {
		// 空子树标记
		fprintf(fp, "0 null ");
		return;
	}
	// 输出当前有效结点：关键字与其它信息
	fprintf(fp, "%d %s ", T->data.key, T->data.others);
	// 递归写入左子树和右子树
	SaveBiTree_PreOrder(T->lchild, fp);
	SaveBiTree_PreOrder(T->rchild, fp);
}
status SaveBiTree(BiTree T, char FileName[])
{
	FILE* fp = fopen(FileName, "w");
	if (fp == NULL)
		return ERROR;
	// 先序遍历写入二叉树到文件，空子树输出 "0 null"
	SaveBiTree_PreOrder(T, fp);
	// 写入结束标记：-1 null
	fprintf(fp, "-1 null ");
	fclose(fp);
	return OK;
}
status LoadBiTree(BiTree* T, char FileName[])
{
	FILE* fp = fopen(FileName, "r");
	if (fp == NULL)
		return ERROR;

	// 使用 definition 数组存放先序定义序列，定义的标准与保存时一致：
	// 有效结点：key > 0，对应的字符串；空子树：key 为0；输入结束：key为-1
	TElemType definition[MAX_TREE_SIZE];
	int count = 0;
	char token[20];

	// 循环读入标记：每次先读 key（字符串形式），转换为整型
	while (fscanf(fp, "%s", token) == 1)
	{
		int k = atoi(token);
		if (k == -1) {  // 遇到结束标记则停止读取
			break;
		}
		// 将当前结点信息保存到 definition 数组中
		definition[count].key = k;
		fscanf(fp, "%s", token); // 读取对应的others字符串
		strcpy(definition[count].others, token);
		count++;
	}
	fclose(fp);

	int index = 0;
	// 调用辅助函数，根据 definition 数组构建二叉树
	return CreateBiTree_Recursive(T, definition, &index);
}

/*多二叉树管理*/
status InitBiTreeManager(BiTreeManager* manager) 
{
	if (manager == NULL) return ERROR;
	manager->count = 0;
	return OK;
}
status AddBiTree(BiTreeManager* manager, char name[], BiTree tree)
{
	if (manager == NULL) return ERROR;
	if (manager->count >= MAX_BTREES) return OVERFLOW;  // 管理器空间满

	//检查是否已存在相同名称的二叉树
	for (int i = 0; i < manager->count; i++) {
		if (strcmp(manager->items[i].name, name) == 0) {
			return ERROR;  // 重名，不能重复添加
		}
	}

	strcpy(manager->items[manager->count].name, name);
	manager->items[manager->count].tree = tree;
	manager->count++;
	return OK;
}
status RemoveBiTree(BiTreeManager* manager, char name[]) 
{
	if (manager == NULL) return ERROR;

	int pos = -1;
	for (int i = 0; i < manager->count; i++) {
		if (strcmp(manager->items[i].name, name) == 0) {
			pos = i;
			break;
		}
	}
	if (pos == -1) return ERROR; // 没有找到指定名称的二叉树

	// 销毁该二叉树
	if(DestroyBiTree(&(manager->items[pos].tree))==ERROR) return ERROR;

	// 将后面的元素依次前移，以填补空缺
	for (int i = pos; i < manager->count - 1; i++) {
		manager->items[i] = manager->items[i + 1];
	}
	manager->count--;
	return OK;
}
void ListBiTrees(BiTreeManager* manager)
//列出管理中的所有二叉树
{
	if (manager == NULL) return;
	printf("当前管理的二叉树列表：\n");
	for (int i = 0; i < manager->count; i++) {
		printf("序号：%d, 名称：%s\n", i + 1, manager->items[i].name);
	}
}
BiTree GetBiTree(BiTreeManager* manager, char name[]) 
//根据二叉树名称返回二叉树指针，如果没找到则返回 NULL
{
	if (manager == NULL) return NULL;
	for (int i = 0; i < manager->count; i++) {
		if (strcmp(manager->items[i].name, name) == 0) {
			return manager->items[i].tree;
		}
	}
	return NULL;
}

/*菜单函数*/
void PrintMenu()
{
	printf("\n  -------二叉树演示系统-------  \n");
	printf("**************************************\n");
	printf("  0.退出演示系统\n");
	printf("  1.创建单个二叉树\n");
	printf("  2.销毁当前二叉树\n");
	printf("  3.清空当前二叉树\n");
	printf("  4.判断当前二叉树是否为空\n");
	printf("  5.获取当前二叉树的深度\n");
	printf("  6.查找关键字为e的结点\n");
	printf("  7.给关键字为e的结点赋值\n");
	printf("  8.获得关键字为e的结点的兄弟结点\n");
	printf("  9.插入结点\n");
	printf(" 10.删除结点\n");
	printf(" 11.前序遍历\n");
	printf(" 12.中序遍历\n");
	printf(" 13.后序遍历\n");
	printf(" 14.层序遍历\n");
	printf(" 15.附加功能1：求最大路径和\n");
	printf(" 16.附加功能2：求最近公共祖先\n");
	printf(" 17.附加功能3：翻转二叉树\n");
	printf(" 18.附加功能4：实现线性表的文件形式保存\n");
	printf(" 19.附加功能5：从文件加载创建二叉树\n");
	printf(" 20.附加功能6：多二叉树管理\n");
	printf("**************************************\n");
	printf("请输入你的选择: ");
}
void PrintSubMenu()
{
	printf("\n--- 多二叉树管理子系统 ---\n");
	printf("  1.创建新的二叉树\n");
	printf("  2.显示所有二叉树状态\n");
	printf("  3.删除某个二叉树\n");
	printf("  4.操作其中某个二叉树\n");
	printf("  0.返回主菜单\n");
	printf("请输入你的选择: ");
}
void PrintSubSubMenu(char* listname)
{
	printf("\n-----操作二叉树 \"%s\" -----\n", listname);
	printf("  0.返回子菜单\n");
	printf("  1.销毁二叉树\n");
	printf("  2.清空二叉树\n");
	printf("  3.二叉树判空\n");
	printf("  4.获取二叉树深度\n");
	printf("  5.查找关键字为e的结点\n");
	printf("  6.给关键字为e的结点赋值\n");
	printf("  7.获得关键字为e的结点的兄弟结点\n");
	printf("  8.插入结点\n");
	printf("  9.删除结点\n");
	printf(" 10.前序遍历\n");
	printf(" 11.中序遍历\n");
	printf(" 12.后序遍历\n");
	printf(" 13.层序遍历\n");
	printf(" 14.附加功能1：求最大路径和\n");
	printf(" 15.附加功能2：求最近公共祖先\n");
	printf(" 16.附加功能3：翻转二叉树\n");
	printf(" 17.附加功能4：实现线性表的文件形式保存\n");
	printf(" 18.附加功能5：从文件加载创建二叉树\n");
	printf("请输入您的选择：\n");
}