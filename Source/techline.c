#include"public.h"
#include"marketfc.h"
#include"techline.h"

/*****************************************
techline.c
COPYRIGHT:	weijingmin
FUNCTION:	draw techline
ABSTRACT:
		A.control the tech index
		B.draw techline
DATE:2019/10/14
******************************************/


/*********************************************
FUNCTION:majorinfo_show
DESCRIPTION����ʾ��ͼ��Ϣ���ܿغ���
INPUT:kind,info,major,max,min
RETURN:��
***********************************************/
void majorinfo_show (int kind, STODAYFLOAT* info, UPLINE* major,float max,float min)
{
	switch (kind)
	{
	case 1:
		Kline_draw(info, max, min);
		MA_draw(info, major, max, min);
		break;
	case 2:
		Kline_draw(info, max, min);
		BOLL_draw(info, major, max, min);
		break;
	case 3:
		Kline_draw(info,max,min);
		ENE_draw(info, major, max, min);
		break;
	}
}


/*********************************************
FUNCTION:viceinfo_show
INPUT����ʾ��ͼ��Ϣ���ܿغ���
DATA FLOW:kind,info,vice
RETURN:��
***********************************************/
void viceinfo_show(int kind, STODAYFLOAT* info, DOWNLINE* vice)
{
	switch (kind)
	{
	case 1:
		BIAS_draw(info, vice);
		break;
	case 2:
		BRAR_draw(info, vice);
		break;
	case 3:
		CR_draw(info, vice);
		break;
	case 4:
		DMA_draw(info, vice);
		break;
	case 5:
		OBV_draw(info, vice);
		break;
	case 6:
		KDJ_draw(info, vice);
		break;
	case 7:
		MACD_draw(info, vice);
		break;
	case 8:
		RSI_draw(info, vice);
		break;
	case 9:
		VOL_draw(info, vice);
	}
}

/*********************************************
FUNCTION:Kline_draw
DESCRIPTION����K��,max,minΪget_border����ı߽�
INPUT:info,max,min
RETURN:��
***********************************************/
void Kline_draw(STODAYFLOAT* info, float max, float min)
{
	int i;
	float rise_fall = 0.0;//�ж��ǵ�
	int top = 0;//��Ӱ����ߴ�
	int bottom = 0;//��Ӱ����ʹ�
	int high = 0;//K�߳����ε��ϱ�������
	int low = 0;//K�߳����ε��±�������
	for (i = 0; i < 90; i++)
	{
		rise_fall = info[i].Close - info[i].Open;//�ǵ�����
		if (rise_fall >= 1e-6)//��Ʊ��ʱ
		{
			setcolor(RED);
			setlinestyle(SOLID_LINE, 0, 1);
			high = 342 - (int)((info[i].Close - min) * 270 / (max - min));//�������Ŵ���С
			low = 342 - (int)((info[i].Open - min) * 270 / (max - min));
			top = 342 - (int)((info[i].High - min) * 270 / (max - min));
			bottom = 342 - (int)((info[i].Low - min) * 270 / (max - min));
			rectangle(619 - 6 * i, high, 615 - 6 * i, low);//��K��ʵ�岿��
			line(617 - 6 * i, high, 617 - 6 * i, top);//����Ӱ��
			line(617 - 6 * i, low, 617 - 6 * i, bottom);//����Ӱ��
		}
		else if (rise_fall < 1e-6)//��Ʊ��ʱ
		{
			setcolor(LIGHTCYAN);
			setlinestyle(SOLID_LINE, 0, 1);
			setfillstyle(SOLID_FILL, LIGHTCYAN);
			high = 342 - (int)((info[i].Open - min) * 270 / (max - min));
			low = 342 - (int)((info[i].Close - min) * 270 / (max - min));
			top = 342 - (int)((info[i].High - min) * 270 / (max - min));
			bottom = 342 - (int)((info[i].Low - min) * 270 / (max - min));
			bar(619 - 6 * i, high, 615 - 6 * i, low);//��K��ʵ�岿��
			line(617 - 6 * i, bottom, 617 - 6 * i, top);//������Ӱ��
		}
	}
}

