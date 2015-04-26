/*******************************************************************************
* File Name: Rx_Left.c
* Version 2.0
*
* Description:
*  This file provides the source code to the API for the SCB Component.
*
* Note:
*
*******************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Rx_Left_PVT.h"

#if(Rx_Left_SCB_MODE_I2C_INC)
    #include "Rx_Left_I2C_PVT.h"
#endif /* (Rx_Left_SCB_MODE_I2C_INC) */

#if(Rx_Left_SCB_MODE_EZI2C_INC)
    #include "Rx_Left_EZI2C_PVT.h"
#endif /* (Rx_Left_SCB_MODE_EZI2C_INC) */

#if(Rx_Left_SCB_MODE_SPI_INC || Rx_Left_SCB_MODE_UART_INC)
    #include "Rx_Left_SPI_UART_PVT.h"
#endif /* (Rx_Left_SCB_MODE_SPI_INC || Rx_Left_SCB_MODE_UART_INC) */


/***************************************
*    Run Time Configuration Vars
***************************************/

/* Stores internal component configuration for Unconfigured mode */
#if(Rx_Left_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    uint8 Rx_Left_scbMode = Rx_Left_SCB_MODE_UNCONFIG;
    uint8 Rx_Left_scbEnableWake;
    uint8 Rx_Left_scbEnableIntr;

    /* I2C configuration variables */
    uint8 Rx_Left_mode;
    uint8 Rx_Left_acceptAddr;

    /* SPI/UART configuration variables */
    volatile uint8 * Rx_Left_rxBuffer;
    uint8  Rx_Left_rxDataBits;
    uint32 Rx_Left_rxBufferSize;

    volatile uint8 * Rx_Left_txBuffer;
    uint8  Rx_Left_txDataBits;
    uint32 Rx_Left_txBufferSize;

    /* EZI2C configuration variables */
    uint8 Rx_Left_numberOfAddr;
    uint8 Rx_Left_subAddrSize;
#endif /* (Rx_Left_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Common SCB Vars
***************************************/

uint8 Rx_Left_initVar = 0u;

#if !defined (CY_REMOVE_Rx_Left_CUSTOM_INTR_HANDLER)
    cyisraddress Rx_Left_customIntrHandler = NULL;
#endif /* !defined (CY_REMOVE_Rx_Left_CUSTOM_INTR_HANDLER) */


/***************************************
*    Private Function Prototypes
***************************************/

static void Rx_Left_ScbEnableIntr(void);
static void Rx_Left_ScbModeStop(void);


/*******************************************************************************
* Function Name: Rx_Left_Init
********************************************************************************
*
* Summary:
*  Initializes the SCB component to operate in one of the selected
*  configurations: I2C, SPI, UART or EZI2C.
*  When the configuration is set to "Unconfigured SCB", this function does
*  not do any initialization. Use mode-specific initialization APIs instead:
*  SCB_I2CInit, SCB_SpiInit, SCB_UartInit or SCB_EzI2CInit.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Rx_Left_Init(void)
{
#if(Rx_Left_SCB_MODE_UNCONFIG_CONST_CFG)
    if(Rx_Left_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        Rx_Left_initVar = 0u;
    }
    else
    {
        /* Initialization was done before this function call */
    }

#elif(Rx_Left_SCB_MODE_I2C_CONST_CFG)
    Rx_Left_I2CInit();

#elif(Rx_Left_SCB_MODE_SPI_CONST_CFG)
    Rx_Left_SpiInit();

#elif(Rx_Left_SCB_MODE_UART_CONST_CFG)
    Rx_Left_UartInit();

#elif(Rx_Left_SCB_MODE_EZI2C_CONST_CFG)
    Rx_Left_EzI2CInit();

