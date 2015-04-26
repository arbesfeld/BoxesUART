/*******************************************************************************
* File Name: Rx_Back_PM.c
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

#include "Rx_Back.h"


/***************************************
* Local data allocation
***************************************/

static Rx_Back_BACKUP_STRUCT  Rx_Back_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: Rx_Back_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component configuration and nonretention registers.
*  It also saves the current component parameter values, as defined in the
*  Configure dialog or as modified by appropriate APIs. This function is called
*  by the Rx_Back_Sleep() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  Rx_Back_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
* Side Effects:
*  All nonretention registers except FIFO are saved to RAM
*
*******************************************************************************/
void Rx_Back_SaveConfig(void)
{
    #if(Rx_Back_CONTROL_REG_REMOVED == 0u)
        Rx_Back_backup.cr = Rx_Back_CONTROL_REG;
    #endif /* End Rx_Back_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: Rx_Back_RestoreConfig
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
*  Rx_Back_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
* Side Effects:
*  All nonretention registers except FIFO loaded from RAM. This function should
*  be called only after Rx_Back_SaveConfig() is called, otherwise
*  incorrect data will be loaded into the registers.
*
*******************************************************************************/
void Rx_Back_RestoreConfig(void)
{
    #if(Rx_Back_CONTROL_REG_REMOVED == 0u)
        Rx_Back_CONTROL_REG = Rx_Back_backup.cr;
    #endif /* End Rx_Back_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: Rx_Back_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. 
*  The Rx_Back_Sleep() API saves the current component state. Then it
*  calls the Rx_Back_Stop() function and calls 
*  Rx_Back_SaveConfig() to save the hardware configuration.
*  Call the Rx_Back_Sleep() function before calling the CyPmSleep() 
*  or the CyPmHibernate() function. 
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  Rx_Back_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Rx_Back_Sleep(void)
{
    #if(Rx_Back_RX_ENABLED || Rx_Back_HD_ENABLED)
        if((Rx_Back_RXSTATUS_ACTL_REG  & Rx_Back_INT_ENABLE) != 0u)
        {
            Rx_Back_backup.enableState = 1u;
        }
        else
        {
            Rx_Back_backup.enableState = 0u;
        }
    #else
        if((Rx_Back_TXSTATUS_ACTL_REG  & Rx_Back_INT_ENABLE) !=0u)
        {
            Rx_Back_backup.enableState = 1u;
        }
        else
        {
            Rx_Back_backup.enableState = 0u;
        }
    #endif /* End Rx_Back_RX_ENABLED || Rx_Back_HD_ENABLED*/

    Rx_Back_Stop();
    Rx_Back_SaveConfig();
}


/*******************************************************************************
* Function Name: Rx_Back_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when 
*  Rx_Back_Sleep() was called. The Rx_Back_Wakeup() function
*  calls the Rx_Back_RestoreConfig() function to restore the 
*  configuration. If the component was enabled before the 
*  Rx_Back_Sleep() function was called, the Rx_Back_Wakeup()
*  function will also re-enable the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  Rx_Back_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Rx_Back_Wakeup(void)
{
    Rx_Back_RestoreConfig();
    #if( (Rx_Back_RX_ENABLED) || (Rx_Back_HD_ENABLED) )
        Rx_Back_ClearRxBuffer();
    #endif /* End (Rx_Back_RX_ENABLED) || (Rx_Back_HD_ENABLED) */
    #if(Rx_Back_TX_ENABLED || Rx_Back_HD_ENABLED)
        Rx_Back_ClearTxBuffer();
    #endif /* End Rx_Back_TX_ENABLED || Rx_Back_HD_ENABLED */

    if(Rx_Back_backup.enableState != 0u)
    {
        Rx_Back_Enable();
    }
}


/* [] END OF FILE */
