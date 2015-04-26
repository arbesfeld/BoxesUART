/*******************************************************************************
* File Name: UART_Rx_Right_1_PM.c
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

#include "UART_Rx_Right_1.h"
#include "UART_Rx_Right_1_PVT.h"

#if(UART_Rx_Right_1_SCB_MODE_I2C_INC)
    #include "UART_Rx_Right_1_I2C_PVT.h"
#endif /* (UART_Rx_Right_1_SCB_MODE_I2C_INC) */

#if(UART_Rx_Right_1_SCB_MODE_EZI2C_INC)
    #include "UART_Rx_Right_1_EZI2C_PVT.h"
#endif /* (UART_Rx_Right_1_SCB_MODE_EZI2C_INC) */

#if(UART_Rx_Right_1_SCB_MODE_SPI_INC || UART_Rx_Right_1_SCB_MODE_UART_INC)
    #include "UART_Rx_Right_1_SPI_UART_PVT.h"
#endif /* (UART_Rx_Right_1_SCB_MODE_SPI_INC || UART_Rx_Right_1_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(UART_Rx_Right_1_SCB_MODE_UNCONFIG_CONST_CFG || \
   (UART_Rx_Right_1_SCB_MODE_I2C_CONST_CFG   && (!UART_Rx_Right_1_I2C_WAKE_ENABLE_CONST))   || \
   (UART_Rx_Right_1_SCB_MODE_EZI2C_CONST_CFG && (!UART_Rx_Right_1_EZI2C_WAKE_ENABLE_CONST)) || \
   (UART_Rx_Right_1_SCB_MODE_SPI_CONST_CFG   && (!UART_Rx_Right_1_SPI_WAKE_ENABLE_CONST))   || \
   (UART_Rx_Right_1_SCB_MODE_UART_CONST_CFG  && (!UART_Rx_Right_1_UART_WAKE_ENABLE_CONST)))

    UART_Rx_Right_1_BACKUP_STRUCT UART_Rx_Right_1_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: UART_Rx_Right_1_Sleep
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
void UART_Rx_Right_1_Sleep(void)
{
#if(UART_Rx_Right_1_SCB_MODE_UNCONFIG_CONST_CFG)

    if(UART_Rx_Right_1_SCB_WAKE_ENABLE_CHECK)
    {
        if(UART_Rx_Right_1_SCB_MODE_I2C_RUNTM_CFG)
        {
            UART_Rx_Right_1_I2CSaveConfig();
        }
        else if(UART_Rx_Right_1_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            UART_Rx_Right_1_EzI2CSaveConfig();
        }
    #if(!UART_Rx_Right_1_CY_SCBIP_V1)
        else if(UART_Rx_Right_1_SCB_MODE_SPI_RUNTM_CFG)
        {
            UART_Rx_Right_1_SpiSaveConfig();
        }
        else if(UART_Rx_Right_1_SCB_MODE_UART_RUNTM_CFG)
        {
            UART_Rx_Right_1_UartSaveConfig();
        }
    #endif /* (!UART_Rx_Right_1_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        UART_Rx_Right_1_backup.enableState = (uint8) UART_Rx_Right_1_GET_CTRL_ENABLED;

        if(0u != UART_Rx_Right_1_backup.enableState)
        {
            UART_Rx_Right_1_Stop();
        }
    }

#else

    #if (UART_Rx_Right_1_SCB_MODE_I2C_CONST_CFG && UART_Rx_Right_1_I2C_WAKE_ENABLE_CONST)
        UART_Rx_Right_1_I2CSaveConfig();

    #elif (UART_Rx_Right_1_SCB_MODE_EZI2C_CONST_CFG && UART_Rx_Right_1_EZI2C_WAKE_ENABLE_CONST)
        UART_Rx_Right_1_EzI2CSaveConfig();

    #elif (UART_Rx_Right_1_SCB_MODE_SPI_CONST_CFG && UART_Rx_Right_1_SPI_WAKE_ENABLE_CONST)
        UART_Rx_Right_1_SpiSaveConfig();

    #elif (UART_Rx_Right_1_SCB_MODE_UART_CONST_CFG && UART_Rx_Right_1_UART_WAKE_ENABLE_CONST)
        UART_Rx_Right_1_UartSaveConfig();

    #else

        UART_Rx_Right_1_backup.enableState = (uint8) UART_Rx_Right_1_GET_CTRL_ENABLED;

        if(0u != UART_Rx_Right_1_backup.enableState)
        {
            UART_Rx_Right_1_Stop();
        }

    #endif /* defined (UART_Rx_Right_1_SCB_MODE_I2C_CONST_CFG) && (UART_Rx_Right_1_I2C_WAKE_ENABLE_CONST) */

#endif /* (UART_Rx_Right_1_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: UART_Rx_Right_1_Wakeup
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
void UART_Rx_Right_1_Wakeup(void)
{
#if(UART_Rx_Right_1_SCB_MODE_UNCONFIG_CONST_CFG)

    if(UART_Rx_Right_1_SCB_WAKE_ENABLE_CHECK)
    {
        if(UART_Rx_Right_1_SCB_MODE_I2C_RUNTM_CFG)
        {
            UART_Rx_Right_1_I2CRestoreConfig();
        }
        else if(UART_Rx_Right_1_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            UART_Rx_Right_1_EzI2CRestoreConfig();
        }
    #if(!UART_Rx_Right_1_CY_SCBIP_V1)
        else if(UART_Rx_Right_1_SCB_MODE_SPI_RUNTM_CFG)
        {
            UART_Rx_Right_1_SpiRestoreConfig();
        }
        else if(UART_Rx_Right_1_SCB_MODE_UART_RUNTM_CFG)
        {
            UART_Rx_Right_1_UartRestoreConfig();
        }
    #endif /* (!UART_Rx_Right_1_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != UART_Rx_Right_1_backup.enableState)
        {
            UART_Rx_Right_1_Enable();
        }
    }

#else

    #if (UART_Rx_Right_1_SCB_MODE_I2C_CONST_CFG  && UART_Rx_Right_1_I2C_WAKE_ENABLE_CONST)
        UART_Rx_Right_1_I2CRestoreConfig();

    #elif (UART_Rx_Right_1_SCB_MODE_EZI2C_CONST_CFG && UART_Rx_Right_1_EZI2C_WAKE_ENABLE_CONST)
        UART_Rx_Right_1_EzI2CRestoreConfig();

    #elif (UART_Rx_Right_1_SCB_MODE_SPI_CONST_CFG && UART_Rx_Right_1_SPI_WAKE_ENABLE_CONST)
        UART_Rx_Right_1_SpiRestoreConfig();

    #elif (UART_Rx_Right_1_SCB_MODE_UART_CONST_CFG && UART_Rx_Right_1_UART_WAKE_ENABLE_CONST)
        UART_Rx_Right_1_UartRestoreConfig();

    #else

        if(0u != UART_Rx_Right_1_backup.enableState)
        {
            UART_Rx_Right_1_Enable();
        }

    #endif /* (UART_Rx_Right_1_I2C_WAKE_ENABLE_CONST) */

#endif /* (UART_Rx_Right_1_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
