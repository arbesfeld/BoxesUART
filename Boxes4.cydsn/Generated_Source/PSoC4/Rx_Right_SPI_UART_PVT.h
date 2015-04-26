/*******************************************************************************
* File Name: Rx_Right_SPI_UART_PVT.h
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

#if !defined(CY_SCB_SPI_UART_PVT_Rx_Right_H)
#define CY_SCB_SPI_UART_PVT_Rx_Right_H

#include "Rx_Right_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if(Rx_Right_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  Rx_Right_rxBufferHead;
    extern volatile uint32  Rx_Right_rxBufferTail;
    extern volatile uint8   Rx_Right_rxBufferOverflow;
#endif /* (Rx_Right_INTERNAL_RX_SW_BUFFER_CONST) */

#if(Rx_Right_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  Rx_Right_txBufferHead;
    extern volatile uint32  Rx_Right_txBufferTail;
#endif /* (Rx_Right_INTERNAL_TX_SW_BUFFER_CONST) */

#if(Rx_Right_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 Rx_Right_rxBufferInternal[Rx_Right_RX_BUFFER_SIZE];
#endif /* (Rx_Right_INTERNAL_RX_SW_BUFFER) */

#if(Rx_Right_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 Rx_Right_txBufferInternal[Rx_Right_TX_BUFFER_SIZE];
#endif /* (Rx_Right_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

#if(Rx_Right_SCB_MODE_SPI_CONST_CFG)
    void Rx_Right_SpiInit(void);
#endif /* (Rx_Right_SCB_MODE_SPI_CONST_CFG) */

#if(Rx_Right_SPI_WAKE_ENABLE_CONST)
    void Rx_Right_SpiSaveConfig(void);
    void Rx_Right_SpiRestoreConfig(void);
#endif /* (Rx_Right_SPI_WAKE_ENABLE_CONST) */

#if(Rx_Right_SCB_MODE_UART_CONST_CFG)
    void Rx_Right_UartInit(void);
#endif /* (Rx_Right_SCB_MODE_UART_CONST_CFG) */

#if(Rx_Right_UART_WAKE_ENABLE_CONST)
    void Rx_Right_UartSaveConfig(void);
    void Rx_Right_UartRestoreConfig(void);
    #define Rx_Right_UartStop() \
        do{                             \
            Rx_Right_UART_RX_CTRL_REG &= ~Rx_Right_UART_RX_CTRL_SKIP_START; \
        }while(0)
#else
        #define Rx_Right_UartStop() do{ /* Does nothing */ }while(0)

#endif /* (Rx_Right_UART_WAKE_ENABLE_CONST) */

/* Interrupt processing */
#define Rx_Right_SpiUartEnableIntRx(intSourceMask)  Rx_Right_SetRxInterruptMode(intSourceMask)
#define Rx_Right_SpiUartEnableIntTx(intSourceMask)  Rx_Right_SetTxInterruptMode(intSourceMask)
uint32  Rx_Right_SpiUartDisableIntRx(void);
uint32  Rx_Right_SpiUartDisableIntTx(void);


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in Rx_Right_SetPins() */
#define Rx_Right_UART_RX_PIN_ENABLE    (Rx_Right_UART_RX)
#define Rx_Right_UART_TX_PIN_ENABLE    (Rx_Right_UART_TX)

/* UART RTS and CTS position to be used in  Rx_Right_SetPins() */
#define Rx_Right_UART_RTS_PIN_ENABLE    (0x10u)
#define Rx_Right_UART_CTS_PIN_ENABLE    (0x20u)

#endif /* (CY_SCB_SPI_UART_PVT_Rx_Right_H) */


/* [] END OF FILE */
