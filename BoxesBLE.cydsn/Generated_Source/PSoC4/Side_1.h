/*******************************************************************************
* File Name: Side_1.h  
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

#if !defined(CY_PINS_Side_1_H) /* Pins Side_1_H */
#define CY_PINS_Side_1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Side_1_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Side_1_Write(uint8 value) ;
void    Side_1_SetDriveMode(uint8 mode) ;
uint8   Side_1_ReadDataReg(void) ;
uint8   Side_1_Read(void) ;
uint8   Side_1_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Side_1_DRIVE_MODE_BITS        (3)
#define Side_1_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Side_1_DRIVE_MODE_BITS))

#define Side_1_DM_ALG_HIZ         (0x00u)
#define Side_1_DM_DIG_HIZ         (0x01u)
#define Side_1_DM_RES_UP          (0x02u)
#define Side_1_DM_RES_DWN         (0x03u)
#define Side_1_DM_OD_LO           (0x04u)
#define Side_1_DM_OD_HI           (0x05u)
#define Side_1_DM_STRONG          (0x06u)
#define Side_1_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Side_1_MASK               Side_1__MASK
#define Side_1_SHIFT              Side_1__SHIFT
#define Side_1_WIDTH              2u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Side_1_PS                     (* (reg32 *) Side_1__PS)
/* Port Configuration */
#define Side_1_PC                     (* (reg32 *) Side_1__PC)
/* Data Register */
#define Side_1_DR                     (* (reg32 *) Side_1__DR)
/* Input Buffer Disable Override */
#define Side_1_INP_DIS                (* (reg32 *) Side_1__PC2)


#if defined(Side_1__INTSTAT)  /* Interrupt Registers */

    #define Side_1_INTSTAT                (* (reg32 *) Side_1__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Side_1_DRIVE_MODE_SHIFT       (0x00u)
#define Side_1_DRIVE_MODE_MASK        (0x07u << Side_1_DRIVE_MODE_SHIFT)


#endif /* End Pins Side_1_H */


/* [] END OF FILE */
