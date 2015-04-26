/*******************************************************************************
* File Name: UART_Rx_Front_PM.c
* Version 2.40
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "UART_Rx_Front.h"


/***************************************
* Local data allocation
***************************************/

static UART_Rx_Front_BACKUP_STRUCT  UART_Rx_Front_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: UART_Rx_Front_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component configuration and nonretention registers.
*  It also saves the current component parameter values, as defined in the
*  Configure dialog or as modified by appropriate APIs. This function is called
*  by the UART_Rx_Front_Sleep() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  UART_Rx_Front_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
* Side Effects:
*  All nonretention registers except FIFO are saved to RAM
*
*******************************************************************************/
void UART_Rx_Front_SaveConfig(void)
{
    #if(UART_Rx_Front_CONTROL_REG_REMOVED == 0u)
        UART_Rx_Front_backup.cr = UART_Rx_Front_CONTROL_REG;
    #endif /* End UART_Rx_Front_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: UART_Rx_Front_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the user configuration of nonretention registers.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  UART_Rx_Front_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
* Side Effects:
*  All nonretention registers except FIFO loaded from RAM. This function should
*  be called only after UART_Rx_Front_SaveConfig() is called, otherwise
*  incorrect data will be loaded into the registers.
*
*******************************************************************************/
void UART_Rx_Front_RestoreConfig(void)
{
    #if(UART_Rx_Front_CONTROL_REG_REMOVED == 0u)
        UART_Rx_Front_CONTROL_REG = UART_Rx_Front_backup.cr;
    #endif /* End UART_Rx_Front_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: UART_Rx_Front_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. 
*  The UART_Rx_Front_Sleep() API saves the current component state. Then it
*  calls the UART_Rx_Front_Stop() function and calls 
*  UART_Rx_Front_SaveConfig() to save the hardware configuration.
*  Call the UART_Rx_Front_Sleep() function before calling the CyPmSleep() 
*  or the CyPmHibernate() function. 
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  UART_Rx_Front_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UART_Rx_Front_Sleep(void)
{
    #if(UART_Rx_Front_RX_ENABLED || UART_Rx_Front_HD_ENABLED)
        if((UART_Rx_Front_RXSTATUS_ACTL_REG  & UART_Rx_Front_INT_ENABLE) != 0u)
        {
            UART_Rx_Front_backup.enableState = 1u;
        }
        else
        {
            UART_Rx_Front_backup.enableState = 0u;
        }
    #else
        if((UART_Rx_Front_TXSTATUS_ACTL_REG  & UART_Rx_Front_INT_ENABLE) !=0u)
        {
            UART_Rx_Front_backup.enableState = 1u;
        }
        else
        {
            UART_Rx_Front_backup.enableState = 0u;
        }
    #endif /* End UART_Rx_Front_RX_ENABLED || UART_Rx_Front_HD_ENABLED*/

    UART_Rx_Front_Stop();
    UART_Rx_Front_SaveConfig();
}


/*******************************************************************************
* Function Name: UART_Rx_Front_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when 
*  UART_Rx_Front_Sleep() was called. The UART_Rx_Front_Wakeup() function
*  calls the UART_Rx_Front_RestoreConfig() function to restore the 
*  configuration. If the component was enabled before the 
*  UART_Rx_Front_Sleep() function was called, the UART_Rx_Front_Wakeup()
*  function will also re-enable the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  UART_Rx_Front_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UART_Rx_Front_Wakeup(void)
{
    UART_Rx_Front_RestoreConfig();
    #if( (UART_Rx_Front_RX_ENABLED) || (UART_Rx_Front_HD_ENABLED) )
        UART_Rx_Front_ClearRxBuffer();
    #endif /* End (UART_Rx_Front_RX_ENABLED) || (UART_Rx_Front_HD_ENABLED) */
    #if(UART_Rx_Front_TX_ENABLED || UART_Rx_Front_HD_ENABLED)
        UART_Rx_Front_ClearTxBuffer();
    #endif /* End UART_Rx_Front_TX_ENABLED || UART_Rx_Front_HD_ENABLED */

    if(UART_Rx_Front_backup.enableState != 0u)
    {
        UART_Rx_Front_Enable();
    }
}


/* [] END OF FILE */
