/*******************************************************************************
* File Name: Rx_FrontINT.c
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

#include "Rx_Front.h"


/***************************************
* Custom Declarations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */

#if (Rx_Front_RX_INTERRUPT_ENABLED && (Rx_Front_RX_ENABLED || Rx_Front_HD_ENABLED))
    /*******************************************************************************
    * Function Name: Rx_Front_RXISR
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
    *  Rx_Front_rxBuffer - RAM buffer pointer for save received data.
    *  Rx_Front_rxBufferWrite - cyclic index for write to rxBuffer,
    *     increments after each byte saved to buffer.
    *  Rx_Front_rxBufferRead - cyclic index for read from rxBuffer,
    *     checked to detect overflow condition.
    *  Rx_Front_rxBufferOverflow - software overflow flag. Set to one
    *     when Rx_Front_rxBufferWrite index overtakes
    *     Rx_Front_rxBufferRead index.
    *  Rx_Front_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when Rx_Front_rxBufferWrite is equal to
    *    Rx_Front_rxBufferRead
    *  Rx_Front_rxAddressMode - this variable contains the Address mode,
    *     selected in customizer or set by UART_SetRxAddressMode() API.
    *  Rx_Front_rxAddressDetected - set to 1 when correct address received,
    *     and analysed to store following addressed data bytes to the buffer.
    *     When not correct address received, set to 0 to skip following data bytes.
    *
    *******************************************************************************/
    CY_ISR(Rx_Front_RXISR)
    {
        uint8 readData;
        uint8 increment_pointer = 0u;

    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

        /* User code required at start of ISR */
        /* `#START Rx_Front_RXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        readData = Rx_Front_RXSTATUS_REG;

        if((readData & (Rx_Front_RX_STS_BREAK | Rx_Front_RX_STS_PAR_ERROR |
                        Rx_Front_RX_STS_STOP_ERROR | Rx_Front_RX_STS_OVERRUN)) != 0u)
        {
            /* ERROR handling. */
            Rx_Front_errorStatus = readData & ( Rx_Front_RX_STS_BREAK | 
                                                        Rx_Front_RX_STS_PAR_ERROR | 
                                                        Rx_Front_RX_STS_STOP_ERROR | 
                                                        Rx_Front_RX_STS_OVERRUN);
            /* `#START Rx_Front_RXISR_ERROR` */

            /* `#END` */
        }

        while((readData & Rx_Front_RX_STS_FIFO_NOTEMPTY) != 0u)
        {
        #if (Rx_Front_RXHW_ADDRESS_ENABLED)
            if(Rx_Front_rxAddressMode == (uint8)Rx_Front__B_UART__AM_SW_DETECT_TO_BUFFER)
            {
                if((readData & Rx_Front_RX_STS_MRKSPC) != 0u)
                {
                    if ((readData & Rx_Front_RX_STS_ADDR_MATCH) != 0u)
                    {
                        Rx_Front_rxAddressDetected = 1u;
                    }
                    else
                    {
                        Rx_Front_rxAddressDetected = 0u;
                    }
                }

                readData = Rx_Front_RXDATA_REG;
                if(Rx_Front_rxAddressDetected != 0u)
                {   /* Store only addressed data */
                    Rx_Front_rxBuffer[Rx_Front_rxBufferWrite] = readData;
                    increment_pointer = 1u;
                }
            }
            else /* Without software addressing */
            {
                Rx_Front_rxBuffer[Rx_Front_rxBufferWrite] = Rx_Front_RXDATA_REG;
                increment_pointer = 1u;
            }
        #else  /* Without addressing */
            Rx_Front_rxBuffer[Rx_Front_rxBufferWrite] = Rx_Front_RXDATA_REG;
            increment_pointer = 1u;
        #endif /* (Rx_Front_RXHW_ADDRESS_ENABLED) */

            /* Do not increment buffer pointer when skip not addressed data */
            if(increment_pointer != 0u)
            {
                if(Rx_Front_rxBufferLoopDetect != 0u)
                {   /* Set Software Buffer status Overflow */
                    Rx_Front_rxBufferOverflow = 1u;
                }
                /* Set next pointer. */
                Rx_Front_rxBufferWrite++;

                /* Check pointer for a loop condition */
                if(Rx_Front_rxBufferWrite >= Rx_Front_RX_BUFFER_SIZE)
                {
                    Rx_Front_rxBufferWrite = 0u;
                }

                /* Detect pre-overload condition and set flag */
                if(Rx_Front_rxBufferWrite == Rx_Front_rxBufferRead)
                {
                    Rx_Front_rxBufferLoopDetect = 1u;
                    /* When Hardware Flow Control selected */
                    #if (Rx_Front_FLOW_CONTROL != 0u)
                        /* Disable RX interrupt mask, it is enabled when user read data from the buffer using APIs */
                        Rx_Front_RXSTATUS_MASK_REG  &= (uint8)~Rx_Front_RX_STS_FIFO_NOTEMPTY;
                        CyIntClearPending(Rx_Front_RX_VECT_NUM);
                        break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                    #endif /* (Rx_Front_FLOW_CONTROL != 0u) */
                }
            }

            /* Read status to decide whether read more bytes */
            readData = Rx_Front_RXSTATUS_REG;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START Rx_Front_RXISR_END` */

        /* `#END` */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
    }

#endif /* (Rx_Front_RX_INTERRUPT_ENABLED && (Rx_Front_RX_ENABLED || Rx_Front_HD_ENABLED)) */


#if (Rx_Front_TX_INTERRUPT_ENABLED && Rx_Front_TX_ENABLED)
    /*******************************************************************************
    * Function Name: Rx_Front_TXISR
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
    *  Rx_Front_txBuffer - RAM buffer pointer for transmit data from.
    *  Rx_Front_txBufferRead - cyclic index for read and transmit data
    *     from txBuffer, increments after each transmitted byte.
    *  Rx_Front_rxBufferWrite - cyclic index for write to txBuffer,
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(Rx_Front_TXISR)
    {
    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

        /* User code required at start of ISR */
        /* `#START Rx_Front_TXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        while((Rx_Front_txBufferRead != Rx_Front_txBufferWrite) &&
             ((Rx_Front_TXSTATUS_REG & Rx_Front_TX_STS_FIFO_FULL) == 0u))
        {
            /* Check pointer wrap around */
            if(Rx_Front_txBufferRead >= Rx_Front_TX_BUFFER_SIZE)
            {
                Rx_Front_txBufferRead = 0u;
            }

            Rx_Front_TXDATA_REG = Rx_Front_txBuffer[Rx_Front_txBufferRead];

            /* Set next pointer */
            Rx_Front_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START Rx_Front_TXISR_END` */

        /* `#END` */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
    }

#endif /* (Rx_Front_TX_INTERRUPT_ENABLED && Rx_Front_TX_ENABLED) */


/* [] END OF FILE */
