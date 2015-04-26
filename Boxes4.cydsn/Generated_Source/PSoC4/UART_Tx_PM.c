/*******************************************************************************
* File Name: UART_Tx_PM.c
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

#include "UART_Tx.h"


/***************************************
* Local data allocation
***************************************/

static UART_Tx_BACKUP_STRUCT  UART_Tx_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: UART_Tx_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component configuration and nonretention registers.
*  It also saves the current component parameter values, as defined in the
*  Configure dialog or as modified by appropriate APIs. This function is called
*  by the UART_Tx_Sleep() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  UART_Tx_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
* Side Effects:
*  All nonretention registers except FIFO are saved to RAM
*
*******************************************************************************/
void UART_Tx_SaveConfig(void)
{
    #if(UART_Tx_CONTROL_REG_REMOVED == 0u)
        UART_Tx_backup.cr = UART_Tx_CONTROL_REG;
    #endif /* End UART_Tx_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: UART_Tx_RestoreConfig
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
*  UART_Tx_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
* Side Effects:
*  All nonretention registers except FIFO loaded from RAM. This function should
*  be called only after UART_Tx_SaveConfig() is called, otherwise
*  incorrect data will be loaded into the registers.
*
*******************************************************************************/
void UART_Tx_RestoreConfig(void)
{
    #if(UART_Tx_CONTROL_REG_REMOVED == 0u)
        UART_Tx_CONTROL_REG = UART_Tx_backup.cr;
    #endif /* End UART_Tx_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: UART_Tx_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. 
*  The UART_Tx_Sleep() API saves the current component state. Then it
*  calls the UART_Tx_Stop() function and calls 
*  UART_Tx_SaveConfig() to save the hardware configuration.
*  Call the UART_Tx_Sleep() function before calling the CyPmSleep() 
*  or the CyPmHibernate() function. 
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  UART_Tx_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UART_Tx_Sleep(void)
{
    #if(UART_Tx_RX_ENABLED || UART_Tx_HD_ENABLED)
        if((UART_Tx_RXSTATUS_ACTL_REG  & UART_Tx_INT_ENABLE) != 0u)
        {
            UART_Tx_backup.enableState = 1u;
        }
        else
        {
            UART_Tx_backup.enableState = 0u;
        }
    #else
        if((UART_Tx_TXSTATUS_ACTL_REG  & UART_Tx_INT_ENABLE) !=0u)
        {
            UART_Tx_backup.enableState = 1u;
        }
        else
        {
            UART_Tx_backup.enableState = 0u;
        }
    #endif /* End UART_Tx_RX_ENABLED || UART_Tx_HD_ENABLED*/

    UART_Tx_Stop();
    UART_Tx_SaveConfig();
}


/*******************************************************************************
* Function Name: UART_Tx_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when 
*  UART_Tx_Sleep() was called. The UART_Tx_Wakeup() function
*  calls the UART_Tx_RestoreConfig() function to restore the 
*  configuration. If the component was enabled before the 
*  UART_Tx_Sleep() function was called, the UART_Tx_Wakeup()
*  function will also re-enable the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  UART_Tx_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UART_Tx_Wakeup(void)
{
    UART_Tx_RestoreConfig();
    #if( (UART_Tx_RX_ENABLED) || (UART_Tx_HD_ENABLED) )
        UART_Tx_ClearRxBuffer();
    #endif /* End (UART_Tx_RX_ENABLED) || (UART_Tx_HD_ENABLED) */
    #if(UART_Tx_TX_ENABLED || UART_Tx_HD_ENABLED)
        UART_Tx_ClearTxBuffer();
    #endif /* End UART_Tx_TX_ENABLED || UART_Tx_HD_ENABLED */

    if(UART_Tx_backup.enableState != 0u)
    {
        UART_Tx_Enable();
    }
}


/* [] END OF FILE */
