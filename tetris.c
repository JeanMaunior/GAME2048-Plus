
#include "gamestruct.h"

int exit_flag = 0;          //退出标志，在tetris()函数中检查，在CheckExit()中改变


int const random_number[6][16] =    {{2,2,2,2,2,2,2,2,2,2,4,4,4,4,4,4},
                                    {2,2,2,2,2,2,2,2,4,4,4,4,4,8,8,8},
                                    {2,2,2,2,2,4,4,4,4,4,8,8,8,8,16,16},
                                    {2,2,2,4,4,4,4,8,8,8,8,16,16,16,32,32},
                                    {2,2,2,4,4,4,8,8,8,8,16,16,16,32,32,64},
                                    {2,2,4,4,8,8,8,8,16,16,16,32,32,64,64,128}};    //随机数列表，用于规定产生的数字，
                                                                                    //使之与当前场上最大数字相匹配

int max_num = 0;            //记录场上的最大数字



/*
函数功能：找到场上的最大数字，用于从文件读取保存的结果之后
*/
int FindMax(TERIS_2048 *t)
{
    int i,j;
    for(i=0; i<HEIGHT; i++)
    {
        for(j=0; j<WIDTH; j++)
        {
            max_num = max(max_num,t->board[i][j]);
        }
    }
}

/*
函数功能：产生一个新的随机数块
*/
void MakeNewBlock(TERIS_2048 *t)
{
    int mode;
    switch(max_num)
    {
    case 0:
    case 2:
    case 4:
        mode = 0;
        break;
    case 8:
        mode = 1;
        break;
    case 16:
        mode = 2;
        break;
    case 32:
        mode = 3;
        break;
    case 64:
        mode = 4;
        break;
    default:
        mode = 5;
        break;
    }
    NEWBLOCK *b;
    b = (NEWBLOCK*)malloc(sizeof(NEWBLOCK));
    b->initial_time = clock();
    srand(time(NULL));
    b->number = random_number[mode][rand()%16];
    b->nb_x = rand()%WIDTH;
    b->nb_y = HEIGHT - 1;
    t->board[b->nb_y][b->nb_x] = b->number;
    t->nb = *b;
}

/*
函数功能：刷新并绘制界面
*/
void Display(TERIS_2048 *t)
{
    int i,j;
    NEWBLOCK *nb;
    nb = &(t->nb);
    system("CLS");
    printf("_______________Teris_2048________________\n");
    printf("Rule:\tWhen two number with the same number is next to each other,\n\tthey will merge into one with a twice number.\n");
    printf("Method:\tUse ← → to control the new block.\n\tThe block will fall down when ↓ is pressed or time is out.\n\tYou can press\"x\"on the key board to pause or exit\n");
    printf("Time:%5d\nscore:%5d\n",(t->time+clock())/1000,t->score);
    printf("_________________Game_Zone_________________\n");
    printf("___________________________________________\n\n");



    for(i=HEIGHT-1; i>=0; i--)
    {
        printf("|");
        for(j=0; j<WIDTH; j++)
        {

            if(t->board[i][j]==0)
                printf("      |");
            else
                printf("%6d|",t->board[i][j]);
        }
        if(i ==0)
        printf("\n");
        else
        printf("\n------------------------------------------\n");
    }
    printf("___________________________________________\n");


}

/*
函数功能：通过改变新产生的数字的纵坐标与棋盘数字
控制新产生的数字向下落
返回值：若在此次下落后还能够继续向下落则返回1，否则返回0
*/
int AutoDown(TERIS_2048 *t)
{
    NEWBLOCK *nb = &(t->nb);
    if(nb->nb_y != 0 && t->board[nb->nb_y-1][nb->nb_x] == 0)
    {
        t->board[nb->nb_y][nb->nb_x] = 0;
        nb->nb_y--;
    }
    t->board[nb->nb_y][nb->nb_x] = nb->number;
    if(nb->nb_y != 0 && t->board[nb->nb_y-1][nb->nb_x] == 0)
        return 0;
    else return 1;
}

