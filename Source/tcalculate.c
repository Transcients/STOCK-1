#include"public.h"
#include"database.h"
#include"tcalcu.h"


/*****************************************
tcalculate.c
COPYRIGHT:	weijingmin
FUNCTION:	search technical index
ABSTRACT:
		A.1K(3),2K(3),3K(3),NK(2)
		B.MA(6)
		C.KDJ(3)
		D.MACD(4)
		E.RSI(2)
		F.VOL/OBV(2)
		G.BIAS(2)
		H.BOLL(3)
		I.caculate technical indicator
DATE:2019/10/30
******************************************/


/********************
��K��ָ�꣺3��
*********************/

/****************************************************************
FUNCTION:K_onelimitup,K_longhatch,K_greatredline
DESCRIPTION��һ����ͣ��
			����Ӱ��
			������
INPUT:pinfo
RETURN:��
****************************************************************/
int K_onelimitup(PRICEINFO* pinfo)//����K�ߡ���һ����ͣ��
{
	int i;
	//Ѱ�ҽ���ʮ������һ����ͣ��
	for (i = 0; i < 90; i++)
	{
		if (pinfo->High[i] == pinfo->Low[i])
		{
			if ((pinfo->Open[i] == pinfo->High[i]) && (pinfo->Close[i] == pinfo->Low[i]))
			{
				return 1;//�ļ����
			}
		}
	}
	return 0;
}

int K_longhatch(PRICEINFO* pinfo)//����K�ߡ�������Ӱ��
{
	int i;
	float max = 0;
	//Ѱ��7�����Ƿ���ڳ���Ӱ��
	for (i = 0; i < 7; i++)
	{
		max = pinfo->Open[i];
		if (max < pinfo->Close[i])
		{
			max = pinfo->Close[i];
		}
		if (pinfo->High[i] > max * 1.03)
		{
			return 1;//�ҵ�����Ӱ��
		}
	}

	return 0;
}

int K_greatredline(PRICEINFO* pinfo)//����K�ߡ���������
{
	int i;
	//Ѱ�ҽ�7�����Ĵ�����
	for (i = 0; i < 7; i++)
	{
		if (pinfo->Open[i] > pinfo->Close[i])//�Կ��̼���Ϊ��ͼۣ����̼���Ϊ��߼ۣ�һ·���ǣ�����δ��
		{
			if ((pinfo->Open[i] == pinfo->High[i]) && (pinfo->Close[i] == pinfo->Low[i]))
			{
				return 1;//�ҵ�
			}
		}
	}
	return 0;
}


/********************
˫K��ָ�꣺3��
*********************/

/****************************************************************
FUNCTION:K2_manysuppress,K2_emptysuppress,K2_trendpause
DESCRIPTION���෽ѹ��
			�շ�ѹ��
			����ͣ��
INPUT:pinfo
RETURN:��
****************************************************************/
int K2_manysuppress(PRICEINFO* pinfo)//˫��K�ߡ����෽ѹ��
{
	int i;
	for (i = 8; i > 0; i--)
	{
		//���ն���
		if (pinfo->Open[i] > pinfo->Close[i] && pinfo->Open[i - 1] < pinfo->Close[i - 1])
		{
			//��һ������ڶ�����
			if (pinfo->Close[i - 1] > pinfo->Open[i] && pinfo->Open[i - 1] > pinfo->Close[i])//�ڶ������̼۴��ڵ�һ�쿪�̼�,���̼۴��ڵ�һ�����̼�
			{
				return 1;
			}
		}
		//��ͷ�ƽ�
		if (pinfo->Open[i] > pinfo->Close[i] && pinfo->Open[i - 1] < pinfo->Close[i - 1])
		{
			//��һ������ڶ�����
			if (pinfo->Open[i - 1]<pinfo->Low[i] && pinfo->Close[i - 1]>pinfo->High[i])
			{
				//�ڶ�������̼۴��ڵ�һ����߼ۣ����̼۴��ڵ�һ����ͼ�
				return 1;
			}
		}
		//������
		if (pinfo->Open[i] > pinfo->Close[i] && pinfo->Open[i - 1] < pinfo->Close[i - 1])
		{
			//��һ������ڶ�����
			if (pinfo->Close[i - 1] > (pinfo->Open[i] + pinfo->Close[i]) / 2.0 && pinfo->Open[i - 1] > pinfo->Close[i])
			{
				//�ڶ������յͿ������̼��ڵ�һ��1/2֮��
				return 1;
			}
		}
		//���ѷ���
		if (pinfo->Open[i] > pinfo->Close[i] && pinfo->Open[i - 1] < pinfo->Close[i - 1])
		{
			//��һ������ڶ�����
			if (pinfo->Close[i - 1] < pinfo->Close[i])
			{
				//�ڶ������̼��ڵ�һ�����̼���
				return 1;
			}
		}
	}
	return 0;
}


