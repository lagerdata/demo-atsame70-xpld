#ifndef _TICKS_INCLUDED
#define _TICKS_INCLUDED
//-------------------------MODULES USED-------------------------------------
#include <stdint.h>


//-------------------------DEFINITIONS AND MACORS---------------------------



//-------------------------TYPEDEFS AND STRUCTURES--------------------------



//-------------------------EXPORTED VARIABLES ------------------------------
#ifndef _TICKS_C_SRC



#endif



//-------------------------EXPORTED FUNCTIONS-------------------------------
void ticks_init(void);
void ticks_delay(uint32_t ms);
uint32_t ticks_getCount(void);

#endif
