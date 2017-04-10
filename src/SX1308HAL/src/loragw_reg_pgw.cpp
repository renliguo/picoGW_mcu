/*
 / _____)             _              | |
( (____  _____ ____ _| |_ _____  ____| |__
 \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 _____) ) ____| | | || |_| ____( (___| | | |
(______/|_____)_|_|_| \__)_____)\____)_| |_|
  (C)2017 Semtech


*/
#include "SX1308.h"
#include "loragw_reg.h"
#include "CmdUSB.h"
#include "loragw_hal.h"
#include "board.h"

const struct lgw_reg_s loregs[LGW_TOTALREGS] = {
    {-1, 0, 0, 0, 2, 0, 0},   /* PAGE_REG */
    {-1, 0, 7, 0, 1, 0, 0},   /* SOFT_RESET */
    {-1, 1, 0, 0, 8, 1, 103}, /* VERSION */
    {-1, 2, 0, 0, 16, 0, 0},  /* RX_DATA_BUF_ADDR */
    {-1, 4, 0, 0, 8, 0, 0},   /* RX_DATA_BUF_DATA */
    {-1, 5, 0, 0, 8, 0, 0},   /* TX_DATA_BUF_ADDR */
    {-1, 6, 0, 0, 8, 0, 0},   /* TX_DATA_BUF_DATA */
    {-1, 7, 0, 0, 8, 0, 0},   /* CAPTURE_RAM_ADDR */
    {-1, 8, 0, 0, 8, 1, 0},   /* CAPTURE_RAM_DATA */
    {-1, 9, 0, 0, 8, 0, 0},   /* MCU_PROM_ADDR */
    {-1, 10, 0, 0, 8, 0, 0},  /* MCU_PROM_DATA */
    {-1, 11, 0, 0, 8, 0, 0},  /* RX_PACKET_DATA_FIFO_NUM_STORED */
    {-1, 12, 0, 0, 16, 1, 0}, /* RX_PACKET_DATA_FIFO_ADDR_POINTER */
    {-1, 14, 0, 0, 8, 1, 0},  /* RX_PACKET_DATA_FIFO_STATUS */
    {-1, 15, 0, 0, 8, 1, 0},  /* RX_PACKET_DATA_FIFO_PAYLOAD_SIZE */
    {-1, 16, 0, 0, 1, 0, 0},  /* MBWSSF_MODEM_ENABLE */
    {-1, 16, 1, 0, 1, 0, 0},  /* CONCENTRATOR_MODEM_ENABLE */
    {-1, 16, 2, 0, 1, 0, 0},  /* FSK_MODEM_ENABLE */
    {-1, 16, 3, 0, 1, 0, 0},  /* GLOBAL_EN */
    {-1, 17, 0, 0, 1, 0, 1},  /* CLK32M_EN */
    {-1, 17, 1, 0, 1, 0, 1},  /* CLKHS_EN */
    {-1, 18, 0, 0, 1, 0, 0},  /* START_BIST0 */
    {-1, 18, 1, 0, 1, 0, 0},  /* START_BIST1 */
    {-1, 18, 2, 0, 1, 0, 0},  /* CLEAR_BIST0 */
    {-1, 18, 3, 0, 1, 0, 0},  /* CLEAR_BIST1 */
    {-1, 19, 0, 0, 1, 1, 0},  /* BIST0_FINISHED */
    {-1, 19, 1, 0, 1, 1, 0},  /* BIST1_FINISHED */
    {-1, 20, 0, 0, 1, 1, 0},  /* MCU_AGC_PROG_RAM_BIST_STATUS */
    {-1, 20, 1, 0, 1, 1, 0},  /* MCU_ARB_PROG_RAM_BIST_STATUS */
    {-1, 20, 2, 0, 1, 1, 0},  /* CAPTURE_RAM_BIST_STATUS */
    {-1, 20, 3, 0, 1, 1, 0},  /* CHAN_FIR_RAM0_BIST_STATUS */
    {-1, 20, 4, 0, 1, 1, 0},  /* CHAN_FIR_RAM1_BIST_STATUS */
    {-1, 21, 0, 0, 1, 1, 0},  /* CORR0_RAM_BIST_STATUS */
    {-1, 21, 1, 0, 1, 1, 0},  /* CORR1_RAM_BIST_STATUS */
    {-1, 21, 2, 0, 1, 1, 0},  /* CORR2_RAM_BIST_STATUS */
    {-1, 21, 3, 0, 1, 1, 0},  /* CORR3_RAM_BIST_STATUS */
    {-1, 21, 4, 0, 1, 1, 0},  /* CORR4_RAM_BIST_STATUS */
    {-1, 21, 5, 0, 1, 1, 0},  /* CORR5_RAM_BIST_STATUS */
    {-1, 21, 6, 0, 1, 1, 0},  /* CORR6_RAM_BIST_STATUS */
    {-1, 21, 7, 0, 1, 1, 0},  /* CORR7_RAM_BIST_STATUS */
    {-1, 22, 0, 0, 1, 1, 0},  /* MODEM0_RAM0_BIST_STATUS */
    {-1, 22, 1, 0, 1, 1, 0},  /* MODEM1_RAM0_BIST_STATUS */
    {-1, 22, 2, 0, 1, 1, 0},  /* MODEM2_RAM0_BIST_STATUS */
    {-1, 22, 3, 0, 1, 1, 0},  /* MODEM3_RAM0_BIST_STATUS */
    {-1, 22, 4, 0, 1, 1, 0},  /* MODEM4_RAM0_BIST_STATUS */
    {-1, 22, 5, 0, 1, 1, 0},  /* MODEM5_RAM0_BIST_STATUS */
    {-1, 22, 6, 0, 1, 1, 0},  /* MODEM6_RAM0_BIST_STATUS */
    {-1, 22, 7, 0, 1, 1, 0},  /* MODEM7_RAM0_BIST_STATUS */
    {-1, 23, 0, 0, 1, 1, 0},  /* MODEM0_RAM1_BIST_STATUS */
    {-1, 23, 1, 0, 1, 1, 0},  /* MODEM1_RAM1_BIST_STATUS */
    {-1, 23, 2, 0, 1, 1, 0},  /* MODEM2_RAM1_BIST_STATUS */
    {-1, 23, 3, 0, 1, 1, 0},  /* MODEM3_RAM1_BIST_STATUS */
    {-1, 23, 4, 0, 1, 1, 0},  /* MODEM4_RAM1_BIST_STATUS */
    {-1, 23, 5, 0, 1, 1, 0},  /* MODEM5_RAM1_BIST_STATUS */
    {-1, 23, 6, 0, 1, 1, 0},  /* MODEM6_RAM1_BIST_STATUS */
    {-1, 23, 7, 0, 1, 1, 0},  /* MODEM7_RAM1_BIST_STATUS */
    {-1, 24, 0, 0, 1, 1, 0},  /* MODEM0_RAM2_BIST_STATUS */
    {-1, 24, 1, 0, 1, 1, 0},  /* MODEM1_RAM2_BIST_STATUS */
    {-1, 24, 2, 0, 1, 1, 0},  /* MODEM2_RAM2_BIST_STATUS */
    {-1, 24, 3, 0, 1, 1, 0},  /* MODEM3_RAM2_BIST_STATUS */
    {-1, 24, 4, 0, 1, 1, 0},  /* MODEM4_RAM2_BIST_STATUS */
    {-1, 24, 5, 0, 1, 1, 0},  /* MODEM5_RAM2_BIST_STATUS */
    {-1, 24, 6, 0, 1, 1, 0},  /* MODEM6_RAM2_BIST_STATUS */
    {-1, 24, 7, 0, 1, 1, 0},  /* MODEM7_RAM2_BIST_STATUS */
    {-1, 25, 0, 0, 1, 1, 0},  /* MODEM_MBWSSF_RAM0_BIST_STATUS */
    {-1, 25, 1, 0, 1, 1, 0},  /* MODEM_MBWSSF_RAM1_BIST_STATUS */
    {-1, 25, 2, 0, 1, 1, 0},  /* MODEM_MBWSSF_RAM2_BIST_STATUS */
    {-1, 26, 0, 0, 1, 1, 0},  /* MCU_AGC_DATA_RAM_BIST0_STATUS */
    {-1, 26, 1, 0, 1, 1, 0},  /* MCU_AGC_DATA_RAM_BIST1_STATUS */
    {-1, 26, 2, 0, 1, 1, 0},  /* MCU_ARB_DATA_RAM_BIST0_STATUS */
    {-1, 26, 3, 0, 1, 1, 0},  /* MCU_ARB_DATA_RAM_BIST1_STATUS */
    {-1, 26, 4, 0, 1, 1, 0},  /* TX_TOP_RAM_BIST0_STATUS */
    {-1, 26, 5, 0, 1, 1, 0},  /* TX_TOP_RAM_BIST1_STATUS */
    {-1, 26, 6, 0, 1, 1, 0},  /* DATA_MNGT_RAM_BIST0_STATUS */
    {-1, 26, 7, 0, 1, 1, 0},  /* DATA_MNGT_RAM_BIST1_STATUS */
    {-1, 27, 0, 0, 4, 0, 0},  /* GPIO_SELECT_INPUT */
    {-1, 28, 0, 0, 4, 0, 0},  /* GPIO_SELECT_OUTPUT */
    {-1, 29, 0, 0, 5, 0, 0},  /* GPIO_MODE */
    {-1, 30, 0, 0, 5, 1, 0},  /* GPIO_PIN_REG_IN */
    {-1, 31, 0, 0, 5, 0, 0},  /* GPIO_PIN_REG_OUT */
    {-1, 32, 0, 0, 8, 1, 0},  /* MCU_AGC_STATUS */
    {-1, 125, 0, 0, 8, 1, 0}, /* MCU_ARB_STATUS */
    {-1, 126, 0, 0, 8, 1, 1}, /* CHIP_ID */
    {-1, 127, 0, 0, 1, 0, 1}, /* EMERGENCY_FORCE_HOST_CTRL */
    {0, 33, 0, 0, 1, 0, 0},   /* RX_INVERT_IQ */
    {0, 33, 1, 0, 1, 0, 1},   /* MODEM_INVERT_IQ */
    {0, 33, 2, 0, 1, 0, 0},   /* MBWSSF_MODEM_INVERT_IQ */
    {0, 33, 3, 0, 1, 0, 0},   /* RX_EDGE_SELECT */
    {0, 33, 4, 0, 1, 0, 0},   /* MISC_RADIO_EN */
    {0, 33, 5, 0, 1, 0, 0},   /* FSK_MODEM_INVERT_IQ */
    {0, 34, 0, 0, 4, 0, 7},   /* FILTER_GAIN */
    {0, 35, 0, 0, 8, 0, 240}, /* RADIO_SELECT */
    {0, 36, 0, 1, 13, 0, -384}, /* IF_FREQ_0 */
    {0, 38, 0, 1, 13, 0, -128}, /* IF_FREQ_1 */
    {0, 40, 0, 1, 13, 0, 128}, /* IF_FREQ_2 */
    {0, 42, 0, 1, 13, 0, 384}, /* IF_FREQ_3 */
    {0, 44, 0, 1, 13, 0, -384}, /* IF_FREQ_4 */
    {0, 46, 0, 1, 13, 0, -128}, /* IF_FREQ_5 */
    {0, 48, 0, 1, 13, 0, 128}, /* IF_FREQ_6 */
    {0, 50, 0, 1, 13, 0, 384}, /* IF_FREQ_7 */
    {0, 52, 0, 1, 13, 0, 0},  /* IF_FREQ_8 */
    {0, 54, 0, 1, 13, 0, 0},  /* IF_FREQ_9 */
    {0, 64, 0, 0, 1, 0, 0},  /* CHANN_OVERRIDE_AGC_GAIN */
    {0, 64, 1, 0, 4, 0, 7},  /* CHANN_AGC_GAIN */
    {0, 65, 0, 0, 7, 0, 0},  /* CORR0_DETECT_EN */
    {0, 66, 0, 0, 7, 0, 0},  /* CORR1_DETECT_EN */
    {0, 67, 0, 0, 7, 0, 0},  /* CORR2_DETECT_EN */
    {0, 68, 0, 0, 7, 0, 0},  /* CORR3_DETECT_EN */
    {0, 69, 0, 0, 7, 0, 0},  /* CORR4_DETECT_EN */
    {0, 70, 0, 0, 7, 0, 0},  /* CORR5_DETECT_EN */
    {0, 71, 0, 0, 7, 0, 0},  /* CORR6_DETECT_EN */
    {0, 72, 0, 0, 7, 0, 0},  /* CORR7_DETECT_EN */
    {0, 73, 0, 0, 1, 0, 0},  /* CORR_SAME_PEAKS_OPTION_SF6 */
    {0, 73, 1, 0, 1, 0, 1},  /* CORR_SAME_PEAKS_OPTION_SF7 */
    {0, 73, 2, 0, 1, 0, 1},  /* CORR_SAME_PEAKS_OPTION_SF8 */
    {0, 73, 3, 0, 1, 0, 1},  /* CORR_SAME_PEAKS_OPTION_SF9 */
    {0, 73, 4, 0, 1, 0, 1},  /* CORR_SAME_PEAKS_OPTION_SF10 */
    {0, 73, 5, 0, 1, 0, 1},  /* CORR_SAME_PEAKS_OPTION_SF11 */
    {0, 73, 6, 0, 1, 0, 1},  /* CORR_SAME_PEAKS_OPTION_SF12 */
    {0, 74, 0, 0, 4, 0, 4},  /* CORR_SIG_NOISE_RATIO_SF6 */
    {0, 74, 4, 0, 4, 0, 4},  /* CORR_SIG_NOISE_RATIO_SF7 */
    {0, 75, 0, 0, 4, 0, 4},  /* CORR_SIG_NOISE_RATIO_SF8 */
    {0, 75, 4, 0, 4, 0, 4},  /* CORR_SIG_NOISE_RATIO_SF9 */
    {0, 76, 0, 0, 4, 0, 4},  /* CORR_SIG_NOISE_RATIO_SF10 */
    {0, 76, 4, 0, 4, 0, 4},  /* CORR_SIG_NOISE_RATIO_SF11 */
    {0, 77, 0, 0, 4, 0, 4},  /* CORR_SIG_NOISE_RATIO_SF12 */
    {0, 78, 0, 0, 4, 0, 4},  /* CORR_NUM_SAME_PEAK */
    {0, 78, 4, 0, 3, 0, 5},  /* CORR_MAC_GAIN */
    {0, 81, 0, 0, 12, 0, 0}, /* ADJUST_MODEM_START_OFFSET_RDX4 */
    {0, 83, 0, 0, 12, 0, 4092}, /* ADJUST_MODEM_START_OFFSET_SF12_RDX4 */
    {0, 85, 0, 0, 8, 0, 7},  /* DBG_CORR_SELECT_SF */
    {0, 86, 0, 0, 8, 0, 0},  /* DBG_CORR_SELECT_CHANNEL */
    {0, 87, 0, 0, 8, 1, 0},  /* DBG_DETECT_CPT */
    {0, 88, 0, 0, 8, 1, 0},  /* DBG_SYMB_CPT */
    {0, 89, 0, 0, 1, 0, 1},  /* CHIRP_INVERT_RX */
    {0, 89, 1, 0, 1, 0, 1},  /* DC_NOTCH_EN */
    {0, 90, 0, 0, 1, 0, 0},  /* IMPLICIT_CRC_EN */
    {0, 90, 1, 0, 3, 0, 0},  /* IMPLICIT_CODING_RATE */
    {0, 91, 0, 0, 8, 0, 0},  /* IMPLICIT_PAYLOAD_LENGHT */
    {0, 92, 0, 0, 8, 0, 29}, /* FREQ_TO_TIME_INVERT */
    {0, 93, 0, 0, 6, 0, 9},  /* FREQ_TO_TIME_DRIFT */
    {0, 94, 0, 0, 2, 0, 2},  /* PAYLOAD_FINE_TIMING_GAIN */
    {0, 94, 2, 0, 2, 0, 1},  /* PREAMBLE_FINE_TIMING_GAIN */
    {0, 94, 4, 0, 2, 0, 0},  /* TRACKING_INTEGRAL */
    {0, 95, 0, 0, 4, 0, 1},  /* FRAME_SYNCH_PEAK1_POS */
    {0, 95, 4, 0, 4, 0, 2},  /* FRAME_SYNCH_PEAK2_POS */
    {0, 96, 0, 0, 16, 0, 10}, /* PREAMBLE_SYMB1_NB */
    {0, 98, 0, 0, 1, 0, 1},  /* FRAME_SYNCH_GAIN */
    {0, 98, 1, 0, 1, 0, 1},  /* SYNCH_DETECT_TH */
    {0, 99, 0, 0, 4, 0, 8},  /* LLR_SCALE */
    {0, 99, 4, 0, 2, 0, 2},  /* SNR_AVG_CST */
    {0, 100, 0, 0, 7, 0, 0}, /* PPM_OFFSET */
    {0, 101, 0, 0, 8, 0, 255}, /* MAX_PAYLOAD_LEN */
    {0, 102, 0, 0, 1, 0, 1},  /* ONLY_CRC_EN */
    {0, 103, 0, 0, 8, 0, 0},  /* ZERO_PAD */
    {0, 104, 0, 0, 4, 0, 8},  /* DEC_GAIN_OFFSET */
    {0, 104, 4, 0, 4, 0, 7},  /* CHAN_GAIN_OFFSET */
    {0, 105, 1, 0, 1, 0, 1},  /* FORCE_HOST_RADIO_CTRL */
    {0, 105, 2, 0, 1, 0, 1},  /* FORCE_HOST_FE_CTRL */
    {0, 105, 3, 0, 1, 0, 1},  /* FORCE_DEC_FILTER_GAIN */
    {0, 106, 0, 0, 1, 0, 1},  /* MCU_RST_0 */
    {0, 106, 1, 0, 1, 0, 1},  /* MCU_RST_1 */
    {0, 106, 2, 0, 1, 0, 0},  /* MCU_SELECT_MUX_0 */
    {0, 106, 3, 0, 1, 0, 0},  /* MCU_SELECT_MUX_1 */
    {0, 106, 4, 0, 1, 1, 0},  /* MCU_CORRUPTION_DETECTED_0 */
    {0, 106, 5, 0, 1, 1, 0},  /* MCU_CORRUPTION_DETECTED_1 */
    {0, 106, 6, 0, 1, 0, 0},  /* MCU_SELECT_EDGE_0 */
    {0, 106, 7, 0, 1, 0, 0},  /* MCU_SELECT_EDGE_1 */
    {0, 107, 0, 0, 8, 0, 1},  /* CHANN_SELECT_RSSI */
    {0, 108, 0, 0, 8, 0, 32}, /* RSSI_BB_DEFAULT_VALUE */
    {0, 109, 0, 0, 8, 0, 100}, /* RSSI_DEC_DEFAULT_VALUE */
    {0, 110, 0, 0, 8, 0, 100}, /* RSSI_CHANN_DEFAULT_VALUE */
    {0, 111, 0, 0, 5, 0, 7},  /* RSSI_BB_FILTER_ALPHA */
    {0, 112, 0, 0, 5, 0, 5},  /* RSSI_DEC_FILTER_ALPHA */
    {0, 113, 0, 0, 5, 0, 8},  /* RSSI_CHANN_FILTER_ALPHA */
    {0, 114, 0, 0, 6, 0, 0},  /* IQ_MISMATCH_A_AMP_COEFF */
    {0, 115, 0, 0, 6, 0, 0},  /* IQ_MISMATCH_A_PHI_COEFF */
    {0, 116, 0, 0, 6, 0, 0},  /* IQ_MISMATCH_B_AMP_COEFF */
    {0, 116, 6, 0, 1, 0, 0},  /* IQ_MISMATCH_B_SEL_I */
    {0, 117, 0, 0, 6, 0, 0},  /* IQ_MISMATCH_B_PHI_COEFF */
    {1, 33, 0, 0, 1, 0, 0},   /* TX_TRIG_IMMEDIATE */
    {1, 33, 1, 0, 1, 0, 0},   /* TX_TRIG_DELAYED */
    {1, 33, 2, 0, 1, 0, 0},   /* TX_TRIG_GPS */
    {1, 34, 0, 0, 16, 0, 0},  /* TX_START_DELAY */
    {1, 36, 0, 0, 4, 0, 1},  /* TX_FRAME_SYNCH_PEAK1_POS */
    {1, 36, 4, 0, 4, 0, 2},  /* TX_FRAME_SYNCH_PEAK2_POS */
    {1, 37, 0, 0, 3, 0, 0},  /* TX_RAMP_DURATION */
    {1, 39, 0, 1, 8, 0, 0},  /* TX_OFFSET_I */
    {1, 40, 0, 1, 8, 0, 0},  /* TX_OFFSET_Q */
    {1, 41, 0, 0, 1, 0, 0},  /* TX_MODE */
    {1, 41, 1, 0, 4, 0, 0},  /* TX_ZERO_PAD */
    {1, 41, 5, 0, 1, 0, 0},  /* TX_EDGE_SELECT */
    {1, 41, 6, 0, 1, 0, 0},  /* TX_EDGE_SELECT_TOP */
    {1, 42, 0, 0, 2, 0, 0},  /* TX_GAIN */
    {1, 42, 2, 0, 3, 0, 5},  /* TX_CHIRP_LOW_PASS */
    {1, 42, 5, 0, 2, 0, 0},  /* TX_FCC_WIDEBAND */
    {1, 42, 7, 0, 1, 0, 1},  /* TX_SWAP_IQ */
    {1, 43, 0, 0, 1, 0, 0},  /* MBWSSF_IMPLICIT_HEADER */
    {1, 43, 1, 0, 1, 0, 0},  /* MBWSSF_IMPLICIT_CRC_EN */
    {1, 43, 2, 0, 3, 0, 0},  /* MBWSSF_IMPLICIT_CODING_RATE */
    {1, 44, 0, 0, 8, 0, 0},  /* MBWSSF_IMPLICIT_PAYLOAD_LENGHT */
    {1, 45, 0, 0, 1, 0, 1},  /* MBWSSF_AGC_FREEZE_ON_DETECT */
    {1, 46, 0, 0, 4, 0, 1},  /* MBWSSF_FRAME_SYNCH_PEAK1_POS */
    {1, 46, 4, 0, 4, 0, 2},  /* MBWSSF_FRAME_SYNCH_PEAK2_POS */
    {1, 47, 0, 0, 16, 0, 10}, /* MBWSSF_PREAMBLE_SYMB1_NB */
    {1, 49, 0, 0, 1, 0, 1},  /* MBWSSF_FRAME_SYNCH_GAIN */
    {1, 49, 1, 0, 1, 0, 1},  /* MBWSSF_SYNCH_DETECT_TH */
    {1, 50, 0, 0, 8, 0, 10}, /* MBWSSF_DETECT_MIN_SINGLE_PEAK */
    {1, 51, 0, 0, 3, 0, 3},  /* MBWSSF_DETECT_TRIG_SAME_PEAK_NB */
    {1, 52, 0, 0, 8, 0, 29}, /* MBWSSF_FREQ_TO_TIME_INVERT */
    {1, 53, 0, 0, 6, 0, 36}, /* MBWSSF_FREQ_TO_TIME_DRIFT */
    {1, 54, 0, 0, 12, 0, 0}, /* MBWSSF_PPM_CORRECTION */
    {1, 56, 0, 0, 2, 0, 2},  /* MBWSSF_PAYLOAD_FINE_TIMING_GAIN */
    {1, 56, 2, 0, 2, 0, 1},  /* MBWSSF_PREAMBLE_FINE_TIMING_GAIN */
    {1, 56, 4, 0, 2, 0, 0},  /* MBWSSF_TRACKING_INTEGRAL */
    {1, 57, 0, 0, 8, 0, 0},  /* MBWSSF_ZERO_PAD */
    {1, 58, 0, 0, 2, 0, 0},  /* MBWSSF_MODEM_BW */
    {1, 58, 2, 0, 1, 0, 0},  /* MBWSSF_RADIO_SELECT */
    {1, 58, 3, 0, 1, 0, 1},  /* MBWSSF_RX_CHIRP_INVERT */
    {1, 59, 0, 0, 4, 0, 8},  /* MBWSSF_LLR_SCALE */
    {1, 59, 4, 0, 2, 0, 3},  /* MBWSSF_SNR_AVG_CST */
    {1, 59, 6, 0, 1, 0, 0},  /* MBWSSF_PPM_OFFSET */
    {1, 60, 0, 0, 4, 0, 7},  /* MBWSSF_RATE_SF */
    {1, 60, 4, 0, 1, 0, 1},  /* MBWSSF_ONLY_CRC_EN */
    {1, 61, 0, 0, 8, 0, 255}, /* MBWSSF_MAX_PAYLOAD_LEN */
    {1, 62, 0, 0, 8, 1, 128}, /* TX_STATUS */
    {1, 63, 0, 0, 3, 0, 0},  /* FSK_CH_BW_EXPO */
    {1, 63, 3, 0, 3, 0, 0},  /* FSK_RSSI_LENGTH */
    {1, 63, 6, 0, 1, 0, 0},  /* FSK_RX_INVERT */
    {1, 63, 7, 0, 1, 0, 0},  /* FSK_PKT_MODE */
    {1, 64, 0, 0, 3, 0, 0},  /* FSK_PSIZE */
    {1, 64, 3, 0, 1, 0, 0},  /* FSK_CRC_EN */
    {1, 64, 4, 0, 2, 0, 0},  /* FSK_DCFREE_ENC */
    {1, 64, 6, 0, 1, 0, 0},  /* FSK_CRC_IBM */
    {1, 65, 0, 0, 5, 0, 0},  /* FSK_ERROR_OSR_TOL */
    {1, 65, 7, 0, 1, 0, 0},  /* FSK_RADIO_SELECT */
    {1, 66, 0, 0, 16, 0, 0}, /* FSK_BR_RATIO */
    {1, 68, 0, 0, 32, 0, 0}, /* FSK_REF_PATTERN_LSB */
    {1, 72, 0, 0, 32, 0, 0}, /* FSK_REF_PATTERN_MSB */
    {1, 76, 0, 0, 8, 0, 0},  /* FSK_PKT_LENGTH */
    {1, 77, 0, 0, 1, 0, 1},  /* FSK_TX_GAUSSIAN_EN */
    {1, 77, 1, 0, 2, 0, 0},  /* FSK_TX_GAUSSIAN_SELECT_BT */
    {1, 77, 3, 0, 1, 0, 1},  /* FSK_TX_PATTERN_EN */
    {1, 77, 4, 0, 1, 0, 0},  /* FSK_TX_PREAMBLE_SEQ */
    {1, 77, 5, 0, 3, 0, 0},  /* FSK_TX_PSIZE */
    {1, 80, 0, 0, 8, 0, 0},  /* FSK_NODE_ADRS */
    {1, 81, 0, 0, 8, 0, 0},  /* FSK_BROADCAST */
    {1, 82, 0, 0, 1, 0, 1},  /* FSK_AUTO_AFC_ON */
    {1, 83, 0, 0, 10, 0, 0}, /* FSK_PATTERN_TIMEOUT_CFG */
    {2, 33, 0, 0, 8, 0, 0},  /* SPI_RADIO_A__DATA */
    {2, 34, 0, 0, 8, 1, 0},  /* SPI_RADIO_A__DATA_READBACK */
    {2, 35, 0, 0, 8, 0, 0},  /* SPI_RADIO_A__ADDR */
    {2, 37, 0, 0, 1, 0, 0},  /* SPI_RADIO_A__CS */
    {2, 38, 0, 0, 8, 0, 0},  /* SPI_RADIO_B__DATA */
    {2, 39, 0, 0, 8, 1, 0},  /* SPI_RADIO_B__DATA_READBACK */
    {2, 40, 0, 0, 8, 0, 0},  /* SPI_RADIO_B__ADDR */
    {2, 42, 0, 0, 1, 0, 0},  /* SPI_RADIO_B__CS */
    {2, 43, 0, 0, 1, 0, 0},  /* RADIO_A_EN */
    {2, 43, 1, 0, 1, 0, 0},  /* RADIO_B_EN */
    {2, 43, 2, 0, 1, 0, 1},  /* RADIO_RST */
    {2, 43, 3, 0, 1, 0, 0},  /* LNA_A_EN */
    {2, 43, 4, 0, 1, 0, 0},  /* PA_A_EN */
    {2, 43, 5, 0, 1, 0, 0},  /* LNA_B_EN */
    {2, 43, 6, 0, 1, 0, 0},  /* PA_B_EN */
    {2, 44, 0, 0, 2, 0, 0},  /* PA_GAIN */
    {2, 45, 0, 0, 4, 0, 2},  /* LNA_A_CTRL_LUT */
    {2, 45, 4, 0, 4, 0, 4},  /* PA_A_CTRL_LUT */
    {2, 46, 0, 0, 4, 0, 2},  /* LNA_B_CTRL_LUT */
    {2, 46, 4, 0, 4, 0, 4},  /* PA_B_CTRL_LUT */
    {2, 47, 0, 0, 5, 0, 0},  /* CAPTURE_SOURCE */
    {2, 47, 5, 0, 1, 0, 0},  /* CAPTURE_START */
    {2, 47, 6, 0, 1, 0, 0},  /* CAPTURE_FORCE_TRIGGER */
    {2, 47, 7, 0, 1, 0, 0},  /* CAPTURE_WRAP */
    {2, 48, 0, 0, 16, 0, 0}, /* CAPTURE_PERIOD */
    {2, 51, 0, 0, 8, 1, 0},  /* MODEM_STATUS */
    {2, 52, 0, 0, 8, 1, 0},  /* VALID_HEADER_COUNTER_0 */
    {2, 54, 0, 0, 8, 1, 0},  /* VALID_PACKET_COUNTER_0 */
    {2, 56, 0, 0, 8, 1, 0},  /* VALID_HEADER_COUNTER_MBWSSF */
    {2, 57, 0, 0, 8, 1, 0},  /* VALID_HEADER_COUNTER_FSK */
    {2, 58, 0, 0, 8, 1, 0},  /* VALID_PACKET_COUNTER_MBWSSF */
    {2, 59, 0, 0, 8, 1, 0},  /* VALID_PACKET_COUNTER_FSK */
    {2, 60, 0, 0, 8, 1, 0},  /* CHANN_RSSI */
    {2, 61, 0, 0, 8, 1, 0},  /* BB_RSSI */
    {2, 62, 0, 0, 8, 1, 0},  /* DEC_RSSI */
    {2, 63, 0, 0, 8, 1, 0},  /* DBG_MCU_DATA */
    {2, 64, 0, 0, 8, 1, 0},  /* DBG_ARB_MCU_RAM_DATA */
    {2, 65, 0, 0, 8, 1, 0},  /* DBG_AGC_MCU_RAM_DATA */
    {2, 66, 0, 0, 16, 1, 0}, /* NEXT_PACKET_CNT */
    {2, 68, 0, 0, 16, 1, 0}, /* ADDR_CAPTURE_COUNT */
    {2, 70, 0, 0, 32, 1, 0}, /* TIMESTAMP */
    {2, 74, 0, 0, 4, 1, 0},  /* DBG_CHANN0_GAIN */
    {2, 74, 4, 0, 4, 1, 0},  /* DBG_CHANN1_GAIN */
    {2, 75, 0, 0, 4, 1, 0},  /* DBG_CHANN2_GAIN */
    {2, 75, 4, 0, 4, 1, 0},  /* DBG_CHANN3_GAIN */
    {2, 76, 0, 0, 4, 1, 0},  /* DBG_CHANN4_GAIN */
    {2, 76, 4, 0, 4, 1, 0},  /* DBG_CHANN5_GAIN */
    {2, 77, 0, 0, 4, 1, 0},  /* DBG_CHANN6_GAIN */
    {2, 77, 4, 0, 4, 1, 0},  /* DBG_CHANN7_GAIN */
    {2, 78, 0, 0, 4, 1, 0},  /* DBG_DEC_FILT_GAIN */
    {2, 79, 0, 0, 3, 1, 0},  /* SPI_DATA_FIFO_PTR */
    {2, 79, 3, 0, 3, 1, 0},  /* PACKET_DATA_FIFO_PTR */
    {2, 80, 0, 0, 8, 0, 0},  /* DBG_ARB_MCU_RAM_ADDR */
    {2, 81, 0, 0, 8, 0, 0},  /* DBG_AGC_MCU_RAM_ADDR */
    {2, 82, 0, 0, 1, 0, 0},  /* SPI_MASTER_CHIP_SELECT_POLARITY */
    {2, 82, 1, 0, 1, 0, 0},  /* SPI_MASTER_CPOL */
    {2, 82, 2, 0, 1, 0, 0},  /* SPI_MASTER_CPHA */
    {2, 83, 0, 0, 1, 0, 0},  /* SIG_GEN_ANALYSER_MUX_SEL */
    {2, 84, 0, 0, 1, 0, 0},  /* SIG_GEN_EN */
    {2, 84, 1, 0, 1, 0, 0},  /* SIG_ANALYSER_EN */
    {2, 84, 2, 0, 2, 0, 0},  /* SIG_ANALYSER_AVG_LEN */
    {2, 84, 4, 0, 3, 0, 0},  /* SIG_ANALYSER_PRECISION */
    {2, 84, 7, 0, 1, 1, 0},  /* SIG_ANALYSER_VALID_OUT */
    {2, 85, 0, 0, 8, 0, 0},  /* SIG_GEN_FREQ */
    {2, 86, 0, 0, 8, 0, 0},  /* SIG_ANALYSER_FREQ */
    {2, 87, 0, 0, 8, 1, 0},  /* SIG_ANALYSER_I_OUT */
    {2, 88, 0, 0, 8, 1, 0},  /* SIG_ANALYSER_Q_OUT */
    {2, 89, 0, 0, 1, 0, 0},  /* GPS_EN */
    {2, 89, 1, 0, 1, 0, 1},  /* GPS_POL */
    {2, 90, 0, 1, 8, 0, 0},  /* SW_TEST_REG1 */
    {2, 91, 2, 1, 6, 0, 0},  /* SW_TEST_REG2 */
    {2, 92, 0, 1, 16, 0, 0}, /* SW_TEST_REG3 */
    {2, 94, 0, 0, 4, 1, 0},  /* DATA_MNGT_STATUS */
    {2, 95, 0, 0, 5, 1, 0},  /* DATA_MNGT_CPT_FRAME_ALLOCATED */
    {2, 96, 0, 0, 5, 1, 0},  /* DATA_MNGT_CPT_FRAME_FINISHED */
    {2, 97, 0, 0, 5, 1, 0},  /* DATA_MNGT_CPT_FRAME_READEN */
    {1, 33, 0, 0, 8, 0, 0}   /* TX_TRIG_ALL (alias) */
};
#define PAGE_ADDR        0x00
#define PAGE_MASK        0x03

