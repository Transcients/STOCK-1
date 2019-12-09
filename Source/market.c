#include"public.h"
#include"market.h"
#include"storead.h"
#include"techline.h"
#include"marketfc.h"
#include"qsearch.h"
#include"trade.h"
#include"traverse.h"

/*****************************************
market.c
COPYRIGHT:	weijingmin
FUNCTION:	market information
ABSTRACT:
		A.show market
		B.function calling and control
		C.button lighting and recovering
DATE:2019/10/4
******************************************/

/*********************************************
FUNCTION:sto_market
DESCRIPTION����������ܿ�
INPUT:cinfo,u��sto_num,sto_name
RETURN:��
***********************************************/
void sto_market(Ctr* cinfo, USER* u, int sto_num, char* sto_name)//Ҫ��ȡ��ĳֻ��Ʊ�ı��;�����ӻ������������
{
	int i;
	int j = 0;
	int key = 0;
	long int sto_date = 1;//Ҫ��ȡ��ĳֻ�ɵ���Ϣ�Ŀ�ʼ����,�е�Сbug
	int page = 0;//����Ʊ�б��ʼҳ
	int num = 0;	//��ť���
	int pos[25] = { 0 };   //���ÿһҳ��ʼ�ֽڵ�����
	int sto_No[8] = { 0 };	//��Ź�Ʊ��ŵ����飬��������е�sto_num���ܻ���
	int day = 0;	//������
	int preday = 0;	//������գ���ֹ��˸
	int kind = 0;	//kindΪ0������ͼ��4���������ݣ�����kindΪ1��3��
	int colorkind = 1;	//��ͬ��colorkind��Ӧ��ͬ�ĸ�ͼ�������
	float max = 0.0, min = 0.0;//�߽����ֵ����Сֵ
	int read_way = 1;//��Ʊ��ʾ�ķ�ʽ��1Ϊÿ���л�һ�죬2Ϊ30�죬3Ϊ60��
	int sto = 1;	//��������Ʊ������鸳ֵ�ı���
	//int maxline = 0;	//�����洢���ݿ�ĩ����������������
	struct tm* tp = NULL;	//ʱ����ʾ�ṹ��
	int minute;//��ʾʱ��
	STODAYFLOAT info[150];	//150���Ʊ��Ϣ�Ľṹ������
	//MarketQueue* Q = NULL;	//��Ʊ����
	MarketQueue Q;
	UPLINE upinfo;	//�����ͼ��Ϣ�Ľṹ��
	DOWNLINE downinfo;	//��Ÿ�ͼ��Ϣ�Ľṹ��
	memset(cinfo,0,sizeof(Ctr));	   //��������Ϣ��ʼ��
	cinfo->func = 4;     		       //��4������麯��
	clrmous(MouseX, MouseY);
	delay(100);
	cleardevice();
	draw_market();
	get_markettime(tp, &minute, 1);	//���ʱ��
	mainmenu_draw();
	control_judge(u);

	memset(info, 0.0, 150 * sizeof(STODAYFLOAT));
	pos[0] = 0;
	put_marketqueue(pos);//Ϊ���з���ռ�,��ø�ҳλ�ò���ʼ��
	/*if ((Q = (MarketQueue*)malloc(sizeof(MarketQueue))) == NULL)
	{
		printf("memoryallocation runs wrong");
		delay(3000);
		exit(1);
	}*/
	klinequeue(&Q);//��ʼ������ļ�ָ��λ��
	sto_daybyday2float(sto_num, sto_date, 150, info);//1Ϊ��Ʊ��ţ�1Ϊ��ʼ������150Ϊ��ȡ����
	get_border(info, &max, &min, 150);//150Ϊ��ȡ����
	Kline_draw(info, max, min);
	MA_draw(info, &upinfo, max, min);
	VOL_draw(info, &downinfo);
	sto = 1;
	for (i = 0; i < 8; i++)
	{
		sto_No[i] = sto;//����ֵ1-8
		sto++;
	}
	//maxline = check_database(sto_num);//���ݿ�ĩ�˵��������ظ�maxline
	output_stoname(sto_name);//��ӡ��ϣ�����Ľ��
	while (1)
	{
		if(bioskey(1))
		{
			key = bioskey(0);
			cinfo->key = key;
			if (key == DOWN)
			{
				delay(50);
				page = (page + 1) % 25;//�������һ�棬��ת����һ��
				setfillstyle(SOLID_FILL, BLACK);
				bar(1, 145, 71, 429);
				setlinestyle(SOLID_LINE, 0, 1);
				setcolor(RED);
				for (i = 0; i < 9; i++)
				{
					line(0, 144 + 36 * i, 72, 144 + 36 * i);
				}
				input_klinequeue(&Q, pos[page]);
				queuedown(&sto, sto_No, 8);//������������sto_No��ÿһҳ��ֵ
				cinfo->key = 0;

				setfillstyle(SOLID_FILL, DARKGRAY);
				bar(73, 154, 79, 427);
				setfillstyle(SOLID_FILL, BLACK);
				bar(73, 170 + 10 * page, 79, 180 + 10 * page);//�������任
				continue;
			}
			else if (key == UP)
			{
				delay(50);
				page--;
				if (page == -1)
				{
					page = 24;//�����һ��
				}
				setfillstyle(SOLID_FILL, BLACK);
				bar(1, 145, 71, 429);
				setlinestyle(SOLID_LINE, 0, 1);
				setcolor(RED);
				for (i = 0; i < 9; i++)
				{
					line(0, 144 + 36 * i, 72, 144 + 36 * i);
				}
				input_klinequeue(&Q, pos[page]);
				queueup(&sto, sto_No, 8);//������������sto_No��ÿһҳ��ֵ
				cinfo->key = 0;

				setfillstyle(SOLID_FILL, DARKGRAY);
				bar(73, 154, 79, 427);
				setfillstyle(SOLID_FILL, BLACK);
				bar(73, 170 + 10 * page, 79, 180 + 10 * page);//�������任
				continue;
			}
			else if (key == LEFT)
			{
				delay(50);
				memset(info, 0.0, 150 * sizeof(STODAYFLOAT));
				change_datadate(sto_num, &sto_date, info, &upinfo, &downinfo, &max, &min, read_way, 1);//maxline);//���Ĺ�Ʊ����ʾ����
				colorkind = 1;
			}
			else if (key == RIGHT)
			{
				delay(50);
				memset(info, 0.0, 150 * sizeof(STODAYFLOAT));
				change_datadate(sto_num, &sto_date, info, &upinfo, &downinfo, &max, &min, read_way, 2);//maxline);//���Ĺ�Ʊ����ʾ����
				colorkind = 1;
			}
			else if (key == ONE)
			{
				read_way = 1;
			}
			else if (key == TWO)
			{
				read_way = 2;
			}
			else if (key == THREE)
			{
				read_way = 3;
			}
			control_key(cinfo);  //���̿���
			continue;
		}
		else if (!bioskey(1))
		{
			newmouse(&MouseX, &MouseY, &press);
			control_mouse(cinfo,u);
		}
		
		
		if(control_menu(cinfo))
		{
			draw_market();
			control_judge(u);
			Kline_draw(info, max, min);
			MA_draw(info, &upinfo, max, min);
			VOL_draw(info, &downinfo);
			get_markettime(tp, &minute, 1);//���»��ʱ��
			input_klinequeue(&Q, pos[page]);
			submenu_draw(cinfo->itemnum);
			output_stoname(sto_name);//��ӡ��ϣ�����Ľ��
		}
		
		if(cinfo->func != 4 && cinfo->func != 8)
		{
			clrmous(MouseX,MouseY);
			delay(50);                    //��ֹ����
			return; 	 //��������������ܼ����ͷ��أ�����ǻ��ԭ����������ж�
		}
		
		/********************
		��Ʊ����ת��
		*********************/
		if (mouse_press(72, 427, 80, 434) == 1)
		{
			delay(50);
			page = (page + 1) % 25;//�������һ�棬��ת����һ��
			setfillstyle(SOLID_FILL, BLACK);
			bar(1, 145, 71, 429);
			setlinestyle(SOLID_LINE, 0, 1);
			setcolor(RED);
			for (i = 0; i < 9; i++)
			{
				line(0, 144 + 36 * i, 72, 144 + 36 * i);
			}
			input_klinequeue(&Q, pos[page]);
			queuedown(&sto, sto_No, 8);//������������sto_No��ÿһҳ��ֵ

			setfillstyle(SOLID_FILL, DARKGRAY);
			bar(73, 154, 79, 427);
			setfillstyle(SOLID_FILL, BLACK);
			bar(73, 170 + 10 * page, 79, 180 + 10 * page);//�������任
			continue;
		}
		if (mouse_press(72, 147, 80, 154) == 1)
		{
			delay(50);
			page--;
			if (page == -1)
			{
				page = 24;//�����һ��
			}
			/*cleardevice();
			draw_market();*/
			setfillstyle(SOLID_FILL, BLACK);
			bar(1, 145, 71, 429);
			setlinestyle(SOLID_LINE, 0, 1);
			setcolor(RED);
			for (i = 0; i < 9; i++)
			{
				line(0, 144 + 36 * i, 72, 144 + 36 * i);
			}
			input_klinequeue(&Q, pos[page]);
			queueup(&sto, sto_No, 8);//������������sto_No��ÿһҳ��ֵ
			

			setfillstyle(SOLID_FILL, DARKGRAY);
			bar(73, 154, 79, 427);
			setfillstyle(SOLID_FILL, BLACK);
			bar(73, 170 + 10 * page, 79, 180 + 10 * page);//�������任
			continue;
		}
		/********************
		���ĸ���
		*********************/
		if (mouse_press(0, 144, 72, 432) == 1)
		{
			memset(info, 0.0, 150 * sizeof(STODAYFLOAT));
			//maxline = change_sto(&sto_num, sto_No, sto_date, info, &upinfo, &downinfo, &max, &min);//���ݿ�ĩ�˵��������ظ�maxline
			change_sto(&sto_num, sto_No, sto_date, info, &upinfo, &downinfo, &max, &min);//maxline);
			setfillstyle(SOLID_FILL, BLACK);
			bar(1, 121, 72, 143);//�ڸ������Ľ��
			search_name(sto_num, sto_name);//��Ʊ��ŵ����Ƶ�����
			output_stoname(sto_name);//��ӡ��ϣ�����Ľ��
			kind = 0;//��ͼ��ʾ���ݸ�Ϊ4��
			colorkind = 1;
		}

		/********************
		���Ĺ�Ʊ����ʾ����
		*********************/
		if (mouse_press(0, 432, 8, 442) == 1)
		{
			delay(50);
			memset(info, 0.0, 150 * sizeof(STODAYFLOAT));
			change_datadate(sto_num, &sto_date, info, &upinfo, &downinfo, &max, &min, read_way, 1);//maxline);//���Ĺ�Ʊ����ʾ����
			colorkind = 1;
		}
		if (mouse_press(64, 432, 72, 442) == 1)
		{
			delay(50);
			memset(info, 0.0, 150 * sizeof(STODAYFLOAT));
			change_datadate(sto_num, &sto_date, info, &upinfo, &downinfo, &max, &min, read_way, 2);//maxline);//���Ĺ�Ʊ����ʾ����
			colorkind = 1;
		}

		if (MouseX > 621 && MouseX < 638 && MouseY> 25 && MouseY < 24 + 39)
		{
			if (mouse_press(621, 25, 638, 24 + 39) == 2)//δ���
			{
				MouseS = 1;
				if (num == 0)//��ֹ���ظ�����
				{
					lightbutton_market(621, 25, 638, 24 + 39, BLUE, 1);
					num = 1;
				}
				continue;
				//��������
			}
			else if (mouse_press(621, 25, 638, 24 + 39) == 1 && cinfo->itemnum == 0)     //���и��˵���ʱ���ܵ��
			{   //����
				MouseS = 0;
				lightbutton_market(621, 25, 638, 24 + 39, BLUE, 1);
				if(strlen(u->user) == 0)
				{
					cpop(1);
				}
				else if(strlen(u->user) != 0 && strlen(u->bankcard) == 0)
				{
					cpop(2);
				}
				else if(strlen(u->user) != 0 && strlen(u->bankcard) != 0)
					trade(cinfo, u, 0, sto_num);           //��ת������ڼ�ֻ��
				if(cinfo->func != 4 && cinfo->func != 8)
				{
					clrmous(MouseX,MouseY);
					delay(10);
					return;            //����Ҫ�ͷŶ�ջ
				}        //��������������飬������
				else 
				{      //�ɹ���������
					cleardevice();
					mainmenu_draw();
					control_judge(u);
					draw_market();
					get_markettime(tp, &minute, 1);	//���ʱ��
					output_stoname(sto_name);//��ӡ��ϣ�����Ľ��
					Kline_draw(info, max, min);
					MA_draw(info, &upinfo, max, min);
					VOL_draw(info, &downinfo);
					input_klinequeue(&Q, pos[page]);
					submenu_draw(cinfo->itemnum);
					continue;
				}
			}
		}

		if (MouseX > 621 && MouseX < 638 && MouseY> 25 + 40 && MouseY < 24 + 40 + 39)
		{
			if (mouse_press(621, 25 + 40, 638, 24 + 40 + 39) == 2)//δ���
			{
				MouseS = 1;
				if (num == 0)//��ֹ���ظ�����
				{
					lightbutton_market(621, 25 + 40, 638, 24 + 40 + 39, BLUE, 2);
					num = 2;
				}
				continue;

				//��������
			}
			else if (mouse_press(621, 25 + 40, 638, 24 + 40 + 39) == 1 && cinfo->itemnum == 0)
			{ //ѡ��
				MouseS = 0;
				lightbutton_market(621, 25 + 40, 638, 24 + 40 + 39, BLUE, 2);
				cinfo->itemnum = 0;
				cinfo->func = 9;
				continue;
			}
		}

		if (MouseX > 621 && MouseX < 638 && MouseY> 25 + 40 + 49 && MouseY < 24 + 79 + 40)
		{
			if (mouse_press(621, 25 + 40 + 40, 638, 24 + 79 + 40) == 2)//δ���
			{
				MouseS = 1;
				if (num == 0)//��ֹ���ظ�����
				{
					lightbutton_market(621, 25 + 40 + 40, 638, 24 + 79 + 40, BLUE, 3);
					num = 3;
				}
				continue;
				//��������
			}
			else if (mouse_press(621, 25 + 40 + 40, 638, 24 + 79 + 40) == 1 && cinfo->itemnum == 0)
			{ //����
				MouseS = 0;
				lightbutton_market(621, 25 + 40 + 40, 638, 24 + 79 + 40, BLUE, 3);
				cinfo->func = 0;
				continue;
			}
		}

		if (MouseX > 621 && MouseX < 638 && MouseY> 24 + 79 + 42 && MouseY < 24 + 79 + 42 + 38)
		{
			if (mouse_press(621, 24 + 79 + 42, 638, 24 + 79 + 42 + 38) == 2)//δ���
			{
				MouseS = 1;
				if (num == 0)//��ֹ���ظ�����
				{
					lightbutton_market(621, 24 + 79 + 42, 638, 24 + 79 + 42 + 38, BLUE, 4);
					num = 4;
				}
				continue;

				//��������
			}
			else if (mouse_press(621, 24 + 79 + 42, 638, 24 + 79 + 42 + 38) == 1 && cinfo->itemnum == 0)
			{ //�ʲ�
				MouseS = 0;
				lightbutton_market(621, 24 + 79 + 42, 638, 24 + 79 + 42 + 38, BLUE, 4);
				if(strlen(u->user) == 0)
					cpop(1);
				else if(strlen(u->user) != 0 && strlen(u->bankcard) == 0)
					cpop(2);
				else if(strlen(u->user) != 0 && strlen(u->bankcard) != 0)
					personinfo(cinfo, u);
				if(cinfo->func != 4 && cinfo->func != 8)
				{
					clrmous(MouseX,MouseY);
					delay(100);
					return;            //����Ҫ�ͷŶ�ջ
				}        //��������������飬������
				else 
				{      //�ɹ���������
					cleardevice();
					mainmenu_draw();
					control_judge(u);
					draw_market();
					get_markettime(tp, &minute, 1);	//���ʱ��
					output_stoname(sto_name);//��ӡ��ϣ�����Ľ��
					Kline_draw(info, max, min);
					MA_draw(info, &upinfo, max, min);
					VOL_draw(info, &downinfo);
					input_klinequeue(&Q, pos[page]);
					submenu_draw(cinfo->itemnum);
					continue;
				}
			}
		}
		/*if (MouseX > 1 && MouseX < 72 && MouseY> 24 && MouseY < 48 && cinfo->itemnum == 0)
		{
			if (mouse_press(1, 24, 72, 48) == 2)//δ���1,24,72,48
			{
				MouseS = 1;
				if (num == 0)//��ֹ���ظ�����
				{
					lightbutton_market(1, 24, 72, 48, BLUE, 5);
					num = 5;
				}
				continue;

				//��������
			}
			else if (mouse_press(1, 24, 72, 48) == 1)
			{
				MouseS = 0;
				lightbutton_market(1, 24, 72, 48, BLUE, 5);
				continue;
			}
		}

		if (MouseX > 1 && MouseX < 72 && MouseY> 48 && MouseY < 72 && cinfo->itemnum == 0)
		{
			if (mouse_press(1, 48, 72, 72) == 2)//δ���1,48,72,72
			{
				MouseS = 1;
				if (num == 0)//��ֹ���ظ�����
				{
					lightbutton_market(1, 48, 72, 72, BLUE, 6);
					num = 6;
				}
				continue;

				//��������
			}
			else if (mouse_press(1, 48, 72, 72) == 1)
			{
				MouseS = 0;
				lightbutton_market(1, 48, 72, 72, BLUE, 6);
				continue;
			}
		}

		if (MouseX > 1 && MouseX < 72 && MouseY> 72 && MouseY < 96 && cinfo->itemnum == 0)
		{
			if (mouse_press(1, 72, 72, 96) == 2)//δ���1,72,72,96
			{
				MouseS = 1;
				if (num == 0)//��ֹ���ظ�����
				{
					lightbutton_market(1, 72, 72, 96, BLUE, 7);
					num = 7;
				}
				continue;

				//��������
			}
			else if (mouse_press(1, 72, 72, 96) == 1)
			{
				MouseS = 0;
				lightbutton_market(1, 72, 72, 96, BLUE, 7);
				continue;
			}
		}

		if (MouseX > 1 && MouseX < 72 && MouseY> 96 && MouseY < 120 && cinfo->itemnum == 0)
		{
			if (mouse_press(1, 96, 72, 120) == 2)//δ���1,96,72,120
			{
				MouseS = 1;
				if (num == 0)//��ֹ���ظ�����
				{
					lightbutton_market(1, 96, 72, 120, BLUE, 8);
					num = 8;
				}
				continue;

				//��������
			}
			else if (mouse_press(1, 96, 72, 120) == 1)
			{
				MouseS = 0;
				lightbutton_market(1, 96, 72, 120, BLUE, 8);
				continue;
			}
		}

		if (MouseX > 1 && MouseX < 72 && MouseY> 120 && MouseY < 144 && cinfo->itemnum == 0)
		{
			if (mouse_press(1, 120, 72, 144) == 2)//δ���1,120,72,144
			{
				MouseS = 1;
				if (num == 0)//��ֹ���ظ�����
				{
					lightbutton_market(1, 120, 72, 144, BLUE, 9);
					num = 9;
				}
				continue;

				//��������
			}
			else if (mouse_press(1, 120, 72, 144) == 1)
			{
				MouseS = 0;
				lightbutton_market(1, 120, 72, 144, BLUE, 9);
				continue;
			}
		}*/

		/********************
		BIAS������
		*********************/
		if (MouseX > 40 && MouseX < 80 && MouseY> 456 && MouseY < 480)
		{
			if (mouse_press(40, 456, 80, 480) == 2)//δ���
			{
				MouseS = 1;
				if (num == 0)//��ֹ���ظ�����
				{
					lightbutton_market(40, 456, 80, 480, BLUE, 10);
					num = 10;
				}
				continue;

				//��������
			}
			else if (mouse_press(40, 456, 80, 480) == 1)
			{
				MouseS = 0;
				lightbutton_market(40, 456, 80, 480, BLUE, 10);
				setfillstyle(SOLID_FILL, BLACK);
				bar(81, 343, 619, 455);
				for (i = 8; i < 11; i++)
				{
					for (j = 0; j < 135; j++)
					{
						putpixel(80 + 4 * j, 72 + 40 * i, RED);
					}
				}
				colorkind = 4;
				viceinfo_show(1, info, &downinfo);
				continue;
			}
		}

		/********************
		BOLL������
		*********************/
		else if (MouseX > 80 && MouseX < 120 && MouseY> 456 && MouseY < 480)//BOLL������
		{
			if (mouse_press(80, 456, 120, 480) == 2)//δ���
			{
				MouseS = 1;
				if (num == 0)//��ֹ���ظ�����
				{
					lightbutton_market(80, 456, 120, 480, LIGHTMAGENTA, 11);
					num = 11;
				}
				continue;

				//��������
			}
			else if (mouse_press(80, 456, 120, 480) == 1)
			{
				MouseS = 0;
				lightbutton_market(80, 456, 120, 480, BLUE, 11);
				setfillstyle(SOLID_FILL, BLACK);
				bar(81, 73, 619, 341);
				for (i = 0; i < 9; i++)
				{
					for (j = 0; j < 135; j++)
					{
						putpixel(80 + 4 * j, 72 + 40 * i, RED);
					}
				}
				kind = 1;//��һ��ѭ��ֻ��ʾ��ͼ����������
				majorinfo_show(2, info, &upinfo, max, min);
				continue;
			}
		}


		/********************
		BRAR������Ըָ��
		*********************/
		else if (MouseX > 120 && MouseX < 160 && MouseY> 456 && MouseY < 480)
		{
			if (mouse_press(120, 456, 160, 480) == 2)//δ���
			{
				MouseS = 1;
				if (num == 0)//��ֹ���ظ�����
				{
					lightbutton_market(120, 456, 160, 480, BLUE, 12);
					num = 12;
				}
				continue;

				//��������
			}
			else if (mouse_press(120, 456, 160, 480) == 1)
			{
				MouseS = 0;
				lightbutton_market(120, 456, 160, 480, BLUE, 12);
				setfillstyle(SOLID_FILL, BLACK);
				bar(81, 343, 619, 455);
				for (i = 8; i < 11; i++)
				{
					for (j = 0; j < 135; j++)
					{
						putpixel(80 + 4 * j, 72 + 40 * i, RED);
					}
				}
				colorkind = 6;
				viceinfo_show(2, info, &downinfo);
				continue;
			}
		}


		/********************
		CR����ָ��
		*********************/
		else if (MouseX > 160 && MouseX < 180 && MouseY> 456 && MouseY < 480)
		{
			if (mouse_press(160, 456, 180, 480) == 2)//δ���
			{
				MouseS = 1;
				if (num == 0)//��ֹ���ظ�����
				{
					lightbutton_market(160, 456, 180, 480, BLUE, 13);
					num = 13;
				}
				continue;

				//��������
			}
			else if (mouse_press(160, 456, 180, 480) == 1)
			{
				MouseS = 0;
				lightbutton_market(160, 456, 180, 480, BLUE, 13);
				setfillstyle(SOLID_FILL, BLACK);
				bar(81, 343, 619, 455);
				for (i = 8; i < 11; i++)
				{
					for (j = 0; j < 135; j++)
					{
						putpixel(80 + 4 * j, 72 + 40 * i, RED);
					}
				}
				colorkind = 4;
				viceinfo_show(3, info, &downinfo);
				continue;
			}
		}

		/********************
		DMAƽ���߲�
		*********************/
		else if (MouseX > 180 && MouseX < 210 && MouseY> 456 && MouseY < 480)
		{
			if (mouse_press(180, 456, 210, 480) == 2)//δ���
			{
				MouseS = 1;
				if (num == 0)//��ֹ���ظ�����
				{
					lightbutton_market(180, 456, 210, 480, BLUE, 14);
					num = 14;
				}
				continue;

				//��������
			}
			else if (mouse_press(180, 456, 210, 480) == 1)
			{
				MouseS = 0;
				lightbutton_market(180, 456, 210, 480, BLUE, 14);
				setfillstyle(SOLID_FILL, BLACK);
				bar(81, 343, 619, 455);
				for (i = 8; i < 11; i++)
				{
					for (j = 0; j < 135; j++)
					{
						putpixel(80 + 4 * j, 72 + 40 * i, RED);
					}
				}
				colorkind = 6;
				viceinfo_show(4, info, &downinfo);
				continue;
			}
		}

		/********************
		OBV������
		*********************/
		else if (MouseX > 210 && MouseX < 240 && MouseY> 456 && MouseY < 480)
		{
			if (mouse_press(210, 456, 240, 480) == 2)//δ���
			{
				MouseS = 1;
				if (num == 0)//��ֹ���ظ�����
				{
					lightbutton_market(210, 456, 240, 480, BLUE, 15);
					num = 15;
				}
				continue;

				//��������
			}
			else if (mouse_press(210, 456, 240, 480) == 1)
			{
				MouseS = 0;
				lightbutton_market(210, 456, 240, 480, BLUE, 15);
				setfillstyle(SOLID_FILL, BLACK);
				bar(81, 343, 619, 455);
				for (i = 8; i < 11; i++)
				{
					for (j = 0; j < 135; j++)
					{
						putpixel(80 + 4 * j, 72 + 40 * i, RED);
					}
				}
				colorkind = 5;
				viceinfo_show(5, info, &downinfo);
				continue;
			}
		}

		/********************
		ENE�����
		*********************/
		else if (MouseX > 240 && MouseX < 270 && MouseY> 456 && MouseY < 480)//ENE�����
		{
			if (mouse_press(240, 456, 270, 480) == 2)//δ���
			{
				MouseS = 1;
				if (num == 0)//��ֹ���ظ�����
				{
					lightbutton_market(240, 456, 270, 480, LIGHTMAGENTA, 16);
					num = 16;
				}
				continue;

				//��������
			}
			else if (mouse_press(240, 456, 270, 480) == 1)
			{
				MouseS = 0;
				lightbutton_market(240, 456, 270, 480, LIGHTMAGENTA, 16);
				setfillstyle(SOLID_FILL, BLACK);
				bar(81, 73, 619, 341);
				for (i = 0; i < 9; i++)
				{
					for (j = 0; j < 135; j++)
					{
						putpixel(80 + 4 * j, 72 + 40 * i, RED);
					}
				}
				kind = 1;
				majorinfo_show(3, info, &upinfo, max, min);
				continue;
			}
		}

		/********************
		���ָ��KDJ
		*********************/
		else if (MouseX > 270 && MouseX < 300 && MouseY> 456 && MouseY < 480)//KDJ
		{
			if (mouse_press(270, 456, 300, 480) == 2)//δ���
			{
				MouseS = 1;
				if (num == 0)//��ֹ���ظ�����
				{
					lightbutton_market(270, 456, 300, 480, BLUE, 17);
					num = 17;
				}
				continue;

				//��������
			}
			else if (mouse_press(270, 456, 300, 480) == 1)
			{
				MouseS = 0;
				lightbutton_market(270, 456, 300, 480, BLUE, 17);
				setfillstyle(SOLID_FILL, BLACK);
				bar(81, 343, 619, 455);
				for (i = 8; i < 11; i++)
				{
					for (j = 0; j < 135; j++)
					{
						putpixel(80 + 4 * j, 72 + 40 * i, RED);
					}
				}
				colorkind = 2;
				viceinfo_show(6, info, &downinfo);
				continue;
			}
		}

		/********************
		MACD��ͬ�ƶ�ƽ����
		*********************/
		else if (MouseX > 300 && MouseX < 340 && MouseY> 456 && MouseY < 480)
		{
			if (mouse_press(300, 456, 340, 480) == 2)//δ���
			{
				MouseS = 1;
				if (num == 0)//��ֹ���ظ�����
				{
					lightbutton_market(300, 456, 340, 480, BLUE, 18);
					num = 18;
				}
				continue;

				//��������
			}
			else if (mouse_press(300, 456, 340, 480) == 1)
			{
				MouseS = 0;
				lightbutton_market(300, 456, 340, 480, BLUE, 18);
				setfillstyle(SOLID_FILL, BLACK);
				bar(81, 343, 619, 455);
				for (i = 8; i < 11; i++)
				{
					for (j = 0; j < 135; j++)
					{
						putpixel(80 + 4 * j, 72 + 40 * i, RED);
					}
				}
				colorkind = 3;
				viceinfo_show(7, info, &downinfo);
				continue;
			}
		}



		/********************
		RSI���ǿ��ָ��
		*********************/
		else if (MouseX > 340 && MouseX < 370 && MouseY> 456 && MouseY < 480)
		{
			if (mouse_press(340, 456, 370, 480) == 2)//δ���
			{
				MouseS = 1;
				if (num == 0)//��ֹ���ظ�����
				{
					lightbutton_market(340, 456, 370, 480, BLUE, 19);
					num = 19;
				}
				continue;

				//��������
			}
			else if (mouse_press(340, 456, 370, 480) == 1)
			{
				MouseS = 0;
				lightbutton_market(340, 456, 370, 480, BLUE, 19);
				setfillstyle(SOLID_FILL, BLACK);
				bar(81, 343, 619, 455);
				for (i = 8; i < 11; i++)
				{
					for (j = 0; j < 135; j++)
					{
						putpixel(80 + 4 * j, 72 + 40 * i, RED);
					}
				}
				colorkind = 4;
				viceinfo_show(8, info, &downinfo);
				continue;
			}
		}

		/********************
		VOL�ɽ���
		*********************/
		else if (MouseX > 370 && MouseX < 400 && MouseY> 456 && MouseY < 480)
		{
			if (mouse_press(370, 456, 400, 480) == 2)//δ���
			{
				MouseS = 1;
				if (num == 0)//��ֹ���ظ�����
				{
					lightbutton_market(370, 456, 400, 480, BLUE, 20);
					num = 20;
				}
				continue;

				//��������
			}
			else if (mouse_press(370, 456, 400, 480) == 1)
			{
				MouseS = 0;
				lightbutton_market(370, 456, 400, 480, BLUE, 20);
				setfillstyle(SOLID_FILL, BLACK);
				bar(81, 343, 619, 455);
				for (i = 8; i < 11; i++)
				{
					for (j = 0; j < 135; j++)
					{
						putpixel(80 + 4 * j, 72 + 40 * i, RED);
					}
				}
				kind = 0;
				colorkind = 1;
				viceinfo_show(9, info, &downinfo);
				continue;
			}
		}

		/********************
		1 preday
		*********************/
		if (MouseX > 480 && MouseX < 530 && MouseY> 456 && MouseY < 480)
		{
			if (mouse_press(480, 456, 530, 480) == 2)//δ���
			{
				MouseS = 1;
				if (num == 0)//��ֹ���ظ�����
				{
					lightbutton_market(480, 456, 530, 480, YELLOW, 21);
					num = 21;
				}
				continue;

				//��������
			}
			else if (mouse_press(480, 456, 530, 480) == 1)
			{
				MouseS = 0;
				lightbutton_market(480, 456, 530, 480, LIGHTMAGENTA, 21);
				read_way = 1;
				continue;
			}
		}

		/********************
		30 preday
		*********************/
		else if (MouseX > 530 && MouseX < 590 && MouseY> 456 && MouseY < 480)
		{
			if (mouse_press(530, 456, 590, 480) == 2)//δ���
			{
				MouseS = 1;
				if (num == 0)//��ֹ���ظ�����
				{
					lightbutton_market(530, 456, 590, 480, YELLOW, 22);
					num = 22;
				}
				continue;

				//��������
			}
			else if (mouse_press(530, 456, 590, 480) == 1)
			{
				MouseS = 0;
				lightbutton_market(530, 456, 590, 480, LIGHTMAGENTA, 22);
				read_way = 2;
				continue;
			}
		}

		/********************
		90 preday
		*********************/
		else if (MouseX > 590 && MouseX < 640 && MouseY> 456 && MouseY < 480)
		{
			if (mouse_press(590, 456, 640, 480) == 2)//δ���
			{
				MouseS = 1;
				if (num == 0)//��ֹ���ظ�����
				{
					lightbutton_market(590, 456, 640, 480, YELLOW, 23);
					num = 23;
				}
				continue;

				//��������
			}
			else if (mouse_press(590, 456, 640, 480) == 1)
			{
				MouseS = 0;
				lightbutton_market(590, 456, 640, 480, LIGHTMAGENTA, 23);
				read_way = 3;
				continue;
			}
		}
		
		if (num != 0)
		{
			MouseS = 0;
			recoverbutton_market(num);
			delay(10);
			num = 0;
		}
		
		/********************
		��Ʊʵʱ������ʾ
		*********************/
		if (MouseX < 620 && MouseX>80 && MouseY < 455 && MouseY > 100 && cinfo->itemnum == 0)
		{
			MouseS = 3;
			preday = day;
			day = ((620 - MouseX) / 6) - 1;
			if (day < 0)
			{
				day = 0;//��ֹ���
			}
			mouse_datashow(info, upinfo, downinfo, &preday, &day, kind, colorkind);//�����������ʾ
			continue;
		}


		if (MouseS != 0)
		{
			MouseS = 0;
		}
	}
}

