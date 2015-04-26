/*******************************************************************************
* File Name: Tx.h
* Version 2.40
*
* Description:
*  Contains the function prototypes and constants available to the UART
*  user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_UART_Tx_H)
#define CY_UART_Tx_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"


/***************************************
* Conditional Compilation Parameters
***************************************/

#define Tx_RX_ENABLED                     (0u)
#define Tx_TX_ENABLED                     (1u)
#define Tx_HD_ENABLED                     (0u)
#define Tx_RX_INTERRUPT_ENABLED           (0u)
#define Tx_TX_INTERRUPT_ENABLED           (0u)
#define Tx_INTERNAL_CLOCK_USED            (1u)
#define Tx_RXHW_ADDRESS_ENABLED           (0u)
#define Tx_OVER_SAMPLE_COUNT              (8u)
#define Tx_PARITY_TYPE                    (0u)
#define Tx_PARITY_TYPE_SW                 (0u)
#define Tx_BREAK_DETECT                   (0u)
#define Tx_BREAK_BITS_TX                  (13u)
#define Tx_BREAK_BITS_RX                  (13u)
#define Tx_TXCLKGEN_DP                    (1u)
#define Tx_USE23POLLING                   (1u)
#define Tx_FLOW_CONTROL                   (0u)
#define Tx_CLK_FREQ                       (0u)
#define Tx_TX_BUFFER_SIZE                 (4u)
#define Tx_RX_BUFFER_SIZE                 (4u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component UART_v2_40 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#if defined(Tx_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG)
    #define Tx_CONTROL_REG_REMOVED            (0u)
#else
    #define Tx_CONTROL_REG_REMOVED            (1u)
#endif /* End Tx_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Structure Definition
***************************************/

/* Sleep Mode API Support */
typedef struct Tx_backupStruct_
{
    uint8 enableState;

    #if(Tx_CONTROL_REG_REMOVED == 0u)
        uint8 cr;
    #endif /* End Tx_CONTROL_REG_REMOVED */

} Tx_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void Tx_Start(void) ;
void Tx_Stop(void) ;
uint8 Tx_ReadControlRegister(void) ;
void Tx_WriteControlRegister(uint8 control) ;

void Tx_Init(void) ;
void Tx_Enable(void) ;
void Tx_SaveConfig(void) ;
void Tx_RestoreConfig(void) ;
void Tx_Sleep(void) ;
void Tx_Wakeup(void) ;

/* Only if RX is enabled */
#if( (Tx_RX_ENABLED) || (Tx_HD_ENABLED) )

    #if (Tx_RX_INTERRUPT_ENABLED)
        #define Tx_EnableRxInt()  CyIntEnable (Tx_RX_VECT_NUM)
        #define Tx_DisableRxInt() CyIntDisable(Tx_RX_VECT_NUM)
        CY_ISR_PROTO(Tx_RXISR);
    #endif /* Tx_RX_INTERRUPT_ENABLED */

    void Tx_SetRxAddressMode(uint8 addressMode)
                                                           ;
    void Tx_SetRxAddress1(uint8 address) ;
    void Tx_SetRxAddress2(uint8 address) ;

    void  Tx_SetRxInterruptMode(uint8 intSrc) ;
    uint8 Tx_ReadRxData(void) ;
    uint8 Tx_ReadRxStatus(void) ;
    uint8 Tx_GetChar(void) ;
    uint16 Tx_GetByte(void) ;
    uint8 Tx_GetRxBufferSize(void)
                                                            ;
    void Tx_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define Tx_GetRxInterruptSource   Tx_ReadRxStatus

#endif /* End (Tx_RX_ENABLED) || (Tx_HD_ENABLED) */

