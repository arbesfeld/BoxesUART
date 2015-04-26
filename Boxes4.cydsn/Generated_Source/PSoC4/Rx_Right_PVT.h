/*******************************************************************************
* File Name: .h
* Version 2.0
*
* Description:
*  This private file provides constants and parameter values for the
*  SCB Component.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PVT_Rx_Right_H)
#define CY_SCB_PVT_Rx_Right_H

#include "Rx_Right.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define Rx_Right_SetI2CExtClkInterruptMode(interruptMask) Rx_Right_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define Rx_Right_ClearI2CExtClkInterruptSource(interruptMask) Rx_Right_CLEAR_INTR_I2C_EC(interruptMask)
#define Rx_Right_GetI2CExtClkInterruptSource()                (Rx_Right_INTR_I2C_EC_REG)
#define Rx_Right_GetI2CExtClkInterruptMode()                  (Rx_Right_INTR_I2C_EC_MASK_REG)
#define Rx_Right_GetI2CExtClkInterruptSourceMasked()          (Rx_Right_INTR_I2C_EC_MASKED_REG)

#if (!Rx_Right_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define Rx_Right_SetSpiExtClkInterruptMode(interruptMask) \
                                                                Rx_Right_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define Rx_Right_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                Rx_Right_CLEAR_INTR_SPI_EC(interruptMask)
    #define Rx_Right_GetExtSpiClkInterruptSource()                 (Rx_Right_INTR_SPI_EC_REG)
    #define Rx_Right_GetExtSpiClkInterruptMode()                   (Rx_Right_INTR_SPI_EC_MASK_REG)
    #define Rx_Right_GetExtSpiClkInterruptSourceMasked()           (Rx_Right_INTR_SPI_EC_MASKED_REG)
#endif /* (!Rx_Right_CY_SCBIP_V1) */

#if(Rx_Right_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void Rx_Right_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (Rx_Right_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if !defined (CY_REMOVE_Rx_Right_CUSTOM_INTR_HANDLER)
    extern cyisraddress Rx_Right_customIntrHandler;
#endif /* !defined (CY_REMOVE_Rx_Right_CUSTOM_INTR_HANDLER) */

extern Rx_Right_BACKUP_STRUCT Rx_Right_backup;

#if(Rx_Right_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 Rx_Right_scbMode;
    extern uint8 Rx_Right_scbEnableWake;
    extern uint8 Rx_Right_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 Rx_Right_mode;
    extern uint8 Rx_Right_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * Rx_Right_rxBuffer;
    extern uint8   Rx_Right_rxDataBits;
    extern uint32  Rx_Right_rxBufferSize;

    extern volatile uint8 * Rx_Right_txBuffer;
    extern uint8   Rx_Right_txDataBits;
    extern uint32  Rx_Right_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 Rx_Right_numberOfAddr;
    extern uint8 Rx_Right_subAddrSize;
#endif /* (Rx_Right_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*        Conditional Macro
****************************************/

#if(Rx_Right_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define Rx_Right_SCB_MODE_I2C_RUNTM_CFG     (Rx_Right_SCB_MODE_I2C      == Rx_Right_scbMode)
    #define Rx_Right_SCB_MODE_SPI_RUNTM_CFG     (Rx_Right_SCB_MODE_SPI      == Rx_Right_scbMode)
    #define Rx_Right_SCB_MODE_UART_RUNTM_CFG    (Rx_Right_SCB_MODE_UART     == Rx_Right_scbMode)
    #define Rx_Right_SCB_MODE_EZI2C_RUNTM_CFG   (Rx_Right_SCB_MODE_EZI2C    == Rx_Right_scbMode)
    #define Rx_Right_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (Rx_Right_SCB_MODE_UNCONFIG == Rx_Right_scbMode)

    /* Defines wakeup enable */
    #define Rx_Right_SCB_WAKE_ENABLE_CHECK       (0u != Rx_Right_scbEnableWake)
#endif /* (Rx_Right_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!Rx_Right_CY_SCBIP_V1)
    #define Rx_Right_SCB_PINS_NUMBER    (7u)
#else
    #define Rx_Right_SCB_PINS_NUMBER    (2u)
#endif /* (!Rx_Right_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_Rx_Right_H) */


/* [] END OF FILE */
