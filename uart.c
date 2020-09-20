// 19-Sep-2020


#include "uart.h"


extern void tmr_uart_start(void);
extern void tmr_uart_stop(void);


static uint16_t txbuff=0;

volatile static uint8_t bitcnt=0;



//-----------------------------------------------------------------------------
inline void uart_cont(void)
    {
    if(bitcnt)
        {
        (txbuff&1) ? TX_LED_OFF : TX_LED_ON;
        txbuff>>=1;
        bitcnt--;
        }
    }


//-----------------------------------------------------------------------------
void uart_init(void)
    {
    bitcnt=0;
    TX_LED_OFF;
    TX_LED_INIT;
    tmr_uart_start();
    }


//-----------------------------------------------------------------------------
void uart_deinit(void)
    {
    while(bitcnt);
    tmr_uart_stop();
    TX_LED_OFF;
    }


//-----------------------------------------------------------------------------
void uart_char(char code)
    {
    while(bitcnt);
    txbuff=((code<<1)|(1<<(NUM_OF_BITS-1)));
    bitcnt=NUM_OF_BITS;
    }


//-----------------------------------------------------------------------------
void uart_print(const char* str)
    {
    for(; *str; str++) uart_char(*str);
    }


