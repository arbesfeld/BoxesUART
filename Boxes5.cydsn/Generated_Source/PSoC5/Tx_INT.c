/*******************************************************************************
* File Name: TxINT.c
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

#include "Tx.h"


/***************************************
* Custom Declarations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */

#if (Tx_RX_INTERRUPT_ENABLED && (Tx_RX_ENABLED || Tx_HD_ENABLED))
    /*******************************************************************************
    * Function Name: Tx_RXISR
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
    *  Tx_rxBuffer - RAM buffer pointer for save received data.
    *  Tx_rxBufferWrite - cyclic index for write to rxBuffer,
    *     increments after each byte saved to buffer.
    *  Tx_rxBufferRead - cyclic index for read from rxBuffer,
    *     checked to detect overflow condition.
    *  Tx_rxBufferOverflow - software overflow flag. Set to one
    *     when Tx_rxBufferWrite index overtakes
    *     Tx_rxBufferRead index.
    *  Tx_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when Tx_rxBufferWrite is equal to
    *    Tx_rxBufferRead
    *  Tx_rxAddressMode - this variable contains the Address mode,
    *     selected in customizer or set by UART_SetRxAddressMode() API.
    *  Tx_rxAddressDetected - set to 1 when correct address received,
    *     and analysed to store following addressed data bytes to the buffer.
    *     When not correct address received, set to 0 to skip following data bytes.
    *
    *******************************************************************************/
    CY_ISR(Tx_RXISR)
    {
        uint8 readData;
        uint8 increment_pointer = 0u;

    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

        /* User code required at start of ISR */
        /* `#START Tx_RXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        readData = Tx_RXSTATUS_REG;

        if((readData & (Tx_RX_STS_BREAK | Tx_RX_STS_PAR_ERROR |
                        Tx_RX_STS_STOP_ERROR | Tx_RX_STS_OVERRUN)) != 0u)
        {
            /* ERROR handling. */
            Tx_errorStatus = readData & ( Tx_RX_STS_BREAK | 
                                                        Tx_RX_STS_PAR_ERROR | 
                                                        Tx_RX_STS_STOP_ERROR | 
                                                        Tx_RX_STS_OVERRUN);
            /* `#START Tx_RXISR_ERROR` */

            /* `#END` */
        }

        while((readData & Tx_RX_STS_FIFO_NOTEMPTY) != 0u)
        {
        #if (Tx_RXHW_ADDRESS_ENABLED)
            if(Tx_rxAddressMode == (uint8)Tx__B_UART__AM_SW_DETECT_TO_BUFFER)
            {
                if((readData & Tx_RX_STS_MRKSPC) != 0u)
                {
                    if ((readData & Tx_RX_STS_ADDR_MATCH) != 0u)
                    {
                        Tx_rxAddressDetected = 1u;
                    }
                    else
                    {
                        Tx_rxAddressDetected = 0u;
                    }
                }

                readData = Tx_RXDATA_REG;
                if(Tx_rxAddressDetected != 0u)
                {   /* Store only addressed data */
                    Tx_rxBuffer[Tx_rxBufferWrite] = readData;
                    increment_pointer = 1u;
                }
            }
            else /* Without software addressing */
            {
                Tx_rxBuffer[Tx_rxBufferWrite] = Tx_RXDATA_REG;
                increment_pointer = 1u;
            }
        #else  /* Without addressing */
            Tx_rxBuffer[Tx_rxBufferWrite] = Tx_RXDATA_REG;
            increment_pointer = 1u;
        #endif /* (Tx_RXHW_ADDRESS_ENABLED) */

            /* Do not increment buffer pointer when skip not addressed data */
            if(increment_pointer != 0u)
            {
                if(Tx_rxBufferLoopDetect != 0u)
                {   /* Set Software Buffer status Overflow */
                    Tx_rxBufferOverflow = 1u;
                }
                /* Set next pointer. */
                Tx_rxBufferWrite++;

                /* Check pointer for a loop condition */
                if(Tx_rxBufferWrite >= Tx_RX_BUFFER_SIZE)
                {
                    Tx_rxBufferWrite = 0u;
                }

                /* Detect pre-overload condition and set flag */
                if(Tx_rxBufferWrite == Tx_rxBufferRead)
                {
                    Tx_rxBufferLoopDetect = 1u;
                    /* When Hardware Flow Control selected */
                    #if (Tx_FLOW_CONTROL != 0u)
                        /* Disable RX interrupt mask, it is enabled when user read data from the buffer using APIs */
                        Tx_RXSTATUS_MASK_REG  &= (uint8)~Tx_RX_STS_FIFO_NOTEMPTY;
                        CyIntClearPending(Tx_RX_VECT_NUM);
                        break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                    #endif /* (Tx_FLOW_CONTROL != 0u) */
                }
            }

            /* Read status to decide whether read more bytes */
            readData = Tx_RXSTATUS_REG;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START Tx_RXISR_END` */

        /* `#END` */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
    }

#endif /* (Tx_RX_INTERRUPT_ENABLED && (Tx_RX_ENABLED || Tx_HD_ENABLED)) */


#if (Tx_TX_INTERRUPT_ENABLED && Tx_TX_ENABLED)
    /*******************************************************************************
    * Function Name: Tx_TXISR
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
    *  Tx_txBuffer - RAM buffer pointer for transmit data from.
    *  Tx_txBufferRead - cyclic index for read and transmit data
    *     from txBuffer, increments after each transmitted byte.
    *  Tx_rxBufferWrite - cyclic index for write to txBuffer,
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(Tx_TXISR)
    {
    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

        /* User code required at start of ISR */
        /* `#START Tx_TXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        while((Tx_txBufferRead != Tx_txBufferWrite) &&
             ((Tx_TXSTATUS_REG & Tx_TX_STS_FIFO_FULL) == 0u))
        {
            /* Check pointer wrap around */
            if(Tx_txBufferRead >= Tx_TX_BUFFER_SIZE)
            {
                Tx_txBufferRead = 0u;
            }

            Tx_TXDATA_REG = Tx_txBuffer[Tx_txBufferRead];

            /* Set next pointer */
            Tx_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START Tx_TXISR_END` */

        /* `#END` */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
    }

#endif /* (Tx_TX_INTERRUPT_ENABLED && Tx_TX_ENABLED) */


/* [] END OF FILE */
