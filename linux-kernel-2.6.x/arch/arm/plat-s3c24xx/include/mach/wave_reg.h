
#define		WAVE_MAC_INT_STATUS_REG									0x81000000		/* 0 */
#define		WAVE_MAC_INT_MASK_REG									0x81000004		/* 0xFFFFFF */
#define		WAVE_MAC_RESET_CLEAR_REG								0x81000008		/* 0 */
#define		WAVE_MAC_HW_VERSION_REG								0x8100000C


#define		WAVE_MAC_CCH_AC1_FRAME_CONTENTS_REG					0x81001000		/* 0 */
#define		WAVE_MAC_CCH_AC1_FRAME_INFO_REG						0x81001004		/* 0x0 */
#define		WAVE_MAC_CCH_AC1_FREE_SPACE_REG						0x81001008		/* 0x1000 */
#define		WAVE_MAC_CCH_AC2_FRAME_CONTENTS_REG					0x81001010		/* 0x0 */
#define		WAVE_MAC_CCH_AC2_FRAME_INFO_REG						0x81001014		/* 0x0 */
#define		WAVE_MAC_CCH_AC2_FREE_SPACE_REG						0x81001018		/* 0x1000 */
#define		WAVE_MAC_CCH_AC3_FRAME_CONTENTS_REG					0x81001020		/* 0x0 */
#define		WAVE_MAC_CCH_AC3_FRAME_INFO_REG						0x81001024		/* 0x0 */
#define		WAVE_MAC_CCH_AC3_FREE_SPACE_REG						0x81001028		/* 0x1000 */
#define		WAVE_MAC_CCH_AC4_FRAME_CONTENTS_REG					0x81001030		/* 0x0 */	
#define		WAVE_MAC_CCH_AC4_FRAME_INFO_REG						0x81001034		/* 0x0 */
#define		WAVE_MAC_CCH_AC4_FREE_SPACE_REG						0x81001038		/* 0x1000 */
#define		WAVE_MAC_SCH_AC1_FRAME_CONTENTS_REG					0x81001040		/* 0x0 */
#define		WAVE_MAC_SCH_AC1_FRAME_INFO_REG						0x81001044		/* 0x0 */
#define		WAVE_MAC_SCH_AC1_FREE_SPACE_REG						0x81001048		/* 0x1000 */
#define		WAVE_MAC_SCH_AC2_FRAME_CONTENTS_REG					0x81001050		/* 0x0 */
#define		WAVE_MAC_SCH_AC2_FRAME_INFO_REG						0x81001054		/* 0x0 */
#define		WAVE_MAC_SCH_AC2_FREE_SPACE_REG						0x81001058		/* 0x1000 */
#define		WAVE_MAC_SCH_AC3_FRAME_CONTENTS_REG					0x81001060		/* 0x0 */
#define		WAVE_MAC_SCH_AC3_FRAME_INFO_REG						0x81001064		/* 0x0 */	
#define		WAVE_MAC_SCH_AC3_FREE_SPACE_REG						0x81001068		/* 0x1000 */
#define		WAVE_MAC_SCH_AC4_FRAME_CONTENTS_REG					0x81001070		/* 0x0 */
#define		WAVE_MAC_SCH_AC4_FRAME_INFO_REG						0x81001074		/* 0x0 */
#define		WAVE_MAC_SCH_AC4_FREE_SPACE_REG						0x81001078		/* 0x1000 */


#define		WAVE_MAC_EXTRA_QUEUE_FRAME_CONTENTS_REG				0x81001080		/* 0x0 */
#define		WAVE_MAC_EXTRA_QUEUE_FRAME_INFO_REG					0x81001084		/* 0x0 */


#define		WAVE_MAC_RX_DATA_QUEUE_DATA_FRAME_REG				0x81001100		/* 0x0 */
#define		WAVE_MAC_RX_INFO_QUEUE_FOR_DATA_FRAME_REG			0x81001104		/* 0x0 */
#define		WAVE_MAC_RX_DATA_OVERFLOW_DISCARD_COUNT_REG		0x81001108

#define		WAVE_MAC_RX_DATA_QUEUE_FOR_MANAGE_FRAME_REG		0x81001110		/* 0x0 */
#define		WAVE_MAC_RX_INFO_QUEUE_FOR_MANAGE_FRAME_REG		0x81001114		/* 0x0 */
#define		WAVE_MAC_RX_MANAGE_OVERFLOW_DISCARD_COUNT_REG		0x81001118

