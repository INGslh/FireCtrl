// AStarMath.cpp : 定义控制台应用程序的入口点。  
//  

//#include <stdafx.h>  
#include "A_Star.h" 
#include"Coordinate.h"
#include <stdio.h>
#include <iostream>

CAStarBase Astarbase;
using namespace std;
int main()
{
	int m, n;
	int (*point)[2];
	cout << "input ";
	cin >> Astarbase.row_num;
	point = new int[Astarbase.row_num][2];
	for (m = 0; m < Astarbase.row_num; m++)
		for (n = 0; n < 2; n++)
			cin >> point[m][n];
	for (m = 0; m < Astarbase.row_num; m++)
		for (n = 0; n < 2; n++)
			cout << point[m][n];
	cout << "\n\n";
	Astarbase.Create(&pBuff[0][0], 43 ,20,point);
	Astarbase.PrintCharArr(&pBuff[0][0]);
	PAPoint pPoint = Astarbase.CalcNextPoint(NULL, &pBuff[0][0]);
	if (pPoint == NULL)
	{
		cout<<"no path can arrive!\r\n"<<endl;
	}
	else{
		cout<<"success arrived!\r\n"<<endl;
	}
	getchar();
	getchar();
	return 0;
}