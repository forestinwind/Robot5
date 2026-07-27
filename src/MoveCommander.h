#pragma once

#include"Robot.h"
#include<Eigen/Dense>
#include<iostream>
namespace RinnRobotCommander{
    class MoveCommander{
    private:
        static Eigen::Matrix3d eulerZYXToRotation(double rxDeg, double ryDeg, double rzDeg) {
            const double deg2rad = std::acos(-1.0) / 180.0;
            const double rx = rxDeg * deg2rad;
            const double ry = ryDeg * deg2rad;
            const double rz = rzDeg * deg2rad;

            auto Rz = [](double a) { return Eigen::AngleAxisd(a, Eigen::Vector3d::UnitZ()); };
            auto Ry = [](double a) { return Eigen::AngleAxisd(a, Eigen::Vector3d::UnitY()); };

            return (Rz(rz) * Ry(ry)).toRotationMatrix();
        }
        static const Eigen::Vector3d moveDir;
        static Eigen::Vector3d getFlangeLoc(Eigen::Vector3d dir, Eigen::Vector3d p,Eigen::Vector3d seenDir = moveDir){
            Eigen::Matrix3d mat = eulerZYXToRotation(dir.x(), dir.y(), dir.z());
            return p + mat * seenDir;
        }
        static Eigen::Vector3d deFlangeLoc(Eigen::Vector3d dir, Eigen::Vector3d p,Eigen::Vector3d seenDir = moveDir){
            Eigen::Matrix3d mat = eulerZYXToRotation(dir.x(), dir.y(), dir.z());
            return p + mat * -seenDir;
        }
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
            controlSystem::SetPtPSpeedEx(convexSpeed(dx,0),convexSpeed(dy,1),convexSpeed(dz,2),
                convexSpeed(drx,3),convexSpeed(dry,4),convexSpeed(drz,5));
        }
    public:
        MoveCommander(double ratio[], double Pitch[], int pusle[], double HLimit[], double LLimit[], int dirReverse[], int wAxisMap[],double toolPos[3] = nullptr){
            //int nRtn = controlSystem::InitSystem(ratio, Pitch, pusle, HLimit, LLimit, dirReverse, wAxisMap);
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
            JointPositions *pos = new JointPositions();
            controlSystem::GetCurJPos(pos);
            Eigen::Vector3d tipPos = getFlangeLoc(Eigen::Vector3d(rx,ry,rz),Eigen::Vector3d(x,y,z));
            Eigen::Vector3d targetPos = tipPos + Eigen::Vector3d(dx,dy,dz);
            Eigen::Vector3d targetDir = Eigen::Vector3d(rx + drx, ry + dry, rz + drz);
            Eigen::Vector3d targetFlangePos = deFlangeLoc(targetDir,targetPos);
            SetSpeed(dx/sec,dy/sec,dz/sec,drx/sec,dry/sec,drz/sec);
            std::cout<<"rated: " << dx / sec << ", " << dy / sec << ", " << dz / sec << ", " << drx / sec << ", " << dry / sec << ", " << drz / sec << std::endl;
            pos->j1 =dx, pos->j2 = dy, pos->j3 = dz, pos->j4 = drx, pos->j5 = dry, pos->j6 = drz;
            controlSystem::MovePTP(pos);
            delete pos;
        }
        ~MoveCommander(){
            controlSystem::CloseSystem();
        }
    };
    const Eigen::Vector3d MoveCommander::moveDir(1.05,0.69,-504.41);
}