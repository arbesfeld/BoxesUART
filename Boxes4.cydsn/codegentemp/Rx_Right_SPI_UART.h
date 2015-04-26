/*******************************************************************************
* File Name: Rx_Right_SPI_UART.h
* Version 2.0
*
* Description:
*  This file provides constants and parameter values for the SCB Component in
*  SPI and UART modes.
*
* Note:
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_SPI_UART_Rx_Right_H)
#define CY_SCB_SPI_UART_Rx_Right_H

#include "Rx_Right.h"


/***************************************
*   SPI Initial Parameter Constants
****************************************/

#define Rx_Right_SPI_MODE                   (0u)
#define Rx_Right_SPI_SUB_MODE               (0u)
#define Rx_Right_SPI_CLOCK_MODE             (0u)
#define Rx_Right_SPI_OVS_FACTOR             (16u)
#define Rx_Right_SPI_MEDIAN_FILTER_ENABLE   (0u)
#define Rx_Right_SPI_LATE_MISO_SAMPLE_ENABLE (0u)
#define Rx_Right_SPI_RX_DATA_BITS_NUM       (8u)
#define Rx_Right_SPI_TX_DATA_BITS_NUM       (8u)
#define Rx_Right_SPI_WAKE_ENABLE            (0u)
#define Rx_Right_SPI_BITS_ORDER             (1u)
#define Rx_Right_SPI_TRANSFER_SEPARATION    (1u)
#define Rx_Right_SPI_NUMBER_OF_SS_LINES     (1u)
#define Rx_Right_SPI_RX_BUFFER_SIZE         (8u)
#define Rx_Right_SPI_TX_BUFFER_SIZE         (8u)

#define Rx_Right_SPI_INTERRUPT_MODE         (0u)

#define Rx_Right_SPI_INTR_RX_MASK           (0u)
#define Rx_Right_SPI_INTR_TX_MASK           (0u)

#define Rx_Right_SPI_RX_TRIGGER_LEVEL       (7u)
#define Rx_Right_SPI_TX_TRIGGER_LEVEL       (0u)

#define Rx_Right_SPI_BYTE_MODE_ENABLE       (0u)
#define Rx_Right_SPI_FREE_RUN_SCLK_ENABLE   (0u)
#define Rx_Right_SPI_SS0_POLARITY           (0u)
#define Rx_Right_SPI_SS1_POLARITY           (0u)
#define Rx_Right_SPI_SS2_POLARITY           (0u)
#define Rx_Right_SPI_SS3_POLARITY           (0u)


/***************************************
*   UART Initial Parameter Constants
****************************************/

#define Rx_Right_UART_SUB_MODE              (0u)
#define Rx_Right_UART_DIRECTION             (3u)
#define Rx_Right_UART_DATA_BITS_NUM         (8u)
#define Rx_Right_UART_PARITY_TYPE           (0u)
#define Rx_Right_UART_STOP_BITS_NUM         (2u)
#define Rx_Right_UART_OVS_FACTOR            (12u)
#define Rx_Right_UART_IRDA_LOW_POWER        (0u)
#define Rx_Right_UART_MEDIAN_FILTER_ENABLE  (0u)
#define Rx_Right_UART_RETRY_ON_NACK         (0u)
#define Rx_Right_UART_IRDA_POLARITY         (0u)
#define Rx_Right_UART_DROP_ON_FRAME_ERR     (0u)
#define Rx_Right_UART_DROP_ON_PARITY_ERR    (0u)
#define Rx_Right_UART_WAKE_ENABLE           (0u)
#define Rx_Right_UART_RX_BUFFER_SIZE        (8u)
#define Rx_Right_UART_TX_BUFFER_SIZE        (8u)
#define Rx_Right_UART_MP_MODE_ENABLE        (0u)
#define Rx_Right_UART_MP_ACCEPT_ADDRESS     (0u)
#define Rx_Right_UART_MP_RX_ADDRESS         (2u)
#define Rx_Right_UART_MP_RX_ADDRESS_MASK    (255u)

#define Rx_Right_UART_INTERRUPT_MODE        (1u)

#define Rx_Right_UART_INTR_RX_MASK          (4u)
#define Rx_Right_UART_INTR_TX_MASK          (0u)

#define Rx_Right_UART_RX_TRIGGER_LEVEL      (7u)
#define Rx_Right_UART_TX_TRIGGER_LEVEL      (0u)

#define Rx_Right_UART_BYTE_MODE_ENABLE      (0u)
#define Rx_Right_UART_CTS_ENABLE            (0u)
#define Rx_Right_UART_CTS_POLARITY          (0u)
#define Rx_Right_UART_RTS_POLARITY          (0u)
#define Rx_Right_UART_RTS_FIFO_LEVEL        (4u)

/* SPI mode enum */
#define Rx_Right_SPI_SLAVE  (0u)
#define Rx_Right_SPI_MASTER (1u)

/* UART direction enum */
#define Rx_Right_UART_RX    (1u)
#define Rx_Right_UART_TX    (2u)
#define Rx_Right_UART_TX_RX (3u)


/***************************************
*   Conditional Compilation Parameters
****************************************/