/*********************************************
FUNCTION:put_marketqueue
DESCRIPTION�����ö��й���
INPUT:pos
RETURN:��
***********************************************/
void put_marketqueue(int* pos)
{
	int i;
	for (i = 1; i < 26; i++)
	{
		pos[i] = count_klinequeue(pos[i - 1]);//�ݹ飬��ÿҳ���ļ��п�ʼ��λ��
	}
}

/*********************************************
FUNCTION:lightbutton_market
DESCRIPTION��������水ť����
INPUT:x,y,x1,y1,color,flag
RETURN:��
***********************************************/
void lightbutton_market(int x, int y, int x1, int y1, int color, int flag)
{
	clrmous(MouseX, MouseY);
	//delay(50);
	if (flag == 1 || flag == 2 || flag == 3 || flag == 4)
	{
		setfillstyle(1, color);
		bar(x, y, x1, y1);
		switch (flag)
		{
		case 1:
			puthz(622, 27, "��", 16, 17, RED);
			puthz(622, 27 + 18, "��", 16, 17, RED);
			break;
		case 2:
			puthz(622, 27 + 40, "ѡ", 16, 17, RED);
			puthz(622, 27 + 40 + 18, "��", 16, 17, RED);
			break;
		case 3:
			puthz(622, 27 + 2 * 40, "��", 16, 17, RED);
			puthz(622, 27 + 2 * 40 + 18, "��", 16, 17, RED);
			break;
		case 4:
			puthz(622, 27 + 3 * 40, "��", 16, 17, RED);
			puthz(622, 27 + 3 * 40 + 18, "��", 16, 17, RED);
			break;
		}
	}
	settextjustify(LEFT_TEXT, TOP_TEXT);
	settextstyle(2, HORIZ_DIR, 6);
	setcolor(color);
	switch (flag)
	{
	/*case 5:
		puthz(4, 28, "��ָ֤��", 16, 17, RED);
		break;
	case 6:
		puthz(4, 52, "���ָ��", 16, 17, RED);
		break;
	case 7:
		puthz(4, 76, "��Ʊ����", 16, 17, RED);
		break;
	case 8:
		puthz(4, 100, "��Ʊ����", 16, 17, RED);
		break;
	case 9:
		puthz(4, 124, "�ۺ�����", 16, 17, RED);
		break;*/
	case 10:
		outtextxy(42, 458, "BIAS");
		break;
	case 11:
		outtextxy(82, 458, "BOLL");
		break;
	case 12:
		outtextxy(122, 458, "BRAR");
		break;
	case 13:
		outtextxy(162, 458, "CR");
		break;
	case 14:
		outtextxy(182, 458, "DMA");
		break;
	case 15:
		outtextxy(212, 458, "OBV");
		break;
	case 16:
		outtextxy(242, 458, "ENE");
		break;
	case 17:
		outtextxy(272, 458, "KDJ");
		break;
	case 18:
		outtextxy(302, 458, "MACD");
		break;
	case 19:
		outtextxy(342, 458, "RSI");
		break;
	case 20:
		outtextxy(372, 458, "VOL");
		break;
	case 21:
		outtextxy(482, 458, "1pre");
		break;
	case 22:
		outtextxy(532, 458, "30pre");
		break;
	case 23:
		outtextxy(590, 458, "90pre");
		break;
	}
}