int K2_emptysuppress(PRICEINFO* pinfo)//˫��K�ߡ����շ�ѹ��
{
	int i;
	for (i = 8; i > 0; i--)
	{
		//�������
		if (pinfo->Open[i] < pinfo->Close[i] && pinfo->Open[i - 1] > pinfo->Close[i - 1])
		{
			//��������������
			if (pinfo->Open[i] > pinfo->Open[i - 1])
			{
				//�ڶ������Ϳ������ɼ��������ش�����
				return 1;
			}
		}
		//��ͷ�ƽ�
		if (pinfo->Open[i] < pinfo->Close[i] && pinfo->Open[i - 1] > pinfo->Close[i - 1])
		{
			//��������������
			if (pinfo->Open[i - 1]<pinfo->High[i] && pinfo->Close[i - 1]>pinfo->Low[i])
			{
				//�ڶ������߷��򸲸ǵ�һ������
				return 1;
			}
		}
		//���ƸǶ�
		if (pinfo->Open[i] < pinfo->Close[i] && pinfo->Open[i - 1] > pinfo->Close[i - 1])
		{
			//��������������
			if (pinfo->Close[i - 1] < (pinfo->Open[i] + pinfo->Close[i]) / 2.0 && pinfo->Open[i - 1] > pinfo->Close[i])
			{
				//�ڶ������ո߿������̼��ڵ�һ��1/2֮��
				return 1;
			}
		}
		//���ѷ���
		if (pinfo->Open[i] < pinfo->Close[i] && pinfo->Open[i - 1] > pinfo->Close[i - 1])
		{
			//��������������
			if (pinfo->Close[i - 1] > pinfo->Close[i])
			{
				//�ڶ������̼��ڵ�һ�����̼���
				return 1;
			}
		}
	}
	return 0;
}

int K2_trendpause(PRICEINFO* pinfo)//˫��K�ߡ�������ͣ��
{
	int i;
	for (i = 8; i > 0; i--)
	{
		//����
		if (pinfo->High[i - 1] > pinfo->High[i] && pinfo->Low[i - 1] > pinfo->Low[i])
		{
			return 1;
		}
		//����
		if (pinfo->Low[i - 1] > pinfo->High[i] || pinfo->High[i - 1] < pinfo->Low[i])
		{
			return 1;
		}
	}
	return 0;
}


/********************
��K��ָ�꣺3��
*********************/

/**************************************************************
FUNCTION:K3_tribleredline,K3_triblegreenline,K3_islandreverse
DESCRIPTION��������
			������
			���η�ת
INPUT:pinfo
RETURN:��
****************************************************************/
int K3_tribleredline(PRICEINFO* pinfo)//����K�ߡ���������
{
	float medium1, medium2, medium3;
	medium1 = (pinfo->Open[3] + pinfo->Close[3]) / 2.0;//������
	medium2 = (pinfo->Open[2] + pinfo->Close[2]) / 2.0;//�ڶ���
	medium3 = (pinfo->Open[1] + pinfo->Close[1]) / 2.0;//��һ��
	if (medium1 < medium2 && medium2 < medium3)
	{
		return 1;
	}
	return 0;
}

int K3_triblegreenline(PRICEINFO* pinfo)//����K�ߡ���������
{
	float medium1, medium2, medium3;
	medium1 = (pinfo->Open[3] + pinfo->Close[3]) / 2.0;//������
	medium2 = (pinfo->Open[2] + pinfo->Close[2]) / 2.0;//�ڶ���
	medium3 = (pinfo->Open[1] + pinfo->Close[1]) / 2.0;//��һ��
	if (medium1 > medium2 && medium2 > medium3)
	{
		return 1;
	}
	return 0;
}

int K3_islandreverse(PRICEINFO* pinfo)//����K�ߡ������η�ת
{
	if (pinfo->Low[3] > pinfo->High[2] && pinfo->High[2] < pinfo->Low[1])
	{
		//��ʾ���Ƶ�ת�ۣ�֮����ܻ�������������̬
		return 1;
	}
	return 0;
}

/********************
��K��ָ�꣺2��
*********************/