#if(Rx_Right_SCB_MODE_UNCONFIG_CONST_CFG)

    /* Mode */
    #define Rx_Right_SPI_MASTER_CONST       (1u)

    /* Direction */
    #define Rx_Right_RX_DIRECTION           (1u)
    #define Rx_Right_TX_DIRECTION           (1u)
    #define Rx_Right_UART_RX_DIRECTION      (1u)
    #define Rx_Right_UART_TX_DIRECTION      (1u)

    /* Only external RX and TX buffer for Uncofigured mode */
    #define Rx_Right_INTERNAL_RX_SW_BUFFER   (0u)
    #define Rx_Right_INTERNAL_TX_SW_BUFFER   (0u)

    /* Get RX and TX buffer size */
    #define Rx_Right_RX_BUFFER_SIZE (Rx_Right_rxBufferSize)
    #define Rx_Right_TX_BUFFER_SIZE (Rx_Right_txBufferSize)

    /* Return true if buffer is provided */
    #define Rx_Right_CHECK_RX_SW_BUFFER (NULL != Rx_Right_rxBuffer)
    #define Rx_Right_CHECK_TX_SW_BUFFER (NULL != Rx_Right_txBuffer)

    /* Always provide global variables to support RX and TX buffers */
    #define Rx_Right_INTERNAL_RX_SW_BUFFER_CONST    (1u)
    #define Rx_Right_INTERNAL_TX_SW_BUFFER_CONST    (1u)

    /* Get wakeup enable option */
    #define Rx_Right_SPI_WAKE_ENABLE_CONST  (1u)
    #define Rx_Right_CHECK_SPI_WAKE_ENABLE  (0u != Rx_Right_scbEnableWake)
    #define Rx_Right_UART_WAKE_ENABLE_CONST (1u)

    /* SPI/UART: TX or RX FIFO size */
    #if (Rx_Right_CY_SCBIP_V0 || Rx_Right_CY_SCBIP_V1)
        #define Rx_Right_SPI_UART_FIFO_SIZE (Rx_Right_FIFO_SIZE)
    #else
        #define Rx_Right_SPI_UART_FIFO_SIZE (Rx_Right_GET_FIFO_SIZE(Rx_Right_CTRL_REG & \
                                                                                    Rx_Right_CTRL_BYTE_MODE))
    #endif /* (Rx_Right_CY_SCBIP_V0 || Rx_Right_CY_SCBIP_V1) */

#else

    /* Internal RX and TX buffer: for SPI or UART */
    #if (Rx_Right_SCB_MODE_SPI_CONST_CFG)

        /* SPI Direction */
        #define Rx_Right_SPI_RX_DIRECTION (1u)
        #define Rx_Right_SPI_TX_DIRECTION (1u)

        /* Get FIFO size */
        #if (Rx_Right_CY_SCBIP_V0 || Rx_Right_CY_SCBIP_V1)
            #define Rx_Right_SPI_UART_FIFO_SIZE    (Rx_Right_FIFO_SIZE)
        #else
            #define Rx_Right_SPI_UART_FIFO_SIZE \
                                           Rx_Right_GET_FIFO_SIZE(Rx_Right_SPI_BYTE_MODE_ENABLE)

        #endif /* (Rx_Right_CY_SCBIP_V0 || Rx_Right_CY_SCBIP_V1) */

        /* SPI internal RX and TX buffers */
        #define Rx_Right_INTERNAL_SPI_RX_SW_BUFFER  (Rx_Right_SPI_RX_BUFFER_SIZE > \
                                                                Rx_Right_SPI_UART_FIFO_SIZE)
        #define Rx_Right_INTERNAL_SPI_TX_SW_BUFFER  (Rx_Right_SPI_TX_BUFFER_SIZE > \
                                                                Rx_Right_SPI_UART_FIFO_SIZE)

        /* Internal SPI RX and TX buffer */
        #define Rx_Right_INTERNAL_RX_SW_BUFFER  (Rx_Right_INTERNAL_SPI_RX_SW_BUFFER)
        #define Rx_Right_INTERNAL_TX_SW_BUFFER  (Rx_Right_INTERNAL_SPI_TX_SW_BUFFER)

        /* Internal SPI RX and TX buffer size */
        #define Rx_Right_RX_BUFFER_SIZE         (Rx_Right_SPI_RX_BUFFER_SIZE + 1u)
        #define Rx_Right_TX_BUFFER_SIZE         (Rx_Right_SPI_TX_BUFFER_SIZE)

        /* Get wakeup enable option */
        #define Rx_Right_SPI_WAKE_ENABLE_CONST  (0u != Rx_Right_SPI_WAKE_ENABLE)
        #define Rx_Right_UART_WAKE_ENABLE_CONST (0u)

    #else

        /* UART Direction */
        #define Rx_Right_UART_RX_DIRECTION (0u != (Rx_Right_UART_DIRECTION & Rx_Right_UART_RX))
        #define Rx_Right_UART_TX_DIRECTION (0u != (Rx_Right_UART_DIRECTION & Rx_Right_UART_TX))

        /* Get FIFO size */
        #if (Rx_Right_CY_SCBIP_V0 || Rx_Right_CY_SCBIP_V1)
            #define Rx_Right_SPI_UART_FIFO_SIZE    (Rx_Right_FIFO_SIZE)
        #else
            #define Rx_Right_SPI_UART_FIFO_SIZE \
                                           Rx_Right_GET_FIFO_SIZE(Rx_Right_UART_BYTE_MODE_ENABLE)
        #endif /* (Rx_Right_CY_SCBIP_V0 || Rx_Right_CY_SCBIP_V1) */

        /* UART internal RX and TX buffers */
        #define Rx_Right_INTERNAL_UART_RX_SW_BUFFER  (Rx_Right_UART_RX_BUFFER_SIZE > \
                                                                Rx_Right_SPI_UART_FIFO_SIZE)
        #define Rx_Right_INTERNAL_UART_TX_SW_BUFFER  (Rx_Right_UART_TX_BUFFER_SIZE > \
                                                                    Rx_Right_SPI_UART_FIFO_SIZE)

        /* Internal UART RX and TX buffer */
        #define Rx_Right_INTERNAL_RX_SW_BUFFER  (Rx_Right_INTERNAL_UART_RX_SW_BUFFER)
        #define Rx_Right_INTERNAL_TX_SW_BUFFER  (Rx_Right_INTERNAL_UART_TX_SW_BUFFER)

        /* Internal UART RX and TX buffer size */
        #define Rx_Right_RX_BUFFER_SIZE         (Rx_Right_UART_RX_BUFFER_SIZE + 1u)
        #define Rx_Right_TX_BUFFER_SIZE         (Rx_Right_UART_TX_BUFFER_SIZE)

        /* Get wakeup enable option */
        #define Rx_Right_SPI_WAKE_ENABLE_CONST  (0u)
        #define Rx_Right_UART_WAKE_ENABLE_CONST (0u != Rx_Right_UART_WAKE_ENABLE)

    #endif /* (Rx_Right_SCB_MODE_SPI_CONST_CFG) */

    /* Mode */
    #define Rx_Right_SPI_MASTER_CONST   (Rx_Right_SPI_MODE == Rx_Right_SPI_MASTER)

    /* Direction */
    #define Rx_Right_RX_DIRECTION ((Rx_Right_SCB_MODE_SPI_CONST_CFG) ? \
                                            (Rx_Right_SPI_RX_DIRECTION) : (Rx_Right_UART_RX_DIRECTION))

    #define Rx_Right_TX_DIRECTION ((Rx_Right_SCB_MODE_SPI_CONST_CFG) ? \
                                            (Rx_Right_SPI_TX_DIRECTION) : (Rx_Right_UART_TX_DIRECTION))

    /* Internal RX and TX buffer: for SPI or UART. Used in conditional compilation check */
    #define Rx_Right_CHECK_RX_SW_BUFFER (Rx_Right_INTERNAL_RX_SW_BUFFER)
    #define Rx_Right_CHECK_TX_SW_BUFFER (Rx_Right_INTERNAL_TX_SW_BUFFER)

    /* Provide global variables to support RX and TX buffers */
    #define Rx_Right_INTERNAL_RX_SW_BUFFER_CONST    (Rx_Right_INTERNAL_RX_SW_BUFFER)
    #define Rx_Right_INTERNAL_TX_SW_BUFFER_CONST    (Rx_Right_INTERNAL_TX_SW_BUFFER)

    /* Wakeup for SPI */
    #define Rx_Right_CHECK_SPI_WAKE_ENABLE  (Rx_Right_SPI_WAKE_ENABLE_CONST)

