/*******************************************************************************
* File Name: Rx_Left_PINS.h
* Version 2.0
*
* Description:
*  This file provides constants and parameter values for the pin components
*  buried into SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PINS_Rx_Left_H)
#define CY_SCB_PINS_Rx_Left_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* Unconfigured pins */
#define Rx_Left_REMOVE_MOSI_SCL_RX_WAKE_PIN    (1u)
#define Rx_Left_REMOVE_MOSI_SCL_RX_PIN         (1u)
#define Rx_Left_REMOVE_MISO_SDA_TX_PIN         (1u)
#define Rx_Left_REMOVE_SCLK_PIN                (1u)
#define Rx_Left_REMOVE_SS0_PIN                 (1u)
#define Rx_Left_REMOVE_SS1_PIN                 (1u)
#define Rx_Left_REMOVE_SS2_PIN                 (1u)
#define Rx_Left_REMOVE_SS3_PIN                 (1u)

/* Mode defined pins */
#define Rx_Left_REMOVE_I2C_PINS                (1u)
#define Rx_Left_REMOVE_SPI_MASTER_PINS         (1u)
#define Rx_Left_REMOVE_SPI_SLAVE_PINS          (1u)
#define Rx_Left_REMOVE_SPI_MASTER_SS0_PIN      (1u)
#define Rx_Left_REMOVE_SPI_MASTER_SS1_PIN      (1u)
#define Rx_Left_REMOVE_SPI_MASTER_SS2_PIN      (1u)
#define Rx_Left_REMOVE_SPI_MASTER_SS3_PIN      (1u)
#define Rx_Left_REMOVE_UART_TX_PIN             (1u)
#define Rx_Left_REMOVE_UART_RX_TX_PIN          (1u)
#define Rx_Left_REMOVE_UART_RX_PIN             (0u)
#define Rx_Left_REMOVE_UART_RX_WAKE_PIN        (1u)
#define Rx_Left_REMOVE_UART_RTS_PIN            (1u)
#define Rx_Left_REMOVE_UART_CTS_PIN            (1u)

/* Unconfigured pins */
#define Rx_Left_MOSI_SCL_RX_WAKE_PIN   (0u == Rx_Left_REMOVE_MOSI_SCL_RX_WAKE_PIN)
#define Rx_Left_MOSI_SCL_RX_PIN        (0u == Rx_Left_REMOVE_MOSI_SCL_RX_PIN)
#define Rx_Left_MISO_SDA_TX_PIN        (0u == Rx_Left_REMOVE_MISO_SDA_TX_PIN)
#define Rx_Left_SCLK_PIN               (0u == Rx_Left_REMOVE_SCLK_PIN)
#define Rx_Left_SS0_PIN                (0u == Rx_Left_REMOVE_SS0_PIN)
#define Rx_Left_SS1_PIN                (0u == Rx_Left_REMOVE_SS1_PIN)
#define Rx_Left_SS2_PIN                (0u == Rx_Left_REMOVE_SS2_PIN)
#define Rx_Left_SS3_PIN                (0u == Rx_Left_REMOVE_SS3_PIN)

/* Mode defined pins */
#define Rx_Left_I2C_PINS               (0u == Rx_Left_REMOVE_I2C_PINS)
#define Rx_Left_SPI_MASTER_PINS        (0u == Rx_Left_REMOVE_SPI_MASTER_PINS)
#define Rx_Left_SPI_SLAVE_PINS         (0u == Rx_Left_REMOVE_SPI_SLAVE_PINS)
#define Rx_Left_SPI_MASTER_SS0_PIN     (0u == Rx_Left_REMOVE_SPI_MASTER_SS0_PIN)
#define Rx_Left_SPI_MASTER_SS1_PIN     (0u == Rx_Left_REMOVE_SPI_MASTER_SS1_PIN)
#define Rx_Left_SPI_MASTER_SS2_PIN     (0u == Rx_Left_REMOVE_SPI_MASTER_SS2_PIN)
#define Rx_Left_SPI_MASTER_SS3_PIN     (0u == Rx_Left_REMOVE_SPI_MASTER_SS3_PIN)
#define Rx_Left_UART_TX_PIN            (0u == Rx_Left_REMOVE_UART_TX_PIN)
#define Rx_Left_UART_RX_TX_PIN         (0u == Rx_Left_REMOVE_UART_RX_TX_PIN)
#define Rx_Left_UART_RX_PIN            (0u == Rx_Left_REMOVE_UART_RX_PIN)
#define Rx_Left_UART_RX_WAKE_PIN       (0u == Rx_Left_REMOVE_UART_RX_WAKE_PIN)
#define Rx_Left_UART_RTS_PIN           (0u == Rx_Left_REMOVE_UART_RTS_PIN)
#define Rx_Left_UART_CTS_PIN           (0u == Rx_Left_REMOVE_UART_CTS_PIN)