/**************************************************************
FUNCTION:KN_bathbeauty,KN_fodderchoppor
DESCRIPTION����ˮܽ��
			��ͷա��
INPUT:pinfo
RETURN:��
****************************************************************/
int KN_bathbeauty(PRICEINFO* pinfo)//���K�ߡ�����ˮܽ��
{
	int i;
	for (i = 20; i > 0; i--)
	{
		if ((pinfo->Open[i - 1] + pinfo->Close[i - 1]) / 2.0 > (pinfo->Open[i] + pinfo->Close[i]) / 2.0)
		{
			//��ͬˮ��ʢ������һ��εض���
			continue;
		}
		else
		{
			return 0;
		}
	}
	return 1;//��Ʊ�������
}

int KN_fodderchoppor(PRICEINFO* pinfo)//���K�ߡ�����ͷա��
{
	int i;
	for (i = 20; i > 0; i--)
	{
		if ((pinfo->Open[i - 1] + pinfo->Close[i - 1]) / 2.0 < (pinfo->Open[i] + pinfo->Close[i]) / 2.0)
		{
			//��ͬա��һ��ն�϶෽������
			continue;
		}
		else
		{
			return 0;
		}
	}
	return 1;//��Ʊ������
}



/********************
����ָ�꣺6��
*********************/

/**************************************************************
FUNCTION:MA_manyarray,MA_emptyarray,MA_bond,MA_divergence,
		MA_turnup,MA_turndown
DESCRIPTION����ͷ����
			��ͷ����
			ճ��
			��ɢ
			��ͷ����
			��ͷ����
INPUT:pinfo
RETURN:��
****************************************************************/
int MA_manyarray(float* Close)//���ߡ�����ͷ����
{
	int i;
	float MA[7][4] = { 0 };//7�죬�ĸ�����ֵ
	get_7MA(MA, Close);//���7����ľ���ֵ,(MA5,MA10,MA20,MA60)
	//MA5 > MA10 > MA20 > MA60��ά��ʱ��3����Ϊ��ͷ���еĶ���
	for (i = 0; i < 3; i++)
	{
		if (MA[i][0] > MA[i][1] && MA[i][1] > MA[i][2] && MA[i][2] > MA[i][3]);
		else
		{
			return 0;
		}

		//������������
		if (i != 2)
		{
			if (MA[i][0] > MA[i + 1][0] && MA[i][1] > MA[i + 1][1]
				&& MA[i][2] > MA[i + 1][2] && MA[i][3] > MA[i + 1][3])
			{
				continue;
			}
			else
			{
				return 0;
			}
		}
	}
	return 1;
}

int MA_emptyarray(float* Close)//���ߡ�����ͷ����
{
	int i;
	float MA[7][4] = { 0 };		//7�죬�ĸ�����ֵ
	get_7MA(MA, Close);			//���7����ľ���ֵ,(MA5,MA10,MA20,MA60)
	//MA5 < MA10 < MA20 < MA60��ά��ʱ��3����Ϊ��ͷ���еĶ���
	for (i = 0; i < 3; i++)
	{
		if (MA[i][0] < MA[i][1] && MA[i][1] < MA[i][2] && MA[i][2] < MA[i][3]);
		else
		{
			return 0;
		}

		//�����½�����
		if (i != 2)
		{
			if (MA[i][0] < MA[i + 1][0] && MA[i][1] < MA[i + 1][1]
				&& MA[i][2] < MA[i + 1][2] && MA[i][3] < MA[i + 1][3]);
			else
			{
				return 0;
			}
		}
	}
	return 1;
}

int MA_bond(float* Close)//���ߡ���ճ��
{
	int i, j;
	float max, min;
	float MA[7][4] = { 0 };//7�죬�ĸ�����ֵ
	get_7MA(MA, Close);//���7����ľ���ֵ,(MA5,MA10,MA20,MA60)
	//t1Ϊ���MA,t2Ϊ��СMA,t1/t2<1.01
	for (i = 0; i < 7; i++)
	{
		min = MA[i][0];
		max = MA[i][0];
		for (j = 1; j < 4; j++)
		{
			if (MA[i][j] > max)
			{
				max = MA[i][j];
			}

			if (MA[i][j] < min)
			{
				min = MA[i][j];
			}
		}
	}
	if (((max / min - 1) * 100) < 1)
	{
		return 1;//ճ��
	}

	return 0;
}

