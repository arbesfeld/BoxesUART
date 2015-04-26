/*******************************************************************************
* File Name: Rx_Bottom.h
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


#if !defined(CY_UART_Rx_Bottom_H)
#define CY_UART_Rx_Bottom_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"


/***************************************
* Conditional Compilation Parameters
***************************************/

#define Rx_Bottom_RX_ENABLED                     (1u)
#define Rx_Bottom_TX_ENABLED                     (0u)
#define Rx_Bottom_HD_ENABLED                     (0u)
#define Rx_Bottom_RX_INTERRUPT_ENABLED           (0u)
#define Rx_Bottom_TX_INTERRUPT_ENABLED           (0u)
#define Rx_Bottom_INTERNAL_CLOCK_USED            (1u)
#define Rx_Bottom_RXHW_ADDRESS_ENABLED           (0u)
#define Rx_Bottom_OVER_SAMPLE_COUNT              (8u)
#define Rx_Bottom_PARITY_TYPE                    (0u)
#define Rx_Bottom_PARITY_TYPE_SW                 (0u)
#define Rx_Bottom_BREAK_DETECT                   (0u)
#define Rx_Bottom_BREAK_BITS_TX                  (13u)
#define Rx_Bottom_BREAK_BITS_RX                  (13u)
#define Rx_Bottom_TXCLKGEN_DP                    (1u)
#define Rx_Bottom_USE23POLLING                   (1u)
#define Rx_Bottom_FLOW_CONTROL                   (0u)
#define Rx_Bottom_CLK_FREQ                       (0u)
#define Rx_Bottom_TX_BUFFER_SIZE                 (4u)
#define Rx_Bottom_RX_BUFFER_SIZE                 (4u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component UART_v2_40 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#if defined(Rx_Bottom_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG)
    #define Rx_Bottom_CONTROL_REG_REMOVED            (0u)
#else
    #define Rx_Bottom_CONTROL_REG_REMOVED            (1u)
#endif /* End Rx_Bottom_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Structure Definition
***************************************/

/* Sleep Mode API Support */
typedef struct Rx_Bottom_backupStruct_
{
    uint8 enableState;

    #if(Rx_Bottom_CONTROL_REG_REMOVED == 0u)
        uint8 cr;
    #endif /* End Rx_Bottom_CONTROL_REG_REMOVED */

} Rx_Bottom_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void Rx_Bottom_Start(void) ;
void Rx_Bottom_Stop(void) ;
uint8 Rx_Bottom_ReadControlRegister(void) ;
void Rx_Bottom_WriteControlRegister(uint8 control) ;

void Rx_Bottom_Init(void) ;
void Rx_Bottom_Enable(void) ;
void Rx_Bottom_SaveConfig(void) ;
void Rx_Bottom_RestoreConfig(void) ;
void Rx_Bottom_Sleep(void) ;
void Rx_Bottom_Wakeup(void) ;

/* Only if RX is enabled */
#if( (Rx_Bottom_RX_ENABLED) || (Rx_Bottom_HD_ENABLED) )

    #if (Rx_Bottom_RX_INTERRUPT_ENABLED)
        #define Rx_Bottom_EnableRxInt()  CyIntEnable (Rx_Bottom_RX_VECT_NUM)
        #define Rx_Bottom_DisableRxInt() CyIntDisable(Rx_Bottom_RX_VECT_NUM)
        CY_ISR_PROTO(Rx_Bottom_RXISR);
    #endif /* Rx_Bottom_RX_INTERRUPT_ENABLED */

    void Rx_Bottom_SetRxAddressMode(uint8 addressMode)
                                                           ;
    void Rx_Bottom_SetRxAddress1(uint8 address) ;
    void Rx_Bottom_SetRxAddress2(uint8 address) ;

    void  Rx_Bottom_SetRxInterruptMode(uint8 intSrc) ;
    uint8 Rx_Bottom_ReadRxData(void) ;
    uint8 Rx_Bottom_ReadRxStatus(void) ;
    uint8 Rx_Bottom_GetChar(void) ;
    uint16 Rx_Bottom_GetByte(void) ;
    uint8 Rx_Bottom_GetRxBufferSize(void)
                                                            ;
    void Rx_Bottom_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define Rx_Bottom_GetRxInterruptSource   Rx_Bottom_ReadRxStatus

#endif /* End (Rx_Bottom_RX_ENABLED) || (Rx_Bottom_HD_ENABLED) */

