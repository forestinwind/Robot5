#include "Robot.h"


int InitSystem(double ratio[], double Pitch[], int pusle[], double HLimit[], double LLimit[], int dirReverse[], int wAxisMap[])
{
    SYS_MAC_PARAM      stMacParam;
    SYS_ENCODER_CONFIG stENCConfig;
    SYS_CARD_CONFIG    stCardConfig;
    int m_nAxisNum = 8;
    int nRtn;
    int g_nGroupIndex;
    MCS_SetSysMaxSpeed(1500);//1000mm/s
    nRtn = MCS_CloseSystem();
    //////////////////////////////////////////////////////////////////////////////////////////
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
        wAxisMap[3], wAxisMap[4], wAxisMap[5], wAxisMap[6], wAxisMap[7], 0);
    stCardConfig.wCardType = 4;

    nRtn = MCS_InitSystemEx(1, &stCardConfig, 1);
    if (nRtn != 0)
    {
        return nRtn;
    }
    MCS_SetOverTravelCheck(1, 1, 1, 1, 1, 1, 1, 1, g_nGroupIndex);
    MCS_SetAbsolute(g_nGroupIndex);   // 设为绝对坐标模式
    for (int i = 0; i < (m_nAxisNum); i++)
    {
        MCS_SetServoOn(i); // 使能伺服，电机上电锁住
        MCS_DefinePos(i, 0, g_nGroupIndex); // 将当前位置定义为 0
    }
    return 0;
}

void CloseSystem()
{
    int i;
    for (i = 0; i < (5); i++)
    {
        MCS_SetServoOff(i);
    }
    MCS_CloseSystem();
}
