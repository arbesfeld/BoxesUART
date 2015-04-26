/*******************************************************************************
* File Name: Rx_Right_Register.c  
* Version 1.90
*
* Description:
*  This file contains API to enable firmware to read the value of a Status 
*  Register.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Rx_Right_Register.h"

#if !defined(Rx_Right_Register_sts_sts_reg__REMOVED) /* Check for removal by optimization */


/*******************************************************************************
* Function Name: Rx_Right_Register_Read
********************************************************************************
*
* Summary:
*  Reads the current value assigned to the Status Register.
*
* Parameters:
*  None.
*
* Return:
*  The current value in the Status Register.
*
*******************************************************************************/
uint8 Rx_Right_Register_Read(void) 
{ 
    return Rx_Right_Register_Status;
}


/*******************************************************************************
* Function Name: Rx_Right_Register_InterruptEnable
********************************************************************************
*
* Summary:
*  Enables the Status Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Rx_Right_Register_InterruptEnable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    Rx_Right_Register_Status_Aux_Ctrl |= Rx_Right_Register_STATUS_INTR_ENBL;
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: Rx_Right_Register_InterruptDisable
********************************************************************************
*
* Summary:
*  Disables the Status Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Rx_Right_Register_InterruptDisable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    Rx_Right_Register_Status_Aux_Ctrl &= (uint8)(~Rx_Right_Register_STATUS_INTR_ENBL);
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: Rx_Right_Register_WriteMask
********************************************************************************
*
* Summary:
*  Writes the current mask value assigned to the Status Register.
*
* Parameters:
*  mask:  Value to write into the mask register.
*
* Return:
*  None.
*
*******************************************************************************/
void Rx_Right_Register_WriteMask(uint8 mask) 
{
    #if(Rx_Right_Register_INPUTS < 8u)
    	mask &= ((uint8)(1u << Rx_Right_Register_INPUTS) - 1u);
	#endif /* End Rx_Right_Register_INPUTS < 8u */
    Rx_Right_Register_Status_Mask = mask;
}


/*******************************************************************************
* Function Name: Rx_Right_Register_ReadMask
********************************************************************************
*
* Summary:
*  Reads the current interrupt mask assigned to the Status Register.
*
* Parameters:
*  None.
*
* Return:
*  The value of the interrupt mask of the Status Register.
*
*******************************************************************************/
uint8 Rx_Right_Register_ReadMask(void) 
{
    return Rx_Right_Register_Status_Mask;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