/*********************************************
FUNCTION:MA_draw
DESCRIPTION������MA�ߣ�majorΪ�����ͼ������Ϣ�Ľṹ��ָ��
INPUT:info,major,max,min
RETURN:��
***********************************************/
void MA_draw(STODAYFLOAT* info, UPLINE* major, float max, float min)
{
	int i, j;
	for (i = 0; i < 90; i++)
	{
		major->first[i] = 0.0;
		major->second[i] = 0.0;
		major->third[i] = 0.0;
		major->forth[i] = 0.0;
	}
	for (i = 0; i < 90; i++)
	{
		for (j = 0; j < 5; j++)
		{
			major->first[i] += info[i + j].Close;
		}
		major->first[i] /= 5.0;//�������վ�ֵ
		for (j = 0; j < 10; j++)
		{
			major->second[i] += info[i + j].Close;
		}
		major->second[i] /= 10.0;//����ʮ�վ�ֵ
		for (j = 0; j < 20; j++)
		{
			major->third[i] += info[i + j].Close;
		}
		major->third[i] /= 20.0;//�����ʮ�վ�ֵ
		for (j = 0; j < 60; j++)
		{
			major->forth[i] += info[i + j].Close;
		}
		major->forth[i] /= 60.0;//������ʮ�վ�ֵ
	}

	setlinestyle(SOLID_LINE, 0, 1);
	for (i = 1; i < 90; i++)
	{
		//(MA-min)/(342-y)=(max-min)/270
		setcolor(WHITE);
		line(625 - 6 * i, 341 - (int)((major->first[i - 1] - min) * 260 / (max - min)), 619 - 6 * i, 341 - (int)((major->first[i] - min) * 260 / (max - min)));//����5�վ���
		setcolor(YELLOW);
		line(625 - 6 * i, 341 - (int)((major->second[i - 1] - min) * 260 / (max - min)), 619 - 6 * i, 341 - (int)((major->second[i] - min) * 260 / (max - min)));//����10�վ���
		setcolor(LIGHTMAGENTA);
		line(625 - 6 * i, 341 - (int)((major->third[i - 1] - min) * 260 / (max - min)), 619 - 6 * i, 341 - (int)((major->third[i] - min) * 260 / (max - min)));//����20�վ���
		setcolor(GREEN);
		line(625 - 6 * i, 341 - (int)((major->forth[i - 1] - min) * 260 / (max - min)), 619 - 6 * i, 341 - (int)((major->forth[i] - min) * 260 / (max - min)));//����60�վ���
	}
	settextjustify(LEFT_TEXT, TOP_TEXT);
	settextstyle(2, HORIZ_DIR, 4);
	setcolor(WHITE);
	outtextxy(82, 72, "M5:");
	setcolor(YELLOW);
	outtextxy(172, 72, "M10:");
	setcolor(LIGHTMAGENTA);
	outtextxy(262, 72, "M20:");
	setcolor(GREEN);
	outtextxy(352, 72, "M60:");

}

/*********************************************
FUNCTION:BOLL_draw
DESCRIPTION������BOLL������ָ��
INPUT:info,major,max,min
RETURN:��
***********************************************/
void BOLL_draw(STODAYFLOAT* info, UPLINE* major, float max, float min)
{
	int i,j;
	float std_dev = 0.0;
	for (i = 0; i < 90; i++)
	{
		major->first[i] = 0.0;
		major->second[i] = 0.0;
		major->third[i] = 0.0;
	}
	for (i = 0; i < 90; i++)
	{
		for (j = 0; j < 20; j++)
		{
			major->second[i] += info[i + j].Close;
		}
		major->second[i] /= 20.0;//�й���=N�յ��ƶ�ƽ���ߣ���������ָ��Nһ��Ϊ20
		std_dev = std_deviation(info, 20, i);//�����i�տ�ʼ20���ڵķ���
		major->first[i] = major->second[i] + 2 * std_dev;//�Ϲ��ߣ�up�ߣ�=�й���+�����ı�׼�2SD��
		major->third[i] = major->second[i] - 2 * std_dev;//�¹��ߣ�down�ߣ�=�й���-�����ı�׼�2SD��
	}

	setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
	for (i = 1; i < 90; i++)
	{
		setcolor(WHITE);
		line(625 - 6 * i, 341 - (int)((major->first[i - 1] - min) * 260 / (max - min)), 619 - 6 * i, 341 - (int)((major->first[i] - min) * 260 / (max - min)));//���Ʋ������Ϲ�
		setcolor(YELLOW);
		line(625 - 6 * i, 341 - (int)((major->second[i - 1] - min) * 260 / (max - min)), 619 - 6 * i, 341 - (int)((major->second[i] - min) * 260 / (max - min)));//���Ʋ������й�
		setcolor(LIGHTMAGENTA);
		line(625 - 6 * i, 341 - (int)((major->third[i - 1] - min) * 260 / (max - min)), 619 - 6 * i, 341 - (int)((major->third[i] - min) * 260 / (max - min)));//���Ʋ������¹�
	}
	settextjustify(LEFT_TEXT, TOP_TEXT);
	settextstyle(2, HORIZ_DIR, 4);
	setcolor(WHITE);
	outtextxy(82, 72, "UP:");
	setcolor(YELLOW);
	outtextxy(172, 72, "MB:");
	setcolor(LIGHTMAGENTA);
	outtextxy(262, 72, "DN:");
}

