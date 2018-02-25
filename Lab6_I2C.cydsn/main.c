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

#define numOfChars  79
#define write       0
#define read        1

CY_ISR_PROTO(byteReceived);
void printInstructions();
void parseInput();
void readWriteMem();

uint8 currentMemLocation;
uint16 memLocation;

uint8 directionRW;
uint8 chipSelect;

uint8 group1Address =   80;
uint8 chip1Address  =    6;
uint8 chip2Address  =    4;

uint8 address;



uint8 format;

uint8 readNumBytes; 
uint8 writeNumBytes;

uint8 data[numOfChars];
uint8 writeData[numOfChars] = "";
uint8 readData[numOfChars];

uint8 addressW = 86;
uint8 addressR = 86;

uint8 format;


int updateFlag;
int i = 0;
int x = 0;
int y = 0;
int entry = 0;

char holding[numOfChars] = "";
char input[numOfChars] = "";
char empty[numOfChars] = "";
char nextByte;

uint8 testAdd[1] = {0x00};
uint8 testW[5] = {0x00,0x30,0x31,0x32, 0x33};
uint8 testR[4] = {1,2,3,4};

int main(void)
{
    
    UART_Start();
    I2C_Start();
    //I2C_Enable();
    
    printInstructions();
    
    isr_1_StartEx(byteReceived);
    CyGlobalIntEnable; 
    
    for(;;)
    {
        if(updateFlag){
            parseInput();
            readWriteMem();


            updateFlag = 0;
        }
    }
}

CY_ISR(byteReceived){
    //gets incoming byte from UART and stores it
    nextByte = UART_GetChar(); 
    //if the byte is a printable character & the string isn't full
    if(nextByte > 31 && nextByte < 127 && x < numOfChars){
        //echo character back to host computer 
        UART_PutChar(nextByte);
        //store character into an input buffer
        input[x] = nextByte;
        //increment to next buffer location
        x++;
    }
    
    //if byte is non printable
    else{
        //if the byte is a delete perform rubout sequence
        if(nextByte == 0x7F && x > 0){
            UART_PutChar(0x08);
            UART_PutChar(0x20);
            UART_PutChar(0x08);
            //sets input buffer location back 1 to reflect host readout
            x--;     
            //replaces deleted character with null
            input[x] = 0;
        }
        
        //if carriage return (enter) is sent
        else if(nextByte == 0x0D){
            //new line and carriage return
            UART_PutString("\n");
            UART_PutChar(nextByte);
            
            //add carriage return deliminator to input buffer
            input[x] = 0x0D;
            
            //store input array in a holding array
            for (i = 0; i < numOfChars; i++){
                holding[i] = input[i];
            }
            
            //clear input array
            for(y = 0;y < numOfChars; y++){
                input[y] = empty[y];
            }
            
            //return input buffer write location to beginning
            x = 0;
            //set flag for action in the main code
            updateFlag = 1;
        }
        
        //if byte is not printable or if input buffer is full..
        //or if trying to delete past 0 send bell to host computer
        else{
            UART_PutChar(7);
        }
    }
}
    
void printInstructions(){
    UART_PutString("\n\r Please type a command. A command will look similar to the examples below.\n\r");
    UART_PutString("\n\r W # XX A Your message here");
    UART_PutString("\n\r A # XX H NN\n\r");
    UART_PutString("\n\r W for write or R for Read");
    UART_PutString("\n\r # determines which EEPROM");
    UART_PutString("\n\r XX determines memory location (in hex)");
    UART_PutString("\n\r A for ASCII or H for ASCII encoded hex bytes");
    UART_PutString("\n\r NN for READ commands determines number of bytes (in hex) to be read\n\r");
    UART_PutString("\n\r Examples given below\n\r");
    UART_PutString("\n\r W 1 31 A Mary had a little lamb");
    UART_PutString("\n\r R 2 31 H 34\n\r");
    UART_PutString("\n\r>");
}

void parseInput(){
    if (holding[0] == 'W' || holding[0] == 'w'){
        directionRW = write;
    }
    else if(holding[0] == 'R' || holding[0] == 'r'){
        directionRW = read;
    }
    
    readNumBytes = (((holding[9] - '0') << 4) | (holding[10] - '0'));
    
    chipSelect = holding[2];
    
    memLocation = (((holding[4] - '0') << 4) | (holding[5] - '0'));
    writeData[0] = memLocation;
    format = holding[7];
    
    for (i = 9; holding[i] != 0x0D; i++){
        writeData[i-8] = holding[i];
        writeData[i-7] = 0x0D;
        
        writeNumBytes = i-8;
    }
    
    
}


void readWriteMem(){
    if(chipSelect == '1'){
        address = (group1Address | chip1Address);
    }
    
    else{
        address = (group1Address | chip2Address);
    }
    
    if(directionRW == write){
        I2C_MasterWriteBuf(address, writeData, writeNumBytes, I2C_MODE_COMPLETE_XFER);
        while(!(I2C_MasterStatus() & I2C_MSTAT_WR_CMPLT));
        I2C_MasterClearStatus();
        CyDelay(5);
    }
    
    if(directionRW == read){
        I2C_MasterWriteBuf(address, writeData, 1, I2C_MODE_COMPLETE_XFER);
        while(!(I2C_MasterStatus() & I2C_MSTAT_WR_CMPLT));
        I2C_MasterClearStatus();
        CyDelay(5);
        
        I2C_MasterReadBuf(address, readData, readNumBytes, I2C_MODE_COMPLETE_XFER);
        while(!(I2C_MasterStatus() & I2C_MSTAT_RD_CMPLT));
        I2C_MasterClearStatus();
        
        for(i = 0; i < readNumBytes; i++){
            UART_PutChar(readData[i]);
        }
        UART_PutString(">");
        //UART_PutString(holding);
        //UART_PutString("\n");
        updateFlag = 0;
    }
}