/*******************************************************************************
* File Name: RGBLed.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_RGBLed_H) /* Pins RGBLed_H */
#define CY_PINS_RGBLed_H

#include "cytypes.h"
#include "cyfitter.h"
#include "RGBLed_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    RGBLed_Write(uint8 value) ;
void    RGBLed_SetDriveMode(uint8 mode) ;
uint8   RGBLed_ReadDataReg(void) ;
uint8   RGBLed_Read(void) ;
uint8   RGBLed_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define RGBLed_DRIVE_MODE_BITS        (3)
#define RGBLed_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - RGBLed_DRIVE_MODE_BITS))

#define RGBLed_DM_ALG_HIZ         (0x00u)
#define RGBLed_DM_DIG_HIZ         (0x01u)
#define RGBLed_DM_RES_UP          (0x02u)
#define RGBLed_DM_RES_DWN         (0x03u)
#define RGBLed_DM_OD_LO           (0x04u)
#define RGBLed_DM_OD_HI           (0x05u)
#define RGBLed_DM_STRONG          (0x06u)
#define RGBLed_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define RGBLed_MASK               RGBLed__MASK
#define RGBLed_SHIFT              RGBLed__SHIFT
#define RGBLed_WIDTH              3u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define RGBLed_PS                     (* (reg32 *) RGBLed__PS)
/* Port Configuration */
#define RGBLed_PC                     (* (reg32 *) RGBLed__PC)
/* Data Register */
#define RGBLed_DR                     (* (reg32 *) RGBLed__DR)
/* Input Buffer Disable Override */
#define RGBLed_INP_DIS                (* (reg32 *) RGBLed__PC2)


#if defined(RGBLed__INTSTAT)  /* Interrupt Registers */

    #define RGBLed_INTSTAT                (* (reg32 *) RGBLed__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define RGBLed_DRIVE_MODE_SHIFT       (0x00u)
#define RGBLed_DRIVE_MODE_MASK        (0x07u << RGBLed_DRIVE_MODE_SHIFT)


#endif /* End Pins RGBLed_H */


/* [] END OF FILE */
