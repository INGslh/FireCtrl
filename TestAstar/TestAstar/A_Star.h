/*
A star 算法的基础处理
*/
#ifndef _A_STAR_BASE_H_  
#define _A_STAR_BASE_H_  
#include "windows.h"  

typedef struct _APoint{
	int x; // x 坐标  
	int y; // y 坐标  
	int type; // 类型  
	int f; // f = g + h  
	int g;
	int h;
} APoint, *PAPoint;

enum APointType{
	APT_UNKNOWN, // 未知状态  
	APT_OPENED, // 开放列表中  
	APT_CLOSED, // 关闭列表中  
	APT_STARTPOINT, // 起始点  
	APT_ENDPOINT, // 结束点  
	APT_ENDPOINT_TO,   //中间节点
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
	//PAPoint CalcNextPoint(PAPoint ptCalc); // 应用迭代的办法进行查询
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
	PAPoint CalcNextPoint(PAPoint ptCalc, char* pDateArr); // 应用迭代的办法进行查询  
	PAPoint FindPointPath(int x,int y,int temp);
};

#endif  