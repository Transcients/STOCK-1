#include<io.h>
#include<direct.h>
#include"trdbuy.h"
#include"public.h"
#include"trade.h"
#include"traverse.h"
#include"storead.h"

/*********************************************
trdbuy.c
COPYRIGHT: dengshumin
FUNCTION:  stock buy
ABSTRACT:  
		A. buy stock
		B. update hold and history
		C. button lightning and recovering
DATE: 2019/10/23
**********************************************/

/********************************************************
FUNCTION: buy
DESCRIPTION: �û�������������ʵ��
ATTENTION:   stk_locatʵ���˴���������Ķ�λ����
INPUT: trmenu_ord,trmenu_ord_last,cinfo,u,stk_locat
RETURN: ��
********************************************************/
void buy(short int *trmenu_ord,short int *trmenu_ord_last,Ctr* cinfo,USER* u,int stk_locat)
{
	struct tm *tp = NULL;
	time_t t;
	short int num = 0;                  // ������ť���
	short int input_flag = 0;
	char STK_CODE[7] = {'\0'};        	//6λ����֤ȯ����
	char STK_NAME[10] = {'\0'};       	//��Ʊ����
	char STK_PRICE[7] = {'\0'};       	//��С�������6λ������/�����۸�
	char STK_NUM[10] = {'\0'};        	//���9λ����Ʊ����һ����100һ��
	char STK_AFFORD[10] = {'\0'};     	//���򣨹ɣ������9λ
	char STK_SUM[20] = {'\0'};        	//�ܽ��
	char STK_TIME[11] = {'\0'};         //�ɽ�����
	char STK_TEMP[10] = {'\0'};         //��ʱ����
	char STK_PRICE_MAR[7] = {'\0'};     //��Ʊ�м�
	float stk_price = 0;                //��Ʊ�۸񣨸�������
	float stk_balance = 0;    		    //���
	float stk_price_mar = 0;            //��Ʊ�мۣ���������
	double stk_sum = 0;                 //��Ʊ�ܼ�
	unsigned long stk_num = 0;          //��Ʊ����
	unsigned long stk_afford = 0;       //�����
	int minute = 0;
	int stk_second = 0;
	memset(cinfo,0,sizeof(Ctr));	    //��������Ϣ��ʼ��
	cinfo->func = 3;          	   	    //��3��ǽ��׺����Ľ���
	mainmenu_draw();
	control_judge(u);
	buy_draw();
	get_time(tp, &minute, 1);           //��ȡʱ��              
	get_balance1(u, &stk_balance);      //ÿ�ε���һ��buy,�����ݿ��л�ȡ���,����ʾ
	read_balance(stk_balance);          //�������
	if(stk_locat != 0)
	{                  					//�������Ĺ�Ʊλ�ò�Ϊ0
		get_buy(stk_locat,STK_CODE, STK_NAME, STK_PRICE);             //�����ȡ
		settextjustify(LEFT_TEXT, TOP_TEXT);
		settextstyle(2, HORIZ_DIR, 6);
		setcolor(BLACK);
		outtextxy(230, 73, STK_CODE);
		if(STK_NAME[0] >= '!' && STK_NAME[0] <= 'z')
		{
			setcolor(WHITE);
			settextjustify(LEFT_TEXT, TOP_TEXT);
			settextstyle(2, HORIZ_DIR, 6);
			outtextxy(232, 106, "*ST");
			puthz(261,108,STK_NAME + 3, 16, 17, WHITE);
		}
		else
		{
			puthz(232,108,STK_NAME,16,17,WHITE);	
		}
		if(strlen(STK_PRICE) != 0)
		{
			memset(STK_PRICE_MAR,'\0',sizeof(STK_PRICE_MAR));
			setcolor(BLACK);
			settextjustify(LEFT_TEXT, TOP_TEXT);
			settextstyle(2, HORIZ_DIR, 6);
			outtextxy(230,137,STK_PRICE);
			turn_a2f(STK_PRICE,&stk_price);     	//������Ķ���
			strcpy(STK_PRICE_MAR, STK_PRICE);       //�����м�
			stk_price_mar = stk_price;              //�м۵�����������۸�
			puthz(420,140,"��ǰ�м�",16,17,LIGHTRED);
			setcolor(WHITE);
			outtextxy(500,137,STK_PRICE_MAR);             //��ʾ��ǰ�м�
			stk_afford = (unsigned long)(stk_balance / stk_price);	 //��������
			if(stk_afford >= 100)
			{
				stk_hundred(stk_afford,STK_AFFORD);     
				setcolor(BLACK);
				settextjustify(LEFT_TEXT, TOP_TEXT);
				settextstyle(2, HORIZ_DIR, 6);
				outtextxy(230,169,STK_AFFORD);          //����������
			}
		}
	}
	stk_second = tp->tm_sec;
	while(1)
	{
		if(strlen(u->user) == 0)
			cinfo->func = 0;
		get_time(tp, &minute, 0);
		if(strlen(STK_NAME) != 0)              //���й�Ʊ��ʾ�������          
		{	
			if(tp->tm_sec < stk_second)          //����һ����
			{
				if((tp->tm_sec + 60 - stk_second) >= 8)         //��8���м۱䶯һ�� 
				{
					get_new_price(STK_PRICE_MAR, &stk_price_mar, 1);
					stk_second = tp->tm_sec;
				}
			}
			else 
			{
				if((tp->tm_sec - stk_second) >= 8)
				{
					get_new_price(STK_PRICE_MAR, &stk_price_mar, 1);
					stk_second = tp->tm_sec;
				}
			}
		}
		read_balance(stk_balance);
		if(!bioskey(1))
		{
			newmouse(&MouseX, &MouseY, &press);
			control_mouse(cinfo,u);
		}
		else if(bioskey(1))
		{
			cinfo->key = bioskey(0);
		}
		control_key(cinfo);
		if(control_menu(cinfo))
		{
			mainmenu_draw();
			control_judge(u);
			trade_menu_draw(1);
			buy_draw();
			get_time(tp, &minute, 1); 
			read_balance(stk_balance);
			submenu_draw(cinfo->itemnum);
			continue;
		}
		if(cinfo->func != 3 && cinfo->func != 13)
		{
			clrmous(MouseX,MouseY);
			delay(10);                 					    //��ֹ����
			return; 										//��������������ܼ����ͷ��أ�����ǻ��ԭ����������ж�
		}
		if(change_trdmenu(trmenu_ord,trmenu_ord_last))      //����л��˵�
			return;
		if(MouseX > 222 && MouseX < 381 && MouseY > 74 && MouseY < 94)
		{
			if(mouse_press(222,74,381,94) == 2)
			{
				MouseS = 2;
				continue;
			}
			else if(mouse_press(222,74,381,94) == 1)
			{ 	//�����Ҳ��һ�����ð�ť
				input_flag = 0;
				clrmous(MouseX,MouseY);
				setfillstyle(1,WHITE);
				MouseS = 0;
				bar(222,74,381,94);            //֤ȯ����
				bar(222,138,361,158);          //����۸�
				bar(222,170,381,190);		   //�����
				bar(222,234,361,254);          //������������
				setfillstyle(1,BLACK);         //�ڸ�
				bar(222,106,381,126);          //֤ȯ����
				bar(420, 138, 630, 158);       //��ǰ�м�
				bar(420,170,630,190);          //����۸�������� 
				//setfillstyle(1,WHITE);
				stk_num = 0;
				stk_price = 0;
				stk_afford = 0;
				stk_price_mar = 0;
				memset(STK_CODE,'\0',sizeof(STK_CODE));
				memset(STK_NAME,'\0',sizeof(STK_NAME));
				memset(STK_PRICE,'\0',sizeof(STK_PRICE));
				memset(STK_AFFORD,'\0',sizeof(STK_AFFORD));
				memset(STK_NUM,'\0',sizeof(STK_NUM));
				memset(STK_PRICE_MAR,'\0',sizeof(STK_PRICE_MAR));
				memset(STK_SUM,'\0',sizeof(STK_SUM));
				input_trade(STK_CODE,222,74,6,WHITE);
				if(strlen(STK_CODE) != 0)
				{
					if(strlen(STK_CODE) == 6)
					{
						if(get_stkname(STK_CODE,STK_NAME,STK_PRICE) != 0)    //���������㷨,����λ�÷���
						{         //���ҵ�	
							if(STK_NAME[0] >= '!' && STK_NAME[0] <= 'z')
							{
								setcolor(WHITE);
								settextjustify(LEFT_TEXT, TOP_TEXT);
								settextstyle(2, HORIZ_DIR, 6);
								outtextxy(232, 106, "*ST");
								puthz(261,108,STK_NAME + 3, 16, 17, WHITE);
							}
							else
							{
								puthz(232,108,STK_NAME,16,17,WHITE);	
							}
						}	   
					}
				}
				if(strlen(STK_PRICE) != 0)
				{
					setcolor(BLACK);
					settextjustify(LEFT_TEXT, TOP_TEXT);
					settextstyle(2, HORIZ_DIR, 6);
					outtextxy(230,137,STK_PRICE);
					turn_a2f(STK_PRICE, &stk_price);     	//������Ķ���
					stk_afford = (unsigned long)(stk_balance / stk_price);	 //��������
					if(stk_afford >= 100)
					{
						stk_hundred(stk_afford,STK_AFFORD);     
						setcolor(BLACK);
						settextjustify(LEFT_TEXT, TOP_TEXT);
						settextstyle(2, HORIZ_DIR, 6);
						outtextxy(230,169,STK_AFFORD);          //����������
					}
					stk_price_mar = stk_price;                	//���ݿ�۸�����м�
					memset(STK_PRICE_MAR,'\0',sizeof(STK_PRICE_MAR));
					strcpy(STK_PRICE_MAR,STK_PRICE);
					setfillstyle(1,BLACK);
					bar(420, 138, 540, 158);
					puthz(420,140,"��ǰ�м�",16,17,LIGHTRED);
					settextjustify(LEFT_TEXT,TOP_TEXT);
					settextstyle(2,0,6);
					setcolor(WHITE);
					outtextxy(500,137,STK_PRICE_MAR);             //��ʾ��ǰ�м�
				}
				continue;					
			}
		}

		if(MouseX > 222 && MouseX < 362 && MouseY > 138 && MouseY < 158)
		{    //�۸��
			if(mouse_press(222,138,362,158) == 2)
			{
				MouseS = 2;
				continue;
			}
			else if(mouse_press(222,138,362,158) == 1)
			{
				setfillstyle(1,WHITE);
				MouseS = 0;
				memset(STK_PRICE,'\0',sizeof(STK_PRICE));
				stk_price = 0;            //��0
				clrmous(MouseX,MouseY);
				bar(222,138,361,158);
				input_trade(STK_PRICE,222,138,6,WHITE);
				if(strlen(STK_PRICE) != 0)
				{       //�۸�䶯
					turn_a2f(STK_PRICE,&stk_price);       	//�۸�ת��Ϊ������
					stk_afford =(unsigned long)(stk_balance / stk_price);	//�����Լ۸�Ϊ�����
					stk_hundred(stk_afford,STK_AFFORD);     //ת�ַ�
					setfillstyle(1,WHITE);					//��������
					bar(222,170,381,190);                   //���ǿ����
					setfillstyle(1,BLACK);
					bar(420,170,630,190);                   //�ڸ�����۸�������壿
					setcolor(BLACK);
					settextjustify(LEFT_TEXT, TOP_TEXT);
					settextstyle(2, HORIZ_DIR, 6);
					outtextxy(230,169,STK_AFFORD);        		//����������
				}   //����
				continue;
			}	
		}
		if(MouseX > 362 && MouseX < 381 && MouseY > 138 && MouseY < 158)
		{
			if(mouse_press(362,138,381,148) == 1 )       //����۸����Ӱ�ť
			{
				stk_price = 0;
				delay(150);
				turn_a2f(STK_PRICE,&stk_price);     	//������Ķ���
				stk_price += 0.01;                 		//������+0.01
				float_to_str(STK_PRICE,stk_price,2);    //������������   
				setfillstyle(1,WHITE);
				bar(222,138,361,158);
				setfillstyle(1,BLACK);
				bar(420,170,630,190);                   //�ڸ�����ʱ���м���Ϣ
				setcolor(BLACK);
				settextjustify(LEFT_TEXT, TOP_TEXT);
				settextstyle(2, HORIZ_DIR, 6);
				outtextxy(230,137,STK_PRICE);
				continue;                           
			}
			else if(mouse_press(362,148,381,158) == 1 )
			{
				delay(150);
				stk_price = 0;
				turn_a2f(STK_PRICE,&stk_price);
				if(stk_price >= 0.01)
					stk_price = stk_price - 0.01;
				else
					stk_price = 0;
				float_to_str(STK_PRICE,stk_price,2);	 //������������
				setfillstyle(1,WHITE);
				bar(222,138,361,158);
				setfillstyle(1,BLACK);
				bar(420,170,630,190);                   //�ڸ�����ʱ���м���Ϣ
				setcolor(BLACK);
				settextjustify(LEFT_TEXT, TOP_TEXT);
				settextstyle(2, HORIZ_DIR, 6);
				outtextxy(230,137,STK_PRICE);
				continue;
			}
		}
		
		if(MouseX > 222 && MouseX < 381 && MouseY > 170 && MouseY < 190)
		{
			if(mouse_press(222,170,381,190) == 2)
			{
				if(num == 0 )
				{
					lightbutton_trade_buy(1);    //���������
					num = 1;
				}
				continue;         //����
			}
			else if(mouse_press(222,170,381,190) == 1) //�������ɣ����¿������
			{
				new_afford(&stk_afford, stk_balance, stk_price, STK_AFFORD);
				continue;
			}
		}
		if(MouseX > 225 && MouseX < 385 && MouseY > 195 && MouseY < 225)
		{
			if(mouse_press(227,200,262,221) == 2 )
			{
				if(num == 0 )
				{
					lightbutton_trade_buy(2);
					num = 2;
				}
				continue;
			}
			else if(mouse_press(227,200,262,221) == 1)     //���1/2��
			{
				clrmous(MouseX,MouseY);
				delay(150);
				setfillstyle(1,WHITE);					
				bar(222,234,362,254);
				if(stk_judge(stk_afford, 2) != 0);  		 //�Կ������1/2����������������ϣ�������һ�ٹ������
				{
					stk_num = (stk_afford / 100) * 100 / 2;
					stk_hundred(stk_num, STK_NUM);    //��������ʽ���
					stk_turn_a2i(STK_NUM, &stk_num);
					setcolor(BLACK);
					settextjustify(LEFT_TEXT, TOP_TEXT);
					settextstyle(2, HORIZ_DIR, 6);
					outtextxy(230,233,STK_NUM);
					stk_judgesum(stk_num,stk_afford,stk_price,STK_SUM,STK_NUM,&stk_sum); 
				}
				continue;
			}
			if(mouse_press(267,200,302,221) == 2)
			{
				if(num == 0 )
				{
					lightbutton_trade_buy(3);
					num = 3;
				}
				continue;
			}
			else if(mouse_press(267,200,302,221) == 1)
			{
				clrmous(MouseX,MouseY);
				delay(150);
				setfillstyle(1,WHITE);					
				bar(222,234,362,254);
				if(stk_judge(stk_afford, 3) != 0);   //�Կ������1/3����������������ϣ�������һ�ٹ������
				{
					stk_num = (stk_afford / 100) * 100 / 3;
					stk_hundred(stk_num,STK_NUM);
					stk_turn_a2i(STK_NUM,&stk_num);
					setcolor(BLACK);
					settextjustify(LEFT_TEXT, TOP_TEXT);
					settextstyle(2, HORIZ_DIR, 6);
					outtextxy(230,233,STK_NUM);
					stk_judgesum(stk_num,stk_afford,stk_price,STK_SUM,STK_NUM,&stk_sum);
				}
				continue;
			}
			if(mouse_press(307,200,342,221) == 2)
			{
				if(num == 0 )
				{
					lightbutton_trade_buy(4);
					num = 4;
				}
				continue;
			}
			else if(mouse_press(307,200,342,221) == 1)
			{
				clrmous(MouseX,MouseY);
				delay(150);
				setfillstyle(1,WHITE);					
				bar(222,234,362,254);
				if(stk_judge(stk_afford, 4) != 0);   //�Կ������1/4����������������ϣ�������һ�ٹ������
				{
					stk_num = (stk_afford / 100) * 100 / 4;
					stk_hundred(stk_num,STK_NUM);
					stk_turn_a2i(STK_NUM,&stk_num);
					setcolor(BLACK);
					settextjustify(LEFT_TEXT, TOP_TEXT);
					settextstyle(2, HORIZ_DIR, 6);
					outtextxy(230,233,STK_NUM);
					stk_judgesum(stk_num,stk_afford,stk_price,STK_SUM,STK_NUM,&stk_sum);
				}
				continue;
			}
			if(mouse_press(347,200,382,221) == 2)
			{
				if(num == 0 )
				{
					lightbutton_trade_buy(5);
					num = 5;
				}
				continue;
			}
			else if(mouse_press(347,200,382,221) == 1)
			{
				clrmous(MouseX,MouseY);
				delay(150);
				setfillstyle(1,WHITE);					
				bar(222,234,362,254);
				if(stk_judge(stk_afford, 5) != 0);   //�Կ������1/5����������������ϣ�������һ�ٹ������
				{
					stk_num = (stk_afford / 100) * 100 / 5;
					stk_hundred(stk_num,STK_NUM);
					stk_turn_a2i(STK_NUM,&stk_num);     
					setcolor(BLACK);
					settextjustify(LEFT_TEXT, TOP_TEXT);
					settextstyle(2, HORIZ_DIR, 6);
					outtextxy(230,233,STK_NUM);
					stk_judgesum(stk_num,stk_afford,stk_price,STK_SUM,STK_NUM,&stk_sum);
				}   
				continue;
			}
		}
		if(MouseX > 222 && MouseX < 362 && MouseY > 234 && MouseY <254)
		{
			if(mouse_press(222,234,362,254) == 2)
			{
				MouseS = 2;
				continue;
			}
			else if(mouse_press(222,234,362,254) == 1)
			{
				setfillstyle(1,WHITE);
				MouseS = 0;
				clrmous(MouseX,MouseY);
				memset(STK_NUM,'\0',sizeof(STK_NUM));          
				stk_num = 0;           //���㣬stk_num��ֵ����Ļһ��
				bar(222,234,361,254);
				input_trade(STK_NUM,222,234,6,WHITE);
				if(strlen(STK_NUM) != 0)
				{
					stk_turn_a2i(STK_NUM,&stk_num);
					stk_judgesum(stk_num,stk_afford,stk_price,STK_SUM,STK_NUM,&stk_sum);
				}
				continue;
			}
		}
		if(MouseX > 362 && MouseX < 381 && MouseY > 234 && MouseY < 254)
		{
			if(mouse_press(362,234,381,244) == 1)   //����������һ��
			{
				delay(150);
				//stk_num = 0;
				stk_turn_a2i(STK_NUM,&stk_num);   //���
				stk_num += 100;
				memset(STK_NUM,'\0',sizeof(STK_NUM));
				ultoa(stk_num,STK_NUM,10);
				setfillstyle(1,WHITE);
				bar(222,234,361,254);
				setcolor(BLACK);
				settextjustify(LEFT_TEXT, TOP_TEXT);
				settextstyle(2, HORIZ_DIR, 6);
				outtextxy(230,233,STK_NUM);
				stk_judgesum(stk_num,stk_afford,stk_price,STK_SUM,STK_NUM,&stk_sum);
				continue;
			}
			else if(mouse_press(362,244,381,254) == 1)
			{
				delay(150);
				stk_turn_a2i(STK_NUM,&stk_num);   //���
				if(stk_num >= 100)
					stk_num -= 100;
				else 
					stk_num = 0;
				memset(STK_NUM,'\0',sizeof(STK_NUM));
				ultoa(stk_num,STK_NUM,10);         
				setfillstyle(1,WHITE);
				bar(222,234,361,254);
				setcolor(BLACK);
				settextjustify(LEFT_TEXT, TOP_TEXT);
				settextstyle(2, HORIZ_DIR, 6);
				outtextxy(230,233,STK_NUM);     //ÿ�θı��ֵ���������Ļ��
				stk_judgesum(stk_num,stk_afford,stk_price,STK_SUM,STK_NUM,&stk_sum);
				continue;
			}
			continue;
		}
		if(MouseX > 163 && MouseX < 235 && MouseY > 274 && MouseY < 304)
		{
			if(mouse_press(163,274,235,304) == 2)
			{
				MouseS = 1;
				if(num == 0 )
				{
					lightbutton_trade_buy(6);
					num = 6;
				}
				continue;
			}
			else if(mouse_press(163,274,235,304) == 1)
			{ 	//�������
				delay(150);
				MouseS = 0;
				clrmous(MouseX,MouseY);
				setfillstyle(1,BLACK);
				bar(121,25,640,456);         //ȫ������
				buy_draw();
				num = 0;
				input_flag = 0;
				memset(STK_CODE,'\0',sizeof(STK_CODE));
				memset(STK_NAME,'\0',sizeof(STK_NAME));
				memset(STK_PRICE,'\0',sizeof(STK_PRICE));
				memset(STK_PRICE_MAR,'\0',sizeof(STK_PRICE_MAR));
				memset(STK_AFFORD,'\0',sizeof(STK_AFFORD));
				memset(STK_NUM,'\0',sizeof(STK_NUM));
				memset(STK_SUM,'\0',sizeof(STK_SUM));
				stk_num = 0;
				stk_price = 0;
				stk_afford = 0;
				stk_price_mar = 0;
				stk_sum = 0;
				continue;
			}
		}		
		
		if(MouseX > 289 && MouseX < 361 && MouseY > 274 && MouseY < 304)
		{
			if(mouse_press(289,274,361,304) == 2)
			{
				MouseS = 1;
				if(num == 0 )
				{
					lightbutton_trade_buy(7);
					num = 7;
				}
				continue;
			}
			else if(mouse_press(289,274,361,304) == 1)   //���밴ť
			{
				MouseS = 0;
				delay(150);
				setfillstyle(1,BLACK);
				bar(420,277,550,297);      //����ɹ���
				if(stk_judgebuy(STK_CODE,STK_NAME,STK_NUM,STK_PRICE,STK_SUM,STK_PRICE_MAR) && stk_judgesum(stk_num,stk_afford,stk_price,STK_SUM,STK_NUM,&stk_sum) && (stk_num != 0))
				{	//ȫ���롢�ж��ܼۡ��м�
					t = time(NULL);
					tp = localtime(&t);
					memset(STK_TIME,'\0',sizeof(STK_TIME));
					memset(STK_TEMP,'\0',sizeof(STK_TEMP));
					ultoa(1900 + tp->tm_year,STK_TEMP,10);
					strcat(STK_TIME,STK_TEMP);
					strcat(STK_TIME,"/");
					memset(STK_TEMP,'\0',sizeof(STK_TEMP));
					ultoa(1 + tp->tm_mon,STK_TEMP,10);
					strcat(STK_TIME,STK_TEMP);
					strcat(STK_TIME,"/");
					memset(STK_TEMP,'\0',sizeof(STK_TEMP));
					ultoa(tp->tm_mday,STK_TEMP,10);
					strcat(STK_TIME,STK_TEMP);
					//��ȡ�ɽ�����
					stk_balance = stk_balance - stk_sum;
					input_balance(u,stk_balance);
					get_time(tp, &minute, 1);
					read_balance(stk_balance);  //�ɽ�֮�����¶�ȡ
				//	printf("%d",tp->tm_sec);
					stk_input_hst(u,STK_TIME,STK_CODE,STK_NAME,STK_NUM,STK_PRICE,STK_SUM,1);
					stk_input_hold(u,STK_TIME,STK_CODE,STK_NAME,STK_NUM,STK_PRICE,0);
					delay(300);
					puthz(420, 277, "����ɹ���", 16, 17, YELLOW);
					new_afford(&stk_afford, stk_balance, stk_price, STK_AFFORD);   //���¼�������
				}  //�ɽ����ڣ�֤ȯ���룬֤ȯ���ƣ��������ɽ��������ɽ����ۣ��ɽ����
				continue;      //���������ж�,�Լ��������ݿ�
			} //����֮����BC��������
		}
		if(num != 0)
		{
			recoverbutton_trade_buy(num);
			num = 0;
		}
		if(strlen(STK_CODE) == 6)
		{
			if(input_flag == 0)
			{
				clrmous(MouseX,MouseY);       //ȥ��
				settextstyle(2,0,6);
				setfillstyle(1,LIGHTBLUE);
				bar(222,74,381,94);
				setcolor(WHITE);
				settextjustify(LEFT_TEXT, TOP_TEXT);
				settextstyle(2, HORIZ_DIR, 6);
				outtextxy(230,73,STK_CODE);
				input_flag = 1;                   	 //��Ϊ���������Ǻŷ�ֹ�ظ�����
			}
			continue;
		}
		if(input_flag != 0)
		{
			input_flag = 0;
		}
	}
}

