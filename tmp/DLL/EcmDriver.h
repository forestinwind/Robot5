/******************************************************************************
 *	File	:	EcmUsrDriver.h
 *	Version :	1.1
 *	Date	:	2021/01/26
 *	Author	:	XFORCE
 *
 *	ECM-XF basic driver example - Header file
 *
 *	Demonstrate how to implement API type user driver
 *
 * @copyright (C) 2020 NEXTW TECHNOLOGY CO., LTD.. All rights reserved.
 *
 ******************************************************************************/
#ifndef _ECMADCDRIVER_H_
#define _ECMADCDRIVER_H_
#include <stdint.h>
#include <stdio.h>
#include <string.h>


//EcmDriver.h
#include "windows.h"

#ifdef _MSC_VER
#define PACKED_STRUCT(name) __pragma(pack(push, 1)) struct name __pragma(pack(pop))
#define ECM_PACK_BEGIN	__pragma(pack(push, 1))
#define ECM_PACK
#define ECM_PACK_END	__pragma(pack(pop))
#elif defined(__GNUC__)
#define PACKED_STRUCT(name) struct __attribute__((packed)) name
#define ECM_PACK_BEGIN	__pragma(pack(push, 1))
#define ECM_PACK  __attribute__((__packed__))
#define ECM_PACK_END	__pragma(pack(pop))
#endif

#ifdef ECMXFUSBDRV_EXPORTS
#define ECM_DLL_SYMBOL		__declspec(dllexport)
#else
#define ECM_DLL_SYMBOL		__declspec(dllimport)
#endif
#define ECM_DLL_FUNCTYPE	__cdecl

#define CIA402_SW_STATE_MASK			0x6F
#define CIA402_SW_NOTREADYTOSWITCHON	0x00
#define CIA402_SW_SWITCHEDONDISABLED	0x40
#define CIA402_SW_READYTOSWITCHON		0x21
#define CIA402_SW_SWITCHEDON			0x23
#define CIA402_SW_OPERATIONENABLED		0x27
#define CIA402_SW_QUICKSTOPACTIVE		0x07
#define CIA402_SW_FAULTREACTIONACTIVE	0x0F
#define CIA402_SW_FAULT					0x08

#define ECM_INDEX						0xFF

#define EC_STATE_NONE					0x00
#define EC_STATE_INIT					0x01
#define EC_STATE_PRE_OP					0x02
#define EC_STATE_BOOT					0x03
#define EC_STATE_SAFE_OP				0x04
#define EC_STATE_OPERATIONAL			0x08
#define EC_STATE_ACK					0x10
#define EC_STATE_ERROR					0x10

#define PDO_FIFO_SIZE				16384
#define PKG_DATA_MIN_SIZE			32
#define PKG_DATA_MAX_SIZE			1408
#define PACK_HEAD_SIZE				24
#define CRC_FIELD_SIZE				4
#define PACK_STOPWORD_SIZE			4
#define PKG_MIN_SIZE				64
#define PKG_MAX_SIZE				1440
#ifdef ECM_XFU
#define PKG_DATA_DEFAULT_SIZE		992
#define PKG_DEFAULT_SIZE			1024
#else
#define PKG_DATA_DEFAULT_SIZE		1024
#define PKG_DEFAULT_SIZE			1056
#endif
 //#define SPI_FIFO_MAX_SIZE			1408
#define PDO_FIFO_MAX_CNT			128
#define PDO_FIFO_DEFAULT_CNT		64
#define TXPDO_EXDATA_SIZE			0

#define ECM_ERR_LINK_PIN_MASK			0x01
#define ECM_ERR_LINK_CHK_MASK			0x02
#define ECM_ERR_ECAT_STA_MASK			0x04
#define ECM_ERR_ASYNC_CMD_MASK			0x08
#define	ECM_ERR_SPI_MASK				0x10
#define	ECM_ERR_FIFO_MASK				0x20
#define ECM_ERR_CRC_MASK				0x40
#define ECM_ERR_CMD_MASK				0x80

#define ECM_CRC_TYPE_NONE	0
#define ECM_CRC_TYPE_8		1
#define ECM_CRC_TYPE_16		2
#define ECM_CRC_TYPE_32		3