/* Only if TX is enabled */
#if(Tx_TX_ENABLED || Tx_HD_ENABLED)

    #if(Tx_TX_INTERRUPT_ENABLED)
        #define Tx_EnableTxInt()  CyIntEnable (Tx_TX_VECT_NUM)
        #define Tx_DisableTxInt() CyIntDisable(Tx_TX_VECT_NUM)
        #define Tx_SetPendingTxInt() CyIntSetPending(Tx_TX_VECT_NUM)
        #define Tx_ClearPendingTxInt() CyIntClearPending(Tx_TX_VECT_NUM)
        CY_ISR_PROTO(Tx_TXISR);
    #endif /* Tx_TX_INTERRUPT_ENABLED */

    void Tx_SetTxInterruptMode(uint8 intSrc) ;
    void Tx_WriteTxData(uint8 txDataByte) ;
    uint8 Tx_ReadTxStatus(void) ;
    void Tx_PutChar(uint8 txDataByte) ;
    void Tx_PutString(const char8 string[]) ;
    void Tx_PutArray(const uint8 string[], uint8 byteCount)
                                                            ;
    void Tx_PutCRLF(uint8 txDataByte) ;
    void Tx_ClearTxBuffer(void) ;
    void Tx_SetTxAddressMode(uint8 addressMode) ;
    void Tx_SendBreak(uint8 retMode) ;
    uint8 Tx_GetTxBufferSize(void)
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define Tx_PutStringConst         Tx_PutString
    #define Tx_PutArrayConst          Tx_PutArray
    #define Tx_GetTxInterruptSource   Tx_ReadTxStatus

#endif /* End Tx_TX_ENABLED || Tx_HD_ENABLED */

#if(Tx_HD_ENABLED)
    void Tx_LoadRxConfig(void) ;
    void Tx_LoadTxConfig(void) ;
#endif /* End Tx_HD_ENABLED */


/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Tx) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    Tx_CyBtldrCommStart(void) CYSMALL ;
    void    Tx_CyBtldrCommStop(void) CYSMALL ;
    void    Tx_CyBtldrCommReset(void) CYSMALL ;
    cystatus Tx_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus Tx_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Tx)
        #define CyBtldrCommStart    Tx_CyBtldrCommStart
        #define CyBtldrCommStop     Tx_CyBtldrCommStop
        #define CyBtldrCommReset    Tx_CyBtldrCommReset
        #define CyBtldrCommWrite    Tx_CyBtldrCommWrite
        #define CyBtldrCommRead     Tx_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Tx) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define Tx_BYTE2BYTE_TIME_OUT (25u)
    #define Tx_PACKET_EOP         (0x17u) /* End of packet defined by bootloader */
    #define Tx_WAIT_EOP_DELAY     (5u)    /* Additional 5ms to wait for End of packet */
    #define Tx_WAIT_1_MS          (1u)    /* Time Out quantity equal 1mS */

#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define Tx_SET_SPACE      (0x00u)
#define Tx_SET_MARK       (0x01u)

/* Status Register definitions */
#if( (Tx_TX_ENABLED) || (Tx_HD_ENABLED) )
    #if(Tx_TX_INTERRUPT_ENABLED)
        #define Tx_TX_VECT_NUM            (uint8)Tx_TXInternalInterrupt__INTC_NUMBER
        #define Tx_TX_PRIOR_NUM           (uint8)Tx_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* Tx_TX_INTERRUPT_ENABLED */

    #define Tx_TX_STS_COMPLETE_SHIFT          (0x00u)
    #define Tx_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
    #define Tx_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #if(Tx_TX_ENABLED)
        #define Tx_TX_STS_FIFO_FULL_SHIFT     (0x02u)
    #else /* (Tx_HD_ENABLED) */
        #define Tx_TX_STS_FIFO_FULL_SHIFT     (0x05u)  /* Needs MD=0 */
    #endif /* (Tx_TX_ENABLED) */

    #define Tx_TX_STS_COMPLETE            (uint8)(0x01u << Tx_TX_STS_COMPLETE_SHIFT)
    #define Tx_TX_STS_FIFO_EMPTY          (uint8)(0x01u << Tx_TX_STS_FIFO_EMPTY_SHIFT)
    #define Tx_TX_STS_FIFO_FULL           (uint8)(0x01u << Tx_TX_STS_FIFO_FULL_SHIFT)
    #define Tx_TX_STS_FIFO_NOT_FULL       (uint8)(0x01u << Tx_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (Tx_TX_ENABLED) || (Tx_HD_ENABLED)*/

