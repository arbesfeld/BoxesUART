/*******************************************************************************
* File Name: UART_6.h
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


#if !defined(CY_UART_UART_6_H)
#define CY_UART_UART_6_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"


/***************************************
* Conditional Compilation Parameters
***************************************/

#define UART_6_RX_ENABLED                     (1u)
#define UART_6_TX_ENABLED                     (0u)
#define UART_6_HD_ENABLED                     (0u)
#define UART_6_RX_INTERRUPT_ENABLED           (0u)
#define UART_6_TX_INTERRUPT_ENABLED           (0u)
#define UART_6_INTERNAL_CLOCK_USED            (1u)
#define UART_6_RXHW_ADDRESS_ENABLED           (0u)
#define UART_6_OVER_SAMPLE_COUNT              (8u)
#define UART_6_PARITY_TYPE                    (0u)
#define UART_6_PARITY_TYPE_SW                 (0u)
#define UART_6_BREAK_DETECT                   (0u)
#define UART_6_BREAK_BITS_TX                  (13u)
#define UART_6_BREAK_BITS_RX                  (13u)
#define UART_6_TXCLKGEN_DP                    (1u)
#define UART_6_USE23POLLING                   (1u)
#define UART_6_FLOW_CONTROL                   (0u)
#define UART_6_CLK_FREQ                       (0u)
#define UART_6_TX_BUFFER_SIZE                 (4u)
#define UART_6_RX_BUFFER_SIZE                 (4u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component UART_v2_40 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#if defined(UART_6_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG)
    #define UART_6_CONTROL_REG_REMOVED            (0u)
#else
    #define UART_6_CONTROL_REG_REMOVED            (1u)
#endif /* End UART_6_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Structure Definition
***************************************/

/* Sleep Mode API Support */
typedef struct UART_6_backupStruct_
{
    uint8 enableState;

    #if(UART_6_CONTROL_REG_REMOVED == 0u)
        uint8 cr;
    #endif /* End UART_6_CONTROL_REG_REMOVED */

} UART_6_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void UART_6_Start(void) ;
void UART_6_Stop(void) ;
uint8 UART_6_ReadControlRegister(void) ;
void UART_6_WriteControlRegister(uint8 control) ;

void UART_6_Init(void) ;
void UART_6_Enable(void) ;
void UART_6_SaveConfig(void) ;
void UART_6_RestoreConfig(void) ;
void UART_6_Sleep(void) ;
void UART_6_Wakeup(void) ;

/* Only if RX is enabled */
#if( (UART_6_RX_ENABLED) || (UART_6_HD_ENABLED) )

    #if (UART_6_RX_INTERRUPT_ENABLED)
        #define UART_6_EnableRxInt()  CyIntEnable (UART_6_RX_VECT_NUM)
        #define UART_6_DisableRxInt() CyIntDisable(UART_6_RX_VECT_NUM)
        CY_ISR_PROTO(UART_6_RXISR);
    #endif /* UART_6_RX_INTERRUPT_ENABLED */

    void UART_6_SetRxAddressMode(uint8 addressMode)
                                                           ;
    void UART_6_SetRxAddress1(uint8 address) ;
    void UART_6_SetRxAddress2(uint8 address) ;

    void  UART_6_SetRxInterruptMode(uint8 intSrc) ;
    uint8 UART_6_ReadRxData(void) ;
    uint8 UART_6_ReadRxStatus(void) ;
    uint8 UART_6_GetChar(void) ;
    uint16 UART_6_GetByte(void) ;
    uint8 UART_6_GetRxBufferSize(void)
                                                            ;
    void UART_6_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define UART_6_GetRxInterruptSource   UART_6_ReadRxStatus

#endif /* End (UART_6_RX_ENABLED) || (UART_6_HD_ENABLED) */

