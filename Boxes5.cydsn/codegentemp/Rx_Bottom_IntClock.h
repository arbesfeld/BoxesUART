/*******************************************************************************
* File Name: Rx_Bottom_IntClock.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_Rx_Bottom_IntClock_H)
#define CY_CLOCK_Rx_Bottom_IntClock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void Rx_Bottom_IntClock_Start(void) ;
void Rx_Bottom_IntClock_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void Rx_Bottom_IntClock_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void Rx_Bottom_IntClock_StandbyPower(uint8 state) ;
void Rx_Bottom_IntClock_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 Rx_Bottom_IntClock_GetDividerRegister(void) ;
void Rx_Bottom_IntClock_SetModeRegister(uint8 modeBitMask) ;
void Rx_Bottom_IntClock_ClearModeRegister(uint8 modeBitMask) ;
uint8 Rx_Bottom_IntClock_GetModeRegister(void) ;
void Rx_Bottom_IntClock_SetSourceRegister(uint8 clkSource) ;
uint8 Rx_Bottom_IntClock_GetSourceRegister(void) ;
#if defined(Rx_Bottom_IntClock__CFG3)
void Rx_Bottom_IntClock_SetPhaseRegister(uint8 clkPhase) ;
uint8 Rx_Bottom_IntClock_GetPhaseRegister(void) ;
#endif /* defined(Rx_Bottom_IntClock__CFG3) */

#define Rx_Bottom_IntClock_Enable()                       Rx_Bottom_IntClock_Start()
#define Rx_Bottom_IntClock_Disable()                      Rx_Bottom_IntClock_Stop()
#define Rx_Bottom_IntClock_SetDivider(clkDivider)         Rx_Bottom_IntClock_SetDividerRegister(clkDivider, 1u)
#define Rx_Bottom_IntClock_SetDividerValue(clkDivider)    Rx_Bottom_IntClock_SetDividerRegister((clkDivider) - 1u, 1u)
#define Rx_Bottom_IntClock_SetMode(clkMode)               Rx_Bottom_IntClock_SetModeRegister(clkMode)
#define Rx_Bottom_IntClock_SetSource(clkSource)           Rx_Bottom_IntClock_SetSourceRegister(clkSource)
#if defined(Rx_Bottom_IntClock__CFG3)
#define Rx_Bottom_IntClock_SetPhase(clkPhase)             Rx_Bottom_IntClock_SetPhaseRegister(clkPhase)
#define Rx_Bottom_IntClock_SetPhaseValue(clkPhase)        Rx_Bottom_IntClock_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(Rx_Bottom_IntClock__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define Rx_Bottom_IntClock_CLKEN              (* (reg8 *) Rx_Bottom_IntClock__PM_ACT_CFG)
#define Rx_Bottom_IntClock_CLKEN_PTR          ((reg8 *) Rx_Bottom_IntClock__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define Rx_Bottom_IntClock_CLKSTBY            (* (reg8 *) Rx_Bottom_IntClock__PM_STBY_CFG)
#define Rx_Bottom_IntClock_CLKSTBY_PTR        ((reg8 *) Rx_Bottom_IntClock__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define Rx_Bottom_IntClock_DIV_LSB            (* (reg8 *) Rx_Bottom_IntClock__CFG0)
#define Rx_Bottom_IntClock_DIV_LSB_PTR        ((reg8 *) Rx_Bottom_IntClock__CFG0)
#define Rx_Bottom_IntClock_DIV_PTR            ((reg16 *) Rx_Bottom_IntClock__CFG0)

/* Clock MSB divider configuration register. */
#define Rx_Bottom_IntClock_DIV_MSB            (* (reg8 *) Rx_Bottom_IntClock__CFG1)
#define Rx_Bottom_IntClock_DIV_MSB_PTR        ((reg8 *) Rx_Bottom_IntClock__CFG1)

/* Mode and source configuration register */
#define Rx_Bottom_IntClock_MOD_SRC            (* (reg8 *) Rx_Bottom_IntClock__CFG2)
#define Rx_Bottom_IntClock_MOD_SRC_PTR        ((reg8 *) Rx_Bottom_IntClock__CFG2)

#if defined(Rx_Bottom_IntClock__CFG3)
/* Analog clock phase configuration register */
#define Rx_Bottom_IntClock_PHASE              (* (reg8 *) Rx_Bottom_IntClock__CFG3)
#define Rx_Bottom_IntClock_PHASE_PTR          ((reg8 *) Rx_Bottom_IntClock__CFG3)
#endif /* defined(Rx_Bottom_IntClock__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define Rx_Bottom_IntClock_CLKEN_MASK         Rx_Bottom_IntClock__PM_ACT_MSK
#define Rx_Bottom_IntClock_CLKSTBY_MASK       Rx_Bottom_IntClock__PM_STBY_MSK

/* CFG2 field masks */
#define Rx_Bottom_IntClock_SRC_SEL_MSK        Rx_Bottom_IntClock__CFG2_SRC_SEL_MASK
#define Rx_Bottom_IntClock_MODE_MASK          (~(Rx_Bottom_IntClock_SRC_SEL_MSK))

#if defined(Rx_Bottom_IntClock__CFG3)
/* CFG3 phase mask */
#define Rx_Bottom_IntClock_PHASE_MASK         Rx_Bottom_IntClock__CFG3_PHASE_DLY_MASK
#endif /* defined(Rx_Bottom_IntClock__CFG3) */

#endif /* CY_CLOCK_Rx_Bottom_IntClock_H */


/* [] END OF FILE */
