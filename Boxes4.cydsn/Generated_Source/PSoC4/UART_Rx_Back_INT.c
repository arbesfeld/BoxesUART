/*******************************************************************************
* File Name: UART_Rx_BackINT.c
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

#include "UART_Rx_Back.h"


/***************************************
* Custom Declarations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */

#if (UART_Rx_Back_RX_INTERRUPT_ENABLED && (UART_Rx_Back_RX_ENABLED || UART_Rx_Back_HD_ENABLED))
    /*******************************************************************************
    * Function Name: UART_Rx_Back_RXISR
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
    *  UART_Rx_Back_rxBuffer - RAM buffer pointer for save received data.
    *  UART_Rx_Back_rxBufferWrite - cyclic index for write to rxBuffer,
    *     increments after each byte saved to buffer.
    *  UART_Rx_Back_rxBufferRead - cyclic index for read from rxBuffer,
    *     checked to detect overflow condition.
    *  UART_Rx_Back_rxBufferOverflow - software overflow flag. Set to one
    *     when UART_Rx_Back_rxBufferWrite index overtakes
    *     UART_Rx_Back_rxBufferRead index.
    *  UART_Rx_Back_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when UART_Rx_Back_rxBufferWrite is equal to
    *    UART_Rx_Back_rxBufferRead
    *  UART_Rx_Back_rxAddressMode - this variable contains the Address mode,
    *     selected in customizer or set by UART_SetRxAddressMode() API.
    *  UART_Rx_Back_rxAddressDetected - set to 1 when correct address received,
    *     and analysed to store following addressed data bytes to the buffer.
    *     When not correct address received, set to 0 to skip following data bytes.
    *
    *******************************************************************************/
    CY_ISR(UART_Rx_Back_RXISR)
    {
        uint8 readData;
        uint8 increment_pointer = 0u;

    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

        /* User code required at start of ISR */
        /* `#START UART_Rx_Back_RXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        readData = UART_Rx_Back_RXSTATUS_REG;

        if((readData & (UART_Rx_Back_RX_STS_BREAK | UART_Rx_Back_RX_STS_PAR_ERROR |
                        UART_Rx_Back_RX_STS_STOP_ERROR | UART_Rx_Back_RX_STS_OVERRUN)) != 0u)
        {
            /* ERROR handling. */
            UART_Rx_Back_errorStatus = readData & ( UART_Rx_Back_RX_STS_BREAK | 
                                                        UART_Rx_Back_RX_STS_PAR_ERROR | 
                                                        UART_Rx_Back_RX_STS_STOP_ERROR | 
                                                        UART_Rx_Back_RX_STS_OVERRUN);
            /* `#START UART_Rx_Back_RXISR_ERROR` */

            /* `#END` */
        }

        while((readData & UART_Rx_Back_RX_STS_FIFO_NOTEMPTY) != 0u)
        {
        #if (UART_Rx_Back_RXHW_ADDRESS_ENABLED)
            if(UART_Rx_Back_rxAddressMode == (uint8)UART_Rx_Back__B_UART__AM_SW_DETECT_TO_BUFFER)
            {
                if((readData & UART_Rx_Back_RX_STS_MRKSPC) != 0u)
                {
                    if ((readData & UART_Rx_Back_RX_STS_ADDR_MATCH) != 0u)
                    {
                        UART_Rx_Back_rxAddressDetected = 1u;
                    }
                    else
                    {
                        UART_Rx_Back_rxAddressDetected = 0u;
                    }
                }

                readData = UART_Rx_Back_RXDATA_REG;
                if(UART_Rx_Back_rxAddressDetected != 0u)
                {   /* Store only addressed data */
                    UART_Rx_Back_rxBuffer[UART_Rx_Back_rxBufferWrite] = readData;
                    increment_pointer = 1u;
                }
            }
            else /* Without software addressing */
            {
                UART_Rx_Back_rxBuffer[UART_Rx_Back_rxBufferWrite] = UART_Rx_Back_RXDATA_REG;
                increment_pointer = 1u;
            }
        #else  /* Without addressing */
            UART_Rx_Back_rxBuffer[UART_Rx_Back_rxBufferWrite] = UART_Rx_Back_RXDATA_REG;
            increment_pointer = 1u;
        #endif /* (UART_Rx_Back_RXHW_ADDRESS_ENABLED) */

            /* Do not increment buffer pointer when skip not addressed data */
            if(increment_pointer != 0u)
            {
                if(UART_Rx_Back_rxBufferLoopDetect != 0u)
                {   /* Set Software Buffer status Overflow */
                    UART_Rx_Back_rxBufferOverflow = 1u;
                }
                /* Set next pointer. */
                UART_Rx_Back_rxBufferWrite++;

                /* Check pointer for a loop condition */
                if(UART_Rx_Back_rxBufferWrite >= UART_Rx_Back_RX_BUFFER_SIZE)
                {
                    UART_Rx_Back_rxBufferWrite = 0u;
                }

                /* Detect pre-overload condition and set flag */
                if(UART_Rx_Back_rxBufferWrite == UART_Rx_Back_rxBufferRead)
                {
                    UART_Rx_Back_rxBufferLoopDetect = 1u;
                    /* When Hardware Flow Control selected */
                    #if (UART_Rx_Back_FLOW_CONTROL != 0u)
                        /* Disable RX interrupt mask, it is enabled when user read data from the buffer using APIs */
                        UART_Rx_Back_RXSTATUS_MASK_REG  &= (uint8)~UART_Rx_Back_RX_STS_FIFO_NOTEMPTY;
                        CyIntClearPending(UART_Rx_Back_RX_VECT_NUM);
                        break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                    #endif /* (UART_Rx_Back_FLOW_CONTROL != 0u) */
                }
            }

            /* Read status to decide whether read more bytes */
            readData = UART_Rx_Back_RXSTATUS_REG;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START UART_Rx_Back_RXISR_END` */

        /* `#END` */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
    }

