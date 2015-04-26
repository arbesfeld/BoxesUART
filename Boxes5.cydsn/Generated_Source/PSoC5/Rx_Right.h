/*******************************************************************************
* File Name: Rx_Right.h
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


#if !defined(CY_UART_Rx_Right_H)
#define CY_UART_Rx_Right_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"


/***************************************
* Conditional Compilation Parameters
***************************************/

#define Rx_Right_RX_ENABLED                     (1u)
#define Rx_Right_TX_ENABLED                     (0u)
#define Rx_Right_HD_ENABLED                     (0u)
#define Rx_Right_RX_INTERRUPT_ENABLED           (0u)
#define Rx_Right_TX_INTERRUPT_ENABLED           (0u)
#define Rx_Right_INTERNAL_CLOCK_USED            (1u)
#define Rx_Right_RXHW_ADDRESS_ENABLED           (0u)
#define Rx_Right_OVER_SAMPLE_COUNT              (8u)
#define Rx_Right_PARITY_TYPE                    (0u)
#define Rx_Right_PARITY_TYPE_SW                 (0u)
#define Rx_Right_BREAK_DETECT                   (0u)
#define Rx_Right_BREAK_BITS_TX                  (13u)
#define Rx_Right_BREAK_BITS_RX                  (13u)
#define Rx_Right_TXCLKGEN_DP                    (1u)
#define Rx_Right_USE23POLLING                   (1u)
#define Rx_Right_FLOW_CONTROL                   (0u)
#define Rx_Right_CLK_FREQ                       (0u)
#define Rx_Right_TX_BUFFER_SIZE                 (4u)
#define Rx_Right_RX_BUFFER_SIZE                 (4u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component UART_v2_40 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#if defined(Rx_Right_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG)
    #define Rx_Right_CONTROL_REG_REMOVED            (0u)
#else
    #define Rx_Right_CONTROL_REG_REMOVED            (1u)
#endif /* End Rx_Right_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Structure Definition
***************************************/

/* Sleep Mode API Support */
typedef struct Rx_Right_backupStruct_
{
    uint8 enableState;

    #if(Rx_Right_CONTROL_REG_REMOVED == 0u)
        uint8 cr;
    #endif /* End Rx_Right_CONTROL_REG_REMOVED */

} Rx_Right_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void Rx_Right_Start(void) ;
void Rx_Right_Stop(void) ;
uint8 Rx_Right_ReadControlRegister(void) ;
void Rx_Right_WriteControlRegister(uint8 control) ;

void Rx_Right_Init(void) ;
void Rx_Right_Enable(void) ;
void Rx_Right_SaveConfig(void) ;
void Rx_Right_RestoreConfig(void) ;
void Rx_Right_Sleep(void) ;
void Rx_Right_Wakeup(void) ;

/* Only if RX is enabled */
#if( (Rx_Right_RX_ENABLED) || (Rx_Right_HD_ENABLED) )

    #if (Rx_Right_RX_INTERRUPT_ENABLED)
        #define Rx_Right_EnableRxInt()  CyIntEnable (Rx_Right_RX_VECT_NUM)
        #define Rx_Right_DisableRxInt() CyIntDisable(Rx_Right_RX_VECT_NUM)
        CY_ISR_PROTO(Rx_Right_RXISR);
    #endif /* Rx_Right_RX_INTERRUPT_ENABLED */

    void Rx_Right_SetRxAddressMode(uint8 addressMode)
                                                           ;
    void Rx_Right_SetRxAddress1(uint8 address) ;
    void Rx_Right_SetRxAddress2(uint8 address) ;

    void  Rx_Right_SetRxInterruptMode(uint8 intSrc) ;
    uint8 Rx_Right_ReadRxData(void) ;
    uint8 Rx_Right_ReadRxStatus(void) ;
    uint8 Rx_Right_GetChar(void) ;
    uint16 Rx_Right_GetByte(void) ;
    uint8 Rx_Right_GetRxBufferSize(void)
                                                            ;
    void Rx_Right_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define Rx_Right_GetRxInterruptSource   Rx_Right_ReadRxStatus

