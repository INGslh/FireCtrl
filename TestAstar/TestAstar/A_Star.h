/*
A star �㷨�Ļ�������
*/
#ifndef _A_STAR_BASE_H_  
#define _A_STAR_BASE_H_  
#include "windows.h"  

typedef struct _APoint{
	int x; // x ����  
	int y; // y ����  
	int type; // ����  
	int f; // f = g + h  
	int g;
	int h;
} APoint, *PAPoint;

enum APointType{
	APT_UNKNOWN, // δ֪״̬  
	APT_OPENED, // �����б���  
	APT_CLOSED, // �ر��б���  
	APT_STARTPOINT, // ��ʼ��  
	APT_ENDPOINT, // ������  
	APT_ENDPOINT_TO,   //�м�ڵ�
	APT_OBSTACLE
};


class CAStarBase{
public:
	CAStarBase();
	~CAStarBase();
private:
	PAPoint m_pAPointArr;
	int m_nAPointArrWidth;
	int m_nAPointArrHeight;
	PAPoint m_pStartPoint, m_pEndPoint, m_pCurPoint;
	//PAPoint CalcNextPoint(PAPoint ptCalc); // Ӧ�õ����İ취���в�ѯ
	char* m_pOldArr;
public:
	int row_num;
	PAPoint m_pShopPoint[24];
	BOOL Create(char* pDateArr, int nWidth, int nHeight,int point[][2]);
	void SetStartPoint(int x, int y);
	void SetEndPoint(int x, int y);
	void SetOpened(int x, int y);
	void SetClosed(int x, int y);
	void SetCurrent(int x, int y);
	void PrintCharArr(char* pDateArr);
	PAPoint CalcNextPoint(PAPoint ptCalc, char* pDateArr); // Ӧ�õ����İ취���в�ѯ  
	PAPoint FindPointPath(int x,int y,int temp);
};

#endif  