/***************************************************
FUNCTION: lightbutton_trade_buy
DESCRIPTION: ����������
INPUT: num
RETURN: ��
***************************************************/
void lightbutton_trade_buy(short int num)
{
	delay(10);
	clrmous(MouseX,MouseY);
	setcolor(LIGHTGRAY);
	setlinestyle(0,0,1);
	if(num == 1)
	{
		setlinestyle(0,0,3);
		setcolor(RED);
		rectangle(222,170,381,190);
	}
	else if(num == 2)
	{
		line(262,200,262,220);
		line(227,221,262,221);
	}
	else if(num == 3)
	{
		line(302,200,302,220);
		line(267,221,302,221);
	}
	else if(num == 4)
	{
		line(342,200,342,220);
		line(307,221,342,221);
	}
	else if(num == 5)
	{
		line(382,200,382,220);
		line(347,221,382,221);
	}
	else if(num == 6)
	{
		setfillstyle(1,LIGHTBLUE);
		bar(163,274,235,304);                 //y+20
		puthz(171,277,"����",24,32,BLUE);
		setcolor(WHITE);
		rectangle(163,274,235,304);
	}
	else if(num == 7)
	{
		setfillstyle(1,LIGHTRED);
		bar(289,274,361,304);
		puthz(297,277,"����",24,32,RED);
		setcolor(WHITE);
		rectangle(289,274,361,304);
	}
}

