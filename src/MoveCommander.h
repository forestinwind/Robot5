#pragma once

#include"Robot.h"

#include<iostream>
namespace RinnRobotCommander{
    class MoveCommander{
    private:
        double tool_Pos[3];
        double tool_Speed[6];
        double wRPM;
        double convexSpeed(double d,size_t idx){
            return d/tool_Speed[idx]*100;
        }
        double toRad(double deg){
            return deg*M_PI/180;
        }
        void SetSpeed(double dx,double dy,double dz,double drx,double dry,double drz){
            MCS_SetPtPSpeedEx(convexSpeed(dx,0),convexSpeed(dy,1),convexSpeed(dz,2),
                convexSpeed(drx,3),convexSpeed(dry,4),convexSpeed(drz,5),0,0);
        }
    public:
        MoveCommander(double ratio[], double Pitch[], int pusle[], double HLimit[], double LLimit[], int dirReverse[], int wAxisMap[],double toolPos[3] = nullptr){
            int nRtn = InitSystem(ratio, Pitch, pusle, HLimit, LLimit, dirReverse, wAxisMap);
            wRPM = 50;
            if(toolPos){
                tool_Pos[0] = toolPos[0];
                tool_Pos[1] = toolPos[1];
                tool_Pos[2] = toolPos[2];
            }
            for(int i = 0; i < 6; i++){
                tool_Speed[i] = wRPM*Pitch[i+1]/ratio[i+1];
            }
        }
        void MoveIntime(double dx,double dy,double dz,double drx,double dry,double drz,double sec){
            double x, y, z, rx, ry, rz, a, b;
            MCS_GetCurRefPos(&x, &y, &z, &rx, &ry, &rz, &a, &b);
            SetSpeed(dx/sec,dy/sec,dz/sec,drx/sec,dry/sec,drz/sec);
            std::cout<<"rated: " << dx / sec << ", " << dy / sec << ", " << dz / sec << ", " << drx / sec << ", " << dry / sec << ", " << drz / sec << std::endl;
            MCS_PtP(dx,dy,dz,drx,dry,drz,0,0);
        }
        ~MoveCommander(){
            CloseSystem();
        }
    }; 
}