/*
函数功能：      确定是否退出，若输入y/Y(退出)，置退出标志exit_flag 为1,
                若输入n,则不改变；若输入其他，则反复提示输入

*/
void CheckExit(TERIS_2048 *t)
{
    int input;
    do
    {
        do
        {
            Display(t);
            printf("Are you sure to exit?(y/n）");
            Sleep(1000);
        }
        while(!_kbhit());
        input =getch();
        if(input =='y'||input =='Y')
        {
            exit_flag = 1;
            return 0;
        }
    }
    while(input!='n'&&input!='N');

}
/*
***核心算法***

函数功能：
1.若无输入，控制新数字块每秒向下落，直至接收到输入或落到底
2.若接收到输入，
    1）输入为方向键，则按照输入进行方块的移动
    2）输入为x,则暂停，确定是否退出
返回值：若按了“下”键，或数字块已经落到底，则返回1，否则返回0；
*/
int Move(TERIS_2048 *t)
{
    int input;
    int down = 0;
    int bottom = 0;     //判断是否自动下落到底
    int i,j;
    NEWBLOCK *nb;
    nb = &(t->nb);
    do
    {
        if((clock()-nb->initial_time)%1000 <= 15)
        {
            bottom = AutoDown(t);
            Display(t);
            Sleep(110);
        }
    }
    while((!_kbhit())&&(!bottom));
    if(!bottom)
    {
        input = getch();
        if(input == 224)
        {
            t->board[t->nb.nb_y][t->nb.nb_x] = 0;
            input = getch();
            fflush(stdin);
            switch(input)
            {
            case 75:        //左
                if(nb->nb_x != 0&&t->board[nb->nb_y][nb->nb_x-1]==0)
                    nb->nb_x--;
                break;
            case 77:        //右
                if(nb->nb_x !=WIDTH-1 && t->board[nb->nb_y][nb->nb_x+1]==0)
                    nb->nb_x++;
                break;
            case 80:        //下
                for(i=0; i<HEIGHT; i++)
                {
                    if(t->board[i][nb->nb_x] == 0)
                    {
                        nb->nb_y = i;
                        break;
                    }
                }
                down = 1;
                break;
            }
            t->board[nb->nb_y][nb->nb_x] = nb->number;      //移动思路：
                                                            //将新数字块原坐标对应数字置0，改变新数字块的坐标，
                                                            //再将改变后的坐标对应数字置为新数字块的数字
            Display(t);
            Sleep(100);
        }
        else if(input == 'x'||input == 'X')
            CheckExit(t);
    }
    else
        down = 1;

    return down;
}

/*
函数功能：消除每一列中的空格，将空格上方的各个数字依次往下移动一格
            用于每次更新数字之后
*/

void CheckDown(TERIS_2048 *t)
{
    int i,j,k,temp;
    int flag;
    do
    {
        flag = 0;
        for(j=0; j<WIDTH; j++)
        {
            for(i=0; i<HEIGHT-1; i++)
            {
                if(t->board[i][j]==0&&t->board[i+1][j]!=0)
                {
                    flag = 1;
                    for(k=i; k<HEIGHT-1; k++)
                    {
                            temp = t->board[k][j];
                            t->board[k][j] = t->board[k+1][j];
                            t->board[k+1][j] = temp;

                    }
                }
            }
        }
    }
    while(flag != 0);
}

/*
函数功能：自左向右，自下向上检查是否有上下相邻的数字相同
            若有，则进行合并
返回值：若进行了合并，则返回1;否则返回0
*/
int AddDown(TERIS_2048 *t)
{
    int flagdown = 0;
    int i,j;
    for(j=0; j<WIDTH; j++)
    {
        for(i=0; i<HEIGHT-1; i++)
        {
            if(t->board[i][j]==t->board[i+1][j]&&t->board[i][j]!=0)
            {
                t->board[i][j]*=2;
                max_num = max(max_num,t->board[i][j]);              //检查是否改变了最大值
                t->score += t->board[i][j];
                t->board[i+1][j] = 0;                               //合并办法： 先将相同两数字靠上的数置为0，靠下的数置为两倍
                CheckDown(t);                                       //              再将空格补齐
                flagdown = 1;
                Display(t);
                Sleep(100);

            }
        }
    }
    return flagdown;
}

