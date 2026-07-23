#define _USE_MATH_DEFINES
#include<iostream>
#include<cmath>
#include<Windows.h>
#include"Robot.h"
#include"MoveCommander.h"
//int ReZero()
//{
//	int nRtn;
//	nRtn = MCS_SetPtPSpeed(1);
//	nRtn = MCS_PtP(0, 0, 0, 0, 0, 0, 0, 0);
//	return nRtn;
//}
void printPos(JointPositions* pos) {
	if (pos == nullptr) {
		std::cout << "Position is null." << std::endl;
		return;
	}
	std::cout << "Current Joint Positions: "
			  << "j1: " << pos->j1 << ", "
			  << "j2: " << pos->j2 << ", "
			  << "j3: " << pos->j3 << ", "
			  << "j4: " << pos->j4 << ", "
			  << "j5: " << pos->j5 << ", "
			  << "j6: " << pos->j6 << ", "
			  << "j7: " << pos->j7 << ", "
			  << "j8: " << pos->j8
			  << std::endl;
}
int main()
{	
	int   Pusle[8] = { 131072, 131072, 131072, 131072, 131072, 131072, 131072, 131072 };
	//Y1,Y2,X,Z,RZ,RY;
	double Pitch[8] = { 10,10,10,124.54,2 * M_PI,2 * M_PI,2 * M_PI,20 };
	double Ratio[8] = { 1.0, 1.0, 1.0, 10.0, 50, 81, 25, 1 };
	double HLimit[8] = { 200,200,200,200,200,200,200,20 };
	double LLimit[8] = { -200,-200,-200,-200,-200,-200,-200,20 };
	int dirReverse[8] = { 0,0,0,0,0,0,0,0 };
	int wAxisMap[8] = { 2, 0, 3, 4, 5, 6, -1, -1 };
	int Encvalue0[8] = { 8105640,-9610163,-2333917,2130859,-8213689,-1682896,0,0 };
	double ToolPos[3] = {1.05,0.69,-504.41};
	RinnRobotCommander::MoveCommander moveCommander(Ratio, Pitch, Pusle, 
		HLimit, LLimit, dirReverse, wAxisMap,ToolPos);
	controlSystem::SetAbsPos(Encvalue0, Ratio, Pitch, Pusle, wAxisMap);
	Sleep(1000);
	JointPositions* pos = new JointPositions();
	controlSystem::GetCurJPos(pos);
	printPos(pos);
	//moveCommander.MoveIntime(0, 10, 10, 0, 0, 0, 5);
	//controlSystem::GetCurJPos(pos);
	//printPos(pos);
	// CloseSystem(); // No longer needed, handled by MoveCommander destructor
	return 0;
}