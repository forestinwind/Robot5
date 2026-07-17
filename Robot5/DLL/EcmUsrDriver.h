/******************************************************************************
 *	File	:	EcmUsrDriver.h
 *	Version :	1.42
 *	Date	:	2021/03/11
 *	Author	:	XFORCE
 *
 *	ECM-XF basic driver example - Header file
 *
 *	Demonstrate how to implement API type user driver
 *
 * @copyright (C) 2020 NEXTW TECHNOLOGY CO., LTD.. All rights reserved.
 *
 ******************************************************************************/

#ifndef _ECM_USR_DRV_H_
#define _ECM_USR_DRV_H_
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "EcmDriver.h"
//#include "platform.h"

#ifdef WIN32
#include <windows.h>
#include <stdint.h>
#ifdef PMCPCIDRV_EXPORTS
#define PMC_LIB_API __declspec(dllexport)
#else
#define PMC_LIB_API __declspec(dllimport)
#endif
 //#define PMC_LIB_CALL _stdcall
#define PMC_LIB_CALL _cdecl
#else /* WIN32*/
#define PMC_LIB_API  /*IMPORT*/
#define PMC_LIB_CALL
#ifndef _DEFINED_BOOL
 //typedef int                 BOOL;
#endif		
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef unsigned long       DWORD;
#endif /* !WIN32*/

