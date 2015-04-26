/*******************************************************************************
* File Name: Rx_Left_SPI_UART_PVT.h
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

#if !defined(CY_SCB_SPI_UART_PVT_Rx_Left_H)
#define CY_SCB_SPI_UART_PVT_Rx_Left_H

#include "Rx_Left_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if(Rx_Left_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  Rx_Left_rxBufferHead;
    extern volatile uint32  Rx_Left_rxBufferTail;
    extern volatile uint8   Rx_Left_rxBufferOverflow;
#endif /* (Rx_Left_INTERNAL_RX_SW_BUFFER_CONST) */

#if(Rx_Left_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  Rx_Left_txBufferHead;
    extern volatile uint32  Rx_Left_txBufferTail;
#endif /* (Rx_Left_INTERNAL_TX_SW_BUFFER_CONST) */

#if(Rx_Left_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 Rx_Left_rxBufferInternal[Rx_Left_RX_BUFFER_SIZE];
#endif /* (Rx_Left_INTERNAL_RX_SW_BUFFER) */

#if(Rx_Left_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 Rx_Left_txBufferInternal[Rx_Left_TX_BUFFER_SIZE];
#endif /* (Rx_Left_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

#if(Rx_Left_SCB_MODE_SPI_CONST_CFG)
    void Rx_Left_SpiInit(void);
#endif /* (Rx_Left_SCB_MODE_SPI_CONST_CFG) */

#if(Rx_Left_SPI_WAKE_ENABLE_CONST)
    void Rx_Left_SpiSaveConfig(void);
    void Rx_Left_SpiRestoreConfig(void);
#endif /* (Rx_Left_SPI_WAKE_ENABLE_CONST) */

#if(Rx_Left_SCB_MODE_UART_CONST_CFG)
    void Rx_Left_UartInit(void);
#endif /* (Rx_Left_SCB_MODE_UART_CONST_CFG) */

#if(Rx_Left_UART_WAKE_ENABLE_CONST)
    void Rx_Left_UartSaveConfig(void);
    void Rx_Left_UartRestoreConfig(void);
    #define Rx_Left_UartStop() \
        do{                             \
            Rx_Left_UART_RX_CTRL_REG &= ~Rx_Left_UART_RX_CTRL_SKIP_START; \
        }while(0)
#else
        #define Rx_Left_UartStop() do{ /* Does nothing */ }while(0)

#endif /* (Rx_Left_UART_WAKE_ENABLE_CONST) */

/* Interrupt processing */
#define Rx_Left_SpiUartEnableIntRx(intSourceMask)  Rx_Left_SetRxInterruptMode(intSourceMask)
#define Rx_Left_SpiUartEnableIntTx(intSourceMask)  Rx_Left_SetTxInterruptMode(intSourceMask)
uint32  Rx_Left_SpiUartDisableIntRx(void);
uint32  Rx_Left_SpiUartDisableIntTx(void);


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in Rx_Left_SetPins() */
#define Rx_Left_UART_RX_PIN_ENABLE    (Rx_Left_UART_RX)
#define Rx_Left_UART_TX_PIN_ENABLE    (Rx_Left_UART_TX)

/* UART RTS and CTS position to be used in  Rx_Left_SetPins() */
#define Rx_Left_UART_RTS_PIN_ENABLE    (0x10u)
#define Rx_Left_UART_CTS_PIN_ENABLE    (0x20u)

#endif /* (CY_SCB_SPI_UART_PVT_Rx_Left_H) */


/* [] END OF FILE */
