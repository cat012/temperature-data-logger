// 1-Wire interface for DS18B20
// Compiler: XC8 v1.33
// 11-Sep-2020


#ifndef DS18B20_H_
#define DS18B20_H_


#define _XTAL_FREQ 8000000


#include <xc.h>
#include <stdint.h>



///////////////////////////////////////////////////////////////////////////////

#define DS18B20_LAT   LATAbits.LATA1
#define DS18B20_PIN   PORTAbits.RA1
#define DS18B20_TRIS  TRISAbits.RA1

///////////////////////////////////////////////////////////////////////////////


#define DS18B20_INPUT   DS18B20_TRIS=1
#define DS18B20_OUTPUT  DS18B20_TRIS=0
#define DS18B20_LOW     DS18B20_LAT=0
#define DS18B20_HIGH    DS18B20_LAT=1

#define DS18B20_INPUT_PULL  DS18B20_LOW; DS18B20_INPUT
#define DS18B20_OUTPUT_LOW  DS18B20_LOW; DS18B20_OUTPUT

#define DS18B20_OUTPUT_HIGH  DS18B20_HIGH; DS18B20_OUTPUT


#define DS18B20_PIN_INIT  DS18B20_INPUT_PULL


#define CMD_CONVERTTEMP 0x44
#define CMD_RSCRATCHPAD 0xbe
#define CMD_SKIPROM 0xcc



uint8_t trm_start(void);
uint8_t trm_read(uint8_t *data);  //data[3]: 0-"+/-"(0/1), 1-"XX.x", 2-"xx.X"



#endif /* DS18B20_H_ */