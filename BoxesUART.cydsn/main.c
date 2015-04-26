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

int main()
{
    StartupLED_Write(1);
    CyDelay(500);
    StartupLED_Write(0);
    CyDelay(500);
    StartupLED_Write(1);
    CyDelay(500);
    StartupLED_Write(0);
    CyDelay(500);
    StartupLED_Write(1);
    
    UART_1_Start();
    CyGlobalIntEnable;
    
    UART_1_LoadTxConfig(); /* Configure UART for transmitting */
    for(;;) {
        UART_1_PutChar('1'); /* Send received byte back */
        CyDelay(500);
        UART_1_PutChar('2'); /* Send received byte back */
        CyDelay(500);
    }
}
