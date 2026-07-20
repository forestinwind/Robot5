#define _USE_MATH_DEFINES
#include<iostream>
#include<cmath>
#include"Robot.h"
#include"MoveCommander.h"
int main()
{	
	int   Pusle[8] = { 131072, 131072, 131072, 131072, 131072, 131072, 131072, 131072 };
	double Pitch[8] = { 5,5,10,124.54,2 * M_PI,2 * M_PI,2 * M_PI,20 };
	double Ratio[8] = { 1.0, 1.0, 1.0, 10.0, 50, 81, 25, 1 };
	double HLimit[8] = { 200,200,200,200,200,200,200,20 };
	double LLimit[8] = { -200,-200,-200,-200,-200,-200,-200,20 };
	int dirReverse[8] = { 0,0,0,0,1,1,0,0 };
	int wAxisMap[8] = { 2, 0, 3, 4, 5, 6, -1, -1 };

	double ToolPos[3] = {1.05,0.69,-504.41};
	RinnRobotCommander::MoveCommander moveCommander(Ratio, Pitch, Pusle, 
		HLimit, LLimit, dirReverse, wAxisMap,ToolPos);

	double x, y, z, rx, ry, rz, a, b;
	MCS_GetCurRefPos(&x, &y, &z, &rx, &ry, &rz, &a, &b);
	std::cout << x << "," << y << "," << z << "," << rx << "," << ry << "," << rz << std::endl;
	moveCommander.MoveIntime(0, 10, 10, 0, 0, 0, 5);
	MCS_GetCurRefPos(&x, &y, &z, &rx, &ry, &rz, &a, &b);
	std::cout << x << "," << y << "," << z << "," << rx << "," << ry << "," << rz << std::endl;
	// CloseSystem(); // No longer needed, handled by MoveCommander destructor
	return 0;
}