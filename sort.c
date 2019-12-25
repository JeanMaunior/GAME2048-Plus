#include <stdio.h>
#include <stdlib.h>
#include "gamestruct.h"

#define N 11
typedef struct bitree
{
    ITEM data;
    struct bitree *lchild;
    struct bitree *rchild;
}BT;
BT* search(BT *root,ITEM data)
{
    BT *p=root;
    BT *f=NULL;
    while(p!=NULL&&p->data.score!=data.score)
    {
        if(p->data.score<data.score)
        {
            f=p;
            p=p->lchild;
        }
        else
        {
            f=p;
            p=p->rchild;
        }
    }
    if(p==NULL)
        return f;
    else
        return p;
}
BT* create(BT *root,ITEM data)
{
    BT *s=NULL,*f=NULL,*p=NULL;
    s=(BT*)malloc(sizeof(BT));
    if(s==NULL)
    {
        exit(0);
    }
    s->data.score=data.score;
    strcpy(s->data.user_name,data.user_name);
    s->lchild=s->rchild=NULL;
    if(root==NULL)
    {
        root=s;
    }
    else
    {
        f=search(root,data);
        if(f->data.score<data.score)
        {
            f->lchild=s;
        }
        else if(f->data.score==data.score)
        {
            p=f->lchild;
            f->lchild=s;
            s->lchild=p;
        }
        else
        {
            f->rchild=s;
        }
    }
    return root;
}
/*void inorder(BT *root, RANKINGLIST ranking)
{
    int i = 0;
    if(root!=NULL)
    {
        inorder(root->lchild,ranking);
        ranking.ranking2048[i].score = root->data.score;
        strcpy(ranking.ranking2048[i].user_name,root->data.user_name);
        printf("ranking1:%d  %s\n",ranking.ranking2048[i].score,ranking.ranking2048[i].user_name);
        i++;
        inorder(root->rchild,ranking);
    }
}*/
int i = 0;
void inorder(BT *root, RANKINGLIST *ranking)
{

    if(root!=NULL)
    {

            inorder(root->lchild,ranking);
                    if(i < list_n)
            {
            ranking->ranking2048[i].score = root->data.score;
            strcpy(ranking->ranking2048[i].user_name,root->data.user_name);
            i++;
            }
            inorder(root->rchild,ranking);

    }
}
/*void del(BT *root,int d)
{
    BT *p=NULL,*s=NULL,*f=root;
    p=search(root,d);
    while(f->rchild!=p&&f->lchild!=p)
    {
        if(f->data.score>=d)
            f=f->lchild;
        else
            f=f->rchild;
    }
    if(!p->rchild)
    {
        f->lchild=p->lchild;
        free(p);
    }
    else if(!p->lchild)
    {
        f->rchild=p->rchild;
        free(p);
    }
    else
    {
        s=p->lchild;
        while(s->rchild)
        {
            s=s->rchild;
        }
        f->lchild=p->lchild;
        s->rchild=p->rchild;
    }
}*/
void sort_main(ITEM rank[list_n], int length, RANKINGLIST *ranking, int score, char user_name[list_n])
{
	int j;
	ITEM a[list_n + 1];
	BT *root = (BT*)malloc(sizeof(BT));
	root = NULL;
	for (j = 0; j < list_n; j++)
	{
		a[j] = rank[j];
	}
	a[j].score = score;
	strcpy(a[j].user_name, user_name);
	for (j = 0; j < list_n + 1; j++)
	{
		root = create(root, a[j]);
	}
	inorder(root, ranking);
}
