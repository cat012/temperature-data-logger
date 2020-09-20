// software UART transmitter
//
// 19-Sep-2020


#ifndef UART_H_
#define	UART_H_


#include <xc.h>
#include <stdint.h>


#define TX_LED_LAT   LATDbits.LATD7
#define TX_LED_TRIS  TRISDbits.RD7


#define TX_LED_INIT  TX_LED_TRIS=0

#define TX_LED_ON   TX_LED_LAT=1
#define TX_LED_OFF  TX_LED_LAT=0


#define NUM_OF_BITS  (8+2)


inline void uart_cont(void);
void uart_init(void);
void uart_deinit(void);
void uart_char(char code);
void uart_print(const char* str);



#endif	/* UART_H_ */