/*******************************************************
FUNCTION: recoverbutton_trade_buy
DESCRIPTION: �������Ļָ�����
INPUT: num
RETURN: �� 
********************************************************/

void recoverbutton_trade_buy(short int num)
{
	delay(10);
	clrmous(MouseX, MouseY);
	setcolor(BLACK);
	setlinestyle(0,0,1);
	if(num == 1)
	{
		setlinestyle(0,0,3);
		setcolor(WHITE);
		rectangle(222,170,381,190);
	}
	else if(num == 2)
	{
		line(262,200,262,220);
		line(227,221,262,221);
	}
	else if(num == 3)
	{
		line(302,200,302,220);
		line(267,221,302,221);
	}
	else if(num == 4)
	{
		line(342,200,342,220);
		line(307,221,342,221);
	}
	else if(num == 5)
	{
		line(382,200,382,220);
		line(347,221,382,221);
	}
	else if(num == 6)
	{
		setfillstyle(1,LIGHTBLUE);
		bar(163,274,235,304);                 //y+20
		puthz(171,277,"����",24,32,WHITE);
	}
	else if(num == 7)
	{
		setfillstyle(1,LIGHTRED);
		bar(289,274,361,304);
		puthz(297,277,"����",24,32,WHITE); 
	}
}

/*******************************************************************
FUNCTION: stk_judgesum
DESCRIPTION: �ж�������������������Ĺ�ϵ��������ʾ
INPUT: stk_num,stk_afford,stk_price,STK_SUM,STK_NUM,stk_sum
return: �������������ڿ���ɷ���1�����򷵻�0
*******************************************************************/
int stk_judgesum(unsigned long stk_num,unsigned long stk_afford,float stk_price,char* STK_SUM,char* STK_NUM, double* stk_sum)     //�������� ����� �ܽ��
{
	if(stk_num > stk_afford)
	{
		setfillstyle(1,LIGHTRED);
		bar(121,334,361,354);
		puthz(129,336,"ע�⣺�����������ڿ�������",16,17,WHITE);
		return 0;
	}
	else 
	{
		memset(STK_SUM,'\0',sizeof(STK_SUM));
		setfillstyle(1,BLACK);
		bar(121,334,361,354);
		setfillstyle(1,LIGHTRED);
		bar(151,334,361,354);
		setcolor(WHITE);
		settextjustify(RIGHT_TEXT,TOP_TEXT);
		settextstyle(2, HORIZ_DIR, 6);
		outtextxy(214,334,STK_NUM);
		puthz(214,336,"��",16,17,WHITE);
		puthz(240,336,"���",16,17,YELLOW);
		settextjustify(LEFT_TEXT,TOP_TEXT);
		setcolor(YELLOW);
		outtextxy(279,334,":");
		*stk_sum = stk_num*stk_price;
		float_to_str(STK_SUM,*stk_sum,2);
		settextjustify(RIGHT_TEXT,TOP_TEXT);
		outtextxy(361,334,STK_SUM);
		return 1;
	}
}

