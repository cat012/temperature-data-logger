// main.h
// PIC18F4520
// Compiler: XC8 v1.33
// 20-Sep-2020


#ifndef MAIN_H_
#define MAIN_H_


#define _XTAL_FREQ 8000000


// CONFIG1H
#pragma config OSC = INTIO67    // Oscillator Selection bits (Internal oscillator block, port function on RA6 and RA7)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bits (Brown-out Reset enabled and controlled by software (SBOREN is enabled))
#pragma config BORV = 3         // Brown Out Reset Voltage bits (Minimum setting)

// CONFIG2H
#pragma config WDT = ON         // Watchdog Timer Enable bit (WDT enabled)
#pragma config WDTPS = 4096     // Watchdog Timer Postscale Select bits (1:4096)

// CONFIG3H
#pragma config CCP2MX = PORTC   // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = OFF      // MCLR Pin Enable bit (RE3 input pin enabled; MCLR disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) not protected from table reads executed in other blocks)

#include <xc.h>


/* unused pins PORTA */
//#define UPIN_A0  LATAbits.LATA0=0; TRISAbits.RA0=0
//#define UPIN_A1  LATAbits.LATA1=0; TRISAbits.RA1=0
#define UPIN_A2  LATAbits.LATA2=0; TRISAbits.RA2=0
#define UPIN_A3  LATAbits.LATA3=0; TRISAbits.RA3=0
#define UPIN_A4  LATAbits.LATA4=0; TRISAbits.RA4=0
//#define UPIN_A5  LATAbits.LATA5=0; TRISAbits.RA5=0
#define UPIN_A6  LATAbits.LATA6=0; TRISAbits.RA6=0
#define UPIN_A7  LATAbits.LATA7=0; TRISAbits.RA7=0

#define UPIN_A_INIT  /*UPIN_A0; UPIN_A1;*/ UPIN_A2; UPIN_A3; UPIN_A4; /*UPIN_A5;*/ UPIN_A6; UPIN_A7

/* unused pins PORTB */
//#define UPIN_B0  LATBbits.LATB0=0; TRISBbits.RB0=0
//#define UPIN_B1  LATBbits.LATB1=0; TRISBbits.RB1=0
//#define UPIN_B2  LATBbits.LATB2=0; TRISBbits.RB2=0
//#define UPIN_B3  LATBbits.LATB3=0; TRISBbits.RB3=0
//#define UPIN_B4  LATBbits.LATB4=0; TRISBbits.RB4=0
//ICSP
//#define UPIN_B5  LATBbits.LATB5=0; TRISBbits.RB5=0
//#define UPIN_B6  LATBbits.LATB6=0; TRISBbits.RB6=0
//#define UPIN_B7  LATBbits.LATB7=0; TRISBbits.RB7=0

#define UPIN_B_INIT  /*UPIN_B0; UPIN_B1 ; UPIN_B2; UPIN_B3; UPIN_B4; UPIN_B5; UPIN_B6; UPIN_B7*/

/* unused pins PORTC */
#define UPIN_C0  LATCbits.LATC0=0; TRISCbits.RC0=0
#define UPIN_C1  LATCbits.LATC1=0; TRISCbits.RC1=0
#define UPIN_C2  LATCbits.LATC2=0; TRISCbits.RC2=0
//i2c
#define UPIN_C3  LATCbits.LATC3=0; TRISCbits.RC3=0
//i2c
#define UPIN_C4  LATCbits.LATC4=0; TRISCbits.RC4=0
#define UPIN_C5  LATCbits.LATC5=0; TRISCbits.RC5=0
#define UPIN_C6  LATCbits.LATC6=0; TRISCbits.RC6=0
//conn. #3  //pullup 1.1M
//button
//#define UPIN_C7  LATCbits.LATC7=0; TRISCbits.RC7=1

#define UPIN_C_INIT   UPIN_C0; UPIN_C1; UPIN_C2; UPIN_C3; UPIN_C4; UPIN_C5; UPIN_C6 /*; UPIN_C7*/

