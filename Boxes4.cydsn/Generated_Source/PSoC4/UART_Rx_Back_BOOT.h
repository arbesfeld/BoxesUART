/*******************************************************************************
* File Name: UART_Rx_Back_BOOT.h
* Version 2.0
*
* Description:
*  This file provides constants and parameter values for the bootloader
*  communication interface of SCB component.
*
* Note:
*
********************************************************************************
* Copyright 2014, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_BOOT_UART_Rx_Back_H)
#define CY_SCB_BOOT_UART_Rx_Back_H

#include "UART_Rx_Back_PVT.h"

#if (UART_Rx_Back_SCB_MODE_I2C_INC)
    #include "UART_Rx_Back_I2C.h"
#endif /* (UART_Rx_Back_SCB_MODE_I2C_INC) */

#if (UART_Rx_Back_SCB_MODE_EZI2C_INC)
    #include "UART_Rx_Back_EZI2C.h"
#endif /* (UART_Rx_Back_SCB_MODE_EZI2C_INC) */

#if (UART_Rx_Back_SCB_MODE_SPI_INC || UART_Rx_Back_SCB_MODE_UART_INC)
    #include "UART_Rx_Back_SPI_UART.h"
#endif /* (UART_Rx_Back_SCB_MODE_SPI_INC || UART_Rx_Back_SCB_MODE_UART_INC) */


/***************************************
*        Function Prototypes
***************************************/

/* Bootloader communication interface enable */
#define UART_Rx_Back_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART_Rx_Back) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

#if (UART_Rx_Back_SCB_MODE_I2C_INC)

    #define UART_Rx_Back_I2C_BTLDR_COMM_ENABLED     (UART_Rx_Back_BTLDR_COMM_ENABLED && \
                                                            (UART_Rx_Back_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             UART_Rx_Back_I2C_SLAVE_CONST))

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_Rx_Back_I2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void UART_Rx_Back_I2CCyBtldrCommStart(void);
    void UART_Rx_Back_I2CCyBtldrCommStop (void);
    void UART_Rx_Back_I2CCyBtldrCommReset(void);
    cystatus UART_Rx_Back_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus UART_Rx_Back_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Size of Read/Write buffers for I2C bootloader  */
    #define UART_Rx_Back_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
    #define UART_Rx_Back_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)
    #define UART_Rx_Back_I2C_MIN_UINT16(a, b)           ( ((uint16)(a) < (uint16) (b)) ? \
                                                                    ((uint32) (a)) : ((uint32) (b)) )
    #define UART_Rx_Back_WAIT_1_MS                      (1u)
#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_Rx_Back_I2C_BTLDR_COMM_ENABLED) */

#endif /* (UART_Rx_Back_SCB_MODE_I2C_INC) */


#if (UART_Rx_Back_SCB_MODE_EZI2C_INC)

    /* Provide EMPTY bootloader communication functions. EZI2C is NOT supported yet */
    #define UART_Rx_Back_EZI2C_BTLDR_COMM_ENABLED   (UART_Rx_Back_BTLDR_COMM_ENABLED && \
                                                         UART_Rx_Back_SCB_MODE_UNCONFIG_CONST_CFG)

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_Rx_Back_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void UART_Rx_Back_EzI2CCyBtldrCommStart(void);
    void UART_Rx_Back_EzI2CCyBtldrCommStop (void);
    void UART_Rx_Back_EzI2CCyBtldrCommReset(void);
    cystatus UART_Rx_Back_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus UART_Rx_Back_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_Rx_Back_EZI2C_BTLDR_COMM_ENABLED) */

#endif /* (UART_Rx_Back_SCB_MODE_EZI2C_INC) */