int MA_divergence(float* Close)//���ߡ�����ɢ
{
	int i, j;
	float MA[7][4] = { 0 };//7�죬�ĸ�����ֵ
	get_7MA(MA, Close);//���7����ľ���ֵ,(MA5,MA10,MA20,MA60)
	//MA5>MA10>MA20>MA60
	for (i = 0; i < 3; i++)
	{
		if (MA[i][0] > MA[i][1] && MA[i][1] > MA[i][2] && MA[i][2] > MA[i][3])
		{
			continue;
		}
		else
		{
			return 0;
		}
	}
	return 1;//��ɢ
}

int MA_turnup(float* Close)//���ߡ�����ͷ����
{
	int i, j;
	float MA[7][4] = { 0 };//7�죬�ĸ�����ֵ
	get_7MA(MA, Close);//���7����ľ���ֵ,(MA5,MA10,MA20,MA60)
	for (i = 0; i < 3; i++)
	{
		if (i != 2)
		{
			if (MA[i][0] > MA[i + 1][0] && MA[i][1] > MA[i + 1][1]
				&& MA[i][2] > MA[i + 1][2] && MA[i][3] > MA[i + 1][3])//����MA����
			{
				continue;
			}
			else
			{
				return 0;
			}
		}
	}
	return 1;
}

int MA_turndown(float* Close)//���ߡ�����ͷ����
{
	int i, j;
	float MA[7][4] = { 0 };//7�죬�ĸ�����ֵ
	get_7MA(MA, Close);//���7����ľ���ֵ,(MA5,MA10,MA20,MA60)
	for (i = 0; i < 3; i++)
	{
		if (i != 2)
		{
			if (MA[i][0] < MA[i + 1][0] && MA[i][1] < MA[i + 1][1]
				&& MA[i][2] < MA[i + 1][2] && MA[i][3] < MA[i + 1][3])//����MA����
			{
				continue;
			}
			else
			{
				return 0;
			}
		}
	}
	return 1;
}


/**************************************************************
FUNCTION:get_7MA
DESCRIPTION�����7�����4�־���
INPUT:MA,close
RETURN:��
****************************************************************/
void get_7MA(float MA[][4], float* close)
{
	int i, j;
	for (i = 0; i < 7; i++)
	{
		for (j = 0; j < 5; j++)
		{
			MA[i][0] += close[i + j];
		}
		MA[i][0] /= 5.0;//�������վ�ֵ
		for (j = 0; j < 10; j++)
		{
			MA[i][1] += close[i + j];
		}
		MA[i][1] /= 10.0;//����ʮ�վ�ֵ
		for (j = 0; j < 20; j++)
		{
			MA[i][2] += close[i + j];
		}
		MA[i][2] /= 20.0;//�����ʮ�վ�ֵ
		for (j = 0; j < 60; j++)
		{
			MA[i][3] += close[i + j];
		}
		MA[i][3] /= 60.0;//������ʮ�վ�ֵ
	}
}



/********************
KDJָ�꣺4��
*********************/

/**************************************************************
FUNCTION:KDJ_goldencross,KDJ_overbuy,KDJ_deadcross,KDJ_oversell
DESCRIPTION�����
			����
			����
			����
INPUT:pinfo
RETURN:��
****************************************************************/
int KDJ_goldencross(PRICEINFO* pinfo)//���ָ�ꡪ������
{
	int i;
	float K[7] = { 0 };
	float D[7] = { 0 };
	float J[7] = { 0 };
	get_KDJ(pinfo, K, D, J);
	//�µ������У�K����D��K�����µ���D��ʱ��Ϊ�����ź�
	for (i = 7; i > 0; i--)
	{
		if (K[i] < K[i - 1])//�µ���
		{
			return 0;
		}
	}
	if (K[0] > D[0] && K[6] < D[6])
	{
		return 1;//�����γ�����
	}
	return 0;
}


int KDJ_overbuy(PRICEINFO* pinfo)//���ָ�ꡪ������
{
	int i;
	float K[7] = { 0 };
	float D[7] = { 0 };
	float J[7] = { 0 };
	get_KDJ(pinfo, K, D, J);
	for (i = 0; i < 7; i++)
	{
		if (J[i] > 100)
		{
			return 1;//J����100Ϊ����
		}
	}
	return 0;
}