/***************************************
*             Includes
****************************************/

#if(Rx_Left_MOSI_SCL_RX_WAKE_PIN)
    #include "Rx_Left_spi_mosi_i2c_scl_uart_rx_wake.h"
#endif /* (Rx_Left_MOSI_SCL_RX_WAKE_PIN) */

#if(Rx_Left_MOSI_SCL_RX_PIN)
    #include "Rx_Left_spi_mosi_i2c_scl_uart_rx.h"
#endif /* (Rx_Left_MOSI_SCL_RX_PIN) */

#if(Rx_Left_MISO_SDA_TX_PIN)
    #include "Rx_Left_spi_miso_i2c_sda_uart_tx.h"
#endif /* (Rx_Left_MISO_SDA_TX_PIN_PIN) */

#if(Rx_Left_SCLK_PIN)
    #include "Rx_Left_spi_sclk.h"
#endif /* (Rx_Left_SCLK_PIN) */

#if(Rx_Left_SS0_PIN)
    #include "Rx_Left_spi_ss0.h"
#endif /* (Rx_Left_SS1_PIN) */

#if(Rx_Left_SS1_PIN)
    #include "Rx_Left_spi_ss1.h"
#endif /* (Rx_Left_SS1_PIN) */

#if(Rx_Left_SS2_PIN)
    #include "Rx_Left_spi_ss2.h"
#endif /* (Rx_Left_SS2_PIN) */

#if(Rx_Left_SS3_PIN)
    #include "Rx_Left_spi_ss3.h"
#endif /* (Rx_Left_SS3_PIN) */

#if(Rx_Left_I2C_PINS)
    #include "Rx_Left_scl.h"
    #include "Rx_Left_sda.h"
#endif /* (Rx_Left_I2C_PINS) */

#if(Rx_Left_SPI_MASTER_PINS)
    #include "Rx_Left_sclk_m.h"
    #include "Rx_Left_mosi_m.h"
    #include "Rx_Left_miso_m.h"
#endif /* (Rx_Left_SPI_MASTER_PINS) */

#if(Rx_Left_SPI_SLAVE_PINS)
    #include "Rx_Left_sclk_s.h"
    #include "Rx_Left_mosi_s.h"
    #include "Rx_Left_miso_s.h"
    #include "Rx_Left_ss_s.h"
#endif /* (Rx_Left_SPI_SLAVE_PINS) */

#if(Rx_Left_SPI_MASTER_SS0_PIN)
    #include "Rx_Left_ss0_m.h"
#endif /* (Rx_Left_SPI_MASTER_SS0_PIN) */

#if(Rx_Left_SPI_MASTER_SS1_PIN)
    #include "Rx_Left_ss1_m.h"
#endif /* (Rx_Left_SPI_MASTER_SS1_PIN) */

#if(Rx_Left_SPI_MASTER_SS2_PIN)
    #include "Rx_Left_ss2_m.h"
#endif /* (Rx_Left_SPI_MASTER_SS2_PIN) */

#if(Rx_Left_SPI_MASTER_SS3_PIN)
    #include "Rx_Left_ss3_m.h"
#endif /* (Rx_Left_SPI_MASTER_SS3_PIN) */

#if(Rx_Left_UART_TX_PIN)
    #include "Rx_Left_tx.h"
#endif /* (Rx_Left_UART_TX_PIN) */

#if(Rx_Left_UART_RX_TX_PIN)
    #include "Rx_Left_rx_tx.h"