#if (UART_Rx_Back_SCB_MODE_SPI_INC || UART_Rx_Back_SCB_MODE_UART_INC)
    /* Provide EMPTY bootloader communication functions. SPI and UART is NOT supported yet */
    #define UART_Rx_Back_SPI_BTLDR_COMM_ENABLED     (UART_Rx_Back_BTLDR_COMM_ENABLED && \
                                                        UART_Rx_Back_SCB_MODE_UNCONFIG_CONST_CFG)

    #define UART_Rx_Back_UART_BTLDR_COMM_ENABLED    (UART_Rx_Back_BTLDR_COMM_ENABLED && \
                                                        UART_Rx_Back_SCB_MODE_UNCONFIG_CONST_CFG)

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_Rx_Back_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void UART_Rx_Back_SpiCyBtldrCommStart(void);
    void UART_Rx_Back_SpiCyBtldrCommStop (void);
    void UART_Rx_Back_SpiCyBtldrCommReset(void);
    cystatus UART_Rx_Back_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus UART_Rx_Back_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_Rx_Back_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_Rx_Back_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void UART_Rx_Back_UartCyBtldrCommStart(void);
    void UART_Rx_Back_UartCyBtldrCommStop (void);
    void UART_Rx_Back_UartCyBtldrCommReset(void);
    cystatus UART_Rx_Back_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus UART_Rx_Back_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_Rx_Back_UART_BTLDR_COMM_ENABLED) */

#endif /* (UART_Rx_Back_SCB_MODE_SPI_INC || UART_Rx_Back_SCB_MODE_UART_INC) */

#if !defined (UART_Rx_Back_I2C_BTLDR_COMM_ENABLED)
    #define UART_Rx_Back_I2C_BTLDR_COMM_ENABLED     (0u)
#endif /* (UART_Rx_Back_I2C_BTLDR_COMM_ENABLED) */

#if !defined (UART_Rx_Back_EZI2C_BTLDR_COMM_ENABLED)
    #define UART_Rx_Back_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (UART_Rx_Back_EZI2C_BTLDR_COMM_ENABLED) */

#if !defined (UART_Rx_Back_SPI_BTLDR_COMM_ENABLED)
    #define UART_Rx_Back_SPI_BTLDR_COMM_ENABLED     (0u)
#endif /* (UART_Rx_Back_SPI_BTLDR_COMM_ENABLED) */

#if !defined (UART_Rx_Back_UART_BTLDR_COMM_ENABLED)
    #define UART_Rx_Back_UART_BTLDR_COMM_ENABLED    (0u)
#endif /* (UART_Rx_Back_UART_BTLDR_COMM_ENABLED) */

/* Bootloader enabled condition for each mode */
#define UART_Rx_Back_BTLDR_COMM_MODE_ENABLED    (UART_Rx_Back_I2C_BTLDR_COMM_ENABLED   || \
                                                     UART_Rx_Back_EZI2C_BTLDR_COMM_ENABLED || \
                                                     UART_Rx_Back_SPI_BTLDR_COMM_ENABLED   || \
                                                     UART_Rx_Back_UART_BTLDR_COMM_ENABLED)

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_Rx_Back_BTLDR_COMM_ENABLED)
    #if (UART_Rx_Back_BTLDR_COMM_MODE_ENABLED)
        /* Bootloader physical layer functions */
        void UART_Rx_Back_CyBtldrCommStart(void);
        void UART_Rx_Back_CyBtldrCommStop (void);
        void UART_Rx_Back_CyBtldrCommReset(void);
        cystatus UART_Rx_Back_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus UART_Rx_Back_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (UART_Rx_Back_BTLDR_COMM_MODE_ENABLED) */

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART_Rx_Back)
        #define CyBtldrCommStart    UART_Rx_Back_CyBtldrCommStart
        #define CyBtldrCommStop     UART_Rx_Back_CyBtldrCommStop
        #define CyBtldrCommReset    UART_Rx_Back_CyBtldrCommReset
        #define CyBtldrCommWrite    UART_Rx_Back_CyBtldrCommWrite
        #define CyBtldrCommRead     UART_Rx_Back_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART_Rx_Back) */
#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_Rx_Back_BTLDR_COMM_ENABLED) */

#endif /* (CY_SCB_BOOT_UART_Rx_Back_H) */

/* [] END OF FILE */
