/*******************************************************************************
* File Name: UART_4.h
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


#if !defined(CY_UART_UART_4_H)
#define CY_UART_UART_4_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"


/***************************************
* Conditional Compilation Parameters
***************************************/

#define UART_4_RX_ENABLED                     (1u)
#define UART_4_TX_ENABLED                     (0u)
#define UART_4_HD_ENABLED                     (0u)
#define UART_4_RX_INTERRUPT_ENABLED           (0u)
#define UART_4_TX_INTERRUPT_ENABLED           (0u)
#define UART_4_INTERNAL_CLOCK_USED            (1u)
#define UART_4_RXHW_ADDRESS_ENABLED           (0u)
#define UART_4_OVER_SAMPLE_COUNT              (8u)
#define UART_4_PARITY_TYPE                    (0u)
#define UART_4_PARITY_TYPE_SW                 (0u)
#define UART_4_BREAK_DETECT                   (0u)
#define UART_4_BREAK_BITS_TX                  (13u)
#define UART_4_BREAK_BITS_RX                  (13u)
#define UART_4_TXCLKGEN_DP                    (1u)
#define UART_4_USE23POLLING                   (1u)
#define UART_4_FLOW_CONTROL                   (0u)
#define UART_4_CLK_FREQ                       (0u)
#define UART_4_TX_BUFFER_SIZE                 (4u)
#define UART_4_RX_BUFFER_SIZE                 (4u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component UART_v2_40 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#if defined(UART_4_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG)
    #define UART_4_CONTROL_REG_REMOVED            (0u)
#else
    #define UART_4_CONTROL_REG_REMOVED            (1u)
#endif /* End UART_4_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Structure Definition
***************************************/

/* Sleep Mode API Support */
typedef struct UART_4_backupStruct_
{
    uint8 enableState;

    #if(UART_4_CONTROL_REG_REMOVED == 0u)
        uint8 cr;
    #endif /* End UART_4_CONTROL_REG_REMOVED */

} UART_4_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void UART_4_Start(void) ;
void UART_4_Stop(void) ;
uint8 UART_4_ReadControlRegister(void) ;
void UART_4_WriteControlRegister(uint8 control) ;

void UART_4_Init(void) ;
void UART_4_Enable(void) ;
void UART_4_SaveConfig(void) ;
void UART_4_RestoreConfig(void) ;
void UART_4_Sleep(void) ;
void UART_4_Wakeup(void) ;

/* Only if RX is enabled */
#if( (UART_4_RX_ENABLED) || (UART_4_HD_ENABLED) )

    #if (UART_4_RX_INTERRUPT_ENABLED)
        #define UART_4_EnableRxInt()  CyIntEnable (UART_4_RX_VECT_NUM)
        #define UART_4_DisableRxInt() CyIntDisable(UART_4_RX_VECT_NUM)
        CY_ISR_PROTO(UART_4_RXISR);
    #endif /* UART_4_RX_INTERRUPT_ENABLED */

    void UART_4_SetRxAddressMode(uint8 addressMode)
                                                           ;
    void UART_4_SetRxAddress1(uint8 address) ;
    void UART_4_SetRxAddress2(uint8 address) ;

    void  UART_4_SetRxInterruptMode(uint8 intSrc) ;
    uint8 UART_4_ReadRxData(void) ;
    uint8 UART_4_ReadRxStatus(void) ;
    uint8 UART_4_GetChar(void) ;
    uint16 UART_4_GetByte(void) ;
    uint8 UART_4_GetRxBufferSize(void)
                                                            ;
    void UART_4_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define UART_4_GetRxInterruptSource   UART_4_ReadRxStatus

#endif /* End (UART_4_RX_ENABLED) || (UART_4_HD_ENABLED) */