/************************************************************************
FUNCTION: stk_judgebuy
DESCRIPTION: �ж��ܼۡ��м�
INPUT: stk_code,stk_name,stk_num,stk_price,stk_sum,stk_price_mar
RETURN: ������Ҫ���򷵻�1�����򷵻�0
************************************************************************/
int stk_judgebuy(char* stk_code,char* stk_name,char* stk_num,char* stk_price,char* stk_sum,char* stk_price_mar)
{
	float price = 0;
	float price_mar = 0;
	if((strlen(stk_code) != 0) && (strlen(stk_name) != 0) && (strlen(stk_num) != 0) && (strlen(stk_price) != 0) && (strlen(stk_sum) != 0) && (strlen(stk_price_mar) != 0))
	{
		turn_a2f(stk_price,&price);
		turn_a2f(stk_price_mar,&price_mar);
		if(price <= price_mar)
		{
			if((price_mar - price) > 0.05)
			{
				setfillstyle(1,BLACK);
				bar(420,170,630,190);
				puthz(420,172,"����۸��������",16,17,YELLOW);
				return 0;
			}
			else
			{
				setfillstyle(1,BLACK);
				bar(420,170,630,190);
				return 1;
			}
		}
		else
		{
			setfillstyle(1,BLACK);
			bar(420,170,630,190);
			puthz(420,172,"����۸�����м�",16,17,YELLOW);
			return 1;
		}
	}
	else 
		return 0;
}

