
#include "gamestruct.h"
#include <graphics.h>		// 这样引用 EasyX 图形库
#include <map>


int InputNum()
{
    int number,i = 0;
    char character[2], input_ch;
    memset(character, '\0', sizeof(character));
    do
    {
        input_ch = _getch();
        if (input_ch == 8 && i != 0)
        {
            i--;
            character[i] = '\0';
        }
        else if (i < 1 && input_ch != 13)
        {
            character[i] = input_ch;
            i++;
        }
        setfillcolor(0x8eecff);
        solidrectangle(90, 650, 350, 698);
        settext(30, 1000, BLACK);
        printtext(_T(character), 90, 650, 350, 700);
    } while (input_ch != 13);
    number = int(character[0] - '0');
    return number;
}


int PrintMenu()
{
    int option = -1;
    do
    {
        setfillcolor(0x8eecff);
        solidrectangle(0, 0, 430, 800);
        settext(30, 1000, 0x3958e9);
        printtext(_T("GAME MENU"), 75, -200, 355, 550);
        printtext(_T("1.2048                       "), 75, 50, 355, 550);
        printtext(_T("2.TETRIS                  "), 75, 150, 355, 550);
        printtext(_T("3.AI of 2048              "), 75, 250, 355, 550);
        printtext(_T("4.Search in Ranking"), 75, 350, 355, 550);
        printtext(_T("5.exit                         "), 75, 450, 355, 550);
        printtext(_T("Input the your chice:"), 75, 650, 355, 500);
        setlinecolor(0x3958e9);
        line(200, 700, 240, 700);
        
        option = InputNum();
    } while (option <= 0 || option >= 6);
    Sleep(200);
    return option;
}

int GetGameOption()
{
    int option = -1;
    do
    {
        setfillcolor(0x8eecff);
        solidrectangle(0, 0, 430, 800);
        settext(30, 1000, 0x3958e9);
        printtext(_T("GAME MENU"), 75, -200, 355, 550);
        printtext(_T("1.NEW GAME             "), 75, 50, 355, 550);
        printtext(_T("2.RESUME                 "), 75, 150, 355, 550);
        printtext(_T("3.RETURN TO MENU"), 75, 250, 355, 550);
        printtext(_T("Input the your chice:"), 75, 600, 355, 500);
        setlinecolor(0x3958e9);
        line(200, 700, 240, 700);

        option = InputNum();
    } while (option <= 0 || option >= 4);
    Sleep(200);
    return option;
}


int GetSearchOption()
{
	int option = -1;
	do
	{
		setfillcolor(0x8eecff);
		solidrectangle(0, 0, 430, 800);
		settext(25, 1000, 0x3958e9);
		printtext(_T("SEARCH MENU"), 75, -200, 355, 550);
		printtext(_T("1.SEARCH IN 2048 RANKING    "), 60, 50, 370, 550);
		printtext(_T("2.SEARCH IN TETRIS RANKING"), 60, 150, 370, 550);
		printtext(_T("3.RETURN TO MENU                 "), 60, 250, 370, 550);
		printtext(_T("Input the your chice:"), 75, 600, 355, 500);
		setlinecolor(0x3958e9);
		line(200, 700, 240, 700);

		option = InputNum();
	} while (option <= 0 || option >= 4);
	Sleep(200);
	return option;
}


extern "C" void menu()
{
    int menu_option = -1, game_option, search_option;
    initgraph(430, 800);
    setbkmode(TRANSPARENT);
    setbkcolor(0x8eecff);
    cleardevice();
    do
    {
        menu_option = PrintMenu();
        switch (menu_option)
        {
            case 1:	game_option = GetGameOption();
					if (game_option == 1 || game_option == 2)
					{
						main_2048(game_option - 1, 0);
					}
					break;
            case 2: game_option = GetGameOption();
                    if (game_option==1 || game_option==2)
                    {
                        tetris(game_option - 1);
                    }
                    break;
            case 3: main_2048(0, 1);
					break;
			case 4: search_option = GetSearchOption();
					if (search_option == 1 || search_option == 2)
					{
						Search(search_option - 1);
					}
                    break;
            default:break;
        }
                  
    }while (menu_option != 5);
}