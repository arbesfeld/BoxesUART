/*******************************************************************************
* File Name: UART_TxRx_Right_UART_BOOT.c
* Version 2.0
*
* Description:
*  This file provides the source code to the API for the bootloader
*  communication support in SCB Component UART mode.
*
* Note:
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "UART_TxRx_Right_BOOT.h"
#include "UART_TxRx_Right_SPI_UART.h"

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_TxRx_Right_UART_BTLDR_COMM_ENABLED)

/***************************************
*    Private I/O Component Vars
***************************************/


/*******************************************************************************
* Function Name: UART_TxRx_Right_UartCyBtldrCommStart
********************************************************************************
*
* Summary:
*  This function does nothing.
*  The SCB in the UART mode does not support the bootloader communication.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void UART_TxRx_Right_UartCyBtldrCommStart(void)
{
    /* Does nothing */
}


/*******************************************************************************
* Function Name: UART_TxRx_Right_UartCyBtldrCommStop
********************************************************************************
*
* Summary:
*  This function does nothing.
*  The SCB in the UART mode does not support the bootloader communication.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void UART_TxRx_Right_UartCyBtldrCommStop(void)
{
    /* Does nothing */
}


/*******************************************************************************
* Function Name: UART_TxRx_Right_UartCyBtldrCommReset
********************************************************************************
*
* Summary:
*  This function does nothing.
*  The SCB in the UART mode does not support the bootloader communication.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void UART_TxRx_Right_UartCyBtldrCommReset(void)
{
    /* Does nothing */
}


/*******************************************************************************
* Function Name: UART_TxRx_Right_UartCyBtldrCommRead
********************************************************************************
*
* Summary:
*  This function does nothing.
*  The SCB in the UART mode does not support the bootloader communication.
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
cystatus UART_TxRx_Right_UartCyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;
    status = CYRET_BAD_PARAM;

    return(status);
}


/*******************************************************************************
* Function Name: UART_TxRx_Right_UartCyBtldrCommWrite
********************************************************************************
*
* Summary:
*  This function does nothing.
*  The SCB in the UART mode does not support the bootloader communication.
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
cystatus UART_TxRx_Right_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;
    status = CYRET_BAD_PARAM;

    return(status);
}

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_TxRx_Right_UART_BTLDR_COMM_ENABLED) */


/* [] END OF FILE */
