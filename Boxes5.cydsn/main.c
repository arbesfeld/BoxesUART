/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>

typedef enum {SIDE_LEFT, SIDE_RIGHT, SIDE_BACK, SIDE_FRONT, SIDE_TOP, SIDE_BOTTOM} Side;
typedef enum {ORIENT_N, ORIENT_E, ORIENT_S, ORIENT_W, ORIENT_UNKNOWN} Orientation;

void DisplayChar(Side side, Orientation orientation) {
    LCD_ClearDisplay();
    LCD_PrintString("Side: ");
    LCD_PrintInt8(side);
    LCD_Position(1, 0);
    LCD_PrintString("Orient: ");
    LCD_PrintInt8(orientation);
};

Orientation OrientationFromReg(uint8 orientation) {
    switch (orientation) {
        case 1:
            return ORIENT_N;
        case 2:
            return ORIENT_E;
        case 4:
            return ORIENT_S;
        case 8:
            return ORIENT_W;
    }
    
    return ORIENT_UNKNOWN;
        
}
void ProcessChar(char c, Side side, Orientation orientation) {
    if (c == '1') {
        LED_Write(1);   
    } else {
        LED_Write(0);
    }
    
    if (orientation == ORIENT_UNKNOWN) {
        // TODO: handle this??    
    }
    
    DisplayChar(side, orientation);
};

CY_ISR_PROTO(isr_Rx_Left_Int);
CY_ISR(isr_Rx_Left_Int) {
    while (Rx_Left_GetRxBufferSize()) {
        ProcessChar(Rx_Left_GetChar(), SIDE_LEFT, OrientationFromReg(Rx_Left_Register_Read()));
    }
}

CY_ISR_PROTO(isr_Rx_Right_Int);
CY_ISR(isr_Rx_Right_Int) {
    while (Rx_Right_GetRxBufferSize()) {
        ProcessChar(Rx_Right_GetChar(), SIDE_RIGHT, OrientationFromReg(Rx_Right_Register_Read()));
    }
}

CY_ISR_PROTO(isr_Rx_Front_Int);
CY_ISR(isr_Rx_Front_Int) {
    while (Rx_Front_GetRxBufferSize()) {
        ProcessChar(Rx_Front_GetChar(), SIDE_FRONT, OrientationFromReg(Rx_Front_Register_Read()));
    }
}

CY_ISR_PROTO(isr_Rx_Back_Int);
CY_ISR(isr_Rx_Back_Int) {
    while (Rx_Back_GetRxBufferSize()) {
        ProcessChar(Rx_Back_GetChar(), SIDE_BACK, OrientationFromReg(Rx_Back_Register_Read()));
    }
}

CY_ISR_PROTO(isr_Rx_Top_Int);
CY_ISR(isr_Rx_Top_Int) {
    while (Rx_Top_GetRxBufferSize()) {
        ProcessChar(Rx_Top_GetChar(), SIDE_TOP, OrientationFromReg(Rx_Top_Register_Read()));
    }
}

CY_ISR_PROTO(isr_Rx_Bottom_Int);
CY_ISR(isr_Rx_Bottom_Int) {
    while (Rx_Bottom_GetRxBufferSize()) {
        ProcessChar(Rx_Bottom_GetChar(), SIDE_BOTTOM, OrientationFromReg(Rx_Bottom_Register_Read()));
    }
}

int main()
{
    StartupLED_Write(1);
    CyDelay(500);
    StartupLED_Write(0);
    CyDelay(500);
    StartupLED_Write(1);
    CyDelay(500);
    StartupLED_Write(0);
    
    Rx_Front_Start();
    Rx_Left_Start();
    Rx_Back_Start();
    Rx_Right_Start();
    Rx_Top_Start();
    Rx_Bottom_Start();
    
    isr_Rx_Front_StartEx(isr_Rx_Front_Int);
    isr_Rx_Back_StartEx(isr_Rx_Back_Int);
    isr_Rx_Left_StartEx(isr_Rx_Left_Int);
    isr_Rx_Right_StartEx(isr_Rx_Right_Int);
    isr_Rx_Top_StartEx(isr_Rx_Top_Int);
    isr_Rx_Bottom_StartEx(isr_Rx_Bottom_Int);
    
    LCD_Start();
	LCD_ClearDisplay();
    
    CyGlobalIntEnable;
    
    uint8 prev = -1;
    for(;;) {
        uint8 pos = Button_Read();
        if (pos != prev) {
            Tx_PutChar(pos ? '1' : '0');
            prev = pos;
        }
    }
}