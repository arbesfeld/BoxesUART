/*******************************************************************************
* File Name: Rx_Left_SPI_UART_INT.c
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

#include "Rx_Left_PVT.h"
#include "Rx_Left_SPI_UART_PVT.h"


/*******************************************************************************
* Function Name: Rx_Left_SPI_UART_ISR
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
CY_ISR(Rx_Left_SPI_UART_ISR)
{
#if(Rx_Left_INTERNAL_RX_SW_BUFFER_CONST)
    uint32 locHead;
    uint32 dataRx;
#endif /* (Rx_Left_INTERNAL_RX_SW_BUFFER_CONST) */

#if(Rx_Left_INTERNAL_TX_SW_BUFFER_CONST)
    uint32 locTail;
#endif /* (Rx_Left_INTERNAL_TX_SW_BUFFER_CONST) */

    if(NULL != Rx_Left_customIntrHandler)
    {
        Rx_Left_customIntrHandler();
    }

    #if(Rx_Left_CHECK_SPI_WAKE_ENABLE)
    {
        /* Clear SPI wakeup source */
        Rx_Left_ClearSpiExtClkInterruptSource(Rx_Left_INTR_SPI_EC_WAKE_UP);
    }
    #endif

    #if(Rx_Left_CHECK_RX_SW_BUFFER)
    {
        if(Rx_Left_CHECK_INTR_RX_MASKED(Rx_Left_INTR_RX_NOT_EMPTY))
        {
            while(0u != Rx_Left_GET_RX_FIFO_ENTRIES)
            {
                /* Get data from RX FIFO */
                dataRx = Rx_Left_RX_FIFO_RD_REG;

                /* Move local head index */
                locHead = (Rx_Left_rxBufferHead + 1u);

                /* Adjust local head index */
                if(Rx_Left_RX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                if(locHead == Rx_Left_rxBufferTail)
                {
                    /* Overflow: through away new data */
                    Rx_Left_rxBufferOverflow = (uint8) Rx_Left_INTR_RX_OVERFLOW;
                }
                else
                {
                    /* Store received data */
                    Rx_Left_PutWordInRxBuffer(locHead, dataRx);

                    /* Move head index */
                    Rx_Left_rxBufferHead = locHead;
                }
            }

            Rx_Left_ClearRxInterruptSource(Rx_Left_INTR_RX_NOT_EMPTY);
        }
    }
    #endif


    #if(Rx_Left_CHECK_TX_SW_BUFFER)
    {
        if(Rx_Left_CHECK_INTR_TX_MASKED(Rx_Left_INTR_TX_NOT_FULL))
        {
            /* Put data into TX FIFO */
            while(Rx_Left_SPI_UART_FIFO_SIZE != Rx_Left_GET_TX_FIFO_ENTRIES)
            {
                /* Check for room in TX software buffer */
                if(Rx_Left_txBufferHead != Rx_Left_txBufferTail)
                {
                    /* Move local tail index */
                    locTail = (Rx_Left_txBufferTail + 1u);

                    /* Adjust local tail index */
                    if(Rx_Left_TX_BUFFER_SIZE == locTail)
                    {
                        locTail = 0u;
                    }

                    /* Put data into TX FIFO */
                    Rx_Left_TX_FIFO_WR_REG = Rx_Left_GetWordFromTxBuffer(locTail);

                    /* Move tail index */
                    Rx_Left_txBufferTail = locTail;
                }
                else
                {
                    /* TX software buffer is empty: complete transfer */
                    Rx_Left_DISABLE_INTR_TX(Rx_Left_INTR_TX_NOT_FULL);
                    break;
                }
            }

            Rx_Left_ClearTxInterruptSource(Rx_Left_INTR_TX_NOT_FULL);
        }
    }
    #endif
}


/* [] END OF FILE */
