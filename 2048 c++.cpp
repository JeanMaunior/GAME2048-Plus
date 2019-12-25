// 2048 c++.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <easyx.h>
#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <tchar.h>
#include <map>
#include <sstream>
#include <cstring>

#include "gamestruct.h"
//#include "filewrite.c"
//#include "sort.c"
//#include "stack.c" 

#pragma comment( lib, "MSIMG32.LIB")

using namespace std;

constexpr auto n = 10;
constexpr auto size = 4;


struct game_2048 game;
std::map<int, IMAGE> image_2048;						// 存储所有数字图像
GAME_STACK_HEAD stack;
RANKINGLIST ranking;
//
//// 设置文字样式和颜色
//void settext(int height, int weight, UINT color)
//{
//    settextstyle(height, 0, _T("Arial"), 0, 0, weight, false, false, false, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
//        CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH);
//    settextcolor(color);
//}
//
//
//// 在指定矩形区域内居中输出字符串
//void printtext(LPCTSTR s, int left, int top, int right, int width)
//{
//    RECT r = { left, top, right, width };
//    drawtext(s, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
//}

// 绘制界面
void Draw()
{
	char c[list_n];
	setfillcolor(0x9eaebb);   //设置当前填充颜色

    // 绘制当前分数
    solidroundrect(112, 30, 264, 119, 10, 10);
    settext(28, 800, 0xdbe6ee);
    printtext(_T("SCORE"), 112, 40, 264, 69);
	itoa(game.score, c, 10);
    //std::wstringstream ss;
    //ss << game.score;
    settext(44, 800, WHITE);
    printtext(_T(c), 112, 70, 264, 114);
    //ss.str(_T(""));

    
    solidroundrect(275, 30, 427, 119, 10, 10);
    settext(28, 800, 0xdbe6ee);
    printtext(_T("TIME"), 275, 40, 427, 69);
    //ss << game.time;
	itoa(game.time, c, 10);
    settext(44, 800, WHITE);
    printtext(_T(c), 275, 70, 427, 114);
    //ss.str(_T(""));

    // 绘制提示信息
    settextcolor(BLACK);
    //ss << "Move blocks to get a bigger block";
    settext(24, 800, 0x707b83);
    printtext(_T("Move blocks to get a bigger block"), 0, 120, 439, 211);

    // 绘制方块底板
    solidroundrect(12, 212, 427, 627, 10, 10);

    // 绘制方块
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            putimage(25 + 100 * j, 225 + 100 * i, &image_2048[game.board[i][j]]);
        }
    }
}

// 用于生成方块图片
//		img:		方块图片指针
//		num:		方块上的数字
//		imgColor:	方块颜色
//		fontSize:	字体大小
//		fontColor:	字体颜色	
void CreateImage_2048(IMAGE* img, LPCTSTR num, COLORREF imgColor, int fontSize, COLORREF fontColor)
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

// 绘制图片缓存
void Load_2048()
{
    IMAGE temp(90, 90);

    CreateImage_2048(&temp, _T(""), 0xb5becc, 72, WHITE);		image_2048[0] = temp;
    CreateImage_2048(&temp, _T("2"), 0xdbe6ee, 72, 0x707b83);		image_2048[2] = temp;
    CreateImage_2048(&temp, _T("4"), 0xc7e1ed, 72, 0x707b83);		image_2048[4] = temp;
    CreateImage_2048(&temp, _T("8"), 0x78b2f4, 72, WHITE);		image_2048[8] = temp;
    CreateImage_2048(&temp, _T("16"), 0x538ded, 72, WHITE);		image_2048[16] = temp;
    CreateImage_2048(&temp, _T("32"), 0x607df6, 72, WHITE);		image_2048[32] = temp;
    CreateImage_2048(&temp, _T("64"), 0x3958e9, 72, WHITE);		image_2048[64] = temp;
    CreateImage_2048(&temp, _T("128"), 0x6bd9f5, 56, WHITE);		image_2048[128] = temp;
    CreateImage_2048(&temp, _T("256"), 0x4bd0f2, 56, WHITE);		image_2048[256] = temp;
    CreateImage_2048(&temp, _T("512"), 0x2ac0e4, 56, WHITE);		image_2048[512] = temp;
    CreateImage_2048(&temp, _T("1024"), 0x13b8e3, 40, WHITE);		image_2048[1024] = temp;
    CreateImage_2048(&temp, _T("2048"), 0x00c5eb, 40, WHITE);		image_2048[2048] = temp;
    CreateImage_2048(&temp, _T("4096"), 0x3958e9, 40, WHITE);		image_2048[4096] = temp;
    CreateImage_2048(&temp, _T("8192"), 0x3958e9, 40, WHITE);		image_2048[8192] = temp;

    SetWorkingImage(NULL);
}

