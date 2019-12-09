#include"trdbuy.h"
#include"public.h"
#include"trade.h"
#include"traverse.h"
#include"storead.h"
#include"trdsale.h"


/************************************************
trade.c
COPYRIGHT: dengshumin
FUNCTION:  user trade control
ABSTRACT:
		A.stock buy
		B.stock sale
		C.history deal
DATE: 2019/10/20
*************************************************/


/**********************************
FUNCTION: trade
DESCRIPTION: ʵ�ֽ��׽�����ܿ���
INPUT: cinfo, u, t, sto_num
RETURN: ��
***********************************/
//                             ������       �ڼ�ֻ��
void trade(Ctr* cinfo,USER* u, short int t, int sto_num) 
{
	short int trmenu_ord = t;                   //�˵���ť��
	short int trmenu_ord_last = t;
	memset(cinfo,0,sizeof(Ctr));	   //��������Ϣ��ʼ��
	cinfo->func = 3;          	   	   //��3��ǽ��׺����Ľ���
	clrmous(MouseX,MouseY);
	delay(10);
	cleardevice();
	mainmenu_draw();
	trade_menu_draw(trmenu_ord);
	//buy_draw();
	while(1)
	{
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
			clrmous(MouseX,MouseY);
			setfillstyle(1,BLACK);
			bar(0,25,639,480);
			mainmenu_draw();
			control_judge(u);
			trade_menu_draw(trmenu_ord);
			if(trmenu_ord == 0)
				buy_draw();
			else if(trmenu_ord == 1)
				sale_draw();
			else if(trmenu_ord == 2)
				history_draw();
			submenu_draw(cinfo->itemnum);
		}
		if(cinfo->func != 3 && cinfo->func != 13)
		{
			clrmous(MouseX,MouseY);
			delay(10);                    //��ֹ����
			return; 	 //��������������ܼ����ͷ��أ�����ǻ��ԭ����������ж�
		}
		change_trdmenu(&trmenu_ord,&trmenu_ord_last);
		if(trmenu_ord == 0)
		{
			buy(&trmenu_ord,&trmenu_ord_last, cinfo, u, sto_num);
		}
		else if(trmenu_ord == 1)          //����������
		{	
			sale(&trmenu_ord,&trmenu_ord_last, cinfo, u);
		}
		else if(trmenu_ord == 2)          //��ʷ�ɽ�
		{
			trd_history(&trmenu_ord,&trmenu_ord_last, cinfo, u);
		}

	}
}

/******************************************
FUNCTION: trade_menu_draw
DESCRIPTION: ���ƽ������˵�
ATTENTION: ���ݲ�����ѡ������ĸ��˵�
INPUT: flag
RETURN: ��
******************************************/
void trade_menu_draw(int flag)
{
	setcolor(RED);
	setlinestyle(0,0,1);
	line(70,24,120,64);
	puthz(12,32,"����",32,36,RED);
	if(flag == 0)
	{
		puthz(63,25+50,"����",24,25,CYAN);
		puthz(63,65+50,"����",24,25,WHITE);
		puthz(13,105+50,"��ʷ�ɽ�",24,25,WHITE);
	}
	else if(flag == 1)
	{
		puthz(63,25+50,"����",24,25,WHITE);
		puthz(63,65+50,"����",24,25,CYAN);
		puthz(13,105+50,"��ʷ�ɽ�",24,25,WHITE);
	}
	else if(flag == 2)
	{
		puthz(63,25+50,"����",24,25,WHITE);
		puthz(63,65+50,"����",24,25,WHITE);
		puthz(13,105+50,"��ʷ�ɽ�",24,25,CYAN);
	}
	setcolor(RED);
	line(120,64,120,459);
/*	setfillstyle(1,WHITE);
	bar(0,456,640,480);
	puthz(10,459,"�������",16,17,BLACK);
	setcolor(DARKGRAY);
	setlinestyle(0,0,1);
	line(89,456,89,480);*/
}

