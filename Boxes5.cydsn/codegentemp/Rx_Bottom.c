/*******************************************************************************
* File Name: Rx_Bottom.c
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

#include "Rx_Bottom.h"
#if (Rx_Bottom_INTERNAL_CLOCK_USED)
    #include "Rx_Bottom_IntClock.h"
#endif /* End Rx_Bottom_INTERNAL_CLOCK_USED */


/***************************************
* Global data allocation
***************************************/

uint8 Rx_Bottom_initVar = 0u;

#if (Rx_Bottom_TX_INTERRUPT_ENABLED && Rx_Bottom_TX_ENABLED)
    volatile uint8 Rx_Bottom_txBuffer[Rx_Bottom_TX_BUFFER_SIZE];
    volatile uint8 Rx_Bottom_txBufferRead = 0u;
    uint8 Rx_Bottom_txBufferWrite = 0u;
#endif /* (Rx_Bottom_TX_INTERRUPT_ENABLED && Rx_Bottom_TX_ENABLED) */

#if (Rx_Bottom_RX_INTERRUPT_ENABLED && (Rx_Bottom_RX_ENABLED || Rx_Bottom_HD_ENABLED))
    uint8 Rx_Bottom_errorStatus = 0u;
    volatile uint8 Rx_Bottom_rxBuffer[Rx_Bottom_RX_BUFFER_SIZE];
    volatile uint8 Rx_Bottom_rxBufferRead  = 0u;
    volatile uint8 Rx_Bottom_rxBufferWrite = 0u;
    volatile uint8 Rx_Bottom_rxBufferLoopDetect = 0u;
    volatile uint8 Rx_Bottom_rxBufferOverflow   = 0u;
    #if (Rx_Bottom_RXHW_ADDRESS_ENABLED)
        volatile uint8 Rx_Bottom_rxAddressMode = Rx_Bottom_RX_ADDRESS_MODE;
        volatile uint8 Rx_Bottom_rxAddressDetected = 0u;
    #endif /* (Rx_Bottom_RXHW_ADDRESS_ENABLED) */
#endif /* (Rx_Bottom_RX_INTERRUPT_ENABLED && (Rx_Bottom_RX_ENABLED || Rx_Bottom_HD_ENABLED)) */


/*******************************************************************************
* Function Name: Rx_Bottom_Start
********************************************************************************
*
* Summary:
*  This is the preferred method to begin component operation.
*  Rx_Bottom_Start() sets the initVar variable, calls the
*  Rx_Bottom_Init() function, and then calls the
*  Rx_Bottom_Enable() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  The Rx_Bottom_intiVar variable is used to indicate initial
*  configuration of this component. The variable is initialized to zero (0u)
*  and set to one (1u) the first time Rx_Bottom_Start() is called. This
*  allows for component initialization without re-initialization in all
*  subsequent calls to the Rx_Bottom_Start() routine.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Rx_Bottom_Start(void) 
{
    /* If not initialized then initialize all required hardware and software */
    if(Rx_Bottom_initVar == 0u)
    {
        Rx_Bottom_Init();
        Rx_Bottom_initVar = 1u;
    }

    Rx_Bottom_Enable();
}


/*******************************************************************************
* Function Name: Rx_Bottom_Init
********************************************************************************
*
* Summary:
*  Initializes or restores the component according to the customizer Configure
*  dialog settings. It is not necessary to call Rx_Bottom_Init() because
*  the Rx_Bottom_Start() API calls this function and is the preferred
*  method to begin component operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Rx_Bottom_Init(void) 
{
    #if(Rx_Bottom_RX_ENABLED || Rx_Bottom_HD_ENABLED)

        #if (Rx_Bottom_RX_INTERRUPT_ENABLED)
            /* Set RX interrupt vector and priority */
            (void) CyIntSetVector(Rx_Bottom_RX_VECT_NUM, &Rx_Bottom_RXISR);
            CyIntSetPriority(Rx_Bottom_RX_VECT_NUM, Rx_Bottom_RX_PRIOR_NUM);
            Rx_Bottom_errorStatus = 0u;
        #endif /* (Rx_Bottom_RX_INTERRUPT_ENABLED) */

        #if (Rx_Bottom_RXHW_ADDRESS_ENABLED)
            Rx_Bottom_SetRxAddressMode(Rx_Bottom_RX_ADDRESS_MODE);
            Rx_Bottom_SetRxAddress1(Rx_Bottom_RX_HW_ADDRESS1);
            Rx_Bottom_SetRxAddress2(Rx_Bottom_RX_HW_ADDRESS2);
        #endif /* End Rx_Bottom_RXHW_ADDRESS_ENABLED */

        /* Init Count7 period */
        Rx_Bottom_RXBITCTR_PERIOD_REG = Rx_Bottom_RXBITCTR_INIT;
        /* Configure the Initial RX interrupt mask */
        Rx_Bottom_RXSTATUS_MASK_REG  = Rx_Bottom_INIT_RX_INTERRUPTS_MASK;
    #endif /* End Rx_Bottom_RX_ENABLED || Rx_Bottom_HD_ENABLED*/

    #if(Rx_Bottom_TX_ENABLED)
        #if (Rx_Bottom_TX_INTERRUPT_ENABLED)
            /* Set TX interrupt vector and priority */
            (void) CyIntSetVector(Rx_Bottom_TX_VECT_NUM, &Rx_Bottom_TXISR);
            CyIntSetPriority(Rx_Bottom_TX_VECT_NUM, Rx_Bottom_TX_PRIOR_NUM);
        #endif /* (Rx_Bottom_TX_INTERRUPT_ENABLED) */

        /* Write Counter Value for TX Bit Clk Generator*/
        #if (Rx_Bottom_TXCLKGEN_DP)
            Rx_Bottom_TXBITCLKGEN_CTR_REG = Rx_Bottom_BIT_CENTER;
            Rx_Bottom_TXBITCLKTX_COMPLETE_REG = ((Rx_Bottom_NUMBER_OF_DATA_BITS +
                        Rx_Bottom_NUMBER_OF_START_BIT) * Rx_Bottom_OVER_SAMPLE_COUNT) - 1u;
        #else
            Rx_Bottom_TXBITCTR_PERIOD_REG = ((Rx_Bottom_NUMBER_OF_DATA_BITS +
                        Rx_Bottom_NUMBER_OF_START_BIT) * Rx_Bottom_OVER_SAMPLE_8) - 1u;
        #endif /* End Rx_Bottom_TXCLKGEN_DP */

        /* Configure the Initial TX interrupt mask */
        #if (Rx_Bottom_TX_INTERRUPT_ENABLED)
            Rx_Bottom_TXSTATUS_MASK_REG = Rx_Bottom_TX_STS_FIFO_EMPTY;
        #else
            Rx_Bottom_TXSTATUS_MASK_REG = Rx_Bottom_INIT_TX_INTERRUPTS_MASK;
        #endif /*End Rx_Bottom_TX_INTERRUPT_ENABLED*/

    #endif /* End Rx_Bottom_TX_ENABLED */

    #if(Rx_Bottom_PARITY_TYPE_SW)  /* Write Parity to Control Register */
        Rx_Bottom_WriteControlRegister( \
            (Rx_Bottom_ReadControlRegister() & (uint8)~Rx_Bottom_CTRL_PARITY_TYPE_MASK) | \
            (uint8)(Rx_Bottom_PARITY_TYPE << Rx_Bottom_CTRL_PARITY_TYPE0_SHIFT) );
    #endif /* End Rx_Bottom_PARITY_TYPE_SW */
}


