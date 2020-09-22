// main.c
// 21-Sep-2020


#include <stdio.h>
#include <stdint.h>

#include "main.h"
#include "ds18b20.h"
#include "led.h"
#include "i2c.h"
#include "eeprom.h"
#include "uart.h"
#include "button.h"


#define LOG_DATA_SIZE  2048
#define LOG_PERIOD_1   1
#define LOG_PERIOD_2   60
#define LOG_PERIOD_3   3600


uint8_t trmdata[3]; //ds18b20 data

volatile uint8_t trmcnt=0;
volatile uint8_t syscnt=0;

char strbuff[8];

uint8_t scrupd=0;

uint16_t logperiod=LOG_PERIOD_2;
uint8_t logen=0;
uint8_t logstart=0;
uint8_t logstop=0;

uint8_t txen=0;
uint8_t txstart=0;
uint8_t txstop=0;



//-----------------------------------------------------------------------------
void tmr_uart_start(void)
    {
    TMR3=TMR3_OVF_PRELOAD;

    TMR3ON=1;
    TMR3IF=0;
    TMR3IE=1;
    }


//-----------------------------------------------------------------------------
void tmr_uart_stop(void)
    {
    TMR3ON=0;
    }


//=============================================================================
void __interrupt isr_high(void)
    {
    if(INT0IF && INT0IE) // external interrupt 0 - pulse from Geiger detector
        {
        INT0IF=0;
        }

    if(TMR0IF && TMR0IE)  //timer0 overflow - 100Hz ticks
        {
        TMR0IF=0;
        TMR0=TMR0_OVF_PRELOAD;

        button_cont();

        if(trmcnt) trmcnt--;
        if(syscnt) syscnt--;
        }

    if(TMR1IF && TMR1IE)  //timer1
        {
        TMR1IF=0;
        TMR1=TMR1_OVF_PRELOAD;

        led_mux();
        }

    if(TMR3IF && TMR3IE)  //timer3
        {
        TMR3IF=0;
        TMR3=TMR3_OVF_PRELOAD;

        //UART_TX_LAT=!UART_TX_LAT;
        uart_cont();
        }
    }


//-----------------------------------------------------------------------------
static inline void log_cont(void)
    {
    static uint16_t logtmr=0;
    static uint16_t logcnt=0;
    int16_t logdata=0;

    logdata=(trmdata[1]*10)+trmdata[2];
    if(trmdata[0]) logdata=-logdata;

    if(logstart)
        {
        logstart=0;
        logen=1;
        logcnt=0;
        ee_write16(logcnt, logdata);
        logcnt+=2;
        logtmr=0;
        }

    if(logstop)
        {
        logstop=0;
        logen=0;
        ee_write16(logcnt,2001);  //log end mark
        logcnt=0;
        }

    if(logen)
        {
        if(++logtmr>=logperiod)
            {
            logtmr=0;
            if(logcnt>=(LOG_DATA_SIZE-2))
                {
                logen=0;
                ee_write16(logcnt,2000);  //log end mark
                logcnt=0;
                }
            else
                {
                ee_write16(logcnt, logdata);
                logcnt+=2;
                }
            }
        }
    }


//-----------------------------------------------------------------------------
static inline void tx_cont(void)
    {
    static uint16_t txcnt=0;

    if(txstart)
        {
        txstart=0;
        txcnt=0;
        txen=1;
        uart_init();
        }

    if(txstop)
        {
        txstop=0;
        txcnt=0;
        txen=0;
        uart_print("2002");
        uart_deinit();
        }

    if(txen)
        {
        int16_t txd=ee_read16(txcnt);

        if(txd==2000 || txd==2001 || txd==2002)
            {
            txcnt=0;
            txen=0;
            scrupd=1;
            sprintf(strbuff,"%04d", txd);
            uart_print(strbuff);
            uart_deinit();
            }
        else
            {
            sprintf(strbuff,"%+04d", txd);
            uart_print(strbuff);
            txcnt+=2;
            if(txcnt>=LOG_DATA_SIZE)
                {
                txcnt=0;
                txen=0;
                uart_print("2003");
                uart_deinit();
                }
            }
        }
    }


