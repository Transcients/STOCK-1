#include"public.h"
#include"database.h"
#include"techslc.h"
#include"slctfunc.h"
#include"fundam.h"

/*****************************************
techselect.c
COPYRIGHT:	weijingmin
FUNCTION:	control and draw
ABSTRACT:
		A.draw T_select page1 and page2
		B.control and skip
		C.button lighting and recovering
DATE:2019/10/26
******************************************/


/*********************************************
FUNCTION:technical_control
DESCRIPTION��ѡ�ɵ��ܿغ���
INPUT:cinfo,u,sto_list,page
RETURN:0/t(sto_list[i])
***********************************************/
int technical_control(Ctr* cinfo,USER* u, int *sto_list,int* page)
{
	int i, j;
	int t = 0;
	int return_page;//������ؼ����ص�ҳ��
	int option[11][6];//������ѡ�ɵ�option����
	//�ֱ��Ӧ��:
	//1Kline,2Kline,3Kline,nKline,MA,KDJ,MACD,RSI,VOL/OBV,B IAS,BOLL
	memset(option, 0, 66*sizeof(int));
	memset(cinfo, 0, sizeof(Ctr ));
	cinfo->func = 5;
	while (1)
	{
		if(cinfo->func != 5 /*&& cinfo->func != 10 && cinfo->func != 9*/)
		{
			clrmous(MouseX, MouseY);
			delay(10);
			return 0;
		}
		switch (*page)
		{
		case 1:
			T_stoselect1(cinfo, u, page, option, sto_list);
			memset(option, 0, 66*sizeof(int));//���˴������з�ҳ��������Ҫȫ������
			return_page = 1;
			break;
		case 2:
			T_stoselect2(cinfo, u, page, option, sto_list);
			memset(option, 0, 66*sizeof(int));//���˴������з�ҳ��������Ҫȫ������
			return_page = 1;
			break;
		case 3:
			t = T_searchresult(cinfo, u, page, sto_list,return_page);//��ʾѡ�ɽ��
			if(t)
				return t;
			break;
		case 4:
			fundam_control(cinfo, u, page, sto_list);//������ѡ��
			return_page = 4;
			break;
		}
	}
}

/*********************************************
FUNCTION:lightbutton_Tselect
DESCRIPTION��ѡ�ɰ�ť����
INPUT:num
RETURN:��
***********************************************/
void lightbutton_Tselect(int num)
{
	clrmous(MouseX, MouseY);
	delay(10);
	switch (num)
	{
	case 1:
		setcolor(BLUE);
		setfillstyle(SOLID_FILL, LIGHTBLUE);
		bar3d(560, 452, 620, 479, 5, 1);
		puthz(565, 457, "��һҳ", 16, 17, BLUE);
		break;
	case 2:
		setcolor(RED);
		setfillstyle(SOLID_FILL, LIGHTRED);
		bar3d(20, 452, 80, 479, 5, 1);
		puthz(25, 457, "��һҳ", 16, 17, RED);
		break;
	case 3:
		setcolor(CYAN);
		setfillstyle(SOLID_FILL, LIGHTCYAN);
		bar3d(250, 452, 290, 479, 5, 1);
		puthz(255, 457, "ѡ��", 16, 17, CYAN);
		break;
	case 4:
		setcolor(MAGENTA);
		setfillstyle(SOLID_FILL, MAGENTA);
		bar3d(250, 452, 290, 479, 5, 1);
		puthz(255, 457, "ѡ��", 16, 17, LIGHTMAGENTA);
		break;
	case 5:
		setcolor(RED);
		setfillstyle(SOLID_FILL, LIGHTRED);
		bar(100, 462, 140, 479);
		rectangle(100, 462, 140, 479);
		puthz(105, 462, "����", 16, 17, RED);
	}
}

