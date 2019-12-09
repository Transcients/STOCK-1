#ifndef _TECHLINE_H_
#define _THCHLINE_H_

#include"database.h"

void majorinfo_show(int kind, STODAYFLOAT* info, UPLINE* major, float max, float min);//��ʾ��ͼ��Ϣ���ܿغ���
void viceinfo_show(int kind, STODAYFLOAT* info, DOWNLINE* vice);////��ʾ��ͼ��Ϣ���ܿغ���

void Kline_draw(STODAYFLOAT* info, float max, float min);//��K��,max,minΪget_border����ı߽�
void MA_draw(STODAYFLOAT* info, UPLINE* major, float max, float min);//����MA�ߣ�majorΪ�����ͼ������Ϣ�Ľṹ��ָ��
void BOLL_draw(STODAYFLOAT* info, UPLINE* major, float max, float min);//����BOLL������ָ��
void ENE_draw(STODAYFLOAT* info, UPLINE* major, float max, float min);//����ENE�����ָ��


void VOL_draw(STODAYFLOAT* info, DOWNLINE* vice);//����VOL�ɽ�����״ͼ,viceΪ��Ÿ�ͼ��Ϣ�Ľṹ��ָ��
void BRAR_draw(STODAYFLOAT* info, DOWNLINE* vice);//����������Ըָ��BRAR
void BIAS_draw(STODAYFLOAT* info, DOWNLINE* vice);//���ƹ�����BIAS
void CR_draw(STODAYFLOAT* info, DOWNLINE* vice);//��������ָ��CR
void DMA_draw(STODAYFLOAT* info, DOWNLINE* vice);//����ƽ���߲�DMA
void OBV_draw(STODAYFLOAT* info, DOWNLINE* vice);//����������OBV
void KDJ_draw(STODAYFLOAT* info, DOWNLINE* vice);//�������ָ��KDJ
void MACD_draw(STODAYFLOAT* info, DOWNLINE* vice);//������ͬ�ƶ�ƽ����MACD
void RSI_draw(STODAYFLOAT* info, DOWNLINE* vice);//�������ǿ��ָ��RSI
float RSI_calculate(STODAYFLOAT* info, int date, int days);//����RSI

#endif