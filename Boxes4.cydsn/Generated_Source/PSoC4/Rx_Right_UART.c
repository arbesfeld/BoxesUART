/*******************************************************************************
* File Name: Rx_Right_UART.c
* Version 2.0
*
* Description:
*  This file provides the source code to the API for the SCB Component in
*  UART mode.
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


#if(Rx_Right_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    const Rx_Right_UART_INIT_STRUCT Rx_Right_configUart =
    {
        Rx_Right_UART_SUB_MODE,
        Rx_Right_UART_DIRECTION,
        Rx_Right_UART_DATA_BITS_NUM,
        Rx_Right_UART_PARITY_TYPE,
        Rx_Right_UART_STOP_BITS_NUM,
        Rx_Right_UART_OVS_FACTOR,
        Rx_Right_UART_IRDA_LOW_POWER,
        Rx_Right_UART_MEDIAN_FILTER_ENABLE,
        Rx_Right_UART_RETRY_ON_NACK,
        Rx_Right_UART_IRDA_POLARITY,
        Rx_Right_UART_DROP_ON_PARITY_ERR,
        Rx_Right_UART_DROP_ON_FRAME_ERR,
        Rx_Right_UART_WAKE_ENABLE,
        0u,
        NULL,
        0u,
        NULL,
        Rx_Right_UART_MP_MODE_ENABLE,
        Rx_Right_UART_MP_ACCEPT_ADDRESS,
        Rx_Right_UART_MP_RX_ADDRESS,
        Rx_Right_UART_MP_RX_ADDRESS_MASK,
        (uint32) Rx_Right_SCB_IRQ_INTERNAL,
        Rx_Right_UART_INTR_RX_MASK,
        Rx_Right_UART_RX_TRIGGER_LEVEL,
        Rx_Right_UART_INTR_TX_MASK,
        Rx_Right_UART_TX_TRIGGER_LEVEL,
        (uint8) Rx_Right_UART_BYTE_MODE_ENABLE,
        (uint8) Rx_Right_UART_CTS_ENABLE,
        (uint8) Rx_Right_UART_CTS_POLARITY,
        (uint8) Rx_Right_UART_RTS_POLARITY,
        (uint8) Rx_Right_UART_RTS_FIFO_LEVEL
    };


    /*******************************************************************************
    * Function Name: Rx_Right_UartInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for the UART operation.
    *
    * Parameters:
    *  config:  Pointer to a structure that contains the following ordered list of
    *           fields. These fields match the selections available in the
    *           customizer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void Rx_Right_UartInit(const Rx_Right_UART_INIT_STRUCT *config)
    {
        uint32 pinsConfig;

        if(NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to bad function parameter */
        }
        else
        {
            /* Get direction to configure UART pins: TX, RX or TX+RX */
            pinsConfig  = config->direction;

        #if !(Rx_Right_CY_SCBIP_V0 || Rx_Right_CY_SCBIP_V1)
            /* Add RTS and CTS pins to configure */
            pinsConfig |= (0u != config->rtsRxFifoLevel) ? (Rx_Right_UART_RTS_PIN_ENABLE) : (0u);
            pinsConfig |= (0u != config->enableCts)         ? (Rx_Right_UART_CTS_PIN_ENABLE) : (0u);
        #endif /* !(Rx_Right_CY_SCBIP_V0 || Rx_Right_CY_SCBIP_V1) */

            /* Configure pins */
            Rx_Right_SetPins(Rx_Right_SCB_MODE_UART, config->mode, pinsConfig);

            /* Store internal configuration */
            Rx_Right_scbMode       = (uint8) Rx_Right_SCB_MODE_UART;
            Rx_Right_scbEnableWake = (uint8) config->enableWake;
            Rx_Right_scbEnableIntr = (uint8) config->enableInterrupt;

            /* Set RX direction internal variables */
            Rx_Right_rxBuffer      =         config->rxBuffer;
            Rx_Right_rxDataBits    = (uint8) config->dataBits;
            Rx_Right_rxBufferSize  = (uint8) config->rxBufferSize;

            /* Set TX direction internal variables */
            Rx_Right_txBuffer      =         config->txBuffer;
            Rx_Right_txDataBits    = (uint8) config->dataBits;
            Rx_Right_txBufferSize  = (uint8) config->txBufferSize;

            /* Configure UART interface */
            if(Rx_Right_UART_MODE_IRDA == config->mode)
            {
                /* OVS settings: IrDA */
                Rx_Right_CTRL_REG  = ((0u != config->enableIrdaLowPower) ?
                                                (Rx_Right_UART_GET_CTRL_OVS_IRDA_LP(config->oversample)) :
                                                (Rx_Right_CTRL_OVS_IRDA_OVS16));
            }
            else
            {
                /* OVS settings: UART and SmartCard */
                Rx_Right_CTRL_REG  = Rx_Right_GET_CTRL_OVS(config->oversample);
            }

            Rx_Right_CTRL_REG     |= Rx_Right_GET_CTRL_BYTE_MODE  (config->enableByteMode)      |
                                             Rx_Right_GET_CTRL_ADDR_ACCEPT(config->multiprocAcceptAddr) |
                                             Rx_Right_CTRL_UART;

            /* Configure sub-mode: UART, SmartCard or IrDA */
            Rx_Right_UART_CTRL_REG = Rx_Right_GET_UART_CTRL_MODE(config->mode);

            /* Configure RX direction */
            Rx_Right_UART_RX_CTRL_REG = Rx_Right_GET_UART_RX_CTRL_MODE(config->stopBits)              |
                                        Rx_Right_GET_UART_RX_CTRL_POLARITY(config->enableInvertedRx)          |
                                        Rx_Right_GET_UART_RX_CTRL_MP_MODE(config->enableMultiproc)            |
                                        Rx_Right_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(config->dropOnParityErr) |
                                        Rx_Right_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(config->dropOnFrameErr);

            if(Rx_Right_UART_PARITY_NONE != config->parity)
            {
               Rx_Right_UART_RX_CTRL_REG |= Rx_Right_GET_UART_RX_CTRL_PARITY(config->parity) |
                                                    Rx_Right_UART_RX_CTRL_PARITY_ENABLED;
            }

            Rx_Right_RX_CTRL_REG      = Rx_Right_GET_RX_CTRL_DATA_WIDTH(config->dataBits)       |
                                                Rx_Right_GET_RX_CTRL_MEDIAN(config->enableMedianFilter) |
                                                Rx_Right_GET_UART_RX_CTRL_ENABLED(config->direction);

            Rx_Right_RX_FIFO_CTRL_REG = Rx_Right_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(config->rxTriggerLevel);

            /* Configure MP address */
            Rx_Right_RX_MATCH_REG     = Rx_Right_GET_RX_MATCH_ADDR(config->multiprocAddr) |
                                                Rx_Right_GET_RX_MATCH_MASK(config->multiprocAddrMask);

            /* Configure RX direction */
            Rx_Right_UART_TX_CTRL_REG = Rx_Right_GET_UART_TX_CTRL_MODE(config->stopBits) |
                                                Rx_Right_GET_UART_TX_CTRL_RETRY_NACK(config->enableRetryNack);

            if(Rx_Right_UART_PARITY_NONE != config->parity)
            {
               Rx_Right_UART_TX_CTRL_REG |= Rx_Right_GET_UART_TX_CTRL_PARITY(config->parity) |
                                                    Rx_Right_UART_TX_CTRL_PARITY_ENABLED;
            }

            Rx_Right_TX_CTRL_REG      = Rx_Right_GET_TX_CTRL_DATA_WIDTH(config->dataBits)    |
                                                Rx_Right_GET_UART_TX_CTRL_ENABLED(config->direction);

            Rx_Right_TX_FIFO_CTRL_REG = Rx_Right_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(config->txTriggerLevel);

        #if !(Rx_Right_CY_SCBIP_V0 || Rx_Right_CY_SCBIP_V1)
            Rx_Right_UART_FLOW_CTRL_REG = Rx_Right_GET_UART_FLOW_CTRL_CTS_ENABLE(config->enableCts) | \
                                            Rx_Right_GET_UART_FLOW_CTRL_CTS_POLARITY (config->ctsPolarity)  | \
                                            Rx_Right_GET_UART_FLOW_CTRL_RTS_POLARITY(config->rtsPolarity)   | \
                                            Rx_Right_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(config->rtsRxFifoLevel);
        #endif /* !(Rx_Right_CY_SCBIP_V0 || Rx_Right_CY_SCBIP_V1) */

            /* Configure interrupt with UART handler but do not enable it */
            CyIntDisable    (Rx_Right_ISR_NUMBER);
            CyIntSetPriority(Rx_Right_ISR_NUMBER, Rx_Right_ISR_PRIORITY);
            (void) CyIntSetVector(Rx_Right_ISR_NUMBER, &Rx_Right_SPI_UART_ISR);

            /* Configure WAKE interrupt */
        #if(Rx_Right_UART_RX_WAKEUP_IRQ)
            CyIntDisable    (Rx_Right_RX_WAKE_ISR_NUMBER);
            CyIntSetPriority(Rx_Right_RX_WAKE_ISR_NUMBER, Rx_Right_RX_WAKE_ISR_PRIORITY);
            (void) CyIntSetVector(Rx_Right_RX_WAKE_ISR_NUMBER, &Rx_Right_UART_WAKEUP_ISR);
        #endif /* (Rx_Right_UART_RX_WAKEUP_IRQ) */

            /* Configure interrupt sources */
            Rx_Right_INTR_I2C_EC_MASK_REG = Rx_Right_NO_INTR_SOURCES;
            Rx_Right_INTR_SPI_EC_MASK_REG = Rx_Right_NO_INTR_SOURCES;
            Rx_Right_INTR_SLAVE_MASK_REG  = Rx_Right_NO_INTR_SOURCES;
            Rx_Right_INTR_MASTER_MASK_REG = Rx_Right_NO_INTR_SOURCES;
            Rx_Right_INTR_RX_MASK_REG     = config->rxInterruptMask;
            Rx_Right_INTR_TX_MASK_REG     = config->txInterruptMask;

            /* Clear RX buffer indexes */
            Rx_Right_rxBufferHead     = 0u;
            Rx_Right_rxBufferTail     = 0u;
            Rx_Right_rxBufferOverflow = 0u;

            /* Clear TX buffer indexes */
            Rx_Right_txBufferHead = 0u;
            Rx_Right_txBufferTail = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: Rx_Right_UartInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for the UART operation.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void Rx_Right_UartInit(void)
    {
        /* Configure UART interface */
        Rx_Right_CTRL_REG = Rx_Right_UART_DEFAULT_CTRL;

        /* Configure sub-mode: UART, SmartCard or IrDA */
        Rx_Right_UART_CTRL_REG = Rx_Right_UART_DEFAULT_UART_CTRL;

        /* Configure RX direction */
        Rx_Right_UART_RX_CTRL_REG = Rx_Right_UART_DEFAULT_UART_RX_CTRL;
        Rx_Right_RX_CTRL_REG      = Rx_Right_UART_DEFAULT_RX_CTRL;
        Rx_Right_RX_FIFO_CTRL_REG = Rx_Right_UART_DEFAULT_RX_FIFO_CTRL;
        Rx_Right_RX_MATCH_REG     = Rx_Right_UART_DEFAULT_RX_MATCH_REG;

        /* Configure TX direction */
        Rx_Right_UART_TX_CTRL_REG = Rx_Right_UART_DEFAULT_UART_TX_CTRL;
        Rx_Right_TX_CTRL_REG      = Rx_Right_UART_DEFAULT_TX_CTRL;
        Rx_Right_TX_FIFO_CTRL_REG = Rx_Right_UART_DEFAULT_TX_FIFO_CTRL;

    #if !(Rx_Right_CY_SCBIP_V0 || Rx_Right_CY_SCBIP_V1)
        Rx_Right_UART_FLOW_CTRL_REG = Rx_Right_UART_DEFAULT_FLOW_CTRL;
    #endif /* !(Rx_Right_CY_SCBIP_V0 || Rx_Right_CY_SCBIP_V1) */

        /* Configure interrupt with UART handler but do not enable it */
    #if(Rx_Right_SCB_IRQ_INTERNAL)
        CyIntDisable    (Rx_Right_ISR_NUMBER);
        CyIntSetPriority(Rx_Right_ISR_NUMBER, Rx_Right_ISR_PRIORITY);
        (void) CyIntSetVector(Rx_Right_ISR_NUMBER, &Rx_Right_SPI_UART_ISR);
    #endif /* (Rx_Right_SCB_IRQ_INTERNAL) */

        /* Configure WAKE interrupt */
    #if(Rx_Right_UART_RX_WAKEUP_IRQ)
        CyIntDisable    (Rx_Right_RX_WAKE_ISR_NUMBER);
        CyIntSetPriority(Rx_Right_RX_WAKE_ISR_NUMBER, Rx_Right_RX_WAKE_ISR_PRIORITY);
        (void) CyIntSetVector(Rx_Right_RX_WAKE_ISR_NUMBER, &Rx_Right_UART_WAKEUP_ISR);
    #endif /* (Rx_Right_UART_RX_WAKEUP_IRQ) */

        /* Configure interrupt sources */
        Rx_Right_INTR_I2C_EC_MASK_REG = Rx_Right_UART_DEFAULT_INTR_I2C_EC_MASK;
        Rx_Right_INTR_SPI_EC_MASK_REG = Rx_Right_UART_DEFAULT_INTR_SPI_EC_MASK;
        Rx_Right_INTR_SLAVE_MASK_REG  = Rx_Right_UART_DEFAULT_INTR_SLAVE_MASK;
        Rx_Right_INTR_MASTER_MASK_REG = Rx_Right_UART_DEFAULT_INTR_MASTER_MASK;
        Rx_Right_INTR_RX_MASK_REG     = Rx_Right_UART_DEFAULT_INTR_RX_MASK;
        Rx_Right_INTR_TX_MASK_REG     = Rx_Right_UART_DEFAULT_INTR_TX_MASK;

    #if(Rx_Right_INTERNAL_RX_SW_BUFFER_CONST)
        Rx_Right_rxBufferHead     = 0u;
        Rx_Right_rxBufferTail     = 0u;
        Rx_Right_rxBufferOverflow = 0u;
    #endif /* (Rx_Right_INTERNAL_RX_SW_BUFFER_CONST) */

    #if(Rx_Right_INTERNAL_TX_SW_BUFFER_CONST)
        Rx_Right_txBufferHead = 0u;
        Rx_Right_txBufferTail = 0u;
    #endif /* (Rx_Right_INTERNAL_TX_SW_BUFFER_CONST) */
    }
#endif /* (Rx_Right_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: Rx_Right_UartSetRxAddress
********************************************************************************
*
* Summary:
*  Sets the hardware detectable receiver address for the UART in the
*  Multiprocessor mode.
*
* Parameters:
*  address: Address for hardware address detection.
*
* Return:
*  None
*
*******************************************************************************/
void Rx_Right_UartSetRxAddress(uint32 address)
{
     uint32 matchReg;

    matchReg = Rx_Right_RX_MATCH_REG;

    matchReg &= ((uint32) ~Rx_Right_RX_MATCH_ADDR_MASK); /* Clear address bits */
    matchReg |= ((uint32)  (address & Rx_Right_RX_MATCH_ADDR_MASK)); /* Set address  */

    Rx_Right_RX_MATCH_REG = matchReg;
}


/*******************************************************************************
* Function Name: Rx_Right_UartSetRxAddressMask
********************************************************************************
*
* Summary:
*  Sets the hardware address mask for the UART in the Multiprocessor mode.
*
* Parameters:
*  addressMask: Address mask.
*   0 - address bit does not care while comparison.
*   1 - address bit is significant while comparison.
*
* Return:
*  None
*
*******************************************************************************/
void Rx_Right_UartSetRxAddressMask(uint32 addressMask)
{
    uint32 matchReg;

    matchReg = Rx_Right_RX_MATCH_REG;

    matchReg &= ((uint32) ~Rx_Right_RX_MATCH_MASK_MASK); /* Clear address mask bits */
    matchReg |= ((uint32) (addressMask << Rx_Right_RX_MATCH_MASK_POS));

    Rx_Right_RX_MATCH_REG = matchReg;
}


#if(Rx_Right_UART_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: Rx_Right_UartGetChar
    ********************************************************************************
    *
    * Summary:
    *  Retrieves the next data element from the receive buffer.
    *  This function is designed for ASCII characters and returns a char
    *  where 1 to 255 are valid characters and 0 indicates an error occurred or
    *  no data present.
    *  - The RX software buffer is disabled: returns the data element
    *    retrieved from the RX FIFO.
    *    Undefined data will be returned if the RX FIFO is empty.
    *  - The RX software buffer is enabled: returns the data element from
    *    the software receive buffer.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  The next data element from the receive buffer.
    *  ASCII character values from 1 to 255 are valid.
    *  A returned zero signifies an error condition or no data available.
    *
    * Side Effects:
    *  The errors bits may not correspond with reading characters due to RX FIFO
    *  and software buffer usage.
    *  RX software buffer is enabled: The internal software buffer overflow
    *  does not treat as an error condition.
    *  Check SCB_rxBufferOverflow to capture that error condition.
    *
    *******************************************************************************/
    uint32 Rx_Right_UartGetChar(void)
    {
        uint32 rxData = 0u;

        /* Reads data only if there is data to read */
        if(0u != Rx_Right_SpiUartGetRxBufferSize())
        {
            rxData = Rx_Right_SpiUartReadRxData();
        }

        if(Rx_Right_CHECK_INTR_RX(Rx_Right_INTR_RX_ERR))
        {
            rxData = 0u; /* Error occurred: returns zero */
            Rx_Right_ClearRxInterruptSource(Rx_Right_INTR_RX_ERR);
        }

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: Rx_Right_UartGetByte
    ********************************************************************************
    *
    * Summary:
    *  Retrieves the next data element from the receive buffer, returns the
    *  received byte and error condition.
    *   - The RX software buffer is disabled: returns the data element retrieved
    *     from the RX FIFO. Undefined data will be returned if the RX FIFO is
    *     empty.
    *   - The RX software buffer is enabled: returns data element from the
    *     software receive buffer.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Bits 7-0 contain the next data element from the receive buffer and
    *  other bits contain the error condition.
    *
    * Side Effects:
    *  The errors bits may not correspond with reading characters due to RX FIFO
    *  and software buffer usage.
    *  RX software buffer is disabled: The internal software buffer overflow
    *  is not returned as status by this function.
    *  Check SCB_rxBufferOverflow to capture that error condition.
    *
    *******************************************************************************/
    uint32 Rx_Right_UartGetByte(void)
    {
        uint32 rxData;
        uint32 tmpStatus;
        uint32 intSourceMask;

        intSourceMask = Rx_Right_SpiUartDisableIntRx();

        if(0u != Rx_Right_SpiUartGetRxBufferSize())
        {
            /* Enables interrupt to receive more bytes: at least one byte is in
            * buffer.
            */
            Rx_Right_SpiUartEnableIntRx(intSourceMask);

            /* Get received byte */
            rxData = Rx_Right_SpiUartReadRxData();
        }
        else
        {
            /* Reads a byte directly from RX FIFO: underflow is raised in the case
            * of empty. Otherwise the first received byte will be read.
            */
            rxData = Rx_Right_RX_FIFO_RD_REG;

            /* Enables interrupt to receive more bytes.
            * The RX_NOT_EMPTY interrupt is cleared by the interrupt routine
            * in case the byte was received and read by code above.
            */
            Rx_Right_SpiUartEnableIntRx(intSourceMask);
        }

        /* Get and clear RX error mask */
        tmpStatus = (Rx_Right_GetRxInterruptSource() & Rx_Right_INTR_RX_ERR);
        Rx_Right_ClearRxInterruptSource(Rx_Right_INTR_RX_ERR);

        /* Puts together data and error status:
        * MP mode and accept address: 9th bit is set to notify mark.
        */
        rxData |= ((uint32) (tmpStatus << 8u));

        return(rxData);
    }


    #if !(Rx_Right_CY_SCBIP_V0 || Rx_Right_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: Rx_Right_UartSetRtsPolarity
        ********************************************************************************
        *
        * Summary:
        *  Sets active polarity of RTS output signal.
        *
        * Parameters:
        *  polarity: Active polarity of RTS output signal.
        *   Rx_Right_UART_RTS_ACTIVE_LOW  - RTS signal is active low.
        *   Rx_Right_UART_RTS_ACTIVE_HIGH - RTS signal is active high.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void Rx_Right_UartSetRtsPolarity(uint32 polarity)
        {
            if(0u != polarity)
            {
                Rx_Right_UART_FLOW_CTRL_REG |= (uint32)  Rx_Right_UART_FLOW_CTRL_RTS_POLARITY;
            }
            else
            {
                Rx_Right_UART_FLOW_CTRL_REG &= (uint32) ~Rx_Right_UART_FLOW_CTRL_RTS_POLARITY;
            }
        }


        /*******************************************************************************
        * Function Name: Rx_Right_UartSetRtsFifoLevel
        ********************************************************************************
        *
        * Summary:
        *  Sets level in the RX FIFO for RTS signal activation.
        *  While the RX FIFO has fewer entries than the RX FIFO level the RTS signal
        *  remains active, otherwise the RTS signal becomes inactive.
        *
        * Parameters:
        *  level: Level in the RX FIFO for RTS signal activation.
        *         The range of valid level values is between 0 and RX FIFO depth - 1.
        *         Setting level value to 0 disables RTS signal activation.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void Rx_Right_UartSetRtsFifoLevel(uint32 level)
        {
            uint32 uartFlowCtrl;

            uartFlowCtrl = Rx_Right_UART_FLOW_CTRL_REG;

            uartFlowCtrl &= ((uint32) ~Rx_Right_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
            uartFlowCtrl |= ((uint32) (Rx_Right_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK & level));

            Rx_Right_UART_FLOW_CTRL_REG = uartFlowCtrl;
        }
    #endif /* !(Rx_Right_CY_SCBIP_V0 || Rx_Right_CY_SCBIP_V1) */

#endif /* (Rx_Right_UART_RX_DIRECTION) */


#if(Rx_Right_UART_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: Rx_Right_UartPutString
    ********************************************************************************
    *
    * Summary:
    *  Places a NULL terminated string in the transmit buffer to be sent at the
    *  next available bus time.
    *  This function is blocking and waits until there is space available to put
    *  all the requested data into the  transmit buffer.
    *
    * Parameters:
    *  string: pointer to the null terminated string array to be placed in the
    *          transmit buffer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void Rx_Right_UartPutString(const char8 string[])
    {
        uint32 bufIndex;

        bufIndex = 0u;

        /* Blocks the control flow until all data has been sent */
        while(string[bufIndex] != ((char8) 0))
        {
            Rx_Right_UartPutChar((uint32) string[bufIndex]);
            bufIndex++;
        }
    }


    /*******************************************************************************
    * Function Name: Rx_Right_UartPutCRLF
    ********************************************************************************
    *
    * Summary:
    *  Places a byte of data followed by a carriage return (0x0D) and
    *  line feed (0x0A) into the transmit buffer.
    *  This function is blocking and waits until there is space available to put
    *  all the requested data into the  transmit buffer.
    *
    * Parameters:
    *  txDataByte : the data to be transmitted.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void Rx_Right_UartPutCRLF(uint32 txDataByte)
    {
        Rx_Right_UartPutChar(txDataByte);  /* Blocks control flow until all data has been sent */
        Rx_Right_UartPutChar(0x0Du);       /* Blocks control flow until all data has been sent */
        Rx_Right_UartPutChar(0x0Au);       /* Blocks control flow until all data has been sent */
    }


    #if !(Rx_Right_CY_SCBIP_V0 || Rx_Right_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: Rx_RightSCB_UartEnableCts
        ********************************************************************************
        *
        * Summary:
        *  Enables usage of CTS input signal by the UART transmitter.
        *
        * Parameters:
        *  None
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void Rx_Right_UartEnableCts(void)
        {
            Rx_Right_UART_FLOW_CTRL_REG |= (uint32)  Rx_Right_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: Rx_Right_UartDisableCts
        ********************************************************************************
        *
        * Summary:
        *  Disables usage of CTS input signal by the UART transmitter.
        *
        * Parameters:
        *  None
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void Rx_Right_UartDisableCts(void)
        {
            Rx_Right_UART_FLOW_CTRL_REG &= (uint32) ~Rx_Right_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: Rx_Right_UartSetCtsPolarity
        ********************************************************************************
        *
        * Summary:
        *  Sets active polarity of CTS input signal.
        *
        * Parameters:
        *  polarity: Active polarity of CTS output signal.
        *   Rx_Right_UART_CTS_ACTIVE_LOW  - CTS signal is active low.
        *   Rx_Right_UART_CTS_ACTIVE_HIGH - CTS signal is active high.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void Rx_Right_UartSetCtsPolarity(uint32 polarity)
        {
            if (0u != polarity)
            {
                Rx_Right_UART_FLOW_CTRL_REG |= (uint32)  Rx_Right_UART_FLOW_CTRL_CTS_POLARITY;
            }
            else
            {
                Rx_Right_UART_FLOW_CTRL_REG &= (uint32) ~Rx_Right_UART_FLOW_CTRL_CTS_POLARITY;
            }
        }
    #endif /* !(Rx_Right_CY_SCBIP_V0 || Rx_Right_CY_SCBIP_V1) */

#endif /* (Rx_Right_UART_TX_DIRECTION) */


#if(Rx_Right_UART_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: Rx_Right_UartSaveConfig
    ********************************************************************************
    *
    * Summary:
    *  Clears and enables interrupt on a falling edge of the Rx input. The GPIO
    *  event wakes up the device and SKIP_START feature allows the UART continue
    *  receiving data bytes properly. The GPIO interrupt does not track in the
    *  active mode therefore requires to be cleared by this API.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void Rx_Right_UartSaveConfig(void)
    {
        /* Clear interrupt activity:
        *  - set skip start and disable RX. At GPIO wakeup RX will be enabled.
        *  - clear rx_wake interrupt source as it triggers during normal operation.
        *  - clear wake interrupt pending state as it becomes pending in active mode.
        */

        Rx_Right_UART_RX_CTRL_REG |= Rx_Right_UART_RX_CTRL_SKIP_START;

    #if(Rx_Right_SCB_MODE_UNCONFIG_CONST_CFG)
        #if(Rx_Right_MOSI_SCL_RX_WAKE_PIN)
            (void) Rx_Right_spi_mosi_i2c_scl_uart_rx_wake_ClearInterrupt();
        #endif /* (Rx_Right_MOSI_SCL_RX_WAKE_PIN) */
    #else
        #if(Rx_Right_UART_RX_WAKE_PIN)
            (void) Rx_Right_rx_wake_ClearInterrupt();
        #endif /* (Rx_Right_UART_RX_WAKE_PIN) */
    #endif /* (Rx_Right_SCB_MODE_UNCONFIG_CONST_CFG) */

    #if(Rx_Right_UART_RX_WAKEUP_IRQ)
        Rx_Right_RxWakeClearPendingInt();
        Rx_Right_RxWakeEnableInt();
    #endif /* (Rx_Right_UART_RX_WAKEUP_IRQ) */
    }


    /*******************************************************************************
    * Function Name: Rx_Right_UartRestoreConfig
    ********************************************************************************
    *
    * Summary:
    *  Disables the RX GPIO interrupt. Until this function is called the interrupt
    *  remains active and triggers on every falling edge of the UART RX line.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void Rx_Right_UartRestoreConfig(void)
    {
    /* Disable RX GPIO interrupt: no more triggers in active mode */
    #if(Rx_Right_UART_RX_WAKEUP_IRQ)
        Rx_Right_RxWakeDisableInt();
    #endif /* (Rx_Right_UART_RX_WAKEUP_IRQ) */
    }
#endif /* (Rx_Right_UART_WAKE_ENABLE_CONST) */


#if(Rx_Right_UART_RX_WAKEUP_IRQ)
    /*******************************************************************************
    * Function Name: Rx_Right_UART_WAKEUP_ISR
    ********************************************************************************
    *
    * Summary:
    *  Handles the Interrupt Service Routine for the SCB UART mode GPIO wakeup
    *  event. This event is configured to trigger on a falling edge of the RX line.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    CY_ISR(Rx_Right_UART_WAKEUP_ISR)
    {
        /* Clear interrupt source: the event becomes multi triggered and is
        * only disabled by Rx_Right_UartRestoreConfig() call.
        */
    #if(Rx_Right_SCB_MODE_UNCONFIG_CONST_CFG)
        #if(Rx_Right_MOSI_SCL_RX_WAKE_PIN)
            (void) Rx_Right_spi_mosi_i2c_scl_uart_rx_wake_ClearInterrupt();
        #endif /* (Rx_Right_MOSI_SCL_RX_WAKE_PIN) */
    #else
        #if(Rx_Right_UART_RX_WAKE_PIN)
            (void) Rx_Right_rx_wake_ClearInterrupt();
        #endif /* (Rx_Right_UART_RX_WAKE_PIN) */
    #endif /* (Rx_Right_SCB_MODE_UNCONFIG_CONST_CFG) */
    }
#endif /* (Rx_Right_UART_RX_WAKEUP_IRQ) */


/* [] END OF FILE */
