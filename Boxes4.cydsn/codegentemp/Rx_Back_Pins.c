/*******************************************************************************
* File Name: Rx_Back_Pins.c  
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
#include "Rx_Back_Pins.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        Rx_Back_Pins_PC =   (Rx_Back_Pins_PC & \
                                (uint32)(~(uint32)(Rx_Back_Pins_DRIVE_MODE_IND_MASK << (Rx_Back_Pins_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (Rx_Back_Pins_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: Rx_Back_Pins_Write
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
void Rx_Back_Pins_Write(uint8 value) 
{
    uint8 drVal = (uint8)(Rx_Back_Pins_DR & (uint8)(~Rx_Back_Pins_MASK));
    drVal = (drVal | ((uint8)(value << Rx_Back_Pins_SHIFT) & Rx_Back_Pins_MASK));
    Rx_Back_Pins_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: Rx_Back_Pins_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Rx_Back_Pins_DM_STRONG     Strong Drive 
*  Rx_Back_Pins_DM_OD_HI      Open Drain, Drives High 
*  Rx_Back_Pins_DM_OD_LO      Open Drain, Drives Low 
*  Rx_Back_Pins_DM_RES_UP     Resistive Pull Up 
*  Rx_Back_Pins_DM_RES_DWN    Resistive Pull Down 
*  Rx_Back_Pins_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Rx_Back_Pins_DM_DIG_HIZ    High Impedance Digital 
*  Rx_Back_Pins_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Rx_Back_Pins_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(Rx_Back_Pins__0__SHIFT, mode);
	SetP4PinDriveMode(Rx_Back_Pins__1__SHIFT, mode);
	SetP4PinDriveMode(Rx_Back_Pins__2__SHIFT, mode);
	SetP4PinDriveMode(Rx_Back_Pins__3__SHIFT, mode);
}


/*******************************************************************************
* Function Name: Rx_Back_Pins_Read
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
*  Macro Rx_Back_Pins_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Rx_Back_Pins_Read(void) 
{
    return (uint8)((Rx_Back_Pins_PS & Rx_Back_Pins_MASK) >> Rx_Back_Pins_SHIFT);
}


/*******************************************************************************
* Function Name: Rx_Back_Pins_ReadDataReg
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
uint8 Rx_Back_Pins_ReadDataReg(void) 
{
    return (uint8)((Rx_Back_Pins_DR & Rx_Back_Pins_MASK) >> Rx_Back_Pins_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Rx_Back_Pins_INTSTAT) 

    /*******************************************************************************
    * Function Name: Rx_Back_Pins_ClearInterrupt
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
    uint8 Rx_Back_Pins_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(Rx_Back_Pins_INTSTAT & Rx_Back_Pins_MASK);
		Rx_Back_Pins_INTSTAT = maskedStatus;
        return maskedStatus >> Rx_Back_Pins_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
