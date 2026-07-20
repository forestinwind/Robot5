#pragma once

#include"Robot.h"

namespace RinnRobotCommander{
    class MoveCommander{
    private:
        double tool_Pos[3];
    public:
        MoveCommander(double ratio[], double Pitch[], int pusle[], double HLimit[], double LLimit[], int dirReverse[], int wAxisMap[],double toolPos[3] = nullptr){
            int nRtn = InitSystem(ratio, Pitch, pusle, HLimit, LLimit, dirReverse, wAxisMap);
            if(toolPos){
                tool_Pos[0] = toolPos[0];
                tool_Pos[1] = toolPos[1];
                tool_Pos[2] = toolPos[2];
            }
        }
        void MoveIntime(double dx,double dy,double dz,double drx,double dry,double drz,double sec){
            double x, y, z, rx, ry, rz, a, b;
            MCS_GetCurRefPos(&x, &y, &z, &rx, &ry, &rz, &a, &b);
            MCS_SetPtPSpeedEx(dx/sec,dy/sec,dz/sec,drx/sec,dry/sec,drz/sec,0,0);
            MCS_PtP(dx,dy,dz,drx,dry,drz,0,0);
        }
        ~MoveCommander(){
            CloseSystem();
        }
    };
}