#endif /* End (Rx_Right_RX_ENABLED) || (Rx_Right_HD_ENABLED) */

/* Only if TX is enabled */
#if(Rx_Right_TX_ENABLED || Rx_Right_HD_ENABLED)

    #if(Rx_Right_TX_INTERRUPT_ENABLED)
        #define Rx_Right_EnableTxInt()  CyIntEnable (Rx_Right_TX_VECT_NUM)
        #define Rx_Right_DisableTxInt() CyIntDisable(Rx_Right_TX_VECT_NUM)
        #define Rx_Right_SetPendingTxInt() CyIntSetPending(Rx_Right_TX_VECT_NUM)
        #define Rx_Right_ClearPendingTxInt() CyIntClearPending(Rx_Right_TX_VECT_NUM)
        CY_ISR_PROTO(Rx_Right_TXISR);
    #endif /* Rx_Right_TX_INTERRUPT_ENABLED */

    void Rx_Right_SetTxInterruptMode(uint8 intSrc) ;
    void Rx_Right_WriteTxData(uint8 txDataByte) ;
    uint8 Rx_Right_ReadTxStatus(void) ;
    void Rx_Right_PutChar(uint8 txDataByte) ;
    void Rx_Right_PutString(const char8 string[]) ;
    void Rx_Right_PutArray(const uint8 string[], uint8 byteCount)
                                                            ;
    void Rx_Right_PutCRLF(uint8 txDataByte) ;
    void Rx_Right_ClearTxBuffer(void) ;
    void Rx_Right_SetTxAddressMode(uint8 addressMode) ;
    void Rx_Right_SendBreak(uint8 retMode) ;
    uint8 Rx_Right_GetTxBufferSize(void)
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define Rx_Right_PutStringConst         Rx_Right_PutString
    #define Rx_Right_PutArrayConst          Rx_Right_PutArray
    #define Rx_Right_GetTxInterruptSource   Rx_Right_ReadTxStatus

#endif /* End Rx_Right_TX_ENABLED || Rx_Right_HD_ENABLED */

#if(Rx_Right_HD_ENABLED)
    void Rx_Right_LoadRxConfig(void) ;
    void Rx_Right_LoadTxConfig(void) ;
#endif /* End Rx_Right_HD_ENABLED */


/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Rx_Right) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    Rx_Right_CyBtldrCommStart(void) CYSMALL ;
    void    Rx_Right_CyBtldrCommStop(void) CYSMALL ;
    void    Rx_Right_CyBtldrCommReset(void) CYSMALL ;
    cystatus Rx_Right_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus Rx_Right_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Rx_Right)
        #define CyBtldrCommStart    Rx_Right_CyBtldrCommStart
        #define CyBtldrCommStop     Rx_Right_CyBtldrCommStop
        #define CyBtldrCommReset    Rx_Right_CyBtldrCommReset
        #define CyBtldrCommWrite    Rx_Right_CyBtldrCommWrite
        #define CyBtldrCommRead     Rx_Right_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Rx_Right) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define Rx_Right_BYTE2BYTE_TIME_OUT (25u)
    #define Rx_Right_PACKET_EOP         (0x17u) /* End of packet defined by bootloader */
    #define Rx_Right_WAIT_EOP_DELAY     (5u)    /* Additional 5ms to wait for End of packet */
    #define Rx_Right_WAIT_1_MS          (1u)    /* Time Out quantity equal 1mS */

#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define Rx_Right_SET_SPACE      (0x00u)
#define Rx_Right_SET_MARK       (0x01u)

