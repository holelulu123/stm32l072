#ifndef __SX_1276_H
#define __SX_1276_H
#include <stdio.h>

// Registers Map
#define RegFifo                        ((__uint8_t)0x00) 
#define RegOpMode                      ((__uint8_t)0x01)
#define RegFrfMsb                      ((__uint8_t)0x06)
#define RegFrfMid                      ((__uint8_t)0x07)
#define RegFrfLsb                      ((__uint8_t)0x08)
#define RegPaConfig                    ((__uint8_t)0x09)
#define RegPaRamp                      ((__uint8_t)0x0A)
#define RegOcp                         ((__uint8_t)0x0B)
#define RegLna                         ((__uint8_t)0x0C)
#define RegFifoAddrPtr                 ((__uint8_t)0x0D)
#define RegFifoTxBaseAddr              ((__uint8_t)0x0E)
#define RegFifoRxBaseAddr              ((__uint8_t)0x0F)
#define FifoRxCurrentAddr              ((__uint8_t)0x10)
#define RegIrqFlagsMask                ((__uint8_t)0x11)
#define RegIrqFlags                    ((__uint8_t)0x12)
#define RegRxNbBytes                   ((__uint8_t)0x13)
#define RegRxHeaderCntValueMsb         ((__uint8_t)0x14)
#define RegRxHeaderCntValueLsb         ((__uint8_t)0x15)
#define RegRxPacketCntValueMsb         ((__uint8_t)0x16)
#define RegRxPacketCntValueLsb         ((__uint8_t)0x17)
#define RegModemStat                   ((__uint8_t)0x18)
#define RegPktSnrValue                 ((__uint8_t)0x19)
#define RegPktRssiValue                ((__uint8_t)0x1A)
#define RegRssiValue                   ((__uint8_t)0x1B)
#define RegHopChannel                  ((__uint8_t)0x1C)
#define RegModemConfig1                ((__uint8_t)0x1D)
#define RegModemConfig2                ((__uint8_t)0x1E)
#define RegSymbTimeoutLsb              ((__uint8_t)0x1F)
#define RegPreambleMsb                 ((__uint8_t)0x20)
#define RegPreambleLsb                 ((__uint8_t)0x21)
#define RegPayloadLength               ((__uint8_t)0x22)
#define RegMaxPayloadLength            ((__uint8_t)0x23)
#define RegHopPeriod                   ((__uint8_t)0x24)
#define RegFifoRxByteAddr              ((__uint8_t)0x25)
#define RegModemConfig3                ((__uint8_t)0x26)
#define RegFeiMsb                      ((__uint8_t)0x28)
#define RegFeiMid                      ((__uint8_t)0x29)
#define RegFeiLsb                      ((__uint8_t)0x2A)
#define RegRssiWideband                ((__uint8_t)0x2C)
#define RegIfFreq1                     ((__uint8_t)0x2F)
#define RegIfFreq2                     ((__uint8_t)0x30)
#define RegDetectOptimize              ((__uint8_t)0x31)
#define RegInvertIQ                    ((__uint8_t)0x33)
#define RegHighBwOptimize1             ((__uint8_t)0x36)
#define RegDetectionThreshold          ((__uint8_t)0x37)
#define RegSyncWord                    ((__uint8_t)0x39)
#define RegHighBwOptimize2             ((__uint8_t)0x3A)
#define RegInvertIQ2                   ((__uint8_t)0x3B)
#define RegDioMapping1                 ((__uint8_t)0x40)
#define RegDioMapping2                 ((__uint8_t)0x41)
#define RegVersion                     ((__uint8_t)0x42)
#define RegTcxo                        ((__uint8_t)0x4B)
#define RegPaDac                       ((__uint8_t)0x4D)
#define RegFormerTemp                  ((__uint8_t)0x5B)
#define RegAgcRef                      ((__uint8_t)0x61)
#define RegAgcThresh1                  ((__uint8_t)0x62)
#define RegAgcThresh2                  ((__uint8_t)0x63)
#define RegAgcThresh3                  ((__uint8_t)0x64)
#define RegPll                         ((__uint8_t)0x70)

