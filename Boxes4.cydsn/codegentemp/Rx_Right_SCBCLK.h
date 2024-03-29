/*******************************************************************************
* File Name: Rx_Right_SCBCLK.h
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

#if !defined(CY_CLOCK_Rx_Right_SCBCLK_H)
#define CY_CLOCK_Rx_Right_SCBCLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void Rx_Right_SCBCLK_StartEx(uint32 alignClkDiv);
#define Rx_Right_SCBCLK_Start() \
    Rx_Right_SCBCLK_StartEx(Rx_Right_SCBCLK__PA_DIV_ID)

#else

void Rx_Right_SCBCLK_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void Rx_Right_SCBCLK_Stop(void);

void Rx_Right_SCBCLK_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 Rx_Right_SCBCLK_GetDividerRegister(void);
uint8  Rx_Right_SCBCLK_GetFractionalDividerRegister(void);

#define Rx_Right_SCBCLK_Enable()                         Rx_Right_SCBCLK_Start()
#define Rx_Right_SCBCLK_Disable()                        Rx_Right_SCBCLK_Stop()
#define Rx_Right_SCBCLK_SetDividerRegister(clkDivider, reset)  \
    Rx_Right_SCBCLK_SetFractionalDividerRegister((clkDivider), 0u)
#define Rx_Right_SCBCLK_SetDivider(clkDivider)           Rx_Right_SCBCLK_SetDividerRegister((clkDivider), 1u)
#define Rx_Right_SCBCLK_SetDividerValue(clkDivider)      Rx_Right_SCBCLK_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define Rx_Right_SCBCLK_DIV_ID     Rx_Right_SCBCLK__DIV_ID

#define Rx_Right_SCBCLK_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define Rx_Right_SCBCLK_CTRL_REG   (*(reg32 *)Rx_Right_SCBCLK__CTRL_REGISTER)
#define Rx_Right_SCBCLK_DIV_REG    (*(reg32 *)Rx_Right_SCBCLK__DIV_REGISTER)

#define Rx_Right_SCBCLK_CMD_DIV_SHIFT          (0u)
#define Rx_Right_SCBCLK_CMD_PA_DIV_SHIFT       (8u)
#define Rx_Right_SCBCLK_CMD_DISABLE_SHIFT      (30u)
#define Rx_Right_SCBCLK_CMD_ENABLE_SHIFT       (31u)

#define Rx_Right_SCBCLK_CMD_DISABLE_MASK       ((uint32)((uint32)1u << Rx_Right_SCBCLK_CMD_DISABLE_SHIFT))
#define Rx_Right_SCBCLK_CMD_ENABLE_MASK        ((uint32)((uint32)1u << Rx_Right_SCBCLK_CMD_ENABLE_SHIFT))

#define Rx_Right_SCBCLK_DIV_FRAC_MASK  (0x000000F8u)
#define Rx_Right_SCBCLK_DIV_FRAC_SHIFT (3u)
#define Rx_Right_SCBCLK_DIV_INT_MASK   (0xFFFFFF00u)
#define Rx_Right_SCBCLK_DIV_INT_SHIFT  (8u)

#else 

#define Rx_Right_SCBCLK_DIV_REG        (*(reg32 *)Rx_Right_SCBCLK__REGISTER)
#define Rx_Right_SCBCLK_ENABLE_REG     Rx_Right_SCBCLK_DIV_REG
#define Rx_Right_SCBCLK_DIV_FRAC_MASK  Rx_Right_SCBCLK__FRAC_MASK
#define Rx_Right_SCBCLK_DIV_FRAC_SHIFT (16u)
#define Rx_Right_SCBCLK_DIV_INT_MASK   Rx_Right_SCBCLK__DIVIDER_MASK
#define Rx_Right_SCBCLK_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_Rx_Right_SCBCLK_H) */

/* [] END OF FILE */