/*
函数功能：自下向上，自左向有检查是否有左右相邻的数字相同
            若有，则进行合并
返回值：若进行了合并，则返回1;否则返回0
*/
int AddLeft(TERIS_2048 *t)
{
    int flagleft = 0;
    int i,j;
    for(i=0; i<HEIGHT; i++)
    {
        for(j=0; j<WIDTH-1; j++)
        {
            if(t->board[i][j]==t->board[i][j+1]&&t->board[i][j]!=0)
            {
                t->board[i][j]*=2;
                max_num = max(max_num,t->board[i][j]);
                t->score += t->board[i][j];
                t->board[i][j+1] = 0;
                CheckDown(t);
                flagleft = 1;
                Display(t);
                Sleep(100);
            }
        }
    }
    return flagleft;
}

/*
***核心算法***
函数功能：让场上所有相邻且相同数字的按一定优先级合并

**优先级：向下>向左；左下>右上
*/
void Add(TERIS_2048 *t)
{
    int flagdown,flagleft,flag;
    int i,j;
    do
    {
        do
        {
            flagdown = AddDown(t);
        }
        while(flagdown == 1);
        flagleft = AddLeft(t);      //向下加和，确保不能再向下时进行向左加和；
                                    //每次向左加和后，重新检查是否可以继续向下加和

    }
    while(flagleft != 0);
}

/*
函数功能：判断是否游戏失败
*/
int IsGameOver(TERIS_2048 *t)
{
    int i;
    for(i=0; i<WIDTH; i++)
    {
        if(t->board[HEIGHT-1][i] != 0&&t->board[HEIGHT-2][i] != 0)
            return 1;
    }
    return 0;
}

/*
函数功能：游戏失败后，记录姓名与分数
*/
void Gameover(TERIS_2048* t)
{
    ITEM* item;
    item = (ITEM*)malloc(sizeof(ITEM));
    printf("\nGame Over!\n");
    printf("Please input your name:(<10characters)\n");
    fgets(item->user_name,LENGTH,stdin);
    item->score = t->score;
}

/*
函数功能：新建游戏，初始化所有参数
*/
TERIS_2048* Initial_2048()
{
    TERIS_2048* t;
    t = (TERIS_2048*)malloc(sizeof(TERIS_2048));
    memset(t->board,0,sizeof(t->board));
    t->score = 0;
    t->time = 0;
    return t;
}

/*
***主函数***
函数功能：控制游戏的总流程，包括新建游戏/读取游戏，游戏进行，游戏结束，游戏退出
输入值：输入0为重新开始游戏；输入1为读取存档继续游戏；输入其他为错误，返回-1
返回值：
*/
int tetris(int option)
{
    TERIS_2048 *teris;
    int over = 0;
    int down = 0;
    if(option == 0)
        teris = Initial_2048();
    else if(option == 1)
    {
        teris = (TERIS_2048*)malloc(sizeof(TERIS_2048));
        resume_tetris(teris);
        FindMax(teris);
    }
    else return -1;
    teris->time -= clock();
    MakeNewBlock(teris);
    Display(teris);
    Sleep(100);
    do
    {
        down = Move(teris);
        if(exit_flag == 0)
        {
            Add(teris);
            over = IsGameOver(teris);
            if(down == 1&&over == 0)
            {
                MakeNewBlock(teris);
                down = 0;
            }
            Display(teris);
            Sleep(80);
        }
    }
    while(over != 1 && exit_flag != 1);
    if(over == 1)
    {
        Gameover(teris);
    }

    else if(exit_flag == 1)
    {
        teris->board[teris->nb.nb_y][teris->nb.nb_x] = 0;
        teris->time += clock();
        store_tetris(*teris);
    }

    return 0;
}

