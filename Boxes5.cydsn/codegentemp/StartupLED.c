/*******************************************************************************
* File Name: StartupLED.c  
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
#include "StartupLED.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 StartupLED__PORT == 15 && ((StartupLED__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: StartupLED_Write
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
void StartupLED_Write(uint8 value) 
{
    uint8 staticBits = (StartupLED_DR & (uint8)(~StartupLED_MASK));
    StartupLED_DR = staticBits | ((uint8)(value << StartupLED_SHIFT) & StartupLED_MASK);
}


/*******************************************************************************
* Function Name: StartupLED_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  StartupLED_DM_STRONG     Strong Drive 
*  StartupLED_DM_OD_HI      Open Drain, Drives High 
*  StartupLED_DM_OD_LO      Open Drain, Drives Low 
*  StartupLED_DM_RES_UP     Resistive Pull Up 
*  StartupLED_DM_RES_DWN    Resistive Pull Down 
*  StartupLED_DM_RES_UPDWN  Resistive Pull Up/Down 
*  StartupLED_DM_DIG_HIZ    High Impedance Digital 
*  StartupLED_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void StartupLED_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(StartupLED_0, mode);
}


/*******************************************************************************
* Function Name: StartupLED_Read
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
*  Macro StartupLED_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 StartupLED_Read(void) 
{
    return (StartupLED_PS & StartupLED_MASK) >> StartupLED_SHIFT;
}


/*******************************************************************************
* Function Name: StartupLED_ReadDataReg
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
uint8 StartupLED_ReadDataReg(void) 
{
    return (StartupLED_DR & StartupLED_MASK) >> StartupLED_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(StartupLED_INTSTAT) 

    /*******************************************************************************
    * Function Name: StartupLED_ClearInterrupt
    ********************************************************************************
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
    uint8 StartupLED_ClearInterrupt(void) 
    {
        return (StartupLED_INTSTAT & StartupLED_MASK) >> StartupLED_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
