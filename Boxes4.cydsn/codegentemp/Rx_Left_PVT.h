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

#if !defined(CY_SCB_PVT_Rx_Left_H)
#define CY_SCB_PVT_Rx_Left_H

#include "Rx_Left.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define Rx_Left_SetI2CExtClkInterruptMode(interruptMask) Rx_Left_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define Rx_Left_ClearI2CExtClkInterruptSource(interruptMask) Rx_Left_CLEAR_INTR_I2C_EC(interruptMask)
#define Rx_Left_GetI2CExtClkInterruptSource()                (Rx_Left_INTR_I2C_EC_REG)
#define Rx_Left_GetI2CExtClkInterruptMode()                  (Rx_Left_INTR_I2C_EC_MASK_REG)
#define Rx_Left_GetI2CExtClkInterruptSourceMasked()          (Rx_Left_INTR_I2C_EC_MASKED_REG)

#if (!Rx_Left_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define Rx_Left_SetSpiExtClkInterruptMode(interruptMask) \
                                                                Rx_Left_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define Rx_Left_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                Rx_Left_CLEAR_INTR_SPI_EC(interruptMask)
    #define Rx_Left_GetExtSpiClkInterruptSource()                 (Rx_Left_INTR_SPI_EC_REG)
    #define Rx_Left_GetExtSpiClkInterruptMode()                   (Rx_Left_INTR_SPI_EC_MASK_REG)
    #define Rx_Left_GetExtSpiClkInterruptSourceMasked()           (Rx_Left_INTR_SPI_EC_MASKED_REG)
#endif /* (!Rx_Left_CY_SCBIP_V1) */

#if(Rx_Left_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void Rx_Left_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (Rx_Left_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if !defined (CY_REMOVE_Rx_Left_CUSTOM_INTR_HANDLER)
    extern cyisraddress Rx_Left_customIntrHandler;
#endif /* !defined (CY_REMOVE_Rx_Left_CUSTOM_INTR_HANDLER) */

extern Rx_Left_BACKUP_STRUCT Rx_Left_backup;

#if(Rx_Left_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 Rx_Left_scbMode;
    extern uint8 Rx_Left_scbEnableWake;
    extern uint8 Rx_Left_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 Rx_Left_mode;
    extern uint8 Rx_Left_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * Rx_Left_rxBuffer;
    extern uint8   Rx_Left_rxDataBits;
    extern uint32  Rx_Left_rxBufferSize;

    extern volatile uint8 * Rx_Left_txBuffer;
    extern uint8   Rx_Left_txDataBits;
    extern uint32  Rx_Left_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 Rx_Left_numberOfAddr;
    extern uint8 Rx_Left_subAddrSize;
#endif /* (Rx_Left_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*        Conditional Macro
****************************************/

#if(Rx_Left_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define Rx_Left_SCB_MODE_I2C_RUNTM_CFG     (Rx_Left_SCB_MODE_I2C      == Rx_Left_scbMode)
    #define Rx_Left_SCB_MODE_SPI_RUNTM_CFG     (Rx_Left_SCB_MODE_SPI      == Rx_Left_scbMode)
    #define Rx_Left_SCB_MODE_UART_RUNTM_CFG    (Rx_Left_SCB_MODE_UART     == Rx_Left_scbMode)
    #define Rx_Left_SCB_MODE_EZI2C_RUNTM_CFG   (Rx_Left_SCB_MODE_EZI2C    == Rx_Left_scbMode)
    #define Rx_Left_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (Rx_Left_SCB_MODE_UNCONFIG == Rx_Left_scbMode)

    /* Defines wakeup enable */
    #define Rx_Left_SCB_WAKE_ENABLE_CHECK       (0u != Rx_Left_scbEnableWake)
#endif /* (Rx_Left_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!Rx_Left_CY_SCBIP_V1)
    #define Rx_Left_SCB_PINS_NUMBER    (7u)
#else
    #define Rx_Left_SCB_PINS_NUMBER    (2u)
#endif /* (!Rx_Left_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_Rx_Left_H) */


/* [] END OF FILE */