void getname(char* str)
{
    initgraph(430, 800);
    setbkmode(TRANSPARENT);
    setbkcolor(0x8eecff);
    cleardevice();

    int i = 0;
    char input;
    //wchar_t name[10];
    char name_[10];

    settext(30, 1000, 0x3958e9);
	printtext(_T("Game Over!"), 75, 50, 355, 500);
    printtext(_T("Input your name:"), 75, 150, 355, 500);
    printtext(_T("(<10characters)"), 75, 200, 355, 550);
    setlinecolor(0x3958e9);
    line(90, 500, 350, 500);
    //memset(name, '\0', sizeof(name));
    memset(name_, '\0', sizeof(name_));
    do
    {
        input = _getch();

        if (input == 8 && i != 0)
        {
            i--;
            //name[i] = '\0';
            name_[i] = '\0';
        }
        else if (i < 9 && input != 13 && isprint(input) != 0)

        {
            //name[i] = input;
            name_[i] = input;
            i++;
        }
        setfillcolor(0x8eecff);
        solidrectangle(90, 450, 350, 498);
        settext(30, 1000, BLACK);
        printtext(_T(name_), 90, 450, 350, 500);
    } while (input != 13);
    strcpy(str, name_);
}

// The functions moveLeft, moveRight, moveUp, moveDown
// return -1 if the moving  is not possible.
// Otherwise they move the numbers as indicated and return
// the change to the score from combining adjacent identical numbers.
// They return 0 if no numbers were combined.
int moveLeft(int board[SIZE][SIZE])
{
    int i, j, k, score = 0, flag = -1, element, next_element;
    //deal with the element which is not 0
    //if the element is equal to the next_element on the left,
    //add it up and change next_element into 0
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            element = board[i][j];
            if (element != 0)
            {
                k = j + 1;
                while (k < SIZE)
                {
                    next_element = board[i][k];
                    if (next_element != 0)
                    {
                        if (element == next_element)
                        {
                            //合并
                            flag = 0;
                            board[i][j] += board[i][k];
                            score += board[i][j];
                            board[i][k] = 0;

                            ////动画
                            //putimage(25 + 100 * i, 225 + 100 * j, &image_2048[score]);
                            //putimage(25 + 100 * i, 225 + 100 * k, &image_2048[0]);
                        }
                        k = SIZE;
                        break;
                    }
                    k++;
                }
            }
        }
    }
    //deal with the element which is 0
    //find the next_element on its right which is not 0
    //change element into next_element and change next_element into 0
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE - 1; j++)
        {
            element = board[i][j];
            if (element == 0)
            {
                k = j + 1;
                while (k < SIZE)
                {
                    next_element = board[i][k];
                    if (next_element != 0)
                    {
                        //不合并，移动
                        flag = 0;
                        board[i][j] = next_element;
                        board[i][k] = 0;
                        

                        //动画
                        //putimage(25 + 100 * i, 225 + 100 * j, &image_2048[next_element]);
                        //putimage(25 + 100 * i, 225 + 100 * k, &image_2048[0]);
                        k = SIZE;
                    }
                    k++;
                }
            }
        }
    }
    if (flag != -1)
        return score;
    else
        return -1;
}

