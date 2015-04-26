/*******************************************************************************
* File Name: UART_Rx_Left_SPI_UART_PVT.h
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

#if !defined(CY_SCB_SPI_UART_PVT_UART_Rx_Left_H)
#define CY_SCB_SPI_UART_PVT_UART_Rx_Left_H

#include "UART_Rx_Left_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if(UART_Rx_Left_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  UART_Rx_Left_rxBufferHead;
    extern volatile uint32  UART_Rx_Left_rxBufferTail;
    extern volatile uint8   UART_Rx_Left_rxBufferOverflow;
#endif /* (UART_Rx_Left_INTERNAL_RX_SW_BUFFER_CONST) */

#if(UART_Rx_Left_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  UART_Rx_Left_txBufferHead;
    extern volatile uint32  UART_Rx_Left_txBufferTail;
#endif /* (UART_Rx_Left_INTERNAL_TX_SW_BUFFER_CONST) */

#if(UART_Rx_Left_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 UART_Rx_Left_rxBufferInternal[UART_Rx_Left_RX_BUFFER_SIZE];
#endif /* (UART_Rx_Left_INTERNAL_RX_SW_BUFFER) */

#if(UART_Rx_Left_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 UART_Rx_Left_txBufferInternal[UART_Rx_Left_TX_BUFFER_SIZE];
#endif /* (UART_Rx_Left_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

#if(UART_Rx_Left_SCB_MODE_SPI_CONST_CFG)
    void UART_Rx_Left_SpiInit(void);
#endif /* (UART_Rx_Left_SCB_MODE_SPI_CONST_CFG) */

#if(UART_Rx_Left_SPI_WAKE_ENABLE_CONST)
    void UART_Rx_Left_SpiSaveConfig(void);
    void UART_Rx_Left_SpiRestoreConfig(void);
#endif /* (UART_Rx_Left_SPI_WAKE_ENABLE_CONST) */

#if(UART_Rx_Left_SCB_MODE_UART_CONST_CFG)
    void UART_Rx_Left_UartInit(void);
#endif /* (UART_Rx_Left_SCB_MODE_UART_CONST_CFG) */

#if(UART_Rx_Left_UART_WAKE_ENABLE_CONST)
    void UART_Rx_Left_UartSaveConfig(void);
    void UART_Rx_Left_UartRestoreConfig(void);
    #define UART_Rx_Left_UartStop() \
        do{                             \
            UART_Rx_Left_UART_RX_CTRL_REG &= ~UART_Rx_Left_UART_RX_CTRL_SKIP_START; \
        }while(0)
#else
        #define UART_Rx_Left_UartStop() do{ /* Does nothing */ }while(0)

#endif /* (UART_Rx_Left_UART_WAKE_ENABLE_CONST) */

/* Interrupt processing */
#define UART_Rx_Left_SpiUartEnableIntRx(intSourceMask)  UART_Rx_Left_SetRxInterruptMode(intSourceMask)
#define UART_Rx_Left_SpiUartEnableIntTx(intSourceMask)  UART_Rx_Left_SetTxInterruptMode(intSourceMask)
uint32  UART_Rx_Left_SpiUartDisableIntRx(void);
uint32  UART_Rx_Left_SpiUartDisableIntTx(void);


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in UART_Rx_Left_SetPins() */
#define UART_Rx_Left_UART_RX_PIN_ENABLE    (UART_Rx_Left_UART_RX)
#define UART_Rx_Left_UART_TX_PIN_ENABLE    (UART_Rx_Left_UART_TX)

/* UART RTS and CTS position to be used in  UART_Rx_Left_SetPins() */
#define UART_Rx_Left_UART_RTS_PIN_ENABLE    (0x10u)
#define UART_Rx_Left_UART_CTS_PIN_ENABLE    (0x20u)

#endif /* (CY_SCB_SPI_UART_PVT_UART_Rx_Left_H) */


/* [] END OF FILE */