#define		WAVE_MAC_TX_FRAME_COUNTER_REG							0x81002000		/* 0x0 */
#define		WAVE_MAC_RX_FRAME_COUNTER_REG							0x81002004		/* 0x0 */
#define		WAVE_MAC_CRC_ERR_COUNTER_REG							0x81002008		/* 0x0 */
#define		WAVE_MAC_PHY_ERR_COUNTER_REG							0x8100200C		/* 0x0 */
#define		WAVE_MAC_TX_DATA_COUNTER_REG							0x81002010		/* 0x0 */
#define		WAVE_MAC_TX_RTS_COUNTER_REG							0x81002014		/* 0x0 */
#define		WAVE_MAC_TX_CTS_COUNTER_REG							0x81002018		/* 0x0 */
#define		WAVE_MAC_TX_ACK_COUNTER_REG							0x8100201C		/* 0x0 */
#define		WAVE_MAC_RX_DATA_COUNTER_REG							0x81002020		/* 0x0 */
#define		WAVE_MAC_RX_MY_RTS_COUNTER_REG						0x81002024		/* 0x0 */
#define		WAVE_MAC_RX_MY_CTS_COUNTER_REG						0x81002028		/* 0x0 */
#define		WAVE_MAC_RX_MY_ACK_COUNTER_REG						0x8100202C		/* 0x0 */
#define		WAVE_MAC_TX_DISCARD_FRAME_COUNTER_REG				0x81002030		/* 0x0 */
#define		WAVE_MAC_RX_OTHER_RTS_COUNTER_REG						0x81002034		/* 0 */
#define		WAVE_MAC_RX_OTHER_CTS_COUNTER_REG						0x81002038		/* 0 */
#define		WAVE_MAC_RX_OTHER_ACK_COUNTER_REG						0x8100203C		/* 0 */

#define		WAVE_MAC_ADDR16_REG										0x81002080		/* 0, change */		
#define		WAVE_MAC_ADDR32_REG										0x81002084		/* 0x03, change */
#define		WAVE_MAC_MULTICAST0_16_REG								0x81002088		/* 0xFFFF */
#define		WAVE_MAC_MULTICAST0_32_REG								0x8100208C		/* 0xFFFFFFFF */
#define		WAVE_MAC_MULTICAST1_16_REG								0x81002090		/* 0xFFFF */
#define		WAVE_MAC_MULTICAST1_32_REG								0x81002094		/* 0xFFFFFFFF */
#define		WAVE_MAC_MULTICAST2_16_REG								0x81002098		/* 0xFFFF */
#define		WAVE_MAC_MULTICAST2_32_REG								0x8100209C		/* 0xFFFFFFFF */
#define		WAVE_MAC_SHORT_RETRY_LIMIT_REG							0x810020A0		/* 0x07 */
#define		WAVE_MAC_LONG_RETRY_LIMIT_REG							0x810020A4		/* 0x04 */
#define		WAVE_MAC_MODE_REG										0x810020A8		/* 0x20, change */
#define		WAVE_MAC_BACKOFF_SEED_REG								0x810020AC		/* 0x03, change */

#define		WAVE_MAC_MIN_CW_FOR_AC0_REG							0x81002100		/* 0x0F */
#define		WAVE_MAC_MAX_CW_FOR_AC0_REG							0x81002104		/* 0x3FF */
#define		WAVE_MAC_MIN_CW_FOR_AC1_REG							0x81002108		/* 0x07 */
#define		WAVE_MAC_MAX_CW_FOR_AC1_REG							0x8100210C		/* 0x3FF */
#define		WAVE_MAC_MIN_CW_FOR_AC2_REG							0x81002110		/* 0x03 */
#define		WAVE_MAC_MAX_CW_FOR_AC2_REG							0x81002114		/* 0x0F */
#define		WAVE_MAC_MIN_CW_FOR_AC3_REG							0x81002118		/* 0x03 */
#define		WAVE_MAC_MAX_CW_FOR_AC3_REG							0x8100211C		/* 0x07 */	
#define		WAVE_MAC_AIFSN_FOR_AC0_REG								0x81002120		/* 0x09 */	
#define		WAVE_MAC_AIFSN_FOR_AC1_REG								0x81002124		/* 0x06 */
#define		WAVE_MAC_AIFSN_FOR_AC2_REG								0x81002128		/* 0x03 */
#define		WAVE_MAC_AIFSN_FOR_AC3_REG								0x8100212C		/* 0x02 */


