// 20-Sep-2020


#include "eeprom.h"



//-----------------------------------------------------------------------------
void ee_write(uint16_t addr, uint8_t data)
    {
    i2c_start();
    i2c_send_byte(EE_W | ((addr&0x700)>>7));  //device address | write | bank
    i2c_send_byte(addr);  //word address
    i2c_send_byte(data);  //write data word
    i2c_stop();

    EE_DELAY_WRITE;
    }


//-----------------------------------------------------------------------------
uint8_t ee_read(uint16_t addr)
    {
    uint8_t data = 0;

    i2c_start();
    i2c_send_byte(EE_W | ((addr&0x700)>>7));  //device address | write | bank
    i2c_send_byte(addr);  //word address

    i2c_start();
    i2c_send_byte(EE_R | ((addr&0x700)>>7));     //device address | read | bank
    data = i2c_read_byte(I2C_NACK);
    i2c_stop();

    return data;
    }


//-----------------------------------------------------------------------------
void ee_write16(uint16_t addr, uint16_t data)
    {
    ee_write(addr, data>>8);
    ee_write(addr+1, data);
    }


//-----------------------------------------------------------------------------
uint16_t ee_read16(uint16_t addr)
    {
    return (ee_read(addr)<<8) | ee_read(addr+1);
    }


//-----------------------------------------------------------------------------
void ee_clear(void)
    {
    for(uint16_t k=0; k<2048; k++) ee_write(k, 0xff);
    }