/*********************************************
FUNCTION:recoverbutton_market
DESCRIPTION��������水ť�����ָ�
INPUT:num
RETURN:��
***********************************************/
void recoverbutton_market(int num)
{
	clrmous(MouseX, MouseY);
	if (num == 1 || num == 2 || num == 3 || num == 4)
	{
		setfillstyle(SOLID_FILL, LIGHTBLUE);
	}
	settextjustify(LEFT_TEXT, TOP_TEXT);
	settextstyle(2, HORIZ_DIR, 6);
	setcolor(RED);
	switch (num)
	{
	case 1:
		bar(621, 25, 638, 24 + 39);
		puthz(622, 27, "��", 16, 17, WHITE);
		puthz(622, 27 + 18, "��", 16, 17, WHITE);
		break;
	case 2:
		bar(621, 25 + 40, 638, 24 + 40 + 39);
		puthz(622, 27 + 40, "ѡ", 16, 17, WHITE);
		puthz(622, 27 + 40 + 18, "��", 16, 17, WHITE);
		break;
	case 3:
		bar(621, 25 + 40 + 40, 638, 24 + 79 + 40);
		puthz(622, 27 + 2 * 40, "��", 16, 17, WHITE);
		puthz(622, 27 + 2 * 40 + 18, "��", 16, 17, WHITE);
		break;
	case 4:
		bar(621, 24 + 79 + 42, 638, 24 + 79 + 42 + 38);
		puthz(622, 27 + 3 * 40, "��", 16, 17, WHITE);
		puthz(622, 27 + 3 * 40 + 18, "��", 16, 17, WHITE);
		break;
	case 5:
		puthz(4, 28, "��ָ֤��", 16, 17, WHITE);
		break;
	case 6:
		puthz(4, 52, "���ָ��", 16, 17, WHITE);
		break;
	case 7:
		puthz(4, 76, "��Ʊ����", 16, 17, WHITE);
		break;
	case 8:
		puthz(4, 100, "��Ʊ����", 16, 17, WHITE);
		break;
	/*case 9:
		puthz(4, 124, "�ۺ�����", 16, 17, WHITE);
		break;*/
	case 10:
		outtextxy(42, 458, "BIAS");
		break;
	case 11:
		outtextxy(82, 458, "BOLL");
		break;
	case 12:
		outtextxy(122, 458, "BRAR");
		break;
	case 13:
		outtextxy(162, 458, "CR");
		break;
	case 14:
		outtextxy(182, 458, "DMA");
		break;
	case 15:
		outtextxy(212, 458, "OBV");
		break;
	case 16:
		outtextxy(242, 458, "ENE");
		break;
	case 17:
		outtextxy(272, 458, "KDJ");
		break;
	case 18:
		outtextxy(302, 458, "MACD");
		break;
	case 19:
		outtextxy(342, 458, "RSI");
		break;
	case 20:
		outtextxy(372, 458, "VOL");
		break;
	case 21:
		outtextxy(482, 458, "1pre");
		break;
	case 22:
		outtextxy(532, 458, "30pre");
		break;
	case 23:
		outtextxy(590, 458, "90pre");
		break;
	}
}

