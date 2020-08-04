#define _LEDCTRL_C_SRC

//-------------------------MODULES USED-------------------------------------
#include "same70q21b.h"
#include "ledctrl.h"


//-------------------------DEFINITIONS AND MACORS---------------------------
#define MIN_NUM_BLINKS 1
#define MAX_NUM_BLINKS 9
#define MIN_BLINK_DURATION 2
#define MAX_BLINK_DURATION 5

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
    RTT->RTT_MR = (1<<24 | 1<<18);

    return LEDCTRL_OK;
}

int32_t ledctrl_blinkled(uint32_t num_blink, uint32_t s_blink_duration)
{
	if(num_blink < MIN_NUM_BLINKS){
		return LEDCTRL_ERR;
	}
	if(num_blink > MAX_NUM_BLINKS){
		return LEDCTRL_ERR;
	}
	if(s_blink_duration < MIN_BLINK_DURATION){
		return LEDCTRL_ERR;
	}
	if(s_blink_duration > MAX_BLINK_DURATION){
		return LEDCTRL_ERR;
	}
	s_blink_duration /=2;

	ledctrl_onof(false);
	for(int i=0;i<(num_blink);i++){
		ledctrl_onof(true);
		uint32_t t = RTT->RTT_VR;
		while((t+s_blink_duration) >= RTT->RTT_VR);
		ledctrl_onof(false);
		t = RTT->RTT_VR;
		while((t+s_blink_duration) >= RTT->RTT_VR);
	}

	return LEDCTRL_OK;
}


int32_t ledctrl_onof(bool led_on)
{

	if(led_on){
		PIO->PIO_SODR = 1<<8;
	}else{
		PIO->PIO_CODR = 1<<8;
	}

	return LEDCTRL_OK;
}



//-------------------------LOCAL FUNCTIONS----------------------------------
