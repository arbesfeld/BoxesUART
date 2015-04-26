/*******************************************************************************
* File Name: Tx.c
* Version 2.40
*
* Description:
*  This file provides all API functionality of the UART component
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
#if (Tx_INTERNAL_CLOCK_USED)
    #include "Tx_IntClock.h"
#endif /* End Tx_INTERNAL_CLOCK_USED */


/***************************************
* Global data allocation
***************************************/

uint8 Tx_initVar = 0u;

#if (Tx_TX_INTERRUPT_ENABLED && Tx_TX_ENABLED)
    volatile uint8 Tx_txBuffer[Tx_TX_BUFFER_SIZE];
    volatile uint8 Tx_txBufferRead = 0u;
    uint8 Tx_txBufferWrite = 0u;
#endif /* (Tx_TX_INTERRUPT_ENABLED && Tx_TX_ENABLED) */

#if (Tx_RX_INTERRUPT_ENABLED && (Tx_RX_ENABLED || Tx_HD_ENABLED))
    uint8 Tx_errorStatus = 0u;
    volatile uint8 Tx_rxBuffer[Tx_RX_BUFFER_SIZE];
    volatile uint8 Tx_rxBufferRead  = 0u;
    volatile uint8 Tx_rxBufferWrite = 0u;
    volatile uint8 Tx_rxBufferLoopDetect = 0u;
    volatile uint8 Tx_rxBufferOverflow   = 0u;
    #if (Tx_RXHW_ADDRESS_ENABLED)
        volatile uint8 Tx_rxAddressMode = Tx_RX_ADDRESS_MODE;
        volatile uint8 Tx_rxAddressDetected = 0u;
    #endif /* (Tx_RXHW_ADDRESS_ENABLED) */
#endif /* (Tx_RX_INTERRUPT_ENABLED && (Tx_RX_ENABLED || Tx_HD_ENABLED)) */


/*******************************************************************************
* Function Name: Tx_Start
********************************************************************************
*
* Summary:
*  This is the preferred method to begin component operation.
*  Tx_Start() sets the initVar variable, calls the
*  Tx_Init() function, and then calls the
*  Tx_Enable() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  The Tx_intiVar variable is used to indicate initial
*  configuration of this component. The variable is initialized to zero (0u)
*  and set to one (1u) the first time Tx_Start() is called. This
*  allows for component initialization without re-initialization in all
*  subsequent calls to the Tx_Start() routine.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Tx_Start(void) 
{
    /* If not initialized then initialize all required hardware and software */
    if(Tx_initVar == 0u)
    {
        Tx_Init();
        Tx_initVar = 1u;
    }

    Tx_Enable();
}


/*******************************************************************************
* Function Name: Tx_Init
********************************************************************************
*
* Summary:
*  Initializes or restores the component according to the customizer Configure
*  dialog settings. It is not necessary to call Tx_Init() because
*  the Tx_Start() API calls this function and is the preferred
*  method to begin component operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Tx_Init(void) 
{
    #if(Tx_RX_ENABLED || Tx_HD_ENABLED)

        #if (Tx_RX_INTERRUPT_ENABLED)
            /* Set RX interrupt vector and priority */
            (void) CyIntSetVector(Tx_RX_VECT_NUM, &Tx_RXISR);
            CyIntSetPriority(Tx_RX_VECT_NUM, Tx_RX_PRIOR_NUM);
            Tx_errorStatus = 0u;
        #endif /* (Tx_RX_INTERRUPT_ENABLED) */

        #if (Tx_RXHW_ADDRESS_ENABLED)
            Tx_SetRxAddressMode(Tx_RX_ADDRESS_MODE);
            Tx_SetRxAddress1(Tx_RX_HW_ADDRESS1);
            Tx_SetRxAddress2(Tx_RX_HW_ADDRESS2);
        #endif /* End Tx_RXHW_ADDRESS_ENABLED */

        /* Init Count7 period */
        Tx_RXBITCTR_PERIOD_REG = Tx_RXBITCTR_INIT;
        /* Configure the Initial RX interrupt mask */
        Tx_RXSTATUS_MASK_REG  = Tx_INIT_RX_INTERRUPTS_MASK;
    #endif /* End Tx_RX_ENABLED || Tx_HD_ENABLED*/

    #if(Tx_TX_ENABLED)
        #if (Tx_TX_INTERRUPT_ENABLED)
            /* Set TX interrupt vector and priority */
            (void) CyIntSetVector(Tx_TX_VECT_NUM, &Tx_TXISR);
            CyIntSetPriority(Tx_TX_VECT_NUM, Tx_TX_PRIOR_NUM);
        #endif /* (Tx_TX_INTERRUPT_ENABLED) */

        /* Write Counter Value for TX Bit Clk Generator*/
        #if (Tx_TXCLKGEN_DP)
            Tx_TXBITCLKGEN_CTR_REG = Tx_BIT_CENTER;
            Tx_TXBITCLKTX_COMPLETE_REG = ((Tx_NUMBER_OF_DATA_BITS +
                        Tx_NUMBER_OF_START_BIT) * Tx_OVER_SAMPLE_COUNT) - 1u;
        #else
            Tx_TXBITCTR_PERIOD_REG = ((Tx_NUMBER_OF_DATA_BITS +
                        Tx_NUMBER_OF_START_BIT) * Tx_OVER_SAMPLE_8) - 1u;
        #endif /* End Tx_TXCLKGEN_DP */

        /* Configure the Initial TX interrupt mask */
        #if (Tx_TX_INTERRUPT_ENABLED)
            Tx_TXSTATUS_MASK_REG = Tx_TX_STS_FIFO_EMPTY;
        #else
            Tx_TXSTATUS_MASK_REG = Tx_INIT_TX_INTERRUPTS_MASK;
        #endif /*End Tx_TX_INTERRUPT_ENABLED*/

    #endif /* End Tx_TX_ENABLED */

    #if(Tx_PARITY_TYPE_SW)  /* Write Parity to Control Register */
        Tx_WriteControlRegister( \
            (Tx_ReadControlRegister() & (uint8)~Tx_CTRL_PARITY_TYPE_MASK) | \
            (uint8)(Tx_PARITY_TYPE << Tx_CTRL_PARITY_TYPE0_SHIFT) );
    #endif /* End Tx_PARITY_TYPE_SW */
}


