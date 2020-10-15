//*************************************
//"filewrite.c"
//store the game state and resume it the next time you open the game

#include "gamestruct.h"


//*********************************//
//Function:store_2048
//Type:void
//Inlet parameter:GAME_2048 e
//Outlet parameter:none
void store_2048(GAME_2048 e)
{
    int i,j;
    FILE *fp;
    if((fp = fopen("store_2048.txt","w")) == NULL)
    {
        printf("FAILED TO CREATE THE 2048 GAME FILE!\n");
        exit(0);
    }
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
            fprintf(fp,"%6d",e.board[i][j]);
        fprintf(fp,"\n");
    }
    fprintf(fp,"%10d\n",e.time);
    fprintf(fp,"%10d\n",e.score);
    fclose(fp);
}


//*********************************//
//Function:resume_2048
//Type:void
//Inlet parameter:GAME_2048 *e
//Outlet parameter:none
void resume_2048(GAME_2048 *e)
{
    int i,j;
    FILE *fp;
    if((fp = fopen("store_2048.txt","r")) == NULL)
    {
        printf("FAILED TO OPEN THE 2048 GAME FILE!\n");
        exit(0);
    }
    rewind(fp);
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++){
            fscanf(fp," %6d",&e->board[i][j]);
        }
        printf("\n");
    }
    fscanf(fp," %10d",&e->time);
    fscanf(fp," %10d",&e->score);
    fclose(fp);
}


//*********************************//
//Function:store_tetris
//Type:void
//Inlet parameter:TERIS_2048 e
//Outlet parameter:none
void store_tetris(TERIS_2048 e)
{
    int i,j;
    FILE *fp;
    if((fp = fopen("store_tetris.txt","w")) == NULL)
    {
        printf("FAILED TO CREATE THE TETRIS GAME FILE!\n");
        exit(0);
    }
    for(i=0;i<HEIGHT;i++)
    {
        for(j=0;j<WIDTH;j++)
            fprintf(fp,"%6d",e.board[i][j]);
        fprintf(fp,"\n");
    }
    fprintf(fp,"%10d\n",e.time);
    fprintf(fp,"%10d\n",e.score);
    fprintf(fp,"%10d\n",e.max_num);
    fclose(fp);
}


//*********************************//
//Function:resume_tetris
//Type:void
//Inlet parameter:TERIS_2048 *e
//Outlet parameter:none
void resume_tetris(TERIS_2048 *e)
{
    int i,j;
    FILE *fp;
    if((fp = fopen("store_tetris.txt","r")) == NULL)
    {
        printf("FAILED TO OPEN THE TETRIS GAME FILE!\n");
        exit(0);
    }
    rewind(fp);
    for(i=0;i<HEIGHT;i++)
    {
        for(j=0;j<WIDTH;j++){
            fscanf(fp," %6d",&e->board[i][j]);
        }
        printf("\n");
    }
    fscanf(fp," %10d",&e->time);
    fscanf(fp," %10d",&e->score);
    fscanf(fp," %10d",&e->max_num);
    fclose(fp);
}


//*********************************//
//Function:store_ranking
//         gameflag = 0 :2048
//         gameflag = 1 :tetris
//Type:void
//Inlet parameter:ITEM ranking[list_n],int gameflag
//Outlet parameter:none
void store_ranking(ITEM ranking[list_n],int gameflag)
{
    int i;
    FILE *fp;
    if(gameflag==0)
    {
        if((fp = fopen("store_2048_ranking.txt","w")) == NULL)
        {
            printf("FAILED TO CREATE THE 2048 RANKING FILE!\n");
            exit(0);
        }
    }
    else if(gameflag==1)
    {
        if((fp = fopen("store_tetris_ranking.txt","w")) == NULL)
        {
            printf("FAILED TO CREATE THE TETRIS RANKING FILE!\n");
            exit(0);
        }
    }
    for(i=0;i<list_n;i++)
    {
        fprintf(fp,"%6d%20s\n",ranking[i].score,ranking[i].user_name);
    }
    fclose(fp);
}


//*********************************//
//Function:resume_ranking
//         gameflag = 0 :2048
//         gameflag = 1 :tetris
//Type:void
//Inlet parameter:ITEM ranking[list_n],int gameflag
//Outlet parameter:none
void resume_ranking(ITEM ranking[list_n],int gameflag)
{
    int i;
    FILE *fp;
    if(gameflag==0)
    {
        if((fp = fopen("store_2048_ranking.txt","r")) == NULL)
        {
            printf("FAILED TO OPEN THE 2048 RANKING FILE!\n");
            exit(0);
        }
    }
    else if(gameflag==1)
    {
        if((fp = fopen("store_tetris_ranking.txt","r")) == NULL)
        {
            printf("FAILED TO CREATE THE TETRIS RANKING FILE!\n");
            exit(0);
        }
    }
    rewind(fp);
    for(i=0;i<list_n;i++)
    {
        fscanf(fp," %6d",&ranking[i].score);
        fscanf(fp," %20s",ranking[i].user_name);
    }
    fclose(fp);
}
