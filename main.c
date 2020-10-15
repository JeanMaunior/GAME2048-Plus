#include <stdio.h>
#include <stdlib.h>
#include "gamestruct.h"



void print_menu()
{
    printf("           1.2048\n");
    printf("           2.TETRIS\n");
    printf("           3.AI of 2048\n");
    printf("           4.RANKING\n");
}



int main()
{
    //mciSendString("open ABC.mp3 alias bkmusic",NULL,0,NULL);
    //mciSendString("play bkmusic repeat",NULL,0,NULL);


    //print_menu();
    game_2048(1);
    return 0;
}