/*************************************
FUNCTION: buy_draw
DESCRIPTION: �����������
INPUT: void
RETURN: ��
*************************************/
void buy_draw(void)
{
	clrmous(MouseX,MouseY);
	setlinestyle(0,0,1);
	setcolor(LIGHTGRAY);
	puthz(160,40,"�����Ʊ",24,26,RED);        //135~381
	
	setfillstyle(1,WHITE);
	puthz(135,76,"֤ȯ����",16,17,RED);     //���32
	bar(222,74,381,94);                     //��20
	
	puthz(135,108,"֤ȯ����",16,17,RED);          //x��222��381
	
	puthz(135,140,"����۸�",16,17,RED);
	bar(222,138,381,158);
	line(362,138,362,158);
	line(362,148,381,148);
	
	puthz(135,172,"���򣨹ɣ�",16,17,RED);
	bar(222,170,381,190);

	settextjustify(LEFT_TEXT, TOP_TEXT);
	settextstyle(2, HORIZ_DIR, 6);
	setcolor(WHITE);
	outtextxy(230,200,"1/2");
	
	outtextxy(270,200,"1/3");
	
	outtextxy(310,200,"1/4");
	
	outtextxy(350,200,"1/5");

	setcolor(LIGHTGRAY);
	puthz(135,236,"��������",16,17,RED);      //(135,234,381,254)
	bar(222,234,381,254);
	line(362,234,362,254);
	line(362,244,381,244);

	setfillstyle(1,LIGHTBLUE);
	bar(163,274,235,304);                 //y+20
	puthz(171,277,"����",24,32,WHITE);

	setfillstyle(1,LIGHTRED);
	bar(289,274,361,304);
	puthz(297,277,"����",24,32,WHITE);
	
	setcolor(RED);
	setfillstyle(1,RED);
	line(372,139,378,146);
	line(378,146,366,146);
	line(366,146,372,139);
	floodfill(372,140,RED);
	line(372,157,378,150);
	line(378,150,366,150);
	line(366,150,372,157);
	floodfill(372,156,RED);
	line(372,235,378,242);
	line(378,242,366,242);
	line(366,242,372,235);
	floodfill(372,236,RED);
	line(372,253,378,246);
	line(378,246,366,246);
	line(366,246,372,253);
	floodfill(372,252,RED);       //��������
}

/*************************************
FUNCTION: sale_draw
DESCRIPTION: ������������
INPUT: void
RETURN: ��
*************************************/
void sale_draw(void)
{
/*	int tr1[] = {372,139,378,146,366,146,372,139};
	int tr2[] = {372,157,378,150,366,150,372,157};
	int tr3[] = {372,203,378,210,366,210,372,203};
	int tr4[] = {372,221,378,214,366,214,372,221};*/
	setcolor(LIGHTGRAY);
	puthz(160,40,"������Ʊ",24,26,LIGHTBLUE);        //135~381
	
	setfillstyle(1,WHITE);
	puthz(135,76,"֤ȯ����",16,17,LIGHTBLUE);     //���32
	bar(222,74,381,94);                     //��20
	
	puthz(135,108,"֤ȯ����",16,17,LIGHTBLUE);          //x��222��381
//	puthz(232,108,"ƽ������",16,17,WHITE);
	
	puthz(135,140,"�����۸�",16,17,LIGHTBLUE);
	bar(222,138,381,158);
	line(362,138,362,158);
	line(362,148,381,148);
	
	puthz(135,172,"�������",16,17,LIGHTBLUE);
	bar(222,170,381,190);

	settextjustify(LEFT_TEXT, TOP_TEXT);
	settextstyle(2, HORIZ_DIR, 6);
	setcolor(WHITE);
	outtextxy(230,200,"1/2");
	
	outtextxy(270,200,"1/3");
	
	outtextxy(310,200,"1/4");
	
	outtextxy(350,200,"1/5");

	setcolor(LIGHTGRAY);
	puthz(135,236,"��������",16,17,LIGHTBLUE);      //(135,234,381,254)
	bar(222,234,381,254);
	line(362,234,362,254);
	line(362,244,381,244);

	setfillstyle(1,LIGHTRED);
	bar(163,274,235,304);                 //y+20
	puthz(171,277,"����",24,32,WHITE);

	setfillstyle(1,LIGHTBLUE);
	bar(289,274,361,304);
	puthz(297,277,"����",24,32,WHITE);
	
	setcolor(RED);
	setfillstyle(1,RED);
	line(372,139,378,146);
	line(378,146,366,146);
	line(366,146,372,139);
	floodfill(372,140,RED);
	line(372,157,378,150);
	line(378,150,366,150);
	line(366,150,372,157);
	floodfill(372,156,RED);
	line(372,235,378,242);
	line(378,242,366,242);
	line(366,242,372,235);
	floodfill(372,236,RED);
	line(372,253,378,246);
	line(378,246,366,246);
	line(366,246,372,253);
	floodfill(372,252,RED);       //��������
	
}

