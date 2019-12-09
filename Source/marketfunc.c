#include"public.h"
#include"database.h"
#include"marketfc.h"
#include"techline.h"
#include"storead.h"

/*******************************
marketfunc.c
COPYRIGHT:	weijingmin
FUNCTION:	function in market
ABSTRACT:
		A.change_datashow
		B.draw float
		C.find drawing border
DATE:2019/10/20
********************************/

/*********************************************
FUNCTION:change_datadate
DESCRIPTION���ı���ʾ��Ϣ������
INPUT:sto_num,No_date,info,
	upinfo,downinfo,max,min,read_way,LR
RETURN:��
***********************************************/
void change_datadate(int sto_num, long int* No_date, STODAYFLOAT info[], UPLINE* upinfo, DOWNLINE* downinfo, float* max, float* min, int read_way, int LR)
{
	int i, j;
	if (LR == 1)//��ఴť��ǰ��
	{
		switch (read_way)
		{
		case 1:
			//if (*No_date + 1 + 150 <= maxline)
			//{
			*No_date += 1;
			//}
			break;
		case 2:
			//if (*No_date + 30 + 150 <= maxline)
			//{
			*No_date += 30;
			//}
			break;
		case 3:
			//if (*No_date + 90 + 150 <= maxline)
			//{
			*No_date += 90;
			//}
		}

		sto_daybyday2float(sto_num, *No_date, 150, info);//1Ϊ��Ʊ��ţ�1Ϊ��ʼ������150Ϊ��ȡ����
		get_border(info, max, min, 150);//150Ϊ��ȡ����
		setfillstyle(SOLID_FILL, BLACK);
		bar(81, 73, 619, 341);
		bar(81, 343, 619, 455);//�ڸ�֮ǰ����ͼ��ͼͼ��
		for (i = 0; i < 11; i++)
		{
			for (j = 0; j < 135; j++)
			{
				putpixel(80 + 4 * j, 72 + 40 * i, RED);
			}
		}
		Kline_draw(info, *max, *min);
		MA_draw(info, upinfo, *max, *min);
		VOL_draw(info, downinfo);
	}
	else if (LR == 2)//�Ҳఴť����
	{
		switch (read_way)
		{
		case 1:
			if (*No_date - 1 >= 1)
			{
				*No_date -= 1;
			}
			break;
		case 2:
			if (*No_date - 30 >= 1)
			{
				*No_date -= 30;
			}
			break;
		case 3:
			if (*No_date - 90 >= 1)
			{
				*No_date -= 90;
			}
			break;
		}
		

		sto_daybyday2float(sto_num, *No_date, 150, info);//1Ϊ��Ʊ��ţ�1Ϊ��ʼ������150Ϊ��ȡ����
		get_border(info, max, min, 150);//150Ϊ��ȡ����
		setfillstyle(SOLID_FILL, BLACK);
		bar(81, 73, 619, 341);
		bar(81, 343, 619, 455);//�ڸ�֮ǰ����ͼ��ͼͼ��
		for (i = 0; i < 11; i++)
		{
			for (j = 0; j < 135; j++)
			{
				putpixel(80 + 4 * j, 72 + 40 * i, RED);
			}
		}
		Kline_draw(info, *max, *min);
		MA_draw(info, upinfo, *max, *min);
		VOL_draw(info, downinfo);
	}
}


