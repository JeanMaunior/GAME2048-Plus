//************************************
//"dfs.c"
//max-min deep search to play 2048 game

#include "gamestruct.h"

#define NGIF  -9999
#define PGIF  9999


int game_board[SIZE][SIZE];
int initialboard[SIZE][SIZE];




//*********************//
//max-min tree strcut
typedef struct MaxNode
{
    int dir;
    int value;
    int alpha;
    int beta;
    struct MinNode *next[SIZE];
}MaxNode;

typedef struct minnode
{
    int value;
    int alpha;
    int beta;
    struct MaxNode *next[2*SIZE*SIZE];
}MinNode;
//**********************//


//*********************************//
//Function:get_exp
//         to get the experiment of a number
//Type:int
//Inlet parameter:int x (the number to calculate)
//Outlet parameter:count (the experiment of the number)
int get_exp(int x)
{
    int count = 1,i = 2;
    if(x==0)
        count = 0;
    else
    {
        while(i < x)
        {
            i *= 2;
            count++;
        }
    }
    return count;
}


//*********************************//
//Function:get_value
//         access the value of current game board
//Type:int
//Inlet parameter:void,(global variable) board[SIZE][SIZE]  (game board of 2048)
//Outlet parameter:value (the accessed value of the board)
int get_value(void)
{
    int corner[SIZE] = {0,0,3,3};         //to find the corner near the max number
    int xy_change[SIZE] = {1,1,-1,-1};    //change nearly x¡¢y to calculate the value
    int a,b,x,y,i,j;
    int value = 0,value1,value2,count = 0,max = -99;
    for(i=0;i<SIZE;i++)             //to find the (x,y) of the max number
    {
        for(j=0;j<SIZE;j++)
        {
            if(game_board[i][j] != 0)
                count++;
            if(game_board[i][j] > max)
            {
                x = i;
                y = j;
                max = game_board[i][j];
            }
        }
    }
    for(i=0;i<3;i++)
    {
        a = corner[x] + i * xy_change[x];
        b = corner[y] + i * xy_change[y];
        value += 2*(get_exp(game_board[a+i*xy_change[x]][b+i*xy_change[y]]) - get_exp(game_board[a][b]));
        if(i==2 || i==3)
        {
            value1 = get_exp(game_board[a-xy_change[x]][b]) - get_exp(game_board[a][b]);
            value2 = get_exp(game_board[a][b-xy_change[y]]) - get_exp(game_board[a][b]);
            value +=  (value1 + value2);
        }
        for(j=0;j<3-i;j++)
        {
            value1 = get_exp(game_board[a+j*xy_change[x]][b]) - get_exp(game_board[a+(j+1)*xy_change[x]][b]);
            value2 = get_exp(game_board[a][b+j*xy_change[y]]) - get_exp(game_board[a][b+(j+1)*xy_change[y]]);
            value +=  (value1 + value2);
        }
    }
    value = value *3 - count * 2;
    return value;
}


//*********************************//
//Function:delete_maxnode
//Type:void
//Inlet parameter:MaxNode *T
//Outlet parameter:none
void delete_maxnode(MaxNode *T)
{
    int i;
    MaxNode *p = T;
    MinNode *pnext = NULL;
    if(p != NULL)
    {
        for(i=0;i<SIZE;i++)
        {
            if(p->next[i] != NULL)
            {
                pnext = p->next[i];
                delete_minnode(pnext);
            }
        }
        free(p);
    }
}


//*********************************//
//Function:delete_minnode
//Type:void
//Inlet parameter:MinNode *T
//Outlet parameter:none
void delete_minnode(MinNode *T)
{
    int i,j;
    MinNode *p = T;
    MaxNode *pnext = NULL;
    if(p != NULL)
    {
        for(i=0;i<SIZE;i++)
        {
            for(j=0;j<SIZE;j++)
            {
                if(p->next[(i*4+j)*2] != NULL)
                {
                    pnext = p->next[(i*4+j)*2];
                    delete_maxnode(pnext);
                }
                if(p->next[(i*4+j)*2+1])
                {
                    pnext = p->next[(i*4+j)*2+1];
                    delete_maxnode(pnext);
                }
            }
        }
        free(p);
    }
}


//*********************************//
//Function:create_maxnode
//Type:int
//Inlet parameter:MaxNode *T,int *dir,int depth,int alpha,int beta
//Outlet parameter:value
int create_maxnode(MaxNode *T,int *dir,int depth,int alpha,int beta)
{
    int i;
    if(depth==0)
    {
        alpha = get_value();
    }
    else
    {
        depth--;
        memcpy(initialboard,game_board,16*sizeof(int));
        if(!(T = (MaxNode*)malloc(sizeof(MaxNode))))
        {
            printf("FAILED TO CREATE MAX NODE!\n");
            exit(0);
        }
        for(i=0;i<4;i++)
        {
            if(move_game(i,game_board) != -1)
            {
                T->value = create_minnode(T->next[i],depth,alpha,beta);
                if(T->value > alpha)
                {
                    *dir = i;
                    alpha = T->value;
                }
                else
                    //delete_maxnode(T->next[i]);
                    T->next[i] = NULL;
                memcpy(game_board,initialboard,SIZE*SIZE*sizeof(int));
            }
            else
            {
                T->next[i] = NULL;
            }
        }
        T->value = alpha;
    }
    return alpha;
}


//*********************************//
//Function:create_minnode
//Type:int
//Inlet parameter:MinNode *T,int depth,int alpha,int beta
//Outlet parameter:value
int create_minnode(MinNode *T,int depth,int alpha,int beta)
{
    int i,j;
    int initialboard[SIZE][SIZE];
    if(depth==0)
    {
        beta = get_value();
    }
    else
    {
        depth--;
        if(!(T = (MinNode*)malloc(sizeof(MinNode))))
        {
            printf("FAILED TO CREATE MIN NODE!\n");
            exit(0);
        }
        for(i=0;i<4;i++)
        {
            for(j=0;j<4;j++)
            {
                if(game_board[i][j]==0)
                {
                    game_board[i][j] = 2;
                    T->value = create_maxnode(T->next[(i*4+j)*2],&T->next[(i*4+j)*2]->dir,depth,alpha,beta);
                    if(T->value < beta)
                        beta = T->value;
                    else
                        //delete_maxnode(T->next[(i*4+j)*2]);
                        T->next[(i*4+j)*2] = NULL;

                    game_board[i][j] = 4;
                    T->value = create_maxnode(T->next[(i*4+j)*2+1],&T->next[(i*4+j)*2+1]->dir,depth,alpha,beta);
                    if(T->value < beta)
                        beta = T->value;
                    else
                        //delete_maxnode(T->next[(i*4+j)*2+1]);
                        T->next[(i*4+j)*2+1] = NULL;

                    game_board[i][j] = 0;
                }
                else
                {
                    T->next[(i*4+j)*2] = NULL;
                    T->next[(i*4+j)*2+1] = NULL;
                }
            }

        }
        T->value = beta;
    }
    return beta;
}


//*********************************//
//Function:DFS
//         deep first search to find a choose of next step in game 2048
//Type:int
//Inlet parameter:int board[SIZE][SIZE]
//Outlet parameter:code[SearchTree.dir] (scan code of up|right|down|left on keyboard)
int DFS(int board[SIZE][SIZE])
{
    int code[4] = {72,77,80,75};
    int value;
    MaxNode SearchTree;
    memcpy(game_board,board,SIZE*SIZE*sizeof(int));
    value = create_maxnode(&SearchTree,&SearchTree.dir,2,NGIF,PGIF);
    return code[SearchTree.dir];
}