/*
Common Settings for the SX1276
*/
#define LORA_Mode                      ((__uint8_t)0x1 << 7)
#define Modulation_Scheme_OOK          ((__uint8_t)0x1 << 5)
#define Low_Frequnecy_Mode_On          ((__uint8_t)0x1 << 3)
#define Transceiver_Mode_Msk           ((__uint8_t)0x7 << 0)
#define Transceiver_Mode_Stdby         ((__uint8_t)0x1 << 0)
#define Transceiver_Mode_FS_TX         ((__uint8_t)0x1 << 1)
#define Transceiver_Mode_Transmitter   ((__uint8_t)0x3 << 0)
#define Transceiver_Mode_FS_RX         ((__uint8_t)0x1 << 2)
#define Transceiver_Mode_Receiver      ((__uint8_t)0x5 << 0)

/*
RF blocks settings for the SX1276
*/
#define PA_Boost_ON                    ((__uint8_t)0x1 << 0)
#define Overload_current_protection_on ((__uint8_t)0x1 << 5)

#define LNA_Gain_G1                    ((__uint8_t)0x1 << 5)
#define LNA_Gain_G2                    ((__uint8_t)0x2 << 5)
#define LNA_Gain_G3                    ((__uint8_t)0x3 << 5)
#define LNA_Gain_G4                    ((__uint8_t)0x4 << 5)
#define LNA_Gain_G5                    ((__uint8_t)0x5 << 5)
#define LNA_Gain_G6                    ((__uint8_t)0x6 << 5)
#define RFI_HF_LNA_Current_adj         ((__uint8_t)0x3 << 0)
// #define RFI_HF_LNA_Current_adj         ((__uint8_t)0x3 << 3) CHECK ON THIS !!!!!!!
#define ImplicitHeaderModeOn           ((__uint8_t)0x1 << 0)

typedef enum {
    LORA_BW_007                      = ((__uint8_t)0x0 << 4),   
    LORA_BW_010                      = ((__uint8_t)0x1 << 4),
    LORA_BW_015                      = ((__uint8_t)0x2 << 4),
    LORA_BW_020                      = ((__uint8_t)0x3 << 4),
    LORA_BW_031                      = ((__uint8_t)0x4 << 4),
    LORA_BW_041                      = ((__uint8_t)0x5 << 4),
    LORA_BW_062                      = ((__uint8_t)0x6 << 4),
    LORA_BW_125                      = ((__uint8_t)0x7 << 4),
    LORA_BW_250                      = ((__uint8_t)0x8 << 4),
    LORA_BW_500                      = ((__uint8_t)0x9 << 4),
}LoraBandWidth;
 
typedef enum {
    LORA_CR_4_5                      = ((__uint8_t)0x1 << 1),
    LORA_CR_4_6                      = ((__uint8_t)0x2 << 1),
    LORA_CR_4_7                      = ((__uint8_t)0x3 << 1),
    LORA_CR_4_8                      = ((__uint8_t)0x4 << 1),
}LoraCodingRates;

typedef enum{
    LORA_SF6                         = ((__uint8_t)0x06 << 4),
    LORA_SF7                         = ((__uint8_t)0x07 << 4),
    LORA_SF8                         = ((__uint8_t)0x08 << 4),
    LORA_SF9                         = ((__uint8_t)0x09 << 4),
    LORA_SF10                        = ((__uint8_t)0x0A << 4),
    LORA_SF11                        = ((__uint8_t)0x0B << 4),
    LORA_SF12                        = ((__uint8_t)0x0C << 4),

}LoRaSpreadingFactors;

#define TxContinuesMode                ((__uint8_t)0x1 << 3)
#define RxPayloadCrcOn                 ((__uint8_t)0x1 << 2)

#endif