#define		WAVE_MAC_RSE_CCH_TIME_REG								0x81002180		/* 0x1388, change */
#define		WAVE_MAC_OBU_CCH_TIME_REG								0x81002184		/* 0x4e20 */
#define		WAVE_MAC_V2I_SCH_TIME_REG								0x81002188		/* 0x11170, change */
#define		WAVE_MAC_V2V_SCH_TIME_REG								0x8100218C		/* 0x0, change */
#define		WAVE_MAC_CCH_SCH_CYCLE_TIME_REG						0x81002190		/* 0x186a0 */
#define		WAVE_MAC_V2IV_SCH_REPEAT_CYCLE_TIME_REG				0x81002194		/* 0x186a0 */
#define		WAVE_MAC_SYNC_TOLERANCE_REG							0x81002198		/* 0x3e8, change */
#define		WAVE_MAC_RF_SWITCH_TIME_REG							0x8100219C		/* 0x3e8, change */
#define		WAVE_MAC_TIME_SLOT_LEN_REG								0x810021A0		/* 0x1388 */	
#define		WAVE_MAC_NUM_OF_TIME_SLOT_FOR_CCH_REG				0x810021A4		/* 0x04, change */
#define		WAVE_MAC_NUM_OF_TIME_SLOT_FOR_V2I_SCH_REG			0x810021A8		/* 0x0e, change */
#define		WAVE_MAC_NUM_OF_TIME_SLOT_FOR_V2V_SCH_REG			0x810021AC		/* 0x0, change */
#define		WAVE_MAC_NUM_OF_TIME_SLOT_REG							0x810021B0


#define		WAVE_MAC_TSF_HTIMER_REG									0x810021C0		/* 0x0 */
#define		WAVE_MAC_TSF_LTIMER_REG									0x810021C4		/* 0x0 */
#define		WAVE_MAC_RX_HTIMER_REG									0x810021C8		/* 0x0 */
#define		WAVE_MAC_RX_LTIMER_REG									0x810021CC		/* 0x0 */
#define		WAVE_MAC_TX_HTIMER_REG									0x810021D0		/* 0x0 */
#define		WAVE_MAC_TX_LTIMER_REG									0x810021D4		/* 0x0 */
#define		WAVE_MAC_TSF_UPDATE_RANGE_REG							0x810021D8

#define		WAVE_MAC_TSF_RX_DELAY_REG								0x810021DC
#define		WAVE_MAC_TSF_TX_DELAY_3M_REG							0x810021E0
#define		WAVE_MAC_TSF_TX_DELAY_45M_REG							0x810021E4
#define		WAVE_MAC_TSF_TX_DELAY_6M_REG							0x810021E8
#define		WAVE_MAC_TSF_TX_DELAY_9M_REG							0x810021EC
#define		WAVE_MAC_TSF_TX_DELAY_12M_REG							0x810021F0
#define		WAVE_MAC_TSF_TX_DELAY_18M_REG							0x810021F4
#define		WAVE_MAC_TSF_TX_DELAY_24M_REG							0x810021F8
#define		WAVE_MAC_TSF_TX_DELAY_27M_REG							0x810021FC



