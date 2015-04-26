/*******************************************************************************
* File Name: UART_TxRx_Right_SPI_UART_PVT.h
* Version 2.0
*
* Description:
*  This private file provides constants and parameter values for the
*  SCB Component in SPI and UART modes.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_SPI_UART_PVT_UART_TxRx_Right_H)
#define CY_SCB_SPI_UART_PVT_UART_TxRx_Right_H

#include "UART_TxRx_Right_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if(UART_TxRx_Right_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  UART_TxRx_Right_rxBufferHead;
    extern volatile uint32  UART_TxRx_Right_rxBufferTail;
    extern volatile uint8   UART_TxRx_Right_rxBufferOverflow;
#endif /* (UART_TxRx_Right_INTERNAL_RX_SW_BUFFER_CONST) */

#if(UART_TxRx_Right_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  UART_TxRx_Right_txBufferHead;
    extern volatile uint32  UART_TxRx_Right_txBufferTail;
#endif /* (UART_TxRx_Right_INTERNAL_TX_SW_BUFFER_CONST) */

#if(UART_TxRx_Right_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 UART_TxRx_Right_rxBufferInternal[UART_TxRx_Right_RX_BUFFER_SIZE];
#endif /* (UART_TxRx_Right_INTERNAL_RX_SW_BUFFER) */

#if(UART_TxRx_Right_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 UART_TxRx_Right_txBufferInternal[UART_TxRx_Right_TX_BUFFER_SIZE];
#endif /* (UART_TxRx_Right_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

#if(UART_TxRx_Right_SCB_MODE_SPI_CONST_CFG)
    void UART_TxRx_Right_SpiInit(void);
#endif /* (UART_TxRx_Right_SCB_MODE_SPI_CONST_CFG) */

#if(UART_TxRx_Right_SPI_WAKE_ENABLE_CONST)
    void UART_TxRx_Right_SpiSaveConfig(void);
    void UART_TxRx_Right_SpiRestoreConfig(void);
#endif /* (UART_TxRx_Right_SPI_WAKE_ENABLE_CONST) */

#if(UART_TxRx_Right_SCB_MODE_UART_CONST_CFG)
    void UART_TxRx_Right_UartInit(void);
#endif /* (UART_TxRx_Right_SCB_MODE_UART_CONST_CFG) */

#if(UART_TxRx_Right_UART_WAKE_ENABLE_CONST)
    void UART_TxRx_Right_UartSaveConfig(void);
    void UART_TxRx_Right_UartRestoreConfig(void);
    #define UART_TxRx_Right_UartStop() \
        do{                             \
            UART_TxRx_Right_UART_RX_CTRL_REG &= ~UART_TxRx_Right_UART_RX_CTRL_SKIP_START; \
        }while(0)
#else
        #define UART_TxRx_Right_UartStop() do{ /* Does nothing */ }while(0)

#endif /* (UART_TxRx_Right_UART_WAKE_ENABLE_CONST) */

/* Interrupt processing */
#define UART_TxRx_Right_SpiUartEnableIntRx(intSourceMask)  UART_TxRx_Right_SetRxInterruptMode(intSourceMask)
#define UART_TxRx_Right_SpiUartEnableIntTx(intSourceMask)  UART_TxRx_Right_SetTxInterruptMode(intSourceMask)
uint32  UART_TxRx_Right_SpiUartDisableIntRx(void);
uint32  UART_TxRx_Right_SpiUartDisableIntTx(void);


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in UART_TxRx_Right_SetPins() */
#define UART_TxRx_Right_UART_RX_PIN_ENABLE    (UART_TxRx_Right_UART_RX)
#define UART_TxRx_Right_UART_TX_PIN_ENABLE    (UART_TxRx_Right_UART_TX)

/* UART RTS and CTS position to be used in  UART_TxRx_Right_SetPins() */
#define UART_TxRx_Right_UART_RTS_PIN_ENABLE    (0x10u)
#define UART_TxRx_Right_UART_CTS_PIN_ENABLE    (0x20u)

#endif /* (CY_SCB_SPI_UART_PVT_UART_TxRx_Right_H) */


/* [] END OF FILE */
