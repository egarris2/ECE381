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
#define numOfBytesInPage 16
#define write       0
#define read        1

CY_ISR_PROTO(byteReceived);
void printInstructions();
void parseInput();
void readWriteMem();

uint8 currentMemLocation;
uint8 memLocation;

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
uint8 writeData1[numOfBytesInPage + 1] = "";
uint8 writeData2[numOfBytesInPage+1] = "";
uint8 writeData3[numOfBytesInPage+1] = "";
uint8 writeData4[numOfBytesInPage+1] = "";
uint8 writeData5[numOfBytesInPage+1] = "";
uint8 readData[numOfChars];

uint8 addressW = 86;
uint8 addressR = 86;

uint8 format;


int updateFlag;
int i = 0;
int y = 0;
int x = 0;
int entry = 0;

char holding[numOfChars] = "";
char input[numOfChars] = "";
char empty[numOfChars] = "";
char nextByte;


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
            UART_PutString("\r\n>");

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
            
            //UART_PutString(holding);
            //clear input array
            for(x = 0;x < numOfChars; x++){
                input[x] = empty[x];
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
    writeData1[0] = memLocation;
    writeData2[0] = memLocation + numOfBytesInPage;
    writeData3[0] = memLocation + numOfBytesInPage*2;
    writeData4[0] = memLocation + numOfBytesInPage*3;
    writeData5[0] = memLocation + numOfBytesInPage*4;
    format = holding[7];
    
    if(format == 'a'){
        for (i = 9; holding[i] != 0x0D; i++){
            if(i < 25){
                writeData1[i-8] = holding[i];
            }
            else if(i < 41){
                writeData2[i-24] = holding[i];
            }
            else if(i < 57){
                writeData3[i-40] = holding[i];
            }
            else if(i < 73){
                writeData4[i-56] = holding[i];
            }
            else if(i < 89){
                writeData5[i-72] = holding[i];
            }
            writeNumBytes = i-6;
        }
    }
    
    else if(format == 'h'){

        for (y = 9, i = 9; holding[i] != 0x0D; y+=3, i++){
            if(i < 25){
                writeData1[i-8] = ((holding[y] - '0') << 4) | (holding[y+1]-'0');
            }
            else if(i < 41){
                writeData2[i-24] = ((holding[y] - '0') << 4) | (holding[y+1]-'0');
            }
            else if(i < 57){
                writeData3[i-40] = ((holding[y] - '0') << 4) | (holding[y+1]-'0');
            }
            else if(i < 73){
                writeData4[i-56] = ((holding[y] - '0') << 4) | (holding[y+1]-'0');
            }
            else if(i < 89){
                writeData5[i-72] = ((holding[y] - '0') << 4) | (holding[y+1]-'0');
            }
            writeNumBytes = i-6;
            
        }
    }
    
    /*UART_PutString("\r\n");
    for (i = 0; i < 20; i++){
        UART_PutChar(writeData1[i]);
    }
    UART_PutString("\r\n");*/
    
}


void readWriteMem(){
    if(chipSelect == '1'){
        address = (group1Address | chip1Address);
    }
    
    else{
        address = (group1Address | chip2Address);
    }
    
    if(directionRW == write){
        I2C_MasterWriteBuf(address, writeData1, numOfBytesInPage + 1, I2C_MODE_COMPLETE_XFER);
        while(!(I2C_MasterStatus() & I2C_MSTAT_WR_CMPLT));
        I2C_MasterClearStatus();
        CyDelay(5);
        
        I2C_MasterWriteBuf(address, writeData2, numOfBytesInPage + 1, I2C_MODE_COMPLETE_XFER);
        while(!(I2C_MasterStatus() & I2C_MSTAT_WR_CMPLT));
        I2C_MasterClearStatus();
        CyDelay(5);
        
        I2C_MasterWriteBuf(address, writeData3, numOfBytesInPage + 1, I2C_MODE_COMPLETE_XFER);
        while(!(I2C_MasterStatus() & I2C_MSTAT_WR_CMPLT));
        I2C_MasterClearStatus();
        CyDelay(5);
        
        I2C_MasterWriteBuf(address, writeData4, numOfBytesInPage + 1, I2C_MODE_COMPLETE_XFER);
        while(!(I2C_MasterStatus() & I2C_MSTAT_WR_CMPLT));
        I2C_MasterClearStatus();
        CyDelay(5);
        
        I2C_MasterWriteBuf(address, writeData5, numOfBytesInPage + 1, I2C_MODE_COMPLETE_XFER);
        while(!(I2C_MasterStatus() & I2C_MSTAT_WR_CMPLT));
        I2C_MasterClearStatus();
        CyDelay(5);
    }
    
    if(directionRW == read){
        I2C_MasterWriteBuf(address, writeData1, 1, I2C_MODE_COMPLETE_XFER);
        while(!(I2C_MasterStatus() & I2C_MSTAT_WR_CMPLT));
        I2C_MasterClearStatus();
        CyDelay(5);
        
        I2C_MasterReadBuf(address, readData, readNumBytes, I2C_MODE_COMPLETE_XFER);
        while(!(I2C_MasterStatus() & I2C_MSTAT_RD_CMPLT));
        I2C_MasterClearStatus();
        
        if(format == 'a'){
            for(i = 0; i < readNumBytes; i++){
                UART_PutChar(readData[i]);
            }
        }
        
        else if(format == 'h'){
            for(i = 0; i < readNumBytes; i++){
                
                UART_PutChar((((readData[i]) & 0xF0) >> 4) + '0');
                UART_PutChar((readData[i] & 0x0F) + '0');
                UART_PutChar(0x20);
            }
        }
        
        //UART_PutString(holding);
        //UART_PutString("\n");
        updateFlag = 0;
    }
}