#endif /* End (Rx_Right_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*       Type Definitions
***************************************/

/* Rx_Right_SPI_INIT_STRUCT */
typedef struct
{
    uint32 mode;
    uint32 submode;
    uint32 sclkMode;
    uint32 oversample;
    uint32 enableMedianFilter;
    uint32 enableLateSampling;
    uint32 enableWake;
    uint32 rxDataBits;
    uint32 txDataBits;
    uint32 bitOrder;
    uint32 transferSeperation;
    uint32 rxBufferSize;
    uint8* rxBuffer;
    uint32 txBufferSize;
    uint8* txBuffer;
    uint32 enableInterrupt;
    uint32 rxInterruptMask;
    uint32 rxTriggerLevel;
    uint32 txInterruptMask;
    uint32 txTriggerLevel;
    uint8 enableByteMode;
    uint8 enableFreeRunSclk;
    uint8 polaritySs;
} Rx_Right_SPI_INIT_STRUCT;

/* Rx_Right_UART_INIT_STRUCT */
typedef struct
{
    uint32 mode;
    uint32 direction;
    uint32 dataBits;
    uint32 parity;
    uint32 stopBits;
    uint32 oversample;
    uint32 enableIrdaLowPower;
    uint32 enableMedianFilter;
    uint32 enableRetryNack;
    uint32 enableInvertedRx;
    uint32 dropOnParityErr;
    uint32 dropOnFrameErr;
    uint32 enableWake;
    uint32 rxBufferSize;
    uint8* rxBuffer;
    uint32 txBufferSize;
    uint8* txBuffer;
    uint32 enableMultiproc;
    uint32 multiprocAcceptAddr;
    uint32 multiprocAddr;
    uint32 multiprocAddrMask;
    uint32 enableInterrupt;
    uint32 rxInterruptMask;
    uint32 rxTriggerLevel;
    uint32 txInterruptMask;
    uint32 txTriggerLevel;
    uint8 enableByteMode;
    uint8 enableCts;
    uint8 ctsPolarity;
    uint8 rtsRxFifoLevel;
    uint8 rtsPolarity;
} Rx_Right_UART_INIT_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

/* SPI specific functions */
#if(Rx_Right_SCB_MODE_UNCONFIG_CONST_CFG)
    void Rx_Right_SpiInit(const Rx_Right_SPI_INIT_STRUCT *config);
#endif /* (Rx_Right_SCB_MODE_UNCONFIG_CONST_CFG) */