/**********************************************************************
FUNCTION: stk_input_hst
DESCRIPTION: ��������Ϣ������ʷ�ɽ�
INPUT: u,stk_time,stk_code,stk_name,stk_num,stk_price,stk_sum,i
RETURN: ��
**********************************************************************/
void stk_input_hst(USER* u,char* stk_time,char* stk_code,char* stk_name,char* stk_num,char* stk_price,char* stk_sum,int i)
{	 //���һ���ǲ�������
	FILE* fp;
	Hstdata *hst_buy;       				 //��ʷ�ɽ���
	char STK_ADR[50] = {'\0'};    		     //��ַ��
	if((hst_buy = (Hstdata*)malloc(sizeof(Hstdata))) == NULL)
	{
		printf("memoryallocation runs wrong");
		delay(3000);
		exit(1);
	}                                        //���ö���
	memset(hst_buy,'\0',sizeof(Hstdata));    //��ʼ��
	strcpy(STK_ADR,"database\\USER\\");      //����'\0'����
	strcat(STK_ADR,u->user);
	//�ɴ����ļ���
	if(access(STK_ADR, 0) == -1)             //�������ļ���
	{
		if(mkdir(STK_ADR) != 0)              //δ�ɹ�����
		{
			printf("The file opens failued");
		}
	}//��������ֱ�Ӵ�
	strcat(STK_ADR,"\\");
	strcat(STK_ADR,"history.dat");
	if((fp=fopen(STK_ADR,"ab+"))==NULL)
	{
		printf("can't find the file history.dat while init the data of stock!\n");
		delay(1000);
		exit(1);
	}
	fseek(fp,0,SEEK_END);      //��λ�����
	strcpy(hst_buy->sto_date,stk_time);
	strcpy(hst_buy->sto_code,stk_code);
	strcpy(hst_buy->sto_name,stk_name);
	strcpy(hst_buy->sto_num,stk_num);
	strcpy(hst_buy->sto_price,stk_price);
	strcpy(hst_buy->sto_amount,stk_sum);
	if(i == 1)
	{
		hst_buy->sto_flag[0] = '1';
	}
	else if(i == 2)
	{
		hst_buy->sto_flag[0] = '2';
	}
	hst_buy->sto_date[11] = '\t';
	hst_buy->sto_code[6] = '\t';
	hst_buy->sto_name[9] = '\t';
	hst_buy->sto_flag[1] = '\t';
	hst_buy->sto_num[9] = '\t';
	hst_buy->sto_price[6] = '\t';
	hst_buy->sto_amount[19] = '\n';    //�����ʽ
	fwrite(hst_buy,sizeof(Hstdata),1,fp);
	if (fclose(fp) != 0)
	{
		printf("\n cannot close Database");
		exit(1);
	}
	if(hst_buy != NULL)
	{
		free(hst_buy);
		hst_buy = NULL;
	}
	return;
}