#if( (Tx_RX_ENABLED) || (Tx_HD_ENABLED) )
    #if(Tx_RX_INTERRUPT_ENABLED)
        #define Tx_RX_VECT_NUM            (uint8)Tx_RXInternalInterrupt__INTC_NUMBER
        #define Tx_RX_PRIOR_NUM           (uint8)Tx_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* Tx_RX_INTERRUPT_ENABLED */
    #define Tx_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define Tx_RX_STS_BREAK_SHIFT             (0x01u)
    #define Tx_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define Tx_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define Tx_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define Tx_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define Tx_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define Tx_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define Tx_RX_STS_MRKSPC           (uint8)(0x01u << Tx_RX_STS_MRKSPC_SHIFT)
    #define Tx_RX_STS_BREAK            (uint8)(0x01u << Tx_RX_STS_BREAK_SHIFT)
    #define Tx_RX_STS_PAR_ERROR        (uint8)(0x01u << Tx_RX_STS_PAR_ERROR_SHIFT)
    #define Tx_RX_STS_STOP_ERROR       (uint8)(0x01u << Tx_RX_STS_STOP_ERROR_SHIFT)
    #define Tx_RX_STS_OVERRUN          (uint8)(0x01u << Tx_RX_STS_OVERRUN_SHIFT)
    #define Tx_RX_STS_FIFO_NOTEMPTY    (uint8)(0x01u << Tx_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define Tx_RX_STS_ADDR_MATCH       (uint8)(0x01u << Tx_RX_STS_ADDR_MATCH_SHIFT)
    #define Tx_RX_STS_SOFT_BUFF_OVER   (uint8)(0x01u << Tx_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define Tx_RX_HW_MASK                     (0x7Fu)
#endif /* End (Tx_RX_ENABLED) || (Tx_HD_ENABLED) */

/* Control Register definitions */
#define Tx_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define Tx_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define Tx_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define Tx_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define Tx_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define Tx_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define Tx_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define Tx_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define Tx_CTRL_HD_SEND               (uint8)(0x01u << Tx_CTRL_HD_SEND_SHIFT)
#define Tx_CTRL_HD_SEND_BREAK         (uint8)(0x01u << Tx_CTRL_HD_SEND_BREAK_SHIFT)
#define Tx_CTRL_MARK                  (uint8)(0x01u << Tx_CTRL_MARK_SHIFT)
#define Tx_CTRL_PARITY_TYPE_MASK      (uint8)(0x03u << Tx_CTRL_PARITY_TYPE0_SHIFT)
#define Tx_CTRL_RXADDR_MODE_MASK      (uint8)(0x07u << Tx_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define Tx_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define Tx_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define Tx_SEND_BREAK                         (0x00u)
#define Tx_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define Tx_REINIT                             (0x02u)
#define Tx_SEND_WAIT_REINIT                   (0x03u)

#define Tx_OVER_SAMPLE_8                      (8u)
#define Tx_OVER_SAMPLE_16                     (16u)

#define Tx_BIT_CENTER                         (Tx_OVER_SAMPLE_COUNT - 2u)

#define Tx_FIFO_LENGTH                        (4u)
#define Tx_NUMBER_OF_START_BIT                (1u)
#define Tx_MAX_BYTE_VALUE                     (0xFFu)

/* 8X always for count7 implementation */
#define Tx_TXBITCTR_BREAKBITS8X   ((Tx_BREAK_BITS_TX * Tx_OVER_SAMPLE_8) - 1u)
/* 8X or 16X for DP implementation */
#define Tx_TXBITCTR_BREAKBITS ((Tx_BREAK_BITS_TX * Tx_OVER_SAMPLE_COUNT) - 1u)

#define Tx_HALF_BIT_COUNT   \
                            (((Tx_OVER_SAMPLE_COUNT / 2u) + (Tx_USE23POLLING * 1u)) - 2u)
