
#include "gamestruct.h"
#include <graphics.h>		// 这样引用 EasyX 图形库
#include <map>

int exit_flag = 0;          //退出标志，在tetris()函数中检查，在CheckExit()中改变


int const random_number[6][16] =    {{2,2,2,2,2,2,2,2,2,2,4,4,4,4,4,4},
                                    {2,2,2,2,2,2,2,2,4,4,4,4,4,8,8,8},
                                    {2,2,2,2,2,4,4,4,4,4,8,8,8,8,16,16},
                                    {2,2,2,4,4,4,4,8,8,8,8,16,16,16,32,32},
                                    {2,2,2,4,4,4,8,8,8,8,16,16,16,32,32,64},
                                    {2,2,4,4,8,8,8,8,16,16,16,32,32,64,64,128}};    //随机数列表，用于规定产生的数字，
                                                                                    //使之与当前场上最大数字相匹配

int max_num = 0;            //记录场上的最大数字






std::map<int, IMAGE> image;		// 存储所有数字图像

//      函数功能： 用于生成方块图片
//		img:		方块图片指针
//		num:		方块上的数字
//		imgColor:	方块颜色
//		fontSize:	字体大小
//		fontColor:	字体颜色	
void CreateImage(IMAGE *img, LPCTSTR num, COLORREF imgColor, int fontSize, COLORREF fontColor)
{
	SetWorkingImage(img);
	setbkmode(TRANSPARENT);
	setbkcolor(0x9eaebb);
	settext(fontSize, 1000, fontColor);
	setfillcolor(imgColor);
	settextcolor(fontColor);

	cleardevice();

	solidroundrect(0, 0, img->getwidth() - 1, img->getheight() - 1, 10, 10);

	RECT r = { 0,0,img->getwidth() - 1,img->getheight() - 1 };
	drawtext(num, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

/*
函数功能：绘制图片缓存
*/
void Load()
{
	IMAGE temp(60, 60);

	CreateImage(&temp, _T(""), 0xb5becc, 60, WHITE);		image[0] = temp;
	CreateImage(&temp, _T("2"), 0xdbe6ee, 60, 0x707b83);		image[2] = temp;
	CreateImage(&temp, _T("4"), 0xc7e1ed, 60, 0x707b83);		image[4] = temp;
	CreateImage(&temp, _T("8"), 0x78b2f4, 60, WHITE);		image[8] = temp;
	CreateImage(&temp, _T("16"), 0x538ded, 50, WHITE);		image[16] = temp;
	CreateImage(&temp, _T("32"), 0x607df6, 50, WHITE);		image[32] = temp;
	CreateImage(&temp, _T("64"), 0x3958e9, 50, WHITE);		image[64] = temp;
	CreateImage(&temp, _T("128"), 0x6bd9f5, 40, WHITE);		image[128] = temp;
	CreateImage(&temp, _T("256"), 0x4bd0f2, 40, WHITE);		image[256] = temp;
	CreateImage(&temp, _T("512"), 0x2ac0e4, 40, WHITE);		image[512] = temp;
	CreateImage(&temp, _T("1024"), 0x13b8e3, 30, WHITE);		image[1024] = temp;
	CreateImage(&temp, _T("2048"), 0x00c5eb, 30, WHITE);		image[2048] = temp;
	CreateImage(&temp, _T("4096"), 0x3958e9, 30, WHITE);		image[4096] = temp;
	CreateImage(&temp, _T("8192"), 0x3958e9, 30, WHITE);		image[8192] = temp;

	SetWorkingImage(NULL);
}

/*
函数功能：找到场上的最大数字，用于从文件读取保存的结果之后
*/
void FindMax(TERIS_2048 *t)
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
    int i,j,p;
	char time[10];
	char score[10];
	itoa((t->time + clock()) / 1000, time, 10);
	itoa(t->score, score, 10);

	setfillcolor(0x9eaebb);
	solidroundrect(70, 170, 210, 200, 10, 10);	//time
	settext(18, 500, WHITE);
	printtext(_T(time), 75, 170, 200, 205);

	setfillcolor(0x9eaebb);
	solidroundrect(280, 170, 420, 200, 10, 10);	//score
	settext(18, 500, WHITE);
	printtext(_T(score), 285, 170, 420, 205);

    for(i=HEIGHT-1; i>=0; i--)
    {
		p = HEIGHT - i - 1;
        for(j=0; j<WIDTH; j++)
        {
			putimage(22 + j * 65, 210 + i * 65, &image[t->board[p][j]]);
        }

    }
}
/*
功能：初始化界面
*/
void Init_Display()
{
		int i, j;

	Load();
	setbkmode(TRANSPARENT);
	setbkcolor(0x8eecff);
	cleardevice();

	setfillcolor(0x9eaebb);
	solidroundrect(10, 30, 420, 90, 10, 10);	//rule
	solidroundrect(10, 100, 420, 160, 10, 10);	//method

	solidroundrect(10, 170, 210, 200, 10, 10);	//time
	solidroundrect(220, 170, 420, 200, 10, 10);	//score
	solidroundrect(17, 205, 412, 795, 10, 10);	//board

	settext(28, 1000, 0x707b83);
	printtext(_T("TETRIS_2048"), 120, 0, 300, 28);

	settext(20, 1000, 0xdbe6ee);
	printtext(_T("Rule:"), 15, 30, 65, 60);
	settext(18, 400, WHITE);
	printtext(_T("When two number with the same number is next "), 40, 30, 430, 60);
	printtext(_T("to each other,they will merge into one with a twice number."), 20, 60, 430, 90);
	settext(20, 1000, 0xdbe6ee);

	printtext(_T("Method:"), 15, 100, 80, 130);
	settext(18, 400, WHITE);
	printtext(_T("Use ← ↓ → to control the new block."), 40, 100, 430, 130);
	printtext(_T("You can press\"x\"on the key board to pause or exit"), 20, 130, 430, 160);

	settext(20, 800, 0xdbe6ee);
	printtext(_T("Time:"), 15, 170, 65, 205);
	printtext(_T("Score:"), 225, 170, 280, 205);



	for (i = 0; i < HEIGHT; i++)
	{
		for (j = 0; j < WIDTH; j++)
		{
			putimage(22 + j * 65, 210 + i * 65, &image[0]);

		}
	}


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
	setfillcolor(0x8eecff);
	solidrectangle(0, 0, 430, 800);	//EXIT
	settext(60, 1000, 0x3958e9);
	printtext(_T("EXIT? (Y/N)"), 80, 200, 350, 500);
    do
    {
        input =getch();
        if(input =='y'||input =='Y')
        {
            exit_flag = 1;
			break;
        }
    }
    while(input!='n'&&input!='N');
	Init_Display();
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
函数功能：游戏失败后，显示“GAME OVER",记录姓名与分数
*/
void Gameover(TERIS_2048* t)
{	
	char score[list_n];
	char name[list_n];

	itoa(t->score, score, 10);
    ITEM* item;
    item = (ITEM*)malloc(sizeof(ITEM));
	setfillcolor(0x8eecff);
	solidrectangle(0, 0, 430, 800);	
	settext(50, 1000, 0x3958e9);
	printtext(_T("Game Over!"), 75, 150, 355, 500);
	printtext(_T("Score:"), 75, 350, 215, 550);
	printtext(_T(score), 215, 350, 355, 550);
	settext(20, 50, 0x3958e9);
	printtext(_T("Press any key to continue..."), 60, 400, 370, 700);
	Sleep(500);
	while (!_kbhit());

	getch();
	setfillcolor(0x8eecff);
	solidrectangle(0, 0, 430, 800);
	settext(30, 1000, 0x3958e9);
	printtext(_T("Score:"), 75, 50, 215, 350);
	printtext(_T(score), 215, 50, 355, 350);
	printtext(_T("Input your name:"), 75, 150, 355, 500);
	printtext(_T("(<10characters)"), 75, 200, 355, 550);
	setlinecolor(0x3958e9);
	line(90, 500, 350, 500);
	char input;
	memset(name, '\0', sizeof(name));
	int i = 0;
	do
	{
		input = _getch();
		if (input == 8 && i != 0)
		{
			i--;
			name[i] = '\0';
		}
		else if (i < 9 && input != 13 && isprint(input) != 0)
		{
			name[i] = input;
			i++;
		}
		setfillcolor(0x8eecff);
		solidrectangle(90, 450, 350, 498);
		settext(30, 1000, BLACK);
		printtext(_T(name), 90, 450, 350, 500);
	} while (input != 13);

	ITEM array[list_n];
	resume_ranking(array,1);

	RANKINGLIST *ranking = (RANKINGLIST*)malloc(sizeof(RANKINGLIST));
	sort_main(array, list_n + 1, ranking, t->score, name);
	store_ranking(ranking,1);
	printlist(*ranking, name,t);
	_getch();


}

/*
函数功能：显示排行榜
*/
void printlist(RANKINGLIST ranking, char *user_name,TERIS_2048* t)
{
	initgraph(430, 800);
	setbkmode(TRANSPARENT);
	setbkcolor(0x8eecff);
	cleardevice();
	TCHAR c[list_n];
	char ch[list_n];
	settext(28, 800, BLACK);
	outtextxy(150, 20, _T("Ranking List"));
	outtextxy(25, 100, _T("Rank"));
	outtextxy(150, 100, _T("Name"));
	outtextxy(300, 100, _T("Score"));
	for (int i = 0; i < list_n; i++)
	{
		_itoa(i + 1, ch, 10);
		outtextxy(50, 150 + 50 * i, _T(ch));
		outtextxy(150, 150 + 50 * i,_T(ranking.ranking2048[i].user_name));
		_itoa(ranking.ranking2048[i].score, ch, 10);
		outtextxy(300, 150 + 50 * i, _T(ch));
	}
	settext(28, 800, RED);
	outtextxy(80, 650, _T("Your Name:"));
	outtextxy(300, 650, _T(user_name));

	outtextxy(80, 700, _T("Your Score"));
	_itoa(t->score, ch, 10);
	outtextxy(300, 700, _T(ch));
	settext(28, 800, BLACK);
	outtextxy(50, 750, _T("Press Any Key To Continue..."));
	setfillcolor(0x8eecff);
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
	exit_flag = 0;
    if(option == 0)
        teris = Initial_2048();
    else if(option == 1)
    {
        teris = (TERIS_2048*)malloc(sizeof(TERIS_2048));
        resume_tetris(teris);
        FindMax(teris);
    }
    else return -1;
	initgraph(430, 800);
	Init_Display();
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
		setfillcolor(0x8eecff);
		solidrectangle(0, 0, 430, 800);	//EXIT
		settext(50, 1000, 0x3958e9);
		printtext(_T("Save Done."), 75, 200, 355, 500);
		settext(20, 50, 0x3958e9);
		printtext(_T("Press any key to continue..."), 60, 400, 370, 700);
		Sleep(500);
		getch();

    }

    return 0;
}