#endif /* (Rx_Left_UART_RX_TX_PIN) */

#if(Rx_Left_UART_RX_PIN)
    #include "Rx_Left_rx.h"
#endif /* (Rx_Left_UART_RX_PIN) */

#if(Rx_Left_UART_RX_WAKE_PIN)
    #include "Rx_Left_rx_wake.h"
#endif /* (Rx_Left_UART_RX_WAKE_PIN) */

#if(Rx_Left_UART_RTS_PIN)
    #include "Rx_Left_rts.h"
#endif /* (Rx_Left_UART_RTS_PIN) */

#if(Rx_Left_UART_CTS_PIN)
    #include "Rx_Left_cts.h"
#endif /* (Rx_Left_UART_CTS_PIN) */


/***************************************
*              Registers
***************************************/

#if(Rx_Left_MOSI_SCL_RX_WAKE_PIN)
    #define Rx_Left_MOSI_SCL_RX_WAKE_HSIOM_REG  \
                                                (*(reg32 *) Rx_Left_spi_mosi_i2c_scl_uart_rx_wake__0__HSIOM)
    #define Rx_Left_MOSI_SCL_RX_WAKE_HSIOM_PTR  \
                                                ( (reg32 *) Rx_Left_spi_mosi_i2c_scl_uart_rx_wake__0__HSIOM)
    #define Rx_Left_MOSI_SCL_RX_WAKE_HSIOM_MASK \
                                                (Rx_Left_spi_mosi_i2c_scl_uart_rx_wake__0__HSIOM_MASK)
    #define Rx_Left_MOSI_SCL_RX_WAKE_HSIOM_POS  \
                                                (Rx_Left_spi_mosi_i2c_scl_uart_rx_wake__0__HSIOM_SHIFT)

    #define Rx_Left_MOSI_SCL_RX_WAKE_INTCFG_REG    (*(reg32 *) \
                                                              Rx_Left_spi_mosi_i2c_scl_uart_rx_wake__0__INTCFG)
    #define Rx_Left_MOSI_SCL_RX_WAKE_INTCFG_PTR    ( (reg32 *) \
                                                              Rx_Left_spi_mosi_i2c_scl_uart_rx_wake__0__INTCFG)

    #define Rx_Left_INTCFG_TYPE_MASK                  (0x03u)
    #define Rx_Left_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS  (Rx_Left_spi_mosi_i2c_scl_uart_rx_wake__SHIFT)
    #define Rx_Left_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK ((uint32)                                           \
                                                                    ((uint32) Rx_Left_INTCFG_TYPE_MASK << \
                                                                    Rx_Left_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS))
#endif /* (Rx_Left_MOSI_SCL_RX_WAKE_PIN) */

#if(Rx_Left_MOSI_SCL_RX_PIN)
    #define Rx_Left_MOSI_SCL_RX_HSIOM_REG      (*(reg32 *) Rx_Left_spi_mosi_i2c_scl_uart_rx__0__HSIOM)
    #define Rx_Left_MOSI_SCL_RX_HSIOM_PTR      ( (reg32 *) Rx_Left_spi_mosi_i2c_scl_uart_rx__0__HSIOM)
    #define Rx_Left_MOSI_SCL_RX_HSIOM_MASK     (Rx_Left_spi_mosi_i2c_scl_uart_rx__0__HSIOM_MASK)
    #define Rx_Left_MOSI_SCL_RX_HSIOM_POS      (Rx_Left_spi_mosi_i2c_scl_uart_rx__0__HSIOM_SHIFT)
#endif /* (Rx_Left_MOSI_SCL_RX_PIN) */

#if(Rx_Left_MISO_SDA_TX_PIN)
    #define Rx_Left_MISO_SDA_TX_HSIOM_REG      (*(reg32 *) Rx_Left_spi_miso_i2c_sda_uart_tx__0__HSIOM)
    #define Rx_Left_MISO_SDA_TX_HSIOM_PTR      ( (reg32 *) Rx_Left_spi_miso_i2c_sda_uart_tx__0__HSIOM)
    #define Rx_Left_MISO_SDA_TX_HSIOM_MASK     (Rx_Left_spi_miso_i2c_sda_uart_tx__0__HSIOM_MASK)
    #define Rx_Left_MISO_SDA_TX_HSIOM_POS      (Rx_Left_spi_miso_i2c_sda_uart_tx__0__HSIOM_SHIFT)
