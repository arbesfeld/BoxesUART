/*******************************************************************************
* File Name: UART_Rx_Right_tx.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_UART_Rx_Right_tx_H) /* Pins UART_Rx_Right_tx_H */
#define CY_PINS_UART_Rx_Right_tx_H

#include "cytypes.h"
#include "cyfitter.h"
#include "UART_Rx_Right_tx_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    UART_Rx_Right_tx_Write(uint8 value) ;
void    UART_Rx_Right_tx_SetDriveMode(uint8 mode) ;
uint8   UART_Rx_Right_tx_ReadDataReg(void) ;
uint8   UART_Rx_Right_tx_Read(void) ;
uint8   UART_Rx_Right_tx_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define UART_Rx_Right_tx_DRIVE_MODE_BITS        (3)
#define UART_Rx_Right_tx_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - UART_Rx_Right_tx_DRIVE_MODE_BITS))

#define UART_Rx_Right_tx_DM_ALG_HIZ         (0x00u)
#define UART_Rx_Right_tx_DM_DIG_HIZ         (0x01u)
#define UART_Rx_Right_tx_DM_RES_UP          (0x02u)
#define UART_Rx_Right_tx_DM_RES_DWN         (0x03u)
#define UART_Rx_Right_tx_DM_OD_LO           (0x04u)
#define UART_Rx_Right_tx_DM_OD_HI           (0x05u)
#define UART_Rx_Right_tx_DM_STRONG          (0x06u)
#define UART_Rx_Right_tx_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define UART_Rx_Right_tx_MASK               UART_Rx_Right_tx__MASK
#define UART_Rx_Right_tx_SHIFT              UART_Rx_Right_tx__SHIFT
#define UART_Rx_Right_tx_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define UART_Rx_Right_tx_PS                     (* (reg32 *) UART_Rx_Right_tx__PS)
/* Port Configuration */
#define UART_Rx_Right_tx_PC                     (* (reg32 *) UART_Rx_Right_tx__PC)
/* Data Register */
#define UART_Rx_Right_tx_DR                     (* (reg32 *) UART_Rx_Right_tx__DR)
/* Input Buffer Disable Override */
#define UART_Rx_Right_tx_INP_DIS                (* (reg32 *) UART_Rx_Right_tx__PC2)


#if defined(UART_Rx_Right_tx__INTSTAT)  /* Interrupt Registers */

    #define UART_Rx_Right_tx_INTSTAT                (* (reg32 *) UART_Rx_Right_tx__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define UART_Rx_Right_tx_DRIVE_MODE_SHIFT       (0x00u)
#define UART_Rx_Right_tx_DRIVE_MODE_MASK        (0x07u << UART_Rx_Right_tx_DRIVE_MODE_SHIFT)


#endif /* End Pins UART_Rx_Right_tx_H */


/* [] END OF FILE */