/*********************************************
FUNCTION:ENE_draw
DESCRIPTION������ENE�����ָ��
INPUT:info,major,max,min
RETURN:��
***********************************************/
void ENE_draw(STODAYFLOAT* info, UPLINE* major, float max, float min)
{
	int i, j;
	float MA10 = 0.0;
	for (i = 0; i < 90; i++)
	{
		major->first[i] = 0.0;
		major->second[i] = 0.0;
		major->third[i] = 0.0;
	}
	for (i = 0; i < 90; i++)
	{
		MA10 = 0.0;
		for (j = 0; j < 10; j++)
		{
			MA10 += info[i + j].Close;
		}
		MA10 /= 10.0;
		major->first[i] = (1 + 11.0 / 100.0) * MA10;	//ENE�Ϲ�=(1+M1/100)*���̼۵�N�ռ��ƶ�ƽ��
		major->third[i] = (1 - 9.0 / 100.0) * MA10;	//ENE�¹�=(1-M2/100)*���̼۵�N�ռ��ƶ�ƽ��
		major->second[i] = (major->first[i] + major->third[i]) / 2.0;	//ENE�й�=(ENE�Ϲ�+ENE�¹�)/2
	}

	setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
	for (i = 1; i < 90; i++)
	{
		setcolor(WHITE);
		line(625 - 6 * i, 341 - (int)((major->first[i - 1] - min) * 260 / (max - min)), 619 - 6 * i, 341 - (int)((major->first[i] - min) * 260 / (max - min)));//����ENE�Ϲ�
		setcolor(YELLOW);
		line(625 - 6 * i, 341 - (int)((major->second[i - 1] - min) * 260 / (max - min)), 619 - 6 * i, 341 - (int)((major->second[i] - min) * 260 / (max - min)));//����ENE�й�
		setcolor(LIGHTMAGENTA);
		line(625 - 6 * i, 341 - (int)((major->third[i - 1] - min) * 260 / (max - min)), 619 - 6 * i, 341 - (int)((major->third[i] - min) * 260 / (max - min)));//����ENE�¹�
	}
	settextjustify(LEFT_TEXT, TOP_TEXT);
	settextstyle(2, HORIZ_DIR, 4);
	setcolor(WHITE);
	outtextxy(82, 72, "UP:");
	setcolor(YELLOW);
	outtextxy(172, 72, "ENE:");
	setcolor(LIGHTMAGENTA);
	outtextxy(262, 72, "DN:");
}

/*********************************************
FUNCTION:VOL_draw
DESCRIPTION�����Ƴɽ�����״ͼ,viceΪ��Ÿ�ͼ�ɽ�����Ϣ�Ľṹ��ָ��
INPUT:info,vice
RETURN:��
***********************************************/
void VOL_draw(STODAYFLOAT* info, DOWNLINE* vice)
{
	int i, j;
	float rise_fall = 0.0;//�ǵ�
	float max = info[0].VOL;

	for (i = 0; i < 90; i++)
	{
		vice->first[i] = 0.0;
		vice->second[i] = 0.0;
		vice->third[i] = 0.0;

		if (info[i].VOL > max)
		{
			max = info[i].VOL;//�������ֵ��ȷ����ͼ���Ƶ���ߵ�
		}
	}

	for (i = 0; i < 90; i++)
	{
		rise_fall = info[i].Close - info[i].Open;
		if (rise_fall >= 1e-6)//��
		{
			setcolor(RED);
			setlinestyle(SOLID_LINE, 0, 1);
			//(456-y)/VOL=114/max
			rectangle(619 - 6 * i, 455, 615 - 6 * i, 455 - (int)(info[i].VOL * 110 / max));
		}
		else if (rise_fall < 1e-6)//��
		{
			setfillstyle(SOLID_FILL, LIGHTCYAN);
			bar(619 - 6 * i, 455, 615 - 6 * i, 455 - (int)(info[i].VOL * 110 / max));
		}
		vice->first[i] = info[i].VOL;//��ͼ���Ͻ���ʾ�ɽ���
		for (j = 0; j < 5; j++)
		{
			vice->second[i] += info[i + j].VOL;
		}
		vice->second[i] /= 5.0;//��ͼ�м���ʾ5�վ�ֵ
		for (j = 0; j < 10; j++)
		{
			vice->third[i] += info[i + j].VOL;
		}
		vice->third[i] /= 10.0;//�ұ���ʾ10�վ�ֵ
	}
	
	setlinestyle(SOLID_LINE, 0, 1);
	for (i = 1; i < 90; i++)
	{
		setcolor(YELLOW);//����5�ճɽ�������
		line(625 - 6 * i, 455 - (int)(vice->second[i - 1] * 100 / max), 619 - 6 * i, 455 - (int)(vice->second[i] * 100 / max));
		setcolor(GREEN);
		line(625 - 6 * i, 455 - (int)(vice->third[i - 1] * 100 / max), 619 - 6 * i, 455 - (int)(vice->third[i] * 100 / max));
	}
	settextjustify(LEFT_TEXT, TOP_TEXT);
	settextstyle(2, HORIZ_DIR, 4);
	setcolor(WHITE);
	outtextxy(82, 342, "VOL:");
	setcolor(YELLOW);
	outtextxy(172, 342, "M5:");
	setcolor(GREEN);
	outtextxy(262, 342, "M10:");
}