#endif /* (Rx_Left_MISO_SDA_TX_PIN_PIN) */

#if(Rx_Left_SCLK_PIN)
    #define Rx_Left_SCLK_HSIOM_REG     (*(reg32 *) Rx_Left_spi_sclk__0__HSIOM)
    #define Rx_Left_SCLK_HSIOM_PTR     ( (reg32 *) Rx_Left_spi_sclk__0__HSIOM)
    #define Rx_Left_SCLK_HSIOM_MASK    (Rx_Left_spi_sclk__0__HSIOM_MASK)
    #define Rx_Left_SCLK_HSIOM_POS     (Rx_Left_spi_sclk__0__HSIOM_SHIFT)
#endif /* (Rx_Left_SCLK_PIN) */

#if(Rx_Left_SS0_PIN)
    #define Rx_Left_SS0_HSIOM_REG      (*(reg32 *) Rx_Left_spi_ss0__0__HSIOM)
    #define Rx_Left_SS0_HSIOM_PTR      ( (reg32 *) Rx_Left_spi_ss0__0__HSIOM)
    #define Rx_Left_SS0_HSIOM_MASK     (Rx_Left_spi_ss0__0__HSIOM_MASK)
    #define Rx_Left_SS0_HSIOM_POS      (Rx_Left_spi_ss0__0__HSIOM_SHIFT)
#endif /* (Rx_Left_SS1_PIN) */

#if(Rx_Left_SS1_PIN)
    #define Rx_Left_SS1_HSIOM_REG      (*(reg32 *) Rx_Left_spi_ss1__0__HSIOM)
    #define Rx_Left_SS1_HSIOM_PTR      ( (reg32 *) Rx_Left_spi_ss1__0__HSIOM)
    #define Rx_Left_SS1_HSIOM_MASK     (Rx_Left_spi_ss1__0__HSIOM_MASK)
    #define Rx_Left_SS1_HSIOM_POS      (Rx_Left_spi_ss1__0__HSIOM_SHIFT)
#endif /* (Rx_Left_SS1_PIN) */

#if(Rx_Left_SS2_PIN)
    #define Rx_Left_SS2_HSIOM_REG     (*(reg32 *) Rx_Left_spi_ss2__0__HSIOM)
    #define Rx_Left_SS2_HSIOM_PTR     ( (reg32 *) Rx_Left_spi_ss2__0__HSIOM)
    #define Rx_Left_SS2_HSIOM_MASK    (Rx_Left_spi_ss2__0__HSIOM_MASK)
    #define Rx_Left_SS2_HSIOM_POS     (Rx_Left_spi_ss2__0__HSIOM_SHIFT)
#endif /* (Rx_Left_SS2_PIN) */

#if(Rx_Left_SS3_PIN)
    #define Rx_Left_SS3_HSIOM_REG     (*(reg32 *) Rx_Left_spi_ss3__0__HSIOM)
    #define Rx_Left_SS3_HSIOM_PTR     ( (reg32 *) Rx_Left_spi_ss3__0__HSIOM)
    #define Rx_Left_SS3_HSIOM_MASK    (Rx_Left_spi_ss3__0__HSIOM_MASK)
    #define Rx_Left_SS3_HSIOM_POS     (Rx_Left_spi_ss3__0__HSIOM_SHIFT)
#endif /* (Rx_Left_SS3_PIN) */