/*************************************
FUNCTION: history_draw
DESCRIPTION: ������ʷ�ɽ�����
INPUT: void
RETURN: ��
*************************************/
void history_draw(void)
{
	int i;
	//setfillstyle(1,WHITE);
	//bar(121,26,639,458);
	setcolor(LIGHTGRAY);
	rectangle(121,26,639,456);
	for(i=0;i<7;i++)
	{
		line(120+74*(i+1),26,120+74*(i+1),455);
		if(i == 0)
			puthz(120+74*i+4,32,"�ɽ�����",16,17,WHITE);
		else if(i == 1)
			puthz(120+74*i+4,32,"֤ȯ����",16,17,WHITE);
		else if(i == 2)
			puthz(120+74*i+4,32,"֤ȯ����",16,17,WHITE);
		else if(i == 3)
			puthz(120+74*i+21,32,"����",16,17,WHITE);
		else if(i == 4)
			puthz(120+74*i+4,32,"�ɽ�����",16,17,WHITE);
		else if(i == 5)
			puthz(120+74*i+4,32,"�ɽ�����",16,17,WHITE);
		else if(i == 6)
			puthz(120+74*i+4,32,"�ɽ����",16,17,WHITE);
	}
	for(i=0;i<17;i++)
	{
		line(121,26+24*(i+1),639,26+24*(i+1));
	}
}

/************************************************
FUNCTION: change_trdmenu
DESCRIPTION: ͨ��������ı亯���˵���
INPUT: trmenu_ord,trmenu_ord_last
RETURN: ����ı��˲˵�ѡ�񷵻�1�����򷵻�0
*************************************************/
int change_trdmenu(short int *trmenu_ord,short int *trmenu_ord_last)
{
	if (mouse_press(60,75,115,100) == 2)
	{
		MouseS = 1;
		return 0;
	}
	else if(mouse_press(60,115,115,140) == 2)
	{
		MouseS = 1;
		return 0;
	}
	else if(mouse_press(10,155,115,180) == 2)
	{
		MouseS = 1;
		return 0;
	}
	else if (mouse_press(60,75,115,100) == 1)
	{
		*trmenu_ord = 0;
	}
	else if(mouse_press(60,115,115,140) == 1)
	{
		*trmenu_ord = 1;
	}
	else if(mouse_press(10,155,115,180) == 1)
	{
		*trmenu_ord = 2;
	}
	if(*trmenu_ord != *trmenu_ord_last)
	{
		clrmous(MouseX,MouseY);
		setfillstyle(1,BLACK);
		bar(121,25,640,455);
		if(*trmenu_ord == 0)
		{
			setfillstyle(1,BLACK);
			bar(60,75,115,100);
			puthz(63,25+50,"����",24,25,CYAN);
			//buy_draw();
		}
		else if(*trmenu_ord == 1)
		{
			setfillstyle(1,BLACK);
			bar(60,115,115,140);
			puthz(63,65+50,"����",24,25,CYAN);
			//sale_draw();
		}
		else if(*trmenu_ord == 2)
		{
			setfillstyle(1,BLACK);
			bar(10,155,115,180);
			puthz(13,105+50,"��ʷ�ɽ�",24,25,CYAN);
			//history_draw();
		}
		if(*trmenu_ord_last == 0)
		{
			setfillstyle(1,BLACK);
			bar(60,75,115,100);
			puthz(63,25+50,"����",24,25,WHITE);
		}
		else if(*trmenu_ord_last == 1)
		{
			setfillstyle(1,BLACK);
			bar(60,115,115,140);
			puthz(63,65+50,"����",24,25,WHITE);
		}
		else if(*trmenu_ord_last == 2)
		{
			setfillstyle(1,BLACK);
			bar(10,155,115,180);
			puthz(13,105+50,"��ʷ�ɽ�",24,25,WHITE);
		}
		*trmenu_ord_last = *trmenu_ord;
		return 1;
	}
	if(MouseS != 0)
		MouseS = 0;
	return 0;
}

