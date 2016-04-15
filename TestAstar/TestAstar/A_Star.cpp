//#include <stdafx.h>  
#include "A_Star.h"  
#include <cstdio>


int dx[24] = { NULL }, dy[24] = { NULL };
static int Stshop_point_num;

CAStarBase::CAStarBase()
{
	m_pAPointArr = NULL;
	m_nAPointArrWidth = 0;
	m_nAPointArrHeight = 0;
	m_pStartPoint = NULL;
	m_pEndPoint = NULL;
	m_pCurPoint = NULL;

}

CAStarBase::~CAStarBase()
{

}

BOOL CAStarBase::Create(char* pDateArr, int nWidth, int nHeight,int point[][2])
{
	if (!pDateArr) return FALSE;                                                   //数组地址是否存在
	if (nWidth<1 || nHeight<1) return FALSE;                                       //判断数组的长宽是否大于一
	m_pAPointArr = new APoint[nWidth*nHeight];
	if (!m_pAPointArr) return FALSE;
	m_pOldArr = pDateArr;                                                          //父节点(指针形式）
	m_nAPointArrWidth = nWidth;                                                    //数组的宽度
	m_nAPointArrHeight = nHeight;                                                  //数组的高度
	int shop_point_num=0;
	for (int y = 0; y<m_nAPointArrHeight; y++)                                     // 初始化数组内容
	{
		for (int x = 0; x<m_nAPointArrWidth; x++)
		{
			m_pAPointArr[y*m_nAPointArrWidth + x].x = x;                           //赋值形式？
			m_pAPointArr[y*m_nAPointArrWidth + x].y = y;
			m_pAPointArr[y*m_nAPointArrWidth + x].g = 0;
			m_pAPointArr[y*m_nAPointArrWidth + x].f = 0;
			m_pAPointArr[y*m_nAPointArrWidth + x].h = 0;
			while (shop_point_num<row_num)
			{
				if (m_pAPointArr[y*m_nAPointArrWidth + x].x == point[shop_point_num][0] &&
					m_pAPointArr[y*m_nAPointArrWidth + x].y == point[shop_point_num][1])
				{
					pDateArr[y*m_nAPointArrWidth + x] = 'F' + shop_point_num;
					m_pAPointArr[y*m_nAPointArrWidth + x].type = APT_ENDPOINT_TO;
					m_pShopPoint[shop_point_num] = m_pAPointArr + y*m_nAPointArrWidth + x;
				}
				shop_point_num++;
			}
			shop_point_num = 0;

			if (pDateArr[y*m_nAPointArrWidth + x] == '1')
			{
				m_pAPointArr[y*m_nAPointArrWidth + x].type = APT_OBSTACLE;
			}
			else if (pDateArr[y*m_nAPointArrWidth + x] == 'S')
			{
				m_pAPointArr[y*m_nAPointArrWidth + x].type = APT_STARTPOINT;
				m_pStartPoint = m_pAPointArr + y*m_nAPointArrWidth + x;            //赋值形式？
				m_pCurPoint = m_pStartPoint;
			}
			else if (pDateArr[y*m_nAPointArrWidth + x] == 'E')
			{
				m_pAPointArr[y*m_nAPointArrWidth + x].type = APT_ENDPOINT;
				m_pEndPoint = m_pAPointArr + y*m_nAPointArrWidth + x;
			}
			else if (pDateArr[y*m_nAPointArrWidth + x] == '0')
			{
				m_pAPointArr[y*m_nAPointArrWidth + x].type = APT_UNKNOWN;
			}

		}
	}
	return TRUE;                                        //初始化返回为真
}


void CAStarBase::SetCurrent(int x, int y)
{
	m_pCurPoint = m_pAPointArr + y*m_nAPointArrWidth + x;
}

void CAStarBase::SetOpened(int x, int y)                //建立“开启列表”
{
	if (m_pAPointArr[y*m_nAPointArrWidth + x].type != APT_OPENED)
	{
		m_pAPointArr[y*m_nAPointArrWidth + x].type = APT_OPENED;
	}
}

void CAStarBase::SetClosed(int x, int y)                 //建立“关闭列表”
{
	if (m_pAPointArr[y*m_nAPointArrWidth + x].type != APT_CLOSED)
	{
		m_pAPointArr[y*m_nAPointArrWidth + x].type = APT_CLOSED;
	}
}


