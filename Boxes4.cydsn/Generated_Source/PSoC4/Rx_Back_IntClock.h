/*******************************************************************************
* File Name: Rx_Back_IntClock.h
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

#if !defined(CY_CLOCK_Rx_Back_IntClock_H)
#define CY_CLOCK_Rx_Back_IntClock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void Rx_Back_IntClock_StartEx(uint32 alignClkDiv);
#define Rx_Back_IntClock_Start() \
    Rx_Back_IntClock_StartEx(Rx_Back_IntClock__PA_DIV_ID)

#else

void Rx_Back_IntClock_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void Rx_Back_IntClock_Stop(void);

void Rx_Back_IntClock_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 Rx_Back_IntClock_GetDividerRegister(void);
uint8  Rx_Back_IntClock_GetFractionalDividerRegister(void);

#define Rx_Back_IntClock_Enable()                         Rx_Back_IntClock_Start()
#define Rx_Back_IntClock_Disable()                        Rx_Back_IntClock_Stop()
#define Rx_Back_IntClock_SetDividerRegister(clkDivider, reset)  \
    Rx_Back_IntClock_SetFractionalDividerRegister((clkDivider), 0u)
#define Rx_Back_IntClock_SetDivider(clkDivider)           Rx_Back_IntClock_SetDividerRegister((clkDivider), 1u)
#define Rx_Back_IntClock_SetDividerValue(clkDivider)      Rx_Back_IntClock_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define Rx_Back_IntClock_DIV_ID     Rx_Back_IntClock__DIV_ID

#define Rx_Back_IntClock_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define Rx_Back_IntClock_CTRL_REG   (*(reg32 *)Rx_Back_IntClock__CTRL_REGISTER)
#define Rx_Back_IntClock_DIV_REG    (*(reg32 *)Rx_Back_IntClock__DIV_REGISTER)

#define Rx_Back_IntClock_CMD_DIV_SHIFT          (0u)
#define Rx_Back_IntClock_CMD_PA_DIV_SHIFT       (8u)
#define Rx_Back_IntClock_CMD_DISABLE_SHIFT      (30u)
#define Rx_Back_IntClock_CMD_ENABLE_SHIFT       (31u)

#define Rx_Back_IntClock_CMD_DISABLE_MASK       ((uint32)((uint32)1u << Rx_Back_IntClock_CMD_DISABLE_SHIFT))
#define Rx_Back_IntClock_CMD_ENABLE_MASK        ((uint32)((uint32)1u << Rx_Back_IntClock_CMD_ENABLE_SHIFT))

#define Rx_Back_IntClock_DIV_FRAC_MASK  (0x000000F8u)
#define Rx_Back_IntClock_DIV_FRAC_SHIFT (3u)
#define Rx_Back_IntClock_DIV_INT_MASK   (0xFFFFFF00u)
#define Rx_Back_IntClock_DIV_INT_SHIFT  (8u)

#else 

#define Rx_Back_IntClock_DIV_REG        (*(reg32 *)Rx_Back_IntClock__REGISTER)
#define Rx_Back_IntClock_ENABLE_REG     Rx_Back_IntClock_DIV_REG
#define Rx_Back_IntClock_DIV_FRAC_MASK  Rx_Back_IntClock__FRAC_MASK
#define Rx_Back_IntClock_DIV_FRAC_SHIFT (16u)
#define Rx_Back_IntClock_DIV_INT_MASK   Rx_Back_IntClock__DIVIDER_MASK
#define Rx_Back_IntClock_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_Rx_Back_IntClock_H) */

/* [] END OF FILE */