/* Modem Register Define */
#define		WAVE_MODEM_PK_ON_THRESHOLD_COUNTER_REG				0x81010000		/* 0x132 */		
#define		WAVE_MODEM_PK_OFF_WINDOW_REG							0x81010004		/* 0xfa00 */
#define		WAVE_MODEM_PK_DETECT_THRESHOLD_REG					0x81010008		/* 0x800 */
#define		WAVE_MODEM_PK_ON_THRESHOLD_VALUE_REG					0x8101000C		/* 0x45 */
#define		WAVE_MODEM_PK_OFF_THRESHOLD_VALUE_REG				0x81010010		/* 0x45 */
#define		WAVE_MODEM_PK_HIGH_POWER_THRESHOLD_REG				0x81010014		/* 0x7ff */
#define		WAVE_MODEM_FOC_REG0										0x81010018		/* 0x20c0 */
#define		WAVE_MODEM_TX_CTRL_REG0									0x8101001C		/* 0x1dd */
#define		WAVE_MODEM_TX_CTRL_REG1									0x81010020		/* 0x0 */
#define		WAVE_MODEM_LNA_DETECT_VALUE_REG						0x81010024		/* 0x245 */
#define		WAVE_MODEM_LNA_GAIN_DEFAULT_VALUE_REG				0x81010028		/* 0x3838 */
#define		WAVE_MODEM_PWR_NOISE_AGC_TRIGGER_VALUE_REG			0x8101002C		/* 0x1414 */
#define		WAVE_MODEM_AGC_MANAGE_REG								0x81010030		/* 0x609b */
#define		WAVE_MODEM_RF_CH1_ID_REG								0x81010034		/* 0xea */
#define		WAVE_MODEM_RF_CH1_FD_REG								0x81010038		/* 0x0 */
#define		WAVE_MODEM_RF_CH2_ID_REG								0x8101003C		/* 0xea */
#define		WAVE_MODEM_RF_CH2_FD_REG								0x81010040		/* 0x0 */
#define		WAVE_MODEM_RF_CH3_ID_REG								0x81010044		/* 0xea */
#define		WAVE_MODEM_RF_CH3_FD_REG								0x81010048		/* 0x0 */
#define		WAVE_MODEM_TXPWR_SET1_REG								0x8101004C		/* 0x0, change */
#define		WAVE_MODEM_TXPWR_SET2_REG								0x81010050		/* 0x0, change */
#define		WAVE_MODEM_TXPWR_SET3_REG								0x81010054		/* 0x0, change */
#define		WAVE_MODEM_TXPWR_SET4_REG								0x81010058		/* 0x0, change */

#define		WAVE_MODEM_MID_DURATION_REG							0x81010060		/* 0x44aa */
#define		WAVE_MODEM_RF_FREQ_RMS_PWR_REG						0x81010064		/* 0x0 */
#define		WAVE_MODEM_TEST_MODE_SW_REG							0x81010068		/* 0x2f */
#define		WAVE_MODEM_RF_STATE_REG								0x8101006C		/* 0xb */
#define		WAVE_MODEM_RF_STATUS_CMD_REG							0x81010070		/* 0x2002, change */
#define		WAVE_MODEM_RF_REG0										0x81010074		/* 0x1140 */
#define		WAVE_MODEM_RF_REG1										0x81010078		/* 0xca */
#define		WAVE_MODEM_RF_STANDBY_REG								0x8101007C		/* 0x10bf */
#define		WAVE_MODEM_RF_ID_RATIO_REG								0x81010080		/* 0xea */
#define		WAVE_MODEM_RF_FD_RATIO_REG								0x81010084		/* 0x0 */
#define		WAVE_MODEM_RF_BS_AND_PLL_REG							0x81010088		/* 0x1865 */
#define		WAVE_MODEM_RF_CALIBRATION_REG							0x8101008C		/* 0x1c00 */
#define		WAVE_MODEM_RF_LPF_REG									0x81010090		/* 0x0 */
#define		WAVE_MODEM_RF_RX_CONT_RSSI_REG						0x81010094		/* 0xc25 */
#define		WAVE_MODEM_RF_TX_LINEAR_GAIN_REG						0x81010098		/* 0x6cd */
#define		WAVE_MODEM_RF_PA_BIAS_DAC_REG							0x8101009C		/* 0x3c0 */
#define		WAVE_MODEM_RF_RX_GAIN_REG								0x810100A0		/* 0x0 */
#define		WAVE_MODEM_RF_TX_VGA_GAIN_REG							0x810100A4		/* 0x0 */
#define		WAVE_MODEM_PACKET_DETECT_THRESHOLD_H_REG			0x810100A8		/* 0x1919 */
#define		WAVE_MODEM_PACKET_DETECT_THRESHOLD_L_REG			0x810100AC		/* 0x3cbb */

