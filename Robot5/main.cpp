#define _USE_MATH_DEFINES
#include<iostream>
#include<cmath>
#include"Robot.h"
int main()
{	
	int   Pusle[8] = { 131072, 131072, 131072, 131072, 131072, 131072, 0, 0 };
	double Pitch[8] = { 5,5,10,117.81,2 * M_PI,2 * M_PI,2 * M_PI,20 };
	double Ratio[8] = { 1.0, 1.0, 1.0, 10.0, 30.0, 75.0, 0, 0 };
	double HLimit[8] = { 200,200,200,200,200,200,200,20 };
	double LLimit[8] = { -200,-200,-200,-200,-200,-200,-200,20 };

	InitSystem(Ratio, Pitch, Pusle, HLimit, LLimit);
	double x, y, z, rx, ry, rz, a, b;
	MCS_GetCurRefPos(&x, &y, &z, &rx, &ry, &rz, &a, &b);
	std::cout << x << "," << y << "," << z << "," << rx << "," << ry << "," << rz << std::endl;
	MCS_JogSpace(5, 1, 0);
	MCS_PtPX(5);
	MCS_GetCurRefPos(&x, &y, &z, &rx, &ry, &rz, &a, &b);
	std::cout << x << "," << y << "," << z << "," << rx << "," << ry << "," << rz << std::endl;
	CloseSystem();
	return 0;
}