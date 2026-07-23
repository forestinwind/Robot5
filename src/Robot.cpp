#define _USE_MATH_DEFINES
#include "Robot.h"
#include"MCSL_Fun.h"
#include"MCSL.h"
#include"kinematics.h"
#include"EcmDriver.h"
#include<cmath>

#define nAxisNum 8
#define CARD_INDEX 0
#define nGroupIndex 0
int controlSystem::InitSystem(double ratio[], double Pitch[], int pusle[], double HLimit[], double LLimit[], int dirReverse[], int wAxisMap[])
{
    SYS_MAC_PARAM      stMacParam;
    SYS_ENCODER_CONFIG stENCConfig;
    SYS_CARD_CONFIG    stCardConfig;
    int m_nAxisNum = nAxisNum;
    int nRtn;
    int g_nGroupIndex;
    MCS_SetSysMaxSpeed(1500);//1000mm/s
    nRtn = MCS_CloseSystem();
    //////////////////////////////////////////////////////////////////////////////////////////
    //各轴最大安全速度 = (wRPM / 60) ×(dfPitch / dfGearRatio)
    for (WORD wChannel = 0; wChannel < (m_nAxisNum); wChannel++)
    {
        stMacParam.wPosToEncoderDir = dirReverse[wChannel];
        stMacParam.dwPPR = pusle[wChannel];//10000;//8388608;//10000;//131072;
        stMacParam.wRPM = 3000;
        stMacParam.dfPitch = Pitch[wChannel];//40.0;
        stMacParam.dfGearRatio = ratio[wChannel];//5.0;
        stMacParam.dfHighLimit = HLimit[wChannel];
        stMacParam.dfLowLimit = LLimit[wChannel];
        stMacParam.dfHighLimitOffset = 0;
        stMacParam.dfLowLimitOffset = 0;
        stMacParam.wPulseMode = DDA_FMT_PD;
        stMacParam.wPulseWidth = 100;
        stMacParam.wCommandMode = OCM_PULSE;
        stMacParam.wOverTravelUpSensorMode = 2;//  not checking
        stMacParam.wOverTravelDownSensorMode = 2;
        //  set encoder configures
        stENCConfig.wType = ENC_TYPE_AB;
        stENCConfig.wAInverse = _NO_;
        stENCConfig.wBInverse = _NO_;
        stENCConfig.wCInverse = _NO_;
        stENCConfig.wABSwap = _NO_;
        stENCConfig.wInputRate = 4;//  set encoder input rate : x4
        nRtn=MCS_SetMacParam(&stMacParam, wChannel, 0);      //  mechanism parameters are the same for all axes
        //MCS_SetEncoderConfig(&stENCConfig, wChannel, CARD_INDEX);//  encoder configures are the same for all axes
    }
    //  set group parameters
    MCS_CloseAllGroups();
    g_nGroupIndex = MCS_CreateGroup(wAxisMap[0], wAxisMap[1], wAxisMap[2],
        wAxisMap[3], wAxisMap[4], wAxisMap[5], wAxisMap[6], wAxisMap[7], CARD_INDEX);
    nRtn = MCS_SetMirrorAxis(-1, 1, -1, -1, -1, -1, -1, -1, g_nGroupIndex);
    if(nRtn != 0)
    {
        return nRtn;
	}
    stCardConfig.wCardType = 4;
    ECM_SetPdoConfEnable(1);
    nRtn = ECM_NewPdoConfTbl(7);
    nRtn = ECM_SetPdoAsDrive(0, 1);
    nRtn = ECM_SetPdoAsDrive(1, 1);
    nRtn = ECM_SetPdoAsDrive(2, 1);
    nRtn = ECM_SetPdoAsDrive(3, 1);
    nRtn = ECM_SetPdoAsDrive(4, 1);
    nRtn = ECM_SetPdoAsDrive(5, 1);
    nRtn = ECM_SetPdoAsDrive(6, 1);
    nRtn = MCS_InitSystemEx(1, &stCardConfig, 1);

    if (nRtn != 0)
    {
        return nRtn;
    }
    MCS_SetOverTravelCheck(1, 1, 1, 1, 1, 1, 1, 1, g_nGroupIndex);
    ECM_EncEnableLatch(1);
    MCS_SetAccTime(300, g_nGroupIndex);
    MCS_SetDecTime(300, g_nGroupIndex);

    MCS_SetAccType('T', g_nGroupIndex);
    MCS_SetDecType('T', g_nGroupIndex);
    MCS_SetPtPAccType('T', 'T', 'T', 'T', 'T', 'T', 'T', 'T', g_nGroupIndex);
    MCS_SetPtPDecType('T', 'T', 'T', 'T', 'T', 'T', 'T', 'T', g_nGroupIndex);

    MCS_SetAbsolute(g_nGroupIndex);   // 设为绝对坐标模式
    for (int i = 0; i < (m_nAxisNum); i++)
    {
        MCS_SetServoOn(i); // 使能伺服，电机上电锁住
        MCS_DefinePos(i, 0, g_nGroupIndex); // 将当前位置定义为 0
    }
    return 0;
}

