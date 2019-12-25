#include "gamestruct.h"

 //链表，用于记录得分
typedef struct LNode
{
    int score;
    struct LNode* next;
}LINKNODE;

//树节点，其数据域为链表
typedef struct Node
{
    char key[10];
    struct Node *left;
    struct Node *right;
    int height;
    LINKNODE score;
}BTNode;

//链表插入,保证为倒序（大到小）
void InsertLink(LINKNODE *p,int e)
{
    LINKNODE* q=NULL;
    LINKNODE* pre = p;
    while(pre->next!=NULL && pre->next->score > e)
        pre = pre->next;
    q = (LINKNODE*)malloc(sizeof(LINKNODE));
    q->score = e;
    q->next =pre->next;
    pre->next = q;
}


//递归计算树高

int height(struct Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

//创建新节点
BTNode* newNode(ITEM *x)
{
    char key[10];
    strcpy(key,x->user_name);
    struct Node* node = (BTNode*)malloc(sizeof(struct Node));
    strcpy(node->key , key);
    node->left = NULL;
    node->right = NULL;
	node->score.next = NULL;
    node->height = 1;
    InsertLink(&(node->score),x->score);
    return(node);
}
//右旋
BTNode* ll_rotate(BTNode* y)
{
    BTNode *x = y->left;
    y->left = x->right;
    x->right = y;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}
//左旋
BTNode* rr_rotate(BTNode* y)
{
    BTNode *x = y->right;
    y->right = x->left;
    x->left = y;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}
//计算平衡因子
int getBalance(BTNode* N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
//插入节点
BTNode* insert(BTNode* node, ITEM *x)
{

    char key[10];
    strcpy(key,x->user_name);
    if (node == NULL)
        return newNode(x);

    if (strcmp(key,node->key)<0)
        node->left = insert(node->left, x);
    else if (strcmp(key , node->key)>0)
        node->right = insert(node->right, x);
    else
        {
            InsertLink(&(node->score),x->score);
            return node;
        }

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);
    if (balance > 1 && strcmp(key,node->left->key)<0) //LL
        return ll_rotate(node);
    if (balance < -1 && strcmp(key , node->right->key)>0)     //RR
        return rr_rotate(node);
    if (balance > 1 && strcmp(key , node->left->key)>0)     //LR
    {
        node->left = rr_rotate(node->left);
        return ll_rotate(node);
    }
    if (balance < -1 && strcmp(key , node->right->key)<0)     //RL
    {
        node->right = ll_rotate(node->right);
        return rr_rotate(node);
    }
    return node;
}

//查找节点
struct Node* SearchTree(struct Node *root,char key[10])
{

    if(root == NULL)
        return root;
    if(strcmp(key,root->key)<0)
        return SearchTree(root->left,key);
    else if(strcmp(key,root->key)>0)
        return SearchTree(root->right,key);
    else return root;

}
//显示节点的名字和分数
void ShowResult(char name[10], BTNode* node)
{
	LINKNODE *p = NULL;
	int pos = 0;
	if (node == NULL)
		SearchResult("", -1, 0);
	else
	{
		p = node->score.next;
		while (p != NULL)
		{
			SearchResult(name, p->score, pos);
			pos++;
			//printf(" %s   %10d\n", name, p->score);
			p = p->next;
		}

	}
}

ITEM ranking_2048[list_n];
ITEM ranking_tetris[list_n];

/*
***主函数***
控制搜索流程
查找对象为宏定义的排行榜
输入：若输入为0，则查找2048的排行榜，若输入为1则查找tetris的排行榜

*/
void Search(int option)
{
    BTNode *root = NULL;
    BTNode* node;
    char name[list_n];

    int i;
    if(option == 0)
    {	
		resume_ranking(ranking_2048, 0);
        for(i=0; i<list_n; i++)
        {
            root = insert(root, &ranking_2048[i]);
        }
    }
    else if(option == 1)
    {
		resume_ranking(ranking_tetris, 1);
        for(i=0; i<list_n; i++)
        {
            root = insert(root, &ranking_tetris[i]);
        }
    }
	getname(name);
    node = SearchTree(root,name);
    ShowResult(name,node);
	Sleep(500);
	while (!_kbhit());
    getch();
}