/*********************************************
FUNCTION:recoverbutton_Tselect
DESCRIPTION��ѡ�ɰ�ť�ָ�����
INPUT:num
RETURN:��
***********************************************/
void recoverbutton_Tselect(int num)
{
	clrmous(MouseX, MouseY);
	delay(10);
	switch (num)
	{
	case 1:
		setcolor(WHITE);
		setfillstyle(SOLID_FILL, BLUE);
		bar3d(560, 452, 620, 479, 5, 1);
		puthz(565, 457, "��һҳ", 16, 17, WHITE);
		break;
	case 2:
		setcolor(WHITE);
		setfillstyle(SOLID_FILL, RED);
		bar3d(20, 452, 80, 479, 5, 1);
		puthz(25, 457, "��һҳ", 16, 17, WHITE);
		break;
	case 3:
		setcolor(WHITE);
		setfillstyle(SOLID_FILL, CYAN);
		bar3d(250, 452, 290, 479, 5, 1);
		puthz(255, 457, "ѡ��", 16, 17, WHITE);
		break;
	case 4:
		setcolor(WHITE);
		setfillstyle(SOLID_FILL, LIGHTMAGENTA);
		bar3d(250, 452, 290, 479, 5, 1);
		puthz(255, 457, "ѡ��", 16, 17, WHITE);
		break;
	case 5:
		setcolor(WHITE);
		setfillstyle(SOLID_FILL, RED);
		bar(100, 462, 140, 479);
		rectangle(100, 462, 140, 479);
		puthz(105, 462, "����", 16, 17, WHITE);
	}
}