#if(Rx_Right_SCB_MODE_SPI_INC)
    #define Rx_Right_SpiIsBusBusy() ((uint32) (0u != (Rx_Right_SPI_STATUS_REG & \
                                                              Rx_Right_SPI_STATUS_BUS_BUSY)))

    #if (Rx_Right_SPI_MASTER_CONST)
        void Rx_Right_SpiSetActiveSlaveSelect(uint32 slaveSelect);
    #endif /*(Rx_Right_SPI_MASTER_CONST) */

    #if !(Rx_Right_CY_SCBIP_V0 || Rx_Right_CY_SCBIP_V1)
        void Rx_Right_SpiSetSlaveSelectPolarity(uint32 slaveSelect, uint32 polarity);
    #endif /* !(Rx_Right_CY_SCBIP_V0 || Rx_Right_CY_SCBIP_V1) */
#endif /* (Rx_Right_SCB_MODE_SPI_INC) */

/* UART specific functions */
#if(Rx_Right_SCB_MODE_UNCONFIG_CONST_CFG)
    void Rx_Right_UartInit(const Rx_Right_UART_INIT_STRUCT *config);
#endif /* (Rx_Right_SCB_MODE_UNCONFIG_CONST_CFG) */

#if(Rx_Right_SCB_MODE_UART_INC)
    void Rx_Right_UartSetRxAddress(uint32 address);
    void Rx_Right_UartSetRxAddressMask(uint32 addressMask);

    /* UART RX direction APIs */
    #if(Rx_Right_UART_RX_DIRECTION)
        uint32 Rx_Right_UartGetChar(void);
        uint32 Rx_Right_UartGetByte(void);

        #if !(Rx_Right_CY_SCBIP_V0 || Rx_Right_CY_SCBIP_V1)
            /* UART APIs for Flow Control */
            void Rx_Right_UartSetRtsPolarity(uint32 polarity);
            void Rx_Right_UartSetRtsFifoLevel(uint32 level);
        #endif /* !(Rx_Right_CY_SCBIP_V0 || Rx_Right_CY_SCBIP_V1) */
    #endif /* (Rx_Right_UART_RX_DIRECTION) */

    /* UART TX direction APIs */
    #if(Rx_Right_UART_TX_DIRECTION)
        #define Rx_Right_UartPutChar(ch)    Rx_Right_SpiUartWriteTxData((uint32)(ch))
        void Rx_Right_UartPutString(const char8 string[]);
        void Rx_Right_UartPutCRLF(uint32 txDataByte);

        #if !(Rx_Right_CY_SCBIP_V0 || Rx_Right_CY_SCBIP_V1)
            /* UART APIs for Flow Control */
            void Rx_Right_UartEnableCts(void);
            void Rx_Right_UartDisableCts(void);
            void Rx_Right_UartSetCtsPolarity(uint32 polarity);
        #endif /* !(Rx_Right_CY_SCBIP_V0 || Rx_Right_CY_SCBIP_V1) */
    #endif /* (Rx_Right_UART_TX_DIRECTION) */
#endif /* (Rx_Right_SCB_MODE_UART_INC) */

/* Common APIs RX direction */
#if(Rx_Right_RX_DIRECTION)
    uint32 Rx_Right_SpiUartReadRxData(void);
    uint32 Rx_Right_SpiUartGetRxBufferSize(void);
    void   Rx_Right_SpiUartClearRxBuffer(void);
#endif /* (Rx_Right_RX_DIRECTION) */

/* Common APIs TX direction */
#if(Rx_Right_TX_DIRECTION)
    void   Rx_Right_SpiUartWriteTxData(uint32 txData);
    void   Rx_Right_SpiUartPutArray(const uint8 wrBuf[], uint32 count);
    void   Rx_Right_SpiUartClearTxBuffer(void);
    uint32 Rx_Right_SpiUartGetTxBufferSize(void);
#endif /* (Rx_Right_TX_DIRECTION) */

CY_ISR_PROTO(Rx_Right_SPI_UART_ISR);

#if(Rx_Right_UART_RX_WAKEUP_IRQ)
    CY_ISR_PROTO(Rx_Right_UART_WAKEUP_ISR);
#endif /* (Rx_Right_UART_RX_WAKEUP_IRQ) */


/***************************************
*     Buffer Access Macro Definitions
***************************************/

#if(Rx_Right_SCB_MODE_UNCONFIG_CONST_CFG)
    /* RX direction */
    void   Rx_Right_PutWordInRxBuffer  (uint32 idx, uint32 rxDataByte);
    uint32 Rx_Right_GetWordFromRxBuffer(uint32 idx);

    /* TX direction */
    void   Rx_Right_PutWordInTxBuffer  (uint32 idx, uint32 txDataByte);
    uint32 Rx_Right_GetWordFromTxBuffer(uint32 idx);

#else
    /* RX direction */
    #if(Rx_Right_INTERNAL_RX_SW_BUFFER_CONST)
        #define Rx_Right_PutWordInRxBuffer(idx, rxDataByte) \
                do{                                                 \
                    Rx_Right_rxBufferInternal[(idx)] = ((uint8) (rxDataByte)); \
                }while(0)

        #define Rx_Right_GetWordFromRxBuffer(idx) Rx_Right_rxBufferInternal[(idx)]

    #endif /* (Rx_Right_INTERNAL_RX_SW_BUFFER_CONST) */

    /* TX direction */
    #if(Rx_Right_INTERNAL_TX_SW_BUFFER_CONST)
        #define Rx_Right_PutWordInTxBuffer(idx, txDataByte) \
                    do{                                             \
                        Rx_Right_txBufferInternal[(idx)] = ((uint8) (txDataByte)); \
                    }while(0)

        #define Rx_Right_GetWordFromTxBuffer(idx) Rx_Right_txBufferInternal[(idx)]

    #endif /* (Rx_Right_INTERNAL_TX_SW_BUFFER_CONST) */