/* Only if TX is enabled */
#if(Rx_Bottom_TX_ENABLED || Rx_Bottom_HD_ENABLED)

    #if(Rx_Bottom_TX_INTERRUPT_ENABLED)
        #define Rx_Bottom_EnableTxInt()  CyIntEnable (Rx_Bottom_TX_VECT_NUM)
        #define Rx_Bottom_DisableTxInt() CyIntDisable(Rx_Bottom_TX_VECT_NUM)
        #define Rx_Bottom_SetPendingTxInt() CyIntSetPending(Rx_Bottom_TX_VECT_NUM)
        #define Rx_Bottom_ClearPendingTxInt() CyIntClearPending(Rx_Bottom_TX_VECT_NUM)
        CY_ISR_PROTO(Rx_Bottom_TXISR);
    #endif /* Rx_Bottom_TX_INTERRUPT_ENABLED */

    void Rx_Bottom_SetTxInterruptMode(uint8 intSrc) ;
    void Rx_Bottom_WriteTxData(uint8 txDataByte) ;
    uint8 Rx_Bottom_ReadTxStatus(void) ;
    void Rx_Bottom_PutChar(uint8 txDataByte) ;
    void Rx_Bottom_PutString(const char8 string[]) ;
    void Rx_Bottom_PutArray(const uint8 string[], uint8 byteCount)
                                                            ;
    void Rx_Bottom_PutCRLF(uint8 txDataByte) ;
    void Rx_Bottom_ClearTxBuffer(void) ;
    void Rx_Bottom_SetTxAddressMode(uint8 addressMode) ;
    void Rx_Bottom_SendBreak(uint8 retMode) ;
    uint8 Rx_Bottom_GetTxBufferSize(void)
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define Rx_Bottom_PutStringConst         Rx_Bottom_PutString
    #define Rx_Bottom_PutArrayConst          Rx_Bottom_PutArray
    #define Rx_Bottom_GetTxInterruptSource   Rx_Bottom_ReadTxStatus

#endif /* End Rx_Bottom_TX_ENABLED || Rx_Bottom_HD_ENABLED */

#if(Rx_Bottom_HD_ENABLED)
    void Rx_Bottom_LoadRxConfig(void) ;
    void Rx_Bottom_LoadTxConfig(void) ;
#endif /* End Rx_Bottom_HD_ENABLED */


/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Rx_Bottom) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    Rx_Bottom_CyBtldrCommStart(void) CYSMALL ;
    void    Rx_Bottom_CyBtldrCommStop(void) CYSMALL ;
    void    Rx_Bottom_CyBtldrCommReset(void) CYSMALL ;
    cystatus Rx_Bottom_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus Rx_Bottom_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Rx_Bottom)
        #define CyBtldrCommStart    Rx_Bottom_CyBtldrCommStart
        #define CyBtldrCommStop     Rx_Bottom_CyBtldrCommStop
        #define CyBtldrCommReset    Rx_Bottom_CyBtldrCommReset
        #define CyBtldrCommWrite    Rx_Bottom_CyBtldrCommWrite
        #define CyBtldrCommRead     Rx_Bottom_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Rx_Bottom) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define Rx_Bottom_BYTE2BYTE_TIME_OUT (25u)
    #define Rx_Bottom_PACKET_EOP         (0x17u) /* End of packet defined by bootloader */
    #define Rx_Bottom_WAIT_EOP_DELAY     (5u)    /* Additional 5ms to wait for End of packet */
    #define Rx_Bottom_WAIT_1_MS          (1u)    /* Time Out quantity equal 1mS */

#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define Rx_Bottom_SET_SPACE      (0x00u)
#define Rx_Bottom_SET_MARK       (0x01u)