/*********************************************
FUNCTION:draw_T_stoselect1
DESCRIPTION��������ѡ�ɵ�һҳ����
INPUT:void
RETURN:��
***********************************************/
void draw_T_stoselect1(void)
{
	setbkcolor(BLACK);
	setlinestyle(SOLID_LINE, 0, 1);
	setcolor(RED);
	line(0, 24, 24, 48);
	line(24, 48, 600, 48);
	line(24, 48, 24, 48 + 240);
	settextjustify(LEFT_TEXT, TOP_TEXT);
	settextstyle(3, HORIZ_DIR, 3);
	outtextxy(6, 48, "K");
	puthz(0, 48 + 24 + 6, "��", 24, 0, RED);
	puthz(0, 48 + 24*2 + 6*2, "��", 24, 0, RED);
	puthz(0, 48 + 24*3 + 6*3, "̬", 24, 0, RED);
	puthz(0, 48 + 24*4 + 6*4, "ѡ", 24, 0, RED);
	puthz(0, 48 + 24*5 + 6*5, "��", 24, 0, RED);


	setcolor(WHITE);
	settextstyle(3, HORIZ_DIR, 1);
	puthz(25, 49, "����", 16, 17, WHITE);
	outtextxy(25 + 17 * 2 + 4, 42, "K");
	puthz(25 + 17 * 3, 49, "��", 16, 17, WHITE);
	outtextxy(25 + 17 * 4 + 2, 42, ":");
	line(25, 68, 225, 68);
	puthz(35, 80, "һ����ͣ��", 16, 17, WHITE);
	draw_element(35 + 17 * 5 + 4, 83, 1, WHITE);//����ť

	puthz(35, 80 + 30, "����Ӱ��", 16, 17, WHITE);
	draw_element(35 + 17 * 5 + 4, 83 + 30, 1, WHITE);//����ť

	puthz(35, 80 + 30 * 2, "������", 16, 17, WHITE);
	draw_element(35 + 17 * 5 + 4, 83 + 30 * 2, 1, WHITE);//����ť


	setcolor(YELLOW);
	settextstyle(3, HORIZ_DIR, 1);
	puthz(312, 49, "����", 16, 17, YELLOW);
	outtextxy(312 + 17 * 2 + 4, 42, "K");
	puthz(312 + 17 * 3, 49, "��", 16, 17, YELLOW);
	outtextxy(312 + 17 * 4 + 2, 42, ":");
	line(312, 68, 512, 68);
	puthz(322, 80, "�෽ѹ��", 16, 17, YELLOW);
	draw_element(322 + 17 * 5 + 4, 83, 1, YELLOW);//����ť

	puthz(322, 80 + 30, "�շ�ѹ��", 16, 17, YELLOW);
	draw_element(322 + 17 * 5 + 4, 83 + 30, 1, YELLOW);//����ť

	puthz(322, 80 + 30 * 2, "����ͣ��", 16, 17, YELLOW);
	draw_element(322 + 17 * 5 + 4, 83 + 30 * 2, 1, YELLOW);//����ť


	setcolor(LIGHTRED);
	settextstyle(3, HORIZ_DIR, 1);
	puthz(25, 168, "����", 16, 17, LIGHTRED);
	outtextxy(25 + 17 * 2 + 4, 162, "K");
	puthz(25 + 17 * 3, 168, "��", 16, 17, LIGHTRED);
	outtextxy(25 + 17 * 4 + 2, 162, ":");
	line(25, 188, 200, 188);
	puthz(35, 200, "������", 16, 17, LIGHTRED);
	draw_element(35 + 17 * 5 + 4, 203, 1, LIGHTRED);//����ť

	puthz(35, 200 + 30, "������", 16, 17, LIGHTRED);
	draw_element(35 + 17 * 5 + 4, 203 + 30, 1, LIGHTRED);//����ť

	puthz(35, 200 + 30 * 2, "���η�ת", 16, 17, LIGHTRED);
	draw_element(35 + 17 * 5 + 4, 203 + 30 * 2, 1, LIGHTRED);//����ť


	setcolor(LIGHTBLUE);
	settextstyle(3, HORIZ_DIR, 1);
	puthz(312, 168, "���", 16, 17, LIGHTBLUE);
	outtextxy(312 + 17 * 2 + 4, 162, "K");
	puthz(312 + 17 * 3, 168, "��", 16, 17, LIGHTBLUE);
	outtextxy(312 + 17 * 4 + 2, 162, ":");
	line(312, 188, 512, 188);
	puthz(322, 200, "��ˮܽ��", 16, 17, LIGHTBLUE);
	draw_element(322 + 17 * 5 + 4, 203, 1, LIGHTBLUE);//����ť

	puthz(322, 200 + 30, "��ͷա��", 16, 17, LIGHTBLUE);
	draw_element(322 + 17 * 5 + 4, 203 + 30, 1, LIGHTBLUE);//����ť

	setcolor(CYAN);
	line(0, 290, 24, 314);
	line(24, 314, 600, 314);
	line(24, 314, 24, 314 + 140);
	settextstyle(3, HORIZ_DIR, 1);
	outtextxy(2, 314, "MA");
	puthz(0, 314 + 24 + 6, "��", 24, 0, CYAN);
	puthz(0, 314 + 24 * 2 + 6 * 2, "̬", 24, 0, CYAN);
	puthz(0, 314 + 24 * 3 + 6 * 3, "ѡ", 24, 0, CYAN);
	puthz(0, 314 + 24 * 4 + 6 * 4, "��", 24, 0, CYAN);

	setcolor(WHITE);
	settextstyle(3, HORIZ_DIR, 1);
	puthz(45, 325, "��ͷ����", 16, 17, WHITE);
	draw_element(45 + 17 * 4 + 12, 332, 2, WHITE);//����ť
	puthz(210, 325, "��ͷ����", 16, 17, WHITE);
	draw_element(210 + 17 * 4 + 12, 332, 2, WHITE);//����ť

	puthz(45, 325 + 40, "ճ��", 16, 17, YELLOW);
	draw_element(45 + 17 * 4 + 12, 332 + 40, 2, YELLOW);//����ť
	puthz(210, 325 + 40, "��ɢ", 16, 17, YELLOW);
	draw_element(210 + 17 * 4 + 12, 332 + 40, 2, YELLOW);//����ť

	puthz(45, 325 + 40 * 2, "��ͷ����", 16, 17, LIGHTMAGENTA);
	draw_element(45 + 17 * 4 + 12, 332 + 40 * 2, 2, LIGHTMAGENTA);//����ť
	puthz(210, 325 + 40 * 2, "��ͷ����", 16, 17, LIGHTMAGENTA);
	draw_element(210 + 17 * 4 + 12, 332 + 40 * 2, 2, LIGHTMAGENTA);//����ť

	setcolor(WHITE);
	setfillstyle(SOLID_FILL, CYAN);
	bar3d(250, 452, 290, 479, 5, 1);
	puthz(255, 457, "ѡ��", 16, 17, WHITE);

	setcolor(WHITE);
	setfillstyle(SOLID_FILL, BLUE);
	bar3d(560, 452, 620, 479, 5, 1);
	puthz(565, 457, "��һҳ", 16, 17, WHITE);

}