static int lgw_regpage = -1; /*! keep the value of the register page selected */

int page_switch(uint8_t target) {
    lgw_regpage = PAGE_MASK & target;
    Sx1308.lgw_currentpage =  lgw_regpage;
    Sx1308.spiWrite( PAGE_ADDR, (uint8_t)lgw_regpage);
    return LGW_REG_SUCCESS;
}

/* soft-reset function */
int lgw_soft_reset(void) {

    Sx1308.spiWrite( 0, 0x80); /* 1 -> SOFT_RESET bit */
    lgw_regpage = 0; /* reset the paging static variable */
    return LGW_REG_SUCCESS;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */


int reg_w_align32(void *spi_target, uint8_t spi_mux_mode, uint8_t spi_mux_target, struct lgw_reg_s r, int32_t reg_value) {
    int i, size_byte;
    uint8_t buf[4] = {0, 0, 0, 0};

    if ((r.leng == 8) && (r.offs == 0)) {
        /* direct write */
        Sx1308.spiWrite(r.addr, (uint8_t)reg_value);
    } else if ((r.offs + r.leng) <= 8) {
        /* single-byte read-modify-write, offs:[0-7], leng:[1-7] */
        buf[0] = Sx1308.spiRead(r.addr);
        buf[1] = ((1 << r.leng) - 1) << r.offs; /* bit mask */
        buf[2] = ((uint8_t)reg_value) << r.offs; /* new data offsetted */
        buf[3] = (~buf[1] & buf[0]) | (buf[1] & buf[2]); /* mixing old & new data */
        Sx1308.spiWrite(r.addr, (uint8_t)buf[3]);
    } else if ((r.offs == 0) && (r.leng > 0) && (r.leng <= 32)) {
        /* multi-byte direct write routine */
        size_byte = (r.leng + 7) / 8; /* add a byte if it's not an exact multiple of 8 */
        for (i = 0; i < size_byte; ++i) {
            /* big endian register file for a file on N bytes
            Least significant byte is stored in buf[0], most one in buf[N-1] */
            buf[i] = (uint8_t)(0x000000FF & reg_value);
            reg_value = (reg_value >> 8);
        }
        Sx1308.spiWriteBurstuint8( r.addr, buf, size_byte);
    } else {
        /* register spanning multiple memory bytes but with an offset */

        return LGW_REG_ERROR;
    }

    return LGW_REG_SUCCESS;
}



int reg_r_align32(void *spi_target, uint8_t spi_mux_mode, uint8_t spi_mux_target, struct lgw_reg_s r, int32_t *reg_value) {
    uint8_t bufu[4] = {0, 0, 0, 0};
    int8_t *bufs = (int8_t *)bufu;
    int i, size_byte;
    uint32_t u = 0;

    if ((r.offs + r.leng) <= 8) {
        /* read one byte, then shift and mask bits to get reg value with sign extension if needed */
        bufu[0] = Sx1308.spiRead(r.addr);
        bufu[1] = bufu[0] << (8 - r.leng - r.offs); /* left-align the data */
        if (r.sign == true) {
            bufs[2] = bufs[1] >> (8 - r.leng); /* right align the data with sign extension (ARITHMETIC right shift) */
            *reg_value = (int32_t)bufs[2]; /* signed pointer -> 32b sign extension */
        } else {
            bufu[2] = bufu[1] >> (8 - r.leng); /* right align the data, no sign extension */
            *reg_value = (int32_t)bufu[2]; /* unsigned pointer -> no sign extension */
        }
    } else if ((r.offs == 0) && (r.leng > 0) && (r.leng <= 32)) {
        size_byte = (r.leng + 7) / 8; /* add a byte if it's not an exact multiple of 8 */
        Sx1308.spiReadBurst(r.addr, bufu, size_byte);
        u = 0;
        for (i = (size_byte - 1); i >= 0; --i) {
            u = (uint32_t)bufu[i] + (u << 8); /* transform a 4-byte array into a 32 bit word */
        }
        if (r.sign == true) {
            u = u << (32 - r.leng); /* left-align the data */
            *reg_value = (int32_t)u >> (32 - r.leng); /* right-align the data with sign extension (ARITHMETIC right shift) */
        } else {
            *reg_value = (int32_t)u; /* unsigned value -> return 'as is' */
        }
    } else {
        /* register spanning multiple memory bytes but with an offset */
        return LGW_REG_ERROR;
    }

    return LGW_REG_SUCCESS;
}

int lgw_reg_w(uint16_t register_id, int32_t reg_value)
{
    struct lgw_reg_s r;

    /* check input parameters */
    if (register_id >= LGW_TOTALREGS) {
        return LGW_REG_ERROR;
    }

    /* intercept direct access to PAGE_REG & SOFT_RESET */
    if (register_id == LGW_PAGE_REG) {
        page_switch(reg_value);
        return LGW_REG_SUCCESS;
    } else if (register_id == LGW_SOFT_RESET) {
        /* only reset if lsb is 1 */
        if ((reg_value & 0x01) != 0)
        {
            return LGW_REG_SUCCESS;
        }
    }

    /* get register struct from the struct array */
    r = loregs[register_id];

    /* reject write to read-only registers */
    if (r.rdon == 1) {

        return LGW_REG_ERROR;
    }

    /* select proper register page if needed */
    if ((r.page != -1)) {
        page_switch(r.page);
    }

    reg_w_align32(0, 0, 0, r, reg_value);

    return LGW_REG_SUCCESS;
}



/**
@brief LoRa concentrator register read
@param register_id register number in the data structure describing registers
@param reg_value pointer to a variable where to write register read value
@return status of register operation (LGW_REG_SUCCESS/LGW_REG_ERROR)
*/
int lgw_reg_r(uint16_t register_id, int32_t *reg_value)
{
    struct lgw_reg_s r;

    /* get register struct from the struct array */
    r = loregs[register_id];

    /* select proper register page if needed */
    if ((r.page != -1)) { // && (r.page != lgw_regpage)) {
        page_switch(r.page);
    }

    reg_r_align32(0, 0, 0, r, reg_value);

    return LGW_REG_SUCCESS;

}

/**
@brief LoRa concentrator register burst write
@param register_id register number in the data structure describing registers
@param data pointer to byte array that will be sent to the LoRa concentrator
@param size size of the transfer, in byte(s)
@return status of register operation (LGW_REG_SUCCESS/LGW_REG_ERROR)
*/
int lgw_reg_wb(uint16_t register_id, uint8_t *data, uint16_t size)
{
    struct lgw_reg_s r;

    /* check input parameters */
    if (size == 0) {

        return LGW_REG_ERROR;
    }
    if (register_id >= LGW_TOTALREGS) {

        return LGW_REG_ERROR;
    }

    /* get register struct from the struct array */
    r = loregs[register_id];

    /* reject write to read-only registers */
    if (r.rdon == 1) {

        return LGW_REG_ERROR;
    }

    /* select proper register page if needed */
    if ((r.page != -1)) {
        page_switch(r.page);
    }

    /* do the burst write */
    Sx1308.spiWriteBurstuint8( r.addr, data, size);

    return LGW_REG_SUCCESS;

}

/**
@brief LoRa concentrator register burst read
@param register_id register number in the data structure describing registers
@param data pointer to byte array that will be written from the LoRa concentrator
@param size size of the transfer, in byte(s)
@return status of register operation (LGW_REG_SUCCESS/LGW_REG_ERROR)
*/
int lgw_reg_rb(uint16_t register_id, uint8_t *data, uint16_t size)
{
    struct lgw_reg_s r;

    /* check input parameters */
    if (size == 0) {

        return LGW_REG_ERROR;
    }
    if (register_id >= LGW_TOTALREGS) {

        return LGW_REG_ERROR;
    }

    /* get register struct from the struct array */
    r = loregs[register_id];

    /* select proper register page if needed */
    if ((r.page != -1)) {
        page_switch(r.page);
    }

    /* do the burst read */
    Sx1308.spiReadBurst(r.addr, data, size);

    return LGW_REG_SUCCESS;
}