#if(Rx_Left_I2C_PINS)
    #define Rx_Left_SCL_HSIOM_REG     (*(reg32 *) Rx_Left_scl__0__HSIOM)
    #define Rx_Left_SCL_HSIOM_PTR     ( (reg32 *) Rx_Left_scl__0__HSIOM)
    #define Rx_Left_SCL_HSIOM_MASK    (Rx_Left_scl__0__HSIOM_MASK)
    #define Rx_Left_SCL_HSIOM_POS     (Rx_Left_scl__0__HSIOM_SHIFT)

    #define Rx_Left_SDA_HSIOM_REG     (*(reg32 *) Rx_Left_sda__0__HSIOM)
    #define Rx_Left_SDA_HSIOM_PTR     ( (reg32 *) Rx_Left_sda__0__HSIOM)
    #define Rx_Left_SDA_HSIOM_MASK    (Rx_Left_sda__0__HSIOM_MASK)
    #define Rx_Left_SDA_HSIOM_POS     (Rx_Left_sda__0__HSIOM_SHIFT)
#endif /* (Rx_Left_I2C_PINS) */


/***************************************
*        Registers Constants
***************************************/

/* Pins constants */
#define Rx_Left_HSIOM_DEF_SEL      (0x00u)
#define Rx_Left_HSIOM_GPIO_SEL     (0x00u)
#define Rx_Left_HSIOM_UART_SEL     (0x09u)
#define Rx_Left_HSIOM_I2C_SEL      (0x0Eu)
#define Rx_Left_HSIOM_SPI_SEL      (0x0Fu)

#define Rx_Left_MOSI_SCL_RX_PIN_INDEX      (0u) /* RX pins without interrupt */
#define Rx_Left_MOSI_SCL_RX_WAKE_PIN_INDEX (0u) /* RX pin with interrupt     */
#define Rx_Left_MISO_SDA_TX_PIN_INDEX      (1u)
#define Rx_Left_SCLK_PIN_INDEX             (2u)
#define Rx_Left_SS0_PIN_INDEX              (3u)
#define Rx_Left_SS1_PIN_INDEX              (4u)
#define Rx_Left_SS2_PIN_INDEX              (5u)
#define Rx_Left_SS3_PIN_INDEX              (6u)

#define Rx_Left_MOSI_SCL_RX_PIN_MASK      ((uint32) 0x01u << Rx_Left_MOSI_SCL_RX_PIN_INDEX)
#define Rx_Left_MOSI_SCL_RX_WAKE_PIN_MASK ((uint32) 0x01u << Rx_Left_MOSI_SCL_RX_WAKE_PIN_INDEX)
#define Rx_Left_MISO_SDA_TX_PIN_MASK      ((uint32) 0x01u << Rx_Left_MISO_SDA_TX_PIN_INDEX)
#define Rx_Left_SCLK_PIN_MASK             ((uint32) 0x01u << Rx_Left_SCLK_PIN_INDEX)
#define Rx_Left_SS0_PIN_MASK              ((uint32) 0x01u << Rx_Left_SS0_PIN_INDEX)
#define Rx_Left_SS1_PIN_MASK              ((uint32) 0x01u << Rx_Left_SS1_PIN_INDEX)
#define Rx_Left_SS2_PIN_MASK              ((uint32) 0x01u << Rx_Left_SS2_PIN_INDEX)
#define Rx_Left_SS3_PIN_MASK              ((uint32) 0x01u << Rx_Left_SS3_PIN_INDEX)

#define Rx_Left_INTCFG_TYPE_FALLING_EDGE   (0x02u)

/* Pin DM defines */
#define Rx_Left_PIN_DM_ALG_HIZ  (0u)
#define Rx_Left_PIN_DM_DIG_HIZ  (1u)
#define Rx_Left_PIN_DM_OD_LO    (4u)
#define Rx_Left_PIN_DM_STRONG   (6u)


/***************************************
*          Macro Definitions
***************************************/

/* Set bits-mask in register */
#define Rx_Left_SET_REGISTER_BITS(reg, mask, pos, mode) \
                    do                                           \
                    {                                            \
                        (reg) = (((reg) & ((uint32) ~(uint32) (mask))) | ((uint32) ((uint32) (mode) << (pos)))); \
                    }while(0)

/* Set bit in the register */
#define Rx_Left_SET_REGISTER_BIT(reg, mask, val) \
                    ((val) ? ((reg) |= (mask)) : ((reg) &= ((uint32) ~((uint32) (mask)))))

