/*******************************************************************************
* File Name: Rx_Right_SPI_UART.c
* Version 2.0
*
* Description:
*  This file provides the source code to the API for the SCB Component in
*  SPI and UART modes.
*
* Note:
*
*******************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Rx_Right_PVT.h"
#include "Rx_Right_SPI_UART_PVT.h"

/***************************************
*        SPI/UART Private Vars
***************************************/

#if(Rx_Right_INTERNAL_RX_SW_BUFFER_CONST)
    volatile uint32 Rx_Right_rxBufferHead;
    volatile uint32 Rx_Right_rxBufferTail;
    volatile uint8  Rx_Right_rxBufferOverflow;
#endif /* (Rx_Right_INTERNAL_RX_SW_BUFFER_CONST) */

#if(Rx_Right_INTERNAL_TX_SW_BUFFER_CONST)
    volatile uint32 Rx_Right_txBufferHead;
    volatile uint32 Rx_Right_txBufferTail;
#endif /* (Rx_Right_INTERNAL_TX_SW_BUFFER_CONST) */

#if(Rx_Right_INTERNAL_RX_SW_BUFFER)
    /* Add one element to the buffer to receive full packet. One byte in receive buffer is always empty */
    volatile uint8 Rx_Right_rxBufferInternal[Rx_Right_RX_BUFFER_SIZE];
#endif /* (Rx_Right_INTERNAL_RX_SW_BUFFER) */

#if(Rx_Right_INTERNAL_TX_SW_BUFFER)
    volatile uint8 Rx_Right_txBufferInternal[Rx_Right_TX_BUFFER_SIZE];
#endif /* (Rx_Right_INTERNAL_TX_SW_BUFFER) */


#if(Rx_Right_RX_DIRECTION)

    /*******************************************************************************
    * Function Name: Rx_Right_SpiUartReadRxData
    ********************************************************************************
    *
    * Summary:
    *  Retrieves the next data element from the receive buffer.
    *   - RX software buffer is disabled: Returns data element retrieved from
    *     RX FIFO. Undefined data will be returned if the RX FIFO is empty.
    *   - RX software buffer is enabled: Returns data element from the software
    *     receive buffer. Zero value is returned if the software receive buffer
    *     is empty.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Next data element from the receive buffer.
    *
    * Global Variables:
    *  Look into Rx_Right_SpiInit for description.
    *
    *******************************************************************************/
    uint32 Rx_Right_SpiUartReadRxData(void)
    {
        uint32 rxData = 0u;

        #if(Rx_Right_INTERNAL_RX_SW_BUFFER_CONST)
            uint32 locTail;
        #endif /* (Rx_Right_INTERNAL_RX_SW_BUFFER_CONST) */

        #if(Rx_Right_CHECK_RX_SW_BUFFER)
        {
            if(Rx_Right_rxBufferHead != Rx_Right_rxBufferTail)
            {
                /* There is data in RX software buffer */

                /* Calculate index to read from */
                locTail = (Rx_Right_rxBufferTail + 1u);

                if(Rx_Right_RX_BUFFER_SIZE == locTail)
                {
                    locTail = 0u;
                }

                /* Get data from RX software buffer */
                rxData = Rx_Right_GetWordFromRxBuffer(locTail);

                /* Change index in the buffer */
                Rx_Right_rxBufferTail = locTail;
            }
        }
        #else
        {
            rxData = Rx_Right_RX_FIFO_RD_REG; /* Read data from RX FIFO */
        }
        #endif

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: Rx_Right_SpiUartGetRxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of received data elements in the receive buffer.
    *   - RX software buffer disabled: returns the number of used entries in
    *     RX FIFO.
    *   - RX software buffer enabled: returns the number of elements which were
    *     placed in the receive buffer. This does not include the hardware RX FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Number of received data elements
    *
    *******************************************************************************/
    uint32 Rx_Right_SpiUartGetRxBufferSize(void)
    {
        uint32 size;
        #if(Rx_Right_INTERNAL_RX_SW_BUFFER_CONST)
            uint32 locHead;
        #endif /* (Rx_Right_INTERNAL_RX_SW_BUFFER_CONST) */

        #if(Rx_Right_CHECK_RX_SW_BUFFER)
        {
            locHead = Rx_Right_rxBufferHead;

            if(locHead >= Rx_Right_rxBufferTail)
            {
                size = (locHead - Rx_Right_rxBufferTail);
            }
            else
            {
                size = (locHead + (Rx_Right_RX_BUFFER_SIZE - Rx_Right_rxBufferTail));
            }
        }
        #else
        {
            size = Rx_Right_GET_RX_FIFO_ENTRIES;
        }
        #endif

        return(size);
    }


    /*******************************************************************************
    * Function Name: Rx_Right_SpiUartClearRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the receive buffer and RX FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void Rx_Right_SpiUartClearRxBuffer(void)
    {
        #if(Rx_Right_INTERNAL_RX_SW_BUFFER_CONST)
            uint32 intSourceMask;
        #endif /* (Rx_Right_INTERNAL_RX_SW_BUFFER_CONST) */

        #if(Rx_Right_CHECK_RX_SW_BUFFER)
        {
            intSourceMask = Rx_Right_SpiUartDisableIntRx();

            Rx_Right_CLEAR_RX_FIFO;

            /* Flush RX software buffer */
            Rx_Right_rxBufferHead     = Rx_Right_rxBufferTail;
            Rx_Right_rxBufferOverflow = 0u;

            /* End RX transfer */
            Rx_Right_ClearRxInterruptSource(Rx_Right_INTR_RX_ALL);

            Rx_Right_SpiUartEnableIntRx(intSourceMask);
        }
        #else
        {
            Rx_Right_CLEAR_RX_FIFO;
        }
        #endif
    }