/*******************************************************************************
* Function Name: Rx_Bottom_Enable
********************************************************************************
*
* Summary:
*  Activates the hardware and begins component operation. It is not necessary
*  to call Rx_Bottom_Enable() because the Rx_Bottom_Start() API
*  calls this function, which is the preferred method to begin component
*  operation.

* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  Rx_Bottom_rxAddressDetected - set to initial state (0).
*
*******************************************************************************/
void Rx_Bottom_Enable(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    #if (Rx_Bottom_RX_ENABLED || Rx_Bottom_HD_ENABLED)
        /* RX Counter (Count7) Enable */
        Rx_Bottom_RXBITCTR_CONTROL_REG |= Rx_Bottom_CNTR_ENABLE;

        /* Enable the RX Interrupt */
        Rx_Bottom_RXSTATUS_ACTL_REG  |= Rx_Bottom_INT_ENABLE;

        #if (Rx_Bottom_RX_INTERRUPT_ENABLED)
            Rx_Bottom_EnableRxInt();

            #if (Rx_Bottom_RXHW_ADDRESS_ENABLED)
                Rx_Bottom_rxAddressDetected = 0u;
            #endif /* (Rx_Bottom_RXHW_ADDRESS_ENABLED) */
        #endif /* (Rx_Bottom_RX_INTERRUPT_ENABLED) */
    #endif /* (Rx_Bottom_RX_ENABLED || Rx_Bottom_HD_ENABLED) */

    #if(Rx_Bottom_TX_ENABLED)
        /* TX Counter (DP/Count7) Enable */
        #if(!Rx_Bottom_TXCLKGEN_DP)
            Rx_Bottom_TXBITCTR_CONTROL_REG |= Rx_Bottom_CNTR_ENABLE;
        #endif /* End Rx_Bottom_TXCLKGEN_DP */

        /* Enable the TX Interrupt */
        Rx_Bottom_TXSTATUS_ACTL_REG |= Rx_Bottom_INT_ENABLE;
        #if (Rx_Bottom_TX_INTERRUPT_ENABLED)
            Rx_Bottom_ClearPendingTxInt(); /* Clear history of TX_NOT_EMPTY */
            Rx_Bottom_EnableTxInt();
        #endif /* (Rx_Bottom_TX_INTERRUPT_ENABLED) */
     #endif /* (Rx_Bottom_TX_INTERRUPT_ENABLED) */

    #if (Rx_Bottom_INTERNAL_CLOCK_USED)
        Rx_Bottom_IntClock_Start();  /* Enable the clock */
    #endif /* (Rx_Bottom_INTERNAL_CLOCK_USED) */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Rx_Bottom_Stop
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
void Rx_Bottom_Stop(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    /* Write Bit Counter Disable */
    #if (Rx_Bottom_RX_ENABLED || Rx_Bottom_HD_ENABLED)
        Rx_Bottom_RXBITCTR_CONTROL_REG &= (uint8) ~Rx_Bottom_CNTR_ENABLE;
    #endif /* (Rx_Bottom_RX_ENABLED || Rx_Bottom_HD_ENABLED) */

    #if (Rx_Bottom_TX_ENABLED)
        #if(!Rx_Bottom_TXCLKGEN_DP)
            Rx_Bottom_TXBITCTR_CONTROL_REG &= (uint8) ~Rx_Bottom_CNTR_ENABLE;
        #endif /* (!Rx_Bottom_TXCLKGEN_DP) */
    #endif /* (Rx_Bottom_TX_ENABLED) */

    #if (Rx_Bottom_INTERNAL_CLOCK_USED)
        Rx_Bottom_IntClock_Stop();   /* Disable the clock */
    #endif /* (Rx_Bottom_INTERNAL_CLOCK_USED) */

    /* Disable internal interrupt component */
    #if (Rx_Bottom_RX_ENABLED || Rx_Bottom_HD_ENABLED)
        Rx_Bottom_RXSTATUS_ACTL_REG  &= (uint8) ~Rx_Bottom_INT_ENABLE;

        #if (Rx_Bottom_RX_INTERRUPT_ENABLED)
            Rx_Bottom_DisableRxInt();
        #endif /* (Rx_Bottom_RX_INTERRUPT_ENABLED) */
    #endif /* (Rx_Bottom_RX_ENABLED || Rx_Bottom_HD_ENABLED) */

    #if (Rx_Bottom_TX_ENABLED)
        Rx_Bottom_TXSTATUS_ACTL_REG &= (uint8) ~Rx_Bottom_INT_ENABLE;

        #if (Rx_Bottom_TX_INTERRUPT_ENABLED)
            Rx_Bottom_DisableTxInt();
        #endif /* (Rx_Bottom_TX_INTERRUPT_ENABLED) */
    #endif /* (Rx_Bottom_TX_ENABLED) */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Rx_Bottom_ReadControlRegister
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
uint8 Rx_Bottom_ReadControlRegister(void) 
{
    #if (Rx_Bottom_CONTROL_REG_REMOVED)
        return(0u);
    #else
        return(Rx_Bottom_CONTROL_REG);
    #endif /* (Rx_Bottom_CONTROL_REG_REMOVED) */
}


/*******************************************************************************
* Function Name: Rx_Bottom_WriteControlRegister
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
void  Rx_Bottom_WriteControlRegister(uint8 control) 
{
    #if (Rx_Bottom_CONTROL_REG_REMOVED)
        if(0u != control)
        {
            /* Suppress compiler warning */
        }
    #else
       Rx_Bottom_CONTROL_REG = control;
    #endif /* (Rx_Bottom_CONTROL_REG_REMOVED) */
}


