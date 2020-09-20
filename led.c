//12-Sep-2020



#include <xc.h>
#include <stdint.h>

#include "led.h"



uint8_t ledbuff[2]={0b00000000, 0b00000000};


const uint8_t scode[] = //codes of symbols //segments: a-b-c-d-e-f-g-h
{
  0b11111100, //0  //0
  0b01100000, //1  //1
  0b11011010, //2  //2
  0b11110010, //3  //3
  0b01100110, //4  //4
  0b10110110, //5  //5
  0b10111110, //6  //6
  0b11100000, //7  //7
  0b11111110, //8  //8
  0b11110110, //9  //9
  0b00000000, //10 //space
  0b00000010, //11 //-
  0b00011100, //12 //L
  0b01111100 //13 //U
};


//-----------------------------------------------------------------------------
void led_mux(void)
    {
    static uint8_t dig=0;

    INIT_LED;

    if(REG_BIT_IS_SET(ledbuff[dig],7)) { LED_S0_LAT=0; }
    if(REG_BIT_IS_SET(ledbuff[dig],6)) { LED_S1_LAT=0; }
    if(REG_BIT_IS_SET(ledbuff[dig],5)) { LED_S2_LAT=0; }
    if(REG_BIT_IS_SET(ledbuff[dig],4)) { LED_S3_LAT=0; }
    if(REG_BIT_IS_SET(ledbuff[dig],3)) { LED_S4_LAT=0; }
    if(REG_BIT_IS_SET(ledbuff[dig],2)) { LED_S5_LAT=0; }
    if(REG_BIT_IS_SET(ledbuff[dig],1)) { LED_S6_LAT=0; }
    if(REG_BIT_IS_SET(ledbuff[dig],0)) { LED_S7_LAT=0; }

    if(dig==0) {LED_D1_LAT=0;}
    if(dig==1) {LED_D0_LAT=0;}

    if(++dig>=2) dig=0;
    }


//-----------------------------------------------------------------------------
void led_char(uint8_t pos, uint8_t sign) //print a character
    {
    uint8_t tmp=0;

    switch(sign) //select the code of symbol
        {
        case 32: tmp=scode[10]; break; //space
        case 45: tmp=scode[11]; break; //"-"
        case 48: tmp=scode[0]; break; //"0"
        case 49: tmp=scode[1]; break; //"1"
        case 50: tmp=scode[2]; break; //"2"
        case 51: tmp=scode[3]; break; //"3"
        case 52: tmp=scode[4]; break; //"4"
        case 53: tmp=scode[5]; break; //"5"
        case 54: tmp=scode[6]; break; //"6"
        case 55: tmp=scode[7]; break; //"7"
        case 56: tmp=scode[8]; break; //"8"
        case 57: tmp=scode[9]; break; //"9"
        case 76: tmp=scode[12]; break; //"L"
        case 85: tmp=scode[13]; break; //"U"
        }

    if(pos<=1) ledbuff[pos]=(tmp|(ledbuff[pos]&0b00000001));
    }


//-----------------------------------------------------------------------------
void led_print(uint8_t pos, const char *str) //print a string  //pos - 0..1
    {
    for(;*str;) led_char(pos++,*str++);
    }


//-----------------------------------------------------------------------------
void led_dot(uint8_t pos, uint8_t on)
    {
    on ? ledbuff[pos]|=1 : ledbuff[pos]&=~1;
    }