/* Only if TX is enabled */
#if(UART_6_TX_ENABLED || UART_6_HD_ENABLED)

    #if(UART_6_TX_INTERRUPT_ENABLED)
        #define UART_6_EnableTxInt()  CyIntEnable (UART_6_TX_VECT_NUM)
        #define UART_6_DisableTxInt() CyIntDisable(UART_6_TX_VECT_NUM)
        #define UART_6_SetPendingTxInt() CyIntSetPending(UART_6_TX_VECT_NUM)
        #define UART_6_ClearPendingTxInt() CyIntClearPending(UART_6_TX_VECT_NUM)
        CY_ISR_PROTO(UART_6_TXISR);
    #endif /* UART_6_TX_INTERRUPT_ENABLED */

    void UART_6_SetTxInterruptMode(uint8 intSrc) ;
    void UART_6_WriteTxData(uint8 txDataByte) ;
    uint8 UART_6_ReadTxStatus(void) ;
    void UART_6_PutChar(uint8 txDataByte) ;
    void UART_6_PutString(const char8 string[]) ;
    void UART_6_PutArray(const uint8 string[], uint8 byteCount)
                                                            ;
    void UART_6_PutCRLF(uint8 txDataByte) ;
    void UART_6_ClearTxBuffer(void) ;
    void UART_6_SetTxAddressMode(uint8 addressMode) ;
    void UART_6_SendBreak(uint8 retMode) ;
    uint8 UART_6_GetTxBufferSize(void)
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define UART_6_PutStringConst         UART_6_PutString
    #define UART_6_PutArrayConst          UART_6_PutArray
    #define UART_6_GetTxInterruptSource   UART_6_ReadTxStatus

#endif /* End UART_6_TX_ENABLED || UART_6_HD_ENABLED */

#if(UART_6_HD_ENABLED)
    void UART_6_LoadRxConfig(void) ;
    void UART_6_LoadTxConfig(void) ;
#endif /* End UART_6_HD_ENABLED */


/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART_6) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    UART_6_CyBtldrCommStart(void) CYSMALL ;
    void    UART_6_CyBtldrCommStop(void) CYSMALL ;
    void    UART_6_CyBtldrCommReset(void) CYSMALL ;
    cystatus UART_6_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus UART_6_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART_6)
        #define CyBtldrCommStart    UART_6_CyBtldrCommStart
        #define CyBtldrCommStop     UART_6_CyBtldrCommStop
        #define CyBtldrCommReset    UART_6_CyBtldrCommReset
        #define CyBtldrCommWrite    UART_6_CyBtldrCommWrite
        #define CyBtldrCommRead     UART_6_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART_6) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define UART_6_BYTE2BYTE_TIME_OUT (25u)
    #define UART_6_PACKET_EOP         (0x17u) /* End of packet defined by bootloader */
    #define UART_6_WAIT_EOP_DELAY     (5u)    /* Additional 5ms to wait for End of packet */
    #define UART_6_WAIT_1_MS          (1u)    /* Time Out quantity equal 1mS */

#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define UART_6_SET_SPACE      (0x00u)
#define UART_6_SET_MARK       (0x01u)

/* Status Register definitions */
#if( (UART_6_TX_ENABLED) || (UART_6_HD_ENABLED) )
    #if(UART_6_TX_INTERRUPT_ENABLED)
        #define UART_6_TX_VECT_NUM            (uint8)UART_6_TXInternalInterrupt__INTC_NUMBER
        #define UART_6_TX_PRIOR_NUM           (uint8)UART_6_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* UART_6_TX_INTERRUPT_ENABLED */

    #define UART_6_TX_STS_COMPLETE_SHIFT          (0x00u)
    #define UART_6_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
    #define UART_6_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #if(UART_6_TX_ENABLED)
        #define UART_6_TX_STS_FIFO_FULL_SHIFT     (0x02u)
    #else /* (UART_6_HD_ENABLED) */
        #define UART_6_TX_STS_FIFO_FULL_SHIFT     (0x05u)  /* Needs MD=0 */
    #endif /* (UART_6_TX_ENABLED) */

    #define UART_6_TX_STS_COMPLETE            (uint8)(0x01u << UART_6_TX_STS_COMPLETE_SHIFT)
    #define UART_6_TX_STS_FIFO_EMPTY          (uint8)(0x01u << UART_6_TX_STS_FIFO_EMPTY_SHIFT)
    #define UART_6_TX_STS_FIFO_FULL           (uint8)(0x01u << UART_6_TX_STS_FIFO_FULL_SHIFT)
    #define UART_6_TX_STS_FIFO_NOT_FULL       (uint8)(0x01u << UART_6_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (UART_6_TX_ENABLED) || (UART_6_HD_ENABLED)*/