/*********************************************
FUNCTION:BIAS_draw
DESCRIPTION�����ƹ�����BIAS
INPUT:info,vice
RETURN:��
***********************************************/
void BIAS_draw(STODAYFLOAT* info, DOWNLINE* vice)//���ƹ�����BIAS
{
	int i, j;
	float MA6 = 0.0;
	float MA12 = 0.0;
	float MA24 = 0.0;
	float max = 0.0, min = 0.0;
	for (i = 0; i < 90; i++)
	{
		vice->first[i] = 0.0;
		vice->second[i] = 0.0;
		vice->third[i] = 0.0;
	}
	//������=[(�������̼�-N��ƽ����)/N��ƽ����]*100%
	//����N��һ��5��6��10��12��24��30��72����ʵ�������У�����ʹ��6�չ����ʽ�Ϊ��Ч��������Ŵ�Ϊ10�ջ�12�ա�
	for (i = 0; i < 90; i++)
	{
		MA6 = 0.0;
		MA12 = 0.0;
		MA24 = 0.0;
		for (j = 0; j < 6; j++)
		{
			MA6 += info[i + j].Close;
		}
		MA6 /= 6.0;
		vice->first[i] = 100 * (info[i].Close - MA6) / MA6;//BIAS6

		for (j = 0; j < 12; j++)
		{
			MA12 += info[i + j].Close;
		}
		MA12 /= 12.0;
		vice->second[i] = 100 * (info[i].Close - MA12) / MA12;//BIAS12

		for (j = 0; j < 24; j++)
		{
			MA24 += info[i + j].Close;
		}
		MA24 /= 24.0;
		vice->third[i] = 100 * (info[i].Close - MA24) / MA24;//BIAS24
	}
	get_viceborder(vice, &max, &min);
	setlinestyle(SOLID_LINE, 0, 1);
	for (i = 1; i < 90; i++)
	{
		setcolor(WHITE);
		line(625 - 6 * i, 455 - (int)((vice->first[i - 1] - min) * 100 / (max - min)), 619 - 6 * i, 455 - (int)((vice->first[i] - min) * 100 / (max - min)));//RSI6
		setcolor(YELLOW);
		line(625 - 6 * i, 455 - (int)((vice->second[i - 1] - min) * 100 / (max - min)), 619 - 6 * i, 455 - (int)((vice->second[i] - min) * 100 / (max - min)));//RSI12
		setcolor(LIGHTMAGENTA);
		line(625 - 6 * i, 455 - (int)((vice->third[i - 1] - min) * 100 / (max - min)), 619 - 6 * i, 455 - (int)((vice->third[i] - min) * 100 / (max - min)));//RSI24
	}
	settextjustify(LEFT_TEXT, TOP_TEXT);
	settextstyle(2, HORIZ_DIR, 4);
	setcolor(WHITE);
	outtextxy(82, 342, "BIAS6:");
	setcolor(YELLOW);
	outtextxy(172, 342, "BIAS12:");
	setcolor(LIGHTMAGENTA);
	outtextxy(262, 342, "BIAS24:");
}