/*********************************************
FUNCTION:draw_market
DESCRIPTION������������
INPUT:void
RETURN:��
***********************************************/
void draw_market(void)
{
	int i,j;
	setbkcolor(BLACK);
	setcolor(RED);
	setlinestyle(SOLID_LINE, 0, 1);
	line(1, 24, 639, 24);
	line(1, 0, 1, 480);
	line(1, 479, 639, 479);
	line(80, 24, 80, 456);
	line(620, 24, 620, 456);
	line(1, 456, 639, 456);
	line(639, 0, 639, 480);
	line(620, 24 + 40, 639, 24 + 40);
	line(620, 24 + 2 * 40, 639, 24 + 2 * 40);
	line(620, 24 + 3 * 40, 639, 24 + 3 * 40);
	line(620, 24 + 4 * 40, 639, 24 + 4 * 40);
	line(80, 24 + 2 * 24, 620, 24 + 2 * 24);
	line(80, 342, 620, 342);
	for (i = 0; i < 11; i++)
	{
		for (j = 0; j < 135; j++)
		{
			putpixel(80 + 4 * j, 72 + 40 * i, RED);
		}
	}

	//���Ҳ�˵���
	setfillstyle(SOLID_FILL, LIGHTBLUE);
	bar(621, 25, 638, 24 + 39);
	bar(621, 25 + 40, 638, 24 + 40 + 39);
	bar(621, 25 + 40 + 40, 638, 24 + 79 + 40);
	bar(621, 24 + 79 + 42, 638, 24 + 79 + 42 + 38);
	puthz(622, 27, "��", 16, 17, WHITE);
	puthz(622, 27 + 18, "��", 16, 17, WHITE);
	puthz(622, 27 + 40, "ѡ", 16, 17, WHITE);
	puthz(622, 27 + 40 + 18, "��", 16, 17, WHITE);
	puthz(622, 27 + 2 * 40, "��", 16, 17, WHITE);
	puthz(622, 27 + 2 * 40 + 18, "��", 16, 17, WHITE);
	puthz(622, 27 + 3 * 40, "��", 16, 17, WHITE);
	puthz(622, 27 + 3 * 40 + 18, "��", 16, 17, WHITE);

	//������Ʊ��
	for (i = 0; i < 9; i++)
	{
		line(0, 144 + 36 * i, 72, 144 + 36 * i);
	}
	
	//����Ʊ�����϶�����ʱ��ѡ���϶���
	setfillstyle(SOLID_FILL, DARKGRAY);
	bar(73, 145, 79, 455);
	line(72, 144, 72, 456);
	line(72, 144, 80, 144);
	line(0, 144 + 36 * 8 + 10, 72, 144 + 36 * 8 + 10);
	bar(1, 144 + 36 * 8 + 1, 71, 144 + 36 * 8 + 9);
	setfillstyle(SOLID_FILL, BLACK);
	bar(73, 170, 79, 180);

	setcolor(BLACK);
	line(73, 154, 79, 154);
	line(79, 154, 76, 147);
	line(73, 154, 76, 147);
	line(73, 427, 76, 434);
	line(76, 434, 79, 427);
	line(73, 427, 79, 427);
	setfillstyle(SOLID_FILL, BLACK);
	floodfill(76, 150, BLACK);
	floodfill(76, 430, BLACK);//����Ʊ���е����ť
	line(1, 437, 8, 440);
	line(1, 437, 8, 434);
	line(8, 434, 8, 440);
	line(64, 434, 71, 437);
	line(64, 440, 71, 437);
	line(64, 434, 64, 440);
	floodfill(4, 437, BLACK);
	floodfill(68, 437, BLACK);//����Ʊʱ���л������ť

	//���ײ⼼��ָ��
	setcolor(RED);
	settextjustify(LEFT_TEXT, TOP_TEXT);
	settextstyle(2, HORIZ_DIR, 6);
	line(40, 456, 40, 479);
	puthz(4, 460, "ָ��", 16, 17, RED);

	line(80, 456, 80, 479);
	outtextxy(42, 458, "BIAS");//40,456,80,480

	line(120, 456, 120, 479);
	outtextxy(82, 458, "BOLL");//80,456,120,480

	line(160, 456, 160, 479);
	outtextxy(122, 458, "BRAR");//120,456,160,480

	line(180, 456, 180, 479);
	outtextxy(162, 458, "CR");//160,456,180,480

	line(210, 456, 210, 479);
	outtextxy(182, 458, "DMA");//180,456,210,480

	line(240, 456, 240, 479);
	outtextxy(212, 458, "OBV");//210,456,240,480

	line(270, 456, 270, 479);
	outtextxy(242, 458, "ENE");//240,456,270,480

	line(300, 456, 300, 479);
	outtextxy(272, 458, "KDJ");//270,456,300,480

	line(340, 456, 340, 479);
	outtextxy(302, 458, "MACD");//300,456,320,480

	line(370, 456, 370, 479);
	outtextxy(342, 458, "RSI");

	line(400, 456, 400, 479);
	outtextxy(372, 458, "VOL");


	line(480, 456, 480, 479);
	puthz(408, 460, "�����л�", 16, 17, RED);

	line(525, 456, 525, 479);
	outtextxy(482, 458, "1pre");
	line(585, 456, 585, 479);
	outtextxy(532, 458, "30pre");
	outtextxy(590, 458, "90pre");


	//�����˵���
	/*line(1, 48, 72, 48);
	line(72, 48, 80, 40);
	puthz(4, 28, "��ָ֤��", 16, 17, WHITE);

	line(1, 72, 72, 72);
	line(72, 72, 80, 64);
	puthz(4, 52, "���ָ��", 16, 17, WHITE);

	line(1, 96, 72, 96);
	line(72, 96, 80, 88);
	puthz(4, 76, "��Ʊ����", 16, 17, WHITE);

	line(1, 120, 72, 120);
	line(72, 120, 80, 112);
	puthz(4, 100, "��Ʊ����", 16, 17, WHITE);

	line(1, 144, 72, 144);
	line(72, 144, 80, 136);
	puthz(4, 124, "�ۺ�����", 16, 17, WHITE);*/

	puthz(3, 88, "��Ʊ��", 24, 25, LIGHTCYAN);

	//��������Ϣ��
	settextjustify(LEFT_TEXT, TOP_TEXT);
	settextstyle(0, HORIZ_DIR, 1);
	puthz(82, 26, "ʱ��", 16, 17, YELLOW);
	setcolor(YELLOW);
	outtextxy(80 + 17 * 2, 32, ":");

	puthz(190, 26, "��", 16, 17, WHITE);
	setcolor(WHITE);
	outtextxy(188 + 17 * 2, 32, ":");

	puthz(298, 26, "���", 16, 17, RED);
	setcolor(RED);
	outtextxy(296 + 17 * 2, 32, ":");

	puthz(406, 26, "���", 16, 17, GREEN);
	setcolor(GREEN);
	outtextxy(404 + 17 * 2, 32, ":");

	puthz(514, 26, "����", 16, 17, WHITE);
	setcolor(WHITE);
	outtextxy(516 + 17 * 2, 32, ":");

	puthz(82, 50, "�ǵ�", 16, 17, LIGHTRED);
	setcolor(LIGHTRED);
	outtextxy(80 + 17 * 2, 56, ":");

	puthz(190, 50, "�Ƿ�", 16, 17, RED);
	setcolor(RED);
	outtextxy(188 + 17 * 2, 56, ":");

	puthz(298, 50, "���", 16, 17, YELLOW);
	setcolor(YELLOW);
	outtextxy(296 + 17 * 2, 56, ":");

	puthz(406, 50, "�ɽ���", 16, 17, LIGHTBLUE);
	setcolor(LIGHTBLUE);
	outtextxy(404 + 17 * 3, 56, ":");

	puthz(514, 50, "�ɽ���", 16, 17, LIGHTCYAN);
	setcolor(CYAN);
	outtextxy(512 + 17 * 3, 56, ":");

}