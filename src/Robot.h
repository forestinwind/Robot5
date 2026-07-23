#pragma once
#include<iostream>

typedef struct {
	double j1;
	double j2;
	double j3;
	double j4; // deg
	double j5; // deg
	double j6; // deg
	double j7;
	double j8;
} JointPositions;

class controlSystem {
    controlSystem() = delete;
public:
	// 初始化系统：减速比、导程、脉冲数、正限位、负限位、电机正反转、轴映射
    static int InitSystem(double ratio[], double Pitch[], int pusle[], double HLimit[], double LLimit[], int dirReverse[], int wAxisMap[]);
	// 关闭系统
    static void CloseSystem();
	// 获取绝对编码器值
    static int GetAbsEncValue(int* absshift23, int channel);
	//设置当前绝对位置
    static int SetAbsPos(int Encvalue0[], double ratio[], double Pitch[], int pusle[], int wAxisMap[]);
	// 设置轴为关节坐标值
	static int DefinePos(int Axis, double pos);
	// 获取关节坐标
	static int  GetCurJPos(JointPositions* pos);
	// 设置点位速度比例
	static double  SetPtPSpeed(double dRatio);
	// 设置点位速度比例
	static int  SetPtPSpeedEx(double dfRatioX, double dfRatioY, double dfRatioZ, double dfRatioU, double dfRatioV, double dfRatioW);
	// ptp点位运动到绝对位置
	static int  MovePTP(JointPositions* pos);
	// 上、下使能伺服
	static void SetServoON(int axis, bool Enable);
	// 停止运行
	static void AbortMotion();
	/*  GetMotionStatus() 返回值
	0 GMS_RUNNING 处于运动状态，尚有运动命令未执行完成
	1 GMS_STOP 处于停止状态，已无库存运动命令
	2 GMS_HOLD 处于暂停状态(因使用者呼叫MCS_HoldMotion)
	3 GMS_DELAYING 处于延迟状态(因使用者呼叫MCS_DelayMotion)
	4 GMS_BLOCKHOLD
	5 GMS_MPGING
	其他失败*/
	static int GetMotionStatus();


	// 获取世界坐标
	//int  GetCurCPos(double* dfCurX, double* dfCurY, double* dfCurZ, double* dfCurRX, double* dfCurRY, double* dfCurRZ, double* dfCurA, double* dfCurB, DWORD* pdwPosture);
	// Jog 点位运行脉冲数
	int  JogPulse(int Axis, int Pulse);
	// Jog 点位运行距离
	int  JogPtpSpace(int Axis, double Space, double speedRatio);
	// 世界坐标运动到绝对位置
	//int  MoveLine(double dfCX, double dfCY, double dfCZ, double dfCRX, double dfCRY, double dfCRZ, double dfCA, DWORD posture);
	// 世界坐标运动XYZR空间轨迹
	//int  ArcXYZ_Aux(double dfX0, double dfY0, double dfZ0, double dfX1, double dfY1, double dfZ1, double dfRX1, double dfRY1, double dfRZ1, DWORD posture);
	// XY 平面设置圆心和RX\RY\RZ目标位置和圆周运动方向
    //int CircleXY(double cx, double cy, double rx, double ry, double rz, BYTE byCirDir, DWORD posture = 0);
	// Jog运动直线距离
	int  JogLineSpace(int Axis, double Space, double Speed);
	// 设置插补速度
	double  SetLineSpeed(double Speed);
	// 获取总线错误代码
	int  GetECatErrorCode();
	// 获取EIO输入值
	void GetEIOIntPutValue(int* Value);
	// 设置EIO输出值
	void SetEIOOutPutValue(int Value);
	// 获取GPIO输入值
	void GetGPIOIntPutValue(int* Value);
	// 设置GPIO输出值
	void SetGPIOOutPutValue(int Value);
	// 获取GPIO输出值
	void GetGPIOOutPutValue(int* Value);
	// 清除报警
	int ClearError();
	void GetCompPos(int32_t* X0, int32_t* X1, int* num, int32_t* A0, int32_t* A1);
	void SetCompEnable(int status, int Speca);
	// 设置加减速时间
	int SetAccTime(double dfAccTime);
	int SetDecTime(double dfDecTime);
	// 获取缓冲区运动指令数量
	int GetCommandCount(int* pnCmdCount);
	// 清空缓冲区运动指令数量
	int ResetCommandIndex();
	// 设置平滑
	int  SetBlending(bool  sw);
    static int testmotion();
};