#endif /* (Rx_Right_RX_DIRECTION) */


#if(Rx_Right_TX_DIRECTION)

    /*******************************************************************************
    * Function Name: Rx_Right_SpiUartWriteTxData
    ********************************************************************************
    *
    * Summary:
    *  Places a data entry into the transmit buffer to be sent at the next available
    *  bus time.
    *  This function is blocking and waits until there is space available to put the
    *  requested data in the transmit buffer.
    *
    * Parameters:
    *  txDataByte: the data to be transmitted.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void Rx_Right_SpiUartWriteTxData(uint32 txData)
    {
        #if(Rx_Right_INTERNAL_TX_SW_BUFFER_CONST)
            uint32 locHead;
            uint32 intSourceMask;
        #endif /* (Rx_Right_INTERNAL_TX_SW_BUFFER_CONST) */

        #if(Rx_Right_CHECK_TX_SW_BUFFER)
        {
            /* Head index to put data */
            locHead = (Rx_Right_txBufferHead + 1u);

            /* Adjust TX software buffer index */
            if(Rx_Right_TX_BUFFER_SIZE == locHead)
            {
                locHead = 0u;
            }

            while(locHead == Rx_Right_txBufferTail)
            {
                /* Wait for space in TX software buffer */
            }

            /* TX software buffer has at least one room */

            if((Rx_Right_txBufferHead == Rx_Right_txBufferTail) &&
               (Rx_Right_SPI_UART_FIFO_SIZE != Rx_Right_GET_TX_FIFO_ENTRIES))
            {
                /* TX software buffer is empty: put data directly in TX FIFO */
                Rx_Right_TX_FIFO_WR_REG = txData;
            }
            /* Put data in TX software buffer */
            else
            {
                /* Clear old status of INTR_TX_NOT_FULL. It sets at the end of transfer when TX FIFO is empty. */
                Rx_Right_ClearTxInterruptSource(Rx_Right_INTR_TX_NOT_FULL);

                Rx_Right_PutWordInTxBuffer(locHead, txData);

                Rx_Right_txBufferHead = locHead;

                /* Enable interrupt to transmit */
                intSourceMask  = Rx_Right_INTR_TX_NOT_FULL;
                intSourceMask |= Rx_Right_GetTxInterruptMode();
                Rx_Right_SpiUartEnableIntTx(intSourceMask);
            }
        }
        #else
        {
            while(Rx_Right_SPI_UART_FIFO_SIZE == Rx_Right_GET_TX_FIFO_ENTRIES)
            {
                /* Block while TX FIFO is FULL */
            }

            Rx_Right_TX_FIFO_WR_REG = txData;
        }
        #endif
    }


    /*******************************************************************************
    * Function Name: Rx_Right_SpiUartPutArray
    ********************************************************************************
    *
    * Summary:
    *  Places an array of data into the transmit buffer to be sent.
    *  This function is blocking and waits until there is a space available to put
    *  all the requested data in the transmit buffer. The array size can be greater
    *  than transmit buffer size.
    *
    * Parameters:
    *  wrBuf:  pointer to an array with data to be placed in transmit buffer.
    *  count:  number of data elements to be placed in the transmit buffer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void Rx_Right_SpiUartPutArray(const uint8 wrBuf[], uint32 count)
    {
        uint32 i;

        for(i=0u; i < count; i++)
        {
            Rx_Right_SpiUartWriteTxData((uint32) wrBuf[i]);
        }
    }


    /*******************************************************************************
    * Function Name: Rx_Right_SpiUartGetTxBufferSize
    ********************************************************************************
    *
    * Summary:
    * Returns the number of elements currently in the transmit buffer.
    *  - TX software buffer is disabled: returns the number of used entries in
    *    TX FIFO.
    *  - TX software buffer is enabled: returns the number of elements currently
    *    used in the transmit buffer. This number does not include used entries in
    *    the TX FIFO. The transmit buffer size is zero until the TX FIFO is
    *    not full.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Number of data elements ready to transmit.
    *
    *******************************************************************************/
    uint32 Rx_Right_SpiUartGetTxBufferSize(void)
    {
        uint32 size;
        #if(Rx_Right_INTERNAL_TX_SW_BUFFER_CONST)
            uint32 locTail;
        #endif /* (Rx_Right_INTERNAL_TX_SW_BUFFER_CONST) */

        #if(Rx_Right_CHECK_TX_SW_BUFFER)
        {
            /* Get current Tail index */
            locTail = Rx_Right_txBufferTail;

            if(Rx_Right_txBufferHead >= locTail)
            {
                size = (Rx_Right_txBufferHead - locTail);
            }
            else
            {
                size = (Rx_Right_txBufferHead + (Rx_Right_TX_BUFFER_SIZE - locTail));
            }
        }
        #else
        {
            size = Rx_Right_GET_TX_FIFO_ENTRIES;
        }
        #endif

        return(size);
    }


    /*******************************************************************************
    * Function Name: Rx_Right_SpiUartClearTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the transmit buffer and TX FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void Rx_Right_SpiUartClearTxBuffer(void)
    {
        #if(Rx_Right_INTERNAL_TX_SW_BUFFER_CONST)
            uint32 intSourceMask;
        #endif /* (Rx_Right_INTERNAL_TX_SW_BUFFER_CONST) */

        #if(Rx_Right_CHECK_TX_SW_BUFFER)
        {
            intSourceMask = Rx_Right_SpiUartDisableIntTx();

            Rx_Right_CLEAR_TX_FIFO;

            /* Flush TX software buffer */
            Rx_Right_txBufferHead = Rx_Right_txBufferTail;

            /* End TX transfer if it is in progress */
            intSourceMask &= (uint32) ~Rx_Right_INTR_TX_NOT_FULL;

            Rx_Right_SpiUartEnableIntTx(intSourceMask);
        }
        #else
        {
            Rx_Right_CLEAR_TX_FIFO;
        }
        #endif
    }