/*********************************************************************
FUNCTION: stk_input_hold
DESCRIPTION: �����׺���Ϣ���Ĵ���ֲ�
ATTENTION: ����iΪ0�������룬Ϊ1ʱ��������
INPUT:  u,stk_time,stk_code,stk_name,stk_num,stk_price,i
RETURN: ��
*********************************************************************/
void stk_input_hold(USER* u, char* stk_time,char* stk_code, char* stk_name,char* stk_num,char* stk_price,int i)      //�ֲ�
{	//�ɽ����ڣ�֤ȯ���룬֤ȯ���ƣ��ɽ��������ɽ�����
	FILE* fp;
	Hold* hold;       				         //�ֲ���
	int l = 0;                               //�ļ�λ��
	int day = 0;                             //ʱ��
	int prime[3] = {0};                      //����ĳֲ�ʱ��
	int now[3] = {0};                        //���ڵĳֲ�ʱ��
	unsigned long num = 0;               	 //�ֹ���
	unsigned long num_prime = 0;             //��ʷ�ֹ���
	float price = 0;                         //�ɱ��۸�
	float price_prime = 0;                   //��Ʊ����
	double sum = 0;               			 //��Ʊ�ܼ�
	double sum_prime = 0;                    //�ֲֽ��
	char STK_ADR[50] = {'\0'};    		     //��ַ��
	if((hold = (Hold*)malloc(sizeof(Hold))) == NULL)
	{
		printf("memoryallocation runs wrong");
		delay(3000);
		exit(1);
	}                                        //�������ã���ʱ�ͷ�
	memset(hold,'\0',sizeof(Hold));  		 //��ʼ��
	strcpy(STK_ADR,"database\\USER\\");      //����'\0'����
	strcat(STK_ADR,u->user);
	//�ɴ����ļ���
	if(access(STK_ADR, 0) == -1)             //�������ļ���
	{
		if(mkdir(STK_ADR) != 0)              //δ�ɹ�����
		{
			printf("The file opens failued");
		}
	}//��������ֱ�Ӵ�
	strcat(STK_ADR,"\\");
	strcat(STK_ADR,"hold.dat");
	if(access(STK_ADR, 0) == -1)              //��������ڳֲ��ļ�
	{
		if((fp = fopen(STK_ADR,"ab+"))==NULL)
		{
			printf("can't find the file hold.dat while init the data of stock!\n");
			delay(1000);
			exit(1);
		}
	}
	else      								  //�����ڣ�����rb��ʽ
	{
		if((fp = fopen(STK_ADR, "rb+")) == NULL)
		{
			printf("can't find the file hold.dat while init the data of stock!\n");
			delay(1000);
			exit(1);
		}
	}
	
	if(i == 0)
	{
		l = get_hold_stk(hold, stk_name, STK_ADR);   //��֤ȯ���ƻ�ȡ�ֲֹ�Ʊ
		if(l == 0)
		{
			memset(hold,'\0',sizeof(Hold));
			strcpy(hold->sto_date,stk_time);
			strcpy(hold->sto_code,stk_code);
			strcpy(hold->sto_name,stk_name);
			strcpy(hold->sto_num,stk_num);
			strcpy(hold->sto_price,stk_price);
			hold->sto_day[0] = '0';
			hold->sto_date[10] = '\t';
			hold->sto_code[6] = '\t';  
			hold->sto_name[9] = '\t';
			hold->sto_num[9] = '\t';
			hold->sto_price[6] = '\t';
			hold->sto_day[3] = '\n';
			fseek(fp, 0, SEEK_END);
			fwrite(hold, sizeof(Hold), 1, fp);
			if(hold != NULL)
			{
				free(hold);
				hold = NULL;
			}
			if(fclose(fp) != 0)
			{
				printf("\n cannot close Database");
				exit(1);
			}
			return;
		}
		else 												//��������������ں����︲��
		{
			itoa(day, hold->sto_day, 10);
			stk_turn_a2i(stk_num, &num);      				//�ɽ�����
			turn_a2f(stk_price,&price);                     //�ɽ��۸�
			sum = price * num;                              //�ܽ��
		
			stk_turn_a2i(hold->sto_num, &num_prime);        //�ֹ���
			turn_a2f(hold->sto_price,&price_prime);         //ԭ�ɱ��۸�
			sum_prime = price_prime * num_prime;            //ԭ�۸��ܽ�
	
			sum = sum + sum_prime;                          //�ܽ��
			num = num + num_prime;                          //�����������
			price = sum / num;                              //�µĳɱ��ܼ�
		
			memset(hold->sto_num, '\0', sizeof(hold->sto_num));
			ultoa(num, hold->sto_num, 10);                  //����hold��
			float_to_str(hold->sto_price, price, 2);        //price����
			
			turn_a2i(hold->sto_date, prime, prime + 1, prime + 2);
			turn_a2i(stk_time, now, now + 1, now + 2);
			day = get_hold_day(prime, now);
			memset(hold->sto_day, '\0', sizeof(hold->sto_day));
			itoa(day, hold->sto_day, 10);                   //�ֲ�����
		
			hold->sto_date[10] = '\t';
			hold->sto_code[6] = '\t';  
			hold->sto_name[9] = '\t';
			hold->sto_num[9] = '\t';
			hold->sto_price[6] = '\t';
			hold->sto_day[3] = '\n';
		
			l = l - 1;   
			fseek(fp, l * sizeof(Hold), SEEK_SET);
			fwrite(hold, sizeof(Hold), 1, fp);              //д��ֲ�
			if(hold != NULL)
			{
				free(hold);
				hold = NULL;
			}
			if(fclose(fp) != 0)
			{
				printf("\n cannot close Database");
				exit(1);
			}
			return ;                                       //д�벢�ͷ�Ȼ�󷵻�
		}
	}
	else if(i == 1)
	{
		l = get_hold_stk(hold, stk_name, STK_ADR);  	   //λ��
		stk_turn_a2i(hold->sto_num, &num_prime);           //�ֲֹ�Ʊ
		stk_turn_a2i(stk_num, &num);                       //�ɽ�����
		//printf("%s",stk_num);
	//	printf("\n%ld",num);
	//	printf("\n%ld",num_prime);
		num = num_prime - num;                     		   //�����������
		
		
		memset(hold->sto_num, '\0', sizeof(hold->sto_num));
		if(num == 0)
		{  //���������Ϊ0
			memset(hold, '\0', sizeof(Hold));  			   //��NULl��Ӧ�õ���ǰ�Ƹ��ǵ���
		}
		else
		{   //��Ϊ0
			ultoa(num, hold->sto_num, 10);                 //����hold��
			turn_a2i(hold->sto_date, prime, prime + 1, prime + 2);
			turn_a2i(stk_time, now, now + 1, now + 2);
			day = get_hold_day(prime, now);
			memset(hold->sto_day, '\0', sizeof(hold->sto_day));
			itoa(day, hold->sto_day, 10);                  //�ֲ�����
		}
		
		hold->sto_date[10] = '\t';
		hold->sto_code[6] = '\t';  
		hold->sto_name[9] = '\t';
		hold->sto_num[9] = '\t';
		hold->sto_price[6] = '\t';
		hold->sto_day[3] = '\n';
		l = l - 1;   
		
		fseek(fp, l * sizeof(Hold), SEEK_SET);
		fwrite(hold, sizeof(Hold), 1, fp);              //д��ֲ�
		if(hold != NULL)
		{
			free(hold);
			hold = NULL;
		}
		if(fclose(fp) != 0)
		{
			printf("\n cannot close Database");
			exit(1);
		}
		return ;                                       //д�벢�ͷ�Ȼ�󷵻�
	}
	if(hold != NULL)
	{
		free(hold);
		hold = NULL;
	}
	if(fclose(fp) != 0)
	{
		printf("\n cannot close Database");
		exit(1);
	}
}