int KDJ_deadcross(PRICEINFO* pinfo)//���ָ�ꡪ������
{
	int i;
	float K[7] = { 0 };
	float D[7] = { 0 };
	float J[7] = { 0 };
	get_KDJ(pinfo, K, D, J);
	//�µ������У�K����D��K�����µ���D��ʱ��Ϊ�����ź�
	for (i = 7; i > 0; i--)
	{
		if (K[i] < K[i - 1])//������
		{
			return 0;
		}
	}
	if (K[0] < D[0] && K[6] > D[6])
	{
		return 1;//�����γ�����
	}
	return 0;
}

int KDJ_oversell(PRICEINFO* pinfo)//���ָ�ꡪ������
{
	int i;
	float K[7] = { 0 };
	float D[7] = { 0 };
	float J[7] = { 0 };
	get_KDJ(pinfo, K, D, J);
	for (i = 0; i < 7; i++)
	{
		if (J[i] < 0)
		{
			return 1;//JС��0Ϊ����
		}
	}
	return 0;
}

/**************************************************************
FUNCTION:get_KDJ
DESCRIPTION�����7��KDJ��ֵ
INPUT:pinfo,k,d,j
RETURN:��
****************************************************************/
void get_KDJ(PRICEINFO* pinfo, float* k, float* d, float* j)
{
	int i, m;
	float RSV = 0.0, closemax, closemin;//max,minΪ9����
	float K[20] = { 0.0 };
	float D[20] = { 0.0 };
	float J[20] = { 0.0 };
	K[20] = 50.0;
	D[20] = 50.0;//����ǰһ��Kֵ��Dֵ����ɷֱ���50������
	for (i = 19; i >= 0; i--)
	{
		//n��RSV=��Cn��Ln��/��Hn��Ln����100;
		//CnΪ��n�����̼ۣ�LnΪn���ڵ���ͼۣ�HnΪn���ڵ���߼�;
		closemin = pinfo->Close[i];
		closemax = pinfo->Close[i];
		for (m = 0; m < 9; m++)//��9��Ϊ���ڵ�KD��
		{
			if (pinfo->Close[i + m] > closemax)
			{
				closemax = pinfo->Close[i + m];
			}
			if (pinfo->Close[i + m] < closemin)
			{
				closemin = pinfo->Close[i + m];
			}
		}
		RSV = 100 * (pinfo->Close[i] - closemin) / (closemax - closemin);
		K[i] = K[i + 1] * 0.67 + RSV * 0.33;//����Kֵ=2/3��ǰһ��Kֵ+1/3������RSV
		D[i] = D[i + 1] * 0.67 + K[i] * 0.33;//����Dֵ=2/3��ǰһ��Dֵ+1/3������Kֵ
		J[i] = 3 * K[i + 1] - 2 * D[i + 1];//����Jֵ=3*����Kֵ-2*����Dֵ
	}
	for (i = 0; i < 7; i++)
	{
		k[i] = K[i];
		d[i] = D[i];
		j[i] = J[i];//������ָ�긴��
	}
}


/********************
MACDָ�꣺4��
*********************/
int MACD_updevide(PRICEINFO* pinfo)//��ͬ�ƶ�ƽ���ߡ���������
{
	float EMA12[8] = { 0.0 };
	float EMA26[8] = { 0.0 };
	float DIFF[8] = { 0.0 };
	float DEA[8] = { 0.0 };
	get_MACD(pinfo, EMA12, EMA26, DIFF, DEA);
	/*�ұߵĹɼ۱���߷�ֵ�Ĺɼ۸��ߣ�
	����ʱDIF��MACD������߷�ֵʱ���ֵ���ߵ�ʱ��
	����˵��ʱ����MACD�Ķ����롣*/
	if (pinfo->Close[0] < pinfo->Close[1] && pinfo->Close[1] < pinfo->Close[2]);
	else
	{
		return 0;
	}
	if (DIFF[0] > DIFF[1] && DIFF[1] > DIFF[2] && DIFF[2] > DIFF[3]
		&& DEA[0] > DEA[1] && DEA[1] > DEA[2] && DEA[2] > DEA[3])
	{
		return 1;
	}
	return 0;

}

int MACD_goldencross(PRICEINFO* pinfo)//��ͬ�ƶ�ƽ���ߡ������
{
	int i;
	float EMA12[8] = { 0 };
	float EMA26[8] = { 0 };
	float DIFF[8] = { 0 };
	float DEA[8] = { 0 };
	get_MACD(pinfo, EMA12, EMA26, DIFF, DEA);
	//�����������У�DIF���ϴ�DEA��(�����ϴ�����)��,�γ�MACD�����̬
	for (i = 7; i > 0; i--)
	{
		if (DIFF[i] > DIFF[i - 1])//�µ���
		{
			return 0;
		}
	}
	if (DIFF[0] < DEA[0] && DIFF[6] > DEA[6])
	{
		return 1;//�����γ�����
	}
	return 0;
}

