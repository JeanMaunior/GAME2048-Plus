
#include "gamestruct.h"
#include <graphics.h>





extern "C" void getname(char* str)
{
	initgraph(430, 800);
	setbkmode(TRANSPARENT);
	setbkcolor(0x8eecff);
	cleardevice();

	int i = 0;
	char input;
	char name[10];
	settext(30, 1000, 0x3958e9);
	printtext(_T("Input your name:"), 75, 150, 355, 500);
	printtext(_T("(<10characters)"), 75, 200, 355, 550);
	setlinecolor(0x3958e9);
	line(90, 500, 350, 500);
	memset(name, '\0', sizeof(name));
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
	strcpy(str, name);
}





extern "C" void SearchResult(char* name,int x,int pos)
{	
	char score[10];
	itoa(x, score, 10);
	if (pos == 0)
	{
		setfillcolor(0x8eecff);
		solidrectangle(0, 0, 430, 800);
	}
	settext(50, 1000, 0x3958e9);
	printtext(_T("Result"), 0, 30, 430, 100);
	settext(30, 800, 0x3958e9);

	if(x == -1)
		printtext(_T("No such player."), 25, 100, 405, 150);
	else
	{
		printtext(_T("Name:"), 75, 100, 215, 120);
		printtext(_T("Score:"), 215, 100, 355, 120);
		settext(25, 600, 0x3958e9);
		printtext(_T(name),75, 130 + 25 * pos, 215, 150 + 25 * pos);
		printtext(_T(score),215, 130 + 25 * pos, 355, 150 + 25 * pos);
	}
	settext(20, 50, 0x3958e9);
	printtext(_T("Press any key to continue..."), 60, 400, 370, 700);


}