/* unused pins PORTD */
#define UPIN_D0  LATDbits.LATD0=0; TRISDbits.RD0=0
//#define UPIN_D1  LATDbits.LATD1=0; TRISDbits.RD1=0
#define UPIN_D2  LATDbits.LATD2=0; TRISDbits.RD2=0
#define UPIN_D3  LATDbits.LATD3=0; TRISDbits.RD3=0
#define UPIN_D4  LATDbits.LATD4=0; TRISDbits.RD4=0
//#define UPIN_D5  LATDbits.LATD5=0; TRISDbits.RD5=0
#define UPIN_D6  LATDbits.LATD6=0; TRISDbits.RD6=0
//#define UPIN_D7  LATDbits.LATD7=0; TRISDbits.RD7=0

#define UPIN_D_INIT  UPIN_D0; /*UPIN_D1;*/ UPIN_D2; UPIN_D3; UPIN_D4; /*UPIN_D5;*/ UPIN_D6 /*; UPIN_D7*/

/* unused pins PORTE */
//#define UPIN_E0  LATEbits.LATE0=0; TRISEbits.RE0=0
#define UPIN_E1  LATEbits.LATE1=0; TRISEbits.RE1=0
//#define UPIN_E2  LATEbits.LATE2=0; TRISEbits.RE2=0

#define UPIN_E_INIT  /*UPIN_E0;*/  UPIN_E1 /*; UPIN_E2*/


#define UPIN_ALL_INIT  UPIN_A_INIT; UPIN_B_INIT; UPIN_C_INIT; UPIN_D_INIT; UPIN_E_INIT



/* timer 0 prescaler settings */
#define  TMR0_PRESCALER_256  0b00000111
#define  TMR0_PRESCALER_128  0b00000110
#define  TMR0_PRESCALER_64   0b00000101
#define  TMR0_PRESCALER_32   0b00000100
#define  TMR0_PRESCALER_16   0b00000011
#define  TMR0_PRESCALER_8    0b00000010
#define  TMR0_PRESCALER_4    0b00000001
#define  TMR0_PRESCALER_2    0b00000000

#define TMR0_PRESCALER  TMR0_PRESCALER_2

#define TMR0_OVF_FREQ     100U
#define TMR0_OVF_PRELOAD  (65536U-(((_XTAL_FREQ/4U)/2U)/TMR0_OVF_FREQ))

#define TMR0_PERIOD_MS  (1000U/TMR0_OVF_FREQ)
#define EVENT_PERIOD(x)  ((x)/TMR0_PERIOD_MS)


/* timer 1 prescaler settings */
#define TMR1_PRESCALER_8  0b00110000
#define TMR1_PRESCALER_4  0b00100000
#define TMR1_PRESCALER_2  0b00010000
#define TMR1_PRESCALER_1  0b00000000

#define TMR1_PRESCALER  TMR1_PRESCALER_1

#define TMR1_OVF_FREQ     200U
#define TMR1_OVF_PRELOAD  (65536U-(((_XTAL_FREQ/4U)/1U)/TMR1_OVF_FREQ))


/* timer 2 prescaler settings */
#define TMR2_PRESCALER_16  0b00000010
#define TMR2_PRESCALER_4   0b00000001
#define TMR2_PRESCALER_1   0b00000000

#define TMR2_PRESCALER  TMR2_PRESCALER_1


/* timer 3 prescaler settings */
#define TMR3_PRESCALER_8  0b00110000
#define TMR3_PRESCALER_4  0b00100000
#define TMR3_PRESCALER_2  0b00010000
#define TMR3_PRESCALER_1  0b00000000

#define TMR3_PRESCALER  TMR3_PRESCALER_1

#define TMR3_OVF_FREQ     1230UL
#define TMR3_OVF_PRELOAD  (65536U-(((_XTAL_FREQ/4U)/1U)/TMR3_OVF_FREQ))


//NOTE
//Preload timer: 65536-(((Xtal_Freq/4)/Prescaler)/Int_Freq)
//Int_Freq: ((Xtal_Freq/4)/Prescaler)/(65536-Preload)
//Int_Time: 1/((Xtal_Freq/4)/Prescaler)/(65536-Preload)


#endif /* MAIN_H_ */


