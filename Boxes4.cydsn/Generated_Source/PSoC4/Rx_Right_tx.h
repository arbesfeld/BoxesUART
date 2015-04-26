/*******************************************************************************
* File Name: Rx_Right_tx.h  
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

#if !defined(CY_PINS_Rx_Right_tx_H) /* Pins Rx_Right_tx_H */
#define CY_PINS_Rx_Right_tx_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Rx_Right_tx_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Rx_Right_tx_Write(uint8 value) ;
void    Rx_Right_tx_SetDriveMode(uint8 mode) ;
uint8   Rx_Right_tx_ReadDataReg(void) ;
uint8   Rx_Right_tx_Read(void) ;
uint8   Rx_Right_tx_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Rx_Right_tx_DRIVE_MODE_BITS        (3)
#define Rx_Right_tx_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Rx_Right_tx_DRIVE_MODE_BITS))

#define Rx_Right_tx_DM_ALG_HIZ         (0x00u)
#define Rx_Right_tx_DM_DIG_HIZ         (0x01u)
#define Rx_Right_tx_DM_RES_UP          (0x02u)
#define Rx_Right_tx_DM_RES_DWN         (0x03u)
#define Rx_Right_tx_DM_OD_LO           (0x04u)
#define Rx_Right_tx_DM_OD_HI           (0x05u)
#define Rx_Right_tx_DM_STRONG          (0x06u)
#define Rx_Right_tx_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Rx_Right_tx_MASK               Rx_Right_tx__MASK
#define Rx_Right_tx_SHIFT              Rx_Right_tx__SHIFT
#define Rx_Right_tx_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Rx_Right_tx_PS                     (* (reg32 *) Rx_Right_tx__PS)
/* Port Configuration */
#define Rx_Right_tx_PC                     (* (reg32 *) Rx_Right_tx__PC)
/* Data Register */
#define Rx_Right_tx_DR                     (* (reg32 *) Rx_Right_tx__DR)
/* Input Buffer Disable Override */
#define Rx_Right_tx_INP_DIS                (* (reg32 *) Rx_Right_tx__PC2)


#if defined(Rx_Right_tx__INTSTAT)  /* Interrupt Registers */

    #define Rx_Right_tx_INTSTAT                (* (reg32 *) Rx_Right_tx__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Rx_Right_tx_DRIVE_MODE_SHIFT       (0x00u)
#define Rx_Right_tx_DRIVE_MODE_MASK        (0x07u << Rx_Right_tx_DRIVE_MODE_SHIFT)


#endif /* End Pins Rx_Right_tx_H */


/* [] END OF FILE */
