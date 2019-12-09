#include"public.h"
#include"about.h"

/*****************************************
about.c
COPYRIGHT:	weijingmin
FUNCTION:	detail infomation for software
ABSTRACT:
		A.show about
		B.show help
DATE:2019/11/6
******************************************/


/*********************************************
FUNCTION:About
DESCRIPTION�����ڽ����ܿ�
INPUT:cinfo,u
RETURN:��
***********************************************/
void About(Ctr* cinfo, USER* u)//����
{
	int num = 0;//��ť���
	int cnt = 0;
	memset(cinfo, 0, sizeof(Ctr));
	cinfo->func = 7;            //��7��ǹ��ں���
	clrmous(MouseX, MouseY);
	cleardevice();
	mainmenu_draw();
	control_judge(u);
	About_show();
	while (1)
	{
		if (!bioskey(1))
		{
			newmouse(&MouseX, &MouseY, &press);
			control_mouse(cinfo, u);
		}
		else if (bioskey(1))
		{
			cinfo->key = bioskey(0);
		}
		control_key(cinfo);
		if (control_menu(cinfo))
		{
			cleardevice();
			mainmenu_draw();
			control_judge(u);
			submenu_draw(cinfo->itemnum);
			About_show();
			continue;
		}

		if (cinfo->func != 7 && cinfo->func != 15)
		{
			clrmous(MouseX, MouseY);
			delay(10);
			return;
		}

		if (MouseX > 590 && MouseX < 630 && MouseY > 400 && MouseY < 420)//ת��
		{
			if (mouse_press(590, 400, 630, 420) == 2)//δ���
			{
				MouseS = 1;
				if (num == 0)//��ֹ���ظ�����
				{
					lightbutton_about(590, 400, 630, 420, WHITE, LIGHTBLUE);
					num = 1;
				}
				continue;

				//��������
			}

			if (mouse_press(590, 400, 630, 420) == 1)//&& cinfo->itemnum == 0)
			{
				MouseS = 0;
				lightbutton_about(590, 400, 630, 420, WHITE, LIGHTBLUE);
				cnt = (cnt + 1) % 2;
				switch (cnt)
				{
				case 0:
					About_show();//��ʾ����
					break;
				case 1:
					Help_show();
					break;
				}
				continue;
				//���޸�
			}
		}

		if (num != 0)
		{
			MouseS = 0;
			recoverbutton_about(num);
			num = 0;
		}
		if (MouseS != 0)
		{
			MouseS = 0;
		}
	}
}

/*********************************************
FUNCTION:lightbutton_about
DESCRIPTION��About��ť����
INPUT:x,y,x1,y1,color1,color2
RETURN:��
***********************************************/
void lightbutton_about(int x, int y, int x1, int y1, int color1, int color2)//About��ť����
{
	clrmous(MouseX, MouseY);
	delay(10);
	setcolor(color1);
	setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
	setfillstyle(1, color2);
	bar(x, y, x1, y1);
	rectangle(x, y, x1, y1);	//���߿�
	puthz(595, 402, "�л�", 16, 17, BLUE);
}

/*********************************************
FUNCTION:recoverbutton_about
DESCRIPTION��About��ť�ָ�
INPUT:status
RETURN:��
***********************************************/
void recoverbutton_about(int status)//About��ť�ָ�
{
	clrmous(MouseX, MouseY);

	switch (status)
	{
	case 1:
		setfillstyle(SOLID_FILL, BLUE);
		bar(590, 400, 630, 420);
		puthz(595, 402, "�л�", 16, 17, WHITE);
		break;
	}
}

