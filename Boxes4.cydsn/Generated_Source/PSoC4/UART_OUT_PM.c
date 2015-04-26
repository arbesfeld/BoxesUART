/*******************************************************************************
* File Name: UART_OUT_PM.c
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

#include "UART_OUT.h"


/***************************************
* Local data allocation
***************************************/

static UART_OUT_BACKUP_STRUCT  UART_OUT_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: UART_OUT_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component configuration and nonretention registers.
*  It also saves the current component parameter values, as defined in the
*  Configure dialog or as modified by appropriate APIs. This function is called
*  by the UART_OUT_Sleep() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  UART_OUT_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
* Side Effects:
*  All nonretention registers except FIFO are saved to RAM
*
*******************************************************************************/
void UART_OUT_SaveConfig(void)
{
    #if(UART_OUT_CONTROL_REG_REMOVED == 0u)
        UART_OUT_backup.cr = UART_OUT_CONTROL_REG;
    #endif /* End UART_OUT_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: UART_OUT_RestoreConfig
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
*  UART_OUT_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
* Side Effects:
*  All nonretention registers except FIFO loaded from RAM. This function should
*  be called only after UART_OUT_SaveConfig() is called, otherwise
*  incorrect data will be loaded into the registers.
*
*******************************************************************************/
void UART_OUT_RestoreConfig(void)
{
    #if(UART_OUT_CONTROL_REG_REMOVED == 0u)
        UART_OUT_CONTROL_REG = UART_OUT_backup.cr;
    #endif /* End UART_OUT_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: UART_OUT_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. 
*  The UART_OUT_Sleep() API saves the current component state. Then it
*  calls the UART_OUT_Stop() function and calls 
*  UART_OUT_SaveConfig() to save the hardware configuration.
*  Call the UART_OUT_Sleep() function before calling the CyPmSleep() 
*  or the CyPmHibernate() function. 
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  UART_OUT_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UART_OUT_Sleep(void)
{
    #if(UART_OUT_RX_ENABLED || UART_OUT_HD_ENABLED)
        if((UART_OUT_RXSTATUS_ACTL_REG  & UART_OUT_INT_ENABLE) != 0u)
        {
            UART_OUT_backup.enableState = 1u;
        }
        else
        {
            UART_OUT_backup.enableState = 0u;
        }
    #else
        if((UART_OUT_TXSTATUS_ACTL_REG  & UART_OUT_INT_ENABLE) !=0u)
        {
            UART_OUT_backup.enableState = 1u;
        }
        else
        {
            UART_OUT_backup.enableState = 0u;
        }
    #endif /* End UART_OUT_RX_ENABLED || UART_OUT_HD_ENABLED*/

    UART_OUT_Stop();
    UART_OUT_SaveConfig();
}


/*******************************************************************************
* Function Name: UART_OUT_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when 
*  UART_OUT_Sleep() was called. The UART_OUT_Wakeup() function
*  calls the UART_OUT_RestoreConfig() function to restore the 
*  configuration. If the component was enabled before the 
*  UART_OUT_Sleep() function was called, the UART_OUT_Wakeup()
*  function will also re-enable the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  UART_OUT_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UART_OUT_Wakeup(void)
{
    UART_OUT_RestoreConfig();
    #if( (UART_OUT_RX_ENABLED) || (UART_OUT_HD_ENABLED) )
        UART_OUT_ClearRxBuffer();
    #endif /* End (UART_OUT_RX_ENABLED) || (UART_OUT_HD_ENABLED) */
    #if(UART_OUT_TX_ENABLED || UART_OUT_HD_ENABLED)
        UART_OUT_ClearTxBuffer();
    #endif /* End UART_OUT_TX_ENABLED || UART_OUT_HD_ENABLED */

    if(UART_OUT_backup.enableState != 0u)
    {
        UART_OUT_Enable();
    }
}


/* [] END OF FILE */