/* Only if TX is enabled */
#if(UART_4_TX_ENABLED || UART_4_HD_ENABLED)

    #if(UART_4_TX_INTERRUPT_ENABLED)
        #define UART_4_EnableTxInt()  CyIntEnable (UART_4_TX_VECT_NUM)
        #define UART_4_DisableTxInt() CyIntDisable(UART_4_TX_VECT_NUM)
        #define UART_4_SetPendingTxInt() CyIntSetPending(UART_4_TX_VECT_NUM)
        #define UART_4_ClearPendingTxInt() CyIntClearPending(UART_4_TX_VECT_NUM)
        CY_ISR_PROTO(UART_4_TXISR);
    #endif /* UART_4_TX_INTERRUPT_ENABLED */

    void UART_4_SetTxInterruptMode(uint8 intSrc) ;
    void UART_4_WriteTxData(uint8 txDataByte) ;
    uint8 UART_4_ReadTxStatus(void) ;
    void UART_4_PutChar(uint8 txDataByte) ;
    void UART_4_PutString(const char8 string[]) ;
    void UART_4_PutArray(const uint8 string[], uint8 byteCount)
                                                            ;
    void UART_4_PutCRLF(uint8 txDataByte) ;
    void UART_4_ClearTxBuffer(void) ;
    void UART_4_SetTxAddressMode(uint8 addressMode) ;
    void UART_4_SendBreak(uint8 retMode) ;
    uint8 UART_4_GetTxBufferSize(void)
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define UART_4_PutStringConst         UART_4_PutString
    #define UART_4_PutArrayConst          UART_4_PutArray
    #define UART_4_GetTxInterruptSource   UART_4_ReadTxStatus

#endif /* End UART_4_TX_ENABLED || UART_4_HD_ENABLED */

#if(UART_4_HD_ENABLED)
    void UART_4_LoadRxConfig(void) ;
    void UART_4_LoadTxConfig(void) ;
#endif /* End UART_4_HD_ENABLED */


/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART_4) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    UART_4_CyBtldrCommStart(void) CYSMALL ;
    void    UART_4_CyBtldrCommStop(void) CYSMALL ;
    void    UART_4_CyBtldrCommReset(void) CYSMALL ;
    cystatus UART_4_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus UART_4_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART_4)
        #define CyBtldrCommStart    UART_4_CyBtldrCommStart
        #define CyBtldrCommStop     UART_4_CyBtldrCommStop
        #define CyBtldrCommReset    UART_4_CyBtldrCommReset
        #define CyBtldrCommWrite    UART_4_CyBtldrCommWrite
        #define CyBtldrCommRead     UART_4_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART_4) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define UART_4_BYTE2BYTE_TIME_OUT (25u)
    #define UART_4_PACKET_EOP         (0x17u) /* End of packet defined by bootloader */
    #define UART_4_WAIT_EOP_DELAY     (5u)    /* Additional 5ms to wait for End of packet */
    #define UART_4_WAIT_1_MS          (1u)    /* Time Out quantity equal 1mS */

#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define UART_4_SET_SPACE      (0x00u)
#define UART_4_SET_MARK       (0x01u)

/* Status Register definitions */
#if( (UART_4_TX_ENABLED) || (UART_4_HD_ENABLED) )
    #if(UART_4_TX_INTERRUPT_ENABLED)
        #define UART_4_TX_VECT_NUM            (uint8)UART_4_TXInternalInterrupt__INTC_NUMBER
        #define UART_4_TX_PRIOR_NUM           (uint8)UART_4_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* UART_4_TX_INTERRUPT_ENABLED */

    #define UART_4_TX_STS_COMPLETE_SHIFT          (0x00u)
    #define UART_4_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
    #define UART_4_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #if(UART_4_TX_ENABLED)
        #define UART_4_TX_STS_FIFO_FULL_SHIFT     (0x02u)
    #else /* (UART_4_HD_ENABLED) */
        #define UART_4_TX_STS_FIFO_FULL_SHIFT     (0x05u)  /* Needs MD=0 */
    #endif /* (UART_4_TX_ENABLED) */

    #define UART_4_TX_STS_COMPLETE            (uint8)(0x01u << UART_4_TX_STS_COMPLETE_SHIFT)
    #define UART_4_TX_STS_FIFO_EMPTY          (uint8)(0x01u << UART_4_TX_STS_FIFO_EMPTY_SHIFT)
    #define UART_4_TX_STS_FIFO_FULL           (uint8)(0x01u << UART_4_TX_STS_FIFO_FULL_SHIFT)
    #define UART_4_TX_STS_FIFO_NOT_FULL       (uint8)(0x01u << UART_4_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (UART_4_TX_ENABLED) || (UART_4_HD_ENABLED)*/

