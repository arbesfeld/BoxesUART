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

#define Tx_PutChar Rx_Right_UartPutChar

typedef enum {LEFT, RIGHT, BACK, FRONT} Side;

uint8 m_orientation[4] = {-1, -1, -1, -1};

void ProcessChar(char c, Side side) {
    if (c == '1') {
        LED_Write(1);   
    } else {
        LED_Write(0);
    }
    
    RGBLed_Write(m_orientation[side]);
    switch (side) {
    case LEFT:
        //RGBLed_Write(0);
        break;
    case RIGHT:
        //RGBLed_Write(1);
        break;
    case BACK:
        //RGBLed_Write(2);
        break;
    case FRONT:
        //RGBLed_Write(3);
        break;
    }
};

CY_ISR_PROTO(isr_Rx_Left_Int);
CY_ISR(isr_Rx_Left_Int) {
    while (Rx_Left_SpiUartGetRxBufferSize()) {
        ProcessChar(Rx_Left_UartGetChar(), LEFT);
    }
    Rx_Left_ClearRxInterruptSource(Rx_Left_INTR_RX_ALL);
}

CY_ISR_PROTO(isr_Rx_Right_Int);
CY_ISR(isr_Rx_Right_Int) {
    while (Rx_Right_SpiUartGetRxBufferSize()) {
        ProcessChar(Rx_Right_UartGetChar(), RIGHT);
    }
    
    Rx_Right_ClearRxInterruptSource(Rx_Right_INTR_RX_ALL);
}

CY_ISR_PROTO(isr_Rx_Front_Int);
CY_ISR(isr_Rx_Front_Int) {
    while (Rx_Front_GetRxBufferSize()) {
        ProcessChar(Rx_Front_GetChar(), FRONT);
    }
}

CY_ISR_PROTO(isr_Rx_Back_Int);
CY_ISR(isr_Rx_Back_Int) {
    while (Rx_Back_GetRxBufferSize()) {
        ProcessChar(Rx_Back_GetChar(), BACK);
    }
}

int main()
{
    Rx_Front_Start();
    Rx_Left_Start();
    Rx_Back_Start();
    Rx_Right_Start();
    
    Rx_Left_SetCustomInterruptHandler(isr_Rx_Left_Int);
    Rx_Right_SetCustomInterruptHandler(isr_Rx_Right_Int);
    isr_Rx_Front_StartEx(isr_Rx_Front_Int);
    isr_Rx_Back_StartEx(isr_Rx_Back_Int);
    
    CyGlobalIntEnable;
    
    uint8 prev = -1;
    for(;;) {
        uint8 pos = Button_Read();
        if (pos != prev) {
            Tx_PutChar(pos ? '1' : '0');
            prev = pos;
        }
        
        uint8 frontPins = Rx_Front_Pins_Read();
        if (frontPins != 0) {
            m_orientation[FRONT] = frontPins;
        }
        
        uint8 backPins = Rx_Back_Pins_Read();
        if (backPins != 0) {
            m_orientation[BACK] = backPins;
        }
    }
}

/* [] END OF FILE */