#define		WAVE_MODEM_RMS_POWER_VAL1_REG							0x810100B0		/* 0x1b */
#define		WAVE_MODEM_RMS_POWER_VAL2_REG							0x810100B4		/* 0x22 */
#define		WAVE_MODEM_RMS_POWER_VAL3_REG							0x810100B8		/* 0x2b */
#define		WAVE_MODEM_RMS_POWER_VAL4_REG							0x810100BC		/* 0x37 */
#define		WAVE_MODEM_RMS_POWER_VAL5_REG							0x810100C0		/* 0x45 */
#define		WAVE_MODEM_RMS_POWER_VAL6_REG							0x810100C4		/* 0x57 */
#define		WAVE_MODEM_RMS_POWER_VAL7_REG							0x810100C8		/* 0x6e */
#define		WAVE_MODEM_RMS_POWER_VAL8_REG							0x810100CC		/* 0x8b */
#define		WAVE_MODEM_RMS_POWER_VAL9_REG							0x810100D0		/* 0xaf */
#define		WAVE_MODEM_RMS_POWER_VAL10_REG						0x810100D4		/* 0xdd */
#define		WAVE_MODEM_RMS_POWER_VAL11_REG						0x810100D8		/* 0x117 */
#define		WAVE_MODEM_RMS_POWER_VAL12_REG						0x810100DC		/* 0x160 */
#define		WAVE_MODEM_RMS_POWER_VAL13_REG						0x810100E0		/* 0x1bc */
#define		WAVE_MODEM_RMS_POWER_VAL14_REG						0x810100E4		/* 0x22f */
#define		WAVE_MODEM_MID_THRESHOLD3_REG							0x810100E8		/* 0xa8 */
#define		WAVE_MODEM_MID_THRESHOLD45_REG						0x810100EC		/* 0xfc */
#define		WAVE_MODEM_MID_THRESHOLD6_REG							0x810100F0		/* 0x150 */
#define		WAVE_MODEM_MID_THRESHOLD9_REG							0x810100F4		/* 0x1f8 */
#define		WAVE_MODEM_MID_THRESHOLD12_REG						0x810100F8		/* 0x2a0 */
#define		WAVE_MODEM_MID_THRESHOLD18_REG						0x810100FC		/* 0x3f0 */
#define		WAVE_MODEM_MID_THRESHOLD24_REG						0x81010100		/* 0x540 */
#define		WAVE_MODEM_MID_THRESHOLD27_REG						0x81010104		/* 0x5e8 */
#define		WAVE_MODEM_MID_CYCLE3_REG								0x81010108		/* 0xa8 */
#define		WAVE_MODEM_MID_CYCLE45_REG								0x8101010C		/* 0xfc */
#define		WAVE_MODEM_MID_CYCLE6_REG								0x81010110		/* 0x150 */
#define		WAVE_MODEM_MID_CYCLE9_REG								0x81010114		/* 0x1f8 */
#define		WAVE_MODEM_MID_CYCLE12_REG								0x81010118		/* 0x2a0 */
#define		WAVE_MODEM_MID_CYCLE18_REG								0x8101011C		/* 0x3f0 */
#define		WAVE_MODEM_MID_CYCLE24_REG								0x81010120		/* 0x540 */
#define		WAVE_MODEM_MID_CYCLE27_REG								0x81010124		/* 0x5e8 */

#define		WAVE_MODEM_RX_SIGNAL_FIELD1_REG						0x81010148		/* 0x0 */
#define		WAVE_MODEM_RX_SIGNAL_FIELD2_REG						0x8101014C		/* 0x0 */
#define		WAVE_MODEM_PHY_NO_ERR_COUNTER_L_REG					0x81010150
#define		WAVE_MODEM_PHY_NO_ERR_COUNTER_H_REG					0x81010154
#define		WAVE_MODEM_PHY_CARRIER_LOST_ERR_COUNTER_L_REG		0x81010158
#define		WAVE_MODEM_PHY_CARRIER_LOST_ERR_COUNTER_H_REG		0x8101015C
#define		WAVE_MODEM_PHY_UNSUPPORT_RATE_ERR_COUNTER_L_REG	0x81010160
#define		WAVE_MODEM_PHY_UNSUPPORT_RATE_ERR_COUNTER_H_REG	0x81010164
#define		WAVE_MODEM_PHY_FORMAT_ERR_COUNTER_L_REG				0x81010168
#define		WAVE_MODEM_PHY_FORMAT_ERR_COUNTER_H_REG				0x8101016C
#define		WAVE_MODEM_VERSION_VALUE_REG							0x81010170