#if( (UART_6_RX_ENABLED) || (UART_6_HD_ENABLED) )
    #if(UART_6_RX_INTERRUPT_ENABLED)
        #define UART_6_RX_VECT_NUM            (uint8)UART_6_RXInternalInterrupt__INTC_NUMBER
        #define UART_6_RX_PRIOR_NUM           (uint8)UART_6_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* UART_6_RX_INTERRUPT_ENABLED */
    #define UART_6_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define UART_6_RX_STS_BREAK_SHIFT             (0x01u)
    #define UART_6_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define UART_6_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define UART_6_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define UART_6_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define UART_6_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define UART_6_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define UART_6_RX_STS_MRKSPC           (uint8)(0x01u << UART_6_RX_STS_MRKSPC_SHIFT)
    #define UART_6_RX_STS_BREAK            (uint8)(0x01u << UART_6_RX_STS_BREAK_SHIFT)
    #define UART_6_RX_STS_PAR_ERROR        (uint8)(0x01u << UART_6_RX_STS_PAR_ERROR_SHIFT)
    #define UART_6_RX_STS_STOP_ERROR       (uint8)(0x01u << UART_6_RX_STS_STOP_ERROR_SHIFT)
    #define UART_6_RX_STS_OVERRUN          (uint8)(0x01u << UART_6_RX_STS_OVERRUN_SHIFT)
    #define UART_6_RX_STS_FIFO_NOTEMPTY    (uint8)(0x01u << UART_6_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define UART_6_RX_STS_ADDR_MATCH       (uint8)(0x01u << UART_6_RX_STS_ADDR_MATCH_SHIFT)
    #define UART_6_RX_STS_SOFT_BUFF_OVER   (uint8)(0x01u << UART_6_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define UART_6_RX_HW_MASK                     (0x7Fu)
#endif /* End (UART_6_RX_ENABLED) || (UART_6_HD_ENABLED) */

/* Control Register definitions */
#define UART_6_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define UART_6_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define UART_6_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define UART_6_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define UART_6_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define UART_6_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define UART_6_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define UART_6_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define UART_6_CTRL_HD_SEND               (uint8)(0x01u << UART_6_CTRL_HD_SEND_SHIFT)
#define UART_6_CTRL_HD_SEND_BREAK         (uint8)(0x01u << UART_6_CTRL_HD_SEND_BREAK_SHIFT)
#define UART_6_CTRL_MARK                  (uint8)(0x01u << UART_6_CTRL_MARK_SHIFT)
#define UART_6_CTRL_PARITY_TYPE_MASK      (uint8)(0x03u << UART_6_CTRL_PARITY_TYPE0_SHIFT)
#define UART_6_CTRL_RXADDR_MODE_MASK      (uint8)(0x07u << UART_6_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define UART_6_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define UART_6_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define UART_6_SEND_BREAK                         (0x00u)
#define UART_6_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define UART_6_REINIT                             (0x02u)
#define UART_6_SEND_WAIT_REINIT                   (0x03u)

#define UART_6_OVER_SAMPLE_8                      (8u)
#define UART_6_OVER_SAMPLE_16                     (16u)

#define UART_6_BIT_CENTER                         (UART_6_OVER_SAMPLE_COUNT - 2u)

#define UART_6_FIFO_LENGTH                        (4u)
#define UART_6_NUMBER_OF_START_BIT                (1u)
#define UART_6_MAX_BYTE_VALUE                     (0xFFu)

/* 8X always for count7 implementation */
#define UART_6_TXBITCTR_BREAKBITS8X   ((UART_6_BREAK_BITS_TX * UART_6_OVER_SAMPLE_8) - 1u)
/* 8X or 16X for DP implementation */
#define UART_6_TXBITCTR_BREAKBITS ((UART_6_BREAK_BITS_TX * UART_6_OVER_SAMPLE_COUNT) - 1u)

#define UART_6_HALF_BIT_COUNT   \
                            (((UART_6_OVER_SAMPLE_COUNT / 2u) + (UART_6_USE23POLLING * 1u)) - 2u)