#if (Tx_OVER_SAMPLE_COUNT == Tx_OVER_SAMPLE_8)
    #define Tx_HD_TXBITCTR_INIT   (((Tx_BREAK_BITS_TX + \
                            Tx_NUMBER_OF_START_BIT) * Tx_OVER_SAMPLE_COUNT) - 1u)

    /* This parameter is increased on the 2 in 2 out of 3 mode to sample voting in the middle */
    #define Tx_RXBITCTR_INIT  ((((Tx_BREAK_BITS_RX + Tx_NUMBER_OF_START_BIT) \
                            * Tx_OVER_SAMPLE_COUNT) + Tx_HALF_BIT_COUNT) - 1u)

#else /* Tx_OVER_SAMPLE_COUNT == Tx_OVER_SAMPLE_16 */
    #define Tx_HD_TXBITCTR_INIT   ((8u * Tx_OVER_SAMPLE_COUNT) - 1u)
    /* 7bit counter need one more bit for OverSampleCount = 16 */
    #define Tx_RXBITCTR_INIT      (((7u * Tx_OVER_SAMPLE_COUNT) - 1u) + \
                                                      Tx_HALF_BIT_COUNT)
#endif /* End Tx_OVER_SAMPLE_COUNT */

#define Tx_HD_RXBITCTR_INIT                   Tx_RXBITCTR_INIT


/***************************************
* Global variables external identifier
***************************************/

extern uint8 Tx_initVar;
#if (Tx_TX_INTERRUPT_ENABLED && Tx_TX_ENABLED)
    extern volatile uint8 Tx_txBuffer[Tx_TX_BUFFER_SIZE];
    extern volatile uint8 Tx_txBufferRead;
    extern uint8 Tx_txBufferWrite;
#endif /* (Tx_TX_INTERRUPT_ENABLED && Tx_TX_ENABLED) */
#if (Tx_RX_INTERRUPT_ENABLED && (Tx_RX_ENABLED || Tx_HD_ENABLED))
    extern uint8 Tx_errorStatus;
    extern volatile uint8 Tx_rxBuffer[Tx_RX_BUFFER_SIZE];
    extern volatile uint8 Tx_rxBufferRead;
    extern volatile uint8 Tx_rxBufferWrite;
    extern volatile uint8 Tx_rxBufferLoopDetect;
    extern volatile uint8 Tx_rxBufferOverflow;
    #if (Tx_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 Tx_rxAddressMode;
        extern volatile uint8 Tx_rxAddressDetected;
    #endif /* (Tx_RXHW_ADDRESS_ENABLED) */
#endif /* (Tx_RX_INTERRUPT_ENABLED && (Tx_RX_ENABLED || Tx_HD_ENABLED)) */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define Tx__B_UART__AM_SW_BYTE_BYTE 1
#define Tx__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define Tx__B_UART__AM_HW_BYTE_BY_BYTE 3
#define Tx__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define Tx__B_UART__AM_NONE 0

#define Tx__B_UART__NONE_REVB 0
#define Tx__B_UART__EVEN_REVB 1
#define Tx__B_UART__ODD_REVB 2
#define Tx__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define Tx_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define Tx_NUMBER_OF_STOP_BITS    (1u)

#if (Tx_RXHW_ADDRESS_ENABLED)
    #define Tx_RX_ADDRESS_MODE    (0u)
    #define Tx_RX_HW_ADDRESS1     (0u)
    #define Tx_RX_HW_ADDRESS2     (0u)
#endif /* (Tx_RXHW_ADDRESS_ENABLED) */

#define Tx_INIT_RX_INTERRUPTS_MASK \
                                  (uint8)((0 << Tx_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << Tx_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << Tx_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << Tx_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << Tx_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << Tx_RX_STS_BREAK_SHIFT) \
                                        | (0 << Tx_RX_STS_OVERRUN_SHIFT))