/*************************************************
FUNCTION: get_new_price
DESCRIPTION: �����м�
INPUT: STK_PRICE,stk_price_mar,color
RETURN: ��
**************************************************/
void get_new_price(char* STK_PRICE_MAR, float* stk_price_mar,int color)                     //��ȡ�µ��м�
{
	int i = 0, j = 0;
	srand(time(NULL));
	j = rand() % 2;
	//printf("%f",*stk_price_mar);
	if(j == 0)
	{ 
		i = rand() % 4;         //0,1,2,3
		if(i == 1)
			*stk_price_mar = *stk_price_mar + 0.01;
		else if(i == 2)
			*stk_price_mar = *stk_price_mar + 0.02;
		else if(i == 3)
			*stk_price_mar = *stk_price_mar + 0.03;
	}
	else if(j == 1)
	{
		i = rand() % 4;         //0,1,2,3
		if(i == 1)
			*stk_price_mar = *stk_price_mar - 0.01;
		else if(i == 2)
			*stk_price_mar = *stk_price_mar - 0.02;
		else if(i == 3)
			*stk_price_mar = *stk_price_mar - 0.03;
	}
	//printf("%f",*stk_price_mar);
	memset(STK_PRICE_MAR,'\0',sizeof(STK_PRICE_MAR));
	float_to_str(STK_PRICE_MAR, *stk_price_mar, 2);
	setfillstyle(1,BLACK);
	bar(420, 138, 630, 158);
	if(color == 1)
	{
		puthz(420,140,"��ǰ�м�",16,17,LIGHTRED);
	}
	else if(color == 2)
	{
		puthz(420,140,"��ǰ�м�",16,17,LIGHTCYAN);
	}
	settextjustify(LEFT_TEXT,TOP_TEXT);
	settextstyle(2,0,6);
	setcolor(WHITE);
	outtextxy(500,137,STK_PRICE_MAR);             //��ʾ��ǰ�м�
}

/*********************************************************
FUNCTION: new_afford
DESCRIPTION: ���¿������
INPUT: stk_afford,stk_balance,stk_price,STK_AFFORD
RETURN: ��
*********************************************************/

void new_afford(unsigned long* stk_afford,float stk_balance, float stk_price, char* STK_AFFORD)
{
	clrmous(MouseX,MouseY);
	*stk_afford = 0;
	setfillstyle(1,WHITE);					
	bar(222,170,381,190);                    //�����Լ�����
	setfillstyle(1,BLACK);
	bar(420,170,630,190);                   //�ڸ�����ʱ���м���Ϣ
	*stk_afford = (unsigned long)(stk_balance / stk_price);	
	if(*stk_afford >= 100)
	{
		stk_hundred(*stk_afford,STK_AFFORD);			//�������������۸��Լ��Լ���������������(�����ɺ���)
		setcolor(BLACK);
		settextjustify(LEFT_TEXT, TOP_TEXT);
		settextstyle(2, HORIZ_DIR, 6);
		outtextxy(230,169,STK_AFFORD);          //����������
	}
}