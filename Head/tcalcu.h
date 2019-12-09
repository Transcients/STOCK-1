#ifndef _TCALCU_H_
#define _TCALCU_H_
#include"database.h"

int K_onelimitup(PRICEINFO* pinfo);//����K�ߡ���һ����ͣ��
int K_longhatch(PRICEINFO* pinfo);//����K�ߡ�������Ӱ��
int K_greatredline(PRICEINFO* pinfo);//����K�ߡ���������

int K2_manysuppress(PRICEINFO* pinfo);//˫��K�ߡ����෽ѹ��
int K2_emptysuppress(PRICEINFO* pinfo);//˫��K�ߡ����շ�ѹ��
int K2_trendpause(PRICEINFO* pinfo);//˫��K�ߡ�������ͣ��

int K3_tribleredline(PRICEINFO* pinfo);//����K�ߡ���������
int K3_triblegreenline(PRICEINFO* pinfo);//����K�ߡ���������
int K3_islandreverse(PRICEINFO* pinfo);//����K�ߡ������η�ת

int KN_bathbeauty(PRICEINFO* pinfo);//���K�ߡ�����ˮܽ��
int KN_fodderchoppor(PRICEINFO* pinfo);//���K�ߡ�����ͷա��

int MA_manyarray(float* Close);//���ߡ�����ͷ����
int MA_emptyarray(float* Close);//���ߡ�����ͷ����
int MA_bond(float* Close);// ���ߡ���ճ��
int MA_divergence(float* close);//���ߡ�����ɢ
int MA_turnup(float* close);//���ߡ�����ͷ����
int MA_turndown(float* close);//���ߡ�����ͷ����
void get_7MA(float MA[][4], float* close);//���7�����4�־���

int KDJ_goldencross(PRICEINFO* pinfo);//���ָ�ꡪ�����
int KDJ_deadcross(PRICEINFO* pinfo);//���ָ�ꡪ������
int KDJ_overbuy(PRICEINFO* pinfo);//���ָ�ꡪ������
int KDJ_oversell(PRICEINFO* pinfo);//���ָ�ꡪ������
void get_KDJ(PRICEINFO* pinfo, float* k, float* d, float* j);//���7��KDJ��ֵ

int MACD_updevide(PRICEINFO* pinfo);//��ͬ�ƶ�ƽ���ߡ���������
int MACD_goldencross(PRICEINFO* pinfo);//��ͬ�ƶ�ƽ���ߡ������
int MACD_downdevide(PRICEINFO* pinfo);//��ͬ�ƶ�ƽ���ߡ����ױ���
int MACD_deadcross(PRICEINFO* pinfo);//��ͬ�ƶ�ƽ���ߡ�������
void get_MACD(PRICEINFO* pinfo, float* ema12, float* ema26, float* diff, float* dea);//���7����MACD��ֵ

int RSI_overbuy(PRICEINFO* pinfo);//���ǿ��ָ�ꡪ������
int RSI_oversell(PRICEINFO* pinfo);//���ǿ��ָ�ꡪ������
float get_RSI(PRICEINFO* pinfo, int date, int days);//���7�����RSI��RSI��6,12,24������

int VOLOBV_trendup(PRICEINFO* pinfo);//�ɽ���/������������������
int VOLOBV_trenddown(PRICEINFO* pinfo);//�ɽ���/�����������½�����
void get_OBV(PRICEINFO* pinfo, float* obv);//���7�����������

int BIAS_overbuy(PRICEINFO* pinfo);// �����ʡ�������
int BIAS_oversell(PRICEINFO* pinfo);//�����ʡ�������
void get_BIAS(PRICEINFO* pinfo, float* bias6, float* bias12, float* bias24);//���7��Ĺ�����

int BOLL_breaktoprail(PRICEINFO* pinfo);//���ִ�����ͻ���Ϲ�
int BOLL_breakmediumrail(PRICEINFO* pinfo);//���ִ�����ͻ���й�
int BOLL_breakbottomrail(PRICEINFO* pinfo);//���ִ�����ͻ���¹�
void get_BOLL(PRICEINFO* pinfo, float* uprail, float* midrail, float* downrail);//���7��Ĳ��ִ�
float get_std_deviation(PRICEINFO* pinfo, int days, int date);//�����׼��,daysΪ20.0

#endif