#if( (UART_4_RX_ENABLED) || (UART_4_HD_ENABLED) )
    #if(UART_4_RX_INTERRUPT_ENABLED)
        #define UART_4_RX_VECT_NUM            (uint8)UART_4_RXInternalInterrupt__INTC_NUMBER
        #define UART_4_RX_PRIOR_NUM           (uint8)UART_4_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* UART_4_RX_INTERRUPT_ENABLED */
    #define UART_4_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define UART_4_RX_STS_BREAK_SHIFT             (0x01u)
    #define UART_4_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define UART_4_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define UART_4_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define UART_4_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define UART_4_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define UART_4_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define UART_4_RX_STS_MRKSPC           (uint8)(0x01u << UART_4_RX_STS_MRKSPC_SHIFT)
    #define UART_4_RX_STS_BREAK            (uint8)(0x01u << UART_4_RX_STS_BREAK_SHIFT)
    #define UART_4_RX_STS_PAR_ERROR        (uint8)(0x01u << UART_4_RX_STS_PAR_ERROR_SHIFT)
    #define UART_4_RX_STS_STOP_ERROR       (uint8)(0x01u << UART_4_RX_STS_STOP_ERROR_SHIFT)
    #define UART_4_RX_STS_OVERRUN          (uint8)(0x01u << UART_4_RX_STS_OVERRUN_SHIFT)
    #define UART_4_RX_STS_FIFO_NOTEMPTY    (uint8)(0x01u << UART_4_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define UART_4_RX_STS_ADDR_MATCH       (uint8)(0x01u << UART_4_RX_STS_ADDR_MATCH_SHIFT)
    #define UART_4_RX_STS_SOFT_BUFF_OVER   (uint8)(0x01u << UART_4_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define UART_4_RX_HW_MASK                     (0x7Fu)
#endif /* End (UART_4_RX_ENABLED) || (UART_4_HD_ENABLED) */

/* Control Register definitions */
#define UART_4_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define UART_4_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define UART_4_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define UART_4_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define UART_4_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define UART_4_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define UART_4_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define UART_4_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define UART_4_CTRL_HD_SEND               (uint8)(0x01u << UART_4_CTRL_HD_SEND_SHIFT)
#define UART_4_CTRL_HD_SEND_BREAK         (uint8)(0x01u << UART_4_CTRL_HD_SEND_BREAK_SHIFT)
#define UART_4_CTRL_MARK                  (uint8)(0x01u << UART_4_CTRL_MARK_SHIFT)
#define UART_4_CTRL_PARITY_TYPE_MASK      (uint8)(0x03u << UART_4_CTRL_PARITY_TYPE0_SHIFT)
#define UART_4_CTRL_RXADDR_MODE_MASK      (uint8)(0x07u << UART_4_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define UART_4_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define UART_4_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define UART_4_SEND_BREAK                         (0x00u)
#define UART_4_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define UART_4_REINIT                             (0x02u)
#define UART_4_SEND_WAIT_REINIT                   (0x03u)

#define UART_4_OVER_SAMPLE_8                      (8u)
#define UART_4_OVER_SAMPLE_16                     (16u)

#define UART_4_BIT_CENTER                         (UART_4_OVER_SAMPLE_COUNT - 2u)

#define UART_4_FIFO_LENGTH                        (4u)
#define UART_4_NUMBER_OF_START_BIT                (1u)
#define UART_4_MAX_BYTE_VALUE                     (0xFFu)

/* 8X always for count7 implementation */
#define UART_4_TXBITCTR_BREAKBITS8X   ((UART_4_BREAK_BITS_TX * UART_4_OVER_SAMPLE_8) - 1u)
/* 8X or 16X for DP implementation */
#define UART_4_TXBITCTR_BREAKBITS ((UART_4_BREAK_BITS_TX * UART_4_OVER_SAMPLE_COUNT) - 1u)

#define UART_4_HALF_BIT_COUNT   \
                            (((UART_4_OVER_SAMPLE_COUNT / 2u) + (UART_4_USE23POLLING * 1u)) - 2u)