/* Status Register definitions */
#if( (Rx_Bottom_TX_ENABLED) || (Rx_Bottom_HD_ENABLED) )
    #if(Rx_Bottom_TX_INTERRUPT_ENABLED)
        #define Rx_Bottom_TX_VECT_NUM            (uint8)Rx_Bottom_TXInternalInterrupt__INTC_NUMBER
        #define Rx_Bottom_TX_PRIOR_NUM           (uint8)Rx_Bottom_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* Rx_Bottom_TX_INTERRUPT_ENABLED */

    #define Rx_Bottom_TX_STS_COMPLETE_SHIFT          (0x00u)
    #define Rx_Bottom_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
    #define Rx_Bottom_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #if(Rx_Bottom_TX_ENABLED)
        #define Rx_Bottom_TX_STS_FIFO_FULL_SHIFT     (0x02u)
    #else /* (Rx_Bottom_HD_ENABLED) */
        #define Rx_Bottom_TX_STS_FIFO_FULL_SHIFT     (0x05u)  /* Needs MD=0 */
    #endif /* (Rx_Bottom_TX_ENABLED) */

    #define Rx_Bottom_TX_STS_COMPLETE            (uint8)(0x01u << Rx_Bottom_TX_STS_COMPLETE_SHIFT)
    #define Rx_Bottom_TX_STS_FIFO_EMPTY          (uint8)(0x01u << Rx_Bottom_TX_STS_FIFO_EMPTY_SHIFT)
    #define Rx_Bottom_TX_STS_FIFO_FULL           (uint8)(0x01u << Rx_Bottom_TX_STS_FIFO_FULL_SHIFT)
    #define Rx_Bottom_TX_STS_FIFO_NOT_FULL       (uint8)(0x01u << Rx_Bottom_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (Rx_Bottom_TX_ENABLED) || (Rx_Bottom_HD_ENABLED)*/

#if( (Rx_Bottom_RX_ENABLED) || (Rx_Bottom_HD_ENABLED) )
    #if(Rx_Bottom_RX_INTERRUPT_ENABLED)
        #define Rx_Bottom_RX_VECT_NUM            (uint8)Rx_Bottom_RXInternalInterrupt__INTC_NUMBER
        #define Rx_Bottom_RX_PRIOR_NUM           (uint8)Rx_Bottom_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* Rx_Bottom_RX_INTERRUPT_ENABLED */
    #define Rx_Bottom_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define Rx_Bottom_RX_STS_BREAK_SHIFT             (0x01u)
    #define Rx_Bottom_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define Rx_Bottom_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define Rx_Bottom_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define Rx_Bottom_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define Rx_Bottom_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define Rx_Bottom_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define Rx_Bottom_RX_STS_MRKSPC           (uint8)(0x01u << Rx_Bottom_RX_STS_MRKSPC_SHIFT)
    #define Rx_Bottom_RX_STS_BREAK            (uint8)(0x01u << Rx_Bottom_RX_STS_BREAK_SHIFT)
    #define Rx_Bottom_RX_STS_PAR_ERROR        (uint8)(0x01u << Rx_Bottom_RX_STS_PAR_ERROR_SHIFT)
    #define Rx_Bottom_RX_STS_STOP_ERROR       (uint8)(0x01u << Rx_Bottom_RX_STS_STOP_ERROR_SHIFT)
    #define Rx_Bottom_RX_STS_OVERRUN          (uint8)(0x01u << Rx_Bottom_RX_STS_OVERRUN_SHIFT)
    #define Rx_Bottom_RX_STS_FIFO_NOTEMPTY    (uint8)(0x01u << Rx_Bottom_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define Rx_Bottom_RX_STS_ADDR_MATCH       (uint8)(0x01u << Rx_Bottom_RX_STS_ADDR_MATCH_SHIFT)
    #define Rx_Bottom_RX_STS_SOFT_BUFF_OVER   (uint8)(0x01u << Rx_Bottom_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define Rx_Bottom_RX_HW_MASK                     (0x7Fu)
#endif /* End (Rx_Bottom_RX_ENABLED) || (Rx_Bottom_HD_ENABLED) */

/* Control Register definitions */
#define Rx_Bottom_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define Rx_Bottom_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define Rx_Bottom_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define Rx_Bottom_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define Rx_Bottom_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define Rx_Bottom_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define Rx_Bottom_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define Rx_Bottom_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define Rx_Bottom_CTRL_HD_SEND               (uint8)(0x01u << Rx_Bottom_CTRL_HD_SEND_SHIFT)
#define Rx_Bottom_CTRL_HD_SEND_BREAK         (uint8)(0x01u << Rx_Bottom_CTRL_HD_SEND_BREAK_SHIFT)
#define Rx_Bottom_CTRL_MARK                  (uint8)(0x01u << Rx_Bottom_CTRL_MARK_SHIFT)
#define Rx_Bottom_CTRL_PARITY_TYPE_MASK      (uint8)(0x03u << Rx_Bottom_CTRL_PARITY_TYPE0_SHIFT)
#define Rx_Bottom_CTRL_RXADDR_MODE_MASK      (uint8)(0x07u << Rx_Bottom_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define Rx_Bottom_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define Rx_Bottom_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define Rx_Bottom_SEND_BREAK                         (0x00u)
#define Rx_Bottom_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define Rx_Bottom_REINIT                             (0x02u)
#define Rx_Bottom_SEND_WAIT_REINIT                   (0x03u)

