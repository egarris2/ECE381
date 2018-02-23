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
#include "project.h"
#include <string.h>

CY_ISR_PROTO(byteReceived);
CY_ISR_PROTO(clearString);
     
char menu = 0x30;
char subMenu = 0x30;
char stringNum = 0x00;
int updateFlag;
int i = 0;
int x = 0;
int y = 0;
int entry = 0;


char string1[17] = "";
char string2[17] = "";
char string3[17] = "";
char string4[17] = "";
char empty[17] = "";
char input[17] = "";
char nextByte;

int main(void)
{
    LCD_Start();
    UART_Start();
    isr_1_StartEx(byteReceived);
    CLR_STR_ISR_StartEx(clearString);
    UART_PutString("\n\rSelect an option\n\r1) Write\n\r2) Read\n\r3) Display \n\r");
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    string1[4] = 0x00;
    LCD_PrintString("\r");
    
    for(;;)
    {
        if(updateFlag){
            updateFlag = 0;
            switch(menu){
                case 0x30 :
                        UART_PutString("\n\rSelect an option\n\r1) Write\n\r2) Read\n\r3) Display \n\r");
                    break;
                case 0x31 :
                        UART_PutString("\n\rWhich String would you like to write to?\n\r");
                        menu = 0x34;
                    break;
                case 0x32 :
                        UART_PutString("\n\rWhich String would you like to read?\n\r");
                        menu = 0x035;
                    break;
                case 0x33 :
                        UART_PutString("\n\rWhich String would you like to display?\n\r");
                        menu = 0x36;
                    break;
                        
                case 0x34 :
                        if(entry == 0){
                            UART_PutString("\n\rWriting to string:\n\r");
                            entry = 1;
                        }
                        
                        else{
                            for (i = 0; i < 17; i++){
                                switch (stringNum){
                                case 0x01 :
                                        string1[i] = input[i];
                                    break;
                                case 0x02 :
                                        string2[i] = input[i];
                                    break;
                                case 0x03 :
                                        string3[i] = input[i];
                                    break;
                                case 0x04 :
                                        string4[i] = input[i];
                                    break;
                                }      
                            }
                            for(y = 0; y< 17; y++){
                                input[y] = 0x00;
                            }
                            entry = 0;
                            menu = 0x30;
                            updateFlag = 1;
                        }
                break;
                case 0x35 :
                    
                        UART_PutString("\n\rReading String:\n\r");
                                
                            switch (stringNum){
                            case 0x01 :
                                    UART_PutString(string1);
                                break;
                            case 0x02 :
                                    UART_PutString(string2);
                                break;
                            case 0x03 :
                                    UART_PutString(string3);
                                break;
                            case 0x04 :
                                    UART_PutString(string4);
                                break;
                            }
                            UART_PutString("\n");
                            menu = 0x30;  
                    
                        
                break;
                case 0x36 :
                        UART_PutString("\n\rDisplaying String:\n\r"); 
                        
                            LCD_ClearDisplay();
                            
                            switch (stringNum){
                            case 0x01 :                                    
                                    LCD_PrintString(string1);
                                break;
                            case 0x02 :
                                    LCD_PrintString(string2);
                                break;
                            case 0x03 :
                                    LCD_PrintString(string3);
                                break;  
                            case 0x04 :
                                    LCD_PrintString(string4);
                                break;
                            }                            
                            menu = 0x30;
                break;
            }
        }         
    }
}

CY_ISR(byteReceived){
    nextByte = UART_GetChar(); 
    if(x < 17){
        UART_PutChar(nextByte);
        if (nextByte != 0x0D){
            input[x] = nextByte;
        }
        x++;
    }
    else{
        
        if(nextByte == 0x7F){
            UART_PutChar(nextByte);
            input[x] = nextByte;
            x++;
        }
        else{
            UART_PutChar(0x07);
        }
    }
    
    if(nextByte == 0x7F || nextByte == 0x08){
        UART_PutChar(0x08);
        UART_PutChar(0x08);
        UART_PutChar(0x20);
        UART_PutChar(0x20);
        UART_PutChar(0x08);
        UART_PutChar(0x08);
        
//        if(x > 1){
//            x--;
//            input[x] = 0x00;
//        }
        if(x > 0){
            x-=2;
            input[x] = 0x00;
        }
    }
    if (nextByte == 0x0D){
        input[x--] = 0;
        x = 0;
        UART_PutString("\n\r");
        updateFlag = 1;
    }
    
    
    else{
        if(menu == 0x30){
            menu = input[0];
        }   
        
        else if(menu == 0x34 && entry == 0){
            stringNum = input[0] - 0x30;
        }
        
        else if(menu == 0x35 && entry == 0){
            stringNum = input[0] - 0x30;
        }
    }
}

CY_ISR(clearString){
    int k;
    CyDelay(10);
    for(k = 0; k<17; k++){
        string1[k] = empty[k];
        string2[k] = empty[k];
        string3[k] = empty[k];
        string4[k] = empty[k];
    }
    UART_PutString("All strings have been cleared!\n\r");
    SW1_ClearInterrupt();
}
        

/* [] END OF FILE */