#if(Rx_Bottom_RX_ENABLED || Rx_Bottom_HD_ENABLED)
    /*******************************************************************************
    * Function Name: Rx_Bottom_SetRxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the RX interrupt sources enabled.
    *
    * Parameters:
    *  IntSrc:  Bit field containing the RX interrupts to enable. Based on the 
    *  bit-field arrangement of the status register. This value must be a 
    *  combination of status register bit-masks shown below:
    *      Rx_Bottom_RX_STS_FIFO_NOTEMPTY    Interrupt on byte received.
    *      Rx_Bottom_RX_STS_PAR_ERROR        Interrupt on parity error.
    *      Rx_Bottom_RX_STS_STOP_ERROR       Interrupt on stop error.
    *      Rx_Bottom_RX_STS_BREAK            Interrupt on break.
    *      Rx_Bottom_RX_STS_OVERRUN          Interrupt on overrun error.
    *      Rx_Bottom_RX_STS_ADDR_MATCH       Interrupt on address match.
    *      Rx_Bottom_RX_STS_MRKSPC           Interrupt on address detect.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void Rx_Bottom_SetRxInterruptMode(uint8 intSrc) 
    {
        Rx_Bottom_RXSTATUS_MASK_REG  = intSrc;
    }


    /*******************************************************************************
    * Function Name: Rx_Bottom_ReadRxData
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
    *  Rx_Bottom_rxBuffer - RAM buffer pointer for save received data.
    *  Rx_Bottom_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  Rx_Bottom_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  Rx_Bottom_rxBufferLoopDetect - cleared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 Rx_Bottom_ReadRxData(void) 
    {
        uint8 rxData;

    #if (Rx_Bottom_RX_INTERRUPT_ENABLED)

        uint8 locRxBufferRead;
        uint8 locRxBufferWrite;

        /* Protect variables that could change on interrupt */
        Rx_Bottom_DisableRxInt();

        locRxBufferRead  = Rx_Bottom_rxBufferRead;
        locRxBufferWrite = Rx_Bottom_rxBufferWrite;

        if( (Rx_Bottom_rxBufferLoopDetect != 0u) || (locRxBufferRead != locRxBufferWrite) )
        {
            rxData = Rx_Bottom_rxBuffer[locRxBufferRead];
            locRxBufferRead++;

            if(locRxBufferRead >= Rx_Bottom_RX_BUFFER_SIZE)
            {
                locRxBufferRead = 0u;
            }
            /* Update the real pointer */
            Rx_Bottom_rxBufferRead = locRxBufferRead;

            if(Rx_Bottom_rxBufferLoopDetect != 0u)
            {
                Rx_Bottom_rxBufferLoopDetect = 0u;
                #if ((Rx_Bottom_RX_INTERRUPT_ENABLED) && (Rx_Bottom_FLOW_CONTROL != 0u))
                    /* When Hardware Flow Control selected - return RX mask */
                    #if( Rx_Bottom_HD_ENABLED )
                        if((Rx_Bottom_CONTROL_REG & Rx_Bottom_CTRL_HD_SEND) == 0u)
                        {   /* In Half duplex mode return RX mask only in RX
                            *  configuration set, otherwise
                            *  mask will be returned in LoadRxConfig() API.
                            */
                            Rx_Bottom_RXSTATUS_MASK_REG  |= Rx_Bottom_RX_STS_FIFO_NOTEMPTY;
                        }
                    #else
                        Rx_Bottom_RXSTATUS_MASK_REG  |= Rx_Bottom_RX_STS_FIFO_NOTEMPTY;
                    #endif /* end Rx_Bottom_HD_ENABLED */
                #endif /* ((Rx_Bottom_RX_INTERRUPT_ENABLED) && (Rx_Bottom_FLOW_CONTROL != 0u)) */
            }
        }
        else
        {   /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit */
            rxData = Rx_Bottom_RXDATA_REG;
        }

        Rx_Bottom_EnableRxInt();

    #else

        /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit */
        rxData = Rx_Bottom_RXDATA_REG;

    #endif /* (Rx_Bottom_RX_INTERRUPT_ENABLED) */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: Rx_Bottom_ReadRxStatus
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
    *  Rx_Bottom_RX_STS_FIFO_NOTEMPTY.
    *  Rx_Bottom_RX_STS_FIFO_NOTEMPTY clears immediately after RX data
    *  register read.
    *
    * Global Variables:
    *  Rx_Bottom_rxBufferOverflow - used to indicate overload condition.
    *   It set to one in RX interrupt when there isn't free space in
    *   Rx_Bottom_rxBufferRead to write new data. This condition returned
    *   and cleared to zero by this API as an
    *   Rx_Bottom_RX_STS_SOFT_BUFF_OVER bit along with RX Status register
    *   bits.
    *
    *******************************************************************************/
    uint8 Rx_Bottom_ReadRxStatus(void) 
    {
        uint8 status;

        status = Rx_Bottom_RXSTATUS_REG & Rx_Bottom_RX_HW_MASK;

    #if (Rx_Bottom_RX_INTERRUPT_ENABLED)
        if(Rx_Bottom_rxBufferOverflow != 0u)
        {
            status |= Rx_Bottom_RX_STS_SOFT_BUFF_OVER;
            Rx_Bottom_rxBufferOverflow = 0u;
        }
    #endif /* (Rx_Bottom_RX_INTERRUPT_ENABLED) */

        return(status);
    }


    /*******************************************************************************
    * Function Name: Rx_Bottom_GetChar
    ********************************************************************************
    *
    * Summary:
    *  Returns the last received byte of data. Rx_Bottom_GetChar() is
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
    *  Rx_Bottom_rxBuffer - RAM buffer pointer for save received data.
    *  Rx_Bottom_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  Rx_Bottom_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  Rx_Bottom_rxBufferLoopDetect - cleared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 Rx_Bottom_GetChar(void) 
    {
        uint8 rxData = 0u;
        uint8 rxStatus;

    #if (Rx_Bottom_RX_INTERRUPT_ENABLED)
        uint8 locRxBufferRead;
        uint8 locRxBufferWrite;

        /* Protect variables that could change on interrupt */
        Rx_Bottom_DisableRxInt();

        locRxBufferRead  = Rx_Bottom_rxBufferRead;
        locRxBufferWrite = Rx_Bottom_rxBufferWrite;

        if( (Rx_Bottom_rxBufferLoopDetect != 0u) || (locRxBufferRead != locRxBufferWrite) )
        {
            rxData = Rx_Bottom_rxBuffer[locRxBufferRead];
            locRxBufferRead++;
            if(locRxBufferRead >= Rx_Bottom_RX_BUFFER_SIZE)
            {
                locRxBufferRead = 0u;
            }
            /* Update the real pointer */
            Rx_Bottom_rxBufferRead = locRxBufferRead;

            if(Rx_Bottom_rxBufferLoopDetect != 0u)
            {
                Rx_Bottom_rxBufferLoopDetect = 0u;
                #if( (Rx_Bottom_RX_INTERRUPT_ENABLED) && (Rx_Bottom_FLOW_CONTROL != 0u) )
                    /* When Hardware Flow Control selected - return RX mask */
                    #if( Rx_Bottom_HD_ENABLED )
                        if((Rx_Bottom_CONTROL_REG & Rx_Bottom_CTRL_HD_SEND) == 0u)
                        {   /* In Half duplex mode return RX mask only if
                            *  RX configuration set, otherwise
                            *  mask will be returned in LoadRxConfig() API.
                            */
                            Rx_Bottom_RXSTATUS_MASK_REG |= Rx_Bottom_RX_STS_FIFO_NOTEMPTY;
                        }
                    #else
                        Rx_Bottom_RXSTATUS_MASK_REG |= Rx_Bottom_RX_STS_FIFO_NOTEMPTY;
                    #endif /* end Rx_Bottom_HD_ENABLED */
                #endif /* Rx_Bottom_RX_INTERRUPT_ENABLED and Hardware flow control*/
            }

        }
        else
        {   rxStatus = Rx_Bottom_RXSTATUS_REG;
            if((rxStatus & Rx_Bottom_RX_STS_FIFO_NOTEMPTY) != 0u)
            {   /* Read received data from FIFO */
                rxData = Rx_Bottom_RXDATA_REG;
                /*Check status on error*/
                if((rxStatus & (Rx_Bottom_RX_STS_BREAK | Rx_Bottom_RX_STS_PAR_ERROR |
                                Rx_Bottom_RX_STS_STOP_ERROR | Rx_Bottom_RX_STS_OVERRUN)) != 0u)
                {
                    rxData = 0u;
                }
            }
        }

        Rx_Bottom_EnableRxInt();

    #else

        rxStatus =Rx_Bottom_RXSTATUS_REG;
        if((rxStatus & Rx_Bottom_RX_STS_FIFO_NOTEMPTY) != 0u)
        {
            /* Read received data from FIFO */
            rxData = Rx_Bottom_RXDATA_REG;

            /*Check status on error*/
            if((rxStatus & (Rx_Bottom_RX_STS_BREAK | Rx_Bottom_RX_STS_PAR_ERROR |
                            Rx_Bottom_RX_STS_STOP_ERROR | Rx_Bottom_RX_STS_OVERRUN)) != 0u)
            {
                rxData = 0u;
            }
        }
    #endif /* (Rx_Bottom_RX_INTERRUPT_ENABLED) */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: Rx_Bottom_GetByte
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
    uint16 Rx_Bottom_GetByte(void) 
    {
        
    #if (Rx_Bottom_RX_INTERRUPT_ENABLED)
        uint16 locErrorStatus;
        /* Protect variables that could change on interrupt */
        Rx_Bottom_DisableRxInt();
        locErrorStatus = (uint16)Rx_Bottom_errorStatus;
        Rx_Bottom_errorStatus = 0u;
        Rx_Bottom_EnableRxInt();
        return ( (uint16)(locErrorStatus << 8u) | Rx_Bottom_ReadRxData() );
    #else
        return ( ((uint16)Rx_Bottom_ReadRxStatus() << 8u) | Rx_Bottom_ReadRxData() );
    #endif /* Rx_Bottom_RX_INTERRUPT_ENABLED */
        
    }


    /*******************************************************************************
    * Function Name: Rx_Bottom_GetRxBufferSize
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
    *  Rx_Bottom_rxBufferWrite - used to calculate left bytes.
    *  Rx_Bottom_rxBufferRead - used to calculate left bytes.
    *  Rx_Bottom_rxBufferLoopDetect - checked to decide left bytes amount.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the RX Buffer is.
    *
    *******************************************************************************/
    uint8 Rx_Bottom_GetRxBufferSize(void)
                                                            
    {
        uint8 size;

    #if (Rx_Bottom_RX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt */
        Rx_Bottom_DisableRxInt();

        if(Rx_Bottom_rxBufferRead == Rx_Bottom_rxBufferWrite)
        {
            if(Rx_Bottom_rxBufferLoopDetect != 0u)
            {
                size = Rx_Bottom_RX_BUFFER_SIZE;
            }
            else
            {
                size = 0u;
            }
        }
        else if(Rx_Bottom_rxBufferRead < Rx_Bottom_rxBufferWrite)
        {
            size = (Rx_Bottom_rxBufferWrite - Rx_Bottom_rxBufferRead);
        }
        else
        {
            size = (Rx_Bottom_RX_BUFFER_SIZE - Rx_Bottom_rxBufferRead) + Rx_Bottom_rxBufferWrite;
        }

        Rx_Bottom_EnableRxInt();

    #else

        /* We can only know if there is data in the fifo. */
        size = ((Rx_Bottom_RXSTATUS_REG & Rx_Bottom_RX_STS_FIFO_NOTEMPTY) != 0u) ? 1u : 0u;

    #endif /* (Rx_Bottom_RX_INTERRUPT_ENABLED) */

        return(size);
    }


    /*******************************************************************************
    * Function Name: Rx_Bottom_ClearRxBuffer
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
    *  Rx_Bottom_rxBufferWrite - cleared to zero.
    *  Rx_Bottom_rxBufferRead - cleared to zero.
    *  Rx_Bottom_rxBufferLoopDetect - cleared to zero.
    *  Rx_Bottom_rxBufferOverflow - cleared to zero.
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
    void Rx_Bottom_ClearRxBuffer(void) 
    {
        uint8 enableInterrupts;

        /* Clear the HW FIFO */
        enableInterrupts = CyEnterCriticalSection();
        Rx_Bottom_RXDATA_AUX_CTL_REG |= (uint8)  Rx_Bottom_RX_FIFO_CLR;
        Rx_Bottom_RXDATA_AUX_CTL_REG &= (uint8) ~Rx_Bottom_RX_FIFO_CLR;
        CyExitCriticalSection(enableInterrupts);

    #if (Rx_Bottom_RX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        Rx_Bottom_DisableRxInt();

        Rx_Bottom_rxBufferRead = 0u;
        Rx_Bottom_rxBufferWrite = 0u;
        Rx_Bottom_rxBufferLoopDetect = 0u;
        Rx_Bottom_rxBufferOverflow = 0u;

        Rx_Bottom_EnableRxInt();

    #endif /* (Rx_Bottom_RX_INTERRUPT_ENABLED) */

    }


    /*******************************************************************************
    * Function Name: Rx_Bottom_SetRxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Sets the software controlled Addressing mode used by the RX portion of the
    *  UART.
    *
    * Parameters:
    *  addressMode: Enumerated value indicating the mode of RX addressing
    *  Rx_Bottom__B_UART__AM_SW_BYTE_BYTE -  Software Byte-by-Byte address
    *                                               detection
    *  Rx_Bottom__B_UART__AM_SW_DETECT_TO_BUFFER - Software Detect to Buffer
    *                                               address detection
    *  Rx_Bottom__B_UART__AM_HW_BYTE_BY_BYTE - Hardware Byte-by-Byte address
    *                                               detection
    *  Rx_Bottom__B_UART__AM_HW_DETECT_TO_BUFFER - Hardware Detect to Buffer
    *                                               address detection
    *  Rx_Bottom__B_UART__AM_NONE - No address detection
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  Rx_Bottom_rxAddressMode - the parameter stored in this variable for
    *   the farther usage in RX ISR.
    *  Rx_Bottom_rxAddressDetected - set to initial state (0).
    *
    *******************************************************************************/
    void Rx_Bottom_SetRxAddressMode(uint8 addressMode)
                                                        
    {
        #if(Rx_Bottom_RXHW_ADDRESS_ENABLED)
            #if(Rx_Bottom_CONTROL_REG_REMOVED)
                if(0u != addressMode)
                {
                    /* Suppress compiler warning */
                }
            #else /* Rx_Bottom_CONTROL_REG_REMOVED */
                uint8 tmpCtrl;
                tmpCtrl = Rx_Bottom_CONTROL_REG & (uint8)~Rx_Bottom_CTRL_RXADDR_MODE_MASK;
                tmpCtrl |= (uint8)(addressMode << Rx_Bottom_CTRL_RXADDR_MODE0_SHIFT);
                Rx_Bottom_CONTROL_REG = tmpCtrl;

                #if(Rx_Bottom_RX_INTERRUPT_ENABLED && \
                   (Rx_Bottom_RXBUFFERSIZE > Rx_Bottom_FIFO_LENGTH) )
                    Rx_Bottom_rxAddressMode = addressMode;
                    Rx_Bottom_rxAddressDetected = 0u;
                #endif /* End Rx_Bottom_RXBUFFERSIZE > Rx_Bottom_FIFO_LENGTH*/
            #endif /* End Rx_Bottom_CONTROL_REG_REMOVED */
        #else /* Rx_Bottom_RXHW_ADDRESS_ENABLED */
            if(0u != addressMode)
            {
                /* Suppress compiler warning */
            }
        #endif /* End Rx_Bottom_RXHW_ADDRESS_ENABLED */
    }


    /*******************************************************************************
    * Function Name: Rx_Bottom_SetRxAddress1
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
    void Rx_Bottom_SetRxAddress1(uint8 address) 
    {
        Rx_Bottom_RXADDRESS1_REG = address;
    }


    /*******************************************************************************
    * Function Name: Rx_Bottom_SetRxAddress2
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
    void Rx_Bottom_SetRxAddress2(uint8 address) 
    {
        Rx_Bottom_RXADDRESS2_REG = address;
    }

#endif  /* Rx_Bottom_RX_ENABLED || Rx_Bottom_HD_ENABLED*/