/*********************************************
FUNCTION:draw_T_stoselect1
DESCRIPTION��������ѡ�ɵڶ�ҳ����
INPUT:void
RETURN:��
***********************************************/
void draw_T_stoselect2(void)
{
	setbkcolor(BLACK);
	setlinestyle(SOLID_LINE, 0, 3);
	setfillstyle(SOLID_FILL, WHITE);
	settextjustify(LEFT_TEXT, TOP_TEXT);
	settextstyle(2, HORIZ_DIR, 6);

	//KDJ
	setfillstyle(SOLID_FILL, WHITE);
	bar(0, 24, 260, 44);
	setcolor(RED);
	line(0, 46, 260, 46);
	setlinestyle(SOLID_LINE, 0, 1);
	line(0, 52, 260, 52);
	line(0, 58, 260, 58);
	puthz(5, 26, "���ָ��", 16, 17, BLACK);
	outtextxy(10 + 17 * 4, 24, "KDJ");
	//KDJָ������̬
	setcolor(WHITE);
	outtextxy(5, 58+4, "KD");
	puthz(24, 58 + 6, "���", 16, 17, WHITE);
	puthz(140, 58 + 6, "����", 16, 17, WHITE);
	outtextxy(5, 58 + 32 + 4, "J");
	puthz(15, 58 + 32 + 6, "����", 16, 17, WHITE);
	puthz(140, 58 + 32 + 6, "����", 16, 17, WHITE);
	draw_element(24 + 90, 58 + 10, 1, RED);
	draw_element(144 + 90, 58 + 10, 1, RED);
	draw_element(24 + 90, 58 + 32 + 10, 1, RED);
	draw_element(144 + 90, 58 + 32 + 10, 1, RED);

	//MACD
	setfillstyle(SOLID_FILL, WHITE);
	bar(320, 24, 580, 44);
	setcolor(BLUE);
	setlinestyle(SOLID_LINE, 0, 3);
	line(320, 46, 580, 46);
	setlinestyle(SOLID_LINE, 0, 1);
	line(320, 52, 580, 52);
	line(320, 58, 580, 58);
	puthz(325, 26, "��ͬ�ƶ�ƽ����", 16, 17, BLACK);
	outtextxy(330 + 17 * 7, 24, "MACD");
	//MACDָ������̬
	setcolor(WHITE);
	puthz(320, 58 + 6, "������", 16, 17, WHITE);
	puthz(460, 58 + 6, "�ױ���", 16, 17, WHITE);
	puthz(320, 58 + 32 + 6, "���", 16, 17, WHITE);
	puthz(460, 58 + 32 + 6, "����", 16, 17, WHITE);
	draw_element(344 + 90, 58 + 10, 1, BLUE);
	draw_element(464 + 90, 58 + 10, 1, BLUE);
	draw_element(344 + 90, 58 + 32 + 10, 1, BLUE);
	draw_element(464 + 90, 58 + 32 + 10, 1, BLUE);


	//RSI
	setfillstyle(SOLID_FILL, WHITE);
	bar(0, 164, 260, 184);
	setcolor(BROWN);
	setlinestyle(SOLID_LINE, 0, 3);
	line(0, 186, 260, 186);
	setlinestyle(SOLID_LINE, 0, 1);
	line(0, 192, 260, 192);
	line(0, 198, 260, 198);
	puthz(5, 166, "���ǿ��ָ��", 16, 17, BLACK);
	outtextxy(10 + 17 * 6, 164, "RSI");
	//RSIָ������̬
	setcolor(WHITE);
	puthz(5, 198 + 6, "����", 16, 17, WHITE);
	outtextxy(10 + 17 * 2, 198 + 4, "(>80)");
	puthz(5, 198 + 32 + 6, "����", 16, 17, WHITE);
	outtextxy(10 + 17 * 2, 198 + 32+ 4, "(<20)");
	draw_element(24 + 90, 198 + 10, 1, BROWN);
	draw_element(24 + 90, 198 + 32 + 10, 1, BROWN);


	//VOL/OBV
	setfillstyle(SOLID_FILL, WHITE);
	bar(320, 164, 580, 184);
	setcolor(GREEN);
	setlinestyle(SOLID_LINE, 0, 3);
	line(320, 186, 580, 186);
	setlinestyle(SOLID_LINE, 0, 1);
	line(320, 192, 580, 192);
	line(320, 198, 580, 198);
	puthz(325, 166, "�ɽ���", 16, 17, BLACK);
	setcolor(BLACK);
	outtextxy(326 + 17 * 3, 164, "/");
	puthz(386, 166, "������", 16, 17, BLACK);
	setcolor(GREEN);
	outtextxy(391 + 17 * 3, 164, "VOL/OBV");
	//VOL/OBVָ������̬
	setcolor(WHITE);
	puthz(320, 198 + 6, "��������", 16, 17, WHITE);
	puthz(320, 198 + 32 + 6, "�µ�����", 16, 17, WHITE);
	draw_element(344 + 90, 198 + 10, 1, GREEN);
	draw_element(344 + 90, 198 + 32 + 10, 1, GREEN);


	//BIAS
	setfillstyle(SOLID_FILL, WHITE);
	bar(0, 304, 260, 324);
	setcolor(LIGHTMAGENTA);
	setlinestyle(SOLID_LINE, 0, 3);
	line(0, 326, 260, 326);
	setlinestyle(SOLID_LINE, 0, 1);
	line(0, 332, 260, 332);
	line(0, 338, 260, 338);
	puthz(5, 306, "������", 16, 17, BLACK);
	outtextxy(10 + 17 * 3, 304, "BIAS");
	//BIASָ������̬
	setcolor(WHITE);
	puthz(5, 338 + 6, "����", 16, 17, WHITE);
	outtextxy(10 + 17 * 2, 338 + 4, "(>16%)");
	puthz(5, 338 + 32 + 6, "����", 16, 17, WHITE);
	outtextxy(10 + 17 * 2, 338 + 32 + 4, "(<-16%)");
	draw_element(24 + 90, 338 + 10, 1, LIGHTMAGENTA);
	draw_element(24 + 90, 338 + 32 + 10, 1, LIGHTMAGENTA);


	//BOLL
	setfillstyle(SOLID_FILL, WHITE);
	bar(320, 304, 580, 324);
	setcolor(LIGHTCYAN);
	setlinestyle(SOLID_LINE, 0, 3);
	line(320, 326, 580, 326);
	setlinestyle(SOLID_LINE, 0, 1);
	line(320, 332, 580, 332);
	line(320, 338, 580, 338);
	puthz(325, 306, "���ִ�", 16, 17, BLACK);
	outtextxy(330 + 17 * 3, 304, "BOLL");
	//BOLLָ������̬
	setcolor(WHITE);
	puthz(320, 338 + 32 + 6, "ͻ��", 16, 17, WHITE);
	line(325 + 17 * 2, 338 + 6 + 8, 325 + 17 * 2 + 20, 338 + 6 + 8);
	puthz(325 + 54 + 5, 338 + 6, "�Ϲ�", 16, 17, WHITE);
	line(325 + 17 * 2, 338 + 32 + 6 + 8, 325 + 17 * 2 + 20, 338 + 32 + 6 + 8);
	puthz(325 + 54 + 5, 338 + 32 + 6, "�й�", 16, 17, WHITE);
	line(325 + 17 * 2, 338 + 64 + 6 + 8, 325 + 17 * 2 + 20, 338 + 64 + 6 + 8);
	puthz(325 + 54 + 5, 338 + 64 + 6, "�¹�", 16, 17, WHITE);
	line(325 + 34, 338 + 14, 325 + 34, 338 + 64 + 14);
	draw_element(344 + 90, 338 + 10, 1, LIGHTCYAN);
	draw_element(344 + 90, 338 + 32 + 10, 1, LIGHTCYAN);
	draw_element(344 + 90, 338 + 64 + 10, 1, LIGHTCYAN);

	setcolor(WHITE);
	setfillstyle(SOLID_FILL, LIGHTMAGENTA);
	bar3d(250, 452, 290, 479, 5, 1);
	puthz(255, 457, "ѡ��", 16, 17, WHITE);


	setcolor(WHITE);
	setfillstyle(SOLID_FILL, RED);
	bar3d(20, 452, 80, 479, 5, 1);
	puthz(25, 457, "��һҳ", 16, 17, WHITE);
}


/*********************************************
FUNCTION:draw_element
DESCRIPTION��������ѡ��Ԫ�ػ���
INPUT:x,y,state,color
RETURN:��
***********************************************/
void draw_element(int x, int y, int state,int color)
{
	switch (state)
	{
	case 1:
		setfillstyle(SOLID_FILL, color);
		bar3d(x, y, x + 10, y + 10, 5, 1);
		break;
	case 2:
		setcolor(color);
		circle(x, y, 5);
		break;
	}
}