/*******************************************************************************
* File Name: UART_Rx_Back_UART.c
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

#include "UART_Rx_Back_PVT.h"
#include "UART_Rx_Back_SPI_UART_PVT.h"


#if(UART_Rx_Back_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    const UART_Rx_Back_UART_INIT_STRUCT UART_Rx_Back_configUart =
    {
        UART_Rx_Back_UART_SUB_MODE,
        UART_Rx_Back_UART_DIRECTION,
        UART_Rx_Back_UART_DATA_BITS_NUM,
        UART_Rx_Back_UART_PARITY_TYPE,
        UART_Rx_Back_UART_STOP_BITS_NUM,
        UART_Rx_Back_UART_OVS_FACTOR,
        UART_Rx_Back_UART_IRDA_LOW_POWER,
        UART_Rx_Back_UART_MEDIAN_FILTER_ENABLE,
        UART_Rx_Back_UART_RETRY_ON_NACK,
        UART_Rx_Back_UART_IRDA_POLARITY,
        UART_Rx_Back_UART_DROP_ON_PARITY_ERR,
        UART_Rx_Back_UART_DROP_ON_FRAME_ERR,
        UART_Rx_Back_UART_WAKE_ENABLE,
        0u,
        NULL,
        0u,
        NULL,
        UART_Rx_Back_UART_MP_MODE_ENABLE,
        UART_Rx_Back_UART_MP_ACCEPT_ADDRESS,
        UART_Rx_Back_UART_MP_RX_ADDRESS,
        UART_Rx_Back_UART_MP_RX_ADDRESS_MASK,
        (uint32) UART_Rx_Back_SCB_IRQ_INTERNAL,
        UART_Rx_Back_UART_INTR_RX_MASK,
        UART_Rx_Back_UART_RX_TRIGGER_LEVEL,
        UART_Rx_Back_UART_INTR_TX_MASK,
        UART_Rx_Back_UART_TX_TRIGGER_LEVEL,
        (uint8) UART_Rx_Back_UART_BYTE_MODE_ENABLE,
        (uint8) UART_Rx_Back_UART_CTS_ENABLE,
        (uint8) UART_Rx_Back_UART_CTS_POLARITY,
        (uint8) UART_Rx_Back_UART_RTS_POLARITY,
        (uint8) UART_Rx_Back_UART_RTS_FIFO_LEVEL
    };


    /*******************************************************************************
    * Function Name: UART_Rx_Back_UartInit
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
    void UART_Rx_Back_UartInit(const UART_Rx_Back_UART_INIT_STRUCT *config)
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

        #if !(UART_Rx_Back_CY_SCBIP_V0 || UART_Rx_Back_CY_SCBIP_V1)
            /* Add RTS and CTS pins to configure */
            pinsConfig |= (0u != config->rtsRxFifoLevel) ? (UART_Rx_Back_UART_RTS_PIN_ENABLE) : (0u);
            pinsConfig |= (0u != config->enableCts)         ? (UART_Rx_Back_UART_CTS_PIN_ENABLE) : (0u);
        #endif /* !(UART_Rx_Back_CY_SCBIP_V0 || UART_Rx_Back_CY_SCBIP_V1) */

            /* Configure pins */
            UART_Rx_Back_SetPins(UART_Rx_Back_SCB_MODE_UART, config->mode, pinsConfig);

            /* Store internal configuration */
            UART_Rx_Back_scbMode       = (uint8) UART_Rx_Back_SCB_MODE_UART;
            UART_Rx_Back_scbEnableWake = (uint8) config->enableWake;
            UART_Rx_Back_scbEnableIntr = (uint8) config->enableInterrupt;

            /* Set RX direction internal variables */
            UART_Rx_Back_rxBuffer      =         config->rxBuffer;
            UART_Rx_Back_rxDataBits    = (uint8) config->dataBits;
            UART_Rx_Back_rxBufferSize  = (uint8) config->rxBufferSize;

            /* Set TX direction internal variables */
            UART_Rx_Back_txBuffer      =         config->txBuffer;
            UART_Rx_Back_txDataBits    = (uint8) config->dataBits;
            UART_Rx_Back_txBufferSize  = (uint8) config->txBufferSize;

            /* Configure UART interface */
            if(UART_Rx_Back_UART_MODE_IRDA == config->mode)
            {
                /* OVS settings: IrDA */
                UART_Rx_Back_CTRL_REG  = ((0u != config->enableIrdaLowPower) ?
                                                (UART_Rx_Back_UART_GET_CTRL_OVS_IRDA_LP(config->oversample)) :
                                                (UART_Rx_Back_CTRL_OVS_IRDA_OVS16));
            }
            else
            {
                /* OVS settings: UART and SmartCard */
                UART_Rx_Back_CTRL_REG  = UART_Rx_Back_GET_CTRL_OVS(config->oversample);
            }

            UART_Rx_Back_CTRL_REG     |= UART_Rx_Back_GET_CTRL_BYTE_MODE  (config->enableByteMode)      |
                                             UART_Rx_Back_GET_CTRL_ADDR_ACCEPT(config->multiprocAcceptAddr) |
                                             UART_Rx_Back_CTRL_UART;

            /* Configure sub-mode: UART, SmartCard or IrDA */
            UART_Rx_Back_UART_CTRL_REG = UART_Rx_Back_GET_UART_CTRL_MODE(config->mode);

            /* Configure RX direction */
            UART_Rx_Back_UART_RX_CTRL_REG = UART_Rx_Back_GET_UART_RX_CTRL_MODE(config->stopBits)              |
                                        UART_Rx_Back_GET_UART_RX_CTRL_POLARITY(config->enableInvertedRx)          |
                                        UART_Rx_Back_GET_UART_RX_CTRL_MP_MODE(config->enableMultiproc)            |
                                        UART_Rx_Back_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(config->dropOnParityErr) |
                                        UART_Rx_Back_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(config->dropOnFrameErr);

            if(UART_Rx_Back_UART_PARITY_NONE != config->parity)
            {
               UART_Rx_Back_UART_RX_CTRL_REG |= UART_Rx_Back_GET_UART_RX_CTRL_PARITY(config->parity) |
                                                    UART_Rx_Back_UART_RX_CTRL_PARITY_ENABLED;
            }

            UART_Rx_Back_RX_CTRL_REG      = UART_Rx_Back_GET_RX_CTRL_DATA_WIDTH(config->dataBits)       |
                                                UART_Rx_Back_GET_RX_CTRL_MEDIAN(config->enableMedianFilter) |
                                                UART_Rx_Back_GET_UART_RX_CTRL_ENABLED(config->direction);

            UART_Rx_Back_RX_FIFO_CTRL_REG = UART_Rx_Back_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(config->rxTriggerLevel);

            /* Configure MP address */
            UART_Rx_Back_RX_MATCH_REG     = UART_Rx_Back_GET_RX_MATCH_ADDR(config->multiprocAddr) |
                                                UART_Rx_Back_GET_RX_MATCH_MASK(config->multiprocAddrMask);

            /* Configure RX direction */
            UART_Rx_Back_UART_TX_CTRL_REG = UART_Rx_Back_GET_UART_TX_CTRL_MODE(config->stopBits) |
                                                UART_Rx_Back_GET_UART_TX_CTRL_RETRY_NACK(config->enableRetryNack);

            if(UART_Rx_Back_UART_PARITY_NONE != config->parity)
            {
               UART_Rx_Back_UART_TX_CTRL_REG |= UART_Rx_Back_GET_UART_TX_CTRL_PARITY(config->parity) |
                                                    UART_Rx_Back_UART_TX_CTRL_PARITY_ENABLED;
            }

            UART_Rx_Back_TX_CTRL_REG      = UART_Rx_Back_GET_TX_CTRL_DATA_WIDTH(config->dataBits)    |
                                                UART_Rx_Back_GET_UART_TX_CTRL_ENABLED(config->direction);

            UART_Rx_Back_TX_FIFO_CTRL_REG = UART_Rx_Back_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(config->txTriggerLevel);

        #if !(UART_Rx_Back_CY_SCBIP_V0 || UART_Rx_Back_CY_SCBIP_V1)
            UART_Rx_Back_UART_FLOW_CTRL_REG = UART_Rx_Back_GET_UART_FLOW_CTRL_CTS_ENABLE(config->enableCts) | \
                                            UART_Rx_Back_GET_UART_FLOW_CTRL_CTS_POLARITY (config->ctsPolarity)  | \
                                            UART_Rx_Back_GET_UART_FLOW_CTRL_RTS_POLARITY(config->rtsPolarity)   | \
                                            UART_Rx_Back_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(config->rtsRxFifoLevel);
        #endif /* !(UART_Rx_Back_CY_SCBIP_V0 || UART_Rx_Back_CY_SCBIP_V1) */

            /* Configure interrupt with UART handler but do not enable it */
            CyIntDisable    (UART_Rx_Back_ISR_NUMBER);
            CyIntSetPriority(UART_Rx_Back_ISR_NUMBER, UART_Rx_Back_ISR_PRIORITY);
            (void) CyIntSetVector(UART_Rx_Back_ISR_NUMBER, &UART_Rx_Back_SPI_UART_ISR);

            /* Configure WAKE interrupt */
        #if(UART_Rx_Back_UART_RX_WAKEUP_IRQ)
            CyIntDisable    (UART_Rx_Back_RX_WAKE_ISR_NUMBER);
            CyIntSetPriority(UART_Rx_Back_RX_WAKE_ISR_NUMBER, UART_Rx_Back_RX_WAKE_ISR_PRIORITY);
            (void) CyIntSetVector(UART_Rx_Back_RX_WAKE_ISR_NUMBER, &UART_Rx_Back_UART_WAKEUP_ISR);
        #endif /* (UART_Rx_Back_UART_RX_WAKEUP_IRQ) */

            /* Configure interrupt sources */
            UART_Rx_Back_INTR_I2C_EC_MASK_REG = UART_Rx_Back_NO_INTR_SOURCES;
            UART_Rx_Back_INTR_SPI_EC_MASK_REG = UART_Rx_Back_NO_INTR_SOURCES;
            UART_Rx_Back_INTR_SLAVE_MASK_REG  = UART_Rx_Back_NO_INTR_SOURCES;
            UART_Rx_Back_INTR_MASTER_MASK_REG = UART_Rx_Back_NO_INTR_SOURCES;
            UART_Rx_Back_INTR_RX_MASK_REG     = config->rxInterruptMask;
            UART_Rx_Back_INTR_TX_MASK_REG     = config->txInterruptMask;

            /* Clear RX buffer indexes */
            UART_Rx_Back_rxBufferHead     = 0u;
            UART_Rx_Back_rxBufferTail     = 0u;
            UART_Rx_Back_rxBufferOverflow = 0u;

            /* Clear TX buffer indexes */
            UART_Rx_Back_txBufferHead = 0u;
            UART_Rx_Back_txBufferTail = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: UART_Rx_Back_UartInit
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
    void UART_Rx_Back_UartInit(void)
    {
        /* Configure UART interface */
        UART_Rx_Back_CTRL_REG = UART_Rx_Back_UART_DEFAULT_CTRL;

        /* Configure sub-mode: UART, SmartCard or IrDA */
        UART_Rx_Back_UART_CTRL_REG = UART_Rx_Back_UART_DEFAULT_UART_CTRL;

        /* Configure RX direction */
        UART_Rx_Back_UART_RX_CTRL_REG = UART_Rx_Back_UART_DEFAULT_UART_RX_CTRL;
        UART_Rx_Back_RX_CTRL_REG      = UART_Rx_Back_UART_DEFAULT_RX_CTRL;
        UART_Rx_Back_RX_FIFO_CTRL_REG = UART_Rx_Back_UART_DEFAULT_RX_FIFO_CTRL;
        UART_Rx_Back_RX_MATCH_REG     = UART_Rx_Back_UART_DEFAULT_RX_MATCH_REG;

        /* Configure TX direction */
        UART_Rx_Back_UART_TX_CTRL_REG = UART_Rx_Back_UART_DEFAULT_UART_TX_CTRL;
        UART_Rx_Back_TX_CTRL_REG      = UART_Rx_Back_UART_DEFAULT_TX_CTRL;
        UART_Rx_Back_TX_FIFO_CTRL_REG = UART_Rx_Back_UART_DEFAULT_TX_FIFO_CTRL;

    #if !(UART_Rx_Back_CY_SCBIP_V0 || UART_Rx_Back_CY_SCBIP_V1)
        UART_Rx_Back_UART_FLOW_CTRL_REG = UART_Rx_Back_UART_DEFAULT_FLOW_CTRL;
    #endif /* !(UART_Rx_Back_CY_SCBIP_V0 || UART_Rx_Back_CY_SCBIP_V1) */

        /* Configure interrupt with UART handler but do not enable it */
    #if(UART_Rx_Back_SCB_IRQ_INTERNAL)
        CyIntDisable    (UART_Rx_Back_ISR_NUMBER);
        CyIntSetPriority(UART_Rx_Back_ISR_NUMBER, UART_Rx_Back_ISR_PRIORITY);
        (void) CyIntSetVector(UART_Rx_Back_ISR_NUMBER, &UART_Rx_Back_SPI_UART_ISR);
    #endif /* (UART_Rx_Back_SCB_IRQ_INTERNAL) */

        /* Configure WAKE interrupt */
    #if(UART_Rx_Back_UART_RX_WAKEUP_IRQ)
        CyIntDisable    (UART_Rx_Back_RX_WAKE_ISR_NUMBER);
        CyIntSetPriority(UART_Rx_Back_RX_WAKE_ISR_NUMBER, UART_Rx_Back_RX_WAKE_ISR_PRIORITY);
        (void) CyIntSetVector(UART_Rx_Back_RX_WAKE_ISR_NUMBER, &UART_Rx_Back_UART_WAKEUP_ISR);
    #endif /* (UART_Rx_Back_UART_RX_WAKEUP_IRQ) */

        /* Configure interrupt sources */
        UART_Rx_Back_INTR_I2C_EC_MASK_REG = UART_Rx_Back_UART_DEFAULT_INTR_I2C_EC_MASK;
        UART_Rx_Back_INTR_SPI_EC_MASK_REG = UART_Rx_Back_UART_DEFAULT_INTR_SPI_EC_MASK;
        UART_Rx_Back_INTR_SLAVE_MASK_REG  = UART_Rx_Back_UART_DEFAULT_INTR_SLAVE_MASK;
        UART_Rx_Back_INTR_MASTER_MASK_REG = UART_Rx_Back_UART_DEFAULT_INTR_MASTER_MASK;
        UART_Rx_Back_INTR_RX_MASK_REG     = UART_Rx_Back_UART_DEFAULT_INTR_RX_MASK;
        UART_Rx_Back_INTR_TX_MASK_REG     = UART_Rx_Back_UART_DEFAULT_INTR_TX_MASK;

    #if(UART_Rx_Back_INTERNAL_RX_SW_BUFFER_CONST)
        UART_Rx_Back_rxBufferHead     = 0u;
        UART_Rx_Back_rxBufferTail     = 0u;
        UART_Rx_Back_rxBufferOverflow = 0u;
    #endif /* (UART_Rx_Back_INTERNAL_RX_SW_BUFFER_CONST) */

    #if(UART_Rx_Back_INTERNAL_TX_SW_BUFFER_CONST)
        UART_Rx_Back_txBufferHead = 0u;
        UART_Rx_Back_txBufferTail = 0u;
    #endif /* (UART_Rx_Back_INTERNAL_TX_SW_BUFFER_CONST) */
    }
