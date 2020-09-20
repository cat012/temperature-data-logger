// 11-Sep-2020


#include "ds18b20.h"


//-----------------------------------------------------------------------------
static uint8_t ds18b20_reset(void)
    {
    DS18B20_OUTPUT_LOW;
    __delay_us(250);
    __delay_us(250);

    DS18B20_INPUT_PULL;
    __delay_us(60);

    uint8_t err = DS18B20_PIN;

    __delay_us(250);
    __delay_us(250);

    return err;  //0 = OK
    }


//-----------------------------------------------------------------------------
static void ds18b20_write_bit(uint8_t data)
    {
    GIE=0;

    DS18B20_OUTPUT_LOW;
    __delay_us(5);

    if(data) { DS18B20_INPUT_PULL; }

    __delay_us(55);
    DS18B20_INPUT_PULL;

    __delay_us(5);

    GIE=1;
    }


//-----------------------------------------------------------------------------
static uint8_t ds18b20_read_bit(void)
    {
    uint8_t data=0;

    GIE=0;

    DS18B20_OUTPUT_LOW;
    __delay_us(5);

    DS18B20_INPUT_PULL;
    __delay_us(5);

    if(DS18B20_PIN) data=1;

    __delay_us(55);

    GIE=1;

    return data;
    }


//-----------------------------------------------------------------------------
static uint8_t ds18b20_read_byte(void)
    {
    uint8_t data = 0;
    for(uint8_t k=0; k<8; k++) data|=(ds18b20_read_bit()<<k);
    return data;
    }


//-----------------------------------------------------------------------------
static void ds18b20_write_byte(uint8_t byte)
    {
    for(uint8_t mask=1; mask; mask<<=1) ds18b20_write_bit(byte & mask);
    }


//-----------------------------------------------------------------------------
uint8_t trm_start(void)
    {
    uint8_t err = ds18b20_reset();

    if(!err)
        {
        ds18b20_write_byte(CMD_SKIPROM);
        ds18b20_write_byte(CMD_CONVERTTEMP);

        DS18B20_OUTPUT_HIGH;  //for parsite power mode
        }

    return err;
    }


//-----------------------------------------------------------------------------
uint8_t trm_read(uint8_t *data)  //data[3]: 0-"+/-"(0/1), 1-"XX.x", 2-"xx.X"
    {
    DS18B20_INPUT_PULL;  //for parsite power mode

    uint8_t err = ds18b20_reset();

    if(!err)
        {
        ds18b20_write_byte(CMD_SKIPROM);
        ds18b20_write_byte(CMD_RSCRATCHPAD);

        uint8_t reg0 = ds18b20_read_byte();
        uint8_t reg1 = ds18b20_read_byte();

        uint16_t temp = ((uint16_t)(reg1<<8)|reg0);
        uint8_t sign = (temp & 0x8000)>>15;

        data[0] = sign;
        if(sign) temp = (~temp)+1;
        data[1] = ((temp & 0x700)<<4)+(temp>>4);
        data[2] = (((temp & 0xf)<<1)+((temp & 0xf)<<3))>>4;
        }

    return err;
    }