#endif /* (UART_Rx_Back_RX_INTERRUPT_ENABLED && (UART_Rx_Back_RX_ENABLED || UART_Rx_Back_HD_ENABLED)) */


#if (UART_Rx_Back_TX_INTERRUPT_ENABLED && UART_Rx_Back_TX_ENABLED)
    /*******************************************************************************
    * Function Name: UART_Rx_Back_TXISR
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
    *  UART_Rx_Back_txBuffer - RAM buffer pointer for transmit data from.
    *  UART_Rx_Back_txBufferRead - cyclic index for read and transmit data
    *     from txBuffer, increments after each transmitted byte.
    *  UART_Rx_Back_rxBufferWrite - cyclic index for write to txBuffer,
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(UART_Rx_Back_TXISR)
    {
    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

        /* User code required at start of ISR */
        /* `#START UART_Rx_Back_TXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        while((UART_Rx_Back_txBufferRead != UART_Rx_Back_txBufferWrite) &&
             ((UART_Rx_Back_TXSTATUS_REG & UART_Rx_Back_TX_STS_FIFO_FULL) == 0u))
        {
            /* Check pointer wrap around */
            if(UART_Rx_Back_txBufferRead >= UART_Rx_Back_TX_BUFFER_SIZE)
            {
                UART_Rx_Back_txBufferRead = 0u;
            }

            UART_Rx_Back_TXDATA_REG = UART_Rx_Back_txBuffer[UART_Rx_Back_txBufferRead];

            /* Set next pointer */
            UART_Rx_Back_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START UART_Rx_Back_TXISR_END` */

        /* `#END` */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
    }

#endif /* (UART_Rx_Back_TX_INTERRUPT_ENABLED && UART_Rx_Back_TX_ENABLED) */


/* [] END OF FILE */
