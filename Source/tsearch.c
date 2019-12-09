#include"public.h"
#include"database.h"
#include"tsearch.h"
#include"storead.h"
#include"tcalcu.h"

/*****************************************
tsearch.c
COPYRIGHT:	weijingmin
FUNCTION:	control function for search
ABSTRACT:
		A.abstract information to pinfo
		B.allocation
		C.judge and search
DATE:2019/10/26
******************************************/

/*********************************************
FUNCTION:T_search
DESCRIPTION��������ѡ����������
INPUT:opt[][6],sto_list,progress_color
RETURN:��
***********************************************/
void T_search(int opt[][6], int* sto_list, int progress_color)
{
	PRICEINFO* pinfo;//90��۸���Ϣ��ָ�룬��Ϊһ���м������ÿ��������ȫ������
	int i;
	int cnt = 0;//�ҵ��˷��������Ķ���֧��Ʊ�����α���
	/*for (i = 0; i < 200; i++)
	{
		sto_list[i] = 0;
	}*/
	memset(sto_list, 0, 200*sizeof(int));
	if ((pinfo = (PRICEINFO*)malloc(sizeof(PRICEINFO))) == 0)
	{
		printf("memoryallocation runs wrong in tsearch.c");
		delay(3000);
		exit(1);
	}
	memset(pinfo, 0, sizeof(PRICEINFO));//��ʼ���ṹ����Ϣ
	setlinestyle(SOLID_LINE, 0, 1);
	setcolor(WHITE);
	rectangle(320, 462, 524, 479);
	setfillstyle(SOLID_FILL, LIGHTGRAY);
	bar(322, 464, 522, 477);
	for (i = 0; i < 200; i++)
	{
		sto_90days2float(pinfo, i + 1);//ѭ����ȡ200֧��Ʊ��90�����ݣ���д��pinfo
		if (techsearch(opt, pinfo) == 1)
		{
			//printf("find");//����
			sto_list[cnt] = i + 1;
			cnt++;
		}
		else
		{
			//printf("not find");//����
		}
		memset(pinfo, 0, sizeof(PRICEINFO));
		refresh_progress(i, progress_color);
	}
	if (pinfo != NULL)
	{
		free(pinfo);
		pinfo = NULL;
	}
}

/*********************************************
FUNCTION:refresh_progress
DESCRIPTION�����½�����
INPUT:progress,color
RETURN:��
***********************************************/
void refresh_progress(int progress,int color)
{
	setfillstyle(SOLID_FILL, color);
	bar(322, 464, 322 + progress, 477);
}

/*********************************************
FUNCTION:sto_90days2float
DESCRIPTION����ȡһֻ��Ʊ
	90���Open,Close,High,Low,VOL��Ϣ
INPUT:pinfo,sto_num
RETURN:��
***********************************************/
void sto_90days2float(PRICEINFO* pinfo, int sto_num)
{
	int i;
	STODAYFLOAT info[90];//��market�Ĳ�������
	memset(info, 0, 90 * sizeof(STODAYFLOAT));
	sto_daybyday2float(sto_num, 1, 90, info);//��ȡ90����Ϣ��д��info
	for (i = 0; i < 90; i++)
	{
		pinfo->Open[i] = info[i].Open;
		pinfo->Close[i] = info[i].Close;
		pinfo->High[i] = info[i].High;
		pinfo->Low[i] = info[i].Low;
		pinfo->VOL[i] = info[i].VOL;//���۸�ṹ��ֵ
	}
}