#define Rx_Bottom_OVER_SAMPLE_8                      (8u)
#define Rx_Bottom_OVER_SAMPLE_16                     (16u)

#define Rx_Bottom_BIT_CENTER                         (Rx_Bottom_OVER_SAMPLE_COUNT - 2u)

#define Rx_Bottom_FIFO_LENGTH                        (4u)
#define Rx_Bottom_NUMBER_OF_START_BIT                (1u)
#define Rx_Bottom_MAX_BYTE_VALUE                     (0xFFu)

/* 8X always for count7 implementation */
#define Rx_Bottom_TXBITCTR_BREAKBITS8X   ((Rx_Bottom_BREAK_BITS_TX * Rx_Bottom_OVER_SAMPLE_8) - 1u)
/* 8X or 16X for DP implementation */
#define Rx_Bottom_TXBITCTR_BREAKBITS ((Rx_Bottom_BREAK_BITS_TX * Rx_Bottom_OVER_SAMPLE_COUNT) - 1u)

#define Rx_Bottom_HALF_BIT_COUNT   \
                            (((Rx_Bottom_OVER_SAMPLE_COUNT / 2u) + (Rx_Bottom_USE23POLLING * 1u)) - 2u)
#if (Rx_Bottom_OVER_SAMPLE_COUNT == Rx_Bottom_OVER_SAMPLE_8)
    #define Rx_Bottom_HD_TXBITCTR_INIT   (((Rx_Bottom_BREAK_BITS_TX + \
                            Rx_Bottom_NUMBER_OF_START_BIT) * Rx_Bottom_OVER_SAMPLE_COUNT) - 1u)

    /* This parameter is increased on the 2 in 2 out of 3 mode to sample voting in the middle */
    #define Rx_Bottom_RXBITCTR_INIT  ((((Rx_Bottom_BREAK_BITS_RX + Rx_Bottom_NUMBER_OF_START_BIT) \
                            * Rx_Bottom_OVER_SAMPLE_COUNT) + Rx_Bottom_HALF_BIT_COUNT) - 1u)

#else /* Rx_Bottom_OVER_SAMPLE_COUNT == Rx_Bottom_OVER_SAMPLE_16 */
    #define Rx_Bottom_HD_TXBITCTR_INIT   ((8u * Rx_Bottom_OVER_SAMPLE_COUNT) - 1u)
    /* 7bit counter need one more bit for OverSampleCount = 16 */
    #define Rx_Bottom_RXBITCTR_INIT      (((7u * Rx_Bottom_OVER_SAMPLE_COUNT) - 1u) + \
                                                      Rx_Bottom_HALF_BIT_COUNT)
#endif /* End Rx_Bottom_OVER_SAMPLE_COUNT */

#define Rx_Bottom_HD_RXBITCTR_INIT                   Rx_Bottom_RXBITCTR_INIT


/***************************************
* Global variables external identifier
***************************************/

extern uint8 Rx_Bottom_initVar;
#if (Rx_Bottom_TX_INTERRUPT_ENABLED && Rx_Bottom_TX_ENABLED)
    extern volatile uint8 Rx_Bottom_txBuffer[Rx_Bottom_TX_BUFFER_SIZE];
    extern volatile uint8 Rx_Bottom_txBufferRead;
    extern uint8 Rx_Bottom_txBufferWrite;
#endif /* (Rx_Bottom_TX_INTERRUPT_ENABLED && Rx_Bottom_TX_ENABLED) */
#if (Rx_Bottom_RX_INTERRUPT_ENABLED && (Rx_Bottom_RX_ENABLED || Rx_Bottom_HD_ENABLED))
    extern uint8 Rx_Bottom_errorStatus;
    extern volatile uint8 Rx_Bottom_rxBuffer[Rx_Bottom_RX_BUFFER_SIZE];
    extern volatile uint8 Rx_Bottom_rxBufferRead;
    extern volatile uint8 Rx_Bottom_rxBufferWrite;
    extern volatile uint8 Rx_Bottom_rxBufferLoopDetect;
    extern volatile uint8 Rx_Bottom_rxBufferOverflow;
    #if (Rx_Bottom_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 Rx_Bottom_rxAddressMode;
        extern volatile uint8 Rx_Bottom_rxAddressDetected;
    #endif /* (Rx_Bottom_RXHW_ADDRESS_ENABLED) */
