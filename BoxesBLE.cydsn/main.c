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


CY_ISR_PROTO(isr_UART_1_Int);
CY_ISR(isr_UART_1_Int) {
    while(UART_1_GetRxBufferSize()) {
        char myChar = UART_1_GetChar();
        if (myChar == '1') {
            LED_Write(1);   
        } else {
            LED_Write(0);
        }
    }
}

int main()
{
    CyGlobalIntEnable;
    uint8 recByte;
    uint8 tmpStat;
    UART_1_Start();
    
    /* Alternatively, check TX_STS_COMPLETE status bit */
    UART_1_LoadRxConfig();
    
    while (1) {
        recByte = UART_1_GetChar();
        if (recByte > 0) {
            if (recByte == '1') {
                LED_Write(1);   
            } else if (recByte == '2') {
                LED_Write(0);
            }
            
            /*
            UART_1_LoadTxConfig();
            UART_1_PutChar(recByte);
            do {
                tmpStat = UART_1_ReadTxStatus();
            } while (~tmpStat & UART_1_TX_STS_COMPLETE); 
            */
            
            //UART_1_LoadRxConfig();
        }
    }
}