/*********************************************
FUNCTION:BRAR_draw
DESCRIPTION������������Ըָ��BRAR
INPUT:info,vice
RETURN:��
***********************************************/
void BRAR_draw(STODAYFLOAT* info, DOWNLINE* vice)//����������Ըָ��BRAR
{
	int i, j;
	float H_O = 0.0, O_L = 0.0;
	float H_CY = 0.0, CY_L = 0.0;
	float max = 0.0, min = 0.0;
	for (i = 0; i < 90; i++)
	{
		vice->first[i] = 0.0;
		vice->second[i] = 0.0;
		vice->third[i] = 0.0;
	}
	for (i = 0; i < 90; i++)
	{
		H_O = 0.0;
		O_L = 0.0;
		for (j = 0; j < 26; j++)
		{
			H_O += info[i + j].High - info[i + j].Low;
			O_L += info[i + j].Open - info[i + j].Low;
		}
		vice->first[i] = 100 * (H_O / O_L);
		/*N��AR=(N���ڣ�H��O��֮�ͳ���N���ڣ�O��L��֮��)*100�����У�HΪ������߼ۣ�LΪ������ͼۣ�OΪ���տ��̼ۣ�NΪ�趨��ʱ�������һ��ԭʼ�������趨Ϊ26��*/
	}
	for (i = 0; i < 90; i++)
	{
		H_CY = 0.0;
		CY_L = 0.0;
		for (j = 0; j < 26; j++)
		{
			H_CY += info[i + j].High - info[i + j + 1].Close;
			CY_L += info[i + j + 1].Close - info[i + j].Low;
		}
		vice->second[i] = 100 * (H_CY / CY_L);
		/*N��BR=N���ڣ�H��CY��֮�ͳ���N���ڣ�CY��L��֮��*100�����У�HΪ������߼ۣ�LΪ������ͼۣ�CYΪǰһ�����յ����̼ۣ�NΪ�趨��ʱ�������һ��ԭʼ�������趨Ϊ26�ա�*/
	}
	get_viceborder(vice, &max, &min);
	setlinestyle(SOLID_LINE, 0, 1);
	for (i = 1; i < 90; i++)
	{
		setcolor(WHITE);
		line(625 - 6 * i, 455 - (int)((vice->first[i - 1] - min) * 100 / (max - min)), 619 - 6 * i, 455 - (int)((vice->first[i] - min) * 100 / (max - min)));//AR
		setcolor(YELLOW);
		line(625 - 6 * i, 455 - (int)((vice->second[i - 1] - min) * 100 / (max - min)), 619 - 6 * i, 455 - (int)((vice->second[i] - min) * 100 / (max - min)));//BR
	}
	settextjustify(LEFT_TEXT, TOP_TEXT);
	settextstyle(2, HORIZ_DIR, 4);
	setcolor(WHITE);
	outtextxy(82, 342, "AR:");
	setcolor(YELLOW);
	outtextxy(172, 342, "BR:");
}

/*********************************************
FUNCTION:CR_draw
DESCRIPTION����������ָ��CR
INPUT:info,vice
RETURN:��
***********************************************/
void CR_draw(STODAYFLOAT* info, DOWNLINE* vice)//��������ָ��CR
{
	int i, j;
	float P1 = 0.0, P2 = 0.0;
	float YM = 0.0;
	float max=0.0, min=0.0;
	for (i = 0; i < 90; i++)
	{
		vice->first[i] = 0.0;
		vice->second[i] = 0.0;
		vice->third[i] = 0.0;
	}
	for (i = 0; i < 110; i++)
	{
		P1 = 0.0;
		P2 = 0.0;
		for (j = 0; j < 26; j++)
		{
			YM = (info[i + j + 1].Close + info[i + j + 1].Open + info[i + j + 1].Low + info[i + j + 1].High) / 4.0;
			/*�м��YMͨ�������գ�YM�����׵���߼ۡ���ͼۡ����̼ۺ����̼۽��м�Ȩƽ�����õ���,��Ȩ��ʽ�����֣�
			1��M = ��2C + H + L����4
			2��M = ��C + H + L + O����4
			3��M = ��C + H + L����3
			4��M = ��H + L����2�����ȡ�ڶ��ּ�Ȩ��ʽ*/
			P1 += info[i + j].High - YM;
			P2 += YM - info[i + j].Low;
		}
		vice->first[i] = 100 * P1 / P2;//CR��N�գ�=P1��P2��100��ʽ�У�P1=����H��YM������ʾN�������෽�������ܺͣ�P2=����YM��L������ʾN�������շ��������ܺ͡�
	}
	for (i = 0; i < 90; i++)
	{
		for (j = 0; j < 10; j++)
		{
			vice->second[i] += vice->first[i + j];
		}
		vice->second[i] /= 10.0;//CRʮ�վ���
	}
	for (i = 0; i < 90; i++)
	{	
		for (j = 0; j < 20; j++)
		{
			vice->third[i] += vice->first[i + j];
		}
		vice->third[i] /= 20.0;//CR��ʮ�վ���
	}
	get_viceborder(vice, &max, &min);
	setlinestyle(SOLID_LINE, 0, 1);
	for (i = 1; i < 90; i++)
	{
		setcolor(WHITE);
		line(625 - 6 * i, 455 - (int)((vice->first[i - 1] - min) * 100 / (max - min)), 619 - 6 * i, 455 - (int)((vice->first[i] - min) * 100 / (max - min)));//RSI6
		setcolor(YELLOW);
		line(625 - 6 * i, 455 - (int)((vice->second[i - 1] - min) * 100 / (max - min)), 619 - 6 * i, 455 - (int)((vice->second[i] - min) * 100 / (max - min)));//RSI12
		setcolor(LIGHTMAGENTA);
		line(625 - 6 * i, 455 - (int)((vice->third[i - 1] - min) * 100 / (max - min)), 619 - 6 * i, 455 - (int)((vice->third[i] - min) * 100 / (max - min)));//RSI24
	}
	settextjustify(LEFT_TEXT, TOP_TEXT);
	settextstyle(2, HORIZ_DIR, 4);
	setcolor(WHITE);
	outtextxy(82, 342, "CR:");
	setcolor(YELLOW);
	outtextxy(172, 342, "MA10:");
	setcolor(LIGHTMAGENTA);
	outtextxy(262, 342, "MA20:");
}