#define	ECM_STA_CRC_TYPE_MASK			0x03
#define ECM_STA_DC_STABLE				0x04
#define ECM_STA_EMAC_INIT_MASK			0x08
#define ECM_STA_ECAT_CONFIG_MASK		0x10
#define ECM_STA_NOP_CMD_MASK			0x20
#define ECM_STA_FIFO_EN_MASK			0x40
#define ECM_STA_ASYNC_OP_BUSY_MASK		0x80

#define ECM_CTL_UPDATE_EC_STATE_MASK		0x01
#define ECM_CTL_ENABLE_RTA_MASK				0x02
#define ECM_CTL_CLR_ASYNC_OP_ERR_MASK		0x08
#define ECM_CTL_CLR_SPI_ERR_MASK			0x10
#define ECM_CTL_CLR_FIFO_ERR_MASK			0x20
#define ECM_CTL_CLR_CRC_ERR_MASK			0x40
#define ECM_CTL_CLR_CMD_ERR_MASK			0x80
#define ECM_CTL_CLR_ALL_ERR_MASK			0xF8

#define ECM_MISC_HEAD_IO_EN_MASK			0x8000
#define ECM_MISC_PDO_WITH_SDO_MASK			0x4000
#define ECM_MISC_PDO_WITH_MBX_STAT			0x2000
#define ECM_MISC_DC_MASTER_SHIFT_EN_MASK	0x1000
#define ECM_MISC_LRW_EN_MASK				0x0800

#define ECM_CRC_INIT_NUM			0x87654321
#define	ECM_CRC_MAGIC_NUM			0x12345678
#define	ECM_START_WORD				0xA1A2A3A4
#define	ECM_STOP_WORD				0x56575859

#define ECM_SDO_OP_WR	0
#define ECM_SDO_OP_RD	1

#define ECM_FIFO_WR			1
#define ECM_FIFO_RD			2
#define ECM_FIFO_WR_DIR		4
#define ECM_FIFO_RD_DIR		8

#define ECM_FIFO_RW			3
#define ECM_FIFO_RWD		6
#define ECM_FIFO_RDW		9

#define ECM_FIFO_RXPDO		0
#define ECM_FIFO_TXPDO		1

#define ECM_PDO_WR_OP		5
#define ECM_PDO_RD_OP		6
#define ECM_PDO_RW_OP		7

#define ECM_STATE_OP_UPDATE		0
#define ECM_STATE_OP_RD			1
#define ECM_STATE_OP_WR			2
#define ECM_STATE_OP_WRandACK	3

#define CIA402_FSM_CTL_ENABLE_MASK			0x10
#define CIA402_FSM_CTL_FAULT_RST_MASK		0x08
#define CIA402_FSM_CTL_FAULT_AUTORST_MASK	0x80


#define ECM_EEPROM_OP_RD			0
#define ECM_EEPROM_OP_WR			1