/******************************************
FUNCTION: input_trade
DESCRIPTION: ��Ʊ�����뷨
ATTENTION:   ��������ֻ����������
INPUT: id,x1,y1,charnum,color
RETURN: ��
******************************************/
void input_trade(char* id, int x1, int y1, int charnum, int color)//������ַ����������xy��������ַ����ƣ���������ɫ
{
	int i = 0;
	char t;
	int s;
	clrmous(MouseX, MouseY);
	delay(20);
	setfillstyle(SOLID_FILL, color);
	setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
	setcolor(BLACK);
	settextstyle(2, 0, 6);
	settextjustify(LEFT_TEXT, TOP_TEXT);
	line(x1 + 10, y1 + 4, x1 + 10, y1 + 16);
	while(bioskey(1))
	{
		s=bioskey(1);//��
	}
	while (1)
	{
	
		t = bioskey(0); 
		if (i < charnum)
		{
			if (t != '\n'
				&& t != '\r'
				&& t != ' '
				&& t != 033)//Esc
			{
				if ((t != '\b' && t >= '0' && t <= '9' ) || t == '.' )
				{
					*(id + i) = t;
					*(id + i + 1) = '\0';
					bar(x1 + 8 + i * 10, y1 + 3, x1 + 12 + i * 10, y1 + 20); //�ڸǹ��
					outtextxy(x1 + 8 + i * 10, y1-1, id + i);//���t�ַ�(16)
					i++;
					line(x1 + 10 + i * 10, y1 + 4, x1 + 10 + i * 10, y1 + 16);
				}
				else if (t == '\b' && i > 0)//�˸��
				{
					bar(x1 + 8 + i * 10, y1 + 3, x1 + 12 + i * 10, y1 + 20);//�ڸǹ��
					bar(x1 - 3 + i * 10, y1 + 3, x1 + 7 + i * 10, y1 + 20);//�ڸ�����
					i--;//����һ������
					line(x1 + 10 + i * 10, y1 + 4, x1 + 10 + i * 10, y1 + 16);//���ƹ��
					*(id + i) = '\0';
					*(id + i + 1) = '\0';
				}
			}
			else
			{
				setfillstyle(SOLID_FILL, color);
				bar(x1 + 8 + i * 10, y1 + 3, x1 + 12 + i * 10, y1 + 20);//�ڸǹ��
				break;
			}
		}
		else if (i >= charnum)
		{
			if (t != '\n'
				&& t != '\r'
				&& t != ' '
				&& t != 033)//Esc
			{
				if (t == '\b' && i > 0)//�˸��
				{
					bar(x1 + 8 + i * 10, y1 + 3, x1 + 12 + i * 10, y1 + 20);//�ڸǹ��
					bar(x1 - 3 + i * 10, y1 + 3, x1 + 7 + i * 10, y1 + 20);//�ڸ�����
					i--;     //����һ������
					line(x1 + 10 + i * 10, y1 + 4, x1 + 10 + i * 10, y1 + 16);//���ƹ��
					*(id + i) = '\0';
				}
			}
			else
			{
				setfillstyle(SOLID_FILL, color);
				bar(x1 + 8 + i * 10, y1 + 3, x1 + 12 + i * 10, y1 + 20);//�ڸǹ��  
				break;
			}
		}
	}
}


