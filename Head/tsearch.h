#ifndef _TSEARCH_H_
#define _TSEARCH_H_

//������ѡ����������
void T_search(int opt[][6], int* sto_list, int progress_color);

//��ȡһֻ��Ʊ90���Open,Close,High,Low,VOL��Ϣ
void sto_90days2float(PRICEINFO* pinfo, int sto_num);

//����������
int techsearch(int opt[][6], PRICEINFO* pinfo);

//���½�����
void refresh_progress(int progress, int color);

#endif