/*********************************************
FUNCTION:mouse_datashow
DESCRIPTION������ƶ�����ʾ����
INPUT:info,upinfo,downinfo,p_preday,p_day,
	state,colorstate
RETURN:��
***********************************************/
void mouse_datashow(STODAYFLOAT* info, UPLINE upinfo, DOWNLINE downinfo, int* p_preday, int* p_day,int state,int colorstate)
{
	float rose = 0.0;//�Ƿ�
	float rise_fall = 0.0;//�ǵ�
	float swing = 0.0;//���
	char year[20] = { '\0' };
	char month[3] = { '\0' };
	char day[3] = { '\0' };
	int d;
	if (MouseX < 620 && MouseX>80 && MouseY < 456 && MouseY > 24 && (*p_preday != *p_day))
	{
		d = *p_day;

		rose = (100 * (info[d].Close - info[d + 1].Close)) / info[d + 1].Close;
		//�Ƿ�=(�ּ�-��һ�����������̼ۣ�/��һ�����������̼�*100%
		rise_fall = info[d].Close - info[d + 1].Close;
		//�ǵ�=������-������(ǰ����Щ�����е�rise_fall�ǵ����ǵ���������ɫ������Ǽ���ָ����ǵ�)
		swing = (100 * (info[d].High - info[d].Low)) / info[d + 1].Close;
		//��Ʊ����ǹ�Ʊ���̺�ĵ�����߼ۺ���ͼ�֮��Ĳ�ľ���ֵ���������̼۵İٷֱ�
		
		//�ڸǸ�������
		setfillstyle(SOLID_FILL, BLACK);
		bar(80 + 17 * 2 + 4, 27, 80 + 17 * 2 + 4 + 7 * 10, 27 + 10);
		bar(190 + 38, 27, 190 + 38 + 7 * 10, 27 + 10);
		bar(296 + 38, 27, 296 + 38 + 7 * 10, 27 + 10);
		bar(404 + 38, 27, 404 + 38 + 7 * 10, 27 + 10);
		bar(512 + 38, 27, 512 + 38 + 7 * 10, 27 + 10);

		bar(80 + 38, 51, 80 + 38 + 7 * 10, 51 + 10);
		bar(190 + 38, 51, 190 + 38 + 7 * 10, 51 + 10);
		bar(296 + 38, 51, 296 + 38 + 7 * 10, 51 + 10);
		bar(404 + 55, 51, 404 + 55 + 5 * 10, 51 + 10);
		bar(512 + 55, 51, 512 + 55 + 5 * 10, 51 + 10);

		bar(80 + 20, 73, 80 + 20 + 6 * 10, 82);
		bar(170 + 28, 73, 170 + 20 + 6 * 10, 82);
		bar(260 + 28, 73, 260 + 20 + 6 * 10, 82);
		bar(350 + 28, 73, 350 + 20 + 6 * 10, 82);

		bar(80 + 28 + 20, 343, 80 + 20 + 6 * 10, 351);
		bar(170 + 28 + 20, 343, 170 + 20 + 6 * 10, 351);
		bar(260 + 28 + 20, 343, 260 + 20 + 6 * 10, 351);

		
		settextjustify(LEFT_TEXT, TOP_TEXT);
		settextstyle(2, HORIZ_DIR, 4);

		if (rise_fall >= 0)
		{
			settextjustify(LEFT_TEXT, TOP_TEXT);
			settextstyle(0, HORIZ_DIR, 1);
			setcolor(LIGHTRED);
			puthz(82, 50, "�ǵ�", 16, 17, LIGHTRED);
			outtextxy(80 + 17 * 2, 56, ":");
		}
		else if (rise_fall < 0)
		{
			settextjustify(LEFT_TEXT, TOP_TEXT);
			settextstyle(0, HORIZ_DIR, 1);
			setcolor(LIGHTBLUE);
			puthz(82, 50, "�ǵ�", 16, 17, LIGHTBLUE);
			outtextxy(80 + 17 * 2, 56, ":");
		}
		settextjustify(LEFT_TEXT, TOP_TEXT);
		settextstyle(2, HORIZ_DIR, 4);
		outtextxy(80 + 38 + 35, 53, "%");
		if (rose >= 0)
		{
			settextjustify(LEFT_TEXT, TOP_TEXT);
			settextstyle(0, HORIZ_DIR, 1);
			setcolor(RED);
			puthz(190, 50, "�Ƿ�", 16, 17, RED);
			outtextxy(188 + 17 * 2, 56, ":");
		}
		else if (rise_fall < 0)
		{
			settextjustify(LEFT_TEXT, TOP_TEXT);
			settextstyle(0, HORIZ_DIR, 1);
			setcolor(LIGHTCYAN);
			puthz(190, 50, "�Ƿ�", 16, 17, LIGHTCYAN);
			outtextxy(188 + 17 * 2, 56, ":");
		}

		settextjustify(LEFT_TEXT, TOP_TEXT);
		settextstyle(2, HORIZ_DIR, 4);
		outtextxy(190 + 38 + 35, 53, "%");
		setcolor(YELLOW);
		outtextxy(296 + 38 + 35, 53, "%");
		setcolor(LIGHTBLUE);
		outtextxy(404 + 55 + 35, 52, "M");
		setcolor(LIGHTCYAN);
		outtextxy(512 + 55 + 35, 52, "B");

		/*settextjustify(LEFT_TEXT, TOP_TEXT);
		settextstyle(2, HORIZ_DIR, 4);
		setcolor(WHITE);
		outtextxy(80 + 28 + 35, 342, "M");
		setcolor(YELLOW);
		outtextxy(170 + 20 + 35, 342, "M");
		setcolor(GREEN);
		outtextxy(260 + 28 + 35, 342, "M");*/

		setcolor(YELLOW);
		settextjustify(LEFT_TEXT, TOP_TEXT);
		settextstyle(2, HORIZ_DIR, 4);
		itoa(info[d].Year, year, 10);
		itoa(info[d].Month, month, 10);
		itoa(info[d].Day, day, 10);
		strcat(year, "/");
		strcat(year, month);
		strcat(year, "/");
		strcat(year, day);

		outtextxy(80 + 44, 28, year);//��ʾʱ��
		draw_float(info[d].Open, 190 + 44, 28, 2, WHITE);//��
		draw_float(info[d].High, 296 + 44, 28, 2, RED);//���
		draw_float(info[d].Low, 404 + 44, 28, 2, GREEN);//���
		draw_float(info[d].Close, 512 + 44, 28, 2, WHITE);//����

		if (rise_fall >= 0)
		{
			draw_float(rise_fall, 80 + 44, 52, 2, LIGHTRED);//�ǵ�
		}
		else if (rise_fall < 0)
		{
			draw_float(rise_fall, 80 + 44, 52, 2, LIGHTBLUE);//�ǵ�
		}
		if (rose >= 0)
		{
			draw_float(rose, 190 + 44, 52, 2, RED);//�Ƿ�
		}
		else if (rose < 0)
		{
			draw_float(rose, 190 + 44, 52, 2, LIGHTCYAN);//�Ƿ�
		}
		draw_float(swing, 296 + 44, 52, 2, YELLOW);//���
		draw_float(info[d].VOL / 1000000.0, 404 + 61, 52, 2, LIGHTBLUE);//�ɽ���
		draw_float(info[d].VOT / 100000000.0, 512 + 61, 52, 2, LIGHTCYAN);//�ɽ���
		
		draw_float(upinfo.first[d], 80 + 20, 72, 2, WHITE);//5�վ��ߣ�BOLL�Ϲ죬ENE�Ϲ�
		draw_float(upinfo.second[d], 170 + 28, 72, 2, YELLOW);//10�վ��ߣ�BOLL�й죬ENE�й�
		draw_float(upinfo.third[d], 260 + 28, 72, 2 , LIGHTMAGENTA);//20�վ��ߣ�BOLL�¹죬ENE�¹�
		if (state == 0)//������Ҫ���ĸ�����
		{
			draw_float(upinfo.forth[d], 350 + 28, 72, 2, GREEN);//60�վ���
		}
		
		if (colorstate == 1)
		{
			draw_float(downinfo.first[d] / 1000000.0, 80 + 28 + 20, 342, 2, WHITE);//��ͼVOL
		}
		else if (colorstate == 2 )
		{
			draw_float(downinfo.first[d], 80 + 28 + 20, 342, 2, LIGHTRED);//K
		}
		else if (colorstate == 3)
		{
			draw_float(downinfo.first[d], 80 + 28 + 20, 342, 2, WHITE);//DIF
		}
		else if (colorstate == 4)
		{
			draw_float(downinfo.first[d], 80 + 28 + 20, 342, 2, WHITE);//RSI6,BIAS24,CR
		}
		else if (colorstate == 5)
		{
			draw_float(downinfo.first[d] / 1000000.0, 80 + 28 + 20, 342, 2, WHITE);//OBV
		}
		else if (colorstate == 6)
		{
			draw_float(downinfo.first[d], 80 + 28 + 20, 342, 2, WHITE);//DMA,AR
		}
		
		if (colorstate == 1)
		{
			draw_float(downinfo.second[d] / 1000000.0, 170 + 28 + 20, 342, 2, YELLOW);//��ͼVOL5�վ���
		}
		else if (colorstate == 2)
		{
			draw_float(downinfo.second[d], 170 + 28 + 20, 342, 2, YELLOW);//DEA
		}
		else if (colorstate == 3)
		{
			draw_float(downinfo.second[d], 170 + 28 + 20, 342, 2, YELLOW);//D
		}
		else if (colorstate == 4)
		{
			draw_float(downinfo.second[d], 170 + 28 + 20, 342, 2, YELLOW);//RSI12,BIAS24,CRMA1
		}
		else if (colorstate == 6)
		{
			draw_float(downinfo.second[d], 170 + 28 + 20, 342, 2, YELLOW);//AMA,BR
		}
		
		
		if (colorstate == 1)
		{
			draw_float(downinfo.third[d] / 1000000.0, 260 + 28 + 20, 342, 2, GREEN);//��ͼVOL10�վ���
		}
		else if (colorstate == 2)
		{
			draw_float(downinfo.third[d], 260 + 28 + 20, 342, 2, LIGHTMAGENTA);//J
		}
		else if (colorstate == 3)
		{
			draw_float(downinfo.third[d], 260 + 28 + 20, 342, 2, RED);//MACD
		}
		else if (colorstate == 4)
		{
			draw_float(downinfo.third[d], 260 + 28 + 20, 342, 2, LIGHTMAGENTA);//RSI24,BIAS24,CRMA2
		}
		
		
	}
}

