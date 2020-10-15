#ifndef GAMESTRUCT_H_INCLUDED
#define GAMESTRUCT_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
//#include <mmsystem.h>

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
    int time;
    int score;
    int max_num;
    NEWBLOCK nb;
}TERIS_2048;



typedef struct
{
    int board[SIZE][SIZE];
    int time;
    int score;
}GAME_2048;


typedef struct
{
    int score;
    char user_name[list_n];
}ITEM;

ITEM ranking[list_n];




//from "stack.c"
void InitGameStack();
void PushGameStack();
void PopGameStack();

//from "filewrite.c"
void store_2048();
void resume_2048();
void store_tetris();
void resume_tetris();
void store_ranking();
void resume_ranking();

//from "game_2048.c"
int move_game();
int gameOver();
int boardContains2048();
void printBoard();
void printHelp();
void insertNewNumber();

//from "dfs.c"
int DFS();



#endif // GAMESTRUCT_H_INCLUDED
