/*******************************************************************************
* File Name: Rx_LeftINT.c
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

#include "Rx_Left.h"


/***************************************
* Custom Declarations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */

#if (Rx_Left_RX_INTERRUPT_ENABLED && (Rx_Left_RX_ENABLED || Rx_Left_HD_ENABLED))
    /*******************************************************************************
    * Function Name: Rx_Left_RXISR
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
    *  Rx_Left_rxBuffer - RAM buffer pointer for save received data.
    *  Rx_Left_rxBufferWrite - cyclic index for write to rxBuffer,
    *     increments after each byte saved to buffer.
    *  Rx_Left_rxBufferRead - cyclic index for read from rxBuffer,
    *     checked to detect overflow condition.
    *  Rx_Left_rxBufferOverflow - software overflow flag. Set to one
    *     when Rx_Left_rxBufferWrite index overtakes
    *     Rx_Left_rxBufferRead index.
    *  Rx_Left_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when Rx_Left_rxBufferWrite is equal to
    *    Rx_Left_rxBufferRead
    *  Rx_Left_rxAddressMode - this variable contains the Address mode,
    *     selected in customizer or set by UART_SetRxAddressMode() API.
    *  Rx_Left_rxAddressDetected - set to 1 when correct address received,
    *     and analysed to store following addressed data bytes to the buffer.
    *     When not correct address received, set to 0 to skip following data bytes.
    *
    *******************************************************************************/
    CY_ISR(Rx_Left_RXISR)
    {
        uint8 readData;
        uint8 increment_pointer = 0u;

    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

        /* User code required at start of ISR */
        /* `#START Rx_Left_RXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        readData = Rx_Left_RXSTATUS_REG;

        if((readData & (Rx_Left_RX_STS_BREAK | Rx_Left_RX_STS_PAR_ERROR |
                        Rx_Left_RX_STS_STOP_ERROR | Rx_Left_RX_STS_OVERRUN)) != 0u)
        {
            /* ERROR handling. */
            Rx_Left_errorStatus = readData & ( Rx_Left_RX_STS_BREAK | 
                                                        Rx_Left_RX_STS_PAR_ERROR | 
                                                        Rx_Left_RX_STS_STOP_ERROR | 
                                                        Rx_Left_RX_STS_OVERRUN);
            /* `#START Rx_Left_RXISR_ERROR` */

            /* `#END` */
        }

        while((readData & Rx_Left_RX_STS_FIFO_NOTEMPTY) != 0u)
        {
        #if (Rx_Left_RXHW_ADDRESS_ENABLED)
            if(Rx_Left_rxAddressMode == (uint8)Rx_Left__B_UART__AM_SW_DETECT_TO_BUFFER)
            {
                if((readData & Rx_Left_RX_STS_MRKSPC) != 0u)
                {
                    if ((readData & Rx_Left_RX_STS_ADDR_MATCH) != 0u)
                    {
                        Rx_Left_rxAddressDetected = 1u;
                    }
                    else
                    {
                        Rx_Left_rxAddressDetected = 0u;
                    }
                }

                readData = Rx_Left_RXDATA_REG;
                if(Rx_Left_rxAddressDetected != 0u)
                {   /* Store only addressed data */
                    Rx_Left_rxBuffer[Rx_Left_rxBufferWrite] = readData;
                    increment_pointer = 1u;
                }
            }
            else /* Without software addressing */
            {
                Rx_Left_rxBuffer[Rx_Left_rxBufferWrite] = Rx_Left_RXDATA_REG;
                increment_pointer = 1u;
            }
        #else  /* Without addressing */
            Rx_Left_rxBuffer[Rx_Left_rxBufferWrite] = Rx_Left_RXDATA_REG;
            increment_pointer = 1u;
        #endif /* (Rx_Left_RXHW_ADDRESS_ENABLED) */

            /* Do not increment buffer pointer when skip not addressed data */
            if(increment_pointer != 0u)
            {
                if(Rx_Left_rxBufferLoopDetect != 0u)
                {   /* Set Software Buffer status Overflow */
                    Rx_Left_rxBufferOverflow = 1u;
                }
                /* Set next pointer. */
                Rx_Left_rxBufferWrite++;

                /* Check pointer for a loop condition */
                if(Rx_Left_rxBufferWrite >= Rx_Left_RX_BUFFER_SIZE)
                {
                    Rx_Left_rxBufferWrite = 0u;
                }

                /* Detect pre-overload condition and set flag */
                if(Rx_Left_rxBufferWrite == Rx_Left_rxBufferRead)
                {
                    Rx_Left_rxBufferLoopDetect = 1u;
                    /* When Hardware Flow Control selected */
                    #if (Rx_Left_FLOW_CONTROL != 0u)
                        /* Disable RX interrupt mask, it is enabled when user read data from the buffer using APIs */
                        Rx_Left_RXSTATUS_MASK_REG  &= (uint8)~Rx_Left_RX_STS_FIFO_NOTEMPTY;
                        CyIntClearPending(Rx_Left_RX_VECT_NUM);
                        break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                    #endif /* (Rx_Left_FLOW_CONTROL != 0u) */
                }
            }

            /* Read status to decide whether read more bytes */
            readData = Rx_Left_RXSTATUS_REG;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START Rx_Left_RXISR_END` */

        /* `#END` */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
    }

#endif /* (Rx_Left_RX_INTERRUPT_ENABLED && (Rx_Left_RX_ENABLED || Rx_Left_HD_ENABLED)) */


#if (Rx_Left_TX_INTERRUPT_ENABLED && Rx_Left_TX_ENABLED)
    /*******************************************************************************
    * Function Name: Rx_Left_TXISR
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
    *  Rx_Left_txBuffer - RAM buffer pointer for transmit data from.
    *  Rx_Left_txBufferRead - cyclic index for read and transmit data
    *     from txBuffer, increments after each transmitted byte.
    *  Rx_Left_rxBufferWrite - cyclic index for write to txBuffer,
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(Rx_Left_TXISR)
    {
    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

        /* User code required at start of ISR */
        /* `#START Rx_Left_TXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        while((Rx_Left_txBufferRead != Rx_Left_txBufferWrite) &&
             ((Rx_Left_TXSTATUS_REG & Rx_Left_TX_STS_FIFO_FULL) == 0u))
        {
            /* Check pointer wrap around */
            if(Rx_Left_txBufferRead >= Rx_Left_TX_BUFFER_SIZE)
            {
                Rx_Left_txBufferRead = 0u;
            }

            Rx_Left_TXDATA_REG = Rx_Left_txBuffer[Rx_Left_txBufferRead];

            /* Set next pointer */
            Rx_Left_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START Rx_Left_TXISR_END` */

        /* `#END` */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
    }

#endif /* (Rx_Left_TX_INTERRUPT_ENABLED && Rx_Left_TX_ENABLED) */


/* [] END OF FILE */