/* Status Register definitions */
#if( (Rx_Right_TX_ENABLED) || (Rx_Right_HD_ENABLED) )
    #if(Rx_Right_TX_INTERRUPT_ENABLED)
        #define Rx_Right_TX_VECT_NUM            (uint8)Rx_Right_TXInternalInterrupt__INTC_NUMBER
        #define Rx_Right_TX_PRIOR_NUM           (uint8)Rx_Right_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* Rx_Right_TX_INTERRUPT_ENABLED */

    #define Rx_Right_TX_STS_COMPLETE_SHIFT          (0x00u)
    #define Rx_Right_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
    #define Rx_Right_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #if(Rx_Right_TX_ENABLED)
        #define Rx_Right_TX_STS_FIFO_FULL_SHIFT     (0x02u)
    #else /* (Rx_Right_HD_ENABLED) */
        #define Rx_Right_TX_STS_FIFO_FULL_SHIFT     (0x05u)  /* Needs MD=0 */
    #endif /* (Rx_Right_TX_ENABLED) */

    #define Rx_Right_TX_STS_COMPLETE            (uint8)(0x01u << Rx_Right_TX_STS_COMPLETE_SHIFT)
    #define Rx_Right_TX_STS_FIFO_EMPTY          (uint8)(0x01u << Rx_Right_TX_STS_FIFO_EMPTY_SHIFT)
    #define Rx_Right_TX_STS_FIFO_FULL           (uint8)(0x01u << Rx_Right_TX_STS_FIFO_FULL_SHIFT)
    #define Rx_Right_TX_STS_FIFO_NOT_FULL       (uint8)(0x01u << Rx_Right_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (Rx_Right_TX_ENABLED) || (Rx_Right_HD_ENABLED)*/

#if( (Rx_Right_RX_ENABLED) || (Rx_Right_HD_ENABLED) )
    #if(Rx_Right_RX_INTERRUPT_ENABLED)
        #define Rx_Right_RX_VECT_NUM            (uint8)Rx_Right_RXInternalInterrupt__INTC_NUMBER
        #define Rx_Right_RX_PRIOR_NUM           (uint8)Rx_Right_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* Rx_Right_RX_INTERRUPT_ENABLED */
    #define Rx_Right_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define Rx_Right_RX_STS_BREAK_SHIFT             (0x01u)
    #define Rx_Right_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define Rx_Right_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define Rx_Right_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define Rx_Right_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define Rx_Right_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define Rx_Right_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define Rx_Right_RX_STS_MRKSPC           (uint8)(0x01u << Rx_Right_RX_STS_MRKSPC_SHIFT)
    #define Rx_Right_RX_STS_BREAK            (uint8)(0x01u << Rx_Right_RX_STS_BREAK_SHIFT)
    #define Rx_Right_RX_STS_PAR_ERROR        (uint8)(0x01u << Rx_Right_RX_STS_PAR_ERROR_SHIFT)
    #define Rx_Right_RX_STS_STOP_ERROR       (uint8)(0x01u << Rx_Right_RX_STS_STOP_ERROR_SHIFT)
    #define Rx_Right_RX_STS_OVERRUN          (uint8)(0x01u << Rx_Right_RX_STS_OVERRUN_SHIFT)
    #define Rx_Right_RX_STS_FIFO_NOTEMPTY    (uint8)(0x01u << Rx_Right_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define Rx_Right_RX_STS_ADDR_MATCH       (uint8)(0x01u << Rx_Right_RX_STS_ADDR_MATCH_SHIFT)
    #define Rx_Right_RX_STS_SOFT_BUFF_OVER   (uint8)(0x01u << Rx_Right_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define Rx_Right_RX_HW_MASK                     (0x7Fu)
#endif /* End (Rx_Right_RX_ENABLED) || (Rx_Right_HD_ENABLED) */

/* Control Register definitions */
#define Rx_Right_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define Rx_Right_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define Rx_Right_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define Rx_Right_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define Rx_Right_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define Rx_Right_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define Rx_Right_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define Rx_Right_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define Rx_Right_CTRL_HD_SEND               (uint8)(0x01u << Rx_Right_CTRL_HD_SEND_SHIFT)
#define Rx_Right_CTRL_HD_SEND_BREAK         (uint8)(0x01u << Rx_Right_CTRL_HD_SEND_BREAK_SHIFT)
#define Rx_Right_CTRL_MARK                  (uint8)(0x01u << Rx_Right_CTRL_MARK_SHIFT)
#define Rx_Right_CTRL_PARITY_TYPE_MASK      (uint8)(0x03u << Rx_Right_CTRL_PARITY_TYPE0_SHIFT)
#define Rx_Right_CTRL_RXADDR_MODE_MASK      (uint8)(0x07u << Rx_Right_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define Rx_Right_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define Rx_Right_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define Rx_Right_SEND_BREAK                         (0x00u)
#define Rx_Right_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define Rx_Right_REINIT                             (0x02u)
#define Rx_Right_SEND_WAIT_REINIT                   (0x03u)