void CAStarBase::PrintCharArr(char* pDateArr)          //打印终点
{
	if (m_pOldArr)                                    //是否有父节点
	{
		for (int y = 0; y<m_nAPointArrHeight; y++)
		{
			for (int x = 0; x<m_nAPointArrWidth; x++)
			{
				if (m_pAPointArr[y*m_nAPointArrWidth + x].type == APT_CLOSED)
					m_pAPointArr[y*m_nAPointArrWidth + x].type = APT_UNKNOWN;
				if (m_pAPointArr[y*m_nAPointArrWidth + x].type == APT_OPENED)
					m_pAPointArr[y*m_nAPointArrWidth + x].type = APT_UNKNOWN;
				/*else if (m_pAPointArr[y*m_nAPointArrWidth + x].type = APT_STARTPOINT)
					*(pDateArr + x + m_nAPointArrWidth*y) = 'S';*/
				if (pDateArr[y*m_nAPointArrWidth + x] == '1')
				{
					m_pAPointArr[y*m_nAPointArrWidth + x].type = APT_OBSTACLE;
				}
				printf("%c ", m_pOldArr[x + m_nAPointArrWidth*y]);
			}
			printf("\r\n");
		}
		printf("\r\n");
	}
}

PAPoint CAStarBase::FindPointPath(int Cx,int Cy,int temp)
{
	int x = Cx;
	int y = Cy; 
	//static int temp = m_pAPointArr[x + m_nAPointArrWidth*y].g - 1;
	static int i=0;
	static int Point_Path[200][2];
	//左
	if (m_pAPointArr[(x - 1) + m_nAPointArrWidth*y].type == APT_CLOSED&&
		m_pAPointArr[(x - 1) + m_nAPointArrWidth*y].g == temp)
	{
		Point_Path[i][0] = x - 1;
		Point_Path[i][1] = y;
		//SetCurrent(Point_Path[i][0], Point_Path[i][1]);
		m_pAPointArr[(x - 1) + m_nAPointArrWidth*y].type = APT_OPENED;
		*(m_pOldArr + (x - 1) + m_nAPointArrWidth* y ) = '-';
		i++;
		temp--;
		return FindPointPath(x-1,y,temp);
	}
	//右
	if (m_pAPointArr[(x + 1) + m_nAPointArrWidth*y].type == APT_CLOSED&&
		m_pAPointArr[(x + 1) + m_nAPointArrWidth*y].g == temp)
	{
		Point_Path[i][0] = x + 1;
		Point_Path[i][1] = y;
		//SetCurrent(Point_Path[i][0], Point_Path[i][1]);
		m_pAPointArr[(x + 1 ) + m_nAPointArrWidth*y ].type = APT_OPENED;
		*(m_pOldArr + (x + 1) + m_nAPointArrWidth* y) = '-';
		i++;
		temp--;
		return FindPointPath(x + 1, y,temp);
	}
	//上
	if (m_pAPointArr[x + m_nAPointArrWidth*(y - 1)].type == APT_CLOSED&&
		m_pAPointArr[x + m_nAPointArrWidth*(y - 1)].g == temp)
	{
		Point_Path[i][0] = x;
		Point_Path[i][1] = y - 1;
		m_pAPointArr[x + m_nAPointArrWidth*(y - 1)].type = APT_OPENED;
		*(m_pOldArr + x + m_nAPointArrWidth* (y - 1)) = '-';
		i++;
		temp--;
		return FindPointPath(x , y - 1,temp);
	}
	//下
	if (m_pAPointArr[x + m_nAPointArrWidth*(y + 1)].type == APT_CLOSED&&
		m_pAPointArr[x + m_nAPointArrWidth*(y + 1)].g == temp)
	{
		Point_Path[i][0] = x;
		Point_Path[i][1] = y + 1;
		m_pAPointArr[x + m_nAPointArrWidth*(y + 1)].type = APT_OPENED;
		*(m_pOldArr + x + m_nAPointArrWidth* (y + 1)) = '-';
		i++;
		temp--;
		return FindPointPath(x, y + 1,temp);
	}
	//到起点的周围
	static int StartNum = 0;
	if (!StartNum)
	{
		StartNum++;
		return 	m_pStartPoint;
	}
	else if ((x == dx[StartNum-1] && abs(y - dy[StartNum-1]) == 1) || (y == dy[StartNum-1] && abs(x - dx[StartNum-1]) == 1))    
	{
		if (StartNum)
		{
			StartNum++;
			return m_pStartPoint;
		}
		else if (StartNum == Stshop_point_num)
		{
			StartNum = 0;
			return m_pStartPoint;
		}
	}
	//退回上一个点
	m_pAPointArr[x + m_nAPointArrWidth*y].type = APT_OPENED;
	*(m_pOldArr + x + m_nAPointArrWidth* y) = '0';
	i--;
	temp++;
	x = Point_Path[i][0];
	y = Point_Path[i][1];
	return FindPointPath(x , y,temp);	
}

