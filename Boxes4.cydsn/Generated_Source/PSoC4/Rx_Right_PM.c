/*******************************************************************************
* File Name: Rx_Right_PM.c
* Version 2.0
*
* Description:
*  This file provides the source code to the Power Management support for
*  the SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Rx_Right.h"
#include "Rx_Right_PVT.h"

#if(Rx_Right_SCB_MODE_I2C_INC)
    #include "Rx_Right_I2C_PVT.h"
#endif /* (Rx_Right_SCB_MODE_I2C_INC) */

#if(Rx_Right_SCB_MODE_EZI2C_INC)
    #include "Rx_Right_EZI2C_PVT.h"
#endif /* (Rx_Right_SCB_MODE_EZI2C_INC) */

#if(Rx_Right_SCB_MODE_SPI_INC || Rx_Right_SCB_MODE_UART_INC)
    #include "Rx_Right_SPI_UART_PVT.h"
#endif /* (Rx_Right_SCB_MODE_SPI_INC || Rx_Right_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(Rx_Right_SCB_MODE_UNCONFIG_CONST_CFG || \
   (Rx_Right_SCB_MODE_I2C_CONST_CFG   && (!Rx_Right_I2C_WAKE_ENABLE_CONST))   || \
   (Rx_Right_SCB_MODE_EZI2C_CONST_CFG && (!Rx_Right_EZI2C_WAKE_ENABLE_CONST)) || \
   (Rx_Right_SCB_MODE_SPI_CONST_CFG   && (!Rx_Right_SPI_WAKE_ENABLE_CONST))   || \
   (Rx_Right_SCB_MODE_UART_CONST_CFG  && (!Rx_Right_UART_WAKE_ENABLE_CONST)))

    Rx_Right_BACKUP_STRUCT Rx_Right_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: Rx_Right_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component to enter Deep Sleep.
*  The "Enable wakeup from Sleep Mode" selection has an influence on
*  this function implementation.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Rx_Right_Sleep(void)
{
#if(Rx_Right_SCB_MODE_UNCONFIG_CONST_CFG)

    if(Rx_Right_SCB_WAKE_ENABLE_CHECK)
    {
        if(Rx_Right_SCB_MODE_I2C_RUNTM_CFG)
        {
            Rx_Right_I2CSaveConfig();
        }
        else if(Rx_Right_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            Rx_Right_EzI2CSaveConfig();
        }
    #if(!Rx_Right_CY_SCBIP_V1)
        else if(Rx_Right_SCB_MODE_SPI_RUNTM_CFG)
        {
            Rx_Right_SpiSaveConfig();
        }
        else if(Rx_Right_SCB_MODE_UART_RUNTM_CFG)
        {
            Rx_Right_UartSaveConfig();
        }
    #endif /* (!Rx_Right_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        Rx_Right_backup.enableState = (uint8) Rx_Right_GET_CTRL_ENABLED;

        if(0u != Rx_Right_backup.enableState)
        {
            Rx_Right_Stop();
        }
    }

#else

    #if (Rx_Right_SCB_MODE_I2C_CONST_CFG && Rx_Right_I2C_WAKE_ENABLE_CONST)
        Rx_Right_I2CSaveConfig();

    #elif (Rx_Right_SCB_MODE_EZI2C_CONST_CFG && Rx_Right_EZI2C_WAKE_ENABLE_CONST)
        Rx_Right_EzI2CSaveConfig();

    #elif (Rx_Right_SCB_MODE_SPI_CONST_CFG && Rx_Right_SPI_WAKE_ENABLE_CONST)
        Rx_Right_SpiSaveConfig();

    #elif (Rx_Right_SCB_MODE_UART_CONST_CFG && Rx_Right_UART_WAKE_ENABLE_CONST)
        Rx_Right_UartSaveConfig();

    #else

        Rx_Right_backup.enableState = (uint8) Rx_Right_GET_CTRL_ENABLED;

        if(0u != Rx_Right_backup.enableState)
        {
            Rx_Right_Stop();
        }

    #endif /* defined (Rx_Right_SCB_MODE_I2C_CONST_CFG) && (Rx_Right_I2C_WAKE_ENABLE_CONST) */

#endif /* (Rx_Right_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: Rx_Right_Wakeup
********************************************************************************
*
* Summary:
*  Prepares the component for the Active mode operation after exiting
*  Deep Sleep. The "Enable wakeup from Sleep Mode" option has an influence
*  on this function implementation.
*  This function should not be called after exiting Sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Rx_Right_Wakeup(void)
{
#if(Rx_Right_SCB_MODE_UNCONFIG_CONST_CFG)

    if(Rx_Right_SCB_WAKE_ENABLE_CHECK)
    {
        if(Rx_Right_SCB_MODE_I2C_RUNTM_CFG)
        {
            Rx_Right_I2CRestoreConfig();
        }
        else if(Rx_Right_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            Rx_Right_EzI2CRestoreConfig();
        }
    #if(!Rx_Right_CY_SCBIP_V1)
        else if(Rx_Right_SCB_MODE_SPI_RUNTM_CFG)
        {
            Rx_Right_SpiRestoreConfig();
        }
        else if(Rx_Right_SCB_MODE_UART_RUNTM_CFG)
        {
            Rx_Right_UartRestoreConfig();
        }
    #endif /* (!Rx_Right_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != Rx_Right_backup.enableState)
        {
            Rx_Right_Enable();
        }
    }

#else

    #if (Rx_Right_SCB_MODE_I2C_CONST_CFG  && Rx_Right_I2C_WAKE_ENABLE_CONST)
        Rx_Right_I2CRestoreConfig();

    #elif (Rx_Right_SCB_MODE_EZI2C_CONST_CFG && Rx_Right_EZI2C_WAKE_ENABLE_CONST)
        Rx_Right_EzI2CRestoreConfig();

    #elif (Rx_Right_SCB_MODE_SPI_CONST_CFG && Rx_Right_SPI_WAKE_ENABLE_CONST)
        Rx_Right_SpiRestoreConfig();

    #elif (Rx_Right_SCB_MODE_UART_CONST_CFG && Rx_Right_UART_WAKE_ENABLE_CONST)
        Rx_Right_UartRestoreConfig();

    #else

        if(0u != Rx_Right_backup.enableState)
        {
            Rx_Right_Enable();
        }

    #endif /* (Rx_Right_I2C_WAKE_ENABLE_CONST) */

#endif /* (Rx_Right_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
