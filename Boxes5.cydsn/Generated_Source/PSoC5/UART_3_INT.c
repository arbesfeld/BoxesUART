/*******************************************************************************
* File Name: UART_3INT.c
* Version 2.40
*
* Description:
*  This file provides all Interrupt Service functionality of the UART component
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "UART_3.h"


/***************************************
* Custom Declarations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */

#if (UART_3_RX_INTERRUPT_ENABLED && (UART_3_RX_ENABLED || UART_3_HD_ENABLED))
    /*******************************************************************************
    * Function Name: UART_3_RXISR
    ********************************************************************************
    *
    * Summary:
    *  Interrupt Service Routine for RX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  UART_3_rxBuffer - RAM buffer pointer for save received data.
    *  UART_3_rxBufferWrite - cyclic index for write to rxBuffer,
    *     increments after each byte saved to buffer.
    *  UART_3_rxBufferRead - cyclic index for read from rxBuffer,
    *     checked to detect overflow condition.
    *  UART_3_rxBufferOverflow - software overflow flag. Set to one
    *     when UART_3_rxBufferWrite index overtakes
    *     UART_3_rxBufferRead index.
    *  UART_3_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when UART_3_rxBufferWrite is equal to
    *    UART_3_rxBufferRead
    *  UART_3_rxAddressMode - this variable contains the Address mode,
    *     selected in customizer or set by UART_SetRxAddressMode() API.
    *  UART_3_rxAddressDetected - set to 1 when correct address received,
    *     and analysed to store following addressed data bytes to the buffer.
    *     When not correct address received, set to 0 to skip following data bytes.
    *
    *******************************************************************************/
    CY_ISR(UART_3_RXISR)
    {
        uint8 readData;
        uint8 increment_pointer = 0u;

    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

        /* User code required at start of ISR */
        /* `#START UART_3_RXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        readData = UART_3_RXSTATUS_REG;

        if((readData & (UART_3_RX_STS_BREAK | UART_3_RX_STS_PAR_ERROR |
                        UART_3_RX_STS_STOP_ERROR | UART_3_RX_STS_OVERRUN)) != 0u)
        {
            /* ERROR handling. */
            UART_3_errorStatus = readData & ( UART_3_RX_STS_BREAK | 
                                                        UART_3_RX_STS_PAR_ERROR | 
                                                        UART_3_RX_STS_STOP_ERROR | 
                                                        UART_3_RX_STS_OVERRUN);
            /* `#START UART_3_RXISR_ERROR` */

            /* `#END` */
        }

        while((readData & UART_3_RX_STS_FIFO_NOTEMPTY) != 0u)
        {
        #if (UART_3_RXHW_ADDRESS_ENABLED)
            if(UART_3_rxAddressMode == (uint8)UART_3__B_UART__AM_SW_DETECT_TO_BUFFER)
            {
                if((readData & UART_3_RX_STS_MRKSPC) != 0u)
                {
                    if ((readData & UART_3_RX_STS_ADDR_MATCH) != 0u)
                    {
                        UART_3_rxAddressDetected = 1u;
                    }
                    else
                    {
                        UART_3_rxAddressDetected = 0u;
                    }
                }

                readData = UART_3_RXDATA_REG;
                if(UART_3_rxAddressDetected != 0u)
                {   /* Store only addressed data */
                    UART_3_rxBuffer[UART_3_rxBufferWrite] = readData;
                    increment_pointer = 1u;
                }
            }
            else /* Without software addressing */
            {
                UART_3_rxBuffer[UART_3_rxBufferWrite] = UART_3_RXDATA_REG;
                increment_pointer = 1u;
            }
        #else  /* Without addressing */
            UART_3_rxBuffer[UART_3_rxBufferWrite] = UART_3_RXDATA_REG;
            increment_pointer = 1u;
        #endif /* (UART_3_RXHW_ADDRESS_ENABLED) */

            /* Do not increment buffer pointer when skip not addressed data */
            if(increment_pointer != 0u)
            {
                if(UART_3_rxBufferLoopDetect != 0u)
                {   /* Set Software Buffer status Overflow */
                    UART_3_rxBufferOverflow = 1u;
                }
                /* Set next pointer. */
                UART_3_rxBufferWrite++;

                /* Check pointer for a loop condition */
                if(UART_3_rxBufferWrite >= UART_3_RX_BUFFER_SIZE)
                {
                    UART_3_rxBufferWrite = 0u;
                }

                /* Detect pre-overload condition and set flag */
                if(UART_3_rxBufferWrite == UART_3_rxBufferRead)
                {
                    UART_3_rxBufferLoopDetect = 1u;
                    /* When Hardware Flow Control selected */
                    #if (UART_3_FLOW_CONTROL != 0u)
                        /* Disable RX interrupt mask, it is enabled when user read data from the buffer using APIs */
                        UART_3_RXSTATUS_MASK_REG  &= (uint8)~UART_3_RX_STS_FIFO_NOTEMPTY;
                        CyIntClearPending(UART_3_RX_VECT_NUM);
                        break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                    #endif /* (UART_3_FLOW_CONTROL != 0u) */
                }
            }

            /* Read status to decide whether read more bytes */
            readData = UART_3_RXSTATUS_REG;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START UART_3_RXISR_END` */

        /* `#END` */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
    }

#endif /* (UART_3_RX_INTERRUPT_ENABLED && (UART_3_RX_ENABLED || UART_3_HD_ENABLED)) */


#if (UART_3_TX_INTERRUPT_ENABLED && UART_3_TX_ENABLED)
    /*******************************************************************************
    * Function Name: UART_3_TXISR
    ********************************************************************************
    *
    * Summary:
    * Interrupt Service Routine for the TX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  UART_3_txBuffer - RAM buffer pointer for transmit data from.
    *  UART_3_txBufferRead - cyclic index for read and transmit data
    *     from txBuffer, increments after each transmitted byte.
    *  UART_3_rxBufferWrite - cyclic index for write to txBuffer,
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(UART_3_TXISR)
    {
    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

        /* User code required at start of ISR */
        /* `#START UART_3_TXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        while((UART_3_txBufferRead != UART_3_txBufferWrite) &&
             ((UART_3_TXSTATUS_REG & UART_3_TX_STS_FIFO_FULL) == 0u))
        {
            /* Check pointer wrap around */
            if(UART_3_txBufferRead >= UART_3_TX_BUFFER_SIZE)
            {
                UART_3_txBufferRead = 0u;
            }

            UART_3_TXDATA_REG = UART_3_txBuffer[UART_3_txBufferRead];

            /* Set next pointer */
            UART_3_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START UART_3_TXISR_END` */

        /* `#END` */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
    }

#endif /* (UART_3_TX_INTERRUPT_ENABLED && UART_3_TX_ENABLED) */


/* [] END OF FILE */