#if (UART_6_OVER_SAMPLE_COUNT == UART_6_OVER_SAMPLE_8)
    #define UART_6_HD_TXBITCTR_INIT   (((UART_6_BREAK_BITS_TX + \
                            UART_6_NUMBER_OF_START_BIT) * UART_6_OVER_SAMPLE_COUNT) - 1u)

    /* This parameter is increased on the 2 in 2 out of 3 mode to sample voting in the middle */
    #define UART_6_RXBITCTR_INIT  ((((UART_6_BREAK_BITS_RX + UART_6_NUMBER_OF_START_BIT) \
                            * UART_6_OVER_SAMPLE_COUNT) + UART_6_HALF_BIT_COUNT) - 1u)

#else /* UART_6_OVER_SAMPLE_COUNT == UART_6_OVER_SAMPLE_16 */
    #define UART_6_HD_TXBITCTR_INIT   ((8u * UART_6_OVER_SAMPLE_COUNT) - 1u)
    /* 7bit counter need one more bit for OverSampleCount = 16 */
    #define UART_6_RXBITCTR_INIT      (((7u * UART_6_OVER_SAMPLE_COUNT) - 1u) + \
                                                      UART_6_HALF_BIT_COUNT)
#endif /* End UART_6_OVER_SAMPLE_COUNT */

#define UART_6_HD_RXBITCTR_INIT                   UART_6_RXBITCTR_INIT


/***************************************
* Global variables external identifier
***************************************/

extern uint8 UART_6_initVar;
#if (UART_6_TX_INTERRUPT_ENABLED && UART_6_TX_ENABLED)
    extern volatile uint8 UART_6_txBuffer[UART_6_TX_BUFFER_SIZE];
    extern volatile uint8 UART_6_txBufferRead;
    extern uint8 UART_6_txBufferWrite;
#endif /* (UART_6_TX_INTERRUPT_ENABLED && UART_6_TX_ENABLED) */
#if (UART_6_RX_INTERRUPT_ENABLED && (UART_6_RX_ENABLED || UART_6_HD_ENABLED))
    extern uint8 UART_6_errorStatus;
    extern volatile uint8 UART_6_rxBuffer[UART_6_RX_BUFFER_SIZE];
    extern volatile uint8 UART_6_rxBufferRead;
    extern volatile uint8 UART_6_rxBufferWrite;
    extern volatile uint8 UART_6_rxBufferLoopDetect;
    extern volatile uint8 UART_6_rxBufferOverflow;
    #if (UART_6_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 UART_6_rxAddressMode;
        extern volatile uint8 UART_6_rxAddressDetected;
    #endif /* (UART_6_RXHW_ADDRESS_ENABLED) */
#endif /* (UART_6_RX_INTERRUPT_ENABLED && (UART_6_RX_ENABLED || UART_6_HD_ENABLED)) */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define UART_6__B_UART__AM_SW_BYTE_BYTE 1
#define UART_6__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define UART_6__B_UART__AM_HW_BYTE_BY_BYTE 3
#define UART_6__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define UART_6__B_UART__AM_NONE 0

#define UART_6__B_UART__NONE_REVB 0
#define UART_6__B_UART__EVEN_REVB 1
#define UART_6__B_UART__ODD_REVB 2
#define UART_6__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define UART_6_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define UART_6_NUMBER_OF_STOP_BITS    (1u)

#if (UART_6_RXHW_ADDRESS_ENABLED)
    #define UART_6_RX_ADDRESS_MODE    (0u)
    #define UART_6_RX_HW_ADDRESS1     (0u)
    #define UART_6_RX_HW_ADDRESS2     (0u)
#endif /* (UART_6_RXHW_ADDRESS_ENABLED) */

#define UART_6_INIT_RX_INTERRUPTS_MASK \
                                  (uint8)((1 << UART_6_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << UART_6_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << UART_6_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << UART_6_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << UART_6_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << UART_6_RX_STS_BREAK_SHIFT) \
                                        | (0 << UART_6_RX_STS_OVERRUN_SHIFT))

#define UART_6_INIT_TX_INTERRUPTS_MASK \
                                  (uint8)((0 << UART_6_TX_STS_COMPLETE_SHIFT) \
                                        | (0 << UART_6_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << UART_6_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << UART_6_TX_STS_FIFO_NOT_FULL_SHIFT))


