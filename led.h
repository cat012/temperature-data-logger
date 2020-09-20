// 2-digit led display 
// 12-Sep-2020


#ifndef LED_H_
#define	LED_H_


///////////////////////////////////////////////////////////////////////////////

#define LED_D0_TRIS  TRISAbits.RA5
#define LED_D0_LAT   LATAbits.LATA5

#define LED_D1_TRIS  TRISDbits.RD1
#define LED_D1_LAT   LATDbits.LATD1


#define LED_S0_TRIS  TRISBbits.RB5  //h
#define LED_S0_LAT   LATBbits.LATB5

#define LED_S1_TRIS  TRISBbits.RB4  //g
#define LED_S1_LAT   LATBbits.LATB4

#define LED_S2_TRIS  TRISBbits.RB1  //f
#define LED_S2_LAT   LATBbits.LATB1

#define LED_S3_TRIS  TRISBbits.RB2  //e
#define LED_S3_LAT   LATBbits.LATB2

#define LED_S4_TRIS  TRISBbits.RB3  //d
#define LED_S4_LAT   LATBbits.LATB3

#define LED_S5_TRIS  TRISBbits.RB7  //c
#define LED_S5_LAT   LATBbits.LATB7

#define LED_S6_TRIS  TRISBbits.RB6  //b
#define LED_S6_LAT   LATBbits.LATB6

#define LED_S7_TRIS  TRISBbits.RB0  //a
#define LED_S7_LAT   LATBbits.LATB0

///////////////////////////////////////////////////////////////////////////////


#define INIT_LED_D0  LED_D0_LAT=1; LED_D0_TRIS=0
#define INIT_LED_D1  LED_D1_LAT=1; LED_D1_TRIS=0

#define INIT_LED_D  INIT_LED_D0; INIT_LED_D1


#define INIT_LED_S0  LED_S0_LAT=1; LED_S0_TRIS=0
#define INIT_LED_S1  LED_S1_LAT=1; LED_S1_TRIS=0
#define INIT_LED_S2  LED_S2_LAT=1; LED_S2_TRIS=0
#define INIT_LED_S3  LED_S3_LAT=1; LED_S3_TRIS=0
#define INIT_LED_S4  LED_S4_LAT=1; LED_S4_TRIS=0
#define INIT_LED_S5  LED_S5_LAT=1; LED_S5_TRIS=0
#define INIT_LED_S6  LED_S6_LAT=1; LED_S6_TRIS=0
#define INIT_LED_S7  LED_S7_LAT=1; LED_S7_TRIS=0

#define INIT_LED_S  INIT_LED_S0; INIT_LED_S1; INIT_LED_S2; INIT_LED_S3; INIT_LED_S4; INIT_LED_S5; INIT_LED_S6; INIT_LED_S7

#define INIT_LED  INIT_LED_D; INIT_LED_S



// bit manipulation

#define REG_BIT_SET(reg, bit) ((reg) |= (1<<(bit)))
#define REG_BIT_CLR(reg, bit) ((reg) &= ~(1<<(bit)))

#define REG_BIT_IS_SET(reg, bit) ((reg)>>(bit)&1)
#define REG_BIT_IS_CLR(reg, bit) (!((reg)>>(bit)&1))



void led_mux(void);
void led_print(uint8_t pos, const char *str);
void led_dot(uint8_t pos, uint8_t on);
void led_char(uint8_t pos, uint8_t sign);



#endif	/* LED_H_ */


