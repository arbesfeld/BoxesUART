/*******************************************************************************
* File Name: UART_Rx_Right_PM.c
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

#include "UART_Rx_Right.h"
#include "UART_Rx_Right_PVT.h"

#if(UART_Rx_Right_SCB_MODE_I2C_INC)
    #include "UART_Rx_Right_I2C_PVT.h"
#endif /* (UART_Rx_Right_SCB_MODE_I2C_INC) */

#if(UART_Rx_Right_SCB_MODE_EZI2C_INC)
    #include "UART_Rx_Right_EZI2C_PVT.h"
#endif /* (UART_Rx_Right_SCB_MODE_EZI2C_INC) */

#if(UART_Rx_Right_SCB_MODE_SPI_INC || UART_Rx_Right_SCB_MODE_UART_INC)
    #include "UART_Rx_Right_SPI_UART_PVT.h"
#endif /* (UART_Rx_Right_SCB_MODE_SPI_INC || UART_Rx_Right_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(UART_Rx_Right_SCB_MODE_UNCONFIG_CONST_CFG || \
   (UART_Rx_Right_SCB_MODE_I2C_CONST_CFG   && (!UART_Rx_Right_I2C_WAKE_ENABLE_CONST))   || \
   (UART_Rx_Right_SCB_MODE_EZI2C_CONST_CFG && (!UART_Rx_Right_EZI2C_WAKE_ENABLE_CONST)) || \
   (UART_Rx_Right_SCB_MODE_SPI_CONST_CFG   && (!UART_Rx_Right_SPI_WAKE_ENABLE_CONST))   || \
   (UART_Rx_Right_SCB_MODE_UART_CONST_CFG  && (!UART_Rx_Right_UART_WAKE_ENABLE_CONST)))

    UART_Rx_Right_BACKUP_STRUCT UART_Rx_Right_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: UART_Rx_Right_Sleep
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
void UART_Rx_Right_Sleep(void)
{
#if(UART_Rx_Right_SCB_MODE_UNCONFIG_CONST_CFG)

    if(UART_Rx_Right_SCB_WAKE_ENABLE_CHECK)
    {
        if(UART_Rx_Right_SCB_MODE_I2C_RUNTM_CFG)
        {
            UART_Rx_Right_I2CSaveConfig();
        }
        else if(UART_Rx_Right_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            UART_Rx_Right_EzI2CSaveConfig();
        }
    #if(!UART_Rx_Right_CY_SCBIP_V1)
        else if(UART_Rx_Right_SCB_MODE_SPI_RUNTM_CFG)
        {
            UART_Rx_Right_SpiSaveConfig();
        }
        else if(UART_Rx_Right_SCB_MODE_UART_RUNTM_CFG)
        {
            UART_Rx_Right_UartSaveConfig();
        }
    #endif /* (!UART_Rx_Right_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        UART_Rx_Right_backup.enableState = (uint8) UART_Rx_Right_GET_CTRL_ENABLED;

        if(0u != UART_Rx_Right_backup.enableState)
        {
            UART_Rx_Right_Stop();
        }
    }

#else

    #if (UART_Rx_Right_SCB_MODE_I2C_CONST_CFG && UART_Rx_Right_I2C_WAKE_ENABLE_CONST)
        UART_Rx_Right_I2CSaveConfig();

    #elif (UART_Rx_Right_SCB_MODE_EZI2C_CONST_CFG && UART_Rx_Right_EZI2C_WAKE_ENABLE_CONST)
        UART_Rx_Right_EzI2CSaveConfig();

    #elif (UART_Rx_Right_SCB_MODE_SPI_CONST_CFG && UART_Rx_Right_SPI_WAKE_ENABLE_CONST)
        UART_Rx_Right_SpiSaveConfig();

    #elif (UART_Rx_Right_SCB_MODE_UART_CONST_CFG && UART_Rx_Right_UART_WAKE_ENABLE_CONST)
        UART_Rx_Right_UartSaveConfig();

    #else

        UART_Rx_Right_backup.enableState = (uint8) UART_Rx_Right_GET_CTRL_ENABLED;

        if(0u != UART_Rx_Right_backup.enableState)
        {
            UART_Rx_Right_Stop();
        }

    #endif /* defined (UART_Rx_Right_SCB_MODE_I2C_CONST_CFG) && (UART_Rx_Right_I2C_WAKE_ENABLE_CONST) */

#endif /* (UART_Rx_Right_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: UART_Rx_Right_Wakeup
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
void UART_Rx_Right_Wakeup(void)
{
#if(UART_Rx_Right_SCB_MODE_UNCONFIG_CONST_CFG)

    if(UART_Rx_Right_SCB_WAKE_ENABLE_CHECK)
    {
        if(UART_Rx_Right_SCB_MODE_I2C_RUNTM_CFG)
        {
            UART_Rx_Right_I2CRestoreConfig();
        }
        else if(UART_Rx_Right_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            UART_Rx_Right_EzI2CRestoreConfig();
        }
    #if(!UART_Rx_Right_CY_SCBIP_V1)
        else if(UART_Rx_Right_SCB_MODE_SPI_RUNTM_CFG)
        {
            UART_Rx_Right_SpiRestoreConfig();
        }
        else if(UART_Rx_Right_SCB_MODE_UART_RUNTM_CFG)
        {
            UART_Rx_Right_UartRestoreConfig();
        }
    #endif /* (!UART_Rx_Right_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != UART_Rx_Right_backup.enableState)
        {
            UART_Rx_Right_Enable();
        }
    }

#else

    #if (UART_Rx_Right_SCB_MODE_I2C_CONST_CFG  && UART_Rx_Right_I2C_WAKE_ENABLE_CONST)
        UART_Rx_Right_I2CRestoreConfig();

    #elif (UART_Rx_Right_SCB_MODE_EZI2C_CONST_CFG && UART_Rx_Right_EZI2C_WAKE_ENABLE_CONST)
        UART_Rx_Right_EzI2CRestoreConfig();

    #elif (UART_Rx_Right_SCB_MODE_SPI_CONST_CFG && UART_Rx_Right_SPI_WAKE_ENABLE_CONST)
        UART_Rx_Right_SpiRestoreConfig();

    #elif (UART_Rx_Right_SCB_MODE_UART_CONST_CFG && UART_Rx_Right_UART_WAKE_ENABLE_CONST)
        UART_Rx_Right_UartRestoreConfig();

    #else

        if(0u != UART_Rx_Right_backup.enableState)
        {
            UART_Rx_Right_Enable();
        }

    #endif /* (UART_Rx_Right_I2C_WAKE_ENABLE_CONST) */

#endif /* (UART_Rx_Right_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
