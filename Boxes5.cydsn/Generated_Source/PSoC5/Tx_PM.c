/*******************************************************************************
* File Name: Tx_PM.c
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

#include "Tx.h"


/***************************************
* Local data allocation
***************************************/

static Tx_BACKUP_STRUCT  Tx_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: Tx_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component configuration and nonretention registers.
*  It also saves the current component parameter values, as defined in the
*  Configure dialog or as modified by appropriate APIs. This function is called
*  by the Tx_Sleep() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  Tx_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
* Side Effects:
*  All nonretention registers except FIFO are saved to RAM
*
*******************************************************************************/
void Tx_SaveConfig(void)
{
    #if(Tx_CONTROL_REG_REMOVED == 0u)
        Tx_backup.cr = Tx_CONTROL_REG;
    #endif /* End Tx_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: Tx_RestoreConfig
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
*  Tx_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
* Side Effects:
*  All nonretention registers except FIFO loaded from RAM. This function should
*  be called only after Tx_SaveConfig() is called, otherwise
*  incorrect data will be loaded into the registers.
*
*******************************************************************************/
void Tx_RestoreConfig(void)
{
    #if(Tx_CONTROL_REG_REMOVED == 0u)
        Tx_CONTROL_REG = Tx_backup.cr;
    #endif /* End Tx_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: Tx_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. 
*  The Tx_Sleep() API saves the current component state. Then it
*  calls the Tx_Stop() function and calls 
*  Tx_SaveConfig() to save the hardware configuration.
*  Call the Tx_Sleep() function before calling the CyPmSleep() 
*  or the CyPmHibernate() function. 
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  Tx_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Tx_Sleep(void)
{
    #if(Tx_RX_ENABLED || Tx_HD_ENABLED)
        if((Tx_RXSTATUS_ACTL_REG  & Tx_INT_ENABLE) != 0u)
        {
            Tx_backup.enableState = 1u;
        }
        else
        {
            Tx_backup.enableState = 0u;
        }
    #else
        if((Tx_TXSTATUS_ACTL_REG  & Tx_INT_ENABLE) !=0u)
        {
            Tx_backup.enableState = 1u;
        }
        else
        {
            Tx_backup.enableState = 0u;
        }
    #endif /* End Tx_RX_ENABLED || Tx_HD_ENABLED*/

    Tx_Stop();
    Tx_SaveConfig();
}


/*******************************************************************************
* Function Name: Tx_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when 
*  Tx_Sleep() was called. The Tx_Wakeup() function
*  calls the Tx_RestoreConfig() function to restore the 
*  configuration. If the component was enabled before the 
*  Tx_Sleep() function was called, the Tx_Wakeup()
*  function will also re-enable the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  Tx_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Tx_Wakeup(void)
{
    Tx_RestoreConfig();
    #if( (Tx_RX_ENABLED) || (Tx_HD_ENABLED) )
        Tx_ClearRxBuffer();
    #endif /* End (Tx_RX_ENABLED) || (Tx_HD_ENABLED) */
    #if(Tx_TX_ENABLED || Tx_HD_ENABLED)
        Tx_ClearTxBuffer();
    #endif /* End Tx_TX_ENABLED || Tx_HD_ENABLED */

    if(Tx_backup.enableState != 0u)
    {
        Tx_Enable();
    }
}


/* [] END OF FILE */
