#ifndef GAMESTRUCT_H_INCLUDED
#define GAMESTRUCT_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <math.h>
#include <windows.h>


#define STACK_INIT_SIZE 5
#define SIZE    4
#define list_n 10
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

//tetris_2048
#define WIDTH 6
#define HEIGHT 9
#define LENGTH 10

//DFS_2048
#define NGIF  -999999
#define PGIF  999999
#define Tree_Size 65536  //4*32*4*32*4


typedef struct
{
    int nb_x;
    int nb_y;
    int number;
    int initial_time;
}NEWBLOCK;


typedef struct
{
    int board[HEIGHT][WIDTH];
    unsigned int time;
    int score;
    NEWBLOCK nb;
}TERIS_2048;
//end

typedef struct game_2048
{
    int board[SIZE][SIZE];
    unsigned int time;
    int score;
}GAME_2048;


typedef struct
{
    int score;
    char user_name[list_n];
}ITEM;

typedef struct
{
	ITEM ranking2048[list_n];
	int length_2048;
}RANKINGLIST;

/*
ITEM ranking_2048[list_n];
ITEM ranking_tetris[list_n];
*/


//**********************//
//stack struct//
typedef struct game_stack
{
	struct game_2048 data;
    struct game_stack *next;
}GAME_STACK;

typedef struct
{
    int stack_size;
    GAME_STACK *next;
}GAME_STACK_HEAD;
//**********************//

/*
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
}PTree; */



#ifdef __cplusplus
extern "C" {
#endif

void InitGameStack(GAME_STACK_HEAD *S);
void PushGameStack(GAME_STACK_HEAD *S, struct game_2048 e);
void PopGameStack(GAME_STACK_HEAD *S, struct game_2048 *e);

void store_2048(struct game_2048 e);
void resume_2048(struct game_2048 *e);
void store_tetris(TERIS_2048 e);
void resume_tetris(TERIS_2048 *e);
void store_ranking(RANKINGLIST ranking[list_n], int gameflag);
void resume_ranking(ITEM array[list_n], int gameflag);


int move_game(int move_dir, int board[SIZE][SIZE]);


void sort_main(ITEM rank[list_n], int length, RANKINGLIST *ranking, int score, char user_name[list_n]);
void printlist(RANKINGLIST ranking, char *user_name, TERIS_2048* t);

void Search(int option);


int DFS(int board[SIZE][SIZE]);

#ifdef __cplusplus
}


#endif
void settext(int height, int weight, UINT color);
void printtext(LPCTSTR s, int left, int top, int right, int width);

int tetris(int option);


void main_2048(int  Whether_new, int player);


#endif // GAMESTRUCT_H_INCLUDED