int moveRight(int board[SIZE][SIZE])
{
    int i, j, k, score = 0, flag = -1, element, next_element;
    for (i = 0; i < SIZE; i++)
    {
        for (j = SIZE - 1; j >= 0; j--)
        {
            element = board[i][j];
            if (element != 0)
            {
                k = j - 1;
                while (k >= 0)
                {
                    next_element = board[i][k];
                    if (next_element != 0)
                    {
                        if (element == next_element)
                        {
                            //合并
                            flag = 0;
                            board[i][j] += board[i][k];
                            score += board[i][j];
                            board[i][k] = 0;

                            //动画
                        //    putimage(25 + 100 * i, 225 + 100 * j, &image_2048[score]);
                        //    putimage(25 + 100 * i, 225 + 100 * k, &image_2048[0]);
                        }
                        k = -1;
                        break;
                    }
                    k--;
                }
            }
        }
    }
    for (i = 0; i < SIZE; i++)
    {
        for (j = SIZE - 1; j > 0; j--)
        {
            element = board[i][j];
            if (element == 0)
            {
                k = j - 1;
                while (k >= 0)
                {
                    next_element = board[i][k];
                    if (next_element != 0)
                    {
                        //移动，不合并
                        flag = 0;
                        board[i][j] = next_element;
                        board[i][k] = 0;
                        
                        //动画
                        //putimage(25 + 100 * i, 225 + 100 * j, &image_2048[next_element]);
                        //putimage(25 + 100 * i, 225 + 100 * k, &image_2048[0]);
                        k = -1;
                    }
                    k--;
                }
            }
        }
    }
    if (flag != -1)
        return score;
    else
        return -1;
}

int moveDown(int board[SIZE][SIZE])
{
    int i, j, k, score = 0, flag = -1, element, next_element;
    for (i = SIZE - 1; i >= 0; i--)
    {
        for (j = 0; j < SIZE; j++)
        {
            element = board[i][j];
            if (element != 0)
            {
                k = i - 1;
                while (k >= 0)
                {
                    next_element = board[k][j];
                    if (next_element != 0)
                    {
                        if (board[i][j] == board[k][j])
                        {
                            //合并
                            flag = 0;
                            board[i][j] += board[k][j];
                            score += board[i][j];
                            board[k][j] = 0;
                            //动画
                            //putimage(25 + 100 * i, 225 + 100 * j, &image_2048[score]);
                            //putimage(25 + 100 * k, 225 + 100 * j, &image_2048[0]);
                        }
                        k = 0;
                        break;
                    }
                    k--;
                }
            }
        }
    }
    for (i = SIZE - 1; i > 0; i--)
    {
        for (j = 0; j < SIZE; j++)
        {
            element = board[i][j];
            if (element == 0)
            {
                k = i - 1;
                while (k >= 0)
                {
                    next_element = board[k][j];
                    if (next_element != 0)
                    {
                        //移动，不合并
                        flag = 0;
                        board[i][j] = next_element;
                        board[k][j] = 0;
                        
                        //动画
                        //putimage(25 + 100 * i, 225 + 100 * j, &image_2048[next_element]);
                        //putimage(25 + 100 * k, 225 + 100 * j, &image_2048[0]);
                        k = 0;
                    }
                    k--;
                }
            }
        }
    }
    if (flag != -1)
        return score;
    else
        return -1;
}