void controlSystem::CloseSystem()
{
    int i;
    for (i = 0; i < (nAxisNum); i++)
    {
        MCS_SetServoOff(i);
    }
    MCS_CloseSystem();
}

int controlSystem::GetAbsEncValue(int* absshift23, int channel)
{
    int* pEncHandle = nullptr;
    int ret = ECM_GetObjAddr(0, channel, 1, &pEncHandle);
    if (ret != 1 || pEncHandle == nullptr) {
        return -1;   // 读取失败
    }
    *absshift23 = *pEncHandle;
    return 0;
}

int controlSystem::SetAbsPos(int Encvalue0[], double ratio[], double Pitch[], int pusle[], int wAxisMap[])
{
    int Encvalue[8] = { 0 };   // 全部初始化为0
	double pos[8] = { 0.0 };   // 全部初始化为0.0
    for (int i = 0; i < 8; i++) {
        if (wAxisMap[i] == -1) continue;   // 跳过未使用的轴

        if (GetAbsEncValue(&Encvalue[i], i) != 0) {
            return -1;
        }

        // 计算当前物理位置 (单位：mm)
        pos[i] = (double)(Encvalue[i] - Encvalue0[i]) / pusle[i] * Pitch[i] / ratio[i];
    }
	for (int i = 0; i < 8; i++) {
        if (wAxisMap[i] == -1) continue;   // 跳过未使用的轴
        MCS_DefinePos(i, pos[wAxisMap[i]], 0);   // 将当前位置定义为 pos[i]
    }
    return 0;
}

int controlSystem::DefinePos(int Axis, double pos)
{
    return MCS_DefinePos(Axis, pos, nGroupIndex);
}

int controlSystem::GetCurJPos(JointPositions* pos)
{
	int Status = 0;
    Status = MCS_GetCurPos(&pos->j1, &pos->j2, &pos->j3, &pos->j4, &pos->j5, &pos->j6, &pos->j7, &pos->j8, nGroupIndex);
    pos->j4 = pos->j4 * 180 / M_PI;
    pos->j5 = pos->j5 * 180 / M_PI;
    pos->j6 = pos->j6 * 180 / M_PI;
    return Status;
}

double controlSystem::SetPtPSpeed(double dRatio)
{
    return MCS_SetPtPSpeed(dRatio, nGroupIndex);
}

int controlSystem::SetPtPSpeedEx(double dfRatioX, double dfRatioY, double dfRatioZ, double dfRatioU, double dfRatioV, double dfRatioW)
{
    return MCS_SetPtPSpeedEx(dfRatioX, dfRatioY, dfRatioZ, dfRatioU, dfRatioV, dfRatioW, 0, 0, nGroupIndex);
}

int controlSystem::MovePTP(JointPositions* pos)
{
    if(pos==nullptr)
        return -1;
    return MCS_PtP_V6(pos->j1, pos->j2, pos->j3, pos->j4, pos->j5, pos->j6, 0, 0, nGroupIndex);
}

int controlSystem::testmotion()
{
	int nRtn;
    //MCS_CustomMotionEx
    nRtn = MCS_SetAccType('T', 0); //轨迹规划设置为 T 型曲线
    nRtn = MCS_SetDecType('T', 0);
    nRtn = MCS_SetAccTime(100, 0); //设置加速度时间
    nRtn = MCS_SetDecTime(100, 0);
    nRtn = MCS_SetFeedSpeed(10, 0); //设置进给速度
    nRtn = MCS_Line(10, 10, 0, 0, 0, 0, 0, 0, 0); //XY 直线插补运动到点（10,10），单位：mm
    nRtn = MCS_CircleXY(20, 20, 0, 0); //XY 平面以点（20,20）为圆心画圆
    //nRtn = MCS_ArcXY(5, 20, 3, 30, 0); //XY 平面以当前点为起点，经过点(5,20)走圆弧插补到达目标点（3, 30）
    nRtn = MCS_Line(20, 20, 0, 0, 0, 0, 0, 0, 0); //XY 平面直线插补
    //nRtn = MCS_CircleXY(20, 5, 30, 3); //在 XY 平面，从当前点经点（20，5）走圆弧插补到目标点（3，30）
    nRtn = MCS_Line(-10, -10, 10, 0, 0, 0, 0, 0, 0); //在 XY 平面走直线插补回到点（10,10）,单位：mm
    return 0;
}