#define Rx_Right_OVER_SAMPLE_8                      (8u)
#define Rx_Right_OVER_SAMPLE_16                     (16u)

#define Rx_Right_BIT_CENTER                         (Rx_Right_OVER_SAMPLE_COUNT - 2u)

#define Rx_Right_FIFO_LENGTH                        (4u)
#define Rx_Right_NUMBER_OF_START_BIT                (1u)
#define Rx_Right_MAX_BYTE_VALUE                     (0xFFu)

/* 8X always for count7 implementation */
#define Rx_Right_TXBITCTR_BREAKBITS8X   ((Rx_Right_BREAK_BITS_TX * Rx_Right_OVER_SAMPLE_8) - 1u)
/* 8X or 16X for DP implementation */
#define Rx_Right_TXBITCTR_BREAKBITS ((Rx_Right_BREAK_BITS_TX * Rx_Right_OVER_SAMPLE_COUNT) - 1u)

#define Rx_Right_HALF_BIT_COUNT   \
                            (((Rx_Right_OVER_SAMPLE_COUNT / 2u) + (Rx_Right_USE23POLLING * 1u)) - 2u)
#if (Rx_Right_OVER_SAMPLE_COUNT == Rx_Right_OVER_SAMPLE_8)
    #define Rx_Right_HD_TXBITCTR_INIT   (((Rx_Right_BREAK_BITS_TX + \
                            Rx_Right_NUMBER_OF_START_BIT) * Rx_Right_OVER_SAMPLE_COUNT) - 1u)

    /* This parameter is increased on the 2 in 2 out of 3 mode to sample voting in the middle */
    #define Rx_Right_RXBITCTR_INIT  ((((Rx_Right_BREAK_BITS_RX + Rx_Right_NUMBER_OF_START_BIT) \
                            * Rx_Right_OVER_SAMPLE_COUNT) + Rx_Right_HALF_BIT_COUNT) - 1u)

#else /* Rx_Right_OVER_SAMPLE_COUNT == Rx_Right_OVER_SAMPLE_16 */
    #define Rx_Right_HD_TXBITCTR_INIT   ((8u * Rx_Right_OVER_SAMPLE_COUNT) - 1u)
    /* 7bit counter need one more bit for OverSampleCount = 16 */
    #define Rx_Right_RXBITCTR_INIT      (((7u * Rx_Right_OVER_SAMPLE_COUNT) - 1u) + \
                                                      Rx_Right_HALF_BIT_COUNT)
#endif /* End Rx_Right_OVER_SAMPLE_COUNT */

#define Rx_Right_HD_RXBITCTR_INIT                   Rx_Right_RXBITCTR_INIT


/***************************************
* Global variables external identifier
***************************************/

extern uint8 Rx_Right_initVar;
#if (Rx_Right_TX_INTERRUPT_ENABLED && Rx_Right_TX_ENABLED)
    extern volatile uint8 Rx_Right_txBuffer[Rx_Right_TX_BUFFER_SIZE];
    extern volatile uint8 Rx_Right_txBufferRead;
    extern uint8 Rx_Right_txBufferWrite;