/*********************************************
FUNCTION:About_show
DESCRIPTION����ʾ������Ϣ
INPUT:void
RETURN:��
***********************************************/
void About_show(void)
{
	int i, j;

	delay(300);
	setfillstyle(SOLID_FILL, BLACK);
	bar(1, 24, 639, 479);
	setbkcolor(BLACK);
	settextjustify(LEFT_TEXT, TOP_TEXT);
	settextstyle(2, HORIZ_DIR, 6);
	/*
	- ������Ա�����пƼ���ѧ�˹��������Զ���ѧԺ
				�Զ���1801κ���F��������
	- ������Ա�����пƼ���ѧ�˹��������Զ���ѧԺC���Խ��ڡ�������
	- �������ڣ�2019/11/4
	- ��С��89.6M
	- version:1.0.0

		�����Ϊ���ż���Ʒ���Ե�������Ҫ��ϵ͡�
		���������Ϊ�κ���ҵ��;������������κ�Υ����߳�Ϯ�����
	����Ϯ���󣬿����߽��е�����Ȩ׷�������Ρ�
		������Ŀ���Ŀ�ģ���Ϊ�˷���֤ȯ��ҵ��Ա����Ͷ����Ա��ģ��
	������Ͷ�ʣ��Լ�ѧϰ֤ȯ���������������Դ��ͨ����2009/1/5
	----2019/9/23`(ƽ������<-->���·�չ)������κ�������ʧ�����⣬
	���򿪷��߷����������߽������޸ĺ����ơ�

		����������лC���Կγ���Ƶ�������ʦ�����̣��Լ�������
	���ǵ�ͬѧ����������кܶ಻������ǿɸ����Ż��ĵط���ϣ������
	�������ƺͿ����������ߵĸ�Զ��
	*/
	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 620; j++)
		{
			putpixel(10 + 10 * j, 40 + 20 * i, LIGHTRED);
		}
	}
	puthz(10, 40, "������Ա�����пƼ���ѧ�˹��������Զ���ѧԺ", 16, 17, WHITE);

	puthz(10+17*5, 60, "�Զ���", 16, 17, RED);
	setcolor(RED);
	outtextxy(13 + 17 * 8, 57, "1801");
	puthz(10 + 17 * 12, 60, "κ��", 16, 17, YELLOW);
	setcolor(YELLOW);
	outtextxy(13 + 17 * 14, 57, "min | ");
	puthz(10 + 17 * 17, 60, "������", 16, 17, YELLOW);

	puthz(10, 80, "������Ա�����пƼ���ѧ�˹��������Զ���ѧԺ", 16, 17, WHITE);
	setcolor(RED);
	outtextxy(13 + 17 * 21, 77, "C");
	puthz(10 + 22 * 17, 80, "���Խ��ڡ�������", 16, 17, WHITE);

	puthz(10, 100, "�������ڣ�", 16, 17, WHITE);
	setcolor(RED);
	outtextxy(13 + 17 * 5, 97, "2019/11/9");

	puthz(10, 120, "��С��", 16, 17, WHITE);
	setcolor(YELLOW);
	outtextxy(13 + 17 * 3, 117, "29.2M");

	setcolor(LIGHTCYAN);
	outtextxy(10, 137, "VERSION: 1.0.2");

	puthz(10 + 17 * 2, 180, "�����Ϊ���ż���Ʒ���Ե�������Ҫ��ϵ͡�", 16, 17, WHITE);

	puthz(10 + 17 * 2, 200, "���������Ϊ�κ���ҵ��;������������κ�Υ����߳�Ϯ�����", 16, 17, WHITE);
	puthz(10, 220, "����Ϯ���󣬿����߽��е�����Ȩ׷�������Ρ�", 16, 17, WHITE);

	puthz(10 + 17 * 2, 240, "������Ŀ���Ŀ�ģ���Ϊ�˷���֤ȯ��ҵ��Ա����Ͷ����Ա��ģ��", 16, 17, WHITE);
	puthz(10, 260, "������Ͷ�ʣ��Լ�ѧϰ֤ȯ���������������Դ��ͨ����", 16, 17, WHITE);
	setcolor(RED);
	outtextxy(13 + 17 * 25, 257, "2009/1/5--2019/9/23");
	puthz(10, 280, "��ƽ�����С������·�չ��������κ�������ʧ�����⣬���򿪷��߷�", 16, 17, WHITE);
	puthz(10, 300, "���������߽������޸ĺ����ơ�", 16, 17, WHITE);
	
	puthz(10+17*2, 320, "����������л", 16, 17, WHITE);
	outtextxy(13 + 17 * 10, 317, "C");
	puthz(10 + 17 * 11, 320, "���Կγ���Ƶ�������ʦ�����̣��Լ�������", 16, 17, WHITE);
	puthz(10, 340, "���ǵ�ͬѧ����������кܶ಻������ǿɸ����Ż��ĵط���ϣ������", 16, 17, WHITE);
	puthz(10, 360, "��һֱ�Ȱ�",16, 17, WHITE);
	outtextxy(13 + 17 * 5, 357, "C");
	puthz(13 + 17 * 6, 360, "���Ժͱ����ƣ���������������ߵĸ�Զ��", 16, 17, WHITE);

	
	settextjustify(LEFT_TEXT, TOP_TEXT);
	settextstyle(3, HORIZ_DIR, 4);
	setcolor(RED);
	outtextxy(125, 390, "HUST:");
	settextjustify(LEFT_TEXT, TOP_TEXT);
	settextstyle(2, HORIZ_DIR, 8);
	setcolor(LIGHTRED);
	outtextxy(200, 400, "	  SCHOOL OF");
	setcolor(LIGHTCYAN);
	outtextxy(50, 430, "ARTIFICIAL INTELLIGENCE AND AUTOMATION");

	setfillstyle(SOLID_FILL, BLUE);
	bar(590, 400, 630, 420);
	puthz(595, 402, "�л�", 16, 17, WHITE);
}