#endif /* (Rx_Right_TX_SW_BUFFER_ENABLE) */


/***************************************
*         SPI API Constants
***************************************/

/* SPI sub mode enum */
#define Rx_Right_SPI_MODE_MOTOROLA      (0x00u)
#define Rx_Right_SPI_MODE_TI_COINCIDES  (0x01u)
#define Rx_Right_SPI_MODE_TI_PRECEDES   (0x11u)
#define Rx_Right_SPI_MODE_NATIONAL      (0x02u)
#define Rx_Right_SPI_MODE_MASK          (0x03u)
#define Rx_Right_SPI_MODE_TI_PRECEDES_MASK  (0x10u)
#define Rx_Right_SPI_MODE_NS_MICROWIRE  (Rx_Right_SPI_MODE_NATIONAL)

/* SPI phase and polarity mode enum */
#define Rx_Right_SPI_SCLK_CPHA0_CPOL0   (0x00u)
#define Rx_Right_SPI_SCLK_CPHA0_CPOL1   (0x02u)
#define Rx_Right_SPI_SCLK_CPHA1_CPOL0   (0x01u)
#define Rx_Right_SPI_SCLK_CPHA1_CPOL1   (0x03u)

/* SPI bits order enum */
#define Rx_Right_BITS_ORDER_LSB_FIRST   (0u)
#define Rx_Right_BITS_ORDER_MSB_FIRST   (1u)

/* SPI transfer separation enum */
#define Rx_Right_SPI_TRANSFER_SEPARATED     (0u)
#define Rx_Right_SPI_TRANSFER_CONTINUOUS    (1u)

/* SPI slave select constants */
#define Rx_Right_SPI_SLAVE_SELECT0    (Rx_Right_SCB__SS0_POSISTION)
#define Rx_Right_SPI_SLAVE_SELECT1    (Rx_Right_SCB__SS1_POSISTION)
#define Rx_Right_SPI_SLAVE_SELECT2    (Rx_Right_SCB__SS2_POSISTION)
#define Rx_Right_SPI_SLAVE_SELECT3    (Rx_Right_SCB__SS3_POSISTION)

/* SPI slave select polarity settings */
#define Rx_Right_SPI_SS_ACTIVE_LOW  (0u)
#define Rx_Right_SPI_SS_ACTIVE_HIGH (1u)


/***************************************
*         UART API Constants
***************************************/

/* UART sub-modes enum */
#define Rx_Right_UART_MODE_STD          (0u)
#define Rx_Right_UART_MODE_SMARTCARD    (1u)
#define Rx_Right_UART_MODE_IRDA         (2u)

/* UART direction enum */
#define Rx_Right_UART_RX    (1u)
#define Rx_Right_UART_TX    (2u)
#define Rx_Right_UART_TX_RX (3u)

/* UART parity enum */
#define Rx_Right_UART_PARITY_EVEN   (0u)
#define Rx_Right_UART_PARITY_ODD    (1u)
#define Rx_Right_UART_PARITY_NONE   (2u)

/* UART stop bits enum */
#define Rx_Right_UART_STOP_BITS_1   (2u)
#define Rx_Right_UART_STOP_BITS_1_5 (3u)
#define Rx_Right_UART_STOP_BITS_2   (4u)

/* UART IrDA low power OVS enum */
#define Rx_Right_UART_IRDA_LP_OVS16     (16u)
#define Rx_Right_UART_IRDA_LP_OVS32     (32u)
#define Rx_Right_UART_IRDA_LP_OVS48     (48u)
#define Rx_Right_UART_IRDA_LP_OVS96     (96u)
#define Rx_Right_UART_IRDA_LP_OVS192    (192u)
#define Rx_Right_UART_IRDA_LP_OVS768    (768u)
#define Rx_Right_UART_IRDA_LP_OVS1536   (1536u)

/* Uart MP: mark (address) and space (data) bit definitions */
#define Rx_Right_UART_MP_MARK       (0x100u)
#define Rx_Right_UART_MP_SPACE      (0x000u)

/* UART CTS/RTS polarity settings */
#define Rx_Right_UART_CTS_ACTIVE_LOW    (0u)
#define Rx_Right_UART_CTS_ACTIVE_HIGH   (1u)
#define Rx_Right_UART_RTS_ACTIVE_LOW    (0u)
#define Rx_Right_UART_RTS_ACTIVE_HIGH   (1u)

/* Sources of RX errors */
#define Rx_Right_INTR_RX_ERR        (Rx_Right_INTR_RX_OVERFLOW    | \
                                             Rx_Right_INTR_RX_UNDERFLOW   | \
                                             Rx_Right_INTR_RX_FRAME_ERROR | \
                                             Rx_Right_INTR_RX_PARITY_ERROR)

/* Shifted INTR_RX_ERR defines ONLY for Rx_Right_UartGetByte() */
#define Rx_Right_UART_RX_OVERFLOW       (Rx_Right_INTR_RX_OVERFLOW << 8u)
#define Rx_Right_UART_RX_UNDERFLOW      (Rx_Right_INTR_RX_UNDERFLOW << 8u)
#define Rx_Right_UART_RX_FRAME_ERROR    (Rx_Right_INTR_RX_FRAME_ERROR << 8u)
#define Rx_Right_UART_RX_PARITY_ERROR   (Rx_Right_INTR_RX_PARITY_ERROR << 8u)
#define Rx_Right_UART_RX_ERROR_MASK     (Rx_Right_UART_RX_OVERFLOW    | \
                                                 Rx_Right_UART_RX_UNDERFLOW   | \
                                                 Rx_Right_UART_RX_FRAME_ERROR | \
                                                 Rx_Right_UART_RX_PARITY_ERROR)