#endif /* (Rx_Right_TX_INTERRUPT_ENABLED && Rx_Right_TX_ENABLED) */
#if (Rx_Right_RX_INTERRUPT_ENABLED && (Rx_Right_RX_ENABLED || Rx_Right_HD_ENABLED))
    extern uint8 Rx_Right_errorStatus;
    extern volatile uint8 Rx_Right_rxBuffer[Rx_Right_RX_BUFFER_SIZE];
    extern volatile uint8 Rx_Right_rxBufferRead;
    extern volatile uint8 Rx_Right_rxBufferWrite;
    extern volatile uint8 Rx_Right_rxBufferLoopDetect;
    extern volatile uint8 Rx_Right_rxBufferOverflow;
    #if (Rx_Right_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 Rx_Right_rxAddressMode;
        extern volatile uint8 Rx_Right_rxAddressDetected;
    #endif /* (Rx_Right_RXHW_ADDRESS_ENABLED) */
#endif /* (Rx_Right_RX_INTERRUPT_ENABLED && (Rx_Right_RX_ENABLED || Rx_Right_HD_ENABLED)) */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define Rx_Right__B_UART__AM_SW_BYTE_BYTE 1
#define Rx_Right__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define Rx_Right__B_UART__AM_HW_BYTE_BY_BYTE 3
#define Rx_Right__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define Rx_Right__B_UART__AM_NONE 0

#define Rx_Right__B_UART__NONE_REVB 0
#define Rx_Right__B_UART__EVEN_REVB 1
#define Rx_Right__B_UART__ODD_REVB 2
#define Rx_Right__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define Rx_Right_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define Rx_Right_NUMBER_OF_STOP_BITS    (1u)

#if (Rx_Right_RXHW_ADDRESS_ENABLED)
    #define Rx_Right_RX_ADDRESS_MODE    (0u)
    #define Rx_Right_RX_HW_ADDRESS1     (0u)
    #define Rx_Right_RX_HW_ADDRESS2     (0u)
#endif /* (Rx_Right_RXHW_ADDRESS_ENABLED) */

#define Rx_Right_INIT_RX_INTERRUPTS_MASK \
                                  (uint8)((1 << Rx_Right_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << Rx_Right_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << Rx_Right_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << Rx_Right_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << Rx_Right_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << Rx_Right_RX_STS_BREAK_SHIFT) \
                                        | (0 << Rx_Right_RX_STS_OVERRUN_SHIFT))

#define Rx_Right_INIT_TX_INTERRUPTS_MASK \
                                  (uint8)((0 << Rx_Right_TX_STS_COMPLETE_SHIFT) \
                                        | (0 << Rx_Right_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << Rx_Right_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << Rx_Right_TX_STS_FIFO_NOT_FULL_SHIFT))


/***************************************
*              Registers
***************************************/

