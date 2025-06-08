#define _CRT_SECURE_NO_WARNINGS
#include"functions.h"


status InitBiTree(BiTree* T)
{
	*T = (BiTree)malloc(sizeof(BiTNode));
	if (*T == NULL) {
		return OVERFLOW;  // �ڴ����ʧ��
	}
	// ��ʼ��ͷ�������
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
//�����������ݹ��㷨ִ�й����еݹ鹤��ջ��ԭ���ǵݹ��㷨��������һ��ָ��ջ�ݴ�����·���еĽ��ָ�롣
{
	BiTree stack[MAX_TREE_SIZE];  //����ָ��ջ
	int top = 0; //��ʼ��˳��ջ
	stack[top++] = T; //��ָ���ջ
	BiTree temp;
	while (top) {
		temp = stack[top - 1]; //��ȡջ��ָ��
		while (temp) {
			temp = temp->lchild; //�����ߵ���ͷ
			stack[top++] = temp; //�����ָ�����ν�ջ
		}
		top--; //��ָ��NULL��ջ������topΪջ��Ԫ�ص���һ��
		if (top != 0) {
			temp = stack[--top]; //·�������������ջ������
			visit(T);
			stack[top++] = temp->rchild; //�Һ���ָ���ջ
		}
	}
	return OK;

	//�Ľ��㷨��
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
//����������ȷ��ʵĽ�������Һ���ҲҪ�ȷ��ʣ������Ƚ��ȳ���������������һҪ��
{
	BiTree Queue[MAX_TREE_SIZE];
	int front = 0, rear = 0;
	BiTree cur = T;
	if (cur) Queue[rear++] = cur; //��ָ��ǿգ������
	while (front != rear) {
		cur = Queue[front++]; //���׽�����
		visit(cur);
		if (cur->lchild) Queue[rear++] = cur->lchild;
		if (cur->rchild) Queue[rear++] = cur->rchild;
	}
	return OK;
}

/* ��������������������ǵ��������������choice==1��
   ˵����
   - �� definition[*index].key == -1 ʱ����ʾ����������ñ�ǲ�����ɽ�㣩��
   - �� definition[*index].key == 0 ʱ����ʾ���������� *T ��Ϊ NULL�� */
status CreateBiTree_Recursive(BiTree* T, TElemType definition[], int* index) {
	if (definition[*index].key == -1) {  // ��ֹ���
		(*index)++;
		return OK;
	}
	if (definition[*index].key == 0) {   // ���������
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

/* ��������������ǰ����������й����������choice==2��
   ������
	   pre   : ǰ�����У�����Ϊ n��
	   in    : �������У�����Ϊ n��
	   n     : �����н������
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
	// �����������в��Ҹ����λ��
	for (i = 0; i < n; i++) {
		if (in[i].key == pre[0].key) break;
	}
	if (i == n) return ERROR;  // û���ҵ������ݴ���
	// i Ϊ�������������n-i-1 Ϊ�����������
	CreateBiTree_PreIn(&((*T)->lchild), pre + 1, in, i);
	CreateBiTree_PreIn(&((*T)->rchild), pre + 1 + i, in + i + 1, n - i - 1);
	return OK;
}

/* �������������ݺ�����������й����������choice==3��
   ������
	   post  : �������У�����Ϊ n��
	   in    : �������У�����Ϊ n��
	   n     : �����н������
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
	// �����������һ�����Ϊ��
	(*T)->data = post[n - 1];
	// �����������в��Ҹ���λ��
	for (i = 0; i < n; i++) {
		if (in[i].key == post[n - 1].key)
			break;
	}
	if (i == n) return ERROR;  // ���ݴ���
	// ��������СΪ i����������СΪ n - i - 1
	CreateBiTree_PostIn(&((*T)->lchild), post, in, i);
	CreateBiTree_PostIn(&((*T)->rchild), post + i, in + i + 1, n - i - 1);
	return OK;
}

/* ���������������������� choice ��ֵ������Ӧ��������
   choice==1: ���ݴ���������ǵ�����������д�����������
			 ��ʱ definition ����ĸ�ʽ�а�����������ǣ�key==0������ֹ��ǣ�key==-1����
   choice==2: ����ǰ��+�������н�����������
			 ����Լ����definition[0].key �������� n��
			 ���������� n ��Ԫ��Ϊǰ�����У�
			 ������ n ��Ԫ��Ϊ�������С�
   choice==3: ���ݺ���+�������н�����������
			 ����Լ��ͬ�ϣ�ֻ����ǰһ����Ϊ�������С�
*/
status CreateBiTree(BiTree* T, TElemType definition[], int choice) {
	if (choice == 1) {
		int index = 0;
		return CreateBiTree_Recursive(T, definition, &index);
	}
	else if (choice == 2) {
		// ��Լ����definition[0].key Ϊ����� n��
		// ����ǰ n ��Ϊǰ�����У������� n ��Ϊ��������
		int n = definition[0].key;
		return CreateBiTree_PreIn(T, &definition[1], &definition[1 + n], n);
	}
	else if (choice == 3) {
		// ͬ����definition[0].key Ϊ����� n��
		// ����ǰ n ��Ϊ�������У������� n ��Ϊ��������
		int n = definition[0].key;
		return CreateBiTree_PostIn(T, &definition[1], &definition[1 + n], n);
	}
	else {
		return ERROR;  // ��֧�ֵ����뷽ʽ
	}
}

status ClearBiTree(BiTree* T)
//��������T�ÿգ����ͷ����н��Ŀռ�
{
	// ���T����ΪNULL���򷵻ش���
	if (T == NULL)
		return ERROR;

	// �����������Ϊ�գ��ݹ������������
	if (*T != NULL) {
		ClearBiTree(&((*T)->lchild));  // ���������
		ClearBiTree(&((*T)->rchild));  // ���������

		free(*T); // �ͷŵ�ǰ�ڵ���ڴ棬���ÿ�ָ�룬����Ұָ�����
		*T = NULL;
	}
	return OK;
}
int BiTreeDepth(BiTree T)
//�������T��Ȳ��������ֵ
{
	if (T == NULL) return 0;
	else {
		int left_depth = BiTreeDepth(T->lchild);
		int right_depth = BiTreeDepth(T->rchild);
		// ��ǰ�������Ϊ���������нϴ���+1
		return (left_depth > right_depth ? left_depth : right_depth) + 1;
	}
}
BiTNode* LocateNode(BiTree T, KeyType e)
//e�Ǻ�T�н��ؼ���������ͬ�ĸ���ֵ������e���ҷ��������Ľ�㣬���ظý��ָ�룬���޹ؼ���Ϊe�Ľ�㣬����NULL��
{
	if (T == NULL) return NULL;
	if (T->data.key == e) return T;
	BiTNode* p = LocateNode(T->lchild, e);// �����������в���
	if (p != NULL)
		return p;  // �ҵ��򷵻�
	
	return LocateNode(T->rchild, e); // ����������δ�ҵ�����������������в���
}
status Assign(BiTree* T, KeyType e, TElemType value)
/*e�Ǻ�T�н��ؼ���������ͬ�ĸ���ֵ�����ҽ��ؼ��ֵ���e�Ľ�㣬���ý��ֵ�޸ĳ�value��
����OK��Ҫ����ؼ��ֱ���Ψһ�ԣ����������ʧ�ܣ�����ERROR��*/
{
	BiTNode* p = LocateNode(*T, e);
	if (p == NULL) return ERROR;
	// ��������ĵĹؼ��ֲ�����ԭ���Ĺؼ��֣������������Ƿ��Ѵ��ڸ��¹ؼ���
	if (value.key != p->data.key) {
		BiTNode* q = LocateNode(*T, value.key);
		// ����ҵ��Ľ�㲻�� p ����˵���¹ؼ����Ѵ���
		if (q != NULL)
			return ERROR;
	}
	p->data = value;
	return OK;
}
BiTNode* GetSibling(BiTree T, KeyType e)
/*e�Ǻ�T�н��ؼ���������ͬ�ĸ���ֵ�����ҽ��ؼ��ֵ���e�Ľ����ֵܽ�㣬�������ֵܽ��ָ�롣�������ʧ�ܣ�����NULL��*/
{
	if (T == NULL) return NULL;

	// ����������еĽ�������������򷵻�������ָ��
	if (T->lchild != NULL && T->lchild->data.key == e)
		return T->rchild;  // �����������򷵻�NULL

	// ����������еĽ�������������򷵻�������ָ��
	if (T->rchild != NULL && T->rchild->data.key == e)
		return T->lchild;  // �����������򷵻�NULL

	// �����������еݹ����
	BiTNode* sibling = GetSibling(T->lchild, e);
	if (sibling != NULL)
		return sibling;

	// ��������û�У������������еݹ����
	return GetSibling(T->rchild, e);
}
status InsertNode(BiTree* T, KeyType e, int LR, TElemType c)
/*e�Ǻ�T�н��ؼ���������ͬ�ĸ���ֵ��LRΪ0��1��c�Ǵ������㣻����LRΪ0����1��������c��T�У�
��Ϊ�ؼ���Ϊe�Ľ�������Һ��ӽ�㣬���e��ԭ������������������Ϊ���c��������������OK�������
��ʧ�ܣ�����ERROR�� �ر�أ���LRΪ-1ʱ����Ϊ�������룬ԭ�������Ϊc����������*/
{
	if (T == NULL) return ERROR;

	/* ���������в����Ƿ��Ѵ��ڴ�������c�Ĺؼ��֣��ؼ��ֱ���Ψһ */
	if (LocateNode(*T, c.key) != NULL) {
		return ERROR;  // �ظ��ؼ��֣�����ʧ��
	}

	// �ر�أ�LR Ϊ -1 ʱ��Ϊ�������룬�½�����������ԭ��
	if (LR == -1) {
		BiTNode* newNode = (BiTNode*)malloc(sizeof(BiTNode));
		if (newNode == NULL)
			return ERROR;
		newNode->data = c;
		newNode->lchild = NULL;
		newNode->rchild = *T;  // ԭ�������Ϊ�½���������
		*T = newNode;          // �޸ĸ�ָ��
		return OK;
	}

	// LR Ϊ 0 �� 1 ��������Ȳ��ҹؼ���Ϊ e �Ľ��
	BiTNode* parent = LocateNode(*T, e);
	if (parent == NULL)
		return ERROR;

	BiTNode* newNode = (BiTNode*)malloc(sizeof(BiTNode));
	if (newNode == NULL)
		return ERROR;
	newNode->data = c;
	newNode->lchild = NULL;   // Ĭ���½���������Ϊ��

	if (LR == 0) {
		// ���½�����Ϊ parent �����ӣ��½�������������ԭ����������
		newNode->rchild = parent->lchild;
		parent->lchild = newNode;
	}
	else if (LR == 1) {
		// ���½�����Ϊ parent ���Һ��ӣ��½�������������ԭ����������
		newNode->rchild = parent->rchild;
		parent->rchild = newNode;
	}
	else {
		// ��� LR ���� -1��0 �� 1����Ϊ�Ƿ�����
		free(newNode);
		return ERROR;
	}
	return OK;
}
BiTNode* FindNodeWithParent(BiTree T, KeyType e, BiTNode* parent, BiTNode** outParent)
/*�������������ҹؼ���Ϊ e �Ľ�㣬ͬʱ���ظý��ĸ���㡣
 *����˵����
 *   T        : ��ǰ�����ĸ����
 *   e        : Ҫ���ҵĹؼ���
 *   parent   : ��ǰ���ĸ���㣨�ڵݹ�����д��룩
 *   outParent: ������������������ҵ����ĸ���㣨�����Ϊ������ΪNULL��
 */
{
	if (T == NULL) return NULL;
	if (T->data.key == e) {
		*outParent = parent;
		return T;
	}
	BiTNode* found = FindNodeWithParent(T->lchild, e, T, outParent);  //���������������������ң��Ҳ����ٵ�������������
	if (found != NULL) return found;
	return FindNodeWithParent(T->rchild, e, T, outParent);
}
status DeleteNode(BiTree* T, KeyType e)
/*e�Ǻ�T�н��ؼ���������ͬ�ĸ���ֵ��ɾ��T�йؼ���Ϊe�Ľ�㣻ͬʱ�����ݸñ�ɾ���ĶȽ������ۣ�
	1.��ؼ���Ϊe�Ľ���Ϊ0��ɾ�����ɣ�
	2.��ؼ���Ϊe�Ľ���Ϊ1���ùؼ���Ϊe�Ľ�㺢�Ӵ��汻ɾ����eλ�ã�
	3.��ؼ���Ϊe�Ľ���Ϊ2����e�������������ΪLC�����汻ɾ����eλ�ã���e�������������ΪRC����ΪLC�����ҽڵ����������
�ɹ�ɾ�����󷵻�OK�����򷵻�ERROR��*/
{
	if (T == NULL || *T == NULL) return ERROR;

	BiTNode* parent = NULL;
	BiTNode* p = FindNodeWithParent(*T, e, NULL, &parent);
	if (p == NULL) return ERROR; //δ�ҵ��ؼ���Ϊe�Ľ��

	if (p->lchild == NULL && p->rchild == NULL) {  //���1����ɾ���ΪҶ��㣨��Ϊ0��
		if (parent == NULL) *T = NULL; //��ɾ���Ϊ�����
		else {
			if (parent->lchild == p) parent->lchild = NULL;
			else parent->rchild = NULL;
		}
		free(p);
		return OK;
	}
	else if (p->lchild == NULL || p->rchild == NULL) {  //���2����ɾ����Ϊ1
		BiTNode* child = (p->lchild != NULL) ? p->lchild : p->rchild;
		if (parent == NULL) *T = child; //��ɾ���Ϊ�����
		else {
			if (parent->lchild == p) parent->lchild = child;
			else parent->rchild = child;
		}
		free(p);
		return OK;
	}
	else {  //���3����ɾ����Ϊ2
		// �� LC Ϊ p ����������RC Ϊ p ��������
		BiTNode* LC = p->lchild;
		BiTNode* RC = p->rchild;
		// �� LC ���ҵ����Ҳ�Ľ��
		BiTNode* mostright = LC;
		while (mostright->rchild != NULL)
			mostright = mostright->rchild;
		// �� RC �ӵ� mostright ���Һ�����
		mostright->rchild = RC;
		// �� LC ���� p �ڸ���㴦��λ��
		if (parent == NULL) {  // p Ϊ�����
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
	if (T == NULL) return ERROR;  // ���������ǿ�ָ�룬�򷵻ش���

	if (*T != NULL) {
		// �������������������������ú������
		DestroyBiTree(&((*T)->lchild));
		DestroyBiTree(&((*T)->rchild));
		// �ͷŵ�ǰ���
		free(*T);
		*T = NULL;  // ��ֹ����ָ��
	}
	return OK;
}
status BiTreeEmpty(BiTree T) 
//�������п�
{
	return (T == NULL) ? TRUE : FALSE;
}

int MaxPathSum(BiTree T) 
//�ú������شӸ��ڵ��������һҶ�ӽ���·���У������ data.key ֵ֮�͵����ֵ��
{
	if (T == NULL) return ERROR;

	// �����Ҷ�ӽڵ㣬ֱ�ӷ��ظý��� key ֵ
	if (T->lchild == NULL && T->rchild == NULL) return T->data.key;

	// ���ֻ��һ���������ڣ���ؾ��÷�֧
	if (T->lchild == NULL)
		return T->data.key + MaxPathSum(T->rchild);
	if (T->rchild == NULL)
		return T->data.key + MaxPathSum(T->lchild);

	// ���߶����ڣ�ȡ�����
	int leftSum = MaxPathSum(T->lchild);
	int rightSum = MaxPathSum(T->rchild);
	return T->data.key + (leftSum > rightSum ? leftSum : rightSum);
}
BiTNode* LowestCommonAncestor(BiTree T, KeyType e1, KeyType e2)
//����������ȣ��������������������ؼ��֣�e1 �� e2�����ڽ�������������ȡ�
{
	if (T == NULL) return NULL;

	if (LocateNode(T, e1) == NULL || LocateNode(T, e2) == NULL) return NULL;

	// ����ǰ������� e1 �� e2���򷵻ص�ǰ���
	if (T->data.key == e1 || T->data.key == e2) return T;

	BiTree left = LowestCommonAncestor(T->lchild, e1, e2); 
	BiTree right = LowestCommonAncestor(T->rchild, e1, e2);
	/*
	���� 1��Ŀ��ڵ�����ڶ�Ӧ��������
			���T->lchild�������м�û��e1Ҳû��e2���ݹ�������һ·�ߵ��ף����ֿ����������T==NULL�����̷���NULL�����left����NULL��
		���Ƶأ����T->rchild�������м�û��e1Ҳû��e2����rightҲ����NULL��
	���� 2����һ�������ҵ�Ŀ��ڵ㣨��ò��Ѿ�������������ڵ�����������ȣ�
		   ���磺��T�����������ҵ���e1��e2����ʹ����������ͬʱ��������Ŀ�꣬�����ǵ�����������Ⱦ����������У�����������صĽ�㣩��
		��ôleft�����ظ÷ǿ�ָ�롣���������������δ�ҵ�Ŀ�꣬��right == NULL����֮�������������ҵ���Ŀ�꣨����ĳһ���Ѿ��γ��˾ֲ���
		�����ȣ������������Ҳ�������right���طǿգ���left == NULL��
	���� 3�������������ҵ���Ŀ��
		   ��T����������������e1����������������e2�������෴������ʱleft != NULL��right != NULL��˵��e1��e2�ֱ�λ�ڵ�ǰ�ڵ�T������
		������ͬ������ô��ǰ�ڵ�T����������Ŀ�������������ȡ�(��ʱ�ݹ���÷ֱ𷵻ص���Ŀ��ڵ㱾�����Ѿ���ĳ���������ɵݹ��жϳ�
		�ľֲ����ȡ���
	*/

	// ��������������ҵ���Ŀ�꣬��ǰ��㼴Ϊ�����������
	if (left != NULL && right != NULL) return T;

	// ���򽫷ǿյ�һ�����ϻش�������Ҷ�ӽ�㣬���Ҷ�ΪNULL�����з���NULL
	return left != NULL ? left : right;
}
void InvertTree(BiTree T) 
//��������ת�����������н���������������
{
	if (T == NULL) return;

	// ������������
	BiTree temp = T->lchild;
	T->lchild = T->rchild;
	T->rchild = temp;

	// �ݹ鷭ת��������
	InvertTree(T->lchild);
	InvertTree(T->rchild);
}
// �����������������д�루���ձ�׼��ʽ�������Ч�ڵ���� key �� others����������� "0 null"��
void SaveBiTree_PreOrder(BiTree T, FILE* fp)
{
	if (T == NULL) {
		// ���������
		fprintf(fp, "0 null ");
		return;
	}
	// �����ǰ��Ч��㣺�ؼ�����������Ϣ
	fprintf(fp, "%d %s ", T->data.key, T->data.others);
	// �ݹ�д����������������
	SaveBiTree_PreOrder(T->lchild, fp);
	SaveBiTree_PreOrder(T->rchild, fp);
}
status SaveBiTree(BiTree T, char FileName[])
{
	FILE* fp = fopen(FileName, "w");
	if (fp == NULL)
		return ERROR;
	// �������д����������ļ������������ "0 null"
	SaveBiTree_PreOrder(T, fp);
	// д�������ǣ�-1 null
	fprintf(fp, "-1 null ");
	fclose(fp);
	return OK;
}
status LoadBiTree(BiTree* T, char FileName[])
{
	FILE* fp = fopen(FileName, "r");
	if (fp == NULL)
		return ERROR;

	// ʹ�� definition ���������������У�����ı�׼�뱣��ʱһ�£�
	// ��Ч��㣺key > 0����Ӧ���ַ�������������key Ϊ0�����������keyΪ-1
	TElemType definition[MAX_TREE_SIZE];
	int count = 0;
	char token[20];

	// ѭ�������ǣ�ÿ���ȶ� key���ַ�����ʽ����ת��Ϊ����
	while (fscanf(fp, "%s", token) == 1)
	{
		int k = atoi(token);
		if (k == -1) {  // �������������ֹͣ��ȡ
			break;
		}
		// ����ǰ�����Ϣ���浽 definition ������
		definition[count].key = k;
		fscanf(fp, "%s", token); // ��ȡ��Ӧ��others�ַ���
		strcpy(definition[count].others, token);
		count++;
	}
	fclose(fp);

	int index = 0;
	// ���ø������������� definition ���鹹��������
	return CreateBiTree_Recursive(T, definition, &index);
}

/*�����������*/
status InitBiTreeManager(BiTreeManager* manager) 
{
	if (manager == NULL) return ERROR;
	manager->count = 0;
	return OK;
}
status AddBiTree(BiTreeManager* manager, char name[], BiTree tree)
{
	if (manager == NULL) return ERROR;
	if (manager->count >= MAX_BTREES) return OVERFLOW;  // �������ռ���

	//����Ƿ��Ѵ�����ͬ���ƵĶ�����
	for (int i = 0; i < manager->count; i++) {
		if (strcmp(manager->items[i].name, name) == 0) {
			return ERROR;  // �����������ظ����
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
	if (pos == -1) return ERROR; // û���ҵ�ָ�����ƵĶ�����

	// ���ٸö�����
	if(DestroyBiTree(&(manager->items[pos].tree))==ERROR) return ERROR;

	// �������Ԫ������ǰ�ƣ������ȱ
	for (int i = pos; i < manager->count - 1; i++) {
		manager->items[i] = manager->items[i + 1];
	}
	manager->count--;
	return OK;
}
void ListBiTrees(BiTreeManager* manager)
//�г������е����ж�����
{
	if (manager == NULL) return;
	printf("��ǰ����Ķ������б�\n");
	for (int i = 0; i < manager->count; i++) {
		printf("��ţ�%d, ���ƣ�%s\n", i + 1, manager->items[i].name);
	}
}
BiTree GetBiTree(BiTreeManager* manager, char name[]) 
//���ݶ��������Ʒ��ض�����ָ�룬���û�ҵ��򷵻� NULL
{
	if (manager == NULL) return NULL;
	for (int i = 0; i < manager->count; i++) {
		if (strcmp(manager->items[i].name, name) == 0) {
			return manager->items[i].tree;
		}
	}
	return NULL;
}

/*�˵�����*/
void PrintMenu()
{
	printf("\n  -------��������ʾϵͳ-------  \n");
	printf("**************************************\n");
	printf("  0.�˳���ʾϵͳ\n");
	printf("  1.��������������\n");
	printf("  2.���ٵ�ǰ������\n");
	printf("  3.��յ�ǰ������\n");
	printf("  4.�жϵ�ǰ�������Ƿ�Ϊ��\n");
	printf("  5.��ȡ��ǰ�����������\n");
	printf("  6.���ҹؼ���Ϊe�Ľ��\n");
	printf("  7.���ؼ���Ϊe�Ľ�㸳ֵ\n");
	printf("  8.��ùؼ���Ϊe�Ľ����ֵܽ��\n");
	printf("  9.������\n");
	printf(" 10.ɾ�����\n");
	printf(" 11.ǰ�����\n");
	printf(" 12.�������\n");
	printf(" 13.�������\n");
	printf(" 14.�������\n");
	printf(" 15.���ӹ���1�������·����\n");
	printf(" 16.���ӹ���2���������������\n");
	printf(" 17.���ӹ���3����ת������\n");
	printf(" 18.���ӹ���4��ʵ�����Ա���ļ���ʽ����\n");
	printf(" 19.���ӹ���5�����ļ����ش���������\n");
	printf(" 20.���ӹ���6�������������\n");
	printf("**************************************\n");
	printf("���������ѡ��: ");
}
void PrintSubMenu()
{
	printf("\n--- �������������ϵͳ ---\n");
	printf("  1.�����µĶ�����\n");
	printf("  2.��ʾ���ж�����״̬\n");
	printf("  3.ɾ��ĳ��������\n");
	printf("  4.��������ĳ��������\n");
	printf("  0.�������˵�\n");
	printf("���������ѡ��: ");
}
void PrintSubSubMenu(char* listname)
{
	printf("\n-----���������� \"%s\" -----\n", listname);
	printf("  0.�����Ӳ˵�\n");
	printf("  1.���ٶ�����\n");
	printf("  2.��ն�����\n");
	printf("  3.�������п�\n");
	printf("  4.��ȡ���������\n");
	printf("  5.���ҹؼ���Ϊe�Ľ��\n");
	printf("  6.���ؼ���Ϊe�Ľ�㸳ֵ\n");
	printf("  7.��ùؼ���Ϊe�Ľ����ֵܽ��\n");
	printf("  8.������\n");
	printf("  9.ɾ�����\n");
	printf(" 10.ǰ�����\n");
	printf(" 11.�������\n");
	printf(" 12.�������\n");
	printf(" 13.�������\n");
	printf(" 14.���ӹ���1�������·����\n");
	printf(" 15.���ӹ���2���������������\n");
	printf(" 16.���ӹ���3����ת������\n");
	printf(" 17.���ӹ���4��ʵ�����Ա���ļ���ʽ����\n");
	printf(" 18.���ӹ���5�����ļ����ش���������\n");
	printf("����������ѡ��\n");
}