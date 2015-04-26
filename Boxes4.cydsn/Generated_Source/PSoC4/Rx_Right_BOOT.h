/*******************************************************************************
* File Name: Rx_Right_BOOT.h
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

#if !defined(CY_SCB_BOOT_Rx_Right_H)
#define CY_SCB_BOOT_Rx_Right_H

#include "Rx_Right_PVT.h"

#if (Rx_Right_SCB_MODE_I2C_INC)
    #include "Rx_Right_I2C.h"
#endif /* (Rx_Right_SCB_MODE_I2C_INC) */

#if (Rx_Right_SCB_MODE_EZI2C_INC)
    #include "Rx_Right_EZI2C.h"
#endif /* (Rx_Right_SCB_MODE_EZI2C_INC) */

#if (Rx_Right_SCB_MODE_SPI_INC || Rx_Right_SCB_MODE_UART_INC)
    #include "Rx_Right_SPI_UART.h"
#endif /* (Rx_Right_SCB_MODE_SPI_INC || Rx_Right_SCB_MODE_UART_INC) */


/***************************************
*        Function Prototypes
***************************************/

/* Bootloader communication interface enable */
#define Rx_Right_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Rx_Right) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

#if (Rx_Right_SCB_MODE_I2C_INC)

    #define Rx_Right_I2C_BTLDR_COMM_ENABLED     (Rx_Right_BTLDR_COMM_ENABLED && \
                                                            (Rx_Right_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             Rx_Right_I2C_SLAVE_CONST))

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (Rx_Right_I2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void Rx_Right_I2CCyBtldrCommStart(void);
    void Rx_Right_I2CCyBtldrCommStop (void);
    void Rx_Right_I2CCyBtldrCommReset(void);
    cystatus Rx_Right_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus Rx_Right_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Size of Read/Write buffers for I2C bootloader  */
    #define Rx_Right_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
    #define Rx_Right_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)
    #define Rx_Right_I2C_MIN_UINT16(a, b)           ( ((uint16)(a) < (uint16) (b)) ? \
                                                                    ((uint32) (a)) : ((uint32) (b)) )
    #define Rx_Right_WAIT_1_MS                      (1u)
#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (Rx_Right_I2C_BTLDR_COMM_ENABLED) */

#endif /* (Rx_Right_SCB_MODE_I2C_INC) */


#if (Rx_Right_SCB_MODE_EZI2C_INC)

    /* Provide EMPTY bootloader communication functions. EZI2C is NOT supported yet */
    #define Rx_Right_EZI2C_BTLDR_COMM_ENABLED   (Rx_Right_BTLDR_COMM_ENABLED && \
                                                         Rx_Right_SCB_MODE_UNCONFIG_CONST_CFG)

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (Rx_Right_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void Rx_Right_EzI2CCyBtldrCommStart(void);
    void Rx_Right_EzI2CCyBtldrCommStop (void);
    void Rx_Right_EzI2CCyBtldrCommReset(void);
    cystatus Rx_Right_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus Rx_Right_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (Rx_Right_EZI2C_BTLDR_COMM_ENABLED) */

#endif /* (Rx_Right_SCB_MODE_EZI2C_INC) */

#if (Rx_Right_SCB_MODE_SPI_INC || Rx_Right_SCB_MODE_UART_INC)
    /* Provide EMPTY bootloader communication functions. SPI and UART is NOT supported yet */
    #define Rx_Right_SPI_BTLDR_COMM_ENABLED     (Rx_Right_BTLDR_COMM_ENABLED && \
                                                        Rx_Right_SCB_MODE_UNCONFIG_CONST_CFG)

    #define Rx_Right_UART_BTLDR_COMM_ENABLED    (Rx_Right_BTLDR_COMM_ENABLED && \
                                                        Rx_Right_SCB_MODE_UNCONFIG_CONST_CFG)

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (Rx_Right_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void Rx_Right_SpiCyBtldrCommStart(void);
    void Rx_Right_SpiCyBtldrCommStop (void);
    void Rx_Right_SpiCyBtldrCommReset(void);
    cystatus Rx_Right_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus Rx_Right_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (Rx_Right_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (Rx_Right_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void Rx_Right_UartCyBtldrCommStart(void);
    void Rx_Right_UartCyBtldrCommStop (void);
    void Rx_Right_UartCyBtldrCommReset(void);
    cystatus Rx_Right_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus Rx_Right_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (Rx_Right_UART_BTLDR_COMM_ENABLED) */

#endif /* (Rx_Right_SCB_MODE_SPI_INC || Rx_Right_SCB_MODE_UART_INC) */

#if !defined (Rx_Right_I2C_BTLDR_COMM_ENABLED)
    #define Rx_Right_I2C_BTLDR_COMM_ENABLED     (0u)
#endif /* (Rx_Right_I2C_BTLDR_COMM_ENABLED) */

#if !defined (Rx_Right_EZI2C_BTLDR_COMM_ENABLED)
    #define Rx_Right_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (Rx_Right_EZI2C_BTLDR_COMM_ENABLED) */

#if !defined (Rx_Right_SPI_BTLDR_COMM_ENABLED)
    #define Rx_Right_SPI_BTLDR_COMM_ENABLED     (0u)
#endif /* (Rx_Right_SPI_BTLDR_COMM_ENABLED) */

#if !defined (Rx_Right_UART_BTLDR_COMM_ENABLED)
    #define Rx_Right_UART_BTLDR_COMM_ENABLED    (0u)
#endif /* (Rx_Right_UART_BTLDR_COMM_ENABLED) */

/* Bootloader enabled condition for each mode */
#define Rx_Right_BTLDR_COMM_MODE_ENABLED    (Rx_Right_I2C_BTLDR_COMM_ENABLED   || \
                                                     Rx_Right_EZI2C_BTLDR_COMM_ENABLED || \
                                                     Rx_Right_SPI_BTLDR_COMM_ENABLED   || \
                                                     Rx_Right_UART_BTLDR_COMM_ENABLED)

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (Rx_Right_BTLDR_COMM_ENABLED)
    #if (Rx_Right_BTLDR_COMM_MODE_ENABLED)
        /* Bootloader physical layer functions */
        void Rx_Right_CyBtldrCommStart(void);
        void Rx_Right_CyBtldrCommStop (void);
        void Rx_Right_CyBtldrCommReset(void);
        cystatus Rx_Right_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus Rx_Right_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (Rx_Right_BTLDR_COMM_MODE_ENABLED) */

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Rx_Right)
        #define CyBtldrCommStart    Rx_Right_CyBtldrCommStart
        #define CyBtldrCommStop     Rx_Right_CyBtldrCommStop
        #define CyBtldrCommReset    Rx_Right_CyBtldrCommReset
        #define CyBtldrCommWrite    Rx_Right_CyBtldrCommWrite
        #define CyBtldrCommRead     Rx_Right_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Rx_Right) */
#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (Rx_Right_BTLDR_COMM_ENABLED) */

#endif /* (CY_SCB_BOOT_Rx_Right_H) */

/* [] END OF FILE */