/***********************************************************
FUNCTION: trd_history
DESCRIPTION: ��ʷ�ɽ�����Ŀ��ƺ���
ATTENTION:   ����ͨ����UP��DOWN�����ı�չʾ����ʷ�ɽ�
INPUT: trmenu_ord,trmenu_ord_last,cinfo,u
RETURN: ��
***********************************************************/
void trd_history(short int *trmenu_ord,short int *trmenu_ord_last,Ctr* cinfo,USER* u)
{ //��ʷ�ɽ�����ȡ
	
	struct tm *tp = NULL;
	int page = 1;
	int sum_page = 0;
	int minute = 0;
	float stk_balance = 0;    		    //���
	history_draw(); 
	get_time(tp, &minute, 1);           //��ȡʱ��              
	get_balance1(u, &stk_balance);      //ÿ�ε���һ��buy,�����ݿ��л�ȡ���,����ʾ
	read_balance(stk_balance);          //�������
	sum_page = get_hst(u, 1);            //�����ҳ��
	while(1)
	{
		if(strlen(u->user) == 0)
			cinfo->func = 0;
		get_time(tp, &minute, 0); 
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
		if(sum_page != 0)
		{
			if(cinfo->key == DOWN)
			{
				setfillstyle(1,BLACK);
				bar(121,24,640,455);
				history_draw(); 
				page = (page + 1) % sum_page;
				if(page == 0)             //��0ҳ������
					page = sum_page;
				get_hst(u,page);
				cinfo->key = 0;
				continue;    
			}
			if(cinfo->key == UP)
			{
				setfillstyle(1,BLACK);
				bar(121,24,640,455);
				history_draw(); 
				page = (page - 1) % sum_page;   
				if(page == 0)
					page = sum_page;
				get_hst(u,page);
				cinfo->key = 0;
				continue;
			}
		}
		control_key(cinfo);
		if(control_menu(cinfo))
		{
			setfillstyle(1,BLACK);
			bar(0,25,639,480);
			trade_menu_draw(3);
			history_draw();
			get_time(tp, &minute, 1); 
			read_balance(stk_balance);
			get_hst(u,page);
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
	}
}

/********************************************
FUNCTION: float_to_str
DESCRIPTION: ��������ת��Ϊ�ַ�������
INPUT: str,flt,bits
RETURN: ��
********************************************/
void float_to_str(char *str,float flt,int bits)		//bitsΪҪ�����޶�С��λ��
{
	int i;
	unsigned long integer;//��������
	float decimal;//��bits��С������
	int part;//����������С������(���������)
	float temp_bit;//bits�ĺ�һλ��Ҫ��������
	char ch_integer[5] = { '\0' };
	char ch_decimals[3] = { '\0' };
	
	*str = NULL;
	//���Ϊ����ֵС��1�ĸ���
	if (flt > -1.0 && flt < 0.0)
	{
		strcat(str, "-");//��������
	}
	integer = (unsigned long)flt;
	ultoa(integer, ch_integer, 10);
	strcat(str, ch_integer);//������������
	strcat(str, ".");

	decimal = fabs(flt - (int)flt);//С������
	for (i = 0; i < bits; i++)
	{
		decimal *= 10;//������Ҫ��ӡ��λ����������
	}

	//bits�ĺ�һλtemp_bits��������
	temp_bit = decimal - (int)decimal;
	if (temp_bit < 0.5)
	{
		part = (int)decimal;
	}
	else if (temp_bit >= 0.5)
	{
		part = (int)decimal + 1;
	}

	//���С����һλΪ0����ȫ��һλ
	if (part < 10 && part != 0)
	{
		strcat(str, "0");
	}
	//û��С�����֣���ȫ0
	else if (part == 0)
	{
		strcat(str, "00");
	}

	if (part != 0)
	{
		itoa(part, ch_decimals, 10);
		strcat(str, ch_decimals);//����С������
	}
}

/**************************************************************
FUNCTION: stk_turn_a2i
DESCRIPTION: ���ַ���ת�����޷��ų�����
ATTENTION:   �������Ϊint��ָ�봫�룬����ܻ����𾫶���ʧ
INPUT: str,num
RETURN: ��
***************************************************************/
void stk_turn_a2i(char* str, unsigned long* num)	 //STK_NUM�л���int
{
	unsigned long k = 0;
	int i = 0;
	
	for (i = 0; str[i] != '\0' && str[i] != '\t'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			k *= 10;
			k += (unsigned long)(str[i] - '0');
		}
	}
	*num = k;       //����
}

/***********************************************
FUNCTION: stk_judge
DESCRIPTION: �жϳ���ĳ�����Ƿ񻹴���0
INPUT: stk_afford,divisor
RETURN: �������򷵻�1�����򷵻�0
************************************************/
int stk_judge(unsigned long stk_afford, int divisor)   //divisor����
{
	if((stk_afford / divisor) >= 100)
		return 1;
	else 
		return 0;
}

/*******************************************************
FUNCTION: stk_hundred
DESCRIPTION: ���������������ʽ������ַ�����
ATTENTION:   ���������ֻ����ʽ���ᷢ���ı�
INPUT: stk_afford,STK_AFFORD
RETURN: ��
********************************************************/
void stk_hundred(unsigned long stk_afford,char* STK_AFFORD)  //�������������ʽ,stk_afford����
{
	memset(STK_AFFORD,'\0',sizeof(STK_AFFORD));
	stk_afford = stk_afford/100;
	stk_afford = stk_afford*100;
	ultoa(stk_afford,STK_AFFORD,10);
}


