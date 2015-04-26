/*******************************************************************************
* File Name: UART_Tx.h
* Version 1.30
*
* Description:
*  This file provides constants and parameter values for the Software Transmit
*  UART Component.
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#ifndef CY_SW_TX_UART_UART_Tx_H
#define CY_SW_TX_UART_UART_Tx_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"

#define UART_Tx_BAUD_RATE                      (38400u)
#define UART_Tx_PIN_STATIC_MODE                (1u)


/***************************************
*        Function Prototypes
***************************************/
#if(UART_Tx_PIN_STATIC_MODE == 1u)
    void UART_Tx_Start(void) ;
#else
    void UART_Tx_StartEx(uint8 port, uint8 pin) ;
#endif /* (UART_Tx_PIN_STATIC_MODE == 1u) */

void UART_Tx_Stop(void) ;
void UART_Tx_PutChar(uint8 txDataByte) ;
void UART_Tx_PutString(const char8 string[]) ;
void UART_Tx_PutArray(const uint8 array[], uint32 byteCount) ;
void UART_Tx_PutHexByte(uint8 txHexByte) ;
void UART_Tx_PutHexInt(uint16 txHexInt) ;
void UART_Tx_PutCRLF(void) ;

#endif /* CY_SW_TX_UART_UART_Tx_H */


/* [] END OF FILE */
