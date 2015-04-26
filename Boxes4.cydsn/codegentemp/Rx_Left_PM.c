/*******************************************************************************
* File Name: Rx_Left_PM.c
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

#include "Rx_Left.h"
#include "Rx_Left_PVT.h"

#if(Rx_Left_SCB_MODE_I2C_INC)
    #include "Rx_Left_I2C_PVT.h"
#endif /* (Rx_Left_SCB_MODE_I2C_INC) */

#if(Rx_Left_SCB_MODE_EZI2C_INC)
    #include "Rx_Left_EZI2C_PVT.h"
#endif /* (Rx_Left_SCB_MODE_EZI2C_INC) */

#if(Rx_Left_SCB_MODE_SPI_INC || Rx_Left_SCB_MODE_UART_INC)
    #include "Rx_Left_SPI_UART_PVT.h"
#endif /* (Rx_Left_SCB_MODE_SPI_INC || Rx_Left_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(Rx_Left_SCB_MODE_UNCONFIG_CONST_CFG || \
   (Rx_Left_SCB_MODE_I2C_CONST_CFG   && (!Rx_Left_I2C_WAKE_ENABLE_CONST))   || \
   (Rx_Left_SCB_MODE_EZI2C_CONST_CFG && (!Rx_Left_EZI2C_WAKE_ENABLE_CONST)) || \
   (Rx_Left_SCB_MODE_SPI_CONST_CFG   && (!Rx_Left_SPI_WAKE_ENABLE_CONST))   || \
   (Rx_Left_SCB_MODE_UART_CONST_CFG  && (!Rx_Left_UART_WAKE_ENABLE_CONST)))

    Rx_Left_BACKUP_STRUCT Rx_Left_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: Rx_Left_Sleep
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
void Rx_Left_Sleep(void)
{
#if(Rx_Left_SCB_MODE_UNCONFIG_CONST_CFG)

    if(Rx_Left_SCB_WAKE_ENABLE_CHECK)
    {
        if(Rx_Left_SCB_MODE_I2C_RUNTM_CFG)
        {
            Rx_Left_I2CSaveConfig();
        }
        else if(Rx_Left_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            Rx_Left_EzI2CSaveConfig();
        }
    #if(!Rx_Left_CY_SCBIP_V1)
        else if(Rx_Left_SCB_MODE_SPI_RUNTM_CFG)
        {
            Rx_Left_SpiSaveConfig();
        }
        else if(Rx_Left_SCB_MODE_UART_RUNTM_CFG)
        {
            Rx_Left_UartSaveConfig();
        }
    #endif /* (!Rx_Left_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        Rx_Left_backup.enableState = (uint8) Rx_Left_GET_CTRL_ENABLED;

        if(0u != Rx_Left_backup.enableState)
        {
            Rx_Left_Stop();
        }
    }

#else

    #if (Rx_Left_SCB_MODE_I2C_CONST_CFG && Rx_Left_I2C_WAKE_ENABLE_CONST)
        Rx_Left_I2CSaveConfig();

    #elif (Rx_Left_SCB_MODE_EZI2C_CONST_CFG && Rx_Left_EZI2C_WAKE_ENABLE_CONST)
        Rx_Left_EzI2CSaveConfig();

    #elif (Rx_Left_SCB_MODE_SPI_CONST_CFG && Rx_Left_SPI_WAKE_ENABLE_CONST)
        Rx_Left_SpiSaveConfig();

    #elif (Rx_Left_SCB_MODE_UART_CONST_CFG && Rx_Left_UART_WAKE_ENABLE_CONST)
        Rx_Left_UartSaveConfig();

    #else

        Rx_Left_backup.enableState = (uint8) Rx_Left_GET_CTRL_ENABLED;

        if(0u != Rx_Left_backup.enableState)
        {
            Rx_Left_Stop();
        }

    #endif /* defined (Rx_Left_SCB_MODE_I2C_CONST_CFG) && (Rx_Left_I2C_WAKE_ENABLE_CONST) */

#endif /* (Rx_Left_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: Rx_Left_Wakeup
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
void Rx_Left_Wakeup(void)
{
#if(Rx_Left_SCB_MODE_UNCONFIG_CONST_CFG)

    if(Rx_Left_SCB_WAKE_ENABLE_CHECK)
    {
        if(Rx_Left_SCB_MODE_I2C_RUNTM_CFG)
        {
            Rx_Left_I2CRestoreConfig();
        }
        else if(Rx_Left_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            Rx_Left_EzI2CRestoreConfig();
        }
    #if(!Rx_Left_CY_SCBIP_V1)
        else if(Rx_Left_SCB_MODE_SPI_RUNTM_CFG)
        {
            Rx_Left_SpiRestoreConfig();
        }
        else if(Rx_Left_SCB_MODE_UART_RUNTM_CFG)
        {
            Rx_Left_UartRestoreConfig();
        }
    #endif /* (!Rx_Left_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != Rx_Left_backup.enableState)
        {
            Rx_Left_Enable();
        }
    }

#else

    #if (Rx_Left_SCB_MODE_I2C_CONST_CFG  && Rx_Left_I2C_WAKE_ENABLE_CONST)
        Rx_Left_I2CRestoreConfig();

    #elif (Rx_Left_SCB_MODE_EZI2C_CONST_CFG && Rx_Left_EZI2C_WAKE_ENABLE_CONST)
        Rx_Left_EzI2CRestoreConfig();

    #elif (Rx_Left_SCB_MODE_SPI_CONST_CFG && Rx_Left_SPI_WAKE_ENABLE_CONST)
        Rx_Left_SpiRestoreConfig();

    #elif (Rx_Left_SCB_MODE_UART_CONST_CFG && Rx_Left_UART_WAKE_ENABLE_CONST)
        Rx_Left_UartRestoreConfig();

    #else

        if(0u != Rx_Left_backup.enableState)
        {
            Rx_Left_Enable();
        }

    #endif /* (Rx_Left_I2C_WAKE_ENABLE_CONST) */

#endif /* (Rx_Left_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