/***************************************
*     Vars with External Linkage
***************************************/

#if(Rx_Right_SCB_MODE_UNCONFIG_CONST_CFG)
    extern const Rx_Right_SPI_INIT_STRUCT  Rx_Right_configSpi;
    extern const Rx_Right_UART_INIT_STRUCT Rx_Right_configUart;
#endif /* (Rx_Right_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*    Specific SPI Macro Definitions
***************************************/

#define Rx_Right_GET_SPI_INTR_SLAVE_MASK(sourceMask)  ((sourceMask) & Rx_Right_INTR_SLAVE_SPI_BUS_ERROR)
#define Rx_Right_GET_SPI_INTR_MASTER_MASK(sourceMask) ((sourceMask) & Rx_Right_INTR_MASTER_SPI_DONE)
#define Rx_Right_GET_SPI_INTR_RX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~Rx_Right_INTR_SLAVE_SPI_BUS_ERROR)

#define Rx_Right_GET_SPI_INTR_TX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~Rx_Right_INTR_MASTER_SPI_DONE)


/***************************************
*    Specific UART Macro Definitions
***************************************/

#define Rx_Right_UART_GET_CTRL_OVS_IRDA_LP(oversample) \
        ((Rx_Right_UART_IRDA_LP_OVS16   == (oversample)) ? Rx_Right_CTRL_OVS_IRDA_LP_OVS16 : \
         ((Rx_Right_UART_IRDA_LP_OVS32   == (oversample)) ? Rx_Right_CTRL_OVS_IRDA_LP_OVS32 : \
          ((Rx_Right_UART_IRDA_LP_OVS48   == (oversample)) ? Rx_Right_CTRL_OVS_IRDA_LP_OVS48 : \
           ((Rx_Right_UART_IRDA_LP_OVS96   == (oversample)) ? Rx_Right_CTRL_OVS_IRDA_LP_OVS96 : \
            ((Rx_Right_UART_IRDA_LP_OVS192  == (oversample)) ? Rx_Right_CTRL_OVS_IRDA_LP_OVS192 : \
             ((Rx_Right_UART_IRDA_LP_OVS768  == (oversample)) ? Rx_Right_CTRL_OVS_IRDA_LP_OVS768 : \
              ((Rx_Right_UART_IRDA_LP_OVS1536 == (oversample)) ? Rx_Right_CTRL_OVS_IRDA_LP_OVS1536 : \
                                                                          Rx_Right_CTRL_OVS_IRDA_LP_OVS16)))))))

#define Rx_Right_GET_UART_RX_CTRL_ENABLED(direction) ((0u != (Rx_Right_UART_RX & (direction))) ? \
                                                                     (Rx_Right_RX_CTRL_ENABLED) : (0u))

#define Rx_Right_GET_UART_TX_CTRL_ENABLED(direction) ((0u != (Rx_Right_UART_TX & (direction))) ? \
                                                                     (Rx_Right_TX_CTRL_ENABLED) : (0u))


/***************************************
*        SPI Register Settings
***************************************/

#define Rx_Right_CTRL_SPI      (Rx_Right_CTRL_MODE_SPI)
#define Rx_Right_SPI_RX_CTRL   (Rx_Right_RX_CTRL_ENABLED)
#define Rx_Right_SPI_TX_CTRL   (Rx_Right_TX_CTRL_ENABLED)


/***************************************
*       SPI Init Register Settings
***************************************/

#define Rx_Right_SPI_SS_POLARITY \
             (((uint32) Rx_Right_SPI_SS0_POLARITY << Rx_Right_SPI_SLAVE_SELECT0) | \
              ((uint32) Rx_Right_SPI_SS1_POLARITY << Rx_Right_SPI_SLAVE_SELECT1) | \
              ((uint32) Rx_Right_SPI_SS2_POLARITY << Rx_Right_SPI_SLAVE_SELECT2) | \
              ((uint32) Rx_Right_SPI_SS3_POLARITY << Rx_Right_SPI_SLAVE_SELECT3))