/*********************************************
FUNCTION:draw_float
DESCRIPTION����ָ��λ�û�������
INPUT:flt,x,y,bits,color
RETURN:��
***********************************************/
void draw_float(float flt, int x, int y, int bits,int color)//bitsΪҪ�����޶�С��λ��
{
	int i;
	int integer;//��������
	float decimal;//��bits��С������
	int part;//����������С������(���������)
	float temp_bit;//bits�ĺ�һλ��Ҫ��������
	char ch_integer[5] = { '\0' };
	char ch_decimals[3] = { '\0' };
	char str[12] = { '\0' };

	//���Ϊ����ֵС��1�ĸ���
	if (flt > -1.0 && flt < 0.0)
	{
		strcat(str, "-");//��������
	}
	integer = (int)flt;
	itoa(integer, ch_integer, 10);
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
	setcolor(color);
	outtextxy(x, y, str);

}

/*********************************************
FUNCTION:get_viceborder
DESCRIPTION��Ѱ�һ���ͼ�ı߽纯��
INPUT:vice,max,min
RETURN:��
***********************************************/
void get_viceborder(DOWNLINE* vice, float* max, float* min)
{
	int i;
	*max = vice->first[0];
	*min = vice->first[0];
	for (i = 0; i < 90; i++)
	{
		if (vice->first[i] > * max)
		{
			*max = vice->first[i];
		}
		if (vice->first[i] < *min)
		{
			*min = vice->first[i];
		}
		if (vice->second[i] > * max)
		{
			*max = vice->second[i];
		}
		if (vice->second[i] < *min)
		{
			*min = vice->second[i];
		}
		if (vice->third[i] > * max)
		{
			*max = vice->third[i];
		}
		if (vice->third[i] < *min)
		{
			*min = vice->third[i];
		}
	}
}