/***************************************
*              Registers
***************************************/

#ifdef UART_6_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define UART_6_CONTROL_REG \
                            (* (reg8 *) UART_6_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
    #define UART_6_CONTROL_PTR \
                            (  (reg8 *) UART_6_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
#endif /* End UART_6_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(UART_6_TX_ENABLED)
    #define UART_6_TXDATA_REG          (* (reg8 *) UART_6_BUART_sTX_TxShifter_u0__F0_REG)
    #define UART_6_TXDATA_PTR          (  (reg8 *) UART_6_BUART_sTX_TxShifter_u0__F0_REG)
    #define UART_6_TXDATA_AUX_CTL_REG  (* (reg8 *) UART_6_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define UART_6_TXDATA_AUX_CTL_PTR  (  (reg8 *) UART_6_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define UART_6_TXSTATUS_REG        (* (reg8 *) UART_6_BUART_sTX_TxSts__STATUS_REG)
    #define UART_6_TXSTATUS_PTR        (  (reg8 *) UART_6_BUART_sTX_TxSts__STATUS_REG)
    #define UART_6_TXSTATUS_MASK_REG   (* (reg8 *) UART_6_BUART_sTX_TxSts__MASK_REG)
    #define UART_6_TXSTATUS_MASK_PTR   (  (reg8 *) UART_6_BUART_sTX_TxSts__MASK_REG)
    #define UART_6_TXSTATUS_ACTL_REG   (* (reg8 *) UART_6_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define UART_6_TXSTATUS_ACTL_PTR   (  (reg8 *) UART_6_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(UART_6_TXCLKGEN_DP)
        #define UART_6_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) UART_6_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define UART_6_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) UART_6_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define UART_6_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) UART_6_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define UART_6_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) UART_6_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define UART_6_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) UART_6_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define UART_6_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) UART_6_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define UART_6_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) UART_6_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define UART_6_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) UART_6_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define UART_6_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) UART_6_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define UART_6_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) UART_6_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* UART_6_TXCLKGEN_DP */

#endif /* End UART_6_TX_ENABLED */

#if(UART_6_HD_ENABLED)

    #define UART_6_TXDATA_REG             (* (reg8 *) UART_6_BUART_sRX_RxShifter_u0__F1_REG )
    #define UART_6_TXDATA_PTR             (  (reg8 *) UART_6_BUART_sRX_RxShifter_u0__F1_REG )
    #define UART_6_TXDATA_AUX_CTL_REG     (* (reg8 *) UART_6_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define UART_6_TXDATA_AUX_CTL_PTR     (  (reg8 *) UART_6_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define UART_6_TXSTATUS_REG           (* (reg8 *) UART_6_BUART_sRX_RxSts__STATUS_REG )
    #define UART_6_TXSTATUS_PTR           (  (reg8 *) UART_6_BUART_sRX_RxSts__STATUS_REG )
    #define UART_6_TXSTATUS_MASK_REG      (* (reg8 *) UART_6_BUART_sRX_RxSts__MASK_REG )
    #define UART_6_TXSTATUS_MASK_PTR      (  (reg8 *) UART_6_BUART_sRX_RxSts__MASK_REG )
    #define UART_6_TXSTATUS_ACTL_REG      (* (reg8 *) UART_6_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define UART_6_TXSTATUS_ACTL_PTR      (  (reg8 *) UART_6_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End UART_6_HD_ENABLED */

#if( (UART_6_RX_ENABLED) || (UART_6_HD_ENABLED) )
    #define UART_6_RXDATA_REG             (* (reg8 *) UART_6_BUART_sRX_RxShifter_u0__F0_REG )
    #define UART_6_RXDATA_PTR             (  (reg8 *) UART_6_BUART_sRX_RxShifter_u0__F0_REG )
    #define UART_6_RXADDRESS1_REG         (* (reg8 *) UART_6_BUART_sRX_RxShifter_u0__D0_REG )
    #define UART_6_RXADDRESS1_PTR         (  (reg8 *) UART_6_BUART_sRX_RxShifter_u0__D0_REG )
    #define UART_6_RXADDRESS2_REG         (* (reg8 *) UART_6_BUART_sRX_RxShifter_u0__D1_REG )
    #define UART_6_RXADDRESS2_PTR         (  (reg8 *) UART_6_BUART_sRX_RxShifter_u0__D1_REG )
    #define UART_6_RXDATA_AUX_CTL_REG     (* (reg8 *) UART_6_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define UART_6_RXBITCTR_PERIOD_REG    (* (reg8 *) UART_6_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define UART_6_RXBITCTR_PERIOD_PTR    (  (reg8 *) UART_6_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define UART_6_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) UART_6_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define UART_6_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) UART_6_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define UART_6_RXBITCTR_COUNTER_REG   (* (reg8 *) UART_6_BUART_sRX_RxBitCounter__COUNT_REG )
    #define UART_6_RXBITCTR_COUNTER_PTR   (  (reg8 *) UART_6_BUART_sRX_RxBitCounter__COUNT_REG )

    #define UART_6_RXSTATUS_REG           (* (reg8 *) UART_6_BUART_sRX_RxSts__STATUS_REG )
    #define UART_6_RXSTATUS_PTR           (  (reg8 *) UART_6_BUART_sRX_RxSts__STATUS_REG )
    #define UART_6_RXSTATUS_MASK_REG      (* (reg8 *) UART_6_BUART_sRX_RxSts__MASK_REG )
    #define UART_6_RXSTATUS_MASK_PTR      (  (reg8 *) UART_6_BUART_sRX_RxSts__MASK_REG )
    #define UART_6_RXSTATUS_ACTL_REG      (* (reg8 *) UART_6_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define UART_6_RXSTATUS_ACTL_PTR      (  (reg8 *) UART_6_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (UART_6_RX_ENABLED) || (UART_6_HD_ENABLED) */

#if(UART_6_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define UART_6_INTCLOCK_CLKEN_REG     (* (reg8 *) UART_6_IntClock__PM_ACT_CFG)
    #define UART_6_INTCLOCK_CLKEN_PTR     (  (reg8 *) UART_6_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define UART_6_INTCLOCK_CLKEN_MASK    UART_6_IntClock__PM_ACT_MSK
#endif /* End UART_6_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants
***************************************/

#if(UART_6_TX_ENABLED)
    #define UART_6_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End UART_6_TX_ENABLED */

#if(UART_6_HD_ENABLED)
    #define UART_6_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End UART_6_HD_ENABLED */

#if( (UART_6_RX_ENABLED) || (UART_6_HD_ENABLED) )
    #define UART_6_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (UART_6_RX_ENABLED) || (UART_6_HD_ENABLED) */


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

/* UART v2_40 obsolete definitions */
#define UART_6_TXBUFFERSIZE   UART_6_TX_BUFFER_SIZE
#define UART_6_RXBUFFERSIZE   UART_6_RX_BUFFER_SIZE

#if (UART_6_RXHW_ADDRESS_ENABLED)
    #define UART_6_RXADDRESSMODE  UART_6_RX_ADDRESS_MODE
    #define UART_6_RXHWADDRESS1   UART_6_RX_HW_ADDRESS1
    #define UART_6_RXHWADDRESS2   UART_6_RX_HW_ADDRESS2
    /* Backward compatible define */
    #define UART_6_RXAddressMode  UART_6_RXADDRESSMODE
#endif /* (UART_6_RXHW_ADDRESS_ENABLED) */

/* UART v2_30 obsolete definitions */
#define UART_6_initvar                    UART_6_initVar

#define UART_6_RX_Enabled                 UART_6_RX_ENABLED
#define UART_6_TX_Enabled                 UART_6_TX_ENABLED
#define UART_6_HD_Enabled                 UART_6_HD_ENABLED
#define UART_6_RX_IntInterruptEnabled     UART_6_RX_INTERRUPT_ENABLED
#define UART_6_TX_IntInterruptEnabled     UART_6_TX_INTERRUPT_ENABLED
#define UART_6_InternalClockUsed          UART_6_INTERNAL_CLOCK_USED
#define UART_6_RXHW_Address_Enabled       UART_6_RXHW_ADDRESS_ENABLED
#define UART_6_OverSampleCount            UART_6_OVER_SAMPLE_COUNT
#define UART_6_ParityType                 UART_6_PARITY_TYPE

#if( UART_6_TX_ENABLED && (UART_6_TXBUFFERSIZE > UART_6_FIFO_LENGTH))
    #define UART_6_TXBUFFER               UART_6_txBuffer
    #define UART_6_TXBUFFERREAD           UART_6_txBufferRead
    #define UART_6_TXBUFFERWRITE          UART_6_txBufferWrite
#endif /* End UART_6_TX_ENABLED */
#if( ( UART_6_RX_ENABLED || UART_6_HD_ENABLED ) && \
     (UART_6_RXBUFFERSIZE > UART_6_FIFO_LENGTH) )
    #define UART_6_RXBUFFER               UART_6_rxBuffer
    #define UART_6_RXBUFFERREAD           UART_6_rxBufferRead
    #define UART_6_RXBUFFERWRITE          UART_6_rxBufferWrite
    #define UART_6_RXBUFFERLOOPDETECT     UART_6_rxBufferLoopDetect
    #define UART_6_RXBUFFER_OVERFLOW      UART_6_rxBufferOverflow
#endif /* End UART_6_RX_ENABLED */

#ifdef UART_6_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define UART_6_CONTROL                UART_6_CONTROL_REG
#endif /* End UART_6_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(UART_6_TX_ENABLED)
    #define UART_6_TXDATA                 UART_6_TXDATA_REG
    #define UART_6_TXSTATUS               UART_6_TXSTATUS_REG
    #define UART_6_TXSTATUS_MASK          UART_6_TXSTATUS_MASK_REG
    #define UART_6_TXSTATUS_ACTL          UART_6_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(UART_6_TXCLKGEN_DP)
        #define UART_6_TXBITCLKGEN_CTR        UART_6_TXBITCLKGEN_CTR_REG
        #define UART_6_TXBITCLKTX_COMPLETE    UART_6_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define UART_6_TXBITCTR_PERIOD        UART_6_TXBITCTR_PERIOD_REG
        #define UART_6_TXBITCTR_CONTROL       UART_6_TXBITCTR_CONTROL_REG
        #define UART_6_TXBITCTR_COUNTER       UART_6_TXBITCTR_COUNTER_REG
    #endif /* UART_6_TXCLKGEN_DP */
#endif /* End UART_6_TX_ENABLED */

#if(UART_6_HD_ENABLED)
    #define UART_6_TXDATA                 UART_6_TXDATA_REG
    #define UART_6_TXSTATUS               UART_6_TXSTATUS_REG
    #define UART_6_TXSTATUS_MASK          UART_6_TXSTATUS_MASK_REG
    #define UART_6_TXSTATUS_ACTL          UART_6_TXSTATUS_ACTL_REG
#endif /* End UART_6_HD_ENABLED */

#if( (UART_6_RX_ENABLED) || (UART_6_HD_ENABLED) )
    #define UART_6_RXDATA                 UART_6_RXDATA_REG
    #define UART_6_RXADDRESS1             UART_6_RXADDRESS1_REG
    #define UART_6_RXADDRESS2             UART_6_RXADDRESS2_REG
    #define UART_6_RXBITCTR_PERIOD        UART_6_RXBITCTR_PERIOD_REG
    #define UART_6_RXBITCTR_CONTROL       UART_6_RXBITCTR_CONTROL_REG
    #define UART_6_RXBITCTR_COUNTER       UART_6_RXBITCTR_COUNTER_REG
    #define UART_6_RXSTATUS               UART_6_RXSTATUS_REG
    #define UART_6_RXSTATUS_MASK          UART_6_RXSTATUS_MASK_REG
    #define UART_6_RXSTATUS_ACTL          UART_6_RXSTATUS_ACTL_REG
#endif /* End  (UART_6_RX_ENABLED) || (UART_6_HD_ENABLED) */

#if(UART_6_INTERNAL_CLOCK_USED)
    #define UART_6_INTCLOCK_CLKEN         UART_6_INTCLOCK_CLKEN_REG
#endif /* End UART_6_INTERNAL_CLOCK_USED */

#define UART_6_WAIT_FOR_COMLETE_REINIT    UART_6_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_UART_6_H */


/* [] END OF FILE */