#if(Rx_Right_SCB_MODE_SPI_CONST_CFG)

    /* SPI Configuration */
    #define Rx_Right_SPI_DEFAULT_CTRL \
                    (Rx_Right_GET_CTRL_OVS(Rx_Right_SPI_OVS_FACTOR) | \
                     Rx_Right_GET_CTRL_BYTE_MODE (Rx_Right_SPI_BYTE_MODE_ENABLE) | \
                     Rx_Right_GET_CTRL_EC_AM_MODE(Rx_Right_SPI_WAKE_ENABLE)      | \
                     Rx_Right_CTRL_SPI)

    #define Rx_Right_SPI_DEFAULT_SPI_CTRL \
                    (Rx_Right_GET_SPI_CTRL_CONTINUOUS    (Rx_Right_SPI_TRANSFER_SEPARATION)       | \
                     Rx_Right_GET_SPI_CTRL_SELECT_PRECEDE(Rx_Right_SPI_SUB_MODE &                   \
                                                                  Rx_Right_SPI_MODE_TI_PRECEDES_MASK)     | \
                     Rx_Right_GET_SPI_CTRL_SCLK_MODE     (Rx_Right_SPI_CLOCK_MODE)                | \
                     Rx_Right_GET_SPI_CTRL_LATE_MISO_SAMPLE(Rx_Right_SPI_LATE_MISO_SAMPLE_ENABLE) | \
                     Rx_Right_GET_SPI_CTRL_SCLK_CONTINUOUS(Rx_Right_SPI_FREE_RUN_SCLK_ENABLE)     | \
                     Rx_Right_GET_SPI_CTRL_SSEL_POLARITY (Rx_Right_SPI_SS_POLARITY)               | \
                     Rx_Right_GET_SPI_CTRL_SUB_MODE      (Rx_Right_SPI_SUB_MODE)                  | \
                     Rx_Right_GET_SPI_CTRL_MASTER_MODE   (Rx_Right_SPI_MODE))

    /* RX direction */
    #define Rx_Right_SPI_DEFAULT_RX_CTRL \
                    (Rx_Right_GET_RX_CTRL_DATA_WIDTH(Rx_Right_SPI_RX_DATA_BITS_NUM)     | \
                     Rx_Right_GET_RX_CTRL_BIT_ORDER (Rx_Right_SPI_BITS_ORDER)           | \
                     Rx_Right_GET_RX_CTRL_MEDIAN    (Rx_Right_SPI_MEDIAN_FILTER_ENABLE) | \
                     Rx_Right_SPI_RX_CTRL)

    #define Rx_Right_SPI_DEFAULT_RX_FIFO_CTRL \
                    Rx_Right_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(Rx_Right_SPI_RX_TRIGGER_LEVEL)

    /* TX direction */
    #define Rx_Right_SPI_DEFAULT_TX_CTRL \
                    (Rx_Right_GET_TX_CTRL_DATA_WIDTH(Rx_Right_SPI_TX_DATA_BITS_NUM) | \
                     Rx_Right_GET_TX_CTRL_BIT_ORDER (Rx_Right_SPI_BITS_ORDER)       | \
                     Rx_Right_SPI_TX_CTRL)

    #define Rx_Right_SPI_DEFAULT_TX_FIFO_CTRL \
                    Rx_Right_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(Rx_Right_SPI_TX_TRIGGER_LEVEL)

    /* Interrupt sources */
    #define Rx_Right_SPI_DEFAULT_INTR_SPI_EC_MASK   (Rx_Right_NO_INTR_SOURCES)

    #define Rx_Right_SPI_DEFAULT_INTR_I2C_EC_MASK   (Rx_Right_NO_INTR_SOURCES)
    #define Rx_Right_SPI_DEFAULT_INTR_SLAVE_MASK \
                    (Rx_Right_SPI_INTR_RX_MASK & Rx_Right_INTR_SLAVE_SPI_BUS_ERROR)

    #define Rx_Right_SPI_DEFAULT_INTR_MASTER_MASK \
                    (Rx_Right_SPI_INTR_TX_MASK & Rx_Right_INTR_MASTER_SPI_DONE)

    #define Rx_Right_SPI_DEFAULT_INTR_RX_MASK \
                    (Rx_Right_SPI_INTR_RX_MASK & (uint32) ~Rx_Right_INTR_SLAVE_SPI_BUS_ERROR)

    #define Rx_Right_SPI_DEFAULT_INTR_TX_MASK \
                    (Rx_Right_SPI_INTR_TX_MASK & (uint32) ~Rx_Right_INTR_MASTER_SPI_DONE)

#endif /* (Rx_Right_SCB_MODE_SPI_CONST_CFG) */


/***************************************
*        UART Register Settings
***************************************/

#define Rx_Right_CTRL_UART      (Rx_Right_CTRL_MODE_UART)
#define Rx_Right_UART_RX_CTRL   (Rx_Right_RX_CTRL_LSB_FIRST) /* LSB for UART goes first */
#define Rx_Right_UART_TX_CTRL   (Rx_Right_TX_CTRL_LSB_FIRST) /* LSB for UART goes first */


/***************************************
*      UART Init Register Settings
***************************************/