int MACD_downdevide(PRICEINFO* pinfo)//��ͬ�ƶ�ƽ���ߡ����ױ���
{
	float EMA12[8] = { 0 };
	float EMA26[8] = { 0 };
	float DIFF[8] = { 0 };
	float DEA[8] = { 0 };
	get_MACD(pinfo, EMA12, EMA26, DIFF, DEA);
	/*���Ҳ�Ĺɼ۱����ĵ͹Ȼ���ʱ��DIF����MACD���統����ֵ�ͣ������MACD�ױ���*/
	if (pinfo->Close[0] < pinfo->Close[1] && pinfo->Close[1] < pinfo->Close[2]);
	else
	{
		return 0;
	}
	if (DIFF[0] > DIFF[1] && DIFF[1] > DIFF[2] && DIFF[2] > DIFF[3]
		&& DEA[0] > DEA[1] && DEA[1] > DEA[2] && DEA[2] > DEA[3])
	{
		return 1;
	}
	return 0;
}

int MACD_deadcross(PRICEINFO* pinfo)//��ͬ�ƶ�ƽ���ߡ�������
{
	int i;
	float EMA12[8] = { 0 };
	float EMA26[8] = { 0 };
	float DIFF[8] = { 0 };
	float DEA[8] = { 0 };
	get_MACD(pinfo, EMA12, EMA26, DIFF, DEA);
	//���µ�������DIFF ��������ͻ�� DEA
	for (i = 7; i > 0; i--)
	{
		if (DIFF[i] < DIFF[i - 1])//������
		{
			return 0;
		}
	}
	if (DIFF[0] > DEA[0] && DIFF[6] < DEA[6])
	{
		return 1;//�����γ�����
	}
	return 0;
}

/**************************************************************
FUNCTION:get_MACD
DESCRIPTION�����7����MACD��ֵ
INPUT:pinfo,ema12,ema26,diff,dea
RETURN:��
****************************************************************/
void get_MACD(PRICEINFO* pinfo, float* EMA12, float* EMA26, float* DIFF, float* DEA)
{
	int i;
	EMA12[8] = pinfo->Close[8];
	EMA26[8] = pinfo->Close[8];
	for (i = 7; i >= 0; i--)
	{
		EMA12[i] = EMA12[i + 1] * 0.846 + pinfo->Close[i] * 0.154;
		//EMA��12��=ǰһ��EMA��12����11/13+�������̼ۡ�2/13	
		EMA26[i] = EMA26[i + 1] * 0.926 + pinfo->Close[i] * 0.074;
		//EMA��26��=ǰһ��EMA��26����25/27+�������̼ۡ�2/27
		DIFF[i] = EMA12[i] - EMA26[i];
		//DIF=����EMA��12��������EMA��26��
		DEA[i] = DEA[i + 1] * 0.8 + DIFF[i] * 0.2;
		//����DEA��MACD��=ǰһ��DEA��8/10+����DIF��2/10
	}
}


/********************
RSIָ�꣺2��
*********************/
int RSI_overbuy(PRICEINFO* pinfo)//���ǿ��ָ�ꡪ������
{
	int i;
	float RSI[7] = { 0 };
	for (i = 0; i < 7; i++)
	{
		RSI[i] = get_RSI(pinfo, i, 6);
	}
	//RSI�ϴ�80
	if (RSI[0] < 80 && RSI[6]>80)
	{
		return 1;
	}
	return 0;
}


int RSI_oversell(PRICEINFO* pinfo)//���ǿ��ָ�ꡪ������
{
	int i;
	float RSI[7] = { 0 };
	for (i = 0; i < 7; i++)
	{
		RSI[i] = get_RSI(pinfo, i, 6);
	}
	//RSI�´�20
	if (RSI[0] > 20 && RSI[6] < 20)
	{
		return 1;
	}
	return 0;
}