/*********************************************
FUNCTION:DMA_draw
DESCRIPTION������ƽ���߲�DMA
INPUT:info,vice
RETURN:��
***********************************************/
void DMA_draw(STODAYFLOAT* info, DOWNLINE* vice)//����ƽ���߲�DMA
{
	int i, j;
	float max = 0.0, min = 0.0;
	float short_arv = 0.0, long_arv = 0.0;
	for (i = 0; i < 90; i++)
	{
		vice->first[i] = 0.0;
		vice->second[i] = 0.0;
		vice->third[i] = 0.0;
	}
	for (i = 0; i < 100; i++)
	{
		short_arv = 0.0;
		long_arv = 0.0;
		for (j = 0; j < 10; j++)
		{
			short_arv += info[i + j].Close;
		}
		short_arv /= 10.0;
		for (j = 0; j < 50; j++)
		{
			long_arv += info[i + j].Close;
		}
		long_arv /= 50.0;
		vice->first[i] = short_arv - long_arv;//DMA��10��=10�չɼ�ƽ��ֵ��50�չɼ�ƽ��ֵ
	}
	for (i = 0; i < 90; i++)
	{
		for (j = 0; j < 10; j++)
		{
			vice->second[i] += vice->first[i + j];//AMA��10��=10��DMAƽ��ֵ
		}
		vice->second[i] /= 10.0;
	}
	get_viceborder(vice, &max, &min);
	setlinestyle(SOLID_LINE, 0, 1);
	for (i = 1; i < 90; i++)
	{
		setcolor(WHITE);
		line(625 - 6 * i, 455 - (int)((vice->first[i - 1] - min) * 100 / (max - min)), 619 - 6 * i, 455 - (int)((vice->first[i] - min) * 100 / (max - min)));//RSI6
		setcolor(YELLOW);
		line(625 - 6 * i, 455 - (int)((vice->second[i - 1] - min) * 100 / (max - min)), 619 - 6 * i, 455 - (int)((vice->second[i] - min) * 100 / (max - min)));//RSI12
	}
	settextjustify(LEFT_TEXT, TOP_TEXT);
	settextstyle(2, HORIZ_DIR, 4);
	setcolor(WHITE);
	outtextxy(82, 342, "DMA:");
	setcolor(YELLOW);
	outtextxy(172, 342, "AMA:");
}


/*********************************************
FUNCTION:OBV_draw
DESCRIPTION������������OBV
INPUT:info,vice
RETURN:��
***********************************************/
void OBV_draw(STODAYFLOAT* info, DOWNLINE* vice)//����������OBV
{
	int i;
	float OBV = 0.0;
	float max = 0.0, min = 0.0;
	for (i = 0; i < 90; i++)
	{
		vice->first[i] = 0.0;
		vice->second[i] = 0.0;
		vice->third[i] = 0.0;
	}
	/*��ĳ��Ϊ���ڣ������ۼ�ÿ�����й�Ʊ�ܳɽ�����������ָ�����Ʊ���ǣ������OBV���ϱ��ճɽ���Ϊ����OBV������ָ�����Ʊ�µ��������OBV��ȥ���ճɽ���Ϊ����OBV��һ����˵��ֻ�ǹ۲�OBV���������޶�����壬�������K��ͼ�����Ʋ���ʵ�ʵ�Ч�á�*/
	for (i = 0; i < 90; i++)
	{
		if (info[i + 1].Close - info[i].Close >= 0)//�µ�
		{
			OBV += info[i].VOL;
		}
		else if (info[i + 1].Close - info[i].Close < 0)
		{
			OBV -= info[i].VOL;
		}
		vice->first[i] = OBV;
	}
	get_viceborder(vice, &max, &min);
	setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
	for (i = 1; i < 90; i++)
	{
		//(OBV-min)/(max-min)=(456-y)/110
		setcolor(WHITE);
		line(625 - 6 * i, 455 - (int)((vice->first[i - 1] - min) * 100 / (max - min)), 619 - 6 * i, 455 - (int)((vice->first[i] - min) * 100 / (max - min)));//����k��
	}
	settextjustify(LEFT_TEXT, TOP_TEXT);
	settextstyle(2, HORIZ_DIR, 4);
	setcolor(WHITE);
	outtextxy(82, 342, "OBV:");
}