/*********************************************
FUNCTION:get_border
DESCRIPTION��Ѱ�һ���ͼ�ı߽纯��
INPUT:info,max,min,read_days
RETURN:��
***********************************************/
void get_border(STODAYFLOAT* info, float* max, float* min, int read_days)
{
	int i, j;
	float MA5 = 0.0;//MA5ƽ��
	float MA10 = 0.0;//MA10ƽ��
	float MA20 = 0.0;//MA20ƽ��(�������й�)
	float MA60 = 0.0;//MA60ƽ��
	float std_dev = 0.0;//��׼��
	float BOLL_toprail = 0.0;//�������Ϲ�
	float BOLL_bottomrail = 0.0;//�������¹�
	float ENE_top = 0.0;//ENE�Ϲ�
	float ENE_bottom = 0.0;//ENE�¹�
	//float ENE = 0.0;//ENE�й�

	*max = info[0].High;
	*min = info[0].Low;
	for (i = 0; i < read_days - 60; i++)//i+j����Խ��,j��ൽ��ʮ 
	{
		MA5 = 0.0;
		MA10 = 0.0;
		MA20 = 0.0;
		MA60 = 0.0;
		if (info[i].High > * max)
		{
			*max = info[i].High;//Ѱ��������߼���Ϊ�ϱ߽�
		}
		if (info[i].Low < *min)
		{
			*min = info[i].Low;//Ѱ����С����ͼ���Ϊ�±߽�
		}

		for (j = 0; j < 5; j++)
		{
			MA5 += info[i + j].Close;
		}
		MA5 /= 5.0;//�������վ���
		if (MA5 > * max)
		{
			*max = MA5;//���վ��ߴ�����߼ۣ�Ϊ�ϱ߽�
		}
		if (MA5 < *min)
		{
			*min = MA5;//���վ���С����ͼۣ�Ϊ�±߽�
		}

		for (j = 0; j < 10; j++)
		{
			MA10 += info[i + j].Close;
		}
		MA10 /= 10.0;//����ʮ�վ���
		if (MA10 > * max)
		{
			*max = MA10;//ʮ�վ������Ϊ�ϱ߽�
		}
		if (MA10 < *min)
		{
			*min = MA10;//ʮ�վ�����С��Ϊ�±߽�
		}

		for (j = 0; j < 20; j++)
		{
			MA20 += info[i + j].Close;
		}
		MA20 /= 20.0;//�����ʮ�վ���
		if (MA20 > * max)
		{
			*max = MA20;//��ʮ�վ������Ϊ�ϱ߽�
		}
		if (MA20 < *min)
		{
			*min = MA20;//��ʮ�վ�����С��Ϊ�±߽�
		}

		for (j = 0; j < 60; j++)
		{
			MA60 += info[i + j].Close;
		}
		MA60 /= 60.0;//������ʮ�վ���
		if (MA60 > * max)
		{
			*max = MA60;//��ʮ�վ������Ϊ�ϱ߽�
		}
		if (MA60 < *min)
		{
			*min = MA60;//��ʮ�վ�����С��Ϊ�±߽�
		}

		std_dev = std_deviation(info, 20, i);//�����i�տ�ʼ20���ڵķ���
		//�й���=N�յ��ƶ�ƽ���ߣ���������ָ��Nһ��Ϊ20

		BOLL_toprail = MA20 + 2 * std_dev;//�Ϲ��ߣ�up�ߣ�=�й���+�����ı�׼�2SD��
		BOLL_bottomrail = MA20 - 2 * std_dev;//�¹��ߣ�down�ߣ�=�й���-�����ı�׼�2SD��

		if (BOLL_toprail > * max)
		{
			*max = BOLL_toprail;//�������Ϲ����Ϊ�ϱ߽�
		}
		if (BOLL_bottomrail < *min)
		{
			*min = BOLL_bottomrail;//�������¹����Ϊ�±߽�
		}
		/*M1�����й��׼�ߵ��ϸ��ٷֱȣ�һ����Ϊ11����11%����
		M2�����й��׼�ߵ��µ��ٷֱȣ�һ����Ϊ9����9%����
		N��ƽ��һ��ȡʮ�վ���*/
		ENE_top = (1 + 11 / 100.0) * MA10;		//ENE�Ϲ�=(1+M1/100)*���̼۵�N�ռ��ƶ�ƽ��
		ENE_bottom = (1 - 9 / 100.0) * MA10;	//ENE�¹�=(1-M2/100)*���̼۵�N�ռ��ƶ�ƽ��
		//ENE = (ENE_top + ENE_bottom) / 2.0;	//ENE�й�=(ENE�Ϲ�+ENE�¹�)/2
		if (ENE_top > * max)
		{
			*max = ENE_top;//������Ϲ����Ϊ�ϱ߽�
		}
		if (ENE_bottom < *min)
		{
			*min = ENE_bottom;//������¹����Ϊ�±߽�
		}
	}
}

/*********************************************
FUNCTION:std_deviation
DESCRIPTION�������׼��,daysΪ20.0
INPUT:info,days,date
RETURN:��
***********************************************/
float std_deviation(STODAYFLOAT* info, int days, int date)
{
	int i;
	float aver = 0.0;//20��ƽ��ֵ
	float variance = 0.0;//����
	float std_dev = 0.0;//��׼��
	for (i = 0; i < days; i++)
	{
		aver += info[date + i].Close;
	}
	aver /= days * 1.0;//�����ֵ
	for (i = 0; i < days; i++)
	{
		variance += (info[date + i].Close - aver) * (info[date + i].Close - aver);
	}
	variance /= days * 1.0;//���㷽��
	std_dev = sqrt(variance);//�����׼��

	return std_dev;
}