#endif /* (Rx_Bottom_RX_INTERRUPT_ENABLED && (Rx_Bottom_RX_ENABLED || Rx_Bottom_HD_ENABLED)) */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define Rx_Bottom__B_UART__AM_SW_BYTE_BYTE 1
#define Rx_Bottom__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define Rx_Bottom__B_UART__AM_HW_BYTE_BY_BYTE 3
#define Rx_Bottom__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define Rx_Bottom__B_UART__AM_NONE 0

#define Rx_Bottom__B_UART__NONE_REVB 0
#define Rx_Bottom__B_UART__EVEN_REVB 1
#define Rx_Bottom__B_UART__ODD_REVB 2
#define Rx_Bottom__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define Rx_Bottom_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define Rx_Bottom_NUMBER_OF_STOP_BITS    (1u)

#if (Rx_Bottom_RXHW_ADDRESS_ENABLED)
    #define Rx_Bottom_RX_ADDRESS_MODE    (0u)
    #define Rx_Bottom_RX_HW_ADDRESS1     (0u)
    #define Rx_Bottom_RX_HW_ADDRESS2     (0u)
#endif /* (Rx_Bottom_RXHW_ADDRESS_ENABLED) */

#define Rx_Bottom_INIT_RX_INTERRUPTS_MASK \
                                  (uint8)((1 << Rx_Bottom_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << Rx_Bottom_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << Rx_Bottom_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << Rx_Bottom_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << Rx_Bottom_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << Rx_Bottom_RX_STS_BREAK_SHIFT) \
                                        | (0 << Rx_Bottom_RX_STS_OVERRUN_SHIFT))

#define Rx_Bottom_INIT_TX_INTERRUPTS_MASK \
                                  (uint8)((0 << Rx_Bottom_TX_STS_COMPLETE_SHIFT) \
                                        | (0 << Rx_Bottom_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << Rx_Bottom_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << Rx_Bottom_TX_STS_FIFO_NOT_FULL_SHIFT))


/***************************************
*              Registers
***************************************/

