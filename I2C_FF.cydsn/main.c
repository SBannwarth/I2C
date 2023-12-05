/*******************************************************************
* Copyright         : 11/2023  Stephan Bannwarth
* File Name         : main.c
* Description       : Simple I2C Write on an Portexpander, toggling an LED
* Hardware          : FreeSoC2, MCP23008
* 
* Further Resoureces: MCP23008 Datasheet, Rev. E August 2007
*
* Revision History  :
* 16.11.23      Stephan Bannwarth       Tidy Up Version
* 03.12.23      Stephan Bannwarth       Consistent naming with presentation
* ------------------------------------------------------------------
* ToDo
*  
*
******************************************************************/

#include "project.h"

// Function Prototypes
uint8 I2C_MCP_Write(uint8 icAdr, uint8 regAdr, uint8 regData);


// Global variables
volatile uint8 g_flagTimer250m=0;
uint32_t g_systick = 0;


// Interrupt callbacks
CY_ISR(isr_systick)
{
	g_systick++;
    if(g_systick >= 250)
    {
        g_flagTimer250m = 1;
        g_systick = 0;
    }
}



int main(void)
{
    /******************
    * Initialization
    *******************/
    
    // Variables
    uint8 adress_MCP = 0x00;
    uint8 value_LED = 0x01;
    
    // Componente StartUps
    I2C_Start();    

        
    // Start Up Interrupts
    CySysTickStart();                        /* Start the systick */
    CySysTickSetCallback(0, isr_systick);    /* Add the Systick callback */
    CyGlobalIntEnable;                       /* Enable global interrupts. */
    
    
    /******************
    * Program Start
    *******************/
        
    
    //  MCP23017 Configuration, see regDatasheet for (Reg, Value)
    adress_MCP = 0x25; // 0x25 = 0b0100101, adr = b0100A2A1A0 hier: A2=1, A1=0, A0=1 -> Datasheet, p15
    I2C_MCP_Write(adress_MCP,0x05,0x20);   // 1. sequential operation off: (0x05, 0x20)
    I2C_MCP_Write(adress_MCP,0x00,0x00);   // 2. Port  A is output: (0x00,0x00;)
    
        
    for(;;)
    {
        
        if(g_flagTimer250m == 1)
        {
            
            value_LED = value_LED^0x01;
            I2C_MCP_Write(adress_MCP,0x09,value_LED); 
            
            //HeartBeat_Write(~HeartBeat_Read());
            
            g_flagTimer250m = 0;
        }
             
    
    }
    
    
}

uint8 I2C_MCP_Write(uint8 icAdr, uint8 regAdr, uint8 regData)
{
    /****************************************
    *   Description: Adresses an I2C Device, uses a 8-Bit Register adress, 
    *               and writes 8Bit data to the register
    * 
    *   Implementation: 
    *               "PSoC® 5LP Architecture TRM", Rev F, --> 26.7.2 Single Master Transmit"
    *               "PSoC® 5LP Registers TRM" Rev. G
    *****************************************/
     
    /******************
    * Initialization and Configuration
    *******************/
    
    uint8 status = 0;
    uint8 CtrlByte = 0;
    
              
    CY_SET_REG8(I2C_XCFG_PTR,0b10000000);   // enable I2C interface
    CY_SET_REG8(I2C_CSR_PTR, 0b00000000);   // clear status register
    CY_SET_REG8(I2C_CFG_PTR, 0b00000010);   // set Master Mode active
    
    
    /*********************************************** 
    // Start Condition & Device Adress & R/W
    ************************************************/
    
    // Device Adress and R/W Bit
    CtrlByte = (icAdr << 1)^0x00;  //0x00: Write 0x01: Read
        
    // Control
    CY_SET_REG8(I2C_DATA_PTR,CtrlByte);
    CY_SET_REG8(I2C_MCSR_PTR,0b00000001);   //On bus: Generate Start Condition, Adress, R/W
    
    
    
    while(0 == (CY_GET_REG8(I2C_CSR_PTR) & I2C_CSR_BYTE_COMPLETE))  // ?
        {
        }
    
    if(0 == (CY_GET_REG8(I2C_CSR_PTR) & I2C_CSR_LRB_NAK)) // Ackwnoleged?
    {
        status = 0; // Acknowleged
    }
    else
    {
        status = 1; // not Acknowleged
        return status;
    }
    
    /*********************************************** 
    // data Byte i Transfer
    ************************************************/
    
    for(uint8 i=1;i < 3; i++)
    {
        switch(i){
        case 1: CY_SET_REG8(I2C_DATA_PTR,regAdr); break;    // Register Adresse
        case 2: CY_SET_REG8(I2C_DATA_PTR,regData); break;      // data
        default: status = 99; break;
        }
    
        CY_SET_REG8(I2C_CSR_PTR, 0b00000100); // Send a Byte on Bus
        
        
        while(0 == (CY_GET_REG8(I2C_CSR_PTR) & I2C_CSR_BYTE_COMPLETE))  // wait until transfer complete
            {
            }
        
        if(0 == (CY_GET_REG8(I2C_CSR_PTR) & I2C_CSR_LRB_NAK)) // Ackwnoleged?
            {
                status = 0;
            }
        else
            {
                status = 1;
                return status;
            }
    }
    
    /*********************************************** 
    // Stop Condition
    ************************************************/
    
    CY_SET_REG8(I2C_CSR_PTR, 0b00000000); // Generate a stop condition, -> Regiset TRM, I2C_MCSR:stop_gen
    
    
    // Succesful transfer ?
    
    if((CY_GET_REG8(I2C_CSR_PTR) & I2C_CSR_STOP_STATUS))
    {
        status = 0;
    }else if((CY_GET_REG8(I2C_CSR_PTR) & I2C_CSR_BUS_ERROR)){
        status =  2;
        return status;
    }
    
    // 
    
    return status;
}

/* [] END OF FILE */
