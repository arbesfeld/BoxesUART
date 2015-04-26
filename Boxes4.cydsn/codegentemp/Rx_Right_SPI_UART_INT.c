/*******************************************************************************
* File Name: Rx_Right_SPI_UART_INT.c
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

#include "Rx_Right_PVT.h"
#include "Rx_Right_SPI_UART_PVT.h"


/*******************************************************************************
* Function Name: Rx_Right_SPI_UART_ISR
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
CY_ISR(Rx_Right_SPI_UART_ISR)
{
#if(Rx_Right_INTERNAL_RX_SW_BUFFER_CONST)
    uint32 locHead;
    uint32 dataRx;
#endif /* (Rx_Right_INTERNAL_RX_SW_BUFFER_CONST) */

#if(Rx_Right_INTERNAL_TX_SW_BUFFER_CONST)
    uint32 locTail;
#endif /* (Rx_Right_INTERNAL_TX_SW_BUFFER_CONST) */

    if(NULL != Rx_Right_customIntrHandler)
    {
        Rx_Right_customIntrHandler();
    }

    #if(Rx_Right_CHECK_SPI_WAKE_ENABLE)
    {
        /* Clear SPI wakeup source */
        Rx_Right_ClearSpiExtClkInterruptSource(Rx_Right_INTR_SPI_EC_WAKE_UP);
    }
    #endif

    #if(Rx_Right_CHECK_RX_SW_BUFFER)
    {
        if(Rx_Right_CHECK_INTR_RX_MASKED(Rx_Right_INTR_RX_NOT_EMPTY))
        {
            while(0u != Rx_Right_GET_RX_FIFO_ENTRIES)
            {
                /* Get data from RX FIFO */
                dataRx = Rx_Right_RX_FIFO_RD_REG;

                /* Move local head index */
                locHead = (Rx_Right_rxBufferHead + 1u);

                /* Adjust local head index */
                if(Rx_Right_RX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                if(locHead == Rx_Right_rxBufferTail)
                {
                    /* Overflow: through away new data */
                    Rx_Right_rxBufferOverflow = (uint8) Rx_Right_INTR_RX_OVERFLOW;
                }
                else
                {
                    /* Store received data */
                    Rx_Right_PutWordInRxBuffer(locHead, dataRx);

                    /* Move head index */
                    Rx_Right_rxBufferHead = locHead;
                }
            }

            Rx_Right_ClearRxInterruptSource(Rx_Right_INTR_RX_NOT_EMPTY);
        }
    }
    #endif


    #if(Rx_Right_CHECK_TX_SW_BUFFER)
    {
        if(Rx_Right_CHECK_INTR_TX_MASKED(Rx_Right_INTR_TX_NOT_FULL))
        {
            /* Put data into TX FIFO */
            while(Rx_Right_SPI_UART_FIFO_SIZE != Rx_Right_GET_TX_FIFO_ENTRIES)
            {
                /* Check for room in TX software buffer */
                if(Rx_Right_txBufferHead != Rx_Right_txBufferTail)
                {
                    /* Move local tail index */
                    locTail = (Rx_Right_txBufferTail + 1u);

                    /* Adjust local tail index */
                    if(Rx_Right_TX_BUFFER_SIZE == locTail)
                    {
                        locTail = 0u;
                    }

                    /* Put data into TX FIFO */
                    Rx_Right_TX_FIFO_WR_REG = Rx_Right_GetWordFromTxBuffer(locTail);

                    /* Move tail index */
                    Rx_Right_txBufferTail = locTail;
                }
                else
                {
                    /* TX software buffer is empty: complete transfer */
                    Rx_Right_DISABLE_INTR_TX(Rx_Right_INTR_TX_NOT_FULL);
                    break;
                }
            }

            Rx_Right_ClearTxInterruptSource(Rx_Right_INTR_TX_NOT_FULL);
        }
    }
    #endif
}


/* [] END OF FILE */
