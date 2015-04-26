/*******************************************************************************
* File Name: Rx_Bottom_Pins.h  
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

#if !defined(CY_PINS_Rx_Bottom_Pins_H) /* Pins Rx_Bottom_Pins_H */
#define CY_PINS_Rx_Bottom_Pins_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Rx_Bottom_Pins_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Rx_Bottom_Pins__PORT == 15 && ((Rx_Bottom_Pins__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Rx_Bottom_Pins_Write(uint8 value) ;
void    Rx_Bottom_Pins_SetDriveMode(uint8 mode) ;
uint8   Rx_Bottom_Pins_ReadDataReg(void) ;
uint8   Rx_Bottom_Pins_Read(void) ;
uint8   Rx_Bottom_Pins_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Rx_Bottom_Pins_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Rx_Bottom_Pins_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Rx_Bottom_Pins_DM_RES_UP          PIN_DM_RES_UP
#define Rx_Bottom_Pins_DM_RES_DWN         PIN_DM_RES_DWN
#define Rx_Bottom_Pins_DM_OD_LO           PIN_DM_OD_LO
#define Rx_Bottom_Pins_DM_OD_HI           PIN_DM_OD_HI
#define Rx_Bottom_Pins_DM_STRONG          PIN_DM_STRONG
#define Rx_Bottom_Pins_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Rx_Bottom_Pins_MASK               Rx_Bottom_Pins__MASK
#define Rx_Bottom_Pins_SHIFT              Rx_Bottom_Pins__SHIFT
#define Rx_Bottom_Pins_WIDTH              4u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Rx_Bottom_Pins_PS                     (* (reg8 *) Rx_Bottom_Pins__PS)
/* Data Register */
#define Rx_Bottom_Pins_DR                     (* (reg8 *) Rx_Bottom_Pins__DR)
/* Port Number */
#define Rx_Bottom_Pins_PRT_NUM                (* (reg8 *) Rx_Bottom_Pins__PRT) 
/* Connect to Analog Globals */                                                  
#define Rx_Bottom_Pins_AG                     (* (reg8 *) Rx_Bottom_Pins__AG)                       
/* Analog MUX bux enable */
#define Rx_Bottom_Pins_AMUX                   (* (reg8 *) Rx_Bottom_Pins__AMUX) 
/* Bidirectional Enable */                                                        
#define Rx_Bottom_Pins_BIE                    (* (reg8 *) Rx_Bottom_Pins__BIE)
/* Bit-mask for Aliased Register Access */
#define Rx_Bottom_Pins_BIT_MASK               (* (reg8 *) Rx_Bottom_Pins__BIT_MASK)
/* Bypass Enable */
#define Rx_Bottom_Pins_BYP                    (* (reg8 *) Rx_Bottom_Pins__BYP)
/* Port wide control signals */                                                   
#define Rx_Bottom_Pins_CTL                    (* (reg8 *) Rx_Bottom_Pins__CTL)
/* Drive Modes */
#define Rx_Bottom_Pins_DM0                    (* (reg8 *) Rx_Bottom_Pins__DM0) 
#define Rx_Bottom_Pins_DM1                    (* (reg8 *) Rx_Bottom_Pins__DM1)
#define Rx_Bottom_Pins_DM2                    (* (reg8 *) Rx_Bottom_Pins__DM2) 
/* Input Buffer Disable Override */
#define Rx_Bottom_Pins_INP_DIS                (* (reg8 *) Rx_Bottom_Pins__INP_DIS)
/* LCD Common or Segment Drive */
#define Rx_Bottom_Pins_LCD_COM_SEG            (* (reg8 *) Rx_Bottom_Pins__LCD_COM_SEG)
/* Enable Segment LCD */
#define Rx_Bottom_Pins_LCD_EN                 (* (reg8 *) Rx_Bottom_Pins__LCD_EN)
/* Slew Rate Control */
#define Rx_Bottom_Pins_SLW                    (* (reg8 *) Rx_Bottom_Pins__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Rx_Bottom_Pins_PRTDSI__CAPS_SEL       (* (reg8 *) Rx_Bottom_Pins__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Rx_Bottom_Pins_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Rx_Bottom_Pins__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Rx_Bottom_Pins_PRTDSI__OE_SEL0        (* (reg8 *) Rx_Bottom_Pins__PRTDSI__OE_SEL0) 
#define Rx_Bottom_Pins_PRTDSI__OE_SEL1        (* (reg8 *) Rx_Bottom_Pins__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Rx_Bottom_Pins_PRTDSI__OUT_SEL0       (* (reg8 *) Rx_Bottom_Pins__PRTDSI__OUT_SEL0) 
#define Rx_Bottom_Pins_PRTDSI__OUT_SEL1       (* (reg8 *) Rx_Bottom_Pins__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Rx_Bottom_Pins_PRTDSI__SYNC_OUT       (* (reg8 *) Rx_Bottom_Pins__PRTDSI__SYNC_OUT) 


#if defined(Rx_Bottom_Pins__INTSTAT)  /* Interrupt Registers */

    #define Rx_Bottom_Pins_INTSTAT                (* (reg8 *) Rx_Bottom_Pins__INTSTAT)
    #define Rx_Bottom_Pins_SNAP                   (* (reg8 *) Rx_Bottom_Pins__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Rx_Bottom_Pins_H */


/* [] END OF FILE */
