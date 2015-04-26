/*******************************************************************************
* File Name: StartupLED.h  
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

#if !defined(CY_PINS_StartupLED_H) /* Pins StartupLED_H */
#define CY_PINS_StartupLED_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "StartupLED_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 StartupLED__PORT == 15 && ((StartupLED__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    StartupLED_Write(uint8 value) ;
void    StartupLED_SetDriveMode(uint8 mode) ;
uint8   StartupLED_ReadDataReg(void) ;
uint8   StartupLED_Read(void) ;
uint8   StartupLED_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define StartupLED_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define StartupLED_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define StartupLED_DM_RES_UP          PIN_DM_RES_UP
#define StartupLED_DM_RES_DWN         PIN_DM_RES_DWN
#define StartupLED_DM_OD_LO           PIN_DM_OD_LO
#define StartupLED_DM_OD_HI           PIN_DM_OD_HI
#define StartupLED_DM_STRONG          PIN_DM_STRONG
#define StartupLED_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define StartupLED_MASK               StartupLED__MASK
#define StartupLED_SHIFT              StartupLED__SHIFT
#define StartupLED_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define StartupLED_PS                     (* (reg8 *) StartupLED__PS)
/* Data Register */
#define StartupLED_DR                     (* (reg8 *) StartupLED__DR)
/* Port Number */
#define StartupLED_PRT_NUM                (* (reg8 *) StartupLED__PRT) 
/* Connect to Analog Globals */                                                  
#define StartupLED_AG                     (* (reg8 *) StartupLED__AG)                       
/* Analog MUX bux enable */
#define StartupLED_AMUX                   (* (reg8 *) StartupLED__AMUX) 
/* Bidirectional Enable */                                                        
#define StartupLED_BIE                    (* (reg8 *) StartupLED__BIE)
/* Bit-mask for Aliased Register Access */
#define StartupLED_BIT_MASK               (* (reg8 *) StartupLED__BIT_MASK)
/* Bypass Enable */
#define StartupLED_BYP                    (* (reg8 *) StartupLED__BYP)
/* Port wide control signals */                                                   
#define StartupLED_CTL                    (* (reg8 *) StartupLED__CTL)
/* Drive Modes */
#define StartupLED_DM0                    (* (reg8 *) StartupLED__DM0) 
#define StartupLED_DM1                    (* (reg8 *) StartupLED__DM1)
#define StartupLED_DM2                    (* (reg8 *) StartupLED__DM2) 
/* Input Buffer Disable Override */
#define StartupLED_INP_DIS                (* (reg8 *) StartupLED__INP_DIS)
/* LCD Common or Segment Drive */
#define StartupLED_LCD_COM_SEG            (* (reg8 *) StartupLED__LCD_COM_SEG)
/* Enable Segment LCD */
#define StartupLED_LCD_EN                 (* (reg8 *) StartupLED__LCD_EN)
/* Slew Rate Control */
#define StartupLED_SLW                    (* (reg8 *) StartupLED__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define StartupLED_PRTDSI__CAPS_SEL       (* (reg8 *) StartupLED__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define StartupLED_PRTDSI__DBL_SYNC_IN    (* (reg8 *) StartupLED__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define StartupLED_PRTDSI__OE_SEL0        (* (reg8 *) StartupLED__PRTDSI__OE_SEL0) 
#define StartupLED_PRTDSI__OE_SEL1        (* (reg8 *) StartupLED__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define StartupLED_PRTDSI__OUT_SEL0       (* (reg8 *) StartupLED__PRTDSI__OUT_SEL0) 
#define StartupLED_PRTDSI__OUT_SEL1       (* (reg8 *) StartupLED__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define StartupLED_PRTDSI__SYNC_OUT       (* (reg8 *) StartupLED__PRTDSI__SYNC_OUT) 


#if defined(StartupLED__INTSTAT)  /* Interrupt Registers */

    #define StartupLED_INTSTAT                (* (reg8 *) StartupLED__INTSTAT)
    #define StartupLED_SNAP                   (* (reg8 *) StartupLED__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_StartupLED_H */


/* [] END OF FILE */
