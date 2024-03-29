/*******************************************************************************
* File Name: UART_Rx_Back_SPI_UART_INT.c
* Version 2.0
*
* Description:
*  This file provides the source code to the Interrupt Service Routine for
*  the SCB Component in SPI and UART modes.
*
* Note:
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "UART_Rx_Back_PVT.h"
#include "UART_Rx_Back_SPI_UART_PVT.h"


/*******************************************************************************
* Function Name: UART_Rx_Back_SPI_UART_ISR
********************************************************************************
*
* Summary:
*  Handles the Interrupt Service Routine for the SCB SPI or UART modes.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
CY_ISR(UART_Rx_Back_SPI_UART_ISR)
{
#if(UART_Rx_Back_INTERNAL_RX_SW_BUFFER_CONST)
    uint32 locHead;
    uint32 dataRx;
#endif /* (UART_Rx_Back_INTERNAL_RX_SW_BUFFER_CONST) */

#if(UART_Rx_Back_INTERNAL_TX_SW_BUFFER_CONST)
    uint32 locTail;
#endif /* (UART_Rx_Back_INTERNAL_TX_SW_BUFFER_CONST) */

    if(NULL != UART_Rx_Back_customIntrHandler)
    {
        UART_Rx_Back_customIntrHandler();
    }

    #if(UART_Rx_Back_CHECK_SPI_WAKE_ENABLE)
    {
        /* Clear SPI wakeup source */
        UART_Rx_Back_ClearSpiExtClkInterruptSource(UART_Rx_Back_INTR_SPI_EC_WAKE_UP);
    }
    #endif

    #if(UART_Rx_Back_CHECK_RX_SW_BUFFER)
    {
        if(UART_Rx_Back_CHECK_INTR_RX_MASKED(UART_Rx_Back_INTR_RX_NOT_EMPTY))
        {
            while(0u != UART_Rx_Back_GET_RX_FIFO_ENTRIES)
            {
                /* Get data from RX FIFO */
                dataRx = UART_Rx_Back_RX_FIFO_RD_REG;

                /* Move local head index */
                locHead = (UART_Rx_Back_rxBufferHead + 1u);

                /* Adjust local head index */
                if(UART_Rx_Back_RX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                if(locHead == UART_Rx_Back_rxBufferTail)
                {
                    /* Overflow: through away new data */
                    UART_Rx_Back_rxBufferOverflow = (uint8) UART_Rx_Back_INTR_RX_OVERFLOW;
                }
                else
                {
                    /* Store received data */
                    UART_Rx_Back_PutWordInRxBuffer(locHead, dataRx);

                    /* Move head index */
                    UART_Rx_Back_rxBufferHead = locHead;
                }
            }

            UART_Rx_Back_ClearRxInterruptSource(UART_Rx_Back_INTR_RX_NOT_EMPTY);
        }
    }
    #endif


    #if(UART_Rx_Back_CHECK_TX_SW_BUFFER)
    {
        if(UART_Rx_Back_CHECK_INTR_TX_MASKED(UART_Rx_Back_INTR_TX_NOT_FULL))
        {
            /* Put data into TX FIFO */
            while(UART_Rx_Back_SPI_UART_FIFO_SIZE != UART_Rx_Back_GET_TX_FIFO_ENTRIES)
            {
                /* Check for room in TX software buffer */
                if(UART_Rx_Back_txBufferHead != UART_Rx_Back_txBufferTail)
                {
                    /* Move local tail index */
                    locTail = (UART_Rx_Back_txBufferTail + 1u);

                    /* Adjust local tail index */
                    if(UART_Rx_Back_TX_BUFFER_SIZE == locTail)
                    {
                        locTail = 0u;
                    }

                    /* Put data into TX FIFO */
                    UART_Rx_Back_TX_FIFO_WR_REG = UART_Rx_Back_GetWordFromTxBuffer(locTail);

                    /* Move tail index */
                    UART_Rx_Back_txBufferTail = locTail;
                }
                else
                {
                    /* TX software buffer is empty: complete transfer */
                    UART_Rx_Back_DISABLE_INTR_TX(UART_Rx_Back_INTR_TX_NOT_FULL);
                    break;
                }
            }

            UART_Rx_Back_ClearTxInterruptSource(UART_Rx_Back_INTR_TX_NOT_FULL);
        }
    }
    #endif
}


/* [] END OF FILE */
