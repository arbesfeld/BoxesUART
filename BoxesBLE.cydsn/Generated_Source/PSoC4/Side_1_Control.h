/*******************************************************************************
* File Name: Side_1_Control.h  
* Version 1.80
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CONTROL_REG_Side_1_Control_H) /* CY_CONTROL_REG_Side_1_Control_H */
#define CY_CONTROL_REG_Side_1_Control_H

#include "cytypes.h"

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 controlState;

} Side_1_Control_BACKUP_STRUCT;


/***************************************
*         Function Prototypes 
***************************************/

void    Side_1_Control_Write(uint8 control) ;
uint8   Side_1_Control_Read(void) ;

void Side_1_Control_SaveConfig(void) ;
void Side_1_Control_RestoreConfig(void) ;
void Side_1_Control_Sleep(void) ; 
void Side_1_Control_Wakeup(void) ;


/***************************************
*            Registers        
***************************************/

/* Control Register */
#define Side_1_Control_Control        (* (reg8 *) Side_1_Control_Sync_ctrl_reg__CONTROL_REG )
#define Side_1_Control_Control_PTR    (  (reg8 *) Side_1_Control_Sync_ctrl_reg__CONTROL_REG )

#endif /* End CY_CONTROL_REG_Side_1_Control_H */


/* [] END OF FILE */
