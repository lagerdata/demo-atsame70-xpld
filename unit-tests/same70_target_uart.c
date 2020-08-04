#define _SAME70_TARGET_UART_C_SRC

//-------------------------MODULES USED-------------------------------------
#include <stdint.h>

#include "same70_target_uart.h"
//-------------------------DEFINITIONS AND MACORS---------------------------





//-------------------------TYPEDEFS AND STRUCTURES--------------------------

#define PMC PMC_REGS


//-------------------------PROTOTYPES OF LOCAL FUNCTIONS--------------------



//-------------------------EXPORTED VARIABLES ------------------------------



//-------------------------GLOBAL VARIABLES---------------------------------



//-------------------------EXPORTED FUNCTIONS-------------------------------
void same70_target_putc(char a)
{
    UART->US_THR = a;
    int cnt = 0;
    while((1 != ((UART->US_CSR>>1)&0x01)) && (cnt < 10000000)){
        cnt++;
    }
}

void same70_target_init_putc(void)
{
    //enable peripheral uart and usart clocks(UART0, UART1, USART0, USART1, USART2)
    PMC->PMC_PCER0= 0x80 | 0x100 | 0x2000 | 0x4000 | 0x8000;

    //enable peripheral uart clocks (UART2, UART3, UART4)
    PMC->PMC_PCER1 = 0x1000 | 0x2000 | 0x4000;


    uint32_t clk_type = (PMC->PMC_MCKR & 0x03);
    uint32_t f_periph = 0;
    switch(clk_type){
        case 0:{//Slow Clock
            f_periph = 32768;
            break;
        }

        case 1:{//Main Clock
            f_periph = MAINCLOCK_HZ;
            break;
        }

        case 2:{//PLC Clock
            f_periph = MAINCLOCK_HZ*(((PMC->CKGR_PLLAR>>16) & 0x7ff)+1)/(PMC->CKGR_PLLAR&0xff);
            break;
        }

        case 3:{//USB Clock
            f_periph = 480000000/((PMC->PMC_MCKR>>13)&0x01);
            break;
        }
        default:{//error
            break;
        }
    }

    //Divide peripheral clock by pre-scaler and master clock division
    uint32_t pres = (((PMC->PMC_MCKR>>4)&0x07));
    pres = 1<<pres;
    uint32_t mdiv = ((PMC->PMC_MCKR>>8)&0x03);
    mdiv = 1<<mdiv;
    if(8 == mdiv){
        mdiv = 3;
    }

    f_periph /= (pres * mdiv);

    //CD = fperiph/16*BAUDRATE
    uint32_t cd = f_periph/16;
    cd /= BAUDRATE;
    UART->US_BRGR = cd;

    //set pins
    //Disable PB4, and enable for peripheral
    PIO->PIO_PDR = (1<<PIN);
    PIO->PIO_ODR = 1<<PIN;
    PIO->PIO_IFDR = 1<<PIN;
    PIO->PIO_CODR = 0;
    PIO->PIO_IDR = 0xffff;
    PIO->PIO_MDER = 0;
    PIO->PIO_MDDR = 1<<PIN;
    PIO->PIO_PUDR = 1<<PIN;
    PIO->PIO_PUER = 0;
    PIO->PIO_PPDDR = 1<<PIN;
    //Peripheral Select Register
    PIO->PIO_ABCDSR[0] = ((PERIPH&0x01)<<PIN);
    PIO->PIO_ABCDSR[1] = (((PERIPH>>1)&0x01)<<PIN);



    // normal mode, peripheral clock, no parity, no digital filter
    UART->US_MR = 0;
    UART->US_MR = (DATABITS<<6) | (PARITY<<9) | (STOP_BITS<<12);

    //enable TX
    UART->US_CR = 0;
    UART->US_CR = (1<<6);
    while(1 != ((UART->US_CSR>>1)&0x01));


}

void same70_target_flush_putc(void)
{

    UART->US_CR = 1<<7;
    UART->US_CR = 0;
    UART->US_CR = (1<<6);
    while(1 != ((UART->US_CSR>>1)&0x01));

}

void same70_target_close_putc(void)
{
    //disable peripheral uart and usart clocks
    PMC->PMC_PCDR0 = (0x80) | (0x100) | (0x2000) | (0x4000) | (0x8000);
    PMC->PMC_PCDR1 = (0x1000) | (0x2000) | (0x4000);
    //Reset TX
    UART->US_CR = (1<<3);
    //Disable TX
    UART->US_CR = (1<<7);


}


//-------------------------LOCAL FUNCTIONS----------------------------------
