#include <graphics.h>		// �������� EasyX ͼ�ο�

/*
�������ܣ�����������ʽ����ɫ
*/
void settext(int height, int weight, UINT color)
{
	settextstyle(height, 0, _T("Arial"), 0, 0, weight, false, false, false, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH);
	settextcolor(color);
}

/*
�������ܣ���ָ�����������ھ�������ַ���
*/
void printtext(LPCTSTR s, int left, int top, int right, int width)
{
	RECT r = { left, top, right, width };
	drawtext(s, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}