#ifdef Rx_Right_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define Rx_Right_CONTROL_REG \
                            (* (reg8 *) Rx_Right_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
    #define Rx_Right_CONTROL_PTR \
                            (  (reg8 *) Rx_Right_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
#endif /* End Rx_Right_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(Rx_Right_TX_ENABLED)
    #define Rx_Right_TXDATA_REG          (* (reg8 *) Rx_Right_BUART_sTX_TxShifter_u0__F0_REG)
    #define Rx_Right_TXDATA_PTR          (  (reg8 *) Rx_Right_BUART_sTX_TxShifter_u0__F0_REG)
    #define Rx_Right_TXDATA_AUX_CTL_REG  (* (reg8 *) Rx_Right_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define Rx_Right_TXDATA_AUX_CTL_PTR  (  (reg8 *) Rx_Right_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define Rx_Right_TXSTATUS_REG        (* (reg8 *) Rx_Right_BUART_sTX_TxSts__STATUS_REG)
    #define Rx_Right_TXSTATUS_PTR        (  (reg8 *) Rx_Right_BUART_sTX_TxSts__STATUS_REG)
    #define Rx_Right_TXSTATUS_MASK_REG   (* (reg8 *) Rx_Right_BUART_sTX_TxSts__MASK_REG)
    #define Rx_Right_TXSTATUS_MASK_PTR   (  (reg8 *) Rx_Right_BUART_sTX_TxSts__MASK_REG)
    #define Rx_Right_TXSTATUS_ACTL_REG   (* (reg8 *) Rx_Right_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define Rx_Right_TXSTATUS_ACTL_PTR   (  (reg8 *) Rx_Right_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(Rx_Right_TXCLKGEN_DP)
        #define Rx_Right_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) Rx_Right_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define Rx_Right_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) Rx_Right_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define Rx_Right_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) Rx_Right_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define Rx_Right_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) Rx_Right_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define Rx_Right_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) Rx_Right_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define Rx_Right_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) Rx_Right_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define Rx_Right_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) Rx_Right_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define Rx_Right_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) Rx_Right_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define Rx_Right_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) Rx_Right_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define Rx_Right_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) Rx_Right_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* Rx_Right_TXCLKGEN_DP */

#endif /* End Rx_Right_TX_ENABLED */

#if(Rx_Right_HD_ENABLED)

    #define Rx_Right_TXDATA_REG             (* (reg8 *) Rx_Right_BUART_sRX_RxShifter_u0__F1_REG )
    #define Rx_Right_TXDATA_PTR             (  (reg8 *) Rx_Right_BUART_sRX_RxShifter_u0__F1_REG )
    #define Rx_Right_TXDATA_AUX_CTL_REG     (* (reg8 *) Rx_Right_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define Rx_Right_TXDATA_AUX_CTL_PTR     (  (reg8 *) Rx_Right_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define Rx_Right_TXSTATUS_REG           (* (reg8 *) Rx_Right_BUART_sRX_RxSts__STATUS_REG )
    #define Rx_Right_TXSTATUS_PTR           (  (reg8 *) Rx_Right_BUART_sRX_RxSts__STATUS_REG )
    #define Rx_Right_TXSTATUS_MASK_REG      (* (reg8 *) Rx_Right_BUART_sRX_RxSts__MASK_REG )
    #define Rx_Right_TXSTATUS_MASK_PTR      (  (reg8 *) Rx_Right_BUART_sRX_RxSts__MASK_REG )
    #define Rx_Right_TXSTATUS_ACTL_REG      (* (reg8 *) Rx_Right_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define Rx_Right_TXSTATUS_ACTL_PTR      (  (reg8 *) Rx_Right_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End Rx_Right_HD_ENABLED */

#if( (Rx_Right_RX_ENABLED) || (Rx_Right_HD_ENABLED) )
    #define Rx_Right_RXDATA_REG             (* (reg8 *) Rx_Right_BUART_sRX_RxShifter_u0__F0_REG )
    #define Rx_Right_RXDATA_PTR             (  (reg8 *) Rx_Right_BUART_sRX_RxShifter_u0__F0_REG )
    #define Rx_Right_RXADDRESS1_REG         (* (reg8 *) Rx_Right_BUART_sRX_RxShifter_u0__D0_REG )
    #define Rx_Right_RXADDRESS1_PTR         (  (reg8 *) Rx_Right_BUART_sRX_RxShifter_u0__D0_REG )
    #define Rx_Right_RXADDRESS2_REG         (* (reg8 *) Rx_Right_BUART_sRX_RxShifter_u0__D1_REG )
    #define Rx_Right_RXADDRESS2_PTR         (  (reg8 *) Rx_Right_BUART_sRX_RxShifter_u0__D1_REG )
    #define Rx_Right_RXDATA_AUX_CTL_REG     (* (reg8 *) Rx_Right_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define Rx_Right_RXBITCTR_PERIOD_REG    (* (reg8 *) Rx_Right_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define Rx_Right_RXBITCTR_PERIOD_PTR    (  (reg8 *) Rx_Right_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define Rx_Right_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) Rx_Right_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define Rx_Right_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) Rx_Right_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define Rx_Right_RXBITCTR_COUNTER_REG   (* (reg8 *) Rx_Right_BUART_sRX_RxBitCounter__COUNT_REG )
    #define Rx_Right_RXBITCTR_COUNTER_PTR   (  (reg8 *) Rx_Right_BUART_sRX_RxBitCounter__COUNT_REG )

    #define Rx_Right_RXSTATUS_REG           (* (reg8 *) Rx_Right_BUART_sRX_RxSts__STATUS_REG )
    #define Rx_Right_RXSTATUS_PTR           (  (reg8 *) Rx_Right_BUART_sRX_RxSts__STATUS_REG )
    #define Rx_Right_RXSTATUS_MASK_REG      (* (reg8 *) Rx_Right_BUART_sRX_RxSts__MASK_REG )
    #define Rx_Right_RXSTATUS_MASK_PTR      (  (reg8 *) Rx_Right_BUART_sRX_RxSts__MASK_REG )
    #define Rx_Right_RXSTATUS_ACTL_REG      (* (reg8 *) Rx_Right_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define Rx_Right_RXSTATUS_ACTL_PTR      (  (reg8 *) Rx_Right_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (Rx_Right_RX_ENABLED) || (Rx_Right_HD_ENABLED) */

#if(Rx_Right_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define Rx_Right_INTCLOCK_CLKEN_REG     (* (reg8 *) Rx_Right_IntClock__PM_ACT_CFG)
    #define Rx_Right_INTCLOCK_CLKEN_PTR     (  (reg8 *) Rx_Right_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define Rx_Right_INTCLOCK_CLKEN_MASK    Rx_Right_IntClock__PM_ACT_MSK
#endif /* End Rx_Right_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants
***************************************/

#if(Rx_Right_TX_ENABLED)
    #define Rx_Right_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End Rx_Right_TX_ENABLED */

#if(Rx_Right_HD_ENABLED)
    #define Rx_Right_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End Rx_Right_HD_ENABLED */

#if( (Rx_Right_RX_ENABLED) || (Rx_Right_HD_ENABLED) )
    #define Rx_Right_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (Rx_Right_RX_ENABLED) || (Rx_Right_HD_ENABLED) */


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

/* UART v2_40 obsolete definitions */
#define Rx_Right_TXBUFFERSIZE   Rx_Right_TX_BUFFER_SIZE
#define Rx_Right_RXBUFFERSIZE   Rx_Right_RX_BUFFER_SIZE

#if (Rx_Right_RXHW_ADDRESS_ENABLED)
    #define Rx_Right_RXADDRESSMODE  Rx_Right_RX_ADDRESS_MODE
    #define Rx_Right_RXHWADDRESS1   Rx_Right_RX_HW_ADDRESS1
    #define Rx_Right_RXHWADDRESS2   Rx_Right_RX_HW_ADDRESS2
    /* Backward compatible define */
    #define Rx_Right_RXAddressMode  Rx_Right_RXADDRESSMODE
#endif /* (Rx_Right_RXHW_ADDRESS_ENABLED) */

/* UART v2_30 obsolete definitions */
#define Rx_Right_initvar                    Rx_Right_initVar

#define Rx_Right_RX_Enabled                 Rx_Right_RX_ENABLED
#define Rx_Right_TX_Enabled                 Rx_Right_TX_ENABLED
#define Rx_Right_HD_Enabled                 Rx_Right_HD_ENABLED
#define Rx_Right_RX_IntInterruptEnabled     Rx_Right_RX_INTERRUPT_ENABLED
#define Rx_Right_TX_IntInterruptEnabled     Rx_Right_TX_INTERRUPT_ENABLED
#define Rx_Right_InternalClockUsed          Rx_Right_INTERNAL_CLOCK_USED
#define Rx_Right_RXHW_Address_Enabled       Rx_Right_RXHW_ADDRESS_ENABLED
#define Rx_Right_OverSampleCount            Rx_Right_OVER_SAMPLE_COUNT
#define Rx_Right_ParityType                 Rx_Right_PARITY_TYPE

#if( Rx_Right_TX_ENABLED && (Rx_Right_TXBUFFERSIZE > Rx_Right_FIFO_LENGTH))
    #define Rx_Right_TXBUFFER               Rx_Right_txBuffer
    #define Rx_Right_TXBUFFERREAD           Rx_Right_txBufferRead
    #define Rx_Right_TXBUFFERWRITE          Rx_Right_txBufferWrite
#endif /* End Rx_Right_TX_ENABLED */
#if( ( Rx_Right_RX_ENABLED || Rx_Right_HD_ENABLED ) && \
     (Rx_Right_RXBUFFERSIZE > Rx_Right_FIFO_LENGTH) )
    #define Rx_Right_RXBUFFER               Rx_Right_rxBuffer
    #define Rx_Right_RXBUFFERREAD           Rx_Right_rxBufferRead
    #define Rx_Right_RXBUFFERWRITE          Rx_Right_rxBufferWrite
    #define Rx_Right_RXBUFFERLOOPDETECT     Rx_Right_rxBufferLoopDetect
    #define Rx_Right_RXBUFFER_OVERFLOW      Rx_Right_rxBufferOverflow
#endif /* End Rx_Right_RX_ENABLED */

#ifdef Rx_Right_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define Rx_Right_CONTROL                Rx_Right_CONTROL_REG
#endif /* End Rx_Right_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(Rx_Right_TX_ENABLED)
    #define Rx_Right_TXDATA                 Rx_Right_TXDATA_REG
    #define Rx_Right_TXSTATUS               Rx_Right_TXSTATUS_REG
    #define Rx_Right_TXSTATUS_MASK          Rx_Right_TXSTATUS_MASK_REG
    #define Rx_Right_TXSTATUS_ACTL          Rx_Right_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(Rx_Right_TXCLKGEN_DP)
        #define Rx_Right_TXBITCLKGEN_CTR        Rx_Right_TXBITCLKGEN_CTR_REG
        #define Rx_Right_TXBITCLKTX_COMPLETE    Rx_Right_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define Rx_Right_TXBITCTR_PERIOD        Rx_Right_TXBITCTR_PERIOD_REG
        #define Rx_Right_TXBITCTR_CONTROL       Rx_Right_TXBITCTR_CONTROL_REG
        #define Rx_Right_TXBITCTR_COUNTER       Rx_Right_TXBITCTR_COUNTER_REG
    #endif /* Rx_Right_TXCLKGEN_DP */
#endif /* End Rx_Right_TX_ENABLED */

#if(Rx_Right_HD_ENABLED)
    #define Rx_Right_TXDATA                 Rx_Right_TXDATA_REG
    #define Rx_Right_TXSTATUS               Rx_Right_TXSTATUS_REG
    #define Rx_Right_TXSTATUS_MASK          Rx_Right_TXSTATUS_MASK_REG
    #define Rx_Right_TXSTATUS_ACTL          Rx_Right_TXSTATUS_ACTL_REG
#endif /* End Rx_Right_HD_ENABLED */

#if( (Rx_Right_RX_ENABLED) || (Rx_Right_HD_ENABLED) )
    #define Rx_Right_RXDATA                 Rx_Right_RXDATA_REG
    #define Rx_Right_RXADDRESS1             Rx_Right_RXADDRESS1_REG
    #define Rx_Right_RXADDRESS2             Rx_Right_RXADDRESS2_REG
    #define Rx_Right_RXBITCTR_PERIOD        Rx_Right_RXBITCTR_PERIOD_REG
    #define Rx_Right_RXBITCTR_CONTROL       Rx_Right_RXBITCTR_CONTROL_REG
    #define Rx_Right_RXBITCTR_COUNTER       Rx_Right_RXBITCTR_COUNTER_REG
    #define Rx_Right_RXSTATUS               Rx_Right_RXSTATUS_REG
    #define Rx_Right_RXSTATUS_MASK          Rx_Right_RXSTATUS_MASK_REG
    #define Rx_Right_RXSTATUS_ACTL          Rx_Right_RXSTATUS_ACTL_REG
#endif /* End  (Rx_Right_RX_ENABLED) || (Rx_Right_HD_ENABLED) */

#if(Rx_Right_INTERNAL_CLOCK_USED)
    #define Rx_Right_INTCLOCK_CLKEN         Rx_Right_INTCLOCK_CLKEN_REG
#endif /* End Rx_Right_INTERNAL_CLOCK_USED */

#define Rx_Right_WAIT_FOR_COMLETE_REINIT    Rx_Right_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_Rx_Right_H */


/* [] END OF FILE */