int moveUp(int board[SIZE][SIZE])
{
    int i, j, k, score = 0, flag = -1, element, next_element;
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            element = board[i][j];
            if (element != 0)
            {
                k = i + 1;
                while (k < SIZE)
                {
                    next_element = board[k][j];
                    if (next_element != 0)
                    {
                        if (element == next_element)
                        {
                            //合并
                            flag = 0;
                            board[i][j] += board[k][j];
                            score += board[i][j];
                            board[k][j] = 0;
                            //动画
                            //putimage(25 + 100 * i, 225 + 100 * j, &image_2048[score]);
                            //putimage(25 + 100 * k, 225 + 100 * j, &image_2048[0]);
                        }
                        k = SIZE;
                        break;
                    }
                    k++;
                }
            }
        }
    }
    for (i = 0; i < SIZE - 1; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            element = board[i][j];
            if (element == 0)
            {
                k = i + 1;
                while (k < SIZE)
                {
                    next_element = board[k][j];
                    if (next_element != 0)
                    {
                        //移动不合并
                        flag = 0;
                        board[i][j] = next_element;
                        board[k][j] = 0;
                        
                        //动画
                        //putimage(25 + 100 * i, 225 + 100 * j, &image_2048[next_element]);
                        //putimage(25 + 100 * k, 225 + 100 * j, &image_2048[0]);
                        k = SIZE;
                    }
                    k++;
                }
            }
        }
    }
    if (flag != -1)
        return score;
    else
        return -1;
}


extern "C" int move_game(int move_dir, int board[SIZE][SIZE])
{
	int score = 1;
	switch (move_dir)
	{
	case UP:
		score = moveUp(board);
		break;
	case RIGHT:
		score = moveRight(board);
		break;
	case DOWN:
		score = moveDown(board);
		break;
	case LEFT:
		score = moveLeft(board);
		break;
	default:
		printf("INVALID DIRECTION!\n");
	}
	return score;
}


// gameOver returns 0 if it is possible to make a move on the board
// It returns 1 otherwise.

int gameOver(int board[SIZE][SIZE])
{
    // 横向检测
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == 0 || board[i][j] == board[i][j + 1] || board[i][j + 1] == 0)
                return 0;
        }
    }

    // 纵向检测
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[j][i] == 0 || board[j][i] == board[j + 1][i] || board[j + 1][i] == 0)
                return 0;
        }
    }

    return 1;
}

// add a new number to the board
// it will either be a 2 (90% probability) or a 4 (10% probability)
void insertNewNumber(int board[SIZE][SIZE])
{
    int row, column;
    int random_number, vacantSquares = 0;
    // count vacant squares
    for (row = 0; row < SIZE; row = row + 1)
    {
        for (column = 0; column < SIZE; column = column + 1)
        {
            if (board[row][column] == 0)
            {
                vacantSquares++;
            }
        }
    }
    if (vacantSquares == 0)
    {
        printf("Internal error no available square\n");
        exit(1);
    }
    // randomly pick a vacant square
    srand(time(NULL));
    random_number = rand() % vacantSquares;
    for (row = 0; row < SIZE; row = row + 1)
    {
        for (column = 0; column < SIZE; column = column + 1)
        {
            if (board[row][column] == 0)
            {
                if (random_number == 0)
                {
                    if (rand() % 10 == 0)
                    {
                        board[row][column] = 4;
                    }
                    else
                    {
                        board[row][column] = 2;
                    }
                    return;
                }
                random_number--;
            }
        }
    }
}

int input()
{
    int c;
    c = _getch();
    while (c != EOF && isspace(c))      //isspace: if c is an empty char,return 1
    {
        c = _getch();
    }
    if (c == 224)
    {
        c = _getch();
    }
    return c;
}

void printlist(RANKINGLIST ranking, char *user_name)
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
	for(int i = 0; i < list_n; i++)
	{
		_itoa(i + 1, ch, 10);
		//MultiByteToWideChar(CP_ACP, 0, ch, -1, c, 100);
		outtextxy(50, 150 + 50 * i, _T(ch));
		//MultiByteToWideChar(CP_ACP, 0, , -1, c, 100);
		outtextxy(150, 150 + 50 * i, _T(ranking.ranking2048[i].user_name));
		_itoa(ranking.ranking2048[i].score, ch, 10);
		//MultiByteToWideChar(CP_ACP, 0, ch, -1, c, 100);
		outtextxy(300, 150 + 50 * i, _T(ch));
	}
	settext(28, 800, RED);
	outtextxy(80, 650, _T("Your Name:"));
	//MultiByteToWideChar(CP_ACP, 0, user_name, -1, c, 100);
	outtextxy(300, 650, _T(user_name));

	outtextxy(80, 700, _T("Your Score"));
	_itoa(game.score, ch, 10);
	//MultiByteToWideChar(CP_ACP, 0, ch, -1, c, 100);
	outtextxy(300, 700, _T(ch));
	settext(28, 800, BLACK);
	outtextxy(50, 750, _T("Press Any Key To Continue..."));
	setfillcolor(0x8eecff);

}