#if (UART_4_OVER_SAMPLE_COUNT == UART_4_OVER_SAMPLE_8)
    #define UART_4_HD_TXBITCTR_INIT   (((UART_4_BREAK_BITS_TX + \
                            UART_4_NUMBER_OF_START_BIT) * UART_4_OVER_SAMPLE_COUNT) - 1u)

    /* This parameter is increased on the 2 in 2 out of 3 mode to sample voting in the middle */
    #define UART_4_RXBITCTR_INIT  ((((UART_4_BREAK_BITS_RX + UART_4_NUMBER_OF_START_BIT) \
                            * UART_4_OVER_SAMPLE_COUNT) + UART_4_HALF_BIT_COUNT) - 1u)

#else /* UART_4_OVER_SAMPLE_COUNT == UART_4_OVER_SAMPLE_16 */
    #define UART_4_HD_TXBITCTR_INIT   ((8u * UART_4_OVER_SAMPLE_COUNT) - 1u)
    /* 7bit counter need one more bit for OverSampleCount = 16 */
    #define UART_4_RXBITCTR_INIT      (((7u * UART_4_OVER_SAMPLE_COUNT) - 1u) + \
                                                      UART_4_HALF_BIT_COUNT)
#endif /* End UART_4_OVER_SAMPLE_COUNT */

#define UART_4_HD_RXBITCTR_INIT                   UART_4_RXBITCTR_INIT


/***************************************
* Global variables external identifier
***************************************/

extern uint8 UART_4_initVar;
#if (UART_4_TX_INTERRUPT_ENABLED && UART_4_TX_ENABLED)
    extern volatile uint8 UART_4_txBuffer[UART_4_TX_BUFFER_SIZE];
    extern volatile uint8 UART_4_txBufferRead;
    extern uint8 UART_4_txBufferWrite;
#endif /* (UART_4_TX_INTERRUPT_ENABLED && UART_4_TX_ENABLED) */
#if (UART_4_RX_INTERRUPT_ENABLED && (UART_4_RX_ENABLED || UART_4_HD_ENABLED))
    extern uint8 UART_4_errorStatus;
    extern volatile uint8 UART_4_rxBuffer[UART_4_RX_BUFFER_SIZE];
    extern volatile uint8 UART_4_rxBufferRead;
    extern volatile uint8 UART_4_rxBufferWrite;
    extern volatile uint8 UART_4_rxBufferLoopDetect;
    extern volatile uint8 UART_4_rxBufferOverflow;
    #if (UART_4_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 UART_4_rxAddressMode;
        extern volatile uint8 UART_4_rxAddressDetected;
    #endif /* (UART_4_RXHW_ADDRESS_ENABLED) */
#endif /* (UART_4_RX_INTERRUPT_ENABLED && (UART_4_RX_ENABLED || UART_4_HD_ENABLED)) */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define UART_4__B_UART__AM_SW_BYTE_BYTE 1
#define UART_4__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define UART_4__B_UART__AM_HW_BYTE_BY_BYTE 3
#define UART_4__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define UART_4__B_UART__AM_NONE 0

#define UART_4__B_UART__NONE_REVB 0
#define UART_4__B_UART__EVEN_REVB 1
#define UART_4__B_UART__ODD_REVB 2
#define UART_4__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define UART_4_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define UART_4_NUMBER_OF_STOP_BITS    (1u)

#if (UART_4_RXHW_ADDRESS_ENABLED)
    #define UART_4_RX_ADDRESS_MODE    (0u)
    #define UART_4_RX_HW_ADDRESS1     (0u)
    #define UART_4_RX_HW_ADDRESS2     (0u)
#endif /* (UART_4_RXHW_ADDRESS_ENABLED) */

#define UART_4_INIT_RX_INTERRUPTS_MASK \
                                  (uint8)((1 << UART_4_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << UART_4_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << UART_4_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << UART_4_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << UART_4_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << UART_4_RX_STS_BREAK_SHIFT) \
                                        | (0 << UART_4_RX_STS_OVERRUN_SHIFT))

#define UART_4_INIT_TX_INTERRUPTS_MASK \
                                  (uint8)((0 << UART_4_TX_STS_COMPLETE_SHIFT) \
                                        | (0 << UART_4_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << UART_4_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << UART_4_TX_STS_FIFO_NOT_FULL_SHIFT))