/**************************************************************
FUNCTION:get_RSI
DESCRIPTION�����7����RSI��ֵ
INPUT:pinfo,date,days
RETURN:��
****************************************************************/
float get_RSI(PRICEINFO* pinfo, int date, int days)//���7�����RSI��RSI��6,12,24������
{
	int i;
	float RSI = 0.0;//���ǿ��ָ��RSI
	float sum_rise = 0.0;//������
	float sum_fall = 0.0;//������
	float difference;//�������̼۵Ĳ�ֵ
	for (i = 0; i < days; i++)
	{
		difference = pinfo[date + i + 1].Close - pinfo[date + i].Close;//ǰһ��-��һ��(���ݿ��������෴)

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


/********************
VOL/OBVָ�꣺2��
*********************/
int VOLOBV_trendup(PRICEINFO* pinfo)//�ɽ���/������������������
{
	int i;
	float OBV[7] = { 0 };
	get_OBV(pinfo, OBV);
	for (i = 7; i > 0; i--)
	{
		if (OBV[i] < OBV[i - 1]);//����
		else
		{
			return 0;
		}
	}
	return 1;
}

int VOLOBV_trenddown(PRICEINFO* pinfo)//�ɽ���/�����������½�����
{
	int i;
	float OBV[7] = { 0 };
	get_OBV(pinfo, OBV);
	for (i = 7; i > 0; i--)
	{
		if (OBV[i] > OBV[i - 1]);//�µ�
		else
		{
			return 0;
		}
	}
	return 1;
}

/**************************************************************
FUNCTION:get_OBV
DESCRIPTION�����7����OBV
INPUT:pinfo,obv
RETURN:��
****************************************************************/
void get_OBV(PRICEINFO* pinfo, float* obv)//���7�����������
{
	int i;
	float OBV = 0.0;
	/*��ĳ��Ϊ���ڣ������ۼ�ÿ�����й�Ʊ�ܳɽ�����
	������ָ�����Ʊ���ǣ������OBV���ϱ��ճɽ���Ϊ����OBV��
	����ָ�����Ʊ�µ��������OBV��ȥ���ճɽ���Ϊ����OBV��
	һ����˵��ֻ�ǹ۲�OBV���������޶�����壬�������K��ͼ�����Ʋ���ʵ�ʵ�Ч�á�*/
	for (i = 0; i < 7; i++)
	{
		if (pinfo->Close[i + 1] - pinfo->Close[i] >= 0)//�µ�
		{
			OBV += pinfo->VOL[i];
		}
		else if (pinfo->Close[i + 1] - pinfo->Close[i] < 0)
		{
			OBV -= pinfo->VOL[i];
		}
		obv[i] = OBV;
	}
}


/********************
BIASָ�꣺2��
*********************/
int BIAS_overbuy(PRICEINFO* pinfo)//�����ʡ�������
{
	int i;
	float BIAS6[7] = { 0 };
	float BIAS12[7] = { 0 };
	float BIAS24[7] = { 0 };
	get_BIAS(pinfo, BIAS6, BIAS12, BIAS24);
	//BIASֵ����15
	for (i = 0; i < 7; i++)
	{
		if (BIAS6[i] > 15)
		{
			return 1;
		}
		if (BIAS12[i] > 15)
		{
			return 1;
		}
		if (BIAS24[i] > 15)
		{
			return 1;
		}
	}
	return 0;
}

int BIAS_oversell(PRICEINFO* pinfo)//�����ʡ�������
{
	int i;
	float BIAS6[7] = { 0 };
	float BIAS12[7] = { 0 };
	float BIAS24[7] = { 0 };
	get_BIAS(pinfo, BIAS6, BIAS12, BIAS24);
	//BIASֵ����15
	for (i = 0; i < 7; i++)
	{
		if (BIAS6[i] < -15)
		{
			return 1;
		}
		if (BIAS12[i] < -15)
		{
			return 1;
		}
		if (BIAS24[i] < -15)
		{
			return 1;
		}
	}
	return 0;
}

/**************************************************************
FUNCTION:get_BIAS
DESCRIPTION�����7����Ĺ�����
INPUT:pinfo,bias6,bias12,bias24
RETURN:��
****************************************************************/
void get_BIAS(PRICEINFO* pinfo, float* bias6, float* bias12, float* bias24)//���7��Ĺ�����
{
	int i, j;
	float MA6 = 0.0;
	float MA12 = 0.0;
	float MA24 = 0.0;
	float BIAS6[20] = { 0 };
	float BIAS12[20] = { 0 };
	float BIAS24[20] = { 0 };
	//������=[(�������̼�-N��ƽ����)/N��ƽ����]*100%
	//����N��һ��5��6��10��12��24��30��72����ʵ�������У�����ʹ��6�չ����ʽ�Ϊ��Ч��������Ŵ�Ϊ10�ջ�12�ա�
	for (i = 0; i < 20; i++)
	{
		MA6 = 0.0;
		MA12 = 0.0;
		MA24 = 0.0;
		for (j = 0; j < 6; j++)
		{
			MA6 += pinfo->Close[i + j];
		}
		MA6 /= 6.0;
		BIAS6[i] = 100 * (pinfo->Close[i] - MA6) / MA6;//BIAS6

		for (j = 0; j < 12; j++)
		{
			MA12 += pinfo->Close[i + j];
		}
		MA12 /= 12.0;
		BIAS12[i] = 100 * (pinfo->Close[i] - MA12) / MA12;//BIAS12

		for (j = 0; j < 24; j++)
		{
			MA24 += pinfo->Close[i + j];
		}
		MA24 /= 24.0;
		BIAS24[i] = 100 * (pinfo->Close[i] - MA24) / MA24;//BIAS24
	}
	for (i = 0; i < 7; i++)
	{
		bias6[i] = BIAS6[i];
		bias12[i] = BIAS12[i];
		bias24[i] = BIAS24[i];
	}
}

/********************
BOLLָ�꣺3��
*********************/
int BOLL_breaktoprail(PRICEINFO* pinfo)//���ִ�����ͻ���Ϲ�
{
	float uprail[7] = { 0 };
	float midrail[7] = { 0 };
	float downrail[7] = { 0 };
	get_BOLL(pinfo, uprail, midrail, downrail);
	if (uprail[6] < midrail[0]
		&& uprail[6] < pinfo->Close[6]
		&& uprail[0] > pinfo->Close[0])
	{
		return 1;
	}

	return 0;
}

int BOLL_breakmediumrail(PRICEINFO* pinfo)//���ִ�����ͻ���й�
{
	float uprail[7] = { 0 };
	float midrail[7] = { 0 };
	float downrail[7] = { 0 };
	get_BOLL(pinfo, uprail, midrail, downrail);
	if (midrail[6] < midrail[0]
		&& midrail[6] < pinfo->Close[6]
		&& midrail[0] > pinfo->Close[0])
	{
		return 1;
	}

	return 0;
}

int BOLL_breakbottomrail(PRICEINFO* pinfo)//���ִ�����ͻ���¹�
{
	float uprail[7] = { 0 };
	float midrail[7] = { 0 };
	float downrail[7] = { 0 };
	get_BOLL(pinfo, uprail, midrail, downrail);
	if (downrail[6] < midrail[0]
		&& downrail[6] < pinfo->Close[6]
		&& downrail[0] > pinfo->Close[0])
	{
		return 1;
	}

	return 0;
}

/**************************************************************
FUNCTION:get_BOLL
DESCRIPTION�����7����Ĳ��ִ�
INPUT:pinfo,uprail,midrail,downrail
RETURN:��
****************************************************************/
void get_BOLL(PRICEINFO* pinfo, float* uprail, float* midrail, float* downrail)//���7��Ĳ��ִ�
{
	int i, j;
	float std_dev = 0.0;
	for (i = 0; i < 7; i++)
	{
		for (j = 0; j < 20; j++)
		{
			midrail[i] += pinfo->Close[i + j];
		}
		midrail[i] /= 20.0;//�й���=N�յ��ƶ�ƽ���ߣ���������ָ��Nһ��Ϊ20
		std_dev = get_std_deviation(pinfo, 20, i);//�����i�տ�ʼ20���ڵķ���
		uprail[i] = midrail[i] + 2 * std_dev;//�Ϲ��ߣ�up�ߣ�=�й���+�����ı�׼�2SD��
		downrail[i] = midrail[i] - 2 * std_dev;//�¹��ߣ�down�ߣ�=�й���-�����ı�׼�2SD��
	}
}

/**************************************************************
FUNCTION:get_std_deviation
DESCRIPTION�������׼��
INPUT:pinfo,days,date
RETURN:��
****************************************************************/
float get_std_deviation(PRICEINFO* pinfo, int days, int date)//�����׼��,daysΪ20.0
{
	int i;
	float aver = 0.0;//20��ƽ��ֵ
	float variance = 0.0;//����
	float std_dev = 0.0;//��׼��
	for (i = 0; i < days; i++)
	{
		aver += pinfo->Close[date + i];
	}
	aver /= days * 1.0;//�����ֵ
	for (i = 0; i < days; i++)
	{
		variance += (pinfo->Close[date + i] - aver) * (pinfo->Close[date + i] - aver);
	}
	variance /= days * 1.0;//���㷽��
	std_dev = sqrt(variance);//�����׼��

	return std_dev;
}