#if( (Rx_Bottom_TX_ENABLED) || (Rx_Bottom_HD_ENABLED) )
    /*******************************************************************************
    * Function Name: Rx_Bottom_SetTxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the TX interrupt sources to be enabled, but does not enable the
    *  interrupt.
    *
    * Parameters:
    *  intSrc: Bit field containing the TX interrupt sources to enable
    *   Rx_Bottom_TX_STS_COMPLETE        Interrupt on TX byte complete
    *   Rx_Bottom_TX_STS_FIFO_EMPTY      Interrupt when TX FIFO is empty
    *   Rx_Bottom_TX_STS_FIFO_FULL       Interrupt when TX FIFO is full
    *   Rx_Bottom_TX_STS_FIFO_NOT_FULL   Interrupt when TX FIFO is not full
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void Rx_Bottom_SetTxInterruptMode(uint8 intSrc) 
    {
        Rx_Bottom_TXSTATUS_MASK_REG = intSrc;
    }


    /*******************************************************************************
    * Function Name: Rx_Bottom_WriteTxData
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
    *  Rx_Bottom_txBuffer - RAM buffer pointer for save data for transmission
    *  Rx_Bottom_txBufferWrite - cyclic index for write to txBuffer,
    *    incremented after each byte saved to buffer.
    *  Rx_Bottom_txBufferRead - cyclic index for read from txBuffer,
    *    checked to identify the condition to write to FIFO directly or to TX buffer
    *  Rx_Bottom_initVar - checked to identify that the component has been
    *    initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void Rx_Bottom_WriteTxData(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function*/
        if(Rx_Bottom_initVar != 0u)
        {
        #if (Rx_Bottom_TX_INTERRUPT_ENABLED)

            /* Protect variables that could change on interrupt. */
            Rx_Bottom_DisableTxInt();

            if( (Rx_Bottom_txBufferRead == Rx_Bottom_txBufferWrite) &&
                ((Rx_Bottom_TXSTATUS_REG & Rx_Bottom_TX_STS_FIFO_FULL) == 0u) )
            {
                /* Add directly to the FIFO. */
                Rx_Bottom_TXDATA_REG = txDataByte;
            }
            else
            {
                if(Rx_Bottom_txBufferWrite >= Rx_Bottom_TX_BUFFER_SIZE)
                {
                    Rx_Bottom_txBufferWrite = 0u;
                }

                Rx_Bottom_txBuffer[Rx_Bottom_txBufferWrite] = txDataByte;

                /* Add to the software buffer. */
                Rx_Bottom_txBufferWrite++;
            }

            Rx_Bottom_EnableTxInt();

        #else

            /* Add directly to the FIFO. */
            Rx_Bottom_TXDATA_REG = txDataByte;

        #endif /*(Rx_Bottom_TX_INTERRUPT_ENABLED) */
        }
    }


    /*******************************************************************************
    * Function Name: Rx_Bottom_ReadTxStatus
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
    uint8 Rx_Bottom_ReadTxStatus(void) 
    {
        return(Rx_Bottom_TXSTATUS_REG);
    }


    /*******************************************************************************
    * Function Name: Rx_Bottom_PutChar
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
    *  Rx_Bottom_txBuffer - RAM buffer pointer for save data for transmission
    *  Rx_Bottom_txBufferWrite - cyclic index for write to txBuffer,
    *     checked to identify free space in txBuffer and incremented after each byte
    *     saved to buffer.
    *  Rx_Bottom_txBufferRead - cyclic index for read from txBuffer,
    *     checked to identify free space in txBuffer.
    *  Rx_Bottom_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to transmit any byte of data in a single transfer
    *
    *******************************************************************************/
    void Rx_Bottom_PutChar(uint8 txDataByte) 
    {
    #if (Rx_Bottom_TX_INTERRUPT_ENABLED)
        /* The temporary output pointer is used since it takes two instructions
        *  to increment with a wrap, and we can't risk doing that with the real
        *  pointer and getting an interrupt in between instructions.
        */
        uint8 locTxBufferWrite;
        uint8 locTxBufferRead;

        do
        { /* Block if software buffer is full, so we don't overwrite. */

        #if ((Rx_Bottom_TX_BUFFER_SIZE > Rx_Bottom_MAX_BYTE_VALUE) && (CY_PSOC3))
            /* Disable TX interrupt to protect variables from modification */
            Rx_Bottom_DisableTxInt();
        #endif /* (Rx_Bottom_TX_BUFFER_SIZE > 255) */

            locTxBufferWrite = Rx_Bottom_txBufferWrite;
            locTxBufferRead  = Rx_Bottom_txBufferRead;

        #if ((Rx_Bottom_TX_BUFFER_SIZE > Rx_Bottom_MAX_BYTE_VALUE) && (CY_PSOC3))
            /* Enable interrupt to continue transmission */
            Rx_Bottom_EnableTxInt();
        #endif /* (Rx_Bottom_TX_BUFFER_SIZE > 255) */
        }
        while( (locTxBufferWrite < locTxBufferRead) ? (locTxBufferWrite == (locTxBufferRead - 1u)) :
                                ((locTxBufferWrite - locTxBufferRead) ==
                                (uint8)(Rx_Bottom_TX_BUFFER_SIZE - 1u)) );

        if( (locTxBufferRead == locTxBufferWrite) &&
            ((Rx_Bottom_TXSTATUS_REG & Rx_Bottom_TX_STS_FIFO_FULL) == 0u) )
        {
            /* Add directly to the FIFO */
            Rx_Bottom_TXDATA_REG = txDataByte;
        }
        else
        {
            if(locTxBufferWrite >= Rx_Bottom_TX_BUFFER_SIZE)
            {
                locTxBufferWrite = 0u;
            }
            /* Add to the software buffer. */
            Rx_Bottom_txBuffer[locTxBufferWrite] = txDataByte;
            locTxBufferWrite++;

            /* Finally, update the real output pointer */
        #if ((Rx_Bottom_TX_BUFFER_SIZE > Rx_Bottom_MAX_BYTE_VALUE) && (CY_PSOC3))
            Rx_Bottom_DisableTxInt();
        #endif /* (Rx_Bottom_TX_BUFFER_SIZE > 255) */

            Rx_Bottom_txBufferWrite = locTxBufferWrite;

        #if ((Rx_Bottom_TX_BUFFER_SIZE > Rx_Bottom_MAX_BYTE_VALUE) && (CY_PSOC3))
            Rx_Bottom_EnableTxInt();
        #endif /* (Rx_Bottom_TX_BUFFER_SIZE > 255) */

            if(0u != (Rx_Bottom_TXSTATUS_REG & Rx_Bottom_TX_STS_FIFO_EMPTY))
            {
                /* Trigger TX interrupt to send software buffer */
                Rx_Bottom_SetPendingTxInt();
            }
        }

    #else

        while((Rx_Bottom_TXSTATUS_REG & Rx_Bottom_TX_STS_FIFO_FULL) != 0u)
        {
            /* Wait for room in the FIFO */
        }

        /* Add directly to the FIFO */
        Rx_Bottom_TXDATA_REG = txDataByte;

    #endif /* End (Rx_Bottom_TX_INTERRUPT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: Rx_Bottom_PutString
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
    *  Rx_Bottom_initVar - checked to identify that the component has been
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
    void Rx_Bottom_PutString(const char8 string[]) 
    {
        uint16 bufIndex = 0u;

        /* If not Initialized then skip this function */
        if(Rx_Bottom_initVar != 0u)
        {
            /* This is a blocking function, it will not exit until all data is sent */
            while(string[bufIndex] != (char8) 0)
            {
                Rx_Bottom_PutChar((uint8)string[bufIndex]);
                bufIndex++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: Rx_Bottom_PutArray
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
    *  Rx_Bottom_initVar - checked to identify that the component has been
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
    void Rx_Bottom_PutArray(const uint8 string[], uint8 byteCount)
                                                                    
    {
        uint8 bufIndex = 0u;

        /* If not Initialized then skip this function */
        if(Rx_Bottom_initVar != 0u)
        {
            while(bufIndex < byteCount)
            {
                Rx_Bottom_PutChar(string[bufIndex]);
                bufIndex++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: Rx_Bottom_PutCRLF
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
    *  Rx_Bottom_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void Rx_Bottom_PutCRLF(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function */
        if(Rx_Bottom_initVar != 0u)
        {
            Rx_Bottom_PutChar(txDataByte);
            Rx_Bottom_PutChar(0x0Du);
            Rx_Bottom_PutChar(0x0Au);
        }
    }


    /*******************************************************************************
    * Function Name: Rx_Bottom_GetTxBufferSize
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
    *  Rx_Bottom_txBufferWrite - used to calculate left space.
    *  Rx_Bottom_txBufferRead - used to calculate left space.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the TX Buffer is.
    *
    *******************************************************************************/
    uint8 Rx_Bottom_GetTxBufferSize(void)
                                                            
    {
        uint8 size;

    #if (Rx_Bottom_TX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        Rx_Bottom_DisableTxInt();

        if(Rx_Bottom_txBufferRead == Rx_Bottom_txBufferWrite)
        {
            size = 0u;
        }
        else if(Rx_Bottom_txBufferRead < Rx_Bottom_txBufferWrite)
        {
            size = (Rx_Bottom_txBufferWrite - Rx_Bottom_txBufferRead);
        }
        else
        {
            size = (Rx_Bottom_TX_BUFFER_SIZE - Rx_Bottom_txBufferRead) +
                    Rx_Bottom_txBufferWrite;
        }

        Rx_Bottom_EnableTxInt();

    #else

        size = Rx_Bottom_TXSTATUS_REG;

        /* Is the fifo is full. */
        if((size & Rx_Bottom_TX_STS_FIFO_FULL) != 0u)
        {
            size = Rx_Bottom_FIFO_LENGTH;
        }
        else if((size & Rx_Bottom_TX_STS_FIFO_EMPTY) != 0u)
        {
            size = 0u;
        }
        else
        {
            /* We only know there is data in the fifo. */
            size = 1u;
        }

    #endif /* (Rx_Bottom_TX_INTERRUPT_ENABLED) */

    return(size);
    }


    /*******************************************************************************
    * Function Name: Rx_Bottom_ClearTxBuffer
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
    *  Rx_Bottom_txBufferWrite - cleared to zero.
    *  Rx_Bottom_txBufferRead - cleared to zero.
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
    void Rx_Bottom_ClearTxBuffer(void) 
    {
        uint8 enableInterrupts;

        enableInterrupts = CyEnterCriticalSection();
        /* Clear the HW FIFO */
        Rx_Bottom_TXDATA_AUX_CTL_REG |= (uint8)  Rx_Bottom_TX_FIFO_CLR;
        Rx_Bottom_TXDATA_AUX_CTL_REG &= (uint8) ~Rx_Bottom_TX_FIFO_CLR;
        CyExitCriticalSection(enableInterrupts);

    #if (Rx_Bottom_TX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        Rx_Bottom_DisableTxInt();

        Rx_Bottom_txBufferRead = 0u;
        Rx_Bottom_txBufferWrite = 0u;

        /* Enable Tx interrupt. */
        Rx_Bottom_EnableTxInt();

    #endif /* (Rx_Bottom_TX_INTERRUPT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: Rx_Bottom_SendBreak
    ********************************************************************************
    *
    * Summary:
    *  Transmits a break signal on the bus.
    *
    * Parameters:
    *  uint8 retMode:  Send Break return mode. See the following table for options.
    *   Rx_Bottom_SEND_BREAK - Initialize registers for break, send the Break
    *       signal and return immediately.
    *   Rx_Bottom_WAIT_FOR_COMPLETE_REINIT - Wait until break transmission is
    *       complete, reinitialize registers to normal transmission mode then return
    *   Rx_Bottom_REINIT - Reinitialize registers to normal transmission mode
    *       then return.
    *   Rx_Bottom_SEND_WAIT_REINIT - Performs both options: 
    *      Rx_Bottom_SEND_BREAK and Rx_Bottom_WAIT_FOR_COMPLETE_REINIT.
    *      This option is recommended for most cases.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  Rx_Bottom_initVar - checked to identify that the component has been
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
    *     When interrupt appear with Rx_Bottom_TX_STS_COMPLETE status:
    *     SendBreak(2);     - complete Break operation
    *
    * Side Effects:
    *  The Rx_Bottom_SendBreak() function initializes registers to send a
    *  break signal.
    *  Break signal length depends on the break signal bits configuration.
    *  The register configuration should be reinitialized before normal 8-bit
    *  communication can continue.
    *
    *******************************************************************************/
    void Rx_Bottom_SendBreak(uint8 retMode) 
    {

        /* If not Initialized then skip this function*/
        if(Rx_Bottom_initVar != 0u)
        {
            /* Set the Counter to 13-bits and transmit a 00 byte */
            /* When that is done then reset the counter value back */
            uint8 tmpStat;

        #if(Rx_Bottom_HD_ENABLED) /* Half Duplex mode*/

            if( (retMode == Rx_Bottom_SEND_BREAK) ||
                (retMode == Rx_Bottom_SEND_WAIT_REINIT ) )
            {
                /* CTRL_HD_SEND_BREAK - sends break bits in HD mode */
                Rx_Bottom_WriteControlRegister(Rx_Bottom_ReadControlRegister() |
                                                      Rx_Bottom_CTRL_HD_SEND_BREAK);
                /* Send zeros */
                Rx_Bottom_TXDATA_REG = 0u;

                do /* Wait until transmit starts */
                {
                    tmpStat = Rx_Bottom_TXSTATUS_REG;
                }
                while((tmpStat & Rx_Bottom_TX_STS_FIFO_EMPTY) != 0u);
            }

            if( (retMode == Rx_Bottom_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == Rx_Bottom_SEND_WAIT_REINIT) )
            {
                do /* Wait until transmit complete */
                {
                    tmpStat = Rx_Bottom_TXSTATUS_REG;
                }
                while(((uint8)~tmpStat & Rx_Bottom_TX_STS_COMPLETE) != 0u);
            }

            if( (retMode == Rx_Bottom_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == Rx_Bottom_REINIT) ||
                (retMode == Rx_Bottom_SEND_WAIT_REINIT) )
            {
                Rx_Bottom_WriteControlRegister(Rx_Bottom_ReadControlRegister() &
                                              (uint8)~Rx_Bottom_CTRL_HD_SEND_BREAK);
            }

        #else /* Rx_Bottom_HD_ENABLED Full Duplex mode */

            static uint8 txPeriod;

            if( (retMode == Rx_Bottom_SEND_BREAK) ||
                (retMode == Rx_Bottom_SEND_WAIT_REINIT) )
            {
                /* CTRL_HD_SEND_BREAK - skip to send parity bit at Break signal in Full Duplex mode */
                #if( (Rx_Bottom_PARITY_TYPE != Rx_Bottom__B_UART__NONE_REVB) || \
                                    (Rx_Bottom_PARITY_TYPE_SW != 0u) )
                    Rx_Bottom_WriteControlRegister(Rx_Bottom_ReadControlRegister() |
                                                          Rx_Bottom_CTRL_HD_SEND_BREAK);
                #endif /* End Rx_Bottom_PARITY_TYPE != Rx_Bottom__B_UART__NONE_REVB  */

                #if(Rx_Bottom_TXCLKGEN_DP)
                    txPeriod = Rx_Bottom_TXBITCLKTX_COMPLETE_REG;
                    Rx_Bottom_TXBITCLKTX_COMPLETE_REG = Rx_Bottom_TXBITCTR_BREAKBITS;
                #else
                    txPeriod = Rx_Bottom_TXBITCTR_PERIOD_REG;
                    Rx_Bottom_TXBITCTR_PERIOD_REG = Rx_Bottom_TXBITCTR_BREAKBITS8X;
                #endif /* End Rx_Bottom_TXCLKGEN_DP */

                /* Send zeros */
                Rx_Bottom_TXDATA_REG = 0u;

                do /* Wait until transmit starts */
                {
                    tmpStat = Rx_Bottom_TXSTATUS_REG;
                }
                while((tmpStat & Rx_Bottom_TX_STS_FIFO_EMPTY) != 0u);
            }

            if( (retMode == Rx_Bottom_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == Rx_Bottom_SEND_WAIT_REINIT) )
            {
                do /* Wait until transmit complete */
                {
                    tmpStat = Rx_Bottom_TXSTATUS_REG;
                }
                while(((uint8)~tmpStat & Rx_Bottom_TX_STS_COMPLETE) != 0u);
            }

            if( (retMode == Rx_Bottom_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == Rx_Bottom_REINIT) ||
                (retMode == Rx_Bottom_SEND_WAIT_REINIT) )
            {

            #if(Rx_Bottom_TXCLKGEN_DP)
                Rx_Bottom_TXBITCLKTX_COMPLETE_REG = txPeriod;
            #else
                Rx_Bottom_TXBITCTR_PERIOD_REG = txPeriod;
            #endif /* End Rx_Bottom_TXCLKGEN_DP */

            #if( (Rx_Bottom_PARITY_TYPE != Rx_Bottom__B_UART__NONE_REVB) || \
                 (Rx_Bottom_PARITY_TYPE_SW != 0u) )
                Rx_Bottom_WriteControlRegister(Rx_Bottom_ReadControlRegister() &
                                                      (uint8) ~Rx_Bottom_CTRL_HD_SEND_BREAK);
            #endif /* End Rx_Bottom_PARITY_TYPE != NONE */
            }
        #endif    /* End Rx_Bottom_HD_ENABLED */
        }
    }


    /*******************************************************************************
    * Function Name: Rx_Bottom_SetTxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the transmitter to signal the next bytes is address or data.
    *
    * Parameters:
    *  addressMode: 
    *       Rx_Bottom_SET_SPACE - Configure the transmitter to send the next
    *                                    byte as a data.
    *       Rx_Bottom_SET_MARK  - Configure the transmitter to send the next
    *                                    byte as an address.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  This function sets and clears Rx_Bottom_CTRL_MARK bit in the Control
    *  register.
    *
    *******************************************************************************/
    void Rx_Bottom_SetTxAddressMode(uint8 addressMode) 
    {
        /* Mark/Space sending enable */
        if(addressMode != 0u)
        {
        #if( Rx_Bottom_CONTROL_REG_REMOVED == 0u )
            Rx_Bottom_WriteControlRegister(Rx_Bottom_ReadControlRegister() |
                                                  Rx_Bottom_CTRL_MARK);
        #endif /* End Rx_Bottom_CONTROL_REG_REMOVED == 0u */
        }
        else
        {
        #if( Rx_Bottom_CONTROL_REG_REMOVED == 0u )
            Rx_Bottom_WriteControlRegister(Rx_Bottom_ReadControlRegister() &
                                                  (uint8) ~Rx_Bottom_CTRL_MARK);
        #endif /* End Rx_Bottom_CONTROL_REG_REMOVED == 0u */
        }
    }

#endif  /* EndRx_Bottom_TX_ENABLED */

#if(Rx_Bottom_HD_ENABLED)


    /*******************************************************************************
    * Function Name: Rx_Bottom_LoadRxConfig
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
    void Rx_Bottom_LoadRxConfig(void) 
    {
        Rx_Bottom_WriteControlRegister(Rx_Bottom_ReadControlRegister() &
                                                (uint8)~Rx_Bottom_CTRL_HD_SEND);
        Rx_Bottom_RXBITCTR_PERIOD_REG = Rx_Bottom_HD_RXBITCTR_INIT;

    #if (Rx_Bottom_RX_INTERRUPT_ENABLED)
        /* Enable RX interrupt after set RX configuration */
        Rx_Bottom_SetRxInterruptMode(Rx_Bottom_INIT_RX_INTERRUPTS_MASK);
    #endif /* (Rx_Bottom_RX_INTERRUPT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: Rx_Bottom_LoadTxConfig
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
    void Rx_Bottom_LoadTxConfig(void) 
    {
    #if (Rx_Bottom_RX_INTERRUPT_ENABLED)
        /* Disable RX interrupts before set TX configuration */
        Rx_Bottom_SetRxInterruptMode(0u);
    #endif /* (Rx_Bottom_RX_INTERRUPT_ENABLED) */

        Rx_Bottom_WriteControlRegister(Rx_Bottom_ReadControlRegister() | Rx_Bottom_CTRL_HD_SEND);
        Rx_Bottom_RXBITCTR_PERIOD_REG = Rx_Bottom_HD_TXBITCTR_INIT;
    }

#endif  /* Rx_Bottom_HD_ENABLED */


/* [] END OF FILE */