#endif /* (Rx_Left_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: Rx_Left_Enable
********************************************************************************
*
* Summary:
*  Enables the SCB component operation.
*  The SCB configuration should be not changed when the component is enabled.
*  Any configuration changes should be made after disabling the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Rx_Left_Enable(void)
{
#if(Rx_Left_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Enable SCB block, only if it is already configured */
    if(!Rx_Left_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        Rx_Left_CTRL_REG |= Rx_Left_CTRL_ENABLED;

        Rx_Left_ScbEnableIntr();
    }
#else
    Rx_Left_CTRL_REG |= Rx_Left_CTRL_ENABLED;

    Rx_Left_ScbEnableIntr();
#endif /* (Rx_Left_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: Rx_Left_Start
********************************************************************************
*
* Summary:
*  Invokes SCB_Init() and SCB_Enable().
*  After this function call, the component is enabled and ready for operation.
*  When configuration is set to "Unconfigured SCB", the component must first be
*  initialized to operate in one of the following configurations: I2C, SPI, UART
*  or EZ I2C. Otherwise this function does not enable the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Rx_Left_initVar - used to check initial configuration, modified
*  on first function call.
*
*******************************************************************************/
void Rx_Left_Start(void)
{
    if(0u == Rx_Left_initVar)
    {
        Rx_Left_Init();
        Rx_Left_initVar = 1u; /* Component was initialized */
    }

    Rx_Left_Enable();
}


/*******************************************************************************
* Function Name: Rx_Left_Stop
********************************************************************************
*
* Summary:
*  Disables the SCB component and its interrupt.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Rx_Left_Stop(void)
{
#if(Rx_Left_SCB_IRQ_INTERNAL)
    Rx_Left_DisableInt();
#endif /* (Rx_Left_SCB_IRQ_INTERNAL) */

    Rx_Left_CTRL_REG &= (uint32) ~Rx_Left_CTRL_ENABLED;  /* Disable scb IP */

#if(Rx_Left_SCB_IRQ_INTERNAL)
    Rx_Left_ClearPendingInt();
#endif /* (Rx_Left_SCB_IRQ_INTERNAL) */

    Rx_Left_ScbModeStop(); /* Calls scbMode specific Stop function */
}


