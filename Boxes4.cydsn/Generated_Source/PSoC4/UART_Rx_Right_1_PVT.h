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

#if !defined(CY_SCB_PVT_UART_Rx_Right_1_H)
#define CY_SCB_PVT_UART_Rx_Right_1_H

#include "UART_Rx_Right_1.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define UART_Rx_Right_1_SetI2CExtClkInterruptMode(interruptMask) UART_Rx_Right_1_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define UART_Rx_Right_1_ClearI2CExtClkInterruptSource(interruptMask) UART_Rx_Right_1_CLEAR_INTR_I2C_EC(interruptMask)
#define UART_Rx_Right_1_GetI2CExtClkInterruptSource()                (UART_Rx_Right_1_INTR_I2C_EC_REG)
#define UART_Rx_Right_1_GetI2CExtClkInterruptMode()                  (UART_Rx_Right_1_INTR_I2C_EC_MASK_REG)
#define UART_Rx_Right_1_GetI2CExtClkInterruptSourceMasked()          (UART_Rx_Right_1_INTR_I2C_EC_MASKED_REG)

#if (!UART_Rx_Right_1_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define UART_Rx_Right_1_SetSpiExtClkInterruptMode(interruptMask) \
                                                                UART_Rx_Right_1_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define UART_Rx_Right_1_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                UART_Rx_Right_1_CLEAR_INTR_SPI_EC(interruptMask)
    #define UART_Rx_Right_1_GetExtSpiClkInterruptSource()                 (UART_Rx_Right_1_INTR_SPI_EC_REG)
    #define UART_Rx_Right_1_GetExtSpiClkInterruptMode()                   (UART_Rx_Right_1_INTR_SPI_EC_MASK_REG)
    #define UART_Rx_Right_1_GetExtSpiClkInterruptSourceMasked()           (UART_Rx_Right_1_INTR_SPI_EC_MASKED_REG)
#endif /* (!UART_Rx_Right_1_CY_SCBIP_V1) */

#if(UART_Rx_Right_1_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void UART_Rx_Right_1_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (UART_Rx_Right_1_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if !defined (CY_REMOVE_UART_Rx_Right_1_CUSTOM_INTR_HANDLER)
    extern cyisraddress UART_Rx_Right_1_customIntrHandler;
#endif /* !defined (CY_REMOVE_UART_Rx_Right_1_CUSTOM_INTR_HANDLER) */

extern UART_Rx_Right_1_BACKUP_STRUCT UART_Rx_Right_1_backup;

#if(UART_Rx_Right_1_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 UART_Rx_Right_1_scbMode;
    extern uint8 UART_Rx_Right_1_scbEnableWake;
    extern uint8 UART_Rx_Right_1_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 UART_Rx_Right_1_mode;
    extern uint8 UART_Rx_Right_1_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * UART_Rx_Right_1_rxBuffer;
    extern uint8   UART_Rx_Right_1_rxDataBits;
    extern uint32  UART_Rx_Right_1_rxBufferSize;

    extern volatile uint8 * UART_Rx_Right_1_txBuffer;
    extern uint8   UART_Rx_Right_1_txDataBits;
    extern uint32  UART_Rx_Right_1_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 UART_Rx_Right_1_numberOfAddr;
    extern uint8 UART_Rx_Right_1_subAddrSize;
#endif /* (UART_Rx_Right_1_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*        Conditional Macro
****************************************/

#if(UART_Rx_Right_1_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define UART_Rx_Right_1_SCB_MODE_I2C_RUNTM_CFG     (UART_Rx_Right_1_SCB_MODE_I2C      == UART_Rx_Right_1_scbMode)
    #define UART_Rx_Right_1_SCB_MODE_SPI_RUNTM_CFG     (UART_Rx_Right_1_SCB_MODE_SPI      == UART_Rx_Right_1_scbMode)
    #define UART_Rx_Right_1_SCB_MODE_UART_RUNTM_CFG    (UART_Rx_Right_1_SCB_MODE_UART     == UART_Rx_Right_1_scbMode)
    #define UART_Rx_Right_1_SCB_MODE_EZI2C_RUNTM_CFG   (UART_Rx_Right_1_SCB_MODE_EZI2C    == UART_Rx_Right_1_scbMode)
    #define UART_Rx_Right_1_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (UART_Rx_Right_1_SCB_MODE_UNCONFIG == UART_Rx_Right_1_scbMode)

    /* Defines wakeup enable */
    #define UART_Rx_Right_1_SCB_WAKE_ENABLE_CHECK       (0u != UART_Rx_Right_1_scbEnableWake)
#endif /* (UART_Rx_Right_1_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!UART_Rx_Right_1_CY_SCBIP_V1)
    #define UART_Rx_Right_1_SCB_PINS_NUMBER    (7u)
#else
    #define UART_Rx_Right_1_SCB_PINS_NUMBER    (2u)
#endif /* (!UART_Rx_Right_1_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_UART_Rx_Right_1_H) */


/* [] END OF FILE */