//-----------------------------------------------------------------------------
void main(void)
    {
    IRCF2=1; IRCF1=1; IRCF0=1; //111=8M 110=4M 101=2M 100=1M 011=500k 010=250k 001=125k 000=31k

    //INTSRC PLLEN - TUN4 TUN3 TUN2 TUN1 TUN0
    OSCTUNE=0b00000001;

    SBOREN=1; //1=enable brown out reset
    SWDTEN=1; //0=disable watchdog timer
    RBPU=1;   //0=enable pull-up

    PEIE=1;
    GIE=1;

    //TMR0ON T08BIT T0CS T0SE PSA T0PS2 T0PS1 T0PS0
    T0CON=0b00000000 | TMR0_PRESCALER;
    TMR0=TMR0_OVF_PRELOAD; //preload
    TMR0ON=1;
    TMR0IF=0;
    TMR0IE=1;

    //RD16 T1RUN T1CKPS1 T1CKPS0 T1OSCEN T1SYNC TMR1CS TMR1ON
    T1CON=0b00000000 | TMR1_PRESCALER;
    TMR1=TMR1_OVF_PRELOAD;
    TMR1ON=1;
    TMR1IF=0;
    TMR1IE=1;

    //- TOUTPS3 TOUTPS2 TOUTPS1 TOUTPS0 TMR2ON T2CKPS1 T2CKPS0
    T2CON=0b00000000 | TMR2_PRESCALER;
    TMR2=0;
    TMR2ON=0;
    TMR2IF=0;
    TMR2IE=0;

    ////RD16 T3CCP2 T3CKPS1 T3CKPS0 T3CCP1 T3SYNC TMR3CS TMR3ON
    T3CON=0b00000000 | TMR3_PRESCALER;
    TMR3=TMR3_OVF_PRELOAD;;
    TMR3ON=0;
    TMR3IF=0;
    TMR3IE=0;

    //- - DCxB1 DCxB0 CCPxM3 CCPxM2 CCPxM1 CCPxM0
    CCP2CON=0b00000000;

    //P1M1 P1M0 DC1B1 DC1B0 CCP1M3 CCP1M2 CCP1M1 CCP1M0
    CCP1CON=0b00000000;

    CMCON=0b000111; //Comparators Off

    ADCON1 = 0b001110; //5-Vref=Vss //4+Vref=Vdd //AN0
    ADCON0 = 0b000000; //Channel 0  //A/D converter module is disabled
    //ADFM - ACQT2 ACQT1 ACQT0 ADCS2 ADCS1 ADCS0
    ADCON2 = 0b10010101; //TACQ 010=4TAD //TAD 000=FOSC/2 100=FOSC/4 101=FOSC/16 Fosc/4=0.5M=2us  //111=FRC
    ADON=0; //Turn off A/D module

    /*** external interrupt 0 settigs ***/
    INTEDG0=0; //on falling edge
    INT0IE=0;

    DS18B20_PIN_INIT;
    INIT_LED;
    UPIN_ALL_INIT;

    i2c_init();
/*
    __delay_ms(50);
    __delay_ms(50);
    __delay_ms(50);
    __delay_ms(50);
    __delay_ms(50);
    __delay_ms(50);
    __delay_ms(50);
    __delay_ms(50);
    __delay_ms(50);
    __delay_ms(50);
    SBOREN=0;
    ee_clear();
    SBOREN=1;
*/
    uint8_t stage=0;
    uint8_t smode=0;

    for(;;)
        {
        if(syscnt==0)
            {
            syscnt=EVENT_PERIOD(50);

            tx_cont();
            }

        if(trmcnt==0)
            {
            trmcnt=EVENT_PERIOD(1000);

            if(stage)
                {
                trm_read(trmdata);
                trm_start();
                log_cont();
                scrupd=1;
                }
            else
                {
                stage=1;
                trm_start();
                led_print(0,(char*) "--");
                }

            CLRWDT();
            }

        if(scrupd)
            {
            scrupd=0;

            if(smode==0)
                {
                led_dot(0,trmdata[0]);
                led_dot(1,trmdata[2]>=5);
                sprintf(strbuff,"%2u",trmdata[1]);
                led_print(0,strbuff);
                }

            if(smode==1)
                {
                led_dot(1,0);
                if((logen || logstart) && !logstop) led_print(0,(char*)"L-");
                else led_print(0,(char*)"L ");
                }

            if(smode==2)
                {
                if((txen || txstart) && !txstop) led_print(0,(char*)"u-");
                else led_print(0,(char*)"u ");
                }

            if(smode==10)
                {
                led_dot(1,0);
                if(logperiod==LOG_PERIOD_3) led_print(0,"1h");
                else
                    {
                    sprintf(strbuff,"%2u",logperiod);
                    led_print(0,strbuff);
                    }
                }
            }

            switch(button_check())
                {
                case 2:
                    if(smode==0) { smode=10; scrupd=1; break; }
                    if(smode==1) { scrupd=1; logen ? logstop=1 : logstart=1; break; }
                    if(smode==2) { scrupd=1; txen ? txstop=1 : txstart=1; break; }
                    if(smode==10) { smode=0; scrupd=1; break; }
                    break;

                case 1:
                    if(smode==0) { smode++; scrupd=1; break; }
                    if(smode==1) { smode++; scrupd=1; break; }
                    if(smode==2) { smode=0; scrupd=1; break; }
                    if(smode==10)
                        {
                        if(logperiod==LOG_PERIOD_1) logperiod=LOG_PERIOD_2;
                        else if(logperiod==LOG_PERIOD_2) logperiod=LOG_PERIOD_3;
                        else if(logperiod==LOG_PERIOD_3) logperiod=LOG_PERIOD_1;
                        scrupd=1;
                        break;
                        };
                    break;

                case 0: break;
                default: break;
                }
        }
    }