/***************************************
*              Registers
***************************************/

#ifdef UART_4_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define UART_4_CONTROL_REG \
                            (* (reg8 *) UART_4_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
    #define UART_4_CONTROL_PTR \
                            (  (reg8 *) UART_4_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
#endif /* End UART_4_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(UART_4_TX_ENABLED)
    #define UART_4_TXDATA_REG          (* (reg8 *) UART_4_BUART_sTX_TxShifter_u0__F0_REG)
    #define UART_4_TXDATA_PTR          (  (reg8 *) UART_4_BUART_sTX_TxShifter_u0__F0_REG)
    #define UART_4_TXDATA_AUX_CTL_REG  (* (reg8 *) UART_4_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define UART_4_TXDATA_AUX_CTL_PTR  (  (reg8 *) UART_4_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define UART_4_TXSTATUS_REG        (* (reg8 *) UART_4_BUART_sTX_TxSts__STATUS_REG)
    #define UART_4_TXSTATUS_PTR        (  (reg8 *) UART_4_BUART_sTX_TxSts__STATUS_REG)
    #define UART_4_TXSTATUS_MASK_REG   (* (reg8 *) UART_4_BUART_sTX_TxSts__MASK_REG)
    #define UART_4_TXSTATUS_MASK_PTR   (  (reg8 *) UART_4_BUART_sTX_TxSts__MASK_REG)
    #define UART_4_TXSTATUS_ACTL_REG   (* (reg8 *) UART_4_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define UART_4_TXSTATUS_ACTL_PTR   (  (reg8 *) UART_4_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(UART_4_TXCLKGEN_DP)
        #define UART_4_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) UART_4_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define UART_4_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) UART_4_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define UART_4_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) UART_4_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define UART_4_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) UART_4_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define UART_4_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) UART_4_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define UART_4_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) UART_4_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define UART_4_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) UART_4_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define UART_4_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) UART_4_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define UART_4_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) UART_4_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define UART_4_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) UART_4_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* UART_4_TXCLKGEN_DP */

#endif /* End UART_4_TX_ENABLED */

#if(UART_4_HD_ENABLED)

    #define UART_4_TXDATA_REG             (* (reg8 *) UART_4_BUART_sRX_RxShifter_u0__F1_REG )
    #define UART_4_TXDATA_PTR             (  (reg8 *) UART_4_BUART_sRX_RxShifter_u0__F1_REG )
    #define UART_4_TXDATA_AUX_CTL_REG     (* (reg8 *) UART_4_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define UART_4_TXDATA_AUX_CTL_PTR     (  (reg8 *) UART_4_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define UART_4_TXSTATUS_REG           (* (reg8 *) UART_4_BUART_sRX_RxSts__STATUS_REG )
    #define UART_4_TXSTATUS_PTR           (  (reg8 *) UART_4_BUART_sRX_RxSts__STATUS_REG )
    #define UART_4_TXSTATUS_MASK_REG      (* (reg8 *) UART_4_BUART_sRX_RxSts__MASK_REG )
    #define UART_4_TXSTATUS_MASK_PTR      (  (reg8 *) UART_4_BUART_sRX_RxSts__MASK_REG )
    #define UART_4_TXSTATUS_ACTL_REG      (* (reg8 *) UART_4_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define UART_4_TXSTATUS_ACTL_PTR      (  (reg8 *) UART_4_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End UART_4_HD_ENABLED */

#if( (UART_4_RX_ENABLED) || (UART_4_HD_ENABLED) )
    #define UART_4_RXDATA_REG             (* (reg8 *) UART_4_BUART_sRX_RxShifter_u0__F0_REG )
    #define UART_4_RXDATA_PTR             (  (reg8 *) UART_4_BUART_sRX_RxShifter_u0__F0_REG )
    #define UART_4_RXADDRESS1_REG         (* (reg8 *) UART_4_BUART_sRX_RxShifter_u0__D0_REG )
    #define UART_4_RXADDRESS1_PTR         (  (reg8 *) UART_4_BUART_sRX_RxShifter_u0__D0_REG )
    #define UART_4_RXADDRESS2_REG         (* (reg8 *) UART_4_BUART_sRX_RxShifter_u0__D1_REG )
    #define UART_4_RXADDRESS2_PTR         (  (reg8 *) UART_4_BUART_sRX_RxShifter_u0__D1_REG )
    #define UART_4_RXDATA_AUX_CTL_REG     (* (reg8 *) UART_4_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define UART_4_RXBITCTR_PERIOD_REG    (* (reg8 *) UART_4_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define UART_4_RXBITCTR_PERIOD_PTR    (  (reg8 *) UART_4_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define UART_4_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) UART_4_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define UART_4_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) UART_4_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define UART_4_RXBITCTR_COUNTER_REG   (* (reg8 *) UART_4_BUART_sRX_RxBitCounter__COUNT_REG )
    #define UART_4_RXBITCTR_COUNTER_PTR   (  (reg8 *) UART_4_BUART_sRX_RxBitCounter__COUNT_REG )

    #define UART_4_RXSTATUS_REG           (* (reg8 *) UART_4_BUART_sRX_RxSts__STATUS_REG )
    #define UART_4_RXSTATUS_PTR           (  (reg8 *) UART_4_BUART_sRX_RxSts__STATUS_REG )
    #define UART_4_RXSTATUS_MASK_REG      (* (reg8 *) UART_4_BUART_sRX_RxSts__MASK_REG )
    #define UART_4_RXSTATUS_MASK_PTR      (  (reg8 *) UART_4_BUART_sRX_RxSts__MASK_REG )
    #define UART_4_RXSTATUS_ACTL_REG      (* (reg8 *) UART_4_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define UART_4_RXSTATUS_ACTL_PTR      (  (reg8 *) UART_4_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (UART_4_RX_ENABLED) || (UART_4_HD_ENABLED) */

#if(UART_4_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define UART_4_INTCLOCK_CLKEN_REG     (* (reg8 *) UART_4_IntClock__PM_ACT_CFG)
    #define UART_4_INTCLOCK_CLKEN_PTR     (  (reg8 *) UART_4_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define UART_4_INTCLOCK_CLKEN_MASK    UART_4_IntClock__PM_ACT_MSK
#endif /* End UART_4_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants
***************************************/

#if(UART_4_TX_ENABLED)
    #define UART_4_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End UART_4_TX_ENABLED */

#if(UART_4_HD_ENABLED)
    #define UART_4_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End UART_4_HD_ENABLED */

#if( (UART_4_RX_ENABLED) || (UART_4_HD_ENABLED) )
    #define UART_4_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (UART_4_RX_ENABLED) || (UART_4_HD_ENABLED) */


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

/* UART v2_40 obsolete definitions */
#define UART_4_TXBUFFERSIZE   UART_4_TX_BUFFER_SIZE
#define UART_4_RXBUFFERSIZE   UART_4_RX_BUFFER_SIZE

#if (UART_4_RXHW_ADDRESS_ENABLED)
    #define UART_4_RXADDRESSMODE  UART_4_RX_ADDRESS_MODE
    #define UART_4_RXHWADDRESS1   UART_4_RX_HW_ADDRESS1
    #define UART_4_RXHWADDRESS2   UART_4_RX_HW_ADDRESS2
    /* Backward compatible define */
    #define UART_4_RXAddressMode  UART_4_RXADDRESSMODE
#endif /* (UART_4_RXHW_ADDRESS_ENABLED) */

/* UART v2_30 obsolete definitions */
#define UART_4_initvar                    UART_4_initVar

#define UART_4_RX_Enabled                 UART_4_RX_ENABLED
#define UART_4_TX_Enabled                 UART_4_TX_ENABLED
#define UART_4_HD_Enabled                 UART_4_HD_ENABLED
#define UART_4_RX_IntInterruptEnabled     UART_4_RX_INTERRUPT_ENABLED
#define UART_4_TX_IntInterruptEnabled     UART_4_TX_INTERRUPT_ENABLED
#define UART_4_InternalClockUsed          UART_4_INTERNAL_CLOCK_USED
#define UART_4_RXHW_Address_Enabled       UART_4_RXHW_ADDRESS_ENABLED
#define UART_4_OverSampleCount            UART_4_OVER_SAMPLE_COUNT
#define UART_4_ParityType                 UART_4_PARITY_TYPE

#if( UART_4_TX_ENABLED && (UART_4_TXBUFFERSIZE > UART_4_FIFO_LENGTH))
    #define UART_4_TXBUFFER               UART_4_txBuffer
    #define UART_4_TXBUFFERREAD           UART_4_txBufferRead
    #define UART_4_TXBUFFERWRITE          UART_4_txBufferWrite
#endif /* End UART_4_TX_ENABLED */
#if( ( UART_4_RX_ENABLED || UART_4_HD_ENABLED ) && \
     (UART_4_RXBUFFERSIZE > UART_4_FIFO_LENGTH) )
    #define UART_4_RXBUFFER               UART_4_rxBuffer
    #define UART_4_RXBUFFERREAD           UART_4_rxBufferRead
    #define UART_4_RXBUFFERWRITE          UART_4_rxBufferWrite
    #define UART_4_RXBUFFERLOOPDETECT     UART_4_rxBufferLoopDetect
    #define UART_4_RXBUFFER_OVERFLOW      UART_4_rxBufferOverflow
#endif /* End UART_4_RX_ENABLED */

#ifdef UART_4_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define UART_4_CONTROL                UART_4_CONTROL_REG
#endif /* End UART_4_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(UART_4_TX_ENABLED)
    #define UART_4_TXDATA                 UART_4_TXDATA_REG
    #define UART_4_TXSTATUS               UART_4_TXSTATUS_REG
    #define UART_4_TXSTATUS_MASK          UART_4_TXSTATUS_MASK_REG
    #define UART_4_TXSTATUS_ACTL          UART_4_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(UART_4_TXCLKGEN_DP)
        #define UART_4_TXBITCLKGEN_CTR        UART_4_TXBITCLKGEN_CTR_REG
        #define UART_4_TXBITCLKTX_COMPLETE    UART_4_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define UART_4_TXBITCTR_PERIOD        UART_4_TXBITCTR_PERIOD_REG
        #define UART_4_TXBITCTR_CONTROL       UART_4_TXBITCTR_CONTROL_REG
        #define UART_4_TXBITCTR_COUNTER       UART_4_TXBITCTR_COUNTER_REG
    #endif /* UART_4_TXCLKGEN_DP */
#endif /* End UART_4_TX_ENABLED */

#if(UART_4_HD_ENABLED)
    #define UART_4_TXDATA                 UART_4_TXDATA_REG
    #define UART_4_TXSTATUS               UART_4_TXSTATUS_REG
    #define UART_4_TXSTATUS_MASK          UART_4_TXSTATUS_MASK_REG
    #define UART_4_TXSTATUS_ACTL          UART_4_TXSTATUS_ACTL_REG
#endif /* End UART_4_HD_ENABLED */

#if( (UART_4_RX_ENABLED) || (UART_4_HD_ENABLED) )
    #define UART_4_RXDATA                 UART_4_RXDATA_REG
    #define UART_4_RXADDRESS1             UART_4_RXADDRESS1_REG
    #define UART_4_RXADDRESS2             UART_4_RXADDRESS2_REG
    #define UART_4_RXBITCTR_PERIOD        UART_4_RXBITCTR_PERIOD_REG
    #define UART_4_RXBITCTR_CONTROL       UART_4_RXBITCTR_CONTROL_REG
    #define UART_4_RXBITCTR_COUNTER       UART_4_RXBITCTR_COUNTER_REG
    #define UART_4_RXSTATUS               UART_4_RXSTATUS_REG
    #define UART_4_RXSTATUS_MASK          UART_4_RXSTATUS_MASK_REG
    #define UART_4_RXSTATUS_ACTL          UART_4_RXSTATUS_ACTL_REG
#endif /* End  (UART_4_RX_ENABLED) || (UART_4_HD_ENABLED) */

#if(UART_4_INTERNAL_CLOCK_USED)
    #define UART_4_INTCLOCK_CLKEN         UART_4_INTCLOCK_CLKEN_REG
#endif /* End UART_4_INTERNAL_CLOCK_USED */

#define UART_4_WAIT_FOR_COMLETE_REINIT    UART_4_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_UART_4_H */


/* [] END OF FILE */