#endif /* (Rx_Right_TX_DIRECTION) */


/*******************************************************************************
* Function Name: Rx_Right_SpiUartDisableIntRx
********************************************************************************
*
* Summary:
*  Disables the RX interrupt sources.
*
* Parameters:
*  None
*
* Return:
*  Returns the RX interrupt sources enabled before the function call.
*
*******************************************************************************/
uint32 Rx_Right_SpiUartDisableIntRx(void)
{
    uint32 intSource;

    intSource = Rx_Right_GetRxInterruptMode();

    Rx_Right_SetRxInterruptMode(Rx_Right_NO_INTR_SOURCES);

    return(intSource);
}


/*******************************************************************************
* Function Name: Rx_Right_SpiUartDisableIntTx
********************************************************************************
*
* Summary:
*  Disables TX interrupt sources.
*
* Parameters:
*  None
*
* Return:
*  Returns TX interrupt sources enabled before function call.
*
*******************************************************************************/
uint32 Rx_Right_SpiUartDisableIntTx(void)
{
    uint32 intSourceMask;

    intSourceMask = Rx_Right_GetTxInterruptMode();

    Rx_Right_SetTxInterruptMode(Rx_Right_NO_INTR_SOURCES);

    return(intSourceMask);
}


#if(Rx_Right_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: Rx_Right_PutWordInRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Stores a byte/word into the RX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    * Parameters:
    *  index:      index to store data byte/word in the RX buffer.
    *  rxDataByte: byte/word to store.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void Rx_Right_PutWordInRxBuffer(uint32 idx, uint32 rxDataByte)
    {
        /* Put data in buffer */
        if(Rx_Right_ONE_BYTE_WIDTH == Rx_Right_rxDataBits)
        {
            Rx_Right_rxBuffer[idx] = ((uint8) rxDataByte);
        }
        else
        {
            Rx_Right_rxBuffer[(uint32)(idx << 1u)]      = LO8(LO16(rxDataByte));
            Rx_Right_rxBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(rxDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: Rx_Right_GetWordFromRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Reads byte/word from RX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Returns byte/word read from RX buffer.
    *
    *******************************************************************************/
    uint32 Rx_Right_GetWordFromRxBuffer(uint32 idx)
    {
        uint32 value;

        if(Rx_Right_ONE_BYTE_WIDTH == Rx_Right_rxDataBits)
        {
            value = Rx_Right_rxBuffer[idx];
        }
        else
        {
            value  = (uint32) Rx_Right_rxBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32)Rx_Right_rxBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return(value);
    }


    /*******************************************************************************
    * Function Name: Rx_Right_PutWordInTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Stores byte/word into the TX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    * Parameters:
    *  idx:        index to store data byte/word in the TX buffer.
    *  txDataByte: byte/word to store.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void Rx_Right_PutWordInTxBuffer(uint32 idx, uint32 txDataByte)
    {
        /* Put data in buffer */
        if(Rx_Right_ONE_BYTE_WIDTH == Rx_Right_txDataBits)
        {
            Rx_Right_txBuffer[idx] = ((uint8) txDataByte);
        }
        else
        {
            Rx_Right_txBuffer[(uint32)(idx << 1u)]      = LO8(LO16(txDataByte));
            Rx_Right_txBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(txDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: Rx_Right_GetWordFromTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Reads byte/word from the TX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    * Parameters:
    *  idx: index to get data byte/word from the TX buffer.
    *
    * Return:
    *  Returns byte/word read from the TX buffer.
    *
    *******************************************************************************/
    uint32 Rx_Right_GetWordFromTxBuffer(uint32 idx)
    {
        uint32 value;

        if(Rx_Right_ONE_BYTE_WIDTH == Rx_Right_txDataBits)
        {
            value = (uint32) Rx_Right_txBuffer[idx];
        }
        else
        {
            value  = (uint32) Rx_Right_txBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32) Rx_Right_txBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return(value);
    }

#endif /* (Rx_Right_SCB_MODE_UNCONFIG_CONST_CFG) */


/* [] END OF FILE */
