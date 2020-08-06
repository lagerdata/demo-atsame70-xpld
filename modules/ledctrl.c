#define _LEDCTRL_C_SRC

//-------------------------MODULES USED-------------------------------------
#include "same70q21b.h"
#include "ticks.h"
#include "ledctrl.h"


//-------------------------DEFINITIONS AND MACORS---------------------------
#define MIN_NUM_BLINKS 1
#define MAX_NUM_BLINKS 9
#define MIN_BLINK_DURATION 1
#define MAX_BLINK_DURATION 4999

#define PIO PIOC_REGS
#define RTT RTT_REGS
//-------------------------TYPEDEFS AND STRUCTURES--------------------------



//-------------------------PROTOTYPES OF LOCAL FUNCTIONS--------------------



//-------------------------EXPORTED VARIABLES ------------------------------



//-------------------------GLOBAL VARIABLES---------------------------------



//-------------------------EXPORTED FUNCTIONS-------------------------------
int32_t ledctrl_init(void)
{
    PIO->PIO_PER = 1<<8;
    PIO->PIO_OER = 1<<8;
    ticks_init();

    return LEDCTRL_OK;
}

int32_t ledctrl_blinkled(uint32_t num_blink, uint32_t ms_blink_duration)
{
	if(num_blink < MIN_NUM_BLINKS){
		return LEDCTRL_ERR;
	}
	if(num_blink > MAX_NUM_BLINKS){
		return LEDCTRL_ERR;
	}
	if(ms_blink_duration < MIN_BLINK_DURATION){
		return LEDCTRL_ERR;
	}
	if(ms_blink_duration > MAX_BLINK_DURATION){
		return LEDCTRL_ERR;
	}
	ms_blink_duration /=2;

	ledctrl_onof(false);
	for(int i=0;i<(num_blink);i++){
		ledctrl_onof(true);
        ticks_delay(ms_blink_duration);
		ledctrl_onof(false);
        ticks_delay(ms_blink_duration);
	}

	return LEDCTRL_OK;
}


int32_t ledctrl_onof(bool led_on)
{

	if(led_on){
		PIO->PIO_CODR = 1<<8;
	}else{
		PIO->PIO_SODR = 1<<8;
	}

	return LEDCTRL_OK;
}



//-------------------------LOCAL FUNCTIONS----------------------------------