/*********************************************
FUNCTION:techsearch
DESCRIPTION������������
INPUT:opt[][6],pinfo
RETURN:0/1
***********************************************/
int techsearch(int opt[][6], PRICEINFO* pinfo)
{
	//����K��
	if (opt[0][0] == 1)//һ����ͣ��
	{
		if (K_onelimitup(pinfo) == 0)//������
		{
			return 0;
		}
	}
	else if (opt[0][1] == 1)//����Ӱ��
	{
		if (K_longhatch(pinfo) == 0)
		{
			return 0;
		}
	}
	else if (opt[0][2] == 1)//������
	{
		if (K_greatredline(pinfo) == 0)
		{
			return 0;
		}
	}


	//˫��K��
	if (opt[1][0] == 1)//�෽ѹ��
	{
		if (K2_manysuppress(pinfo) == 0)
		{
			return 0;
		}
	}
	else if (opt[1][1] == 1)//�շ�ѹ��
	{
		if (K2_emptysuppress(pinfo) == 0)
		{
			return 0;
		}
	}
	else if (opt[1][2] == 1)//����ͣ��
	{
		if (K2_trendpause(pinfo) == 0)
		{
			return 0;
		}
	}


	//����K��
	if (opt[2][0] == 1)//������
	{
		if (K3_tribleredline(pinfo) == 0)
		{
			return 0;
		}
	}
	else if (opt[2][1] == 1)//������
	{
		if (K3_triblegreenline(pinfo) == 0)
		{
			return 0;
		}
	}
	else if (opt[2][2] == 1)//���η�ת
	{
		if (K3_islandreverse(pinfo) == 0)
		{
			return 0;
		}
	}


	//���K��
	if (opt[3][0] == 1)//��ˮܽ��
	{
		if (KN_bathbeauty(pinfo) == 0)
		{
			return 0;
		}
	}
	else if (opt[3][1] == 1)//��ͷա��
	{
		if (KN_fodderchoppor(pinfo) == 0)
		{
			return 0;
		}
	}


	//MA��̬ѡ��
	if (opt[4][0] == 1)//��ͷ����
	{
		if (MA_manyarray(pinfo->Close) == 0)
		{
			return 0;
		}
	}
	else if (opt[4][1] == 1)//��ͷ����
	{
		if (MA_emptyarray(pinfo->Close) == 0)
		{
			return 0;
		}
	}
	else if (opt[4][2] == 1)//ճ��
	{
		if (MA_bond(pinfo->Close) == 0)
		{
			return 0;
		}
	}
	else if (opt[4][3] == 1)//��ɢ
	{
		if (MA_divergence(pinfo->Close) == 0)
		{
			return 0;
		}
	}
	else if (opt[4][4] == 1)//��ͷ����
	{
		if (MA_turnup(pinfo->Close) == 0)
		{
			return 0;
		}
	}
	else if (opt[4][5] == 1)//��ͷ����
	{
		if (MA_turndown(pinfo->Close) == 0)
		{
			return 0;
		}
	}



	//���ָ��KDJ
	if (opt[5][0] == 1)//KD���
	{
		if (KDJ_goldencross(pinfo) == 0)
		{
			return 0;
		}
	}
	else if (opt[5][1] == 1)//J����
	{
		if (KDJ_overbuy(pinfo) == 0)
		{
			return 0;
		}
	}
	else if (opt[5][2] == 1)//KD����
	{
		if (KDJ_deadcross(pinfo) == 0)
		{
			return 0;
		}
	}
	else if (opt[5][3] == 1)//J����
	{
		if (KDJ_oversell(pinfo) == 0)
		{
			return 0;
		}
	}


	//��ͬ�ƶ�ƽ����MACD
	if (opt[6][0] == 1)//������
	{
		if (MACD_updevide(pinfo) == 0)
		{
			return 0;
		}
	}
	else if (opt[6][1] == 1)//���
	{
		if (MACD_goldencross(pinfo) == 0)
		{
			return 0;
		}
	}
	else if (opt[6][2] == 1)//�ױ���
	{
		if (MACD_downdevide(pinfo) == 0)
		{
			return 0;
		}
	}
	else if (opt[6][3] == 1)//����
	{
		if (MACD_deadcross(pinfo) == 0)
		{
			return 0;
		}
	}


	//���ǿ��ָ��RSI
	if (opt[7][0] == 1)//����(>80)
	{
		if (RSI_overbuy(pinfo) == 0)
		{
			return 0;
		}
	}
	else if (opt[7][1] == 1)//����(<80)
	{
		if (RSI_oversell(pinfo) == 0)
		{
			return 0;
		}
	}


	//�ɽ���/������ VOL/OBV
	if (opt[8][0] == 1)//��������
	{
		if (VOLOBV_trendup(pinfo) == 0)
		{
			return 0;
		}
	}
	else if (opt[8][1] == 1)//�µ�����
	{
		if (VOLOBV_trenddown(pinfo) == 0)
		{
			return 0;
		}
	}


	//������BIAS
	if (opt[9][0] == 1)//����(>16%)
	{
		if (BIAS_overbuy(pinfo) == 0)
		{
			return 0;
		}
	}
	else if (opt[9][1] == 1)//����(<-16%)
	{
		if (BIAS_oversell(pinfo) == 0)
		{
			return 0;
		}
	}


	//���ִ�BOLL
	if (opt[10][0] == 1)//ͻ���Ϲ�
	{
		if (BOLL_breaktoprail(pinfo) == 0)
		{
			return 0;
		}
	}
	else if (opt[10][1] == 1)//ͻ���¹�
	{
		if (BOLL_breakmediumrail(pinfo) == 0)
		{
			return 0;
		}
	}
	else if (opt[10][2] == 1)//ͻ���й�
	{
		if (BOLL_breakbottomrail(pinfo) == 0)
		{
			return 0;
		}
	}

	return 1;//�ߵ���һ����ʾ���ѡ����ѡ���һЩ����ָ�궼���㣬��ù�ƱΪ��ѡ��
}