/*********************************************
FUNCTION:KDJ_draw
DESCRIPTION���������ָ��KDJ
INPUT:info,vice
RETURN:��
***********************************************/
void KDJ_draw(STODAYFLOAT* info, DOWNLINE* vice)
{
	int i, j;
	float RSV = 0.0, closemax, closemin;//max,minΪ9����
	float max, min;//�߽�ֵ
	float K[91];
	float D[91];
	float J[91];
	K[90] = 50.0;
	D[90] = 50.0;//����ǰһ��Kֵ��Dֵ����ɷֱ���50������
	for (i = 0; i < 90; i++)
	{
		vice->first[i] = 0.0;
		vice->second[i] = 0.0;
		vice->third[i] = 0.0;
		K[i] = 0.0;
		D[i] = 0.0;
		J[i] = 0.0;
	}
	for (i = 89; i >= 0; i--)
	{
		//n��RSV=��Cn��Ln��/��Hn��Ln����100;
		//CnΪ��n�����̼ۣ�LnΪn���ڵ���ͼۣ�HnΪn���ڵ���߼�;
		closemin = info[i].Close;
		closemax = info[i].Close;
		for (j = 0; j < 9; j++)//��9��Ϊ���ڵ�KD��
		{
			if (info[i + j].Close > closemax)
			{
				closemax = info[i + j].Close;
			}
			if (info[i + j].Close < closemin)
			{
				closemin = info[i + j].Close;
			}
		}
		RSV = 100 * (info[i].Close - closemin) / (closemax - closemin);
		K[i] = K[i + 1] * 0.67 + RSV * 0.33;//����Kֵ=2/3��ǰһ��Kֵ+1/3������RSV
		D[i] = D[i + 1] * 0.67 + K[i] * 0.33;//����Dֵ=2/3��ǰһ��Dֵ+1/3������Kֵ
		J[i] = 3 * K[i + 1] - 2 * D[i + 1];//����Jֵ=3*����Kֵ-2*����Dֵ
	}

	for (i = 0; i < 90; i++)
	{
		vice->first[i] = K[i];
		vice->second[i] = D[i];
		vice->third[i] = J[i];
	}

	get_viceborder(vice, &max, &min);
	setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
	for (i = 1; i < 90; i++)
	{
		//(KDJ-min)/(max-min)=(456-y)/110
		setcolor(LIGHTRED);
		line(625 - 6 * i, 455 - (int)((K[i - 1] - min) * 100 / (max - min)), 619 - 6 * i, 455 - (int)((K[i] - min) * 100 / (max - min)));//����k��
		setcolor(YELLOW);
		line(625 - 6 * i, 455 - (int)((D[i - 1] - min) * 100 / (max - min)), 619 - 6 * i, 455 - (int)((D[i] - min) * 100 / (max - min)));//����d��
		setcolor(LIGHTMAGENTA);
		line(625 - 6 * i, 455 - (int)((J[i - 1] - min) * 100 / (max - min)), 619 - 6 * i, 455 - (int)((J[i] - min) * 100 / (max - min)));//����j��
	}

	settextjustify(LEFT_TEXT, TOP_TEXT);
	settextstyle(2, HORIZ_DIR, 4);
	setcolor(LIGHTRED);
	outtextxy(82, 342, "K:");
	setcolor(YELLOW);
	outtextxy(172, 342, "D:");
	setcolor(LIGHTMAGENTA);
	outtextxy(262, 342, "J:");
}

/*********************************************
FUNCTION:MACD_draw
DESCRIPTION��������ͬ�ƶ�ƽ����MACD
INPUT:info,vice
RETURN:��
***********************************************/
void MACD_draw(STODAYFLOAT* info, DOWNLINE* vice)
{
	int i;
	float EMA12[91] = { 0 };
	float EMA26[91] = { 0 };//12��16���ƶ�ƽ��
	float DIF[91] = { 0 };//���ֵ
	float DEA[91] = { 0 };//���ƽ��ֵ
	float max = 0.0;
	EMA12[90] = info[90].Close;
	EMA26[90] = info[90].Close;
	for (i = 0; i < 90; i++)
	{
		vice->first[i] = 0.0;
		vice->second[i] = 0.0;
		vice->third[i] = 0.0;
	}
	for (i = 89; i >= 0; i--)
	{
		EMA12[i] = EMA12[i + 1] * 0.846 + info[i].Close * 0.154;
		//EMA��12��=ǰһ��EMA��12����11/13+�������̼ۡ�2/13	
		EMA26[i] = EMA26[i + 1] * 0.926 + info[i].Close * 0.074;
		//EMA��26��=ǰһ��EMA��26����25/27+�������̼ۡ�2/27
		DIF[i] = EMA12[i] - EMA26[i];
		//DIF=����EMA��12��������EMA��26��
		DEA[i] = DEA[i + 1] * 0.8 + DIF[i] * 0.2;
		//����DEA��MACD��=ǰһ��DEA��8/10+����DIF��2/10
	}
	for (i = 89; i > 0; i--)
	{
		vice->first[i] = EMA12[i] - EMA26[i];//DIF
		vice->second[i] = DIF[i] * 0.2 + DEA[i + 1] * 0.8;//DEA
		vice->third[i] = 2 * (DIF[i] - DEA[i]);//�ã�DIF-DEA����2��ΪMACD��״ͼ
		if (fabs(vice->first[i]) > max)
		{
			max = fabs(vice->first[i]);
		}
		if (fabs(vice->second[i]) > max)
		{
			max = fabs(vice->second[i]);
		}
		if (fabs(vice->third[i]) > max)
		{
			max = fabs(vice->third[i]);
		}
	}

	setlinestyle(SOLID_LINE, 0, 1);
	for (i = 0; i < 90; i++)
	{
		if ((vice->third[i]) >= 0)
		{
			setcolor(RED);
		}
		else if ((vice->third[i]) < 0)
		{
			setcolor(GREEN);
		}
		line(620 - 6 * i, 400, 620 - 6 * i, 400 - (int)(50 * vice->third[i] / max));//����MACD����
		
	}
	for (i = 1; i < 90; i++)
	{
		setcolor(YELLOW);
		line(625 - 6 * i, 400 - (int)(50 * vice->second[i - 1] / max), 619 - 6 * i, 400 - (int)(50 * vice->second[i] / max));//����DEA
		setcolor(WHITE);
		line(625 - 6 * i, 400 - (int)(50 * vice->first[i - 1] / max), 619 - 6 * i, 400 - (int)(50 * vice->first[i] / max));//����DIF
	}
	settextjustify(LEFT_TEXT, TOP_TEXT);
	settextstyle(2, HORIZ_DIR, 4);
	setcolor(WHITE);
	outtextxy(82, 342, "DIF:");
	setcolor(YELLOW);
	outtextxy(172, 342, "DEA:");
	setcolor(RED);
	outtextxy(262, 342, "MACD:");
}