#ifdef Rx_Bottom_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define Rx_Bottom_CONTROL_REG \
                            (* (reg8 *) Rx_Bottom_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
    #define Rx_Bottom_CONTROL_PTR \
                            (  (reg8 *) Rx_Bottom_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
#endif /* End Rx_Bottom_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(Rx_Bottom_TX_ENABLED)
    #define Rx_Bottom_TXDATA_REG          (* (reg8 *) Rx_Bottom_BUART_sTX_TxShifter_u0__F0_REG)
    #define Rx_Bottom_TXDATA_PTR          (  (reg8 *) Rx_Bottom_BUART_sTX_TxShifter_u0__F0_REG)
    #define Rx_Bottom_TXDATA_AUX_CTL_REG  (* (reg8 *) Rx_Bottom_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define Rx_Bottom_TXDATA_AUX_CTL_PTR  (  (reg8 *) Rx_Bottom_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define Rx_Bottom_TXSTATUS_REG        (* (reg8 *) Rx_Bottom_BUART_sTX_TxSts__STATUS_REG)
    #define Rx_Bottom_TXSTATUS_PTR        (  (reg8 *) Rx_Bottom_BUART_sTX_TxSts__STATUS_REG)
    #define Rx_Bottom_TXSTATUS_MASK_REG   (* (reg8 *) Rx_Bottom_BUART_sTX_TxSts__MASK_REG)
    #define Rx_Bottom_TXSTATUS_MASK_PTR   (  (reg8 *) Rx_Bottom_BUART_sTX_TxSts__MASK_REG)
    #define Rx_Bottom_TXSTATUS_ACTL_REG   (* (reg8 *) Rx_Bottom_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define Rx_Bottom_TXSTATUS_ACTL_PTR   (  (reg8 *) Rx_Bottom_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(Rx_Bottom_TXCLKGEN_DP)
        #define Rx_Bottom_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) Rx_Bottom_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define Rx_Bottom_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) Rx_Bottom_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define Rx_Bottom_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) Rx_Bottom_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define Rx_Bottom_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) Rx_Bottom_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define Rx_Bottom_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) Rx_Bottom_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define Rx_Bottom_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) Rx_Bottom_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define Rx_Bottom_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) Rx_Bottom_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define Rx_Bottom_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) Rx_Bottom_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define Rx_Bottom_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) Rx_Bottom_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define Rx_Bottom_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) Rx_Bottom_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* Rx_Bottom_TXCLKGEN_DP */

#endif /* End Rx_Bottom_TX_ENABLED */

#if(Rx_Bottom_HD_ENABLED)

    #define Rx_Bottom_TXDATA_REG             (* (reg8 *) Rx_Bottom_BUART_sRX_RxShifter_u0__F1_REG )
    #define Rx_Bottom_TXDATA_PTR             (  (reg8 *) Rx_Bottom_BUART_sRX_RxShifter_u0__F1_REG )
    #define Rx_Bottom_TXDATA_AUX_CTL_REG     (* (reg8 *) Rx_Bottom_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define Rx_Bottom_TXDATA_AUX_CTL_PTR     (  (reg8 *) Rx_Bottom_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define Rx_Bottom_TXSTATUS_REG           (* (reg8 *) Rx_Bottom_BUART_sRX_RxSts__STATUS_REG )
    #define Rx_Bottom_TXSTATUS_PTR           (  (reg8 *) Rx_Bottom_BUART_sRX_RxSts__STATUS_REG )
    #define Rx_Bottom_TXSTATUS_MASK_REG      (* (reg8 *) Rx_Bottom_BUART_sRX_RxSts__MASK_REG )
    #define Rx_Bottom_TXSTATUS_MASK_PTR      (  (reg8 *) Rx_Bottom_BUART_sRX_RxSts__MASK_REG )
    #define Rx_Bottom_TXSTATUS_ACTL_REG      (* (reg8 *) Rx_Bottom_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define Rx_Bottom_TXSTATUS_ACTL_PTR      (  (reg8 *) Rx_Bottom_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End Rx_Bottom_HD_ENABLED */

#if( (Rx_Bottom_RX_ENABLED) || (Rx_Bottom_HD_ENABLED) )
    #define Rx_Bottom_RXDATA_REG             (* (reg8 *) Rx_Bottom_BUART_sRX_RxShifter_u0__F0_REG )
    #define Rx_Bottom_RXDATA_PTR             (  (reg8 *) Rx_Bottom_BUART_sRX_RxShifter_u0__F0_REG )
    #define Rx_Bottom_RXADDRESS1_REG         (* (reg8 *) Rx_Bottom_BUART_sRX_RxShifter_u0__D0_REG )
    #define Rx_Bottom_RXADDRESS1_PTR         (  (reg8 *) Rx_Bottom_BUART_sRX_RxShifter_u0__D0_REG )
    #define Rx_Bottom_RXADDRESS2_REG         (* (reg8 *) Rx_Bottom_BUART_sRX_RxShifter_u0__D1_REG )
    #define Rx_Bottom_RXADDRESS2_PTR         (  (reg8 *) Rx_Bottom_BUART_sRX_RxShifter_u0__D1_REG )
    #define Rx_Bottom_RXDATA_AUX_CTL_REG     (* (reg8 *) Rx_Bottom_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define Rx_Bottom_RXBITCTR_PERIOD_REG    (* (reg8 *) Rx_Bottom_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define Rx_Bottom_RXBITCTR_PERIOD_PTR    (  (reg8 *) Rx_Bottom_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define Rx_Bottom_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) Rx_Bottom_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define Rx_Bottom_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) Rx_Bottom_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define Rx_Bottom_RXBITCTR_COUNTER_REG   (* (reg8 *) Rx_Bottom_BUART_sRX_RxBitCounter__COUNT_REG )
    #define Rx_Bottom_RXBITCTR_COUNTER_PTR   (  (reg8 *) Rx_Bottom_BUART_sRX_RxBitCounter__COUNT_REG )

    #define Rx_Bottom_RXSTATUS_REG           (* (reg8 *) Rx_Bottom_BUART_sRX_RxSts__STATUS_REG )
    #define Rx_Bottom_RXSTATUS_PTR           (  (reg8 *) Rx_Bottom_BUART_sRX_RxSts__STATUS_REG )
    #define Rx_Bottom_RXSTATUS_MASK_REG      (* (reg8 *) Rx_Bottom_BUART_sRX_RxSts__MASK_REG )
    #define Rx_Bottom_RXSTATUS_MASK_PTR      (  (reg8 *) Rx_Bottom_BUART_sRX_RxSts__MASK_REG )
    #define Rx_Bottom_RXSTATUS_ACTL_REG      (* (reg8 *) Rx_Bottom_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define Rx_Bottom_RXSTATUS_ACTL_PTR      (  (reg8 *) Rx_Bottom_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (Rx_Bottom_RX_ENABLED) || (Rx_Bottom_HD_ENABLED) */

#if(Rx_Bottom_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define Rx_Bottom_INTCLOCK_CLKEN_REG     (* (reg8 *) Rx_Bottom_IntClock__PM_ACT_CFG)
    #define Rx_Bottom_INTCLOCK_CLKEN_PTR     (  (reg8 *) Rx_Bottom_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define Rx_Bottom_INTCLOCK_CLKEN_MASK    Rx_Bottom_IntClock__PM_ACT_MSK
#endif /* End Rx_Bottom_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants
***************************************/

#if(Rx_Bottom_TX_ENABLED)
    #define Rx_Bottom_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End Rx_Bottom_TX_ENABLED */

#if(Rx_Bottom_HD_ENABLED)
    #define Rx_Bottom_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End Rx_Bottom_HD_ENABLED */

#if( (Rx_Bottom_RX_ENABLED) || (Rx_Bottom_HD_ENABLED) )
    #define Rx_Bottom_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (Rx_Bottom_RX_ENABLED) || (Rx_Bottom_HD_ENABLED) */


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

/* UART v2_40 obsolete definitions */
#define Rx_Bottom_TXBUFFERSIZE   Rx_Bottom_TX_BUFFER_SIZE
#define Rx_Bottom_RXBUFFERSIZE   Rx_Bottom_RX_BUFFER_SIZE

#if (Rx_Bottom_RXHW_ADDRESS_ENABLED)
    #define Rx_Bottom_RXADDRESSMODE  Rx_Bottom_RX_ADDRESS_MODE
    #define Rx_Bottom_RXHWADDRESS1   Rx_Bottom_RX_HW_ADDRESS1
    #define Rx_Bottom_RXHWADDRESS2   Rx_Bottom_RX_HW_ADDRESS2
    /* Backward compatible define */
    #define Rx_Bottom_RXAddressMode  Rx_Bottom_RXADDRESSMODE
#endif /* (Rx_Bottom_RXHW_ADDRESS_ENABLED) */

/* UART v2_30 obsolete definitions */
#define Rx_Bottom_initvar                    Rx_Bottom_initVar

#define Rx_Bottom_RX_Enabled                 Rx_Bottom_RX_ENABLED
#define Rx_Bottom_TX_Enabled                 Rx_Bottom_TX_ENABLED
#define Rx_Bottom_HD_Enabled                 Rx_Bottom_HD_ENABLED
#define Rx_Bottom_RX_IntInterruptEnabled     Rx_Bottom_RX_INTERRUPT_ENABLED
#define Rx_Bottom_TX_IntInterruptEnabled     Rx_Bottom_TX_INTERRUPT_ENABLED
#define Rx_Bottom_InternalClockUsed          Rx_Bottom_INTERNAL_CLOCK_USED
#define Rx_Bottom_RXHW_Address_Enabled       Rx_Bottom_RXHW_ADDRESS_ENABLED
#define Rx_Bottom_OverSampleCount            Rx_Bottom_OVER_SAMPLE_COUNT
#define Rx_Bottom_ParityType                 Rx_Bottom_PARITY_TYPE

#if( Rx_Bottom_TX_ENABLED && (Rx_Bottom_TXBUFFERSIZE > Rx_Bottom_FIFO_LENGTH))
    #define Rx_Bottom_TXBUFFER               Rx_Bottom_txBuffer
    #define Rx_Bottom_TXBUFFERREAD           Rx_Bottom_txBufferRead
    #define Rx_Bottom_TXBUFFERWRITE          Rx_Bottom_txBufferWrite
#endif /* End Rx_Bottom_TX_ENABLED */
#if( ( Rx_Bottom_RX_ENABLED || Rx_Bottom_HD_ENABLED ) && \
     (Rx_Bottom_RXBUFFERSIZE > Rx_Bottom_FIFO_LENGTH) )
    #define Rx_Bottom_RXBUFFER               Rx_Bottom_rxBuffer
    #define Rx_Bottom_RXBUFFERREAD           Rx_Bottom_rxBufferRead
    #define Rx_Bottom_RXBUFFERWRITE          Rx_Bottom_rxBufferWrite
    #define Rx_Bottom_RXBUFFERLOOPDETECT     Rx_Bottom_rxBufferLoopDetect
    #define Rx_Bottom_RXBUFFER_OVERFLOW      Rx_Bottom_rxBufferOverflow
#endif /* End Rx_Bottom_RX_ENABLED */

#ifdef Rx_Bottom_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define Rx_Bottom_CONTROL                Rx_Bottom_CONTROL_REG
#endif /* End Rx_Bottom_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(Rx_Bottom_TX_ENABLED)
    #define Rx_Bottom_TXDATA                 Rx_Bottom_TXDATA_REG
    #define Rx_Bottom_TXSTATUS               Rx_Bottom_TXSTATUS_REG
    #define Rx_Bottom_TXSTATUS_MASK          Rx_Bottom_TXSTATUS_MASK_REG
    #define Rx_Bottom_TXSTATUS_ACTL          Rx_Bottom_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(Rx_Bottom_TXCLKGEN_DP)
        #define Rx_Bottom_TXBITCLKGEN_CTR        Rx_Bottom_TXBITCLKGEN_CTR_REG
        #define Rx_Bottom_TXBITCLKTX_COMPLETE    Rx_Bottom_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define Rx_Bottom_TXBITCTR_PERIOD        Rx_Bottom_TXBITCTR_PERIOD_REG
        #define Rx_Bottom_TXBITCTR_CONTROL       Rx_Bottom_TXBITCTR_CONTROL_REG
        #define Rx_Bottom_TXBITCTR_COUNTER       Rx_Bottom_TXBITCTR_COUNTER_REG
    #endif /* Rx_Bottom_TXCLKGEN_DP */
#endif /* End Rx_Bottom_TX_ENABLED */

#if(Rx_Bottom_HD_ENABLED)
    #define Rx_Bottom_TXDATA                 Rx_Bottom_TXDATA_REG
    #define Rx_Bottom_TXSTATUS               Rx_Bottom_TXSTATUS_REG
    #define Rx_Bottom_TXSTATUS_MASK          Rx_Bottom_TXSTATUS_MASK_REG
    #define Rx_Bottom_TXSTATUS_ACTL          Rx_Bottom_TXSTATUS_ACTL_REG
#endif /* End Rx_Bottom_HD_ENABLED */

#if( (Rx_Bottom_RX_ENABLED) || (Rx_Bottom_HD_ENABLED) )
    #define Rx_Bottom_RXDATA                 Rx_Bottom_RXDATA_REG
    #define Rx_Bottom_RXADDRESS1             Rx_Bottom_RXADDRESS1_REG
    #define Rx_Bottom_RXADDRESS2             Rx_Bottom_RXADDRESS2_REG
    #define Rx_Bottom_RXBITCTR_PERIOD        Rx_Bottom_RXBITCTR_PERIOD_REG
    #define Rx_Bottom_RXBITCTR_CONTROL       Rx_Bottom_RXBITCTR_CONTROL_REG
    #define Rx_Bottom_RXBITCTR_COUNTER       Rx_Bottom_RXBITCTR_COUNTER_REG
    #define Rx_Bottom_RXSTATUS               Rx_Bottom_RXSTATUS_REG
    #define Rx_Bottom_RXSTATUS_MASK          Rx_Bottom_RXSTATUS_MASK_REG
    #define Rx_Bottom_RXSTATUS_ACTL          Rx_Bottom_RXSTATUS_ACTL_REG
#endif /* End  (Rx_Bottom_RX_ENABLED) || (Rx_Bottom_HD_ENABLED) */

#if(Rx_Bottom_INTERNAL_CLOCK_USED)
    #define Rx_Bottom_INTCLOCK_CLKEN         Rx_Bottom_INTCLOCK_CLKEN_REG
#endif /* End Rx_Bottom_INTERNAL_CLOCK_USED */

#define Rx_Bottom_WAIT_FOR_COMLETE_REINIT    Rx_Bottom_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_Rx_Bottom_H */


/* [] END OF FILE */