/*******************************************************************************
* Function Name: Tx_Enable
********************************************************************************
*
* Summary:
*  Activates the hardware and begins component operation. It is not necessary
*  to call Tx_Enable() because the Tx_Start() API
*  calls this function, which is the preferred method to begin component
*  operation.

* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  Tx_rxAddressDetected - set to initial state (0).
*
*******************************************************************************/
void Tx_Enable(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    #if (Tx_RX_ENABLED || Tx_HD_ENABLED)
        /* RX Counter (Count7) Enable */
        Tx_RXBITCTR_CONTROL_REG |= Tx_CNTR_ENABLE;

        /* Enable the RX Interrupt */
        Tx_RXSTATUS_ACTL_REG  |= Tx_INT_ENABLE;

        #if (Tx_RX_INTERRUPT_ENABLED)
            Tx_EnableRxInt();

            #if (Tx_RXHW_ADDRESS_ENABLED)
                Tx_rxAddressDetected = 0u;
            #endif /* (Tx_RXHW_ADDRESS_ENABLED) */
        #endif /* (Tx_RX_INTERRUPT_ENABLED) */
    #endif /* (Tx_RX_ENABLED || Tx_HD_ENABLED) */

    #if(Tx_TX_ENABLED)
        /* TX Counter (DP/Count7) Enable */
        #if(!Tx_TXCLKGEN_DP)
            Tx_TXBITCTR_CONTROL_REG |= Tx_CNTR_ENABLE;
        #endif /* End Tx_TXCLKGEN_DP */

        /* Enable the TX Interrupt */
        Tx_TXSTATUS_ACTL_REG |= Tx_INT_ENABLE;
        #if (Tx_TX_INTERRUPT_ENABLED)
            Tx_ClearPendingTxInt(); /* Clear history of TX_NOT_EMPTY */
            Tx_EnableTxInt();
        #endif /* (Tx_TX_INTERRUPT_ENABLED) */
     #endif /* (Tx_TX_INTERRUPT_ENABLED) */

    #if (Tx_INTERNAL_CLOCK_USED)
        Tx_IntClock_Start();  /* Enable the clock */
    #endif /* (Tx_INTERNAL_CLOCK_USED) */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Tx_Stop
********************************************************************************
*
* Summary:
*  Disables the UART operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Tx_Stop(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    /* Write Bit Counter Disable */
    #if (Tx_RX_ENABLED || Tx_HD_ENABLED)
        Tx_RXBITCTR_CONTROL_REG &= (uint8) ~Tx_CNTR_ENABLE;
    #endif /* (Tx_RX_ENABLED || Tx_HD_ENABLED) */

    #if (Tx_TX_ENABLED)
        #if(!Tx_TXCLKGEN_DP)
            Tx_TXBITCTR_CONTROL_REG &= (uint8) ~Tx_CNTR_ENABLE;
        #endif /* (!Tx_TXCLKGEN_DP) */
    #endif /* (Tx_TX_ENABLED) */

    #if (Tx_INTERNAL_CLOCK_USED)
        Tx_IntClock_Stop();   /* Disable the clock */
    #endif /* (Tx_INTERNAL_CLOCK_USED) */

    /* Disable internal interrupt component */
    #if (Tx_RX_ENABLED || Tx_HD_ENABLED)
        Tx_RXSTATUS_ACTL_REG  &= (uint8) ~Tx_INT_ENABLE;

        #if (Tx_RX_INTERRUPT_ENABLED)
            Tx_DisableRxInt();
        #endif /* (Tx_RX_INTERRUPT_ENABLED) */
    #endif /* (Tx_RX_ENABLED || Tx_HD_ENABLED) */

    #if (Tx_TX_ENABLED)
        Tx_TXSTATUS_ACTL_REG &= (uint8) ~Tx_INT_ENABLE;

        #if (Tx_TX_INTERRUPT_ENABLED)
            Tx_DisableTxInt();
        #endif /* (Tx_TX_INTERRUPT_ENABLED) */
    #endif /* (Tx_TX_ENABLED) */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Tx_ReadControlRegister
********************************************************************************
*
* Summary:
*  Returns the current value of the control register.
*
* Parameters:
*  None.
*
* Return:
*  Contents of the control register.
*
*******************************************************************************/
uint8 Tx_ReadControlRegister(void) 
{
    #if (Tx_CONTROL_REG_REMOVED)
        return(0u);
    #else
        return(Tx_CONTROL_REG);
    #endif /* (Tx_CONTROL_REG_REMOVED) */
}


/*******************************************************************************
* Function Name: Tx_WriteControlRegister
********************************************************************************
*
* Summary:
*  Writes an 8-bit value into the control register
*
* Parameters:
*  control:  control register value
*
* Return:
*  None.
*
*******************************************************************************/
void  Tx_WriteControlRegister(uint8 control) 
{
    #if (Tx_CONTROL_REG_REMOVED)
        if(0u != control)
        {
            /* Suppress compiler warning */
        }
    #else
       Tx_CONTROL_REG = control;
    #endif /* (Tx_CONTROL_REG_REMOVED) */
}


#if(Tx_RX_ENABLED || Tx_HD_ENABLED)
    /*******************************************************************************
    * Function Name: Tx_SetRxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the RX interrupt sources enabled.
    *
    * Parameters:
    *  IntSrc:  Bit field containing the RX interrupts to enable. Based on the 
    *  bit-field arrangement of the status register. This value must be a 
    *  combination of status register bit-masks shown below:
    *      Tx_RX_STS_FIFO_NOTEMPTY    Interrupt on byte received.
    *      Tx_RX_STS_PAR_ERROR        Interrupt on parity error.
    *      Tx_RX_STS_STOP_ERROR       Interrupt on stop error.
    *      Tx_RX_STS_BREAK            Interrupt on break.
    *      Tx_RX_STS_OVERRUN          Interrupt on overrun error.
    *      Tx_RX_STS_ADDR_MATCH       Interrupt on address match.
    *      Tx_RX_STS_MRKSPC           Interrupt on address detect.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void Tx_SetRxInterruptMode(uint8 intSrc) 
    {
        Tx_RXSTATUS_MASK_REG  = intSrc;
    }


    /*******************************************************************************
    * Function Name: Tx_ReadRxData
    ********************************************************************************
    *
    * Summary:
    *  Returns the next byte of received data. This function returns data without
    *  checking the status. You must check the status separately.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Received data from RX register
    *
    * Global Variables:
    *  Tx_rxBuffer - RAM buffer pointer for save received data.
    *  Tx_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  Tx_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  Tx_rxBufferLoopDetect - cleared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 Tx_ReadRxData(void) 
    {
        uint8 rxData;

    #if (Tx_RX_INTERRUPT_ENABLED)

        uint8 locRxBufferRead;
        uint8 locRxBufferWrite;

        /* Protect variables that could change on interrupt */
        Tx_DisableRxInt();

        locRxBufferRead  = Tx_rxBufferRead;
        locRxBufferWrite = Tx_rxBufferWrite;

        if( (Tx_rxBufferLoopDetect != 0u) || (locRxBufferRead != locRxBufferWrite) )
        {
            rxData = Tx_rxBuffer[locRxBufferRead];
            locRxBufferRead++;

            if(locRxBufferRead >= Tx_RX_BUFFER_SIZE)
            {
                locRxBufferRead = 0u;
            }
            /* Update the real pointer */
            Tx_rxBufferRead = locRxBufferRead;

            if(Tx_rxBufferLoopDetect != 0u)
            {
                Tx_rxBufferLoopDetect = 0u;
                #if ((Tx_RX_INTERRUPT_ENABLED) && (Tx_FLOW_CONTROL != 0u))
                    /* When Hardware Flow Control selected - return RX mask */
                    #if( Tx_HD_ENABLED )
                        if((Tx_CONTROL_REG & Tx_CTRL_HD_SEND) == 0u)
                        {   /* In Half duplex mode return RX mask only in RX
                            *  configuration set, otherwise
                            *  mask will be returned in LoadRxConfig() API.
                            */
                            Tx_RXSTATUS_MASK_REG  |= Tx_RX_STS_FIFO_NOTEMPTY;
                        }
                    #else
                        Tx_RXSTATUS_MASK_REG  |= Tx_RX_STS_FIFO_NOTEMPTY;
                    #endif /* end Tx_HD_ENABLED */
                #endif /* ((Tx_RX_INTERRUPT_ENABLED) && (Tx_FLOW_CONTROL != 0u)) */
            }
        }
        else
        {   /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit */
            rxData = Tx_RXDATA_REG;
        }

        Tx_EnableRxInt();

    #else

        /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit */
        rxData = Tx_RXDATA_REG;

    #endif /* (Tx_RX_INTERRUPT_ENABLED) */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: Tx_ReadRxStatus
    ********************************************************************************
    *
    * Summary:
    *  Returns the current state of the receiver status register and the software
    *  buffer overflow status.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Current state of the status register.
    *
    * Side Effect:
    *  All status register bits are clear-on-read except
    *  Tx_RX_STS_FIFO_NOTEMPTY.
    *  Tx_RX_STS_FIFO_NOTEMPTY clears immediately after RX data
    *  register read.
    *
    * Global Variables:
    *  Tx_rxBufferOverflow - used to indicate overload condition.
    *   It set to one in RX interrupt when there isn't free space in
    *   Tx_rxBufferRead to write new data. This condition returned
    *   and cleared to zero by this API as an
    *   Tx_RX_STS_SOFT_BUFF_OVER bit along with RX Status register
    *   bits.
    *
    *******************************************************************************/
    uint8 Tx_ReadRxStatus(void) 
    {
        uint8 status;

        status = Tx_RXSTATUS_REG & Tx_RX_HW_MASK;

    #if (Tx_RX_INTERRUPT_ENABLED)
        if(Tx_rxBufferOverflow != 0u)
        {
            status |= Tx_RX_STS_SOFT_BUFF_OVER;
            Tx_rxBufferOverflow = 0u;
        }
    #endif /* (Tx_RX_INTERRUPT_ENABLED) */

        return(status);
    }


    /*******************************************************************************
    * Function Name: Tx_GetChar
    ********************************************************************************
    *
    * Summary:
    *  Returns the last received byte of data. Tx_GetChar() is
    *  designed for ASCII characters and returns a uint8 where 1 to 255 are values
    *  for valid characters and 0 indicates an error occurred or no data is present.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Character read from UART RX buffer. ASCII characters from 1 to 255 are valid.
    *  A returned zero signifies an error condition or no data available.
    *
    * Global Variables:
    *  Tx_rxBuffer - RAM buffer pointer for save received data.
    *  Tx_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  Tx_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  Tx_rxBufferLoopDetect - cleared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 Tx_GetChar(void) 
    {
        uint8 rxData = 0u;
        uint8 rxStatus;

    #if (Tx_RX_INTERRUPT_ENABLED)
        uint8 locRxBufferRead;
        uint8 locRxBufferWrite;

        /* Protect variables that could change on interrupt */
        Tx_DisableRxInt();

        locRxBufferRead  = Tx_rxBufferRead;
        locRxBufferWrite = Tx_rxBufferWrite;

        if( (Tx_rxBufferLoopDetect != 0u) || (locRxBufferRead != locRxBufferWrite) )
        {
            rxData = Tx_rxBuffer[locRxBufferRead];
            locRxBufferRead++;
            if(locRxBufferRead >= Tx_RX_BUFFER_SIZE)
            {
                locRxBufferRead = 0u;
            }
            /* Update the real pointer */
            Tx_rxBufferRead = locRxBufferRead;

            if(Tx_rxBufferLoopDetect != 0u)
            {
                Tx_rxBufferLoopDetect = 0u;
                #if( (Tx_RX_INTERRUPT_ENABLED) && (Tx_FLOW_CONTROL != 0u) )
                    /* When Hardware Flow Control selected - return RX mask */
                    #if( Tx_HD_ENABLED )
                        if((Tx_CONTROL_REG & Tx_CTRL_HD_SEND) == 0u)
                        {   /* In Half duplex mode return RX mask only if
                            *  RX configuration set, otherwise
                            *  mask will be returned in LoadRxConfig() API.
                            */
                            Tx_RXSTATUS_MASK_REG |= Tx_RX_STS_FIFO_NOTEMPTY;
                        }
                    #else
                        Tx_RXSTATUS_MASK_REG |= Tx_RX_STS_FIFO_NOTEMPTY;
                    #endif /* end Tx_HD_ENABLED */
                #endif /* Tx_RX_INTERRUPT_ENABLED and Hardware flow control*/
            }

        }
        else
        {   rxStatus = Tx_RXSTATUS_REG;
            if((rxStatus & Tx_RX_STS_FIFO_NOTEMPTY) != 0u)
            {   /* Read received data from FIFO */
                rxData = Tx_RXDATA_REG;
                /*Check status on error*/
                if((rxStatus & (Tx_RX_STS_BREAK | Tx_RX_STS_PAR_ERROR |
                                Tx_RX_STS_STOP_ERROR | Tx_RX_STS_OVERRUN)) != 0u)
                {
                    rxData = 0u;
                }
            }
        }

        Tx_EnableRxInt();

    #else

        rxStatus =Tx_RXSTATUS_REG;
        if((rxStatus & Tx_RX_STS_FIFO_NOTEMPTY) != 0u)
        {
            /* Read received data from FIFO */
            rxData = Tx_RXDATA_REG;

            /*Check status on error*/
            if((rxStatus & (Tx_RX_STS_BREAK | Tx_RX_STS_PAR_ERROR |
                            Tx_RX_STS_STOP_ERROR | Tx_RX_STS_OVERRUN)) != 0u)
            {
                rxData = 0u;
            }
        }
    #endif /* (Tx_RX_INTERRUPT_ENABLED) */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: Tx_GetByte
    ********************************************************************************
    *
    * Summary:
    *  Reads UART RX buffer immediately, returns received character and error
    *  condition.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  MSB contains status and LSB contains UART RX data. If the MSB is nonzero,
    *  an error has occurred.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint16 Tx_GetByte(void) 
    {
        
    #if (Tx_RX_INTERRUPT_ENABLED)
        uint16 locErrorStatus;
        /* Protect variables that could change on interrupt */
        Tx_DisableRxInt();
        locErrorStatus = (uint16)Tx_errorStatus;
        Tx_errorStatus = 0u;
        Tx_EnableRxInt();
        return ( (uint16)(locErrorStatus << 8u) | Tx_ReadRxData() );
    #else
        return ( ((uint16)Tx_ReadRxStatus() << 8u) | Tx_ReadRxData() );
    #endif /* Tx_RX_INTERRUPT_ENABLED */
        
    }


    /*******************************************************************************
    * Function Name: Tx_GetRxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of received bytes available in the RX buffer.
    *  * RX software buffer is disabled (RX Buffer Size parameter is equal to 4): 
    *    returns 0 for empty RX FIFO or 1 for not empty RX FIFO.
    *  * RX software buffer is enabled: returns the number of bytes available in 
    *    the RX software buffer. Bytes available in the RX FIFO do not take to 
    *    account.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  uint8: Number of bytes in the RX buffer. 
    *    Return value type depends on RX Buffer Size parameter.
    *
    * Global Variables:
    *  Tx_rxBufferWrite - used to calculate left bytes.
    *  Tx_rxBufferRead - used to calculate left bytes.
    *  Tx_rxBufferLoopDetect - checked to decide left bytes amount.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the RX Buffer is.
    *
    *******************************************************************************/
    uint8 Tx_GetRxBufferSize(void)
                                                            
    {
        uint8 size;

    #if (Tx_RX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt */
        Tx_DisableRxInt();

        if(Tx_rxBufferRead == Tx_rxBufferWrite)
        {
            if(Tx_rxBufferLoopDetect != 0u)
            {
                size = Tx_RX_BUFFER_SIZE;
            }
            else
            {
                size = 0u;
            }
        }
        else if(Tx_rxBufferRead < Tx_rxBufferWrite)
        {
            size = (Tx_rxBufferWrite - Tx_rxBufferRead);
        }
        else
        {
            size = (Tx_RX_BUFFER_SIZE - Tx_rxBufferRead) + Tx_rxBufferWrite;
        }

        Tx_EnableRxInt();

    #else

        /* We can only know if there is data in the fifo. */
        size = ((Tx_RXSTATUS_REG & Tx_RX_STS_FIFO_NOTEMPTY) != 0u) ? 1u : 0u;

    #endif /* (Tx_RX_INTERRUPT_ENABLED) */

        return(size);
    }


    /*******************************************************************************
    * Function Name: Tx_ClearRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the receiver memory buffer and hardware RX FIFO of all received data.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  Tx_rxBufferWrite - cleared to zero.
    *  Tx_rxBufferRead - cleared to zero.
    *  Tx_rxBufferLoopDetect - cleared to zero.
    *  Tx_rxBufferOverflow - cleared to zero.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Setting the pointers to zero makes the system believe there is no data to
    *  read and writing will resume at address 0 overwriting any data that may
    *  have remained in the RAM.
    *
    * Side Effects:
    *  Any received data not read from the RAM or FIFO buffer will be lost.
    *
    *******************************************************************************/
    void Tx_ClearRxBuffer(void) 
    {
        uint8 enableInterrupts;

        /* Clear the HW FIFO */
        enableInterrupts = CyEnterCriticalSection();
        Tx_RXDATA_AUX_CTL_REG |= (uint8)  Tx_RX_FIFO_CLR;
        Tx_RXDATA_AUX_CTL_REG &= (uint8) ~Tx_RX_FIFO_CLR;
        CyExitCriticalSection(enableInterrupts);

    #if (Tx_RX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        Tx_DisableRxInt();

        Tx_rxBufferRead = 0u;
        Tx_rxBufferWrite = 0u;
        Tx_rxBufferLoopDetect = 0u;
        Tx_rxBufferOverflow = 0u;

        Tx_EnableRxInt();

    #endif /* (Tx_RX_INTERRUPT_ENABLED) */

    }


    /*******************************************************************************
    * Function Name: Tx_SetRxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Sets the software controlled Addressing mode used by the RX portion of the
    *  UART.
    *
    * Parameters:
    *  addressMode: Enumerated value indicating the mode of RX addressing
    *  Tx__B_UART__AM_SW_BYTE_BYTE -  Software Byte-by-Byte address
    *                                               detection
    *  Tx__B_UART__AM_SW_DETECT_TO_BUFFER - Software Detect to Buffer
    *                                               address detection
    *  Tx__B_UART__AM_HW_BYTE_BY_BYTE - Hardware Byte-by-Byte address
    *                                               detection
    *  Tx__B_UART__AM_HW_DETECT_TO_BUFFER - Hardware Detect to Buffer
    *                                               address detection
    *  Tx__B_UART__AM_NONE - No address detection
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  Tx_rxAddressMode - the parameter stored in this variable for
    *   the farther usage in RX ISR.
    *  Tx_rxAddressDetected - set to initial state (0).
    *
    *******************************************************************************/
    void Tx_SetRxAddressMode(uint8 addressMode)
                                                        
    {
        #if(Tx_RXHW_ADDRESS_ENABLED)
            #if(Tx_CONTROL_REG_REMOVED)
                if(0u != addressMode)
                {
                    /* Suppress compiler warning */
                }
            #else /* Tx_CONTROL_REG_REMOVED */
                uint8 tmpCtrl;
                tmpCtrl = Tx_CONTROL_REG & (uint8)~Tx_CTRL_RXADDR_MODE_MASK;
                tmpCtrl |= (uint8)(addressMode << Tx_CTRL_RXADDR_MODE0_SHIFT);
                Tx_CONTROL_REG = tmpCtrl;

                #if(Tx_RX_INTERRUPT_ENABLED && \
                   (Tx_RXBUFFERSIZE > Tx_FIFO_LENGTH) )
                    Tx_rxAddressMode = addressMode;
                    Tx_rxAddressDetected = 0u;
                #endif /* End Tx_RXBUFFERSIZE > Tx_FIFO_LENGTH*/
            #endif /* End Tx_CONTROL_REG_REMOVED */
        #else /* Tx_RXHW_ADDRESS_ENABLED */
            if(0u != addressMode)
            {
                /* Suppress compiler warning */
            }
        #endif /* End Tx_RXHW_ADDRESS_ENABLED */
    }


    /*******************************************************************************
    * Function Name: Tx_SetRxAddress1
    ********************************************************************************
    *
    * Summary:
    *  Sets the first of two hardware-detectable receiver addresses.
    *
    * Parameters:
    *  address: Address #1 for hardware address detection.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void Tx_SetRxAddress1(uint8 address) 
    {
        Tx_RXADDRESS1_REG = address;
    }


    /*******************************************************************************
    * Function Name: Tx_SetRxAddress2
    ********************************************************************************
    *
    * Summary:
    *  Sets the second of two hardware-detectable receiver addresses.
    *
    * Parameters:
    *  address: Address #2 for hardware address detection.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void Tx_SetRxAddress2(uint8 address) 
    {
        Tx_RXADDRESS2_REG = address;
    }

#endif  /* Tx_RX_ENABLED || Tx_HD_ENABLED*/


#if( (Tx_TX_ENABLED) || (Tx_HD_ENABLED) )
    /*******************************************************************************
    * Function Name: Tx_SetTxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the TX interrupt sources to be enabled, but does not enable the
    *  interrupt.
    *
    * Parameters:
    *  intSrc: Bit field containing the TX interrupt sources to enable
    *   Tx_TX_STS_COMPLETE        Interrupt on TX byte complete
    *   Tx_TX_STS_FIFO_EMPTY      Interrupt when TX FIFO is empty
    *   Tx_TX_STS_FIFO_FULL       Interrupt when TX FIFO is full
    *   Tx_TX_STS_FIFO_NOT_FULL   Interrupt when TX FIFO is not full
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void Tx_SetTxInterruptMode(uint8 intSrc) 
    {
        Tx_TXSTATUS_MASK_REG = intSrc;
    }


    /*******************************************************************************
    * Function Name: Tx_WriteTxData
    ********************************************************************************
    *
    * Summary:
    *  Places a byte of data into the transmit buffer to be sent when the bus is
    *  available without checking the TX status register. You must check status
    *  separately.
    *
    * Parameters:
    *  txDataByte: data byte
    *
    * Return:
    * None.
    *
    * Global Variables:
    *  Tx_txBuffer - RAM buffer pointer for save data for transmission
    *  Tx_txBufferWrite - cyclic index for write to txBuffer,
    *    incremented after each byte saved to buffer.
    *  Tx_txBufferRead - cyclic index for read from txBuffer,
    *    checked to identify the condition to write to FIFO directly or to TX buffer
    *  Tx_initVar - checked to identify that the component has been
    *    initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void Tx_WriteTxData(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function*/
        if(Tx_initVar != 0u)
        {
        #if (Tx_TX_INTERRUPT_ENABLED)

            /* Protect variables that could change on interrupt. */
            Tx_DisableTxInt();

            if( (Tx_txBufferRead == Tx_txBufferWrite) &&
                ((Tx_TXSTATUS_REG & Tx_TX_STS_FIFO_FULL) == 0u) )
            {
                /* Add directly to the FIFO. */
                Tx_TXDATA_REG = txDataByte;
            }
            else
            {
                if(Tx_txBufferWrite >= Tx_TX_BUFFER_SIZE)
                {
                    Tx_txBufferWrite = 0u;
                }

                Tx_txBuffer[Tx_txBufferWrite] = txDataByte;

                /* Add to the software buffer. */
                Tx_txBufferWrite++;
            }

            Tx_EnableTxInt();

        #else

            /* Add directly to the FIFO. */
            Tx_TXDATA_REG = txDataByte;

        #endif /*(Tx_TX_INTERRUPT_ENABLED) */
        }
    }


    /*******************************************************************************
    * Function Name: Tx_ReadTxStatus
    ********************************************************************************
    *
    * Summary:
    *  Reads the status register for the TX portion of the UART.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Contents of the status register
    *
    * Theory:
    *  This function reads the TX status register, which is cleared on read.
    *  It is up to the user to handle all bits in this return value accordingly,
    *  even if the bit was not enabled as an interrupt source the event happened
    *  and must be handled accordingly.
    *
    *******************************************************************************/
    uint8 Tx_ReadTxStatus(void) 
    {
        return(Tx_TXSTATUS_REG);
    }


    /*******************************************************************************
    * Function Name: Tx_PutChar
    ********************************************************************************
    *
    * Summary:
    *  Puts a byte of data into the transmit buffer to be sent when the bus is
    *  available. This is a blocking API that waits until the TX buffer has room to
    *  hold the data.
    *
    * Parameters:
    *  txDataByte: Byte containing the data to transmit
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  Tx_txBuffer - RAM buffer pointer for save data for transmission
    *  Tx_txBufferWrite - cyclic index for write to txBuffer,
    *     checked to identify free space in txBuffer and incremented after each byte
    *     saved to buffer.
    *  Tx_txBufferRead - cyclic index for read from txBuffer,
    *     checked to identify free space in txBuffer.
    *  Tx_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to transmit any byte of data in a single transfer
    *
    *******************************************************************************/
    void Tx_PutChar(uint8 txDataByte) 
    {
    #if (Tx_TX_INTERRUPT_ENABLED)
        /* The temporary output pointer is used since it takes two instructions
        *  to increment with a wrap, and we can't risk doing that with the real
        *  pointer and getting an interrupt in between instructions.
        */
        uint8 locTxBufferWrite;
        uint8 locTxBufferRead;

        do
        { /* Block if software buffer is full, so we don't overwrite. */

        #if ((Tx_TX_BUFFER_SIZE > Tx_MAX_BYTE_VALUE) && (CY_PSOC3))
            /* Disable TX interrupt to protect variables from modification */
            Tx_DisableTxInt();
        #endif /* (Tx_TX_BUFFER_SIZE > 255) */

            locTxBufferWrite = Tx_txBufferWrite;
            locTxBufferRead  = Tx_txBufferRead;

        #if ((Tx_TX_BUFFER_SIZE > Tx_MAX_BYTE_VALUE) && (CY_PSOC3))
            /* Enable interrupt to continue transmission */
            Tx_EnableTxInt();
        #endif /* (Tx_TX_BUFFER_SIZE > 255) */
        }
        while( (locTxBufferWrite < locTxBufferRead) ? (locTxBufferWrite == (locTxBufferRead - 1u)) :
                                ((locTxBufferWrite - locTxBufferRead) ==
                                (uint8)(Tx_TX_BUFFER_SIZE - 1u)) );

        if( (locTxBufferRead == locTxBufferWrite) &&
            ((Tx_TXSTATUS_REG & Tx_TX_STS_FIFO_FULL) == 0u) )
        {
            /* Add directly to the FIFO */
            Tx_TXDATA_REG = txDataByte;
        }
        else
        {
            if(locTxBufferWrite >= Tx_TX_BUFFER_SIZE)
            {
                locTxBufferWrite = 0u;
            }
            /* Add to the software buffer. */
            Tx_txBuffer[locTxBufferWrite] = txDataByte;
            locTxBufferWrite++;

            /* Finally, update the real output pointer */
        #if ((Tx_TX_BUFFER_SIZE > Tx_MAX_BYTE_VALUE) && (CY_PSOC3))
            Tx_DisableTxInt();
        #endif /* (Tx_TX_BUFFER_SIZE > 255) */

            Tx_txBufferWrite = locTxBufferWrite;

        #if ((Tx_TX_BUFFER_SIZE > Tx_MAX_BYTE_VALUE) && (CY_PSOC3))
            Tx_EnableTxInt();
        #endif /* (Tx_TX_BUFFER_SIZE > 255) */

            if(0u != (Tx_TXSTATUS_REG & Tx_TX_STS_FIFO_EMPTY))
            {
                /* Trigger TX interrupt to send software buffer */
                Tx_SetPendingTxInt();
            }
        }

    #else

        while((Tx_TXSTATUS_REG & Tx_TX_STS_FIFO_FULL) != 0u)
        {
            /* Wait for room in the FIFO */
        }

        /* Add directly to the FIFO */
        Tx_TXDATA_REG = txDataByte;

    #endif /* End (Tx_TX_INTERRUPT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: Tx_PutString
    ********************************************************************************
    *
    * Summary:
    *  Sends a NULL terminated string to the TX buffer for transmission.
    *
    * Parameters:
    *  string[]: Pointer to the null terminated string array residing in RAM or ROM
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  Tx_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  If there is not enough memory in the TX buffer for the entire string, this
    *  function blocks until the last character of the string is loaded into the
    *  TX buffer.
    *
    *******************************************************************************/
    void Tx_PutString(const char8 string[]) 
    {
        uint16 bufIndex = 0u;

        /* If not Initialized then skip this function */
        if(Tx_initVar != 0u)
        {
            /* This is a blocking function, it will not exit until all data is sent */
            while(string[bufIndex] != (char8) 0)
            {
                Tx_PutChar((uint8)string[bufIndex]);
                bufIndex++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: Tx_PutArray
    ********************************************************************************
    *
    * Summary:
    *  Places N bytes of data from a memory array into the TX buffer for
    *  transmission.
    *
    * Parameters:
    *  string[]: Address of the memory array residing in RAM or ROM.
    *  byteCount: Number of bytes to be transmitted. The type depends on TX Buffer
    *             Size parameter.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  Tx_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  If there is not enough memory in the TX buffer for the entire string, this
    *  function blocks until the last character of the string is loaded into the
    *  TX buffer.
    *
    *******************************************************************************/
    void Tx_PutArray(const uint8 string[], uint8 byteCount)
                                                                    
    {
        uint8 bufIndex = 0u;

        /* If not Initialized then skip this function */
        if(Tx_initVar != 0u)
        {
            while(bufIndex < byteCount)
            {
                Tx_PutChar(string[bufIndex]);
                bufIndex++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: Tx_PutCRLF
    ********************************************************************************
    *
    * Summary:
    *  Writes a byte of data followed by a carriage return (0x0D) and line feed
    *  (0x0A) to the transmit buffer.
    *
    * Parameters:
    *  txDataByte: Data byte to transmit before the carriage return and line feed.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  Tx_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void Tx_PutCRLF(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function */
        if(Tx_initVar != 0u)
        {
            Tx_PutChar(txDataByte);
            Tx_PutChar(0x0Du);
            Tx_PutChar(0x0Au);
        }
    }


    /*******************************************************************************
    * Function Name: Tx_GetTxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of bytes in the TX buffer which are waiting to be 
    *  transmitted.
    *  * TX software buffer is disabled (TX Buffer Size parameter is equal to 4): 
    *    returns 0 for empty TX FIFO, 1 for not full TX FIFO or 4 for full TX FIFO.
    *  * TX software buffer is enabled: returns the number of bytes in the TX 
    *    software buffer which are waiting to be transmitted. Bytes available in the
    *    TX FIFO do not take to account.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Number of bytes used in the TX buffer. Return value type depends on the TX 
    *  Buffer Size parameter.
    *
    * Global Variables:
    *  Tx_txBufferWrite - used to calculate left space.
    *  Tx_txBufferRead - used to calculate left space.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the TX Buffer is.
    *
    *******************************************************************************/
    uint8 Tx_GetTxBufferSize(void)
                                                            
    {
        uint8 size;

    #if (Tx_TX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        Tx_DisableTxInt();

        if(Tx_txBufferRead == Tx_txBufferWrite)
        {
            size = 0u;
        }
        else if(Tx_txBufferRead < Tx_txBufferWrite)
        {
            size = (Tx_txBufferWrite - Tx_txBufferRead);
        }
        else
        {
            size = (Tx_TX_BUFFER_SIZE - Tx_txBufferRead) +
                    Tx_txBufferWrite;
        }

        Tx_EnableTxInt();

    #else

        size = Tx_TXSTATUS_REG;

        /* Is the fifo is full. */
        if((size & Tx_TX_STS_FIFO_FULL) != 0u)
        {
            size = Tx_FIFO_LENGTH;
        }
        else if((size & Tx_TX_STS_FIFO_EMPTY) != 0u)
        {
            size = 0u;
        }
        else
        {
            /* We only know there is data in the fifo. */
            size = 1u;
        }

    #endif /* (Tx_TX_INTERRUPT_ENABLED) */

    return(size);
    }


    /*******************************************************************************
    * Function Name: Tx_ClearTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears all data from the TX buffer and hardware TX FIFO.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  Tx_txBufferWrite - cleared to zero.
    *  Tx_txBufferRead - cleared to zero.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Setting the pointers to zero makes the system believe there is no data to
    *  read and writing will resume at address 0 overwriting any data that may have
    *  remained in the RAM.
    *
    * Side Effects:
    *  Data waiting in the transmit buffer is not sent; a byte that is currently
    *  transmitting finishes transmitting.
    *
    *******************************************************************************/
    void Tx_ClearTxBuffer(void) 
    {
        uint8 enableInterrupts;

        enableInterrupts = CyEnterCriticalSection();
        /* Clear the HW FIFO */
        Tx_TXDATA_AUX_CTL_REG |= (uint8)  Tx_TX_FIFO_CLR;
        Tx_TXDATA_AUX_CTL_REG &= (uint8) ~Tx_TX_FIFO_CLR;
        CyExitCriticalSection(enableInterrupts);

    #if (Tx_TX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        Tx_DisableTxInt();

        Tx_txBufferRead = 0u;
        Tx_txBufferWrite = 0u;

        /* Enable Tx interrupt. */
        Tx_EnableTxInt();

    #endif /* (Tx_TX_INTERRUPT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: Tx_SendBreak
    ********************************************************************************
    *
    * Summary:
    *  Transmits a break signal on the bus.
    *
    * Parameters:
    *  uint8 retMode:  Send Break return mode. See the following table for options.
    *   Tx_SEND_BREAK - Initialize registers for break, send the Break
    *       signal and return immediately.
    *   Tx_WAIT_FOR_COMPLETE_REINIT - Wait until break transmission is
    *       complete, reinitialize registers to normal transmission mode then return
    *   Tx_REINIT - Reinitialize registers to normal transmission mode
    *       then return.
    *   Tx_SEND_WAIT_REINIT - Performs both options: 
    *      Tx_SEND_BREAK and Tx_WAIT_FOR_COMPLETE_REINIT.
    *      This option is recommended for most cases.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  Tx_initVar - checked to identify that the component has been
    *     initialized.
    *  txPeriod - static variable, used for keeping TX period configuration.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  SendBreak function initializes registers to send 13-bit break signal. It is
    *  important to return the registers configuration to normal for continue 8-bit
    *  operation.
    *  There are 3 variants for this API usage:
    *  1) SendBreak(3) - function will send the Break signal and take care on the
    *     configuration returning. Function will block CPU until transmission
    *     complete.
    *  2) User may want to use blocking time if UART configured to the low speed
    *     operation
    *     Example for this case:
    *     SendBreak(0);     - initialize Break signal transmission
    *         Add your code here to use CPU time
    *     SendBreak(1);     - complete Break operation
    *  3) Same to 2) but user may want to initialize and use the interrupt to
    *     complete break operation.
    *     Example for this case:
    *     Initialize TX interrupt with "TX - On TX Complete" parameter
    *     SendBreak(0);     - initialize Break signal transmission
    *         Add your code here to use CPU time
    *     When interrupt appear with Tx_TX_STS_COMPLETE status:
    *     SendBreak(2);     - complete Break operation
    *
    * Side Effects:
    *  The Tx_SendBreak() function initializes registers to send a
    *  break signal.
    *  Break signal length depends on the break signal bits configuration.
    *  The register configuration should be reinitialized before normal 8-bit
    *  communication can continue.
    *
    *******************************************************************************/
    void Tx_SendBreak(uint8 retMode) 
    {

        /* If not Initialized then skip this function*/
        if(Tx_initVar != 0u)
        {
            /* Set the Counter to 13-bits and transmit a 00 byte */
            /* When that is done then reset the counter value back */
            uint8 tmpStat;

        #if(Tx_HD_ENABLED) /* Half Duplex mode*/

            if( (retMode == Tx_SEND_BREAK) ||
                (retMode == Tx_SEND_WAIT_REINIT ) )
            {
                /* CTRL_HD_SEND_BREAK - sends break bits in HD mode */
                Tx_WriteControlRegister(Tx_ReadControlRegister() |
                                                      Tx_CTRL_HD_SEND_BREAK);
                /* Send zeros */
                Tx_TXDATA_REG = 0u;

                do /* Wait until transmit starts */
                {
                    tmpStat = Tx_TXSTATUS_REG;
                }
                while((tmpStat & Tx_TX_STS_FIFO_EMPTY) != 0u);
            }

            if( (retMode == Tx_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == Tx_SEND_WAIT_REINIT) )
            {
                do /* Wait until transmit complete */
                {
                    tmpStat = Tx_TXSTATUS_REG;
                }
                while(((uint8)~tmpStat & Tx_TX_STS_COMPLETE) != 0u);
            }

            if( (retMode == Tx_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == Tx_REINIT) ||
                (retMode == Tx_SEND_WAIT_REINIT) )
            {
                Tx_WriteControlRegister(Tx_ReadControlRegister() &
                                              (uint8)~Tx_CTRL_HD_SEND_BREAK);
            }

        #else /* Tx_HD_ENABLED Full Duplex mode */

            static uint8 txPeriod;

            if( (retMode == Tx_SEND_BREAK) ||
                (retMode == Tx_SEND_WAIT_REINIT) )
            {
                /* CTRL_HD_SEND_BREAK - skip to send parity bit at Break signal in Full Duplex mode */
                #if( (Tx_PARITY_TYPE != Tx__B_UART__NONE_REVB) || \
                                    (Tx_PARITY_TYPE_SW != 0u) )
                    Tx_WriteControlRegister(Tx_ReadControlRegister() |
                                                          Tx_CTRL_HD_SEND_BREAK);
                #endif /* End Tx_PARITY_TYPE != Tx__B_UART__NONE_REVB  */

                #if(Tx_TXCLKGEN_DP)
                    txPeriod = Tx_TXBITCLKTX_COMPLETE_REG;
                    Tx_TXBITCLKTX_COMPLETE_REG = Tx_TXBITCTR_BREAKBITS;
                #else
                    txPeriod = Tx_TXBITCTR_PERIOD_REG;
                    Tx_TXBITCTR_PERIOD_REG = Tx_TXBITCTR_BREAKBITS8X;
                #endif /* End Tx_TXCLKGEN_DP */

                /* Send zeros */
                Tx_TXDATA_REG = 0u;

                do /* Wait until transmit starts */
                {
                    tmpStat = Tx_TXSTATUS_REG;
                }
                while((tmpStat & Tx_TX_STS_FIFO_EMPTY) != 0u);
            }

            if( (retMode == Tx_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == Tx_SEND_WAIT_REINIT) )
            {
                do /* Wait until transmit complete */
                {
                    tmpStat = Tx_TXSTATUS_REG;
                }
                while(((uint8)~tmpStat & Tx_TX_STS_COMPLETE) != 0u);
            }

            if( (retMode == Tx_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == Tx_REINIT) ||
                (retMode == Tx_SEND_WAIT_REINIT) )
            {

            #if(Tx_TXCLKGEN_DP)
                Tx_TXBITCLKTX_COMPLETE_REG = txPeriod;
            #else
                Tx_TXBITCTR_PERIOD_REG = txPeriod;
            #endif /* End Tx_TXCLKGEN_DP */

            #if( (Tx_PARITY_TYPE != Tx__B_UART__NONE_REVB) || \
                 (Tx_PARITY_TYPE_SW != 0u) )
                Tx_WriteControlRegister(Tx_ReadControlRegister() &
                                                      (uint8) ~Tx_CTRL_HD_SEND_BREAK);
            #endif /* End Tx_PARITY_TYPE != NONE */
            }
        #endif    /* End Tx_HD_ENABLED */
        }
    }


    /*******************************************************************************
    * Function Name: Tx_SetTxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the transmitter to signal the next bytes is address or data.
    *
    * Parameters:
    *  addressMode: 
    *       Tx_SET_SPACE - Configure the transmitter to send the next
    *                                    byte as a data.
    *       Tx_SET_MARK  - Configure the transmitter to send the next
    *                                    byte as an address.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  This function sets and clears Tx_CTRL_MARK bit in the Control
    *  register.
    *
    *******************************************************************************/
    void Tx_SetTxAddressMode(uint8 addressMode) 
    {
        /* Mark/Space sending enable */
        if(addressMode != 0u)
        {
        #if( Tx_CONTROL_REG_REMOVED == 0u )
            Tx_WriteControlRegister(Tx_ReadControlRegister() |
                                                  Tx_CTRL_MARK);
        #endif /* End Tx_CONTROL_REG_REMOVED == 0u */
        }
        else
        {
        #if( Tx_CONTROL_REG_REMOVED == 0u )
            Tx_WriteControlRegister(Tx_ReadControlRegister() &
                                                  (uint8) ~Tx_CTRL_MARK);
        #endif /* End Tx_CONTROL_REG_REMOVED == 0u */
        }
    }

#endif  /* EndTx_TX_ENABLED */

#if(Tx_HD_ENABLED)


    /*******************************************************************************
    * Function Name: Tx_LoadRxConfig
    ********************************************************************************
    *
    * Summary:
    *  Loads the receiver configuration in half duplex mode. After calling this
    *  function, the UART is ready to receive data.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  Valid only in half duplex mode. You must make sure that the previous
    *  transaction is complete and it is safe to unload the transmitter
    *  configuration.
    *
    *******************************************************************************/
    void Tx_LoadRxConfig(void) 
    {
        Tx_WriteControlRegister(Tx_ReadControlRegister() &
                                                (uint8)~Tx_CTRL_HD_SEND);
        Tx_RXBITCTR_PERIOD_REG = Tx_HD_RXBITCTR_INIT;

    #if (Tx_RX_INTERRUPT_ENABLED)
        /* Enable RX interrupt after set RX configuration */
        Tx_SetRxInterruptMode(Tx_INIT_RX_INTERRUPTS_MASK);
    #endif /* (Tx_RX_INTERRUPT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: Tx_LoadTxConfig
    ********************************************************************************
    *
    * Summary:
    *  Loads the transmitter configuration in half duplex mode. After calling this
    *  function, the UART is ready to transmit data.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  Valid only in half duplex mode. You must make sure that the previous
    *  transaction is complete and it is safe to unload the receiver configuration.
    *
    *******************************************************************************/
    void Tx_LoadTxConfig(void) 
    {
    #if (Tx_RX_INTERRUPT_ENABLED)
        /* Disable RX interrupts before set TX configuration */
        Tx_SetRxInterruptMode(0u);
    #endif /* (Tx_RX_INTERRUPT_ENABLED) */

        Tx_WriteControlRegister(Tx_ReadControlRegister() | Tx_CTRL_HD_SEND);
        Tx_RXBITCTR_PERIOD_REG = Tx_HD_TXBITCTR_INIT;
    }

#endif  /* Tx_HD_ENABLED */


/* [] END OF FILE */
