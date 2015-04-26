/*******************************************************************************
* File Name: RGBLed.c  
* Version 2.10
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "RGBLed.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        RGBLed_PC =   (RGBLed_PC & \
                                (uint32)(~(uint32)(RGBLed_DRIVE_MODE_IND_MASK << (RGBLed_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (RGBLed_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: RGBLed_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None 
*  
*******************************************************************************/
void RGBLed_Write(uint8 value) 
{
    uint8 drVal = (uint8)(RGBLed_DR & (uint8)(~RGBLed_MASK));
    drVal = (drVal | ((uint8)(value << RGBLed_SHIFT) & RGBLed_MASK));
    RGBLed_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: RGBLed_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  RGBLed_DM_STRONG     Strong Drive 
*  RGBLed_DM_OD_HI      Open Drain, Drives High 
*  RGBLed_DM_OD_LO      Open Drain, Drives Low 
*  RGBLed_DM_RES_UP     Resistive Pull Up 
*  RGBLed_DM_RES_DWN    Resistive Pull Down 
*  RGBLed_DM_RES_UPDWN  Resistive Pull Up/Down 
*  RGBLed_DM_DIG_HIZ    High Impedance Digital 
*  RGBLed_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void RGBLed_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(RGBLed__0__SHIFT, mode);
	SetP4PinDriveMode(RGBLed__1__SHIFT, mode);
	SetP4PinDriveMode(RGBLed__2__SHIFT, mode);
}


/*******************************************************************************
* Function Name: RGBLed_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro RGBLed_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 RGBLed_Read(void) 
{
    return (uint8)((RGBLed_PS & RGBLed_MASK) >> RGBLed_SHIFT);
}


/*******************************************************************************
* Function Name: RGBLed_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 RGBLed_ReadDataReg(void) 
{
    return (uint8)((RGBLed_DR & RGBLed_MASK) >> RGBLed_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(RGBLed_INTSTAT) 

    /*******************************************************************************
    * Function Name: RGBLed_ClearInterrupt
    ********************************************************************************
    *
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 RGBLed_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(RGBLed_INTSTAT & RGBLed_MASK);
		RGBLed_INTSTAT = maskedStatus;
        return maskedStatus >> RGBLed_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