/*********************************************
FUNCTION:RSI_draw
DESCRIPTION���������ǿ��ָ��RSI
INPUT:info,vice
RETURN:��
***********************************************/
void RSI_draw(STODAYFLOAT* info, DOWNLINE* vice)//���ǿ��ָ��RSI
{
	int i;
	float max = 0.0, min = 0.0;
	for (i = 0; i < 90; i++)
	{
		vice->first[i] = 0.0;
		vice->second[i] = 0.0;
		vice->third[i] = 0.0;
	}
	for (i = 0; i < 90; i++)
	{
		vice->first[i] = RSI_calculate(info, i, 6);
		vice->second[i] = RSI_calculate(info, i, 12);
		vice->third[i] = RSI_calculate(info, i, 24);
	}
	get_viceborder(vice, &max, &min);
	setlinestyle(SOLID_LINE, 0, 1);
	for (i = 1; i < 90; i++)
	{
		setcolor(WHITE);
		line(625 - 6 * i, 455 - (int)((vice->first[i - 1] - min) * 100 / (max - min)), 619 - 6 * i, 455 - (int)((vice->first[i] - min) * 100 / (max - min)));//RSI6
		setcolor(YELLOW);
		line(625 - 6 * i, 455 - (int)((vice->second[i - 1] - min) * 100 / (max - min)), 619 - 6 * i, 455 - (int)((vice->second[i] - min) * 100 / (max - min)));//RSI12
		setcolor(LIGHTMAGENTA);
		line(625 - 6 * i, 455 - (int)((vice->third[i - 1] - min) * 100 / (max - min)), 619 - 6 * i, 455 - (int)((vice->third[i] - min) * 100 / (max - min)));//RSI24
	}
	settextjustify(LEFT_TEXT, TOP_TEXT);
	settextstyle(2, HORIZ_DIR, 4);
	setcolor(WHITE);
	outtextxy(82, 342, "RSI6:");
	setcolor(YELLOW);
	outtextxy(172, 342, "RSI12:");
	setcolor(LIGHTMAGENTA);
	outtextxy(262, 342, "RSI24:");
}

/*********************************************
FUNCTION:RSI_calculate
DESCRIPTION������RSIRSI
INPUT:info,date,days
RETURN:��
***********************************************/
float RSI_calculate(STODAYFLOAT* info, int date, int days)//RSI��6,12,24������
{
	int i;
	float RSI=0.0;//���ǿ��ָ��RSI
	float sum_rise = 0.0;//������
	float sum_fall = 0.0;//������
	float difference;//�������̼۵Ĳ�ֵ
	for (i = 0; i < days; i++)
	{
		difference = info[date + i + 1].Close - info[date + i].Close;//ǰһ��-��һ��(���ݿ��������෴)

		if (difference >= 0)
		{
			sum_fall += difference;
		}
		else if (difference < 0)
		{
			sum_rise += (-difference);
		}
	}
	RSI = 100 * sum_rise / (sum_rise + sum_fall);
	//RS(���ǿ��)=N�������̼�������֮��ֵ��N�������̼۵�����֮��ֵ
	//RSI(���ǿ��ָ��)=100��100��(1+RS)
	return RSI;
}