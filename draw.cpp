#include <graphics.h>		// 这样引用 EasyX 图形库

/*
函数功能：设置文字样式和颜色
*/
void settext(int height, int weight, UINT color)
{
	settextstyle(height, 0, _T("Arial"), 0, 0, weight, false, false, false, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH);
	settextcolor(color);
}

/*
函数功能：在指定矩形区域内居中输出字符串
*/
void printtext(LPCTSTR s, int left, int top, int right, int width)
{
	RECT r = { left, top, right, width };
	drawtext(s, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}