PAPoint CAStarBase::CalcNextPoint(PAPoint ptCalc, char* pDateArr)
{
	if (ptCalc == NULL)
		ptCalc = m_pStartPoint;
	int x = ptCalc->x;
	int y = ptCalc->y;
	int shop_point_num = 0;
	while (m_pShopPoint[shop_point_num])
	{
		dx[shop_point_num] = m_pShopPoint[shop_point_num]->x;
		dy[shop_point_num] = m_pShopPoint[shop_point_num]->y;
		shop_point_num++;
	}
	Stshop_point_num = shop_point_num;
	dx[Stshop_point_num] = m_pEndPoint->x;
	dy[Stshop_point_num] = m_pEndPoint->y;
	int xmin = x, ymin = y;
	int vmin = 0;                                                   // 最优步骤的坐标和值  
	static int i = 0;
	if ((x == dx[i] && abs(y - dy[i]) == 1) || (y == dy[i] && abs(x - dx[i]) == 1))     //是否在终点的周围
	{
		m_pAPointArr[dx[i] + m_nAPointArrWidth*dy[i]].g = m_pAPointArr[x + m_nAPointArrWidth*y].g + 1;
		vmin = 0;
		printf("\r\n\n");
		if (FindPointPath(dx[i], dy[i], m_pAPointArr[x + m_nAPointArrWidth*y].g) == m_pStartPoint)
			PrintCharArr(pDateArr);
		if ((x == dx[Stshop_point_num] && abs(y - dy[Stshop_point_num]) == 1) 
			|| (y == dy[Stshop_point_num] && abs(x - dx[Stshop_point_num]) == 1))
		{
			i = 0;
			//PrintCharArr(pDateArr);
			return m_pEndPoint;
		}
		vmin = 0;
		//PrintCharArr(pDateArr);
		m_pStartPoint = m_pAPointArr + dy[i] * m_nAPointArrWidth + dx[i];
		i++;
		return CalcNextPoint(m_pStartPoint, pDateArr);
	}
	// 上  
	if ((m_pAPointArr[(x + 0) + m_nAPointArrWidth*(y - 1)].type == APT_UNKNOWN) && y > 0)
	{
		m_pAPointArr[(x + 0) + m_nAPointArrWidth*(y - 1)].g = m_pAPointArr[x + m_nAPointArrWidth*y].g + 1;
		m_pAPointArr[(x + 0) + m_nAPointArrWidth*(y - 1)].h =
			10 * (abs(x - dx[i]) + abs(y - 1 - dy[i]));
		m_pAPointArr[(x + 0) + m_nAPointArrWidth*(y - 1)].f =
			m_pAPointArr[(x + 0) + m_nAPointArrWidth*(y - 1)].g + m_pAPointArr[(x + 0) + m_nAPointArrWidth*(y - 1)].h;
		m_pAPointArr[x + m_nAPointArrWidth*(y - 1)].type = APT_OPENED;
		if (vmin == 0)
		{
			xmin = x;
			ymin = y - 1;
			vmin = m_pAPointArr[(x + 0) + m_nAPointArrWidth*(y - 1)].h;
		}
		else{
			if (vmin > m_pAPointArr[(x + 0) + m_nAPointArrWidth*(y - 1)].h)
			{
				xmin = x;
				ymin = y - 1;
				vmin = m_pAPointArr[(x + 0) + m_nAPointArrWidth*(y - 1)].h;
			}
		}
	}
	// 下  
	if ((m_pAPointArr[(x + 0) + m_nAPointArrWidth*(y + 1)].type == APT_UNKNOWN) && y < m_nAPointArrHeight)
	{
		m_pAPointArr[(x + 0) + m_nAPointArrWidth*(y + 1)].g = m_pAPointArr[x + m_nAPointArrWidth*y].g + 1;
		m_pAPointArr[(x + 0) + m_nAPointArrWidth*(y + 1)].h =
			10 * (abs(x - dx[i]) + abs(y + 1 - dy[i]));
		m_pAPointArr[(x + 0) + m_nAPointArrWidth*(y + 1)].f =
			m_pAPointArr[(x + 0) + m_nAPointArrWidth*(y + 1)].g + m_pAPointArr[(x + 0) + m_nAPointArrWidth*(y + 1)].h;
		m_pAPointArr[x + m_nAPointArrWidth*(y + 1)].type = APT_OPENED;
		if (vmin == 0)
		{
			xmin = x;
			ymin = y + 1;
			vmin = m_pAPointArr[(x + 0) + m_nAPointArrWidth*(y + 1)].h;
		}
		else{
			if (vmin > m_pAPointArr[(x + 0) + m_nAPointArrWidth*(y + 1)].h)
			{
				xmin = x;
				ymin = y + 1;
				vmin = m_pAPointArr[(x + 0) + m_nAPointArrWidth*(y + 1)].h;
			}
		}
	}
	// 左  
	if ((m_pAPointArr[(x - 1) + m_nAPointArrWidth*y].type == APT_UNKNOWN) && x > 0)
	{
		m_pAPointArr[(x - 1) + m_nAPointArrWidth*y].g = m_pAPointArr[x + m_nAPointArrWidth*y].g + 1;
		m_pAPointArr[(x - 1) + m_nAPointArrWidth*y].h =
			10 * (abs(x - 1 - dx[i]) + abs(y - dy[i]));
		m_pAPointArr[(x - 1) + m_nAPointArrWidth*y].f =
			m_pAPointArr[(x - 1) + m_nAPointArrWidth*y].g + m_pAPointArr[(x - 1) + m_nAPointArrWidth*y].h;
		m_pAPointArr[(x - 1) + m_nAPointArrWidth* y].type = APT_OPENED;
		if (vmin == 0)
		{
			xmin = x - 1;
			ymin = y;
			vmin = m_pAPointArr[(x - 1) + m_nAPointArrWidth*y].h;
		}
		else{
			if (vmin > m_pAPointArr[(x - 1) + m_nAPointArrWidth*y].h)
			{
				xmin = x - 1;
				ymin = y;
				vmin = m_pAPointArr[(x - 1) + m_nAPointArrWidth*y].h;
			}
		}
	}

	// 右  
	if ((m_pAPointArr[(x + 1) + m_nAPointArrWidth*y].type == APT_UNKNOWN) && x < m_nAPointArrWidth)
	{
		m_pAPointArr[(x + 1) + m_nAPointArrWidth*y].g = m_pAPointArr[x + m_nAPointArrWidth*y].g + 1;
		m_pAPointArr[(x + 1) + m_nAPointArrWidth*y].h =
			10 * (abs(x + 1 - dx[i]) + abs(y - dy[i]));
		m_pAPointArr[(x + 1) + m_nAPointArrWidth*y].f =
			m_pAPointArr[(x + 1) + m_nAPointArrWidth*y].g + m_pAPointArr[(x + 1) + m_nAPointArrWidth*y].h;
		m_pAPointArr[(x + 1) + m_nAPointArrWidth* y].type = APT_OPENED;
		if (vmin == 0)
		{
			xmin = x + 1;
			ymin = y;
			vmin = m_pAPointArr[(x + 1) + m_nAPointArrWidth*y].h;
		}
		else{
			if (vmin > m_pAPointArr[(x + 1) + m_nAPointArrWidth*y].h)
			{
				xmin = x + 1;
				ymin = y;
				vmin = m_pAPointArr[(x + 1) + m_nAPointArrWidth*y].h;
			}
		}
	}


	int Vim_Campare_x, Vim_Campare_y;
	if (vmin)
	{
		if (vmin > m_pAPointArr[x + m_nAPointArrWidth*y].h)
		{
			for (int for_x = 0; for_x < m_nAPointArrWidth; for_x++)
			{
				for (int for_y = 0; for_y < m_nAPointArrHeight; for_y++)
				{
					if (m_pAPointArr[for_x + m_nAPointArrWidth*for_y].type == APT_OPENED)
					{
						if (m_pAPointArr[for_x + m_nAPointArrWidth*for_y].h < vmin)
						{
							SetCurrent(for_x, for_y);
							SetClosed(for_x, for_y);
							return CalcNextPoint(m_pCurPoint, pDateArr);
						}
					}
				}
			}
		}
		SetCurrent(xmin, ymin);
		SetClosed(xmin, ymin);
		return CalcNextPoint(m_pCurPoint, pDateArr);
	}
	else{
		int Vim_Campare_h=500;
		for (int for_x = 0; for_x < m_nAPointArrWidth; for_x++)
		{
			for (int for_y = 0; for_y < m_nAPointArrHeight; for_y++)
			{
				if (m_pAPointArr[for_x + m_nAPointArrWidth*for_y].type == APT_OPENED)
				{
					if (m_pAPointArr[for_x + m_nAPointArrWidth*for_y].h < Vim_Campare_h)
					{
						Vim_Campare_h = m_pAPointArr[for_x + m_nAPointArrWidth*for_y].h;
						Vim_Campare_x = m_pAPointArr[for_x + m_nAPointArrWidth*for_y].x;
						Vim_Campare_y = m_pAPointArr[for_x + m_nAPointArrWidth*for_y].y;
					}
				}
			}
		}
		SetCurrent(Vim_Campare_x, Vim_Campare_y);
		SetClosed(Vim_Campare_x, Vim_Campare_y);
		return CalcNextPoint(m_pCurPoint, pDateArr);
	}
}