#define Rx_Left_SET_HSIOM_SEL(reg, mask, pos, sel) Rx_Left_SET_REGISTER_BITS(reg, mask, pos, sel)
#define Rx_Left_SET_INCFG_TYPE(reg, mask, pos, intType) \
                                                        Rx_Left_SET_REGISTER_BITS(reg, mask, pos, intType)
#define Rx_Left_SET_INP_DIS(reg, mask, val) Rx_Left_SET_REGISTER_BIT(reg, mask, val)

/* Rx_Left_SET_I2C_SCL_DR(val) - Sets I2C SCL DR register.
*  Rx_Left_SET_I2C_SCL_HSIOM_SEL(sel) - Sets I2C SCL HSIOM settings.
*/
/* SCB I2C: scl signal */
#if(Rx_Left_I2C_PINS)
    #define Rx_Left_SET_I2C_SCL_DR(val) Rx_Left_scl_Write(val)

    #define Rx_Left_SET_I2C_SCL_HSIOM_SEL(sel) \
                          Rx_Left_SET_HSIOM_SEL(Rx_Left_SCL_HSIOM_REG,  \
                                                         Rx_Left_SCL_HSIOM_MASK, \
                                                         Rx_Left_SCL_HSIOM_POS,  \
                                                         (sel))
    #define Rx_Left_WAIT_SCL_SET_HIGH  (0u == Rx_Left_scl_Read())

/* Unconfigured SCB: scl signal */
#elif(Rx_Left_MOSI_SCL_RX_WAKE_PIN)
    #define Rx_Left_SET_I2C_SCL_DR(val) \
                            Rx_Left_spi_mosi_i2c_scl_uart_rx_wake_Write(val)

    #define Rx_Left_SET_I2C_SCL_HSIOM_SEL(sel) \
                    Rx_Left_SET_HSIOM_SEL(Rx_Left_MOSI_SCL_RX_WAKE_HSIOM_REG,  \
                                                   Rx_Left_MOSI_SCL_RX_WAKE_HSIOM_MASK, \
                                                   Rx_Left_MOSI_SCL_RX_WAKE_HSIOM_POS,  \
                                                   (sel))

    #define Rx_Left_WAIT_SCL_SET_HIGH  (0u == Rx_Left_spi_mosi_i2c_scl_uart_rx_wake_Read())

#elif(Rx_Left_MOSI_SCL_RX_PIN)
    #define Rx_Left_SET_I2C_SCL_DR(val) \
                            Rx_Left_spi_mosi_i2c_scl_uart_rx_Write(val)


    #define Rx_Left_SET_I2C_SCL_HSIOM_SEL(sel) \
                            Rx_Left_SET_HSIOM_SEL(Rx_Left_MOSI_SCL_RX_HSIOM_REG,  \
                                                           Rx_Left_MOSI_SCL_RX_HSIOM_MASK, \
                                                           Rx_Left_MOSI_SCL_RX_HSIOM_POS,  \
                                                           (sel))

    #define Rx_Left_WAIT_SCL_SET_HIGH  (0u == Rx_Left_spi_mosi_i2c_scl_uart_rx_Read())

#else
    #define Rx_Left_SET_I2C_SCL_DR(val) \
                                                    do{ /* Does nothing */ }while(0)
    #define Rx_Left_SET_I2C_SCL_HSIOM_SEL(sel) \
                                                    do{ /* Does nothing */ }while(0)

    #define Rx_Left_WAIT_SCL_SET_HIGH  (0u)
#endif /* (Rx_Left_MOSI_SCL_RX_PIN) */

/* SCB I2C: sda signal */
#if(Rx_Left_I2C_PINS)
    #define Rx_Left_WAIT_SDA_SET_HIGH  (0u == Rx_Left_sda_Read())

/* Unconfigured SCB: sda signal */
#elif(Rx_Left_MISO_SDA_TX_PIN)
    #define Rx_Left_WAIT_SDA_SET_HIGH  (0u == Rx_Left_spi_miso_i2c_sda_uart_tx_Read())

#else
    #define Rx_Left_WAIT_SDA_SET_HIGH  (0u)
#endif /* (Rx_Left_MOSI_SCL_RX_PIN) */

#endif /* (CY_SCB_PINS_Rx_Left_H) */


/* [] END OF FILE */
