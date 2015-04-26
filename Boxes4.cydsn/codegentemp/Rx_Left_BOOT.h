/*******************************************************************************
* File Name: Rx_Left_BOOT.h
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

#if !defined(CY_SCB_BOOT_Rx_Left_H)
#define CY_SCB_BOOT_Rx_Left_H

#include "Rx_Left_PVT.h"

#if (Rx_Left_SCB_MODE_I2C_INC)
    #include "Rx_Left_I2C.h"
#endif /* (Rx_Left_SCB_MODE_I2C_INC) */

#if (Rx_Left_SCB_MODE_EZI2C_INC)
    #include "Rx_Left_EZI2C.h"
#endif /* (Rx_Left_SCB_MODE_EZI2C_INC) */

#if (Rx_Left_SCB_MODE_SPI_INC || Rx_Left_SCB_MODE_UART_INC)
    #include "Rx_Left_SPI_UART.h"
#endif /* (Rx_Left_SCB_MODE_SPI_INC || Rx_Left_SCB_MODE_UART_INC) */


/***************************************
*        Function Prototypes
***************************************/

/* Bootloader communication interface enable */
#define Rx_Left_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Rx_Left) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

#if (Rx_Left_SCB_MODE_I2C_INC)

    #define Rx_Left_I2C_BTLDR_COMM_ENABLED     (Rx_Left_BTLDR_COMM_ENABLED && \
                                                            (Rx_Left_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             Rx_Left_I2C_SLAVE_CONST))

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (Rx_Left_I2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void Rx_Left_I2CCyBtldrCommStart(void);
    void Rx_Left_I2CCyBtldrCommStop (void);
    void Rx_Left_I2CCyBtldrCommReset(void);
    cystatus Rx_Left_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus Rx_Left_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Size of Read/Write buffers for I2C bootloader  */
    #define Rx_Left_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
    #define Rx_Left_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)
    #define Rx_Left_I2C_MIN_UINT16(a, b)           ( ((uint16)(a) < (uint16) (b)) ? \
                                                                    ((uint32) (a)) : ((uint32) (b)) )
    #define Rx_Left_WAIT_1_MS                      (1u)
#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (Rx_Left_I2C_BTLDR_COMM_ENABLED) */

#endif /* (Rx_Left_SCB_MODE_I2C_INC) */


#if (Rx_Left_SCB_MODE_EZI2C_INC)

    /* Provide EMPTY bootloader communication functions. EZI2C is NOT supported yet */
    #define Rx_Left_EZI2C_BTLDR_COMM_ENABLED   (Rx_Left_BTLDR_COMM_ENABLED && \
                                                         Rx_Left_SCB_MODE_UNCONFIG_CONST_CFG)

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (Rx_Left_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void Rx_Left_EzI2CCyBtldrCommStart(void);
    void Rx_Left_EzI2CCyBtldrCommStop (void);
    void Rx_Left_EzI2CCyBtldrCommReset(void);
    cystatus Rx_Left_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus Rx_Left_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (Rx_Left_EZI2C_BTLDR_COMM_ENABLED) */

#endif /* (Rx_Left_SCB_MODE_EZI2C_INC) */

#if (Rx_Left_SCB_MODE_SPI_INC || Rx_Left_SCB_MODE_UART_INC)
    /* Provide EMPTY bootloader communication functions. SPI and UART is NOT supported yet */
    #define Rx_Left_SPI_BTLDR_COMM_ENABLED     (Rx_Left_BTLDR_COMM_ENABLED && \
                                                        Rx_Left_SCB_MODE_UNCONFIG_CONST_CFG)

    #define Rx_Left_UART_BTLDR_COMM_ENABLED    (Rx_Left_BTLDR_COMM_ENABLED && \
                                                        Rx_Left_SCB_MODE_UNCONFIG_CONST_CFG)

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (Rx_Left_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void Rx_Left_SpiCyBtldrCommStart(void);
    void Rx_Left_SpiCyBtldrCommStop (void);
    void Rx_Left_SpiCyBtldrCommReset(void);
    cystatus Rx_Left_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus Rx_Left_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (Rx_Left_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (Rx_Left_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void Rx_Left_UartCyBtldrCommStart(void);
    void Rx_Left_UartCyBtldrCommStop (void);
    void Rx_Left_UartCyBtldrCommReset(void);
    cystatus Rx_Left_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus Rx_Left_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (Rx_Left_UART_BTLDR_COMM_ENABLED) */

#endif /* (Rx_Left_SCB_MODE_SPI_INC || Rx_Left_SCB_MODE_UART_INC) */

#if !defined (Rx_Left_I2C_BTLDR_COMM_ENABLED)
    #define Rx_Left_I2C_BTLDR_COMM_ENABLED     (0u)
#endif /* (Rx_Left_I2C_BTLDR_COMM_ENABLED) */

#if !defined (Rx_Left_EZI2C_BTLDR_COMM_ENABLED)
    #define Rx_Left_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (Rx_Left_EZI2C_BTLDR_COMM_ENABLED) */

#if !defined (Rx_Left_SPI_BTLDR_COMM_ENABLED)
    #define Rx_Left_SPI_BTLDR_COMM_ENABLED     (0u)
#endif /* (Rx_Left_SPI_BTLDR_COMM_ENABLED) */

#if !defined (Rx_Left_UART_BTLDR_COMM_ENABLED)
    #define Rx_Left_UART_BTLDR_COMM_ENABLED    (0u)
#endif /* (Rx_Left_UART_BTLDR_COMM_ENABLED) */

/* Bootloader enabled condition for each mode */
#define Rx_Left_BTLDR_COMM_MODE_ENABLED    (Rx_Left_I2C_BTLDR_COMM_ENABLED   || \
                                                     Rx_Left_EZI2C_BTLDR_COMM_ENABLED || \
                                                     Rx_Left_SPI_BTLDR_COMM_ENABLED   || \
                                                     Rx_Left_UART_BTLDR_COMM_ENABLED)

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (Rx_Left_BTLDR_COMM_ENABLED)
    #if (Rx_Left_BTLDR_COMM_MODE_ENABLED)
        /* Bootloader physical layer functions */
        void Rx_Left_CyBtldrCommStart(void);
        void Rx_Left_CyBtldrCommStop (void);
        void Rx_Left_CyBtldrCommReset(void);
        cystatus Rx_Left_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus Rx_Left_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (Rx_Left_BTLDR_COMM_MODE_ENABLED) */

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Rx_Left)
        #define CyBtldrCommStart    Rx_Left_CyBtldrCommStart
        #define CyBtldrCommStop     Rx_Left_CyBtldrCommStop
        #define CyBtldrCommReset    Rx_Left_CyBtldrCommReset
        #define CyBtldrCommWrite    Rx_Left_CyBtldrCommWrite
        #define CyBtldrCommRead     Rx_Left_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Rx_Left) */
#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (Rx_Left_BTLDR_COMM_ENABLED) */

#endif /* (CY_SCB_BOOT_Rx_Left_H) */

/* [] END OF FILE */