/*******************************************************************************
* Function Name: Rx_Left_SetRxFifoLevel
********************************************************************************
*
* Summary:
*  Sets level in the RX FIFO to generate a RX level interrupt.
*  When the RX FIFO has more entries than the RX FIFO level an RX level
*  interrupt request is generated.
*
* Parameters:
*  level: Level in the RX FIFO to generate RX level interrupt.
*         The range of valid level values is between 0 and RX FIFO depth - 1.
*
* Return:
*  None
*
*******************************************************************************/
void Rx_Left_SetRxFifoLevel(uint32 level)
{
    uint32 rxFifoCtrl;

    rxFifoCtrl = Rx_Left_RX_FIFO_CTRL_REG;

    rxFifoCtrl &= ((uint32) ~Rx_Left_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    rxFifoCtrl |= ((uint32) (Rx_Left_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    Rx_Left_RX_FIFO_CTRL_REG = rxFifoCtrl;
}


/*******************************************************************************
* Function Name: Rx_Left_SetTxFifoLevel
********************************************************************************
*
* Summary:
*  Sets level in the TX FIFO to generate a TX level interrupt.
*  When the TX FIFO has more entries than the TX FIFO level an TX level
*  interrupt request is generated.
*
* Parameters:
*  level: Level in the TX FIFO to generate TX level interrupt.
*         The range of valid level values is between 0 and TX FIFO depth - 1.
*
* Return:
*  None
*
*******************************************************************************/
void Rx_Left_SetTxFifoLevel(uint32 level)
{
    uint32 txFifoCtrl;

    txFifoCtrl = Rx_Left_TX_FIFO_CTRL_REG;

    txFifoCtrl &= ((uint32) ~Rx_Left_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    txFifoCtrl |= ((uint32) (Rx_Left_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    Rx_Left_TX_FIFO_CTRL_REG = txFifoCtrl;
}


/*******************************************************************************
* Function Name: Rx_Left_SetCustomInterruptHandler
********************************************************************************
*
* Summary:
*  Registers a function to be called by the internal interrupt handler.
*  First the function that is registered is called, then the internal interrupt
*  handler performs any operation such as software buffer management functions
*  before the interrupt returns.  It is the user's responsibility not to break
*  the software buffer operations. Only one custom handler is supported, which
*  is the function provided by the most recent call.
*  At the initialization time no custom handler is registered.
*
* Parameters:
*  func: Pointer to the function to register.
*        The value NULL indicates to remove the current custom interrupt
*        handler.
*
* Return:
*  None
*
*******************************************************************************/
void Rx_Left_SetCustomInterruptHandler(cyisraddress func)
{
#if !defined (CY_REMOVE_Rx_Left_CUSTOM_INTR_HANDLER)
    Rx_Left_customIntrHandler = func; /* Register interrupt handler */
#else
    if(NULL != func)
    {
        /* Suppress compiler warning */
    }
#endif /* !defined (CY_REMOVE_Rx_Left_CUSTOM_INTR_HANDLER) */
}


/*******************************************************************************
* Function Name: Rx_Left_ScbModeEnableIntr
********************************************************************************
*
* Summary:
*  Enables an interrupt for a specific mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void Rx_Left_ScbEnableIntr(void)
{
#if(Rx_Left_SCB_IRQ_INTERNAL)
    #if(Rx_Left_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Enable interrupt in NVIC */
        if(0u != Rx_Left_scbEnableIntr)
        {
            Rx_Left_EnableInt();
        }
    #else
        Rx_Left_EnableInt();

    #endif /* (Rx_Left_SCB_MODE_UNCONFIG_CONST_CFG) */
#endif /* (Rx_Left_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: Rx_Left_ScbModeStop
********************************************************************************
*
* Summary:
*  Calls the Stop function for a specific operation mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void Rx_Left_ScbModeStop(void)
{
#if(Rx_Left_SCB_MODE_UNCONFIG_CONST_CFG)
    if(Rx_Left_SCB_MODE_I2C_RUNTM_CFG)
    {
        Rx_Left_I2CStop();
    }
    else if (Rx_Left_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        Rx_Left_EzI2CStop();
    }
#if (!Rx_Left_CY_SCBIP_V1)
    else if (Rx_Left_SCB_MODE_UART_RUNTM_CFG)
    {
        Rx_Left_UartStop();
    }
#endif /* (!Rx_Left_CY_SCBIP_V1) */
    else
    {
        /* Do nothing for other modes */
    }
#elif(Rx_Left_SCB_MODE_I2C_CONST_CFG)
    Rx_Left_I2CStop();

#elif(Rx_Left_SCB_MODE_EZI2C_CONST_CFG)
    Rx_Left_EzI2CStop();

#elif(Rx_Left_SCB_MODE_UART_CONST_CFG)
    Rx_Left_UartStop();

#endif /* (Rx_Left_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if(Rx_Left_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: Rx_Left_SetPins
    ********************************************************************************
    *
    * Summary:
    *  Sets the pins settings accordingly to the selected operation mode.
    *  Only available in the Unconfigured operation mode. The mode specific
    *  initialization function calls it.
    *  Pins configuration is set by PSoC Creator when a specific mode of operation
    *  is selected in design time.
    *
    * Parameters:
    *  mode:      Mode of SCB operation.
    *  subMode:   Sub-mode of SCB operation. It is only required for SPI and UART
    *             modes.
    *  uartEnableMask: enables TX or RX direction and RTS and CTS signals.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void Rx_Left_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask)
    {
        uint32 hsiomSel [Rx_Left_SCB_PINS_NUMBER];
        uint32 pinsDm   [Rx_Left_SCB_PINS_NUMBER];

    #if (!Rx_Left_CY_SCBIP_V1)
        uint32 pinsInBuf = 0u;
    #endif /* (!Rx_Left_CY_SCBIP_V1) */

        uint32 i;

        /* Set default HSIOM to GPIO and Drive Mode to Analog Hi-Z */
        for(i = 0u; i < Rx_Left_SCB_PINS_NUMBER; i++)
        {
            hsiomSel[i]  = Rx_Left_HSIOM_DEF_SEL;
            pinsDm[i]    = Rx_Left_PIN_DM_ALG_HIZ;
        }

        if((Rx_Left_SCB_MODE_I2C   == mode) ||
           (Rx_Left_SCB_MODE_EZI2C == mode))
        {
            hsiomSel[Rx_Left_MOSI_SCL_RX_PIN_INDEX] = Rx_Left_HSIOM_I2C_SEL;
            hsiomSel[Rx_Left_MISO_SDA_TX_PIN_INDEX] = Rx_Left_HSIOM_I2C_SEL;

            pinsDm[Rx_Left_MOSI_SCL_RX_PIN_INDEX] = Rx_Left_PIN_DM_OD_LO;
            pinsDm[Rx_Left_MISO_SDA_TX_PIN_INDEX] = Rx_Left_PIN_DM_OD_LO;
        }
    #if (!Rx_Left_CY_SCBIP_V1)
        else if(Rx_Left_SCB_MODE_SPI == mode)
        {
            hsiomSel[Rx_Left_MOSI_SCL_RX_PIN_INDEX] = Rx_Left_HSIOM_SPI_SEL;
            hsiomSel[Rx_Left_MISO_SDA_TX_PIN_INDEX] = Rx_Left_HSIOM_SPI_SEL;
            hsiomSel[Rx_Left_SCLK_PIN_INDEX]        = Rx_Left_HSIOM_SPI_SEL;

            if(Rx_Left_SPI_SLAVE == subMode)
            {
                /* Slave */
                pinsDm[Rx_Left_MOSI_SCL_RX_PIN_INDEX] = Rx_Left_PIN_DM_DIG_HIZ;
                pinsDm[Rx_Left_MISO_SDA_TX_PIN_INDEX] = Rx_Left_PIN_DM_STRONG;
                pinsDm[Rx_Left_SCLK_PIN_INDEX]        = Rx_Left_PIN_DM_DIG_HIZ;

            #if(Rx_Left_SS0_PIN)
                /* Only SS0 is valid choice for Slave */
                hsiomSel[Rx_Left_SS0_PIN_INDEX] = Rx_Left_HSIOM_SPI_SEL;
                pinsDm  [Rx_Left_SS0_PIN_INDEX] = Rx_Left_PIN_DM_DIG_HIZ;
            #endif /* (Rx_Left_SS1_PIN) */

            #if(Rx_Left_MISO_SDA_TX_PIN)
                /* Disable input buffer */
                 pinsInBuf |= Rx_Left_MISO_SDA_TX_PIN_MASK;
            #endif /* (Rx_Left_MISO_SDA_TX_PIN_PIN) */
            }
            else /* (Master) */
            {
                pinsDm[Rx_Left_MOSI_SCL_RX_PIN_INDEX] = Rx_Left_PIN_DM_STRONG;
                pinsDm[Rx_Left_MISO_SDA_TX_PIN_INDEX] = Rx_Left_PIN_DM_DIG_HIZ;
                pinsDm[Rx_Left_SCLK_PIN_INDEX]        = Rx_Left_PIN_DM_STRONG;

            #if(Rx_Left_SS0_PIN)
                hsiomSel [Rx_Left_SS0_PIN_INDEX] = Rx_Left_HSIOM_SPI_SEL;
                pinsDm   [Rx_Left_SS0_PIN_INDEX] = Rx_Left_PIN_DM_STRONG;
                pinsInBuf                                |= Rx_Left_SS0_PIN_MASK;
            #endif /* (Rx_Left_SS0_PIN) */

            #if(Rx_Left_SS1_PIN)
                hsiomSel [Rx_Left_SS1_PIN_INDEX] = Rx_Left_HSIOM_SPI_SEL;
                pinsDm   [Rx_Left_SS1_PIN_INDEX] = Rx_Left_PIN_DM_STRONG;
                pinsInBuf                                |= Rx_Left_SS1_PIN_MASK;
            #endif /* (Rx_Left_SS1_PIN) */

            #if(Rx_Left_SS2_PIN)
                hsiomSel [Rx_Left_SS2_PIN_INDEX] = Rx_Left_HSIOM_SPI_SEL;
                pinsDm   [Rx_Left_SS2_PIN_INDEX] = Rx_Left_PIN_DM_STRONG;
                pinsInBuf                                |= Rx_Left_SS2_PIN_MASK;
            #endif /* (Rx_Left_SS2_PIN) */

            #if(Rx_Left_SS3_PIN)
                hsiomSel [Rx_Left_SS3_PIN_INDEX] = Rx_Left_HSIOM_SPI_SEL;
                pinsDm   [Rx_Left_SS3_PIN_INDEX] = Rx_Left_PIN_DM_STRONG;
                pinsInBuf                                |= Rx_Left_SS3_PIN_MASK;
            #endif /* (Rx_Left_SS2_PIN) */

                /* Disable input buffers */
            #if(Rx_Left_MOSI_SCL_RX_PIN)
                pinsInBuf |= Rx_Left_MOSI_SCL_RX_PIN_MASK;
            #endif /* (Rx_Left_MOSI_SCL_RX_PIN) */

             #if(Rx_Left_MOSI_SCL_RX_WAKE_PIN)
                pinsInBuf |= Rx_Left_MOSI_SCL_RX_WAKE_PIN_MASK;
            #endif /* (Rx_Left_MOSI_SCL_RX_WAKE_PIN) */

            #if(Rx_Left_SCLK_PIN)
                pinsInBuf |= Rx_Left_SCLK_PIN_MASK;
            #endif /* (Rx_Left_SCLK_PIN) */
            }
        }
        else /* UART */
        {
            if(Rx_Left_UART_MODE_SMARTCARD == subMode)
            {
                /* SmartCard */
                hsiomSel[Rx_Left_MISO_SDA_TX_PIN_INDEX] = Rx_Left_HSIOM_UART_SEL;
                pinsDm  [Rx_Left_MISO_SDA_TX_PIN_INDEX] = Rx_Left_PIN_DM_OD_LO;
            }
            else /* Standard or IrDA */
            {
                if(0u != (Rx_Left_UART_RX_PIN_ENABLE & uartEnableMask))
                {
                    hsiomSel[Rx_Left_MOSI_SCL_RX_PIN_INDEX] = Rx_Left_HSIOM_UART_SEL;
                    pinsDm  [Rx_Left_MOSI_SCL_RX_PIN_INDEX] = Rx_Left_PIN_DM_DIG_HIZ;
                }

                if(0u != (Rx_Left_UART_TX_PIN_ENABLE & uartEnableMask))
                {
                    hsiomSel[Rx_Left_MISO_SDA_TX_PIN_INDEX] = Rx_Left_HSIOM_UART_SEL;
                    pinsDm  [Rx_Left_MISO_SDA_TX_PIN_INDEX] = Rx_Left_PIN_DM_STRONG;

                #if(Rx_Left_MISO_SDA_TX_PIN)
                     pinsInBuf |= Rx_Left_MISO_SDA_TX_PIN_MASK;
                #endif /* (Rx_Left_MISO_SDA_TX_PIN_PIN) */
                }

            #if !(Rx_Left_CY_SCBIP_V0 || Rx_Left_CY_SCBIP_V1)
                if(Rx_Left_UART_MODE_STD == subMode)
                {
                    if(0u != (Rx_Left_UART_CTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* CTS input is multiplexed with SCLK */
                        hsiomSel[Rx_Left_SCLK_PIN_INDEX] = Rx_Left_HSIOM_UART_SEL;
                        pinsDm  [Rx_Left_SCLK_PIN_INDEX] = Rx_Left_PIN_DM_DIG_HIZ;
                    }

                    if(0u != (Rx_Left_UART_RTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* RTS output is multiplexed with SS0 */
                        hsiomSel[Rx_Left_SS0_PIN_INDEX] = Rx_Left_HSIOM_UART_SEL;
                        pinsDm  [Rx_Left_SS0_PIN_INDEX] = Rx_Left_PIN_DM_STRONG;

                    #if(Rx_Left_SS0_PIN)
                        /* Disable input buffer */
                        pinsInBuf |= Rx_Left_SS0_PIN_MASK;
                    #endif /* (Rx_Left_SS0_PIN) */
                    }
                }
            #endif /* !(Rx_Left_CY_SCBIP_V0 || Rx_Left_CY_SCBIP_V1) */
            }
        }
    #endif /* (!Rx_Left_CY_SCBIP_V1) */

    /* Configure pins: set HSIOM, DM and InputBufEnable */
    /* Note: the DR register settings do not effect the pin output if HSIOM is other than GPIO */

    #if(Rx_Left_MOSI_SCL_RX_PIN)
        Rx_Left_SET_HSIOM_SEL(Rx_Left_MOSI_SCL_RX_HSIOM_REG,
                                       Rx_Left_MOSI_SCL_RX_HSIOM_MASK,
                                       Rx_Left_MOSI_SCL_RX_HSIOM_POS,
                                       hsiomSel[Rx_Left_MOSI_SCL_RX_PIN_INDEX]);

        Rx_Left_spi_mosi_i2c_scl_uart_rx_SetDriveMode((uint8) pinsDm[Rx_Left_MOSI_SCL_RX_PIN_INDEX]);

    #if (!Rx_Left_CY_SCBIP_V1)
        Rx_Left_SET_INP_DIS(Rx_Left_spi_mosi_i2c_scl_uart_rx_INP_DIS,
                                     Rx_Left_spi_mosi_i2c_scl_uart_rx_MASK,
                                     (0u != (pinsInBuf & Rx_Left_MOSI_SCL_RX_PIN_MASK)));
    #endif /* (!Rx_Left_CY_SCBIP_V1) */
    #endif /* (Rx_Left_MOSI_SCL_RX_PIN) */

    #if(Rx_Left_MOSI_SCL_RX_WAKE_PIN)
        Rx_Left_SET_HSIOM_SEL(Rx_Left_MOSI_SCL_RX_WAKE_HSIOM_REG,
                                       Rx_Left_MOSI_SCL_RX_WAKE_HSIOM_MASK,
                                       Rx_Left_MOSI_SCL_RX_WAKE_HSIOM_POS,
                                       hsiomSel[Rx_Left_MOSI_SCL_RX_WAKE_PIN_INDEX]);

        Rx_Left_spi_mosi_i2c_scl_uart_rx_wake_SetDriveMode((uint8)
                                                               pinsDm[Rx_Left_MOSI_SCL_RX_WAKE_PIN_INDEX]);

        Rx_Left_SET_INP_DIS(Rx_Left_spi_mosi_i2c_scl_uart_rx_wake_INP_DIS,
                                     Rx_Left_spi_mosi_i2c_scl_uart_rx_wake_MASK,
                                     (0u != (pinsInBuf & Rx_Left_MOSI_SCL_RX_WAKE_PIN_MASK)));

         /* Set interrupt on falling edge */
        Rx_Left_SET_INCFG_TYPE(Rx_Left_MOSI_SCL_RX_WAKE_INTCFG_REG,
                                        Rx_Left_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK,
                                        Rx_Left_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS,
                                        Rx_Left_INTCFG_TYPE_FALLING_EDGE);
    #endif /* (Rx_Left_MOSI_SCL_RX_WAKE_PIN) */

    #if(Rx_Left_MISO_SDA_TX_PIN)
        Rx_Left_SET_HSIOM_SEL(Rx_Left_MISO_SDA_TX_HSIOM_REG,
                                       Rx_Left_MISO_SDA_TX_HSIOM_MASK,
                                       Rx_Left_MISO_SDA_TX_HSIOM_POS,
                                       hsiomSel[Rx_Left_MISO_SDA_TX_PIN_INDEX]);

        Rx_Left_spi_miso_i2c_sda_uart_tx_SetDriveMode((uint8) pinsDm[Rx_Left_MISO_SDA_TX_PIN_INDEX]);

    #if (!Rx_Left_CY_SCBIP_V1)
        Rx_Left_SET_INP_DIS(Rx_Left_spi_miso_i2c_sda_uart_tx_INP_DIS,
                                     Rx_Left_spi_miso_i2c_sda_uart_tx_MASK,
                                    (0u != (pinsInBuf & Rx_Left_MISO_SDA_TX_PIN_MASK)));
    #endif /* (!Rx_Left_CY_SCBIP_V1) */
    #endif /* (Rx_Left_MOSI_SCL_RX_PIN) */

    #if(Rx_Left_SCLK_PIN)
        Rx_Left_SET_HSIOM_SEL(Rx_Left_SCLK_HSIOM_REG, Rx_Left_SCLK_HSIOM_MASK,
                                       Rx_Left_SCLK_HSIOM_POS, hsiomSel[Rx_Left_SCLK_PIN_INDEX]);

        Rx_Left_spi_sclk_SetDriveMode((uint8) pinsDm[Rx_Left_SCLK_PIN_INDEX]);

        Rx_Left_SET_INP_DIS(Rx_Left_spi_sclk_INP_DIS,
                                     Rx_Left_spi_sclk_MASK,
                                     (0u != (pinsInBuf & Rx_Left_SCLK_PIN_MASK)));
    #endif /* (Rx_Left_SCLK_PIN) */

    #if(Rx_Left_SS0_PIN)
        Rx_Left_SET_HSIOM_SEL(Rx_Left_SS0_HSIOM_REG, Rx_Left_SS0_HSIOM_MASK,
                                       Rx_Left_SS0_HSIOM_POS, hsiomSel[Rx_Left_SS0_PIN_INDEX]);

        Rx_Left_spi_ss0_SetDriveMode((uint8) pinsDm[Rx_Left_SS0_PIN_INDEX]);

        Rx_Left_SET_INP_DIS(Rx_Left_spi_ss0_INP_DIS,
                                     Rx_Left_spi_ss0_MASK,
                                     (0u != (pinsInBuf & Rx_Left_SS0_PIN_MASK)));
    #endif /* (Rx_Left_SS1_PIN) */

    #if(Rx_Left_SS1_PIN)
        Rx_Left_SET_HSIOM_SEL(Rx_Left_SS1_HSIOM_REG, Rx_Left_SS1_HSIOM_MASK,
                                       Rx_Left_SS1_HSIOM_POS, hsiomSel[Rx_Left_SS1_PIN_INDEX]);

        Rx_Left_spi_ss1_SetDriveMode((uint8) pinsDm[Rx_Left_SS1_PIN_INDEX]);

        Rx_Left_SET_INP_DIS(Rx_Left_spi_ss1_INP_DIS,
                                     Rx_Left_spi_ss1_MASK,
                                     (0u != (pinsInBuf & Rx_Left_SS1_PIN_MASK)));
    #endif /* (Rx_Left_SS1_PIN) */

    #if(Rx_Left_SS2_PIN)
        Rx_Left_SET_HSIOM_SEL(Rx_Left_SS2_HSIOM_REG, Rx_Left_SS2_HSIOM_MASK,
                                       Rx_Left_SS2_HSIOM_POS, hsiomSel[Rx_Left_SS2_PIN_INDEX]);

        Rx_Left_spi_ss2_SetDriveMode((uint8) pinsDm[Rx_Left_SS2_PIN_INDEX]);

        Rx_Left_SET_INP_DIS(Rx_Left_spi_ss2_INP_DIS,
                                     Rx_Left_spi_ss2_MASK,
                                     (0u != (pinsInBuf & Rx_Left_SS2_PIN_MASK)));
    #endif /* (Rx_Left_SS2_PIN) */

    #if(Rx_Left_SS3_PIN)
        Rx_Left_SET_HSIOM_SEL(Rx_Left_SS3_HSIOM_REG,  Rx_Left_SS3_HSIOM_MASK,
                                       Rx_Left_SS3_HSIOM_POS, hsiomSel[Rx_Left_SS3_PIN_INDEX]);

        Rx_Left_spi_ss3_SetDriveMode((uint8) pinsDm[Rx_Left_SS3_PIN_INDEX]);

        Rx_Left_SET_INP_DIS(Rx_Left_spi_ss3_INP_DIS,
                                     Rx_Left_spi_ss3_MASK,
                                     (0u != (pinsInBuf & Rx_Left_SS3_PIN_MASK)));
    #endif /* (Rx_Left_SS3_PIN) */
    }

#endif /* (Rx_Left_SCB_MODE_UNCONFIG_CONST_CFG) */


#if (Rx_Left_CY_SCBIP_V0 || Rx_Left_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: Rx_Left_I2CSlaveNackGeneration
    ********************************************************************************
    *
    * Summary:
    *  Sets command to generate NACK to the address or data.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void Rx_Left_I2CSlaveNackGeneration(void)
    {
        /* Check for EC_AM toggle condition: EC_AM and clock stretching for address are enabled */
        if ((0u != (Rx_Left_CTRL_REG & Rx_Left_CTRL_EC_AM_MODE)) &&
            (0u == (Rx_Left_I2C_CTRL_REG & Rx_Left_I2C_CTRL_S_NOT_READY_ADDR_NACK)))
        {
            /* Toggle EC_AM before NACK generation */
            Rx_Left_CTRL_REG &= ~Rx_Left_CTRL_EC_AM_MODE;
            Rx_Left_CTRL_REG |=  Rx_Left_CTRL_EC_AM_MODE;
        }

        Rx_Left_I2C_SLAVE_CMD_REG = Rx_Left_I2C_SLAVE_CMD_S_NACK;
    }
#endif /* (Rx_Left_CY_SCBIP_V0 || Rx_Left_CY_SCBIP_V1) */


/* [] END OF FILE */
