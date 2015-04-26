/*******************************************************************************
* File Name: UART_OUTINT.c
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

#include "UART_OUT.h"


/***************************************
* Custom Declarations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */

#if (UART_OUT_RX_INTERRUPT_ENABLED && (UART_OUT_RX_ENABLED || UART_OUT_HD_ENABLED))
    /*******************************************************************************
    * Function Name: UART_OUT_RXISR
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
    *  UART_OUT_rxBuffer - RAM buffer pointer for save received data.
    *  UART_OUT_rxBufferWrite - cyclic index for write to rxBuffer,
    *     increments after each byte saved to buffer.
    *  UART_OUT_rxBufferRead - cyclic index for read from rxBuffer,
    *     checked to detect overflow condition.
    *  UART_OUT_rxBufferOverflow - software overflow flag. Set to one
    *     when UART_OUT_rxBufferWrite index overtakes
    *     UART_OUT_rxBufferRead index.
    *  UART_OUT_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when UART_OUT_rxBufferWrite is equal to
    *    UART_OUT_rxBufferRead
    *  UART_OUT_rxAddressMode - this variable contains the Address mode,
    *     selected in customizer or set by UART_SetRxAddressMode() API.
    *  UART_OUT_rxAddressDetected - set to 1 when correct address received,
    *     and analysed to store following addressed data bytes to the buffer.
    *     When not correct address received, set to 0 to skip following data bytes.
    *
    *******************************************************************************/
    CY_ISR(UART_OUT_RXISR)
    {
        uint8 readData;
        uint8 increment_pointer = 0u;

    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

        /* User code required at start of ISR */
        /* `#START UART_OUT_RXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        readData = UART_OUT_RXSTATUS_REG;

        if((readData & (UART_OUT_RX_STS_BREAK | UART_OUT_RX_STS_PAR_ERROR |
                        UART_OUT_RX_STS_STOP_ERROR | UART_OUT_RX_STS_OVERRUN)) != 0u)
        {
            /* ERROR handling. */
            UART_OUT_errorStatus = readData & ( UART_OUT_RX_STS_BREAK | 
                                                        UART_OUT_RX_STS_PAR_ERROR | 
                                                        UART_OUT_RX_STS_STOP_ERROR | 
                                                        UART_OUT_RX_STS_OVERRUN);
            /* `#START UART_OUT_RXISR_ERROR` */

            /* `#END` */
        }

        while((readData & UART_OUT_RX_STS_FIFO_NOTEMPTY) != 0u)
        {
        #if (UART_OUT_RXHW_ADDRESS_ENABLED)
            if(UART_OUT_rxAddressMode == (uint8)UART_OUT__B_UART__AM_SW_DETECT_TO_BUFFER)
            {
                if((readData & UART_OUT_RX_STS_MRKSPC) != 0u)
                {
                    if ((readData & UART_OUT_RX_STS_ADDR_MATCH) != 0u)
                    {
                        UART_OUT_rxAddressDetected = 1u;
                    }
                    else
                    {
                        UART_OUT_rxAddressDetected = 0u;
                    }
                }

                readData = UART_OUT_RXDATA_REG;
                if(UART_OUT_rxAddressDetected != 0u)
                {   /* Store only addressed data */
                    UART_OUT_rxBuffer[UART_OUT_rxBufferWrite] = readData;
                    increment_pointer = 1u;
                }
            }
            else /* Without software addressing */
            {
                UART_OUT_rxBuffer[UART_OUT_rxBufferWrite] = UART_OUT_RXDATA_REG;
                increment_pointer = 1u;
            }
        #else  /* Without addressing */
            UART_OUT_rxBuffer[UART_OUT_rxBufferWrite] = UART_OUT_RXDATA_REG;
            increment_pointer = 1u;
        #endif /* (UART_OUT_RXHW_ADDRESS_ENABLED) */

            /* Do not increment buffer pointer when skip not addressed data */
            if(increment_pointer != 0u)
            {
                if(UART_OUT_rxBufferLoopDetect != 0u)
                {   /* Set Software Buffer status Overflow */
                    UART_OUT_rxBufferOverflow = 1u;
                }
                /* Set next pointer. */
                UART_OUT_rxBufferWrite++;

                /* Check pointer for a loop condition */
                if(UART_OUT_rxBufferWrite >= UART_OUT_RX_BUFFER_SIZE)
                {
                    UART_OUT_rxBufferWrite = 0u;
                }

                /* Detect pre-overload condition and set flag */
                if(UART_OUT_rxBufferWrite == UART_OUT_rxBufferRead)
                {
                    UART_OUT_rxBufferLoopDetect = 1u;
                    /* When Hardware Flow Control selected */
                    #if (UART_OUT_FLOW_CONTROL != 0u)
                        /* Disable RX interrupt mask, it is enabled when user read data from the buffer using APIs */
                        UART_OUT_RXSTATUS_MASK_REG  &= (uint8)~UART_OUT_RX_STS_FIFO_NOTEMPTY;
                        CyIntClearPending(UART_OUT_RX_VECT_NUM);
                        break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                    #endif /* (UART_OUT_FLOW_CONTROL != 0u) */
                }
            }

            /* Read status to decide whether read more bytes */
            readData = UART_OUT_RXSTATUS_REG;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START UART_OUT_RXISR_END` */

        /* `#END` */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
    }

#endif /* (UART_OUT_RX_INTERRUPT_ENABLED && (UART_OUT_RX_ENABLED || UART_OUT_HD_ENABLED)) */


#if (UART_OUT_TX_INTERRUPT_ENABLED && UART_OUT_TX_ENABLED)
    /*******************************************************************************
    * Function Name: UART_OUT_TXISR
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
    *  UART_OUT_txBuffer - RAM buffer pointer for transmit data from.
    *  UART_OUT_txBufferRead - cyclic index for read and transmit data
    *     from txBuffer, increments after each transmitted byte.
    *  UART_OUT_rxBufferWrite - cyclic index for write to txBuffer,
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(UART_OUT_TXISR)
    {
    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

        /* User code required at start of ISR */
        /* `#START UART_OUT_TXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        while((UART_OUT_txBufferRead != UART_OUT_txBufferWrite) &&
             ((UART_OUT_TXSTATUS_REG & UART_OUT_TX_STS_FIFO_FULL) == 0u))
        {
            /* Check pointer wrap around */
            if(UART_OUT_txBufferRead >= UART_OUT_TX_BUFFER_SIZE)
            {
                UART_OUT_txBufferRead = 0u;
            }

            UART_OUT_TXDATA_REG = UART_OUT_txBuffer[UART_OUT_txBufferRead];

            /* Set next pointer */
            UART_OUT_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START UART_OUT_TXISR_END` */

        /* `#END` */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
    }

#endif /* (UART_OUT_TX_INTERRUPT_ENABLED && UART_OUT_TX_ENABLED) */


/* [] END OF FILE */
