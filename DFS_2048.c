//************************************
//"dfs.c"
//max-min deep search to play 2048 game

#include "gamestruct.h"

#define NGIF  -999999
#define PGIF  999999
#define Tree_Size 4096

int game_board[SIZE][SIZE];
int initialboard[4][SIZE][SIZE];
int code[4] = {72,77,80,75};
int weight[SIZE][SIZE] = {{7,6,5,6},{14,12,10,5},{25,20,12,6},{30,25,14,7}};
int init_depth;


typedef struct
{
    int value;
    int parent;
}PTBox;

typedef struct
{
    PTBox nodes[Tree_Size];
    int node_num;
    int dir;
}PTree;


int create_maxnode();
int create_minnode();

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
    return count;int init_depth;
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
    //int value1,value2;
    int value = 0,count = 0,max = -99;
    for(i=0;i<SIZE;i++)
        for(j=0;j<SIZE;j++)
        {
            value += weight[i][j]*(game_board[i][j]);
        }
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
  /*  for(i=0;i<3;i++)
    {
        a = corner[x] + i * xy_change[x];
        b = corner[y] + i * xy_change[y];
        value += (get_exp(game_board[a+i*xy_change[x]][b+i*xy_change[y]]) - get_exp(game_board[a][b]));
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
            value +=  (5-j)*(value1 + value2);
        }
    }  */
    value = value - count * 2;
    return value;
}
int init_depth;

//*********************************//
//Function:init_PTree
//Type:int
//Inlet parameter:PTree *T
//Outlet parameter:0 (T.nodenum)
int init_PTree(PTree *T)
{
    if(!(T = (PTree*)malloc(sizeof(PTree))))
    {
        printf("FAILED TO CREATE CTREE!\n");
        exit(0);
    }
    return 0;
}


//*********************************//
//Function:delete_PTree
//Type:void
//Inlet parameter:PTree *T
//Outlet parameter:none
void delete_PTree(PTree *T)
{
    if(T != NULL)
        free(T);
}


//*********************************//
//Function:array_cpy
//         inout = 0: store initial array
//         inout = 1: get initial array
//Type:void
//Inlet parameter:int depth,int inout
//Outlet parameter:none
void array_cpy(int depth,int inout)
{
    if(inout==0)
        memcpy(initialboard[depth-1],game_board,SIZE*SIZE*sizeof(int));
    else if(inout==1)
        memcpy(game_board,initialboard[depth-1],SIZE*SIZE*sizeof(int));
}


//*********************************//
//Function:create_maxnode
//Type:int
//Inlet parameter:PTree *T,int current_node,int *dir,int depth,int alpha,int beta
//Outlet parameter:value
int create_maxnode(PTree *T,int current_node,int *dir,int depth,int alpha,int beta)
{
    int i;
    if(depth==0)
    {
        alpha = get_value();
    }
    else
    {
        array_cpy(depth,0);
        for(i=0;i<4;i++)
        {
            if(move_game(i,game_board) != -1)
            {
                T->node_num++;
                T->nodes[T->node_num].value = create_minnode(T,T->node_num,depth-1,alpha,beta);
                T->nodes[T->node_num].parent = current_node;

                if(T->nodes[T->node_num].value > alpha)
                {
                    if(depth==init_depth)
                        *dir = i;
                    alpha = T->nodes[T->node_num].value;
                }

            }
            array_cpy(depth,1);
        }
    }
    return alpha;
}


//*********************************//
//Function:create_minnode
//Type:int
//Inlet parameter:PTree *T,int current_node,int depth,int alpha,int beta
//Outlet parameter:value
int create_minnode(PTree *T,int current_node,int depth,int alpha,int beta)
{
    int i,j;
    if(depth==0)
    {
        beta = get_value();
    }
    else
    {
        for(i=0;i<4;i++)
        {
            for(j=0;j<4;j++)
            {
                if(game_board[i][j]==0)
                {
                    game_board[i][j] = 2;
                    T->node_num++;
                    T->nodes[T->node_num].value = create_maxnode(T,T->node_num,&(T->dir),depth-1,alpha,beta);
                    T->nodes[T->node_num].parent = current_node;

                    if(T->nodes[T->node_num].value < beta)
                        beta = T->nodes[T->node_num].value;


                    T->node_num++;
                    T->nodes[T->node_num].value = create_maxnode(T,T->node_num,&(T->dir),depth-1,alpha,beta);
                    T->nodes[T->node_num].parent = current_node;

                    if(T->nodes[T->node_num].value < beta)
                        beta = T->nodes[T->node_num].value;

                    game_board[i][j] = 0;
                }
            }
        }
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
    int depth = 3;
    int result_dir,value;
    PTree SearchTree;
    init_depth = depth;
    SearchTree.node_num = init_PTree(&SearchTree);
    memcpy(game_board,board,SIZE*SIZE*sizeof(int));
    value = create_maxnode(&SearchTree,0,&SearchTree.dir,depth,NGIF,PGIF);
    if(SearchTree.dir>4 || SearchTree.dir<0)   SearchTree.dir = rand()%4;
    result_dir = code[SearchTree.dir];      //get next step of the game
    delete_PTree(&SearchTree);
    return result_dir;
}