enum {
	ECM_SLV_INFO_vid,
	ECM_SLV_INFO_pid,
	ECM_SLV_INFO_rev,
	ECM_SLV_INFO_name,
	ECM_SLV_INFO_configadr,
	ECM_SLV_INFO_aliasadr,
	ECM_SLV_INFO_state,
	ECM_SLV_INFO_ALstatuscode,
	ECM_SLV_INFO_Obytes,
	ECM_SLV_INFO_Ibytes,
	ECM_SLV_INFO_hasdc,
	ECM_SLV_INFO_DCcycle,
	ECM_SLV_INFO_DCshift,
	ECM_SLV_INFO_DCactive,
	ECM_SLV_INFO_outputs,
	ECM_SLV_INFO_inputs,
	ECM_SLV_INFO_islost,
	ECM_SLV_INFO_eep_8byte,
	ECM_SLV_INFO_Itype,
	ECM_SLV_INFO_Dtype,
	ECM_SLV_INFO_Obits,
	ECM_SLV_INFO_Ostartbit,
	ECM_SLV_INFO_Ibits,
	ECM_SLV_INFO_Istartbit,
	ECM_SLV_INFO_ptype,
	ECM_SLV_INFO_topology,
	ECM_SLV_INFO_pdelay,
	ECM_SLV_INFO_DCnext,
	ECM_SLV_INFO_DCprevious,
	ECM_SLV_INFO_configindex,
	ECM_SLV_INFO_SIIindex,
	ECM_SLV_INFO_eep_pdi,
	ECM_SLV_INFO_CoEdetails,
	ECM_SLV_INFO_FoEdetails,
	ECM_SLV_INFO_EoEdetails,
	ECM_SLV_INFO_SoEdetails,
	ECM_SLV_INFO_Ebuscurrent,
	ECM_SLV_INFO_blockLRW,
	ECM_SLV_INFO_group,
	ECM_SLV_INFO_FMMUunused,
	ECM_SLV_INFO_mbx_proto
};
enum {
	ECM_CMD_INFO_UPDATE_OP,
	ECM_CMD_ECAT_INIT_OP,
	ECM_CMD_ECAT_RECONFIG_OP,
	ECM_CMD_ECAT_INIT_DC_OP,
	ECM_CMD_ECAT_PDO_WC_GET,
	ECM_CMD_ECAT_PDO_DATA_FIFO_OP,
	ECM_CMD_ECAT_PDO_DATA_OP,
	ECM_CMD_ECAT_PDO_CONFIG_SET,
	ECM_CMD_ECAT_PDO_CONFIG_REQ,
	ECM_CMD_ECAT_PDO_CONFIG_GET,
	ECM_CMD_ECAT_SDO_REQ,
	ECM_CMD_ECAT_SDO_GET,
	ECM_CMD_ECAT_STATE_SET,
	ECM_CMD_ECAT_STATE_GET,
	ECM_CMD_ECAT_CYCTIME_SET,
	ECM_CMD_ECAT_SLV_INFO_GET,
	ECM_CMD_ECAT_SLV_CNT_GET,
	ECM_CMD_FIFO_CONFIG,
	ECM_CMD_FIFO_ENABLE,
	ECM_CMD_FIFO_PACK_SIZE_GET,
	ECM_CMD_SPI_PACK_SIZE_GET,
	ECM_CMD_SPI_TIMEOUT_SET,
	ECM_CMD_SPI_TIMEOUT_GET,
	ECM_CMD_SPI_RECONFIG_OP,
	ECM_CMD_CRC_ERR_CNT_CLR,
	ECM_CMD_CRC_TYPE_SET,
	ECM_CMD_402_CONFIG_SET,
	ECM_CMD_402_STATE_SET,
	ECM_CMD_402_STATE_GET,
	ECM_CMD_402_CTL_SET,
	ECM_CMD_402_CTL_GET,
	ECM_GPIO_CONFIG_SET,
	ECM_GPIO_FUNC_OP,
	ECM_QEI_FUNC_OP,
	ECM_DAC_FUNC_OP,
	ECM_ADC_FUNC_OP,
	ECM_WDT_FUNC_OP,
	ECM_DCM_PARAM_OP,
	ECM_EEPROM_REQ,
	ECM_EEPROM_GET,
	ECM_CMD_EMAC_RESET_OP,
	ECM_CMD_ECAT_STATE_CHECK,
	ECM_CMD_GET_VALUE,
	ECM_CMD_SET_VALUE,
	ECM_CMD_GET_VAR,
	ECM_CMD_GET_TIMER_TIME,
	ECM_CMD_COMPARE_SET_CONFIG,
	ECM_CMD_COMPARE_GET_CONFIG,
	ECM_CMD_SET_PDO_MAP,
	ECM_CMD_GET_PDO_MAP,
	ECM_CMD_ECAT_DCSYNC,
	ECM_CMD_FIFO_CLR_OP,
	ECM_CMD_FIFO_SET_TX_CNT,
	ECM_CMD_FIFO_GET_TX_CNT,
	ECM_CMD_FIFO_SET_RX_CNT,
	ECM_CMD_FIFO_GET_RX_CNT,
	ECM_CMD_FW_VERSION_GET,
	ECM_CMD_ECAT_STATE_UPDATE,
	ECM_CMD_ECAT_INT_SET_ENABLE,
	ECM_CMD_ECAT_INT_GET_ENABLE,
	ECM_CMD_ECAT_RTA_INIT,
	ECM_CMD_ECAT_RTA_CLOSE,
	ECM_CMD_ECAT_RTA_SET_RULE,
	ECM_CMD_ECAT_RTA_SET_BUF,
	ECM_CMD_ECAT_RTA_SETENABLE,
	ECM_CMD_ECAT_RTA_GETRUNFLAG,
	ECM_CMD_FIFO_INIT,
	ECM_CMD_ECAT_WKC_CONTIERR_SET,
	ECM_CMD_ECAT_WKC_CONTIERR_GET,
	ECM_CMD_ECAT_SDO_ABORTCODE_GET,
	ECM_CMD_ECAT_SET_FIFO_TH,
	ECM_CMD_ECAT_CONFIG_SM,
	ECM_CMD_ECAT_CONFIG_FMMU,
	ECM_CMD_ECAT_CONFIG_MAP,
	ECM_CMD_402_GET_STATUSWORD,
	ECM_CMD_ASYNCCMD_RESET,
	ECM_CMD_SET_PDO_SIZE,
	ECM_CMD_OD_REQ,
	ECM_CMD_OD_GET,
	ECM_CMD_MDIO = ECM_CMD_OD_GET + 3,
	ECM_CMD_DIRECT_ASSIGN,
	ECM_CMD_WARM_RESET = 127,
	ECM_CMD_EMAC_INIT_OP,
	ECM_CMD_EC_INIT_OP,
	ECM_CMD_ECAT_WKC_CONTI_ERR_CNT_GET,
	ECM_CMD_ECAT_WKC_CONTI_ERR_MAX_GET,
	ECM_CMD_ECAT_WKC_CONTI_ERR_MAX_SET,
	ECM_CMD_FIFO_EXPDO_DATA_CNT_SET,
	ECM_CMD_FIFO_EXPDO_DATA_CNT_GET,
	ECM_CMD_FIFO_EXPDO_DATA_TYPE_SET,
	ECM_CMD_FIFO_EXPDO_DATA_TYPE_GET,
	ECM_CMD_RAW_ECAT_FUNC_REQ,
	ECM_CMD_RAW_ECAT_FUNC_GET,
	ECM_CMD_FOE_FUNC_REQ,
	ECM_CMD_FOE_FUNC_GET,
	ECM_CMD_SPI_PACK_SIZE_SET
};
enum {
	ECM_FOE_API_DHOOK,
	ECM_FOE_API_RD,
	ECM_FOE_API_WR
};
typedef enum {
	ECM_RAW_API_APRD = 1,
	ECM_RAW_API_APWR = 2,
	ECM_RAW_API_FPRD = 4,
	ECM_RAW_API_FPWR = 5,
	ECM_RAW_API_BRD = 7,
	ECM_RAW_API_BWR = 8,
	ECM_RAW_API_LRD = 10,
	ECM_RAW_API_LWR = 11,
	ECM_RAW_API_LRW = 12,
	ECM_RAW_API_ARMW = 13,
	ECM_RAW_API_FRMW = 14,
} ecm_datagram_commad_t;
ECM_PACK_BEGIN
typedef struct ECM_PACK ec_dcsync_h
{
	uint8_t Slave;
	uint8_t Paddle;
	uint8_t Mode;
	uint8_t Act;
	uint32_t CyclTime0;
	uint32_t CyclTime1;
	int32_t CyclShift;
} EC_DCSYNC_H;
ECM_PACK_END
ECM_PACK_BEGIN
typedef struct ECM_PACK sdo_write_t
{
	uint8_t OP;
	uint8_t Slave;
	uint16_t Index;
	uint8_t SubIndex;
	uint8_t CA;
	uint16_t size;
	int Timeout;
	uint8_t Data[256];
}SDO_CMD_HEAD;
ECM_PACK_END
ECM_PACK_BEGIN
typedef struct ECM_PACK obj_entry_t
{
	uint8_t u8BitSize;
	uint8_t u8SubIdx;
	uint16_t u16Idx;
} OBJ_ENTRY_T;
ECM_PACK_END
/*typedef union {
	OBJ_ENTRY_SEP_T stT;
	uint32_t u32T;
} OBJ_ENTRY_T;*/
ECM_PACK_BEGIN
typedef struct ECM_PACK pdo_config_t
{
	uint8_t Slave;
	uint8_t PDOCnt;
	uint16_t SmaIdx;
	uint16_t MapIdx[4];
	uint16_t ObjsCnt[4];
	OBJ_ENTRY_T Table[4][8];
} PDO_CONFIG_HEAD;
ECM_PACK_END
ECM_PACK_BEGIN
typedef struct ECM_PACK ecm_eeprom_req_t
{
	uint16_t OP;
	uint16_t slave;
	uint16_t eeproma;
	uint16_t data;
	uint32_t timeout;
} ECM_EEPROM_REQ_T;
ECM_PACK_END
ECM_PACK_BEGIN
typedef struct ECM_PACK spi_cmd_header
{
	uint32_t u32StartWord;
	uint8_t u8Data[4];
	uint16_t u16Reserve;
	uint8_t u8Ctrl;
	uint8_t u8Idx;
	uint8_t u8Cmd;
	uint8_t u8Param;
	uint16_t u16Size;
	uint32_t u32CompIntClr;
	uint8_t u8GpioIntClr[2];
	uint8_t uGpio[2];
} SPI_CMD_HEADER;
ECM_PACK_END
ECM_PACK_BEGIN
typedef struct ECM_PACK spi_cmd_package
{
	SPI_CMD_HEADER Head;
	uint8_t Data[];
} SPI_CMD_PACKAGE;
ECM_PACK_END
ECM_PACK_BEGIN
typedef struct ECM_PACK spi_ret_header
{
	uint32_t u32StartWord;
	uint8_t u8CrcErrCnt;
	uint8_t u8WkcErrCnt;
	uint8_t u8TxFifoCnt;
	uint8_t u8RxFifoCnt;
	uint8_t u8EcState;
	uint8_t u8ErrorStatus;
	uint8_t u8Status;
	uint8_t u8Idx;
	uint8_t u8Cmd;
	uint8_t u8Return;
	uint16_t u16Size;
	uint32_t u32CompIntFlag;
	uint8_t u8GpioIntFlag[2];
	uint8_t u8Gpio[2];
} SPI_RET_HEADER;
ECM_PACK_END
ECM_PACK_BEGIN
typedef struct ECM_PACK spi_ret_package
{
	SPI_RET_HEADER Head;
	uint8_t Data[];
} SPI_RET_PACKAGE;
ECM_PACK_END
ECM_PACK_BEGIN
typedef struct ECM_PACK _cia402_api_param_
{
	uint8_t Ctrl;
	uint8_t TargetState;
	uint8_t ContrlWordOffset;
	uint8_t StatusWordOffset;
} CIA402_API_PARAM;
ECM_PACK_END
ECM_PACK_BEGIN
typedef struct ECM_PACK _ecm_pdo_ext_data_
{
	uint16_t u16WKC;
	uint8_t u8Idx;
	uint8_t u8Reserve;
} ECM_PDO_EXT_DATA;
ECM_PACK_END
ECM_PACK_BEGIN
typedef struct ECM_PACK ec_raw_api_param_h
{
	uint16_t OP;
	uint16_t length;
	uint16_t ADP;
	uint16_t ADO;
	uint32_t LogAdr;
	int timeout;
	int wkc;
	uint8_t data[256];
} EC_RAW_API_PARAM_H;
ECM_PACK_END