void printrestart(int *str)
{
	initgraph(430, 800);
	setbkmode(TRANSPARENT);
	setbkcolor(0x8eecff);
	cleardevice();

	int i = 0;
	char input;
	//wchar_t name[10];
	char name[10];

	settext(30, 1000, 0x3958e9);
	printtext(_T("Do You Want To Restart?"), 75, 150, 355, 500);
	printtext(_T("(Print 'Y' or 'N')"), 75, 200, 355, 550);
	setlinecolor(0x3958e9);
	line(90, 500, 350, 500);
	memset( _T(name), '\0', sizeof(name));
	do
	{
		input = _getch();

		if (input == 8 && i != 0)
		{
			i--;
			name[i] = '\0';
		}
		else if (i < 1 && input != 13 && isprint(input) != 0)

		{
			name[i] = input;
			i++;
			*str = input;
		}
		setfillcolor(0x8eecff);
		solidrectangle(90, 450, 350, 498);
		settext(30, 1000, WHITE);
		printtext(name, 90, 450, 350, 500);
	} while (input != 13);
}

void gamefinished(RANKINGLIST* ranking, struct game_2048 game, int player)
{
    ITEM array[list_n];
    char user_name[list_n];

    resume_ranking(array,0);
    cleardevice();
	if (player == 0)
	{
		getname(user_name);
	}
	else if (player == 1)
	{
		strcpy(user_name,"DFS");
	}
	//getname(user_name);
    sort_main(array, n + 1, ranking,game.score,user_name);
    store_ranking(ranking,0);
	printlist(*ranking,user_name);
	_getch();
}

//初始化
void init()
{
    memset(game.board, 0, 4 * 4 * sizeof(int));	// 把地图初始化为 0
    game.score = 0;
    game.time = 0;
    stack.stack_size = 0;
    ranking.length_2048 = list_n;
    InitGameStack(&stack);

    setbkcolor(WHITE);
    setbkmode(TRANSPARENT);
	cleardevice();
}

void main_2048(int  Whether_new,int player)
{
    int i, j, c, Current_Score, Whether_Won = 0;
    long time1, time2;
	int Whether_restart = 'n';

    initgraph(440, 650);
    Load_2048();

  

	init();
	insertNewNumber(game.board);
    if(Whether_new == 1)
    {
        resume_2048(&game);
    }
	Draw();
	while (gameOver(game.board) == 0)
	{
		time1 = time(NULL);

		if (player == 0)
		{
			c = input();
		}
		else if (player == 1)
		{
			c = DFS(game.board);
			Sleep(250);
		}

		time2 = time(NULL);
		game.time += time2 - time1;

		if (c == EOF || c == 'q' || c == 'Q')                                    //按下退出
		{
			store_2048(game);
			break;
		}
		else if (c == 'r' || c == 'R')                                           //按下返回
		{
			if (stack.stack_size != 0)
				PopGameStack(&stack, &game);
		}
		else if(c == 75 || c == 80 || c == 72 || c == 77)
		{
			PushGameStack(&stack, game);
			Current_Score = 0;
			if (c == 75)
				Current_Score = moveLeft(game.board);
			else if (c == 80)
				Current_Score = moveDown(game.board);
			else if (c == 72)
				Current_Score = moveUp(game.board);
			else if (c == 77)
				Current_Score = moveRight(game.board);
			if (Current_Score != -1)
			{
				insertNewNumber(game.board);
				game.score = game.score + Current_Score;
			}
			Draw();
		}
	}
	gamefinished(&ranking, game, player);
}