/*********************************************
FUNCTION:Help_show
DESCRIPTION����ʾ������Ϣ
INPUT:void
RETURN:��
***********************************************/
void Help_show(void)
{
	int i, j;

	delay(300);
	setfillstyle(SOLID_FILL, BLACK);
	bar(1, 24, 639, 479);
	setbkcolor(BLACK);
	settextjustify(LEFT_TEXT, TOP_TEXT);
	settextstyle(2, HORIZ_DIR, 6);
	/*
	- ������ֿ�ݼ�����˵��

	  ���˵���F1�ɴ�ϵͳ�˵���F2�ɽ��� ���飬F3�ɽ��뻦�
	F4�ɽ���ѡ�ɣ�F5�ɽ��뽻�ף�F6�ɽ������

	  ������棺�û�ͨ��UP����DOWN��������ҳ�����ת���ɲ�
	������֧��Ʊ����ϸ��Ϣ

	  ������棺�û�ͨ��UP����DOWN�������й�Ʊ���е���ת��
	ͨ��LEFT��RIGHT���ɲ鿴�ø���ʮ�����κ�һ�����Ϣ��ͨ��
	1,2,3���л���ͬ�Ļ�����ģʽ

	  ����->��ʷ��¼���棺�û�ͨ��UP����DOWN����������ʷ
	��¼�ķ�ҳ

	  ����->�ֲֽ��棺�û�ͨ��UP����DOWN�������гֲ���Ϣ�ķ�ҳ
	*/
	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 620; j++)
		{
			putpixel(10 + 10 * j, 40 + 20 * i, LIGHTCYAN);
		}
	}

	puthz(10 + 17 * 2, 40, "������ֿ�ݼ�����˵��", 16, 17, WHITE);

	puthz(10 + 17 * 2, 80, "���˵���", 16, 17, WHITE);
	setcolor(RED);
	outtextxy(13 + 17 * 6, 77, "F1");
	puthz(10 + 17 * 8, 80, "�ɴ�ϵͳ�˵���", 16, 17, WHITE);
	outtextxy(13 + 17 * 16, 77, "F2");
	puthz(10 + 17 * 18, 80, "�ɽ������飬", 16, 17, WHITE);
	outtextxy(13 + 17 * 24, 77, "F3");
	puthz(10 + 17 * 26, 80, "�ɽ��뻦�", 16, 17, WHITE);
	outtextxy(13, 97, "F4");
	puthz(10 + 17 * 2, 100, "�ɽ���ѡ�ɣ�", 16, 17, WHITE);
	outtextxy(13 + 17 * 8, 97, "F5");
	puthz(10 + 17 * 10, 100, "�ɽ��뽻�ף�", 16, 17, WHITE);
	outtextxy(10 + 17 * 16, 97, "F6");
	puthz(10 + 17 * 18, 100, "�ɽ������", 16, 17, WHITE);

	puthz(10 + 17 * 2, 140, "������棺�û�ͨ��", 16, 17, WHITE);
	outtextxy(15 + 17 * 11, 137, "UP");
	puthz(10 + 17 * 13, 140, "����", 16, 17, WHITE);
	outtextxy(20 + 17 * 15, 137, "DOWN");
	puthz(10 + 17 * 19, 140, "��������ҳ�����ת���ɲ�", 16, 17, WHITE);
	puthz(10, 160, "������֧��Ʊ����ϸ��Ϣ", 16, 17, WHITE);

	puthz(10 + 17 * 2, 200, "������棺�û�ͨ��", 16, 17, WHITE);
	outtextxy(15 + 17 * 11, 197, "UP");
	puthz(10 + 17 * 13, 200, "����", 16, 17, WHITE);
	outtextxy(23 + 17 * 15, 197, "DOWN");
	puthz(10 + 17 * 19, 200, "�������й�Ʊ���е���ת��ͨ", 16, 17, WHITE);
	puthz(10, 220, "��", 16, 17, WHITE);
	outtextxy(20 + 17, 217, "LEFT");
	puthz(10 + 17 * 4, 220, "��", 16, 17, WHITE);
	outtextxy(23 + 17 * 5, 217, "RIGHT");
	puthz(10 + 17 * 9, 220, "���ɲ鿴�ø���ʮ�����κ�һ�����Ϣ��ͨ��", 16, 17, WHITE);
	outtextxy(10, 240, "1,2,3");
	puthz(10 + 17 * 3, 240, "���л���ͬ�Ļ�����ģʽ", 16, 17, WHITE);

	puthz(10 + 17 * 2, 280, "���ɡ�����ʷ��¼���棺�û�ͨ��", 16, 17, WHITE);
	outtextxy(15 + 17 * 17, 277, "UP");
	puthz(10 + 17 * 19, 280, "����", 16, 17, WHITE);
	outtextxy(23 + 17 * 21, 277, "DOWN");
	puthz(10 + 17 * 25, 280, "����������ʷ", 16, 17, WHITE);
	puthz(10, 300, "��¼�ķ�ҳ", 16, 17, WHITE);

	puthz(10 + 17 * 2, 340, "���ˡ����ֲֽ��棺�û�ͨ��", 16, 17, WHITE);
	outtextxy(15 + 17 * 15, 337, "UP");
	puthz(10 + 17 * 17, 340, "����", 16, 17, WHITE);
	outtextxy(23 + 17 * 19, 337, "DOWN");
	puthz(10 + 17 * 23, 340, "�������гֲ���Ϣ�ķ�ҳ", 16, 17, WHITE);

	settextjustify(LEFT_TEXT, TOP_TEXT);
	settextstyle(3, HORIZ_DIR, 4);
	setcolor(RED);
	outtextxy(125, 390, "HUST:");
	settextjustify(LEFT_TEXT, TOP_TEXT);
	settextstyle(2, HORIZ_DIR, 8);
	setcolor(LIGHTRED);
	outtextxy(200, 400, "	  SCHOOL OF");
	setcolor(LIGHTCYAN);
	outtextxy(50, 430, "ARTIFICIAL INTELLIGENCE AND AUTOMATION");

	setfillstyle(SOLID_FILL, BLUE);
	bar(590, 400, 630, 420);
	puthz(595, 402, "�л�", 16, 17, WHITE);
}