#if(Rx_Right_SCB_MODE_UART_CONST_CFG)

    /* UART configuration */
    #if(Rx_Right_UART_MODE_IRDA == Rx_Right_UART_SUB_MODE)

        #define Rx_Right_DEFAULT_CTRL_OVS   ((0u != Rx_Right_UART_IRDA_LOW_POWER) ?              \
                                (Rx_Right_UART_GET_CTRL_OVS_IRDA_LP(Rx_Right_UART_OVS_FACTOR)) : \
                                (Rx_Right_CTRL_OVS_IRDA_OVS16))

    #else

        #define Rx_Right_DEFAULT_CTRL_OVS   Rx_Right_GET_CTRL_OVS(Rx_Right_UART_OVS_FACTOR)

    #endif /* (Rx_Right_UART_MODE_IRDA == Rx_Right_UART_SUB_MODE) */

    #define Rx_Right_UART_DEFAULT_CTRL \
                                (Rx_Right_GET_CTRL_BYTE_MODE  (Rx_Right_UART_BYTE_MODE_ENABLE)  | \
                                 Rx_Right_GET_CTRL_ADDR_ACCEPT(Rx_Right_UART_MP_ACCEPT_ADDRESS) | \
                                 Rx_Right_DEFAULT_CTRL_OVS                                              | \
                                 Rx_Right_CTRL_UART)

    #define Rx_Right_UART_DEFAULT_UART_CTRL \
                                    (Rx_Right_GET_UART_CTRL_MODE(Rx_Right_UART_SUB_MODE))

    /* RX direction */
    #define Rx_Right_UART_DEFAULT_RX_CTRL_PARITY \
                                ((Rx_Right_UART_PARITY_NONE != Rx_Right_UART_PARITY_TYPE) ?      \
                                  (Rx_Right_GET_UART_RX_CTRL_PARITY(Rx_Right_UART_PARITY_TYPE) | \
                                   Rx_Right_UART_RX_CTRL_PARITY_ENABLED) : (0u))

    #define Rx_Right_UART_DEFAULT_UART_RX_CTRL \
                    (Rx_Right_GET_UART_RX_CTRL_MODE(Rx_Right_UART_STOP_BITS_NUM)                    | \
                     Rx_Right_GET_UART_RX_CTRL_POLARITY(Rx_Right_UART_IRDA_POLARITY)                | \
                     Rx_Right_GET_UART_RX_CTRL_MP_MODE(Rx_Right_UART_MP_MODE_ENABLE)                | \
                     Rx_Right_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(Rx_Right_UART_DROP_ON_PARITY_ERR) | \
                     Rx_Right_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(Rx_Right_UART_DROP_ON_FRAME_ERR)   | \
                     Rx_Right_UART_DEFAULT_RX_CTRL_PARITY)

    #define Rx_Right_UART_DEFAULT_RX_CTRL \
                                (Rx_Right_GET_RX_CTRL_DATA_WIDTH(Rx_Right_UART_DATA_BITS_NUM)        | \
                                 Rx_Right_GET_RX_CTRL_MEDIAN    (Rx_Right_UART_MEDIAN_FILTER_ENABLE) | \
                                 Rx_Right_GET_UART_RX_CTRL_ENABLED(Rx_Right_UART_DIRECTION))

    #define Rx_Right_UART_DEFAULT_RX_FIFO_CTRL \
                                Rx_Right_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(Rx_Right_UART_RX_TRIGGER_LEVEL)

    #define Rx_Right_UART_DEFAULT_RX_MATCH_REG  ((0u != Rx_Right_UART_MP_MODE_ENABLE) ?          \
                                (Rx_Right_GET_RX_MATCH_ADDR(Rx_Right_UART_MP_RX_ADDRESS) | \
                                 Rx_Right_GET_RX_MATCH_MASK(Rx_Right_UART_MP_RX_ADDRESS_MASK)) : (0u))

    /* TX direction */
    #define Rx_Right_UART_DEFAULT_TX_CTRL_PARITY (Rx_Right_UART_DEFAULT_RX_CTRL_PARITY)

    #define Rx_Right_UART_DEFAULT_UART_TX_CTRL \
                                (Rx_Right_GET_UART_TX_CTRL_MODE(Rx_Right_UART_STOP_BITS_NUM)       | \
                                 Rx_Right_GET_UART_TX_CTRL_RETRY_NACK(Rx_Right_UART_RETRY_ON_NACK) | \
                                 Rx_Right_UART_DEFAULT_TX_CTRL_PARITY)

    #define Rx_Right_UART_DEFAULT_TX_CTRL \
                                (Rx_Right_GET_TX_CTRL_DATA_WIDTH(Rx_Right_UART_DATA_BITS_NUM) | \
                                 Rx_Right_GET_UART_TX_CTRL_ENABLED(Rx_Right_UART_DIRECTION))

    #define Rx_Right_UART_DEFAULT_TX_FIFO_CTRL \
                                Rx_Right_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(Rx_Right_UART_TX_TRIGGER_LEVEL)

    #define Rx_Right_UART_DEFAULT_FLOW_CTRL \
                        (Rx_Right_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(Rx_Right_UART_RTS_FIFO_LEVEL) | \
                         Rx_Right_GET_UART_FLOW_CTRL_RTS_POLARITY (Rx_Right_UART_RTS_POLARITY)   | \
                         Rx_Right_GET_UART_FLOW_CTRL_CTS_POLARITY (Rx_Right_UART_CTS_POLARITY)   | \
                         Rx_Right_GET_UART_FLOW_CTRL_CTS_ENABLE   (Rx_Right_UART_CTS_ENABLE))

    /* Interrupt sources */
    #define Rx_Right_UART_DEFAULT_INTR_I2C_EC_MASK  (Rx_Right_NO_INTR_SOURCES)
    #define Rx_Right_UART_DEFAULT_INTR_SPI_EC_MASK  (Rx_Right_NO_INTR_SOURCES)
    #define Rx_Right_UART_DEFAULT_INTR_SLAVE_MASK   (Rx_Right_NO_INTR_SOURCES)
    #define Rx_Right_UART_DEFAULT_INTR_MASTER_MASK  (Rx_Right_NO_INTR_SOURCES)
    #define Rx_Right_UART_DEFAULT_INTR_RX_MASK      (Rx_Right_UART_INTR_RX_MASK)
    #define Rx_Right_UART_DEFAULT_INTR_TX_MASK      (Rx_Right_UART_INTR_TX_MASK)

#endif /* (Rx_Right_SCB_MODE_UART_CONST_CFG) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

#define Rx_Right_SPIM_ACTIVE_SS0    (Rx_Right_SPI_SLAVE_SELECT0)
#define Rx_Right_SPIM_ACTIVE_SS1    (Rx_Right_SPI_SLAVE_SELECT1)
#define Rx_Right_SPIM_ACTIVE_SS2    (Rx_Right_SPI_SLAVE_SELECT2)
#define Rx_Right_SPIM_ACTIVE_SS3    (Rx_Right_SPI_SLAVE_SELECT3)

#endif /* CY_SCB_SPI_UART_Rx_Right_H */


/* [] END OF FILE */