#define		WAVE_TOP_RESET_CLEAR_REG								0x81020008
#define		WAVE_TOP_SYNC_MODE_REG									0x8102000C
#define		WAVE_TOP_SYNC_REG										0x81020010

/* Interrupt Status Register */
#define		SCH_AC1_TX_COMPLETE_INT									0x1
#define		SCH_AC2_TX_COMPLETE_INT									0x2
#define		SCH_AC3_TX_COMPLETE_INT									0x4
#define		SCH_AC4_TX_COMPLETE_INT									0x8
#define		SCH_AC1_RETX_LIMIT_OVERFLOW_INT							0x10
#define		SCH_AC2_RETX_LIMIT_OVERFLOW_INT							0x20
#define		SCH_AC3_RETX_LIMIT_OVERFLOW_INT							0x40
#define		SCH_AC4_RETX_LIMIT_OVERFLOW_INT							0x80
#define		CCH_AC1_TX_COMPLETE_INT									0x100
#define		CCH_AC2_TX_COMPLETE_INT									0x200
#define		CCH_AC3_TX_COMPLETE_INT									0x400
#define		CCH_AC4_TX_COMPLETE_INT									0x800
#define		CCH_AC1_RETX_LIMIT_OVERFLOW_INT							0x1000
#define		CCH_AC2_RETX_LIMIT_OVERFLOW_INT							0x2000
#define		CCH_AC3_RETX_LIMIT_OVERFLOW_INT							0x4000
#define		CCH_AC4_RETX_LIMIT_OVERFLOW_INT							0x8000
#define		RX_DATA_FRAME_INT										0x10000
#define		RX_MANAGEMENT_FRAME_INT									0x20000
#define		DATA_QUEUE_OVERFLOW_INT									0x40000
#define		MANAGEMENT_QUEUE_OVERFLOW_INT							0x80000
#define		DATA_QUEUE_OVERFLOW_CLEAR_INT							0x100000
#define		MANAGEMENT_QUEUE_OVERFLOW_CLEAR_INT					0x200000
#define		TX_START_OF_EXTRA_QUEUE_INT								0x400000

/* SHKO, [주의] 4096과 1024로 정의하면 커널이 부팅하다가 죽음. */
#if 0
#define 		WAVE_RX_QUEUE_SIZE											4096
#define 		WAVE_RX_QUEUE_NUM											1024
#else
#define 		WAVE_RX_QUEUE_SIZE										2048
#define 		WAVE_RX_QUEUE_NUM										256
#endif

typedef struct
{
	unsigned int rssi;
	unsigned int data_rate;
	unsigned int len;
	unsigned int buf[WAVE_RX_QUEUE_SIZE];
}	RX_FRAME_DATA;

typedef struct
{
	unsigned int rssi;
	unsigned int data_rate;
}	RX_DATA_FRAME_INFO;


/* Define IO macros. */

/* 8 bit access */
#define SD_OUTBYTE(reg, data)   ( (*( (volatile U1 *) (reg) ) ) = (U1)(data) )
#define SD_INBYTE(reg)          (  *( (volatile U1 *) (reg) ) )

/* 16 bit access */
#define SD_OUTWORD(reg, data)   ( (*( (volatile U2 *) (reg) ) ) = (U2)(data) )
#define SD_INWORD(reg)          (  *( (volatile U2 *) (reg) ) )

/* 32 bit access */
#define SD_OUTDWORD(reg, data)  ( (*( (volatile U4 *) (reg) ) ) = (U4)(data) )
#define SD_INDWORD(reg)         (  *( (volatile U4 *) (reg) ) )

#define ENDIAN_SWAP16(A)	((((unsigned short)(A) & 0xff00) >> 8) | \
							 (((unsigned short)(A) & 0x00ff) << 8))
							 
#define ENDIAN_SWAP32(A)	((((unsigned int)(A) & 0xff000000) >> 24) | \
							 (((unsigned int)(A) & 0x00ff0000) >> 8) | \
							 (((unsigned int)(A) & 0x0000ff00) << 8) | \
							 (((unsigned int)(A) & 0x000000ff) << 24))





