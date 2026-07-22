#ifndef __KINEMATICS_H__
#define __KINEMATICS_H__

#ifdef __cplusplus
	extern "C" {
#endif

	#include <windows.h>

	typedef unsigned long				DWORD;
	typedef unsigned short				WORD;
	typedef unsigned char				BYTE;
//	typedef int							BOOL;


//////////////////////////////////////////////////////////////////////////////
// Definitions of Calling Convention & Storage-Class Attributes


#define ROBOT_V6_CALL		__stdcall

#ifdef AMCARMROBOT_EXPORTS
	#define ROBOT_V6_API __declspec(dllexport)
#else
	#define ROBOT_V6_API __declspec(dllimport)
#endif



//////////////////////////////////////////////////////////////////////////////

extern WORD MountType ;
// Type definitions
extern int RbtStatus;
extern WORD RobotType[12*8];


// D-H parameters
typedef struct _SCARA_PARAM
{
	double  a1;
	double  a2;
	double  d1;
	double  d4;
} SCARA_PARAM;

typedef struct _SCARA5DOF_PARAM
{
	double  a1;
	double  a2;
	double  a5;
	double  d1;
	double  d4;
} SCARA5DOF_PARAM;
/////////////////////////////////////
typedef struct _SCARA6DOF_PARAM        //add 20221106
{
	double  a2;
	double  d4;
	double  d6;
} SCARA6DOF_PARAM;
////////////20200516-zgx////////////
typedef struct _SCARA2_PARAM
{
	double  a1;
	double  a2;
	double  a5;
	double  d1;
	double  d4;
} SCARA2_PARAM;

typedef struct _SCARA2_PARAM_EX
{
	double J34_CoupleRatio;
	struct TOOL
	{
		double  X_Offset;
		double  Y_Offset;
		double  Z_Offset;
		double  RX_Offset;
		double  RY_Offset;
		double  RZ_Offset;
	}Tool;
	struct WORK
	{
		double  X_Offset;
		double  Y_Offset;
		double  Z_Offset;
		double  RX_Offset;
		double  RY_Offset;
		double  RZ_Offset;
	}Work;
} SCARA2_PARAM_EX;
//////////////////////////////////////////////////////

typedef struct _DELTA_PARAM
{
	double  f;
	double  e;
	double  rf;
	double  re;
} DELTA_PARAM;

typedef struct _STACKER_PARAM
{
	double  a0;
	double  a1;
	double  a2;
	double  a3;
	double  a4;
	double  a5;
	double  origin_offset_x;
} STACKER_PARAM;

typedef struct _DELTA5DOF_PARAM
{
	double  l5;
	double  l6;
	double  l7;
	double  l8;
	double  l9;
	double  l10;
	//double  origin_offset_z;
} DELTA5DOF_PARAM;

typedef struct _CART5DOF_PARAM
{
	double  d4;
	double  d5;
} CART5DOF_PARAM;

typedef struct _DH6DOF_PARAM
{
	double  a1;
	double  a2;
	double  a3;
	double  d3;
	double  d4;
	double  d6;
	double  origin_offset_z;
} DH6DOF_PARAM;

typedef struct _BYD_PARAM
{
	double  a1;
	double  a2;
	double  a3;
	double  a5;
	double  d4;
	double  d6;
	double  origin_offset_z;
} BYD_PARAM;

typedef struct _YT_PARAM
{
	double  a2;
	double  a3;
	double  d1;
	double  d2;
	double  d3;
	double  d4;
	double  d5;
	double  d6;
	double  origin_offset_z;
} YT_PARAM;

typedef struct _PUNCH_PARAM
{
	double  a1;
	double  a2;
	double  d1;
	double  d4;
} PUNCH_PARAM;

typedef struct _DH_PARAM
{
	double  a0;
	double  a1;
	double  a2;
	double  a3;
	double  a4;
	double  a5;
	double  a6;//tool_offset

	double  d1;
	double  d2;
	double  d3;
	double  d4;
	double  d5;
	double  d6;

	double  origin_offset_x;
	double  origin_offset_z;
} DH_PARAM;

typedef struct _DH_PARAM_EX
{
	double J34_CoupleRatio;
	double J45_CoupleRatio;
	double J56_CoupleRatio;
	double J46_CoupleRatio;
	struct TOOL
	{
		double  X_Offset;
		double  Y_Offset;
		double  Z_Offset;
		double  RX_Offset;
		double  RY_Offset;
		double  RZ_Offset;
	}Tool;
	struct WORK
	{
		double  X_Offset;
		double  Y_Offset;
		double  Z_Offset;
		double  RX_Offset;
		double  RY_Offset;
		double  RZ_Offset;
	}Work;
} DH_PARAM_EX;

typedef struct _TEACH_POINT
{
	double  x; // mm
	double  y; // mm
	double  z; // mm

	double  rx; // rad
	double  ry; // rad
	double  rz; // rad
} TEACH_POINT;

///////////zgx20200729 for comotion////////////
typedef struct _TEACH_CPOINT
{
	double  x; // mm
	double  y; // mm
	double  z; // mm

	double  rx; // rad
	double  ry; // rad
	double  rz; // rad

	double j7;  //rad
	double j8;  //rad
} TEACH_CPOINT;


typedef struct _CALIBDATA
{
	// cartes coordination
	double x;
	double y;
	double z;
}CALIBDATA;

typedef struct _TRANS_RULES
{
	double  U1;
	double  U2;
	double  U3;

	double  V1;
	double  V2;
	double  V3;

	double  W1;
	double  W2;
	double  W3;

	double  D1;
	double  D2;
	double  D3;
} TRANS_RULES;
////////////////////////////////////////////////////
typedef struct _TEACH_JPOINT
{
	double  q1; // rad
	double  q2; // rad
	double  q3; // rad
	double  q4; // rad
	double  q5; // rad
	double  q6; // rad
} TEACH_JPOINT;

typedef struct _TEACH_ERROR
{
	double  j1; // mm
	double  j2; // mm

	double  a1; // rad
	double  a2; // rad
} TEACH_ERROR;

typedef struct _CALIB_ERROR
{
	double  j1; // rad
	double  j2; // rad
	double  j3; // rad
	double  j4; // rad
	double  j5; // rad
	double  j6; // rad

	double  a0; //mm
	double  a1; //mm
	double  a2; //mm
	double  a3; //mm
	double  a4; //mm
	double  a5; //mm

	double  d1; //mm
	double  d2; //mm
	double  d3; //mm
	double  d4; //mm
	double  d5; //mm
	double  d6; //mm

	double  Tool;
	double  Tx; //mm, == Tool * cos(j6 + q6)
	double  Ty; //mm, == Tool * sin(j6 + q6)
	double  Tz; //mm, == d6
} CALIB_ERROR;

typedef struct _Cal_ERROR
{
	double  j1; // rad
	double  j2; // rad
	double  j3; // rad
	double  j4; // rad
	double  j5; // rad
	double  j6; // rad

	double  Tx; //mm
	double  Ty; //mm
	double  Tz; //mm
} CAL_ERROR;

typedef struct _SCARA_CALIB
{

	double  L1; //mm the 1st arm length
	double  L2; //mm the 2nd arm length
	double  Dtheta; //rad, the error of theta2

} SCARA_CALIB;

typedef struct _TEACH_LRJ   //teach joint point of scara; left hand and right hand
{
	double  q1; // rad, theta1
	double  q2; // rad, theta2
} TEACH_LRJ;

typedef struct _SCARATOOL
{
    double Tx;
    double Ty;
    double TRz;
}SCARA_T;
//////////////////////////20220415--GPIOqueue///////////////////////
typedef struct QueueGPIO
{
	int   DelayTime;
	int   Mode;
}QGPIO;
//////////////////////////////////////////////////////////////////////////////

/////////////////////////20221028--记录group的轴号信息//////////////////////////
typedef struct GroupInfo
{
	WORD wGroupIndex;
	int j1toch;
	int j2toch;
	int j3toch;
	int j4toch;
	int j5toch;
	int j6toch;
	int j7toch;
	int j8toch;
}GROUPINFO;
///////////////////////////////////////////////////////////////////////////
// Exported functions

// D-H parameters

ROBOT_V6_API void   ROBOT_V6_CALL rbt_SetScaraParam(const SCARA_PARAM& dhp, WORD wGroupIndex = 0);
ROBOT_V6_API void   ROBOT_V6_CALL rbt_GetScaraParam(SCARA_PARAM* pdhp, WORD wGroupIndex = 0);
ROBOT_V6_API void   ROBOT_V6_CALL rbt_SetStackerParam(const STACKER_PARAM& dhp, WORD wGroupIndex = 0);
ROBOT_V6_API void   ROBOT_V6_CALL rbt_GetStackerParam(STACKER_PARAM* pdhp, WORD wGroupIndex = 0);
ROBOT_V6_API void   ROBOT_V6_CALL rbt_Set5DofScaraParam(const SCARA5DOF_PARAM& dhp, WORD wGroupIndex = 0);
ROBOT_V6_API void   ROBOT_V6_CALL rbt_Get5DofScaraParam(SCARA5DOF_PARAM* pdhp, WORD wGroupIndex = 0);
ROBOT_V6_API void   ROBOT_V6_CALL rbt_Set6DofScaraParam(const SCARA6DOF_PARAM& dhp, WORD wGroupIndex = 0);
ROBOT_V6_API void   ROBOT_V6_CALL rbt_Get6DofScaraParam(SCARA6DOF_PARAM* pdhp, WORD wGroupIndex = 0);
ROBOT_V6_API void   ROBOT_V6_CALL rbt_SetDeltaParam(const DELTA_PARAM& dhp, WORD wGroupIndex = 0);
ROBOT_V6_API void   ROBOT_V6_CALL rbt_GetDeltaParam(DELTA_PARAM* pdhp, WORD wGroupIndex = 0);
ROBOT_V6_API void   ROBOT_V6_CALL rbt_Set5DofDeltaParam(const DELTA_PARAM& dhp, WORD wGroupIndex = 0);
ROBOT_V6_API void   ROBOT_V6_CALL rbt_Get5DofDeltaParam(DELTA_PARAM* pdhp, WORD wGroupIndex = 0);
ROBOT_V6_API void   ROBOT_V6_CALL rbt_Set6DofDHParam(const DH6DOF_PARAM& dhp, WORD wGroupIndex = 0);
ROBOT_V6_API void   ROBOT_V6_CALL rbt_Get6DofDHParam(DH6DOF_PARAM* pdhp, WORD wGroupIndex = 0);
ROBOT_V6_API void   ROBOT_V6_CALL rbt_Set6DofDHParamEx(const DH_PARAM_EX& dhp, WORD wGroupIndex = 0);
ROBOT_V6_API void   ROBOT_V6_CALL rbt_Get6DofDHParamEx(DH_PARAM_EX* pdhp, WORD wGroupIndex = 0);
ROBOT_V6_API void   ROBOT_V6_CALL rbt_SetBYDParam(const BYD_PARAM& dhp, WORD wGroupIndex = 0);
ROBOT_V6_API void   ROBOT_V6_CALL rbt_GetBYDParam(BYD_PARAM* pdhp, WORD wGroupIndex = 0);
ROBOT_V6_API void   ROBOT_V6_CALL rbt_Set5DofCartParam(const CART5DOF_PARAM& dhp, WORD wGroupIndex = 0);
ROBOT_V6_API void   ROBOT_V6_CALL rbt_Get5DofCartParam(CART5DOF_PARAM* pdhp, WORD wGroupIndex = 0);

ROBOT_V6_API void   ROBOT_V6_CALL rbt_SetYTParam(const YT_PARAM& dhp, WORD wGroupIndex = 0);
ROBOT_V6_API void   ROBOT_V6_CALL rbt_GetYTParam(YT_PARAM* pdhp, WORD wGroupIndex = 0);

ROBOT_V6_API void   ROBOT_V6_CALL rbt_SetDHParam(const DH_PARAM& dhp, WORD wGroupIndex = 0);
ROBOT_V6_API void   ROBOT_V6_CALL rbt_GetDHParam(DH_PARAM* pdhp, WORD wGroupIndex = 0);
ROBOT_V6_API void   ROBOT_V6_CALL rbt_SetDHParamEx(const DH_PARAM_EX& dhp, WORD wGroupIndex = 0);
ROBOT_V6_API void   ROBOT_V6_CALL rbt_GetDHParamEx(DH_PARAM_EX* pdhp, WORD wGroupIndex = 0);
ROBOT_V6_API void   ROBOT_V6_CALL rbt_SetPunchParam(const PUNCH_PARAM& dhp, WORD wGroupIndex = 0);
ROBOT_V6_API void   ROBOT_V6_CALL rbt_GetPunchParam(PUNCH_PARAM* pdhp, WORD wGroupIndex = 0);

ROBOT_V6_API void   ROBOT_V6_CALL rbt_SetSCARA2Param(const SCARA2_PARAM& dhp, WORD wGroupIndex = 0);
ROBOT_V6_API void   ROBOT_V6_CALL rbt_GetSCARA2Param(SCARA2_PARAM* pdhp, WORD wGroupIndex = 0);
ROBOT_V6_API void   ROBOT_V6_CALL rbt_SetSCARA2ParamEx(const SCARA2_PARAM_EX& dhp, WORD wGroupIndex = 0);
ROBOT_V6_API void   ROBOT_V6_CALL rbt_GetSCARA2ParamEx(SCARA2_PARAM_EX* pdhp, WORD wGroupIndex = 0);

// Customize kinematics transformation rules
ROBOT_V6_API int    ROBOT_V6_CALL rbt_SetKinematicTrans(BOOL bSet, WORD wGroupIndex = 0);

// Kinematic transformation

ROBOT_V6_API int    ROBOT_V6_CALL rbt_FwdKinematics_V6(
			const double* pdfJntPos, // [in, size_is(6)]
			double* pdfCrtPos,       // [out, size_is(6)]
			DWORD* pdwPosture,       // [out]
			WORD wGroupIndex = 0
			);

ROBOT_V6_API int    ROBOT_V6_CALL rbt_InvKinematics_V6(
			const double* pdfCrtPos, // [in, size_is(6)]
			DWORD dwPosture,         // [in]
			double* pdfJntPos,       // [out, size_is(6)]
			WORD wGroupIndex = 0
			);

ROBOT_V6_API int    ROBOT_V6_CALL rbt_InvKinematics_Scara(const double* pdfCrtPos,
											DWORD dwPosture,
											double* pdfJntPos,
											WORD wGroupIndex /*=0*/);

// Retrieve current JOINT/CARTESIAN positions
ROBOT_V6_API int    ROBOT_V6_CALL rbt_GetCurJPos(
			double *j0,
			double *j1,
			double *j2,
			double *j3,
			double *j4,
			double *j5,
			double *j6,
			double *j7,
			WORD wGroupIndex = 0
			);

ROBOT_V6_API int    ROBOT_V6_CALL rbt_GetCurCPos(
			double *x,
			double *y,
			double *z,
			double *rx,
			double *ry,
			double *rz,
			double *a,
			double *b,
			DWORD *pdwPosture,
			WORD wGroupIndex = 0
			);


//nType = 0: Stacker(LP130/LP180), 
//nType = 1: Stacker2(ShanDong), 
//nType = 2: 4-Dof Delta, 
//nType = 3: 5-Dof Delta, 
//nType = 4: 4-Dof Scara, 
//nType = 5: 5-Dof Scara, 
//nType = 6: 6-Dof DH Robot(GR985), 
//nType = 7: 6-Dof DH Robot(BYD Wirst Offset), 
//nType = 8: 5-Dof Cart Robot(3 + 2 Mechine Tool), 
//nType = 9: 4-Dof Cart Robot(Stacker3), 
//nType = 10: 6-Dof Robot(Stacker4), 
//nType = 11: 6-Dof Robot(Stacker5), 
//nType = 12: 4-Dof Scara Robot(Punch),
//nType = 13: 6-Dof DH Robot(GR985) with DH_a3 & DH_d3, 
//nType = 14: Scara5Dof, INV2, Robottype=5
//nType = 15: Scara2 5-Dof Scara    ----20200516
//nType = 16: YT 6-DOF DH robot
//nType = 17: 5-Dof Scara Robot(Punch), same as type=12, only one more axis which track same as the 2nd motor added
//nType = 18: scara for HuiKong, used when the tool mounted on the second arm
//nType = 19: 6-Dof scara(the scara with the three wrist axis)---20221106
//nType Delault = 0 
/////////////////////mount type added by zgx 20201125//////////////////////
//wMountType = 0: stand_up mount
//wMountType = 1: inverted mount
//wMountType = 2: left side mount
//wMountType = 3: right side mount
//wMountType = 4: front mount
//wMountType = 5: back mount
ROBOT_V6_API void   ROBOT_V6_CALL rbt_SetRobotType(int nType, WORD wGroupIndex = 0, WORD wMountType = 0);

// Cone Motion
ROBOT_V6_API int	ROBOT_V6_CALL rbt_Cone_V6(
			double dfBaseVectX,
			double dfBaseVectY,
			double dfBaseVectZ,
			double dfTheta, // [in] degree, +/- stands for direction
			WORD wGroupIndex = 0
			);


// XY-Perpendicular RX/RY/RZ
ROBOT_V6_API int	ROBOT_V6_CALL rbt_RX_V6(
			double dfTheta, // [in] degree, +/- stands for direction
			WORD wGroupIndex = 0
			);

ROBOT_V6_API int	ROBOT_V6_CALL rbt_RY_V6(
			double dfTheta, // [in] degree, +/- stands for direction
			WORD wGroupIndex = 0
			);

ROBOT_V6_API int	ROBOT_V6_CALL rbt_RZ_V6(
			double dfTheta, // [in] degree, +/- stands for direction
			WORD wGroupIndex = 0
			);

////////////////////////////////////////////////////
//将停留时间改成左右可单独设置
////////////////////////////////////////////////////
ROBOT_V6_API int    ROBOT_V6_CALL rbt_LineWaves(
							double dfX,
							double dfY,
							double dfZ,
							double dfRx,
							double dfRy,
							double dfRz,
							double a,   //
							double b,   //add by zgx 20200821
							double dfFrequency,
							double dfAmplitude,
							double dfDelayTimeL,
							double dfDelayTimeR,
							DWORD posture,
							WORD wGroupIndex = 0,
							DWORD dwAxisMask = 0x3F
							);
ROBOT_V6_API int    ROBOT_V6_CALL rbt_LineWave(
							double dfX,
							double dfY,
							double dfZ,
							double dfRx,
							double dfRy,
							double dfRz,
							double dfFrequency,
							double dfAmplitude,
							double dfDelayTime,
							DWORD posture,
							WORD wGroupIndex = 0,
							DWORD dwAxisMask = 0x3F
							);
////////////////////////////////////////////////////
//1.停留时间左右可单独设置
//2.运动和摆动可以一起暂停和停止
//3.当上位机发hold、continue、stop指令时，同时调用rbt_SetMotionStatus()将状态传给custommotion
//4.状态定义 #define HOLDING     1
//        #define CONTINUE    2
//        #define STOP        3
////////////////////////////////////////////////////
ROBOT_V6_API int    ROBOT_V6_CALL rbt_LineWaveEx(
							double dfX,
							double dfY,
							double dfZ,
							double dfRx,
							double dfRy,
							double dfRz,
							double a,    //
							double b,    //add by zgx 20200821
							double dfFrequency,
							double dfAmplitude,
							double dfDelayTimeL,
							double dfDelayTimeR,
							DWORD posture,
							WORD wGroupIndex = 0,
							DWORD dwAxisMask = 0x3F
							);
///////////////////////////////////////////////////////////////////////////
ROBOT_V6_API int    ROBOT_V6_CALL rbt_ArcWave(
							double x0, // 1st ref. point for x axis
							double y0, // 1st ref. point for y axis
							double z0, // 1st ref. point for z axis
							double x1, // target point for x axis
							double y1, // target point for y axis
							double z1, // target point for z axis
							double rx, // target point for x orientation
							double ry, // target point for y orientation
							double rz, // target point for z orientation
							double a,
							double b,
							double dfFrequency,
							double dfAmplitude,
							double dfDelayTime,
							DWORD posture,
							WORD  wGroupIndex = 0,
							DWORD dwAxisMask = 0x3F
							);

ROBOT_V6_API int    ROBOT_V6_CALL rbt_CircleWave(
							double x0, // 1st ref. point for x axis
							double y0, // 1st ref. point for y axis
							double z0, // 1st ref. point for z axis
							double x1, // 2nd ref. point for x axis
							double y1, // 2nd ref. point for y axis
							double z1, // 2nd ref. point for z axis
							double rx, // target point for x orientation
							double ry, // target point for y orientation
							double rz, // target point for z orientation
							double a,
							double b,
							double dfFrequency,
							double dfAmplitude,
							double dfDelayTime,
							DWORD posture,
							WORD  wGroupIndex = 0,
							DWORD dwAxisMask = 0x3F
							);
/////////////////////////////////////////////////////////////////////////
//add left and right delay time 20201201
/////////////////////////////////////////////////////////////////////////
ROBOT_V6_API int    ROBOT_V6_CALL rbt_ArcWaves(
							double x0, // 1st ref. point for x axis
							double y0, // 1st ref. point for y axis
							double z0, // 1st ref. point for z axis
							double x1, // target point for x axis
							double y1, // target point for y axis
							double z1, // target point for z axis
							double rx, // target point for x orientation
							double ry, // target point for y orientation
							double rz, // target point for z orientation
							double a,
							double b,
							double dfFrequency,
							double dfAmplitude,
							double dfDelayTimeL,
							double dfDelayTimeR,
							DWORD posture,
							WORD  wGroupIndex = 0,
							DWORD dwAxisMask = 0x3F
							);
ROBOT_V6_API int    ROBOT_V6_CALL rbt_ArcWaveEx(
							double x0, // 1st ref. point for x axis
							double y0, // 1st ref. point for y axis
							double z0, // 1st ref. point for z axis
							double x1, // target point for x axis
							double y1, // target point for y axis
							double z1, // target point for z axis
							double rx, // target point for x orientation
							double ry, // target point for y orientation
							double rz, // target point for z orientation
							double a,
							double b,
							double dfFrequency,
							double dfAmplitude,
							double dfDelayTimeL,
							double dfDelayTimeR,
							DWORD posture,
							WORD  wGroupIndex = 0,
							DWORD dwAxisMask = 0x3F
							);

ROBOT_V6_API int    ROBOT_V6_CALL rbt_CircleWaves(
							double x0, // 1st ref. point for x axis
							double y0, // 1st ref. point for y axis
							double z0, // 1st ref. point for z axis
							double x1, // 2nd ref. point for x axis
							double y1, // 2nd ref. point for y axis
							double z1, // 2nd ref. point for z axis
							double rx, // target point for x orientation
							double ry, // target point for y orientation
							double rz, // target point for z orientation
							double a,
							double b,
							double dfFrequency,
							double dfAmplitude,
							double dfDelayTimeL,
							double dfDelayTimeR,
							DWORD posture,
							WORD  wGroupIndex = 0,
							DWORD dwAxisMask = 0x3F
							);
////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

ROBOT_V6_API int    ROBOT_V6_CALL rbt_SetToolCordinate(
							          TEACH_POINT p1,
							          TEACH_POINT p2,
							          TEACH_POINT p3,
							          TEACH_POINT p4,
							          TEACH_POINT p5,
							          TEACH_POINT p6,
									  WORD wGroupIndex = 0);

ROBOT_V6_API TEACH_POINT    ROBOT_V6_CALL rbt_GetToolCordinate(
							          TEACH_JPOINT p1,
							          TEACH_JPOINT p2,
							          TEACH_JPOINT p3,
							          TEACH_JPOINT p4,
							          TEACH_JPOINT p5,
							          TEACH_JPOINT p6,
									  WORD wGroupIndex = 0);
////////////////////add by zgx 20200601///////////////////////////////////

ROBOT_V6_API TEACH_POINT    ROBOT_V6_CALL rbt_GetToolCordinateEx(
							          TEACH_JPOINT p1,
							          TEACH_JPOINT p2,
									  WORD wGroupIndex = 0);

ROBOT_V6_API TEACH_ERROR    ROBOT_V6_CALL rbt_GetScaraCompensator(
							          TEACH_POINT r1, //reference point A in Cart unit
							          TEACH_POINT r2, //reference point B in Cart unit
							          TEACH_POINT r3, //reference point C in Cart unit
							          TEACH_POINT r4, //reference point D in Cart unit
							          TEACH_JPOINT p1, //Teaching point A in Joint unit
							          TEACH_JPOINT p2, //Teaching point B in Joint unit
							          TEACH_JPOINT p3, //Teaching point C in Joint unit
							          TEACH_JPOINT p4, //Teaching point D in Joint unit
									  WORD    wGroupIndex = 0);

////////////////////////////////
//scara calib--zgx20210310
////////////////////////////////
ROBOT_V6_API SCARA_CALIB    ROBOT_V6_CALL rbt_GetScaraCompensatorEx(
							          TEACH_LRJ *p1,
									  double     d,
									  WORD    wGroupIndex =0);

ROBOT_V6_API CALIB_ERROR    ROBOT_V6_CALL rbt_GetARCompensator(
							          TEACH_JPOINT *p1,
									  WORD    wTotalPoint = 20,
									  WORD    wGroupIndex =0);

//////////////modify 20200529 by zgx///////////////////////////////
ROBOT_V6_API CAL_ERROR    ROBOT_V6_CALL rbt_GetARCompensatorEx(
							          TEACH_JPOINT *p1,
									  WORD    wTotalPoint = 8,
									  WORD    wGroupIndex =0);

/////////////////////////////////////////////////////////////////////
//added by zgx 2019-8-15
/////////////////////////////////////////////////////////////////////
ROBOT_V6_API int   ROBOT_V6_CALL   rbt_Line_V6(
		                                        double x,
		                                        double y,
		                                        double z,
		                                        double rx,
												double ry,
												double rz,
												double a,
												double b,
												double x0,
												double y0,
												double z0,
												double rx0,
												double ry0,
												double rz0,
												double a0,
												double b0,
												double dfFedSpd,
												double dfAccT,               //add 20221118
										        double dfDecT,
		                                        DWORD posture = 0,
		                                        WORD wGroupIndex = 0
		                                        );


ROBOT_V6_API double ROBOT_V6_CALL rbt_SetFeedSpeed_Ex( double dfFeedSpeed, WORD wGroupIndex = 0);
ROBOT_V6_API int ROBOT_V6_CALL  rbt_RY_V6_R(double dfTheta, WORD wGroupIndex = 0);//////20210120zgx
ROBOT_V6_API int ROBOT_V6_CALL  rbt_RZ_V6_R(double dfTheta, WORD wGroupIndex = 0);//////20211109zgx
ROBOT_V6_API void ROBOT_V6_CALL rbt_GetVersion(char *strVersion);
/////////2019-10-17//////////////
/////////////////////////////////////////////////////
//当上位机发hold、continue、stop指令时，同时调用rbt_SetMotionStatus()将状态传给custommotion
//状态定义         #define HOLDING     1
//        #define CONTINUE    2
//        #define STOP        3
////////////////////////////////////////////////////
ROBOT_V6_API int    ROBOT_V6_CALL  rbt_SetMotionStatus(int rbtStatus, WORD wGroupIndex = 0);
ROBOT_V6_API int    ROBOT_V6_CALL  rbt_GetMotionStatus(WORD wGroupIndex = 0);

///////////////2019-11-20////////////////////////////
ROBOT_V6_API void    ROBOT_V6_CALL CalOrient(
		const double* pdfStartPos,       //current CPOS[6]:X, Y, Z, Rx, Ry, Rz   (in)
		double* vec_normal,              //unit normal vector                    (in)
		double theta,                    //angle of rotation                     (in)
		double* endorient        //required orientation[3]: Rx/Ry/Rz            (out)
		);

///////////////////////////20200729 zgx comotion////////////////////////////////////////

ROBOT_V6_API int    ROBOT_V6_CALL rbt_CoArc(
							double x0, // 1st ref. point for x axis
							double y0, // 1st ref. point for y axis
							double z0, // 1st ref. point for z axis
							double a0, // 1st ref. point for j7 (rad)
							double b0, // 1st ref. point for j8  (rad)
							double x1, // target point for x axis
							double y1, // target point for y axis
							double z1, // target point for z axis
							double rx, // target point for x orientation
							double ry, // target point for y orientation
							double rz, // target point for z orientation
							double a, //rad
							double b,   //rad
							WORD axisA,          //0: no use; 1: 7a-->1 axis of positioner; 2: 7a-->2 axis of positioner
							WORD axisB,         //0: no use; 1: 8b-->1 axis of positioner; 2: 8b-->2 axis of positioner
							TRANS_RULES trM1,   //inclination axis transmatrix
							TRANS_RULES trM2,   //rotation axis transmatrix
							DWORD posture,
							WORD  wGroupIndex = 0,
							DWORD dwAxisMask = 0xFF
							);
ROBOT_V6_API int    ROBOT_V6_CALL rbt_CoCircle(
							double x0, // 1st ref. point for x axis
							double y0, // 1st ref. point for y axis
							double z0, // 1st ref. point for z axis
							double a0, // 1st ref. point for a axis
							double b0, // 1st ref. point for b axis
							double x1, // 2nd ref. point for x axis
							double y1, // 2nd ref. point for y axis
							double z1, // 2nd ref. point for z axis
							double rx, // target point for x orientation
							double ry, // target point for y orientation
							double rz, // target point for z orientation
							double a,
							double b,
							WORD axisA,          //0: no use; 1: 7a-->1 axis of positioner; 2: 7a-->2 axis of positioner
							WORD axisB,         //0: no use; 1: 8b-->1 axis of positioner; 2: 8b-->2 axis of positioner
							TRANS_RULES trM1,   //inclination axis transmatrix
							TRANS_RULES trM2,   //rotation axis transmatrix
							DWORD posture,
							WORD  wGroupIndex = 0,
							DWORD dwAxisMask = 0xFF
);
//ROBOT_V6_API int    ROBOT_V6_CALL rbt_CoLine(
//		                    TEACH_CPOINT* p,   //the two teach C points of the Line (start point and end point)
//		                    WORD wGroupIndex = 0
//							);
ROBOT_V6_API int    ROBOT_V6_CALL rbt_CoLine(
		                    double x,
		                    double y,
		                    double z,
		                    double rx,
		                    double ry,
		                    double rz,
		                    double a,
		                    double b,
							WORD axisA,          //0: no use; 1: 7a-->1 axis of positioner; 2: 7a-->2 axis of positioner
							WORD axisB,         //0: no use; 1: 8b-->1 axis of positioner; 2: 8b-->2 axis of positioner
							TRANS_RULES trM1,   //inclination axis transmatrix
							TRANS_RULES trM2,   //rotation axis transmatrix
		                    DWORD posture = 0,
		                    WORD wGroupIndex = 0,
		                    DWORD dwAxisMask = 0xFF);

///////////input three points for calculation of J7/J8 axis coordinate, return the transfer matrix to World coord////////////////
ROBOT_V6_API void ROBOT_V6_CALL CalPMatrix(
		                    CALIBDATA* p,     //three points for calib J7/J8 axis coordinate when j7=j8=0
							TRANS_RULES* trM, //out: matrix of size(3,4)
		                    WORD wGroupIndex = 0
							);
///////////cal TransM7 & TransM8 (Global Variables)/////////////////
//ROBOT_V6_API void ROBOT_V6_CALL Trans_M(
//		                    CALIBDATA* p,
//		                    WORD wGroupIndex = 0
//		                    );
//////////calc the transfer matrix from Base Coord to World Coord////////////
//void ROBOT_V6_CALL CoM_Fwk(
//		                   TRANSFORMATION_RULES& M7,  //in: transfer Matrix of axis J7 when q7=0
//		                   TRANSFORMATION_RULES& M8,  //in: transfer Matrix of axis J8 when q8=0
//		                   double q7,   //in: current angle of axis J7
//		                   double q8,   //in: current angle of axis J8
//						   TRANSFORMATION_RULES* tr,  //out: matrix of size(3,4)
//		                   WORD wGroupIndex = 0
//		                   );

///////////////vec_str rotate by vec_normal///////////////////////
void    ROBOT_V6_CALL VecRot(
		                  const double* vec_str,
		                  double* vec_normal,
		                  double theta,
	                      double* vec_new
		                  );

/////////////////////////////////////////////////////////////////////
//line + circle + 7\8 axis comotion  add by zgx20200918
////////////////////////////////////////////////////////////////////
ROBOT_V6_API int    ROBOT_V6_CALL rbt_CoLineCircle(
		                  double x, //target point
		                  double y,
		                  double z,
		                  double rx,
		                  double ry,
		                  double rz,
		                  double a,
		                  double b,
		                  double R, //the circle radius
		                  double d, //forward distance
						  WORD axisA,          //0: no use; 1: 7a-->the 1st axis of positioner; 2: 7a-->the 2nd axis of positioner
						  WORD axisB,         //0: no use; 1: 8b-->the 1st axis of positioner; 2: 8b-->the 2nd axis of positioner
						  TRANS_RULES trM1,   //inclination axis transmatrix
						  TRANS_RULES trM2,   //rotation axis transmatrix
		                  DWORD posture = 0,
		                  WORD wGroupIndex = 0,
		                  DWORD dwAxisMask = 0xFF
		                  );

//////////////////////////////////////////////////////////////////////////////////////////////////////
//地轨协同： line + arc + circle
//7 axis is the rack axis, and 8 axis could be selected as incline/rotate/Null
//////////////////////////////////////////////////////////////////////////////////////////////////////
ROBOT_V6_API void   ROBOT_V6_CALL RackVector(CALIBDATA *p, double* Vect, WORD wGroupIndex=0);//20201120
ROBOT_V6_API int    ROBOT_V6_CALL rbt_RackLine(
		                 double x,
		                 double y,
		                 double z,
		                 double rx,
		                 double ry,
		                 double rz,
		                 double a,            //7th axis is the ground rack, the motion unit is mm
		                 double b,
		                 WORD  wAxisP,       //8th axis using---0: no use; 1: inclined axis ; 2: rotate axis
		                 TRANS_RULES TrM,    //axisP transmatrix incline/rotate axis
		                 double* VectA,      //the vector of 7axis for Ground rack
		                 DWORD posture,
		                 WORD wGroupIndex = 0,
		                 DWORD dwAxisMask = 0xFF);
ROBOT_V6_API int   ROBOT_V6_CALL rbt_RackArc(
							double x0, // 1st ref. point for x axis
							double y0, // 1st ref. point for y axis
							double z0, // 1st ref. point for z axis
							double a0, // 1st ref. point for j7 (rad)
							double b0, // 1st ref. point for j8  (rad)
							double x1, // target point for x axis
							double y1, // target point for y axis
							double z1, // target point for z axis
							double rx, // target point for x orientation
							double ry, // target point for y orientation
							double rz, // target point for z orientation
							double a, //rad
                            double b,   //rad
							WORD axisA,          //0: no use; 1: inclined; 2: rotated  (for 8 axis)
							TRANS_RULES TrM,   //inclination/rotation axis transmatrix
							double* VectA,
							DWORD posture,
							WORD  wGroupIndex = 0,
							DWORD dwAxisMask = 0xFF
							);
ROBOT_V6_API int    ROBOT_V6_CALL rbt_RackCircle(
							double x0, // 1st ref. point for x axis
							double y0, // 1st ref. point for y axis
							double z0, // 1st ref. point for z axis
							double a0, // 1st ref. point for a axis
							double b0, // 1st ref. point for b axis
							double x1, // 2nd ref. point for x axis
							double y1, // 2nd ref. point for y axis
							double z1, // 2nd ref. point for z axis
							double rx, // target point for x orientation
							double ry, // target point for y orientation
							double rz, // target point for z orientation
							double a,
                            double b,
							WORD axisA,          //0: no use; 1: inclined axis; 2: rotated axis
							TRANS_RULES TrM,   //rotation axis transmatrix
							double* VectA,
							DWORD posture,
							WORD  wGroupIndex = 0,
							DWORD dwAxisMask = 0xFF
							);
/////////////////////20211210///////////////////////////
/*ROBOT_V6_API int    ROBOT_V6_CALL rbt_Leapfrog(
							double dfX,
							double dfY,
							double dfZ,
							double dfRx,
							double dfRy,
							double dfRz,
							double dfleap,       //起跳高度（绝对位置值，先上升Z到该位置，从该高度开始XY方向运动）
							double dfHpoint,     //最高点高度（绝对位置值）
							double dffall,       //下降高度（绝对位置值，在该高度时XY运动结束，只剩下Z轴下降到目标点，也即安全避让高度为fall-dfZ）
							DWORD posture,
							WORD wGroupIndex = 0,
							DWORD dwAxisMask = 0xFF
							);
///////////////////////////20220331///////////////////////////
ROBOT_V6_API int    ROBOT_V6_CALL rbt_PtPLeapfrog(
							double dfJ0,
							double dfJ1,
							double dfJ2,
							double dfJ3,
							double dfleap,
							double dfHpoint,
							double dffall,
							WORD wGroupIndex = 0,
							DWORD dwAxisMask = 0xFF
							);
*/
///////////////////////////20220415--QueueGPIO////////////////////////////////////////
//ROBOT_V6_API void ROBOT_V6_CALL AMC_EnqueueInit(int DelayTime, int Mode, int EIOnum);
// Mode=0  : GPIO
// Mode=1  : EIO
//EIOnum   : EIO的编号，0代表第一块EIO, 1代表第二块，依次类推
//ROBOT_V6_API void ROBOT_V6_CALL AMC_Enqueueclose();
///////////////////////////////20220505---SCARA_TOOL//////////////////////////////////////
//工具安装在末端
ROBOT_V6_API SCARA_T  ROBOT_V6_CALL rbt_GetScaraTool(
		                  TEACH_POINT p1,                    //从一个手系将工具尖端对准固定点，并记录当前的世界坐标值p1；
		                  TEACH_POINT p2,                    //从另外一个手系将工具尖端对准同一固定点，并记录当前世界坐标值p2;
		                  WORD wGroupIndex
						  );

//工具安装在小臂上
ROBOT_V6_API SCARA_T  ROBOT_V6_CALL rbt_GetScaraTool2(
		                  TEACH_LRJ J1,                    //从一个手系将工具尖端对准固定点，并记录当前j1\j2的关节坐标；
						  TEACH_LRJ J2,                    //从另外一个手系将工具尖端对准同一固定点，并记录当前j1\j2的关节坐标;
		                  WORD wGroupIndex
						  );


/////////////////////////////add 20220613////////////////////////////////////////////////////////
ROBOT_V6_API int    ROBOT_V6_CALL rbt_CoArcB(
							double x0, // 1st ref. point for x axis
							double y0, // 1st ref. point for y axis
							double z0, // 1st ref. point for z axis
							double a0, // 1st ref. point for j7 (rad)
							double b0, // 1st ref. point for j8  (rad)
							double x1, // target point for x axis
							double y1, // target point for y axis
							double z1, // target point for z axis
							double rx, // target point for x orientation
							double ry, // target point for y orientation
							double rz, // target point for z orientation
							double a, //rad
                            double b,   //rad
							WORD axisA,          //0: no use; 1: 7a-->1 axis of positioner; 2: 7a-->2 axis of positioner
							WORD axisB,         //0: no use; 1: 8b-->1 axis of positioner; 2: 8b-->2 axis of positioner
							TRANS_RULES trM1,   //inclination axis transmatrix
							TRANS_RULES trM2,   //rotation axis transmatrix
							DWORD posture,
							WORD  wGroupIndex,
							DWORD dwAxisMask
							);
ROBOT_V6_API int    ROBOT_V6_CALL rbt_CoLineB(                                     //add by zgx 20220914
							double x, // target point for x axis
							double y, // target point for y axis
							double z, // target point for z axis
							double rx, // target point for x orientation
							double ry, // target point for y orientation
							double rz, // target point for z orientation
							double a, //rad
                            double b,   //rad
							WORD axisA,          //0: no use; 1: 7a-->1 axis of positioner; 2: 7a-->2 axis of positioner
							WORD axisB,         //0: no use; 1: 8b-->1 axis of positioner; 2: 8b-->2 axis of positioner
							TRANS_RULES trM1,   //inclination axis transmatrix
							TRANS_RULES trM2,   //rotation axis transmatrix
							DWORD posture,
							WORD  wGroupIndex,
							DWORD dwAxisMask
							);

ROBOT_V6_API int    ROBOT_V6_CALL rbt_EnableCoBlend(
		                              WORD axisA,          //0: no use; 1: 7a-->1 axis of positioner; 2: 7a-->2 axis of positioner
		                              WORD axisB,         //0: no use; 1: 8b-->1 axis of positioner; 2: 8b-->2 axis of positioner
		                              TRANS_RULES trM1,   //inclination axis trans matrix
		                              TRANS_RULES trM2,   //rotation axis trans matrix
		                              DWORD posture,
		                              WORD  wGroupIndex
                                      );
//////////////////////////////////posture hold 20221013////////////////////////////////////////////
ROBOT_V6_API int    ROBOT_V6_CALL rbt_EnableCoBlendEx(
		                              WORD axisA,          //0: no use; 1: 7a-->1 axis of positioner; 2: 7a-->2 axis of positioner
		                              WORD axisB,         //0: no use; 1: 8b-->1 axis of positioner; 2: 8b-->2 axis of positioner
		                              TRANS_RULES trM1,   //inclination axis transmatrix
		                              TRANS_RULES trM2,   //rotation axis transmatrix
		                              DWORD posture,
		                              WORD  wGroupIndex
                                      );
////////////////////////////////////////////////////////////////////////////////////////////////////
ROBOT_V6_API int    ROBOT_V6_CALL rbt_CoWaveArc(
							double x0, // 1st ref. point for x axis
							double y0, // 1st ref. point for y axis
							double z0, // 1st ref. point for z axis
							double a0, // 1st ref. point for j7 (rad)
							double b0, // 1st ref. point for j8  (rad)
							double x1, // target point for x axis
							double y1, // target point for y axis
							double z1, // target point for z axis
							double rx, // target point for x orientation
							double ry, // target point for y orientation
							double rz, // target point for z orientation
							double a, //rad
                            double b,   //rad
							WORD axisA,          //0: no use; 1: 7a-->1 axis of positioner; 2: 7a-->2 axis of positioner
							WORD axisB,         //0: no use; 1: 8b-->1 axis of positioner; 2: 8b-->2 axis of positioner
							TRANS_RULES trM1,   //inclination axis transmatrix
							TRANS_RULES trM2,   //rotation axis transmatrix
							double dfFrequency,
							double dfAmplitude,
							double dfDelayTimeL,
							double dfDelayTimeR,
							DWORD posture,
							WORD  wGroupIndex,
							DWORD dwAxisMask
							);
////////////////////////////////////////////////////////////////////////////
///////////////////////////20220923zgx-posture hold//////////////////////////
ROBOT_V6_API int    ROBOT_V6_CALL rbt_CoArcEx(                                 //在运动过程中焊枪与旋转平面的Z轴保持固定角度不变，目标姿态自动计算得到，
							double x0, // 1st ref. point for x axis            //不使用指令传入目标姿态rx\ry\rz值
							double y0, // 1st ref. point for y axis
							double z0, // 1st ref. point for z axis
							double a0, // 1st ref. point for j7 (rad)
							double b0, // 1st ref. point for j8  (rad)
							double x1, // target point for x axis
							double y1, // target point for y axis
							double z1, // target point for z axis
							double rx, // target point for x orientation
							double ry, // target point for y orientation
							double rz, // target point for z orientation
							double a, //rad
							double b,   //rad
							WORD axisA,          //0: no use; 1: 7a-->1 axis of positioner; 2: 7a-->2 axis of positioner
							WORD axisB,         //0: no use; 1: 8b-->1 axis of positioner; 2: 8b-->2 axis of positioner
							TRANS_RULES trM1,   //inclination axis transmatrix
							TRANS_RULES trM2,   //rotation axis transmatrix
							DWORD posture,
							WORD  wGroupIndex = 0,
							DWORD dwAxisMask = 0xFF
							);
ROBOT_V6_API int    ROBOT_V6_CALL rbt_CoCircleEx(
							double x0, // 1st ref. point for x axis
							double y0, // 1st ref. point for y axis
							double z0, // 1st ref. point for z axis
							double a0, // 1st ref. point for a axis
							double b0, // 1st ref. point for b axis
							double x1, // 2nd ref. point for x axis
							double y1, // 2nd ref. point for y axis
							double z1, // 2nd ref. point for z axis
							double rx, // target point for x orientation
							double ry, // target point for y orientation
							double rz, // target point for z orientation
							double a,
							double b,
							WORD axisA,          //0: no use; 1: 7a-->1 axis of positioner; 2: 7a-->2 axis of positioner
							WORD axisB,         //0: no use; 1: 8b-->1 axis of positioner; 2: 8b-->2 axis of positioner
							TRANS_RULES trM1,   //inclination axis transmatrix
							TRANS_RULES trM2,   //rotation axis transmatrix
							DWORD posture,
							WORD  wGroupIndex = 0,
							DWORD dwAxisMask = 0xFF
                            );
ROBOT_V6_API void    ROBOT_V6_CALL CalOrientEx(
		                   const double* pdfStartPosture,
		                   double* vec_normal,
		                   double theta,
	                       double* endorient
		                   );

////////////////////////////////////////////////////////////////////////////////////////////////
ROBOT_V6_API void    ROBOT_V6_CALL rbt_ClearCnt();   //全局变量清零 20220928
///////////////////////////////////////////////////////////////////////////////////////////////
ROBOT_V6_API void rbt_GetGroupInfo(GROUPINFO* GrouInfo, WORD wGroupIndex);         //打乱轴顺序建立group时对关节和轴号做对应，方便rbt_Line_V6过速判断时进行处理
ROBOT_V6_API void rbt_SetGroupInfo(int j1toch, int j2toch, int j3toch, int j4toch, int j5toch, int j6toch, int j7toch, int j8toch,WORD wGroupIndex);
////////////////////////////////////////////////////////////////////////////////////////////////
ROBOT_V6_API void    ROBOT_V6_CALL rbt_GetCoMotionStatus(int *pnFlag, int *pnNum) ;//获取平滑协同运动时的指令信息：flag=0/1(直线/圆弧)；num当前指令编号（从0开始）
#ifdef __cplusplus
	}
#endif

#endif //__KINEMATICS_H__