#ifdef __cplusplus
extern "C" {
#endif

/*
 *
 * Example
 * 24MHz
 * 500 bytes data
 * 32 bytes header
 * (500+32)*8/24 = 177us
 * 177us + 50us = 227us(SPI communication time)
 *
 * NOTE:
 * if(SPI communication time > ECAT Cycle time)
 * Send more than one PDO in one SPI datagram
 *
 * */
#define TEST_SPI_DATA_SIZE		PKG_DATA_DEFAULT_SIZE
//#define TEST_SPI_IDLE_TIME		150
#define TEST_SPI_CRC_TYPE		ECM_CRC_TYPE_NONE

#define CIA402_SW_STATE_MASK						0x6F
#define CIA402_SW_NOTREADYTOSWITCHON				0x00
#define CIA402_SW_SWITCHEDONDISABLED				0x40
#define CIA402_SW_READYTOSWITCHON					0x21
#define CIA402_SW_SWITCHEDON						0x23
#define CIA402_SW_OPERATIONENABLED					0x27
#define CIA402_SW_QUICKSTOPACTIVE					0x07
#define CIA402_SW_FAULTREACTIONACTIVE				0x0F
#define CIA402_SW_FAULT								0x08
ECM_PACK_BEGIN
typedef struct ECM_PACK spi_cmd_package_t{
	SPI_CMD_HEADER	Head;
	uint8_t			Data[TEST_SPI_DATA_SIZE];
	uint32_t		Crc;
	uint32_t		StopWord;
} SPI_CMD_PACKAGE_T;
ECM_PACK_END
ECM_PACK_BEGIN
typedef struct ECM_PACK spi_ret_package_t{
	SPI_RET_HEADER	Head;
	uint8_t			Data[TEST_SPI_DATA_SIZE];
	uint32_t		Crc;
	uint32_t		StopWord;
} SPI_RET_PACKAGE_T;
ECM_PACK_END
int EcmUniversalCmd(	uint8_t u8Cmd, \
				uint8_t u8Param, \
				uint8_t u8Param0, \
				uint8_t u8Param1, \
				uint8_t u8Param2, \
				uint8_t u8Param3, \
				uint8_t *pu8Return, \
				uint8_t *pu8Status, \
				uint8_t *pu8ErrStatus, \
				uint16_t *pu16ReturnDataSize, \
				uint8_t *pu8ReturnData);
int ECM_WaitAsyncDone(int nMS);
int ECM_IsAsyncBusy(void);
int SpiDataExchange(uint8_t *RetIdx, uint8_t *RetCmd);
PMC_LIB_API int ECM_GetFirmwareVersion(uint8_t *pVersion);
PMC_LIB_API int ECM_CheckDCStable(void);
PMC_LIB_API int ECM_IsSlaveAlive(uint8_t *pEcmStatus, uint8_t *pRxPDOFifoCnt, uint8_t *CrcErrCnt, uint8_t *WkcErrCnt);
PMC_LIB_API int ECM_InfoUpdate(uint8_t *pEcmStatus, uint8_t *pRxPDOFifoCnt, uint8_t *CrcErrCnt, uint8_t *WkcErrCnt);
PMC_LIB_API int ECM_EcatInit(uint16_t DCActCode, uint32_t CycTime);
int ECM_GetRetStatus(uint8_t *pStatus);
int ECM_GetRetErrStatus(uint8_t *pErrStatus);
PMC_LIB_API uint8_t ECM_InitLibrary(uint16_t *pu16SpiDataSize);
PMC_LIB_API void ECM_CloseLibrary();
PMC_LIB_API int ECM_EcatReconfig();
PMC_LIB_API int8_t ECM_EcatSlvCntGet();
PMC_LIB_API int ECM_EcatStateSet(uint8_t u8Slave, uint8_t u8State);
PMC_LIB_API int ECM_EcatStateUpdate(void);
PMC_LIB_API int ECM_EcatStateGet(uint8_t u8Slave, uint8_t *pu8State);
PMC_LIB_API int ECM_EcatStateCheck(uint8_t u8Slave, uint8_t u8State);
int ECM_EcatPdoConfigSet( uint8_t Slave, PDO_CONFIG_HEAD *pConfigData);
int ECM_EcatPdoConfigReq(uint8_t Slave, uint16_t SmaIdx);
int ECM_EcatPdoConfigGet(PDO_CONFIG_HEAD *pBuf);
PMC_LIB_API int ECM_EcatSdoReq(uint8_t OP, uint8_t Slave, uint16_t Index, uint8_t SubIndex, uint16_t size, int Timeout, uint8_t *Data);
PMC_LIB_API int ECM_EcatSdoCAReq(uint8_t OP, uint8_t Slave, uint16_t Index, uint8_t SubIndex, uint16_t size, int Timeout, uint8_t *Data);
PMC_LIB_API int ECM_EcatSdoGet(uint8_t *pBuf);
//PMC_LIB_API int ECM_EcatSdoWrite(uint8_t Slave,  uint16_t Index,  uint8_t SubIndex,  uint16_t size,  int Timeout,  uint8_t *Data);
//PMC_LIB_API int ECM_EcatSdoRead(uint8_t Slave, uint16_t Index, uint8_t SubIndex, uint16_t size, int Timeout, uint8_t *Data);
int ECM_Drv402SM_AdvConfig(uint8_t TblIdx, uint8_t SlvIdx, uint8_t ContrlWordOffset, uint8_t StateWordOffset);
int ECM_Drv402SM_Enable(uint8_t TblIdx, uint8_t SlvIdx);
int ECM_Drv402SM_Disable(uint8_t TblIdx, uint8_t SlvIdx);
int ECM_Drv402SM_StateSet(uint8_t TblIdx, uint8_t State);
int ECM_Drv402SM_StateGet(uint8_t TblIdx, uint8_t *pState);
int ECM_Drv402SM_StateCheck(uint8_t TblIdx, uint8_t ExceptState, int TimeOutMS);
PMC_LIB_API int ECM_FifoRxPdoSizeGet();
PMC_LIB_API int ECM_FifoTxPdoSizeGet();

uint8_t ECM_EcatPdoDataExchange(uint8_t u8OP, uint8_t *pRxData, uint8_t *pTxData, uint16_t *pu16DataSize);
int ECM_EcatPdoFifoDataExchange(uint8_t u8FifoThreshold, uint8_t *pRxData, uint8_t *pTxData, uint16_t u16DataSize, uint8_t *pRxPDOFifoCnt, uint8_t *CrcErrCnt, uint8_t *WkcErrCnt);
PMC_LIB_API int ECM_EcatPdoFifoDataExchangeAdv(uint8_t u8Op, uint8_t u8Cnt, uint8_t *pRxData, uint8_t *pTxData, uint16_t u16DataSize, uint8_t *pu8RxPdoFifoCnt, uint8_t *CrcErrCnt, uint8_t *WkcErrCnt, uint8_t *IsSlvAlive);
int ECM_EcatPdoFifoIsFull(uint8_t u8FifoThreshold);
int ECM_EcatEepromReq(uint16_t OP, uint16_t slave, uint16_t eeproma, uint16_t data, uint32_t timeout);
int ECM_EcatEepromGet(uint64_t *pu64Data);
int ECM_GetPDOConfig(int Slave, int SmaIdx, PDO_CONFIG_HEAD *pPdoConfigBuf);
int ECM_ShowPDOConfig(int Slave, int SmaIdx);
PMC_LIB_API int ECM_StateCheck(uint8_t u8Slave, uint8_t u8ExpectState, int TimeOutMS);
int ECM_EcatDatagramReq(
        ecm_datagram_commad_t cmd,
		uint16_t position,
		uint16_t offset,
		uint32_t logicalAddress,
		uint16_t length,
		int Timeout,
		uint8_t *Data);
int ECM_EcatDatagramGet(uint8_t *pBuf);
PMC_LIB_API int ECM_SlaveInfoGet(uint8_t slave, uint8_t info, uint8_t *pBuf);

PMC_LIB_API int ECM_SetTxFIFOCnt(uint8_t u8TxCnt);
PMC_LIB_API int ECM_SetRxFIFOCnt(uint8_t u8RxCnt);
PMC_LIB_API int ECM_GetTxFIFOCnt(uint8_t *pu8Cnt);
PMC_LIB_API int ECM_GetRxFIFOCnt(uint8_t *pu8Cnt);

PMC_LIB_API int ECM_ClearFIFO(uint8_t u8TxRx);
PMC_LIB_API int ECM_EnableFIFO(uint8_t u8Enable);
PMC_LIB_API int ECM_InitFIFO(void);
PMC_LIB_API int ECM_SetSpiDataSize(uint16_t u16SpiDataSize);
PMC_LIB_API int ECM_GetSpiDataSize(uint16_t *pu16SpiDataSize);

int EcmSpiPackSizeCal(int nSizeLimit);
int ECM_EcatRawCmdReq(uint16_t OP,  \
		uint16_t length, \
		uint16_t ADP, \
		uint16_t ADO, \
		uint32_t LogAdr, \
		int timeout, \
		uint8_t *data);
uint16_t ECM_EcatRawCmdGet(uint8_t *pBuf);
uint16_t ECM_EcatRawCmdRead(uint16_t OP,  \
		uint16_t length, \
		uint16_t ADP, \
		uint16_t ADO, \
		uint32_t LogAdr, \
		int timeout, \
		uint8_t *data);
int ECM_EcatWkcErrorMaxSet(uint8_t u8Max);
int ECM_EcatWkcErrorMaxGet(uint8_t *pu8Max);
int32_t ECM_GetLogTime(uint8_t u8Timer, uint8_t u8Idx, uint8_t u8Type);
int ECM_ShowReturnField();
int ECM_ShowCmdField();
PMC_LIB_API int ECM_EcatSdoSetPdoConfig(PDO_CONFIG_HEAD *pConfigData);
PMC_LIB_API int ECM_DirectAssign(uint8_t u8Slv, uint8_t u8Mode, uint16_t u16Obits, uint16_t u16Ibits);
PMC_LIB_API int ECM_EcatConfigMap(void);
PMC_LIB_API int ECM_EcatConfigSM(uint8_t slave, uint8_t nSM, uint16_t StartAddr, uint16_t SMlength, uint8_t ControlReg, uint8_t Activate);
int ECM_EcatConfigFMMU(uint8_t slave, uint8_t FMMU0func, uint8_t FMMU1func, uint8_t FMMU2func, uint8_t FMMU3func);
int ECM_WarmReset(void);
PMC_LIB_API SPI_CMD_PACKAGE_T * GetEcmCmdBuf();
PMC_LIB_API SPI_RET_PACKAGE_T * GetEcmRetBuf();

PMC_LIB_API int ECM_GetNetLinkPin(int *pPinStatus);


int ECM_SetSpiTransIdleTime(int TimeUS);
int ECM_GetSpiTransIdleTime(int TimeUS);

typedef uint8_t(__stdcall *EcmGpioIsr)(uint8_t u8IntFlag, uint8_t u8GpioIn);
 void RegistryGpioIsr(EcmGpioIsr pcbFunc);

#ifdef __cplusplus
}
#endif

#endif