ECM_PACK_BEGIN
typedef struct ECM_PACK ecm_config_sm_t
{
	uint8_t slave;
	uint8_t nSM;
	uint16_t StartAddr;
	uint16_t SMlength;
	uint8_t ControlReg;
	uint8_t Activate;
} ECM_CONFIG_SM_T;
ECM_PACK_END

ECM_PACK_BEGIN
typedef struct ECM_PACK ecm_config_fmmu_t
{
	uint8_t slave;
	uint8_t FMMU0func;
	uint8_t FMMU1func;
	uint8_t FMMU2func;
	uint8_t FMMU3func;
} ECM_CONFIG_FMMU_T;
ECM_PACK_END


#ifdef __cplusplus
extern "C" {
#endif
	/******************************************************************************
	 * ADC_MODE Definitions
	 ******************************************************************************/
#define ECM_ADC_MODE_SINGLE_END         (0UL)   /* Single-end input mode  */
#define ECM_ADC_MODE_DIFFERENTIAL       (1UL)   /* Differential input mode */

	 /******************************************************************************
	  * ADC_TRIG Definitions
	  ******************************************************************************/
#define ECM_ADC_TRIG_SOFTWARE           (0UL)      /* Software trigger. Use ECM_AdcStartConv() function to trigger ADC input */

	  /**
	   * Open ADC device and Set ADC input mode
	   *
	   * @param  mode				: ADC mode. See ECM_ADC_MODE_## definitions.
	   *
	   * @return					: 1 for success; 0 for timeout; -1 for invalid input parameters.
	   */
	ECM_DLL_SYMBOL int ECM_AdcOpen(uint32_t mode);

	/**
	 * Open ADC device and Set ADC input mode
	 *
	 * @param  mode				: ADC mode. See ECM_ADC_MODE_## definitions.
	 *
	 * @return					: 1 for success; 0 for timeout.
	 */
	ECM_DLL_SYMBOL int ECM_AdcClose(void);

	/**
	 * Select ADC trigger source
	 *
	 * @param  source			: ADC trigger source. See ECM_ADC_TRIG_## definitions.
	 *
	 * @return					: 1 for success; 0 for timeout; -1 for invalid input parameters.
	 */
	ECM_DLL_SYMBOL int ECM_AdcConfigSampleModule(uint32_t source);

	/**
	 * Get ADC data valid flag
	 *
	 * @param  flag 			: ADC data valid flag. The data is valid if the flag is non-zero.
	 *
	 * @return					: 1 for success; 0 for timeout; -1 for invalid input parameters.
	 */
	ECM_DLL_SYMBOL int ECM_AdcGetDataValidFlag(uint32_t *flag);

	/**
	 * Start ADC convert.
	 *
	 * @return					: 1 for success; 0 for timeout; -1 for invalid input parameters.
	 */
	ECM_DLL_SYMBOL int ECM_AdcStartConv(void);

	/**
	 * Get ADC data value
	 *
	 * @param  data 			: ADC data value.
	 *
	 * @return					: 1 for success; 0 for timeout; -1 for invalid input parameters.
	 */
	ECM_DLL_SYMBOL int ECM_AdcGetConvData(uint32_t *data);


	//DAC
	/******************************************************************************
	 * DAC_MODE Definitions
	 ******************************************************************************/
	#define ECM_DAC_TRIG_MODE_WRTTE_DATA            0x0000UL        /* Write data trigger. Use ECM_DacSetData() function to trigger DAC output. */
	#define ECM_DAC_TRIG_MODE_SOFTWARE              0x0010UL        /* software trigger. Use ECM_DacStartConv() function to trigger DAC output. */
	#define ECM_DAC_TRIG_MODE_LOW_LEVEL             0x0030UL        /* Low-level trigger. DAC is triggered if DAC_ST pin is low. */
	#define ECM_DAC_TRIG_MODE_HIGH_LEVEL            0x1030UL        /* High-level trigger. DAC is triggered if DAC_ST pin is high. */
	#define ECM_DAC_TRIG_MODE_RISING_EDGE           0x2030UL        /* Rising-edge trigger. DAC is triggered if DAC_ST pin detect a rising edge. */
	#define ECM_DAC_TRIG_MODE_FALLING_EDGE          0x3030UL        /* Falling-edge trigger. DAC is triggered if DAC_ST pin detect a falling edge. */


	 /**
	  * Open DAC device and Set DAC trigger mode
	  *
	  * @param  mode				: ADC mode. See ECM_DAC_TRIG_MODE_## definitions.
	  *
	  * @return					: 1 for success; 0 for timeout; -1 for invalid input parameters.
	  */
	ECM_DLL_SYMBOL int ECM_DacOpen(uint32_t mode);

	/**
	 * Close DAC device.
	 *
	 * @return					: 1 for success; 0 for timeout.
	 */
	ECM_DLL_SYMBOL int ECM_DacClose(void);

	/**
	  * Set delay time for DAC to become stable.
	 *
	 * @param  delay			: Delay time in micro second. The range is 0 to 1023/96.
	 *
	 * @return					: 1 for success; 0 for timeout; -1 for invalid input parameters.
	 */
	ECM_DLL_SYMBOL int ECM_DacSetDelayTime(uint32_t delay);

	/**
	 * Set DAC data value
	 *
	 * @param  data 			: DAC data value.
	 *
	 * @return					: 1 for success; 0 for timeout; -1 for invalid input parameters.
	 */
	ECM_DLL_SYMBOL int ECM_DacSetData(uint32_t data);

	/**
	 * Start DAC convert.
	 *
	 * @return					: 1 for success; 0 for timeout.
	 */
	ECM_DLL_SYMBOL int ECM_DacStartConv(void);


	//Enc
	/******************************************************************************
	 * ENC_MODE Definitions
	 ******************************************************************************/
#define ECM_ENC_MODE_X4_FREE            0x0UL /* X4 free-counting Mode */
#define ECM_ENC_MODE_X2_FREE            0x1UL /* X2 free-counting Mode */
#define ECM_ENC_MODE_X4_COMP            0x2UL /* X4 compare-counting Mode */
#define ECM_ENC_MODE_X2_COMP            0x3UL /* X2 compare-counting Mode */

	 /**
	  * Open and Set Encoder mode
	  *
	  * @param  mode				: Encoder mode. See ECM_ENC_MODE_## definitions.
	  *
	  * @return					: 1 for success; 0 for timeout; -1 for invalid input parameters.
	  */
	ECM_DLL_SYMBOL int ECM_EncOpen(uint8_t mode);
	ECM_DLL_SYMBOL int ECM_EncClose(void);
	/**
	 * Start Encoder counting
	 *
	 * @return					: 1 for success; 0 for timeout.
	 */
	ECM_DLL_SYMBOL int ECM_EncStart(void);

	/**
	 * Stop Encoder counting
	 *
	 * @return					: 1 for success; 0 for timeout.
	 */
	ECM_DLL_SYMBOL int ECM_EncStop(void);

	/**
	 * Get Encoder counter value
	 *
	 * @param  count			: Encoder counter value pointer. The encoder counter value is filled in *(@count) if success.
	 *
	 * @return					: 1 for success; 0 for timeout; -1 for invalid input parameters.
	 */
	ECM_DLL_SYMBOL int ECM_EncGetCount(uint32_t *count);

	ECM_DLL_SYMBOL int ECM_EncClrCount(void);
	ECM_DLL_SYMBOL int ECM_EncGetLatchCount(uint32_t *count);
	ECM_DLL_SYMBOL int ECM_EncClrLatchCount(void);
	ECM_DLL_SYMBOL int ECM_EncEnableLatch(int nEnable);
	ECM_DLL_SYMBOL int ECM_EncSetCount(uint32_t count);

	//GPIO
	/******************************************************************************

	/******************************************************************************
	 * GPIO_MODE Definitions
	 ******************************************************************************/
#define ECM_GPIO_MODE_INPUT          0x0UL /* Input Mode */
#define ECM_GPIO_MODE_OUTPUT         0x1UL /* Output Mode */
#define ECM_GPIO_MODE_OPEN_DRAIN     0x2UL /* Open-Drain Mode */
#define ECM_GPIO_MODE_BIDIR          0x3UL /* Quasi-bidirectional Mode */
	 /******************************************************************************
	  * GPIO Interrupt Type Definitions
	  ******************************************************************************/
#define ECM_GPIO_INT_DIABLE     	0x0UL /* Disable Interrupt */
#define ECM_GPIO_INT_BOTH_EDGE      0x3UL /* Interrupt enable by both Rising Edge and Falling Edge */
#define ECM_GPIO_INT_FALLING        0x4UL /* Interrupt enable by Input Falling Edge */
#define ECM_GPIO_INT_RISING         0x5UL /* Interrupt enable by Input Rising Edge */

	  /******************************************************************************
	   * GPIO Pull Select Definitions
	   ******************************************************************************/
#define ECM_GPIO_PUSEL_DISABLE          0x0UL           /* Pull Select Disable Mode */
#define ECM_GPIO_PUSEL_PULL_UP          0x1UL           /* Pull-up Mode */
#define ECM_GPIO_PUSEL_PULL_DOWN        0x2UL           /* Pull-down Mode */


	   /**
		* Set GPIO mode
		*
		* @param  ch				: GPIO channel. The valid range is from 0 to 15.
		* @param  direction		: IO direction. See ECM_GPIO_MODE_## definitions.
		* @param  pusel			: Pull select. See ECM_GPIO_PUSEL_## definitions.
		*
		* @return					: 1 for success; 0 for timeout; -1 for invalid input parameters.
		*/
	ECM_DLL_SYMBOL int ECM_GpioSetMode(uint8_t ch, uint8_t direction, uint8_t pusel);


	/**
	 * Enable/Disable Debounce mode
	 *
	 * @param  ch				: GPIO channel. The valid range is from 0 to 15.
	 * @param  enable			: IO direction. 1 for enable debounce; 0 for disable debounce.
	 *
	 * @return					: 1 for success; 0 for timeout; -1 for invalid input parameters.
	 */
	ECM_DLL_SYMBOL int ECM_GpioEnableDebounce(uint8_t ch, uint8_t enable);


	/**
	 * Set Debounce Clock
	 *
	 * @param  source			: 1 for 10K clock source; 0 for 192M clock source
	 * @param  clock			: Debounce cycle. The sampling cycle is 2^(@clock)*(clock source). The valid range is from 0 to 15.
	 *
	 * @return					: 1 for success; 0 for timeout; -1 for invalid input parameters.
	 */
	ECM_DLL_SYMBOL int ECM_GpioSetDebounceClock(uint8_t source, uint8_t clock);

	/**
	 * Set GPIO value.
	 *
	 * @param  val				: GPIO output value. The n-th bit of @val is mapping to the n-th GPIO channel.
	 *
	 * @return					: 1 for success; 0 for timeout; -1 for invalid input parameters.
	 */
	ECM_DLL_SYMBOL int ECM_GpioSetValue(uint16_t val);

	/**
	 * Get GPIO value.
	 *
	 * @param  val				: GPIO input value pointer. The n-th bit of *(@val) is mapping to the n-th GPIO channel.
	 *
	 * @return					: 1 for success; 0 for timeout; -1 for invalid input parameters.
	 */
	ECM_DLL_SYMBOL int ECM_GpioGetValue(uint16_t *val);

	/**
	 * Enable/Disable GPIO Interrupt.
	 *
	 * @param  ch				: GPIO channel. The valid range is from 0 to 15.
	 * @param  inttype			: Interrupt type. See ECM_GPIO_INT_## definitions.
	 *
	 * @return					: 1 for success; 0 for timeout; -1 for invalid input parameters.
	 */
	ECM_DLL_SYMBOL int ECM_GpioIntEnable(uint8_t ch, uint8_t inttype);

	/**
	 * Clear GPIO Interrupt flag.
	 *
	 * @param  ch				: Clear the interrupt flag of the GPIO channel. The valid range is from 0 to 15.
	 *
	 * @return					: 1 for success; 0 for timeout; -1 for invalid input parameters.
	 */
	ECM_DLL_SYMBOL int ECM_GpioIntClear(uint8_t ch);

	/**
	 * Get GPIO Interrupt flag.
	 *
	 * @param  val				: GPIO Interrupt flag pointer. The n-th bit of *(@val) is mapping to the interrupt flag of the n-th GPIO channel.
	 *
	 * @return					: 1 for success; 0 for timeout; -1 for invalid input parameters.
	 */
	ECM_DLL_SYMBOL int ECM_GpioGetIntFlag(uint16_t *val);


	ECM_DLL_SYMBOL int ECM_GpioExtSetValue(uint32_t val);
	ECM_DLL_SYMBOL int ECM_GpioExtGetValue(uint32_t *val);
	ECM_DLL_SYMBOL int ECM_GpioExtGetIntFlag(uint32_t *val);


#ifdef __cplusplus
}
#endif

#endif /* _ECMADCDRIVER_H_ */