#endif /* (UART_Rx_Back_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: UART_Rx_Back_UartSetRxAddress
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
void UART_Rx_Back_UartSetRxAddress(uint32 address)
{
     uint32 matchReg;

    matchReg = UART_Rx_Back_RX_MATCH_REG;

    matchReg &= ((uint32) ~UART_Rx_Back_RX_MATCH_ADDR_MASK); /* Clear address bits */
    matchReg |= ((uint32)  (address & UART_Rx_Back_RX_MATCH_ADDR_MASK)); /* Set address  */

    UART_Rx_Back_RX_MATCH_REG = matchReg;
}


/*******************************************************************************
* Function Name: UART_Rx_Back_UartSetRxAddressMask
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
void UART_Rx_Back_UartSetRxAddressMask(uint32 addressMask)
{
    uint32 matchReg;

    matchReg = UART_Rx_Back_RX_MATCH_REG;

    matchReg &= ((uint32) ~UART_Rx_Back_RX_MATCH_MASK_MASK); /* Clear address mask bits */
    matchReg |= ((uint32) (addressMask << UART_Rx_Back_RX_MATCH_MASK_POS));

    UART_Rx_Back_RX_MATCH_REG = matchReg;
}


#if(UART_Rx_Back_UART_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: UART_Rx_Back_UartGetChar
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
    uint32 UART_Rx_Back_UartGetChar(void)
    {
        uint32 rxData = 0u;

        /* Reads data only if there is data to read */
        if(0u != UART_Rx_Back_SpiUartGetRxBufferSize())
        {
            rxData = UART_Rx_Back_SpiUartReadRxData();
        }

        if(UART_Rx_Back_CHECK_INTR_RX(UART_Rx_Back_INTR_RX_ERR))
        {
            rxData = 0u; /* Error occurred: returns zero */
            UART_Rx_Back_ClearRxInterruptSource(UART_Rx_Back_INTR_RX_ERR);
        }

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: UART_Rx_Back_UartGetByte
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
    uint32 UART_Rx_Back_UartGetByte(void)
    {
        uint32 rxData;
        uint32 tmpStatus;
        uint32 intSourceMask;

        intSourceMask = UART_Rx_Back_SpiUartDisableIntRx();

        if(0u != UART_Rx_Back_SpiUartGetRxBufferSize())
        {
            /* Enables interrupt to receive more bytes: at least one byte is in
            * buffer.
            */
            UART_Rx_Back_SpiUartEnableIntRx(intSourceMask);

            /* Get received byte */
            rxData = UART_Rx_Back_SpiUartReadRxData();
        }
        else
        {
            /* Reads a byte directly from RX FIFO: underflow is raised in the case
            * of empty. Otherwise the first received byte will be read.
            */
            rxData = UART_Rx_Back_RX_FIFO_RD_REG;

            /* Enables interrupt to receive more bytes.
            * The RX_NOT_EMPTY interrupt is cleared by the interrupt routine
            * in case the byte was received and read by code above.
            */
            UART_Rx_Back_SpiUartEnableIntRx(intSourceMask);
        }

        /* Get and clear RX error mask */
        tmpStatus = (UART_Rx_Back_GetRxInterruptSource() & UART_Rx_Back_INTR_RX_ERR);
        UART_Rx_Back_ClearRxInterruptSource(UART_Rx_Back_INTR_RX_ERR);

        /* Puts together data and error status:
        * MP mode and accept address: 9th bit is set to notify mark.
        */
        rxData |= ((uint32) (tmpStatus << 8u));

        return(rxData);
    }


    #if !(UART_Rx_Back_CY_SCBIP_V0 || UART_Rx_Back_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: UART_Rx_Back_UartSetRtsPolarity
        ********************************************************************************
        *
        * Summary:
        *  Sets active polarity of RTS output signal.
        *
        * Parameters:
        *  polarity: Active polarity of RTS output signal.
        *   UART_Rx_Back_UART_RTS_ACTIVE_LOW  - RTS signal is active low.
        *   UART_Rx_Back_UART_RTS_ACTIVE_HIGH - RTS signal is active high.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void UART_Rx_Back_UartSetRtsPolarity(uint32 polarity)
        {
            if(0u != polarity)
            {
                UART_Rx_Back_UART_FLOW_CTRL_REG |= (uint32)  UART_Rx_Back_UART_FLOW_CTRL_RTS_POLARITY;
            }
            else
            {
                UART_Rx_Back_UART_FLOW_CTRL_REG &= (uint32) ~UART_Rx_Back_UART_FLOW_CTRL_RTS_POLARITY;
            }
        }


        /*******************************************************************************
        * Function Name: UART_Rx_Back_UartSetRtsFifoLevel
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
        void UART_Rx_Back_UartSetRtsFifoLevel(uint32 level)
        {
            uint32 uartFlowCtrl;

            uartFlowCtrl = UART_Rx_Back_UART_FLOW_CTRL_REG;

            uartFlowCtrl &= ((uint32) ~UART_Rx_Back_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
            uartFlowCtrl |= ((uint32) (UART_Rx_Back_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK & level));

            UART_Rx_Back_UART_FLOW_CTRL_REG = uartFlowCtrl;
        }
    #endif /* !(UART_Rx_Back_CY_SCBIP_V0 || UART_Rx_Back_CY_SCBIP_V1) */

#endif /* (UART_Rx_Back_UART_RX_DIRECTION) */


#if(UART_Rx_Back_UART_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: UART_Rx_Back_UartPutString
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
    void UART_Rx_Back_UartPutString(const char8 string[])
    {
        uint32 bufIndex;

        bufIndex = 0u;

        /* Blocks the control flow until all data has been sent */
        while(string[bufIndex] != ((char8) 0))
        {
            UART_Rx_Back_UartPutChar((uint32) string[bufIndex]);
            bufIndex++;
        }
    }


    /*******************************************************************************
    * Function Name: UART_Rx_Back_UartPutCRLF
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
    void UART_Rx_Back_UartPutCRLF(uint32 txDataByte)
    {
        UART_Rx_Back_UartPutChar(txDataByte);  /* Blocks control flow until all data has been sent */
        UART_Rx_Back_UartPutChar(0x0Du);       /* Blocks control flow until all data has been sent */
        UART_Rx_Back_UartPutChar(0x0Au);       /* Blocks control flow until all data has been sent */
    }


    #if !(UART_Rx_Back_CY_SCBIP_V0 || UART_Rx_Back_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: UART_Rx_BackSCB_UartEnableCts
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
        void UART_Rx_Back_UartEnableCts(void)
        {
            UART_Rx_Back_UART_FLOW_CTRL_REG |= (uint32)  UART_Rx_Back_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: UART_Rx_Back_UartDisableCts
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
        void UART_Rx_Back_UartDisableCts(void)
        {
            UART_Rx_Back_UART_FLOW_CTRL_REG &= (uint32) ~UART_Rx_Back_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: UART_Rx_Back_UartSetCtsPolarity
        ********************************************************************************
        *
        * Summary:
        *  Sets active polarity of CTS input signal.
        *
        * Parameters:
        *  polarity: Active polarity of CTS output signal.
        *   UART_Rx_Back_UART_CTS_ACTIVE_LOW  - CTS signal is active low.
        *   UART_Rx_Back_UART_CTS_ACTIVE_HIGH - CTS signal is active high.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void UART_Rx_Back_UartSetCtsPolarity(uint32 polarity)
        {
            if (0u != polarity)
            {
                UART_Rx_Back_UART_FLOW_CTRL_REG |= (uint32)  UART_Rx_Back_UART_FLOW_CTRL_CTS_POLARITY;
            }
            else
            {
                UART_Rx_Back_UART_FLOW_CTRL_REG &= (uint32) ~UART_Rx_Back_UART_FLOW_CTRL_CTS_POLARITY;
            }
        }
    #endif /* !(UART_Rx_Back_CY_SCBIP_V0 || UART_Rx_Back_CY_SCBIP_V1) */

#endif /* (UART_Rx_Back_UART_TX_DIRECTION) */


#if(UART_Rx_Back_UART_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: UART_Rx_Back_UartSaveConfig
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
    void UART_Rx_Back_UartSaveConfig(void)
    {
        /* Clear interrupt activity:
        *  - set skip start and disable RX. At GPIO wakeup RX will be enabled.
        *  - clear rx_wake interrupt source as it triggers during normal operation.
        *  - clear wake interrupt pending state as it becomes pending in active mode.
        */

        UART_Rx_Back_UART_RX_CTRL_REG |= UART_Rx_Back_UART_RX_CTRL_SKIP_START;

    #if(UART_Rx_Back_SCB_MODE_UNCONFIG_CONST_CFG)
        #if(UART_Rx_Back_MOSI_SCL_RX_WAKE_PIN)
            (void) UART_Rx_Back_spi_mosi_i2c_scl_uart_rx_wake_ClearInterrupt();
        #endif /* (UART_Rx_Back_MOSI_SCL_RX_WAKE_PIN) */
    #else
        #if(UART_Rx_Back_UART_RX_WAKE_PIN)
            (void) UART_Rx_Back_rx_wake_ClearInterrupt();
        #endif /* (UART_Rx_Back_UART_RX_WAKE_PIN) */
    #endif /* (UART_Rx_Back_SCB_MODE_UNCONFIG_CONST_CFG) */

    #if(UART_Rx_Back_UART_RX_WAKEUP_IRQ)
        UART_Rx_Back_RxWakeClearPendingInt();
        UART_Rx_Back_RxWakeEnableInt();
    #endif /* (UART_Rx_Back_UART_RX_WAKEUP_IRQ) */
    }


    /*******************************************************************************
    * Function Name: UART_Rx_Back_UartRestoreConfig
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
    void UART_Rx_Back_UartRestoreConfig(void)
    {
    /* Disable RX GPIO interrupt: no more triggers in active mode */
    #if(UART_Rx_Back_UART_RX_WAKEUP_IRQ)
        UART_Rx_Back_RxWakeDisableInt();
    #endif /* (UART_Rx_Back_UART_RX_WAKEUP_IRQ) */
    }
#endif /* (UART_Rx_Back_UART_WAKE_ENABLE_CONST) */


#if(UART_Rx_Back_UART_RX_WAKEUP_IRQ)
    /*******************************************************************************
    * Function Name: UART_Rx_Back_UART_WAKEUP_ISR
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
    CY_ISR(UART_Rx_Back_UART_WAKEUP_ISR)
    {
        /* Clear interrupt source: the event becomes multi triggered and is
        * only disabled by UART_Rx_Back_UartRestoreConfig() call.
        */
    #if(UART_Rx_Back_SCB_MODE_UNCONFIG_CONST_CFG)
        #if(UART_Rx_Back_MOSI_SCL_RX_WAKE_PIN)
            (void) UART_Rx_Back_spi_mosi_i2c_scl_uart_rx_wake_ClearInterrupt();
        #endif /* (UART_Rx_Back_MOSI_SCL_RX_WAKE_PIN) */
    #else
        #if(UART_Rx_Back_UART_RX_WAKE_PIN)
            (void) UART_Rx_Back_rx_wake_ClearInterrupt();
        #endif /* (UART_Rx_Back_UART_RX_WAKE_PIN) */
    #endif /* (UART_Rx_Back_SCB_MODE_UNCONFIG_CONST_CFG) */
    }
#endif /* (UART_Rx_Back_UART_RX_WAKEUP_IRQ) */


/* [] END OF FILE */
