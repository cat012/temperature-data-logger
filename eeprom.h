// 24LC16B 16K EEPROM
//
// 17-Sep-2020


#ifndef EEPROM_H_
#define EEPROM_H_


#define _XTAL_FREQ 8000000


#include <stdint.h>

#include "i2c.h"


#define EE_W  0b10100000
#define EE_R  0b10100001


#define EE_DELAY_WRITE  __delay_ms(5)


void ee_write(uint16_t addr, uint8_t data);
uint8_t ee_read(uint16_t addr);
void ee_write16(uint16_t addr, uint16_t data);
uint16_t ee_read16(uint16_t addr);
void ee_clear(void);



#endif // EEPROM_H_