#define Tx_INIT_TX_INTERRUPTS_MASK \
                                  (uint8)((0 << Tx_TX_STS_COMPLETE_SHIFT) \
                                        | (0 << Tx_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << Tx_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << Tx_TX_STS_FIFO_NOT_FULL_SHIFT))


/***************************************
*              Registers
***************************************/

#ifdef Tx_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define Tx_CONTROL_REG \
                            (* (reg8 *) Tx_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
    #define Tx_CONTROL_PTR \
                            (  (reg8 *) Tx_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
#endif /* End Tx_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(Tx_TX_ENABLED)
    #define Tx_TXDATA_REG          (* (reg8 *) Tx_BUART_sTX_TxShifter_u0__F0_REG)
    #define Tx_TXDATA_PTR          (  (reg8 *) Tx_BUART_sTX_TxShifter_u0__F0_REG)
    #define Tx_TXDATA_AUX_CTL_REG  (* (reg8 *) Tx_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define Tx_TXDATA_AUX_CTL_PTR  (  (reg8 *) Tx_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define Tx_TXSTATUS_REG        (* (reg8 *) Tx_BUART_sTX_TxSts__STATUS_REG)
    #define Tx_TXSTATUS_PTR        (  (reg8 *) Tx_BUART_sTX_TxSts__STATUS_REG)
    #define Tx_TXSTATUS_MASK_REG   (* (reg8 *) Tx_BUART_sTX_TxSts__MASK_REG)
    #define Tx_TXSTATUS_MASK_PTR   (  (reg8 *) Tx_BUART_sTX_TxSts__MASK_REG)
    #define Tx_TXSTATUS_ACTL_REG   (* (reg8 *) Tx_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define Tx_TXSTATUS_ACTL_PTR   (  (reg8 *) Tx_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(Tx_TXCLKGEN_DP)
        #define Tx_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) Tx_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define Tx_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) Tx_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define Tx_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) Tx_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define Tx_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) Tx_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define Tx_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) Tx_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define Tx_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) Tx_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define Tx_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) Tx_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define Tx_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) Tx_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define Tx_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) Tx_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define Tx_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) Tx_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* Tx_TXCLKGEN_DP */

#endif /* End Tx_TX_ENABLED */

#if(Tx_HD_ENABLED)

    #define Tx_TXDATA_REG             (* (reg8 *) Tx_BUART_sRX_RxShifter_u0__F1_REG )
    #define Tx_TXDATA_PTR             (  (reg8 *) Tx_BUART_sRX_RxShifter_u0__F1_REG )
    #define Tx_TXDATA_AUX_CTL_REG     (* (reg8 *) Tx_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define Tx_TXDATA_AUX_CTL_PTR     (  (reg8 *) Tx_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define Tx_TXSTATUS_REG           (* (reg8 *) Tx_BUART_sRX_RxSts__STATUS_REG )
    #define Tx_TXSTATUS_PTR           (  (reg8 *) Tx_BUART_sRX_RxSts__STATUS_REG )
    #define Tx_TXSTATUS_MASK_REG      (* (reg8 *) Tx_BUART_sRX_RxSts__MASK_REG )
    #define Tx_TXSTATUS_MASK_PTR      (  (reg8 *) Tx_BUART_sRX_RxSts__MASK_REG )
    #define Tx_TXSTATUS_ACTL_REG      (* (reg8 *) Tx_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define Tx_TXSTATUS_ACTL_PTR      (  (reg8 *) Tx_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End Tx_HD_ENABLED */

#if( (Tx_RX_ENABLED) || (Tx_HD_ENABLED) )
    #define Tx_RXDATA_REG             (* (reg8 *) Tx_BUART_sRX_RxShifter_u0__F0_REG )
    #define Tx_RXDATA_PTR             (  (reg8 *) Tx_BUART_sRX_RxShifter_u0__F0_REG )
    #define Tx_RXADDRESS1_REG         (* (reg8 *) Tx_BUART_sRX_RxShifter_u0__D0_REG )
    #define Tx_RXADDRESS1_PTR         (  (reg8 *) Tx_BUART_sRX_RxShifter_u0__D0_REG )
    #define Tx_RXADDRESS2_REG         (* (reg8 *) Tx_BUART_sRX_RxShifter_u0__D1_REG )
    #define Tx_RXADDRESS2_PTR         (  (reg8 *) Tx_BUART_sRX_RxShifter_u0__D1_REG )
    #define Tx_RXDATA_AUX_CTL_REG     (* (reg8 *) Tx_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define Tx_RXBITCTR_PERIOD_REG    (* (reg8 *) Tx_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define Tx_RXBITCTR_PERIOD_PTR    (  (reg8 *) Tx_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define Tx_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) Tx_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define Tx_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) Tx_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define Tx_RXBITCTR_COUNTER_REG   (* (reg8 *) Tx_BUART_sRX_RxBitCounter__COUNT_REG )
    #define Tx_RXBITCTR_COUNTER_PTR   (  (reg8 *) Tx_BUART_sRX_RxBitCounter__COUNT_REG )

    #define Tx_RXSTATUS_REG           (* (reg8 *) Tx_BUART_sRX_RxSts__STATUS_REG )
    #define Tx_RXSTATUS_PTR           (  (reg8 *) Tx_BUART_sRX_RxSts__STATUS_REG )
    #define Tx_RXSTATUS_MASK_REG      (* (reg8 *) Tx_BUART_sRX_RxSts__MASK_REG )
    #define Tx_RXSTATUS_MASK_PTR      (  (reg8 *) Tx_BUART_sRX_RxSts__MASK_REG )
    #define Tx_RXSTATUS_ACTL_REG      (* (reg8 *) Tx_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define Tx_RXSTATUS_ACTL_PTR      (  (reg8 *) Tx_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (Tx_RX_ENABLED) || (Tx_HD_ENABLED) */

#if(Tx_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define Tx_INTCLOCK_CLKEN_REG     (* (reg8 *) Tx_IntClock__PM_ACT_CFG)
    #define Tx_INTCLOCK_CLKEN_PTR     (  (reg8 *) Tx_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define Tx_INTCLOCK_CLKEN_MASK    Tx_IntClock__PM_ACT_MSK
#endif /* End Tx_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants
***************************************/

#if(Tx_TX_ENABLED)
    #define Tx_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End Tx_TX_ENABLED */

#if(Tx_HD_ENABLED)
    #define Tx_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End Tx_HD_ENABLED */

#if( (Tx_RX_ENABLED) || (Tx_HD_ENABLED) )
    #define Tx_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (Tx_RX_ENABLED) || (Tx_HD_ENABLED) */


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

/* UART v2_40 obsolete definitions */
#define Tx_TXBUFFERSIZE   Tx_TX_BUFFER_SIZE
#define Tx_RXBUFFERSIZE   Tx_RX_BUFFER_SIZE

#if (Tx_RXHW_ADDRESS_ENABLED)
    #define Tx_RXADDRESSMODE  Tx_RX_ADDRESS_MODE
    #define Tx_RXHWADDRESS1   Tx_RX_HW_ADDRESS1
    #define Tx_RXHWADDRESS2   Tx_RX_HW_ADDRESS2
    /* Backward compatible define */
    #define Tx_RXAddressMode  Tx_RXADDRESSMODE
#endif /* (Tx_RXHW_ADDRESS_ENABLED) */

/* UART v2_30 obsolete definitions */
#define Tx_initvar                    Tx_initVar

#define Tx_RX_Enabled                 Tx_RX_ENABLED
#define Tx_TX_Enabled                 Tx_TX_ENABLED
#define Tx_HD_Enabled                 Tx_HD_ENABLED
#define Tx_RX_IntInterruptEnabled     Tx_RX_INTERRUPT_ENABLED
#define Tx_TX_IntInterruptEnabled     Tx_TX_INTERRUPT_ENABLED
#define Tx_InternalClockUsed          Tx_INTERNAL_CLOCK_USED
#define Tx_RXHW_Address_Enabled       Tx_RXHW_ADDRESS_ENABLED
#define Tx_OverSampleCount            Tx_OVER_SAMPLE_COUNT
#define Tx_ParityType                 Tx_PARITY_TYPE

#if( Tx_TX_ENABLED && (Tx_TXBUFFERSIZE > Tx_FIFO_LENGTH))
    #define Tx_TXBUFFER               Tx_txBuffer
    #define Tx_TXBUFFERREAD           Tx_txBufferRead
    #define Tx_TXBUFFERWRITE          Tx_txBufferWrite
#endif /* End Tx_TX_ENABLED */
#if( ( Tx_RX_ENABLED || Tx_HD_ENABLED ) && \
     (Tx_RXBUFFERSIZE > Tx_FIFO_LENGTH) )
    #define Tx_RXBUFFER               Tx_rxBuffer
    #define Tx_RXBUFFERREAD           Tx_rxBufferRead
    #define Tx_RXBUFFERWRITE          Tx_rxBufferWrite
    #define Tx_RXBUFFERLOOPDETECT     Tx_rxBufferLoopDetect
    #define Tx_RXBUFFER_OVERFLOW      Tx_rxBufferOverflow
#endif /* End Tx_RX_ENABLED */

#ifdef Tx_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define Tx_CONTROL                Tx_CONTROL_REG
#endif /* End Tx_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(Tx_TX_ENABLED)
    #define Tx_TXDATA                 Tx_TXDATA_REG
    #define Tx_TXSTATUS               Tx_TXSTATUS_REG
    #define Tx_TXSTATUS_MASK          Tx_TXSTATUS_MASK_REG
    #define Tx_TXSTATUS_ACTL          Tx_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(Tx_TXCLKGEN_DP)
        #define Tx_TXBITCLKGEN_CTR        Tx_TXBITCLKGEN_CTR_REG
        #define Tx_TXBITCLKTX_COMPLETE    Tx_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define Tx_TXBITCTR_PERIOD        Tx_TXBITCTR_PERIOD_REG
        #define Tx_TXBITCTR_CONTROL       Tx_TXBITCTR_CONTROL_REG
        #define Tx_TXBITCTR_COUNTER       Tx_TXBITCTR_COUNTER_REG
    #endif /* Tx_TXCLKGEN_DP */
#endif /* End Tx_TX_ENABLED */

#if(Tx_HD_ENABLED)
    #define Tx_TXDATA                 Tx_TXDATA_REG
    #define Tx_TXSTATUS               Tx_TXSTATUS_REG
    #define Tx_TXSTATUS_MASK          Tx_TXSTATUS_MASK_REG
    #define Tx_TXSTATUS_ACTL          Tx_TXSTATUS_ACTL_REG
#endif /* End Tx_HD_ENABLED */

#if( (Tx_RX_ENABLED) || (Tx_HD_ENABLED) )
    #define Tx_RXDATA                 Tx_RXDATA_REG
    #define Tx_RXADDRESS1             Tx_RXADDRESS1_REG
    #define Tx_RXADDRESS2             Tx_RXADDRESS2_REG
    #define Tx_RXBITCTR_PERIOD        Tx_RXBITCTR_PERIOD_REG
    #define Tx_RXBITCTR_CONTROL       Tx_RXBITCTR_CONTROL_REG
    #define Tx_RXBITCTR_COUNTER       Tx_RXBITCTR_COUNTER_REG
    #define Tx_RXSTATUS               Tx_RXSTATUS_REG
    #define Tx_RXSTATUS_MASK          Tx_RXSTATUS_MASK_REG
    #define Tx_RXSTATUS_ACTL          Tx_RXSTATUS_ACTL_REG
#endif /* End  (Tx_RX_ENABLED) || (Tx_HD_ENABLED) */

#if(Tx_INTERNAL_CLOCK_USED)
    #define Tx_INTCLOCK_CLKEN         Tx_INTCLOCK_CLKEN_REG
#endif /* End Tx_INTERNAL_CLOCK_USED */

#define Tx_WAIT_FOR_COMLETE_REINIT    Tx_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_Tx_H */


/* [] END OF FILE */
