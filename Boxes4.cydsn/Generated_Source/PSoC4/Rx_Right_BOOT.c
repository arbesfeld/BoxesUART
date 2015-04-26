/*******************************************************************************
* File Name: Rx_Right_BOOT.c
* Version 2.0
*
* Description:
*  This file provides the source code to the API for the bootloader
*  communication support in the SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Rx_Right_BOOT.h"


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (Rx_Right_BTLDR_COMM_MODE_ENABLED)

/*******************************************************************************
* Function Name: Rx_Right_CyBtldrCommStart
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommStart function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Rx_Right_CyBtldrCommStart(void)
{
    #if(Rx_Right_SCB_MODE_UNCONFIG_CONST_CFG)
        if(Rx_Right_SCB_MODE_I2C_RUNTM_CFG)
        {
            Rx_Right_I2CCyBtldrCommStart();
        }
        else if(Rx_Right_SCB_MODE_SPI_RUNTM_CFG)
        {
            Rx_Right_SpiCyBtldrCommStart();
        }
        else if(Rx_Right_SCB_MODE_UART_RUNTM_CFG)
        {
            Rx_Right_UartCyBtldrCommStart();
        }
        else if(Rx_Right_SCB_MODE_EZI2C_RUNTM_CFG)
        {
             Rx_Right_EzI2CCyBtldrCommStart();
        }
        else
        {
            /* Unknown mode */
        }
    #elif(Rx_Right_SCB_MODE_I2C_CONST_CFG)
        Rx_Right_I2CCyBtldrCommStart();

    #elif(Rx_Right_SCB_MODE_SPI_CONST_CFG)
        Rx_Right_SpiCyBtldrCommStart();

    #elif(Rx_Right_SCB_MODE_UART_CONST_CFG)
        Rx_Right_UartCyBtldrCommStart();

    #elif(Rx_Right_SCB_MODE_EZI2C_CONST_CFG)
        Rx_Right_EzI2CCyBtldrCommStart();

    #else
        /* Unknown mode */

    #endif /* (Rx_Right_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: Rx_Right_CyBtldrCommStop
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommStop function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Rx_Right_CyBtldrCommStop(void)
{
    #if(Rx_Right_SCB_MODE_UNCONFIG_CONST_CFG)
        if(Rx_Right_SCB_MODE_I2C_RUNTM_CFG)
        {
            Rx_Right_I2CCyBtldrCommStop();
        }
        else if(Rx_Right_SCB_MODE_SPI_RUNTM_CFG)
        {
            Rx_Right_SpiCyBtldrCommStop();
        }
        else if(Rx_Right_SCB_MODE_UART_RUNTM_CFG)
        {
            Rx_Right_UartCyBtldrCommStop();
        }
        else if(Rx_Right_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            Rx_Right_EzI2CCyBtldrCommStop();
        }
        else
        {
            /* Unknown mode */
        }
    #elif(Rx_Right_SCB_MODE_I2C_CONST_CFG)
        Rx_Right_I2CCyBtldrCommStop();

    #elif(Rx_Right_SCB_MODE_SPI_CONST_CFG)
        Rx_Right_SpiCyBtldrCommStop();

    #elif(Rx_Right_SCB_MODE_UART_CONST_CFG)
        Rx_Right_UartCyBtldrCommStop();

    #elif(Rx_Right_SCB_MODE_EZI2C_CONST_CFG)
        Rx_Right_EzI2CCyBtldrCommStop();

    #else
        /* Unknown mode */

    #endif /* (Rx_Right_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: Rx_Right_CyBtldrCommReset
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommReset function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Rx_Right_CyBtldrCommReset(void)
{
    #if(Rx_Right_SCB_MODE_UNCONFIG_CONST_CFG)
        if(Rx_Right_SCB_MODE_I2C_RUNTM_CFG)
        {
            Rx_Right_I2CCyBtldrCommReset();
        }
        else if(Rx_Right_SCB_MODE_SPI_RUNTM_CFG)
        {
            Rx_Right_SpiCyBtldrCommReset();
        }
        else if(Rx_Right_SCB_MODE_UART_RUNTM_CFG)
        {
            Rx_Right_UartCyBtldrCommReset();
        }
        else if(Rx_Right_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            Rx_Right_EzI2CCyBtldrCommReset();
        }
        else
        {
            /* Unknown mode */
        }
    #elif(Rx_Right_SCB_MODE_I2C_CONST_CFG)
        Rx_Right_I2CCyBtldrCommReset();

    #elif(Rx_Right_SCB_MODE_SPI_CONST_CFG)
        Rx_Right_SpiCyBtldrCommReset();

    #elif(Rx_Right_SCB_MODE_UART_CONST_CFG)
        Rx_Right_UartCyBtldrCommReset();

    #elif(Rx_Right_SCB_MODE_EZI2C_CONST_CFG)
        Rx_Right_EzI2CCyBtldrCommReset();

    #else
        /* Unknown mode */

    #endif /* (Rx_Right_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: Rx_Right_CyBtldrCommRead
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommRead function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  pData:    Pointer to storage for the block of data to be read from the
*            bootloader host
*  size:     Number of bytes to be read.
*  count:    Pointer to the variable to write the number of bytes actually
*            read.
*  timeOut:  Number of units in 10 ms to wait before returning because of a
*            timeout.
*
* Return:
*  Returns CYRET_SUCCESS if no problem was encountered or returns the value
*  that best describes the problem.
*
*******************************************************************************/
cystatus Rx_Right_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    #if(Rx_Right_SCB_MODE_UNCONFIG_CONST_CFG)
        if(Rx_Right_SCB_MODE_I2C_RUNTM_CFG)
        {
            status = Rx_Right_I2CCyBtldrCommRead(pData, size, count, timeOut);
        }
        else if(Rx_Right_SCB_MODE_SPI_RUNTM_CFG)
        {
            status = Rx_Right_SpiCyBtldrCommRead(pData, size, count, timeOut);
        }
        else if(Rx_Right_SCB_MODE_UART_RUNTM_CFG)
        {
            status = Rx_Right_UartCyBtldrCommRead(pData, size, count, timeOut);
        }
        else if(Rx_Right_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            status = Rx_Right_EzI2CCyBtldrCommRead(pData, size, count, timeOut);
        }
        else
        {
            status = CYRET_INVALID_STATE; /* Unknown mode: return status */
        }

    #elif(Rx_Right_SCB_MODE_I2C_CONST_CFG)
        status = Rx_Right_I2CCyBtldrCommRead(pData, size, count, timeOut);

    #elif(Rx_Right_SCB_MODE_SPI_CONST_CFG)
        status = Rx_Right_SpiCyBtldrCommRead(pData, size, count, timeOut);

    #elif(Rx_Right_SCB_MODE_UART_CONST_CFG)
        status = Rx_Right_UartCyBtldrCommRead(pData, size, count, timeOut);

    #elif(Rx_Right_SCB_MODE_EZI2C_CONST_CFG)
        status = Rx_Right_EzI2CCyBtldrCommRead(pData, size, count, timeOut);

    #else
        status = CYRET_INVALID_STATE; /* Unknown mode: return status */

    #endif /* (Rx_Right_SCB_MODE_UNCONFIG_CONST_CFG) */

    return(status);
}


/*******************************************************************************
* Function Name: Rx_Right_CyBtldrCommWrite
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommWrite  function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  pData:    Pointer to the block of data to be written to the bootloader host.
*  size:     Number of bytes to be written.
*  count:    Pointer to the variable to write the number of bytes actually
*            written.
*  timeOut:  Number of units in 10 ms to wait before returning because of a
*            timeout.
*
* Return:
*  Returns CYRET_SUCCESS if no problem was encountered or returns the value
*  that best describes the problem.
*
*******************************************************************************/
cystatus Rx_Right_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    #if(Rx_Right_SCB_MODE_UNCONFIG_CONST_CFG)
        if(Rx_Right_SCB_MODE_I2C_RUNTM_CFG)
        {
            status = Rx_Right_I2CCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else if(Rx_Right_SCB_MODE_SPI_RUNTM_CFG)
        {
            status = Rx_Right_SpiCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else if(Rx_Right_SCB_MODE_UART_RUNTM_CFG)
        {
            status = Rx_Right_UartCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else if(Rx_Right_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            status = Rx_Right_EzI2CCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else
        {
            status = CYRET_INVALID_STATE; /* Unknown mode */
        }
    #elif(Rx_Right_SCB_MODE_I2C_CONST_CFG)
        status = Rx_Right_I2CCyBtldrCommWrite(pData, size, count, timeOut);

    #elif(Rx_Right_SCB_MODE_SPI_CONST_CFG)
        status = Rx_Right_SpiCyBtldrCommWrite(pData, size, count, timeOut);

    #elif(Rx_Right_SCB_MODE_UART_CONST_CFG)
        status = Rx_Right_UartCyBtldrCommWrite(pData, size, count, timeOut);

    #elif(Rx_Right_SCB_MODE_EZI2C_CONST_CFG)
        status = Rx_Right_EzI2CCyBtldrCommWrite(pData, size, count, timeOut);

    #else
        status = CYRET_INVALID_STATE; /* Unknown mode */

    #endif /* (Rx_Right_SCB_MODE_UNCONFIG_CONST_CFG) */

    return(status);
}

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (Rx_Right_BTLDR_COMM_MODE_ENABLED) */


/* [] END OF FILE */
