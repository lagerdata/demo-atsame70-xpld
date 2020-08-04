#ifndef _SAME70_TARGET_UART_INCLUDED
#define _SAME70_TARGET_UART_INCLUDED
//-------------------------MODULES USED-------------------------------------
#include "same70q21b.h"



//-------------------------DEFINITIONS AND MACORS---------------------------
#define PERIPHA 0
#define PERIPHB 1
#define PERIPHC 2
#define PERIPHD 3


#define PERIPH PERIPHD
#define PIN 4
#define PIO PIOB_REGS


#define DATA5BITS 0
#define DATA6BITS 1
#define DATA7BITS 2
#define DATA8BITS 3


#define PARITY_EVEN 0
#define PARITY_ODD 1
#define PARITY_SPACE 2
#define PARITY_MARK 3
#define PARITY_NONE 4
#define PARITY_MULTIDROP 5

#define STOP_BITS_ONE 0
#define STOP_BITS_ONE_FIVE 1
#define STOP_BITS_TWO 2


#define UART USART1_REGS
#define BAUDRATE 115200
#define DATABITS DATA8BITS
#define PARITY PARITY_NONE
#define STOP_BITS STOP_BITS_ONE
#define MAINCLOCK_HZ (12000000UL)


//-------------------------TYPEDEFS AND STRUCTURES--------------------------



//-------------------------EXPORTED VARIABLES ------------------------------
#ifndef _SAME70_TARGET_UART_C_SRC



#endif



//-------------------------EXPORTED FUNCTIONS-------------------------------
void same70_target_putc(char a);
void same70_target_init_putc(void);
void same70_target_flush_putc(void);
void same70_target_close_putc(void);


#endif
