#define _MAIN_C_SRC

//-------------------------MODULES USED-------------------------------------
#include "unity.h"
#include "same70q21b.h"
#include "efc.h"
#include "same70_target_uart.h"
#include "test1.h"
//-------------------------DEFINITIONS AND MACORS---------------------------



//-------------------------TYPEDEFS AND STRUCTURES--------------------------



//-------------------------PROTOTYPES OF LOCAL FUNCTIONS--------------------
static void _initSAME70(void);


//-------------------------EXPORTED VARIABLES ------------------------------



//-------------------------GLOBAL VARIABLES---------------------------------



//-------------------------EXPORTED FUNCTIONS-------------------------------
int main(void)
{
    _initSAME70();

    UnityBegin("test1.c");
    DO_TEST(test_thatSucceeds);
    DO_TEST(test_succeedsWithCondition);
    UnityEnd();


    return 0;
}

void HardFault_Handler(void)
{
    while(1);
}
//-------------------------LOCAL FUNCTIONS----------------------------------



static void _initSAME70(void)
{
    //EFC Initialization
    EFC_REGS->EEFC_FMR = EEFC_FMR_FWS(6) | EEFC_FMR_CLOE_Msk ;

    // Configure and Enable PLLA
    PMC_REGS->CKGR_PLLAR = CKGR_PLLAR_ONE_Msk | CKGR_PLLAR_PLLACOUNT(0x3f) |
        CKGR_PLLAR_MULA(25 - 1) |
        CKGR_PLLAR_DIVA(1);

    while ( (PMC_REGS->PMC_SR & PMC_SR_LOCKA_Msk) != PMC_SR_LOCKA_Msk);

    // Program PMC_MCKR.PRES and wait for PMC_SR.MCKRDY to be set
    PMC_REGS->PMC_MCKR = (PMC_REGS->PMC_MCKR & ~PMC_MCKR_PRES_Msk) | PMC_MCKR_PRES_CLK_1;
    while ((PMC_REGS->PMC_SR & PMC_SR_MCKRDY_Msk) != PMC_SR_MCKRDY_Msk);

    // Program PMC_MCKR.MDIV and Wait for PMC_SR.MCKRDY to be set
    PMC_REGS->PMC_MCKR = (PMC_REGS->PMC_MCKR & ~PMC_MCKR_MDIV_Msk) | PMC_MCKR_MDIV_PCK_DIV2;
    while ((PMC_REGS->PMC_SR & PMC_SR_MCKRDY_Msk) != PMC_SR_MCKRDY_Msk);

    // Program PMC_MCKR.CSS and Wait for PMC_SR.MCKRDY to be set
    PMC_REGS->PMC_MCKR = (PMC_REGS->PMC_MCKR & ~PMC_MCKR_CSS_Msk) | PMC_MCKR_CSS_PLLA_CLK;
    while ((PMC_REGS->PMC_SR & PMC_SR_MCKRDY_Msk) != PMC_SR_MCKRDY_Msk);

    // Enable Peripheral Clock
    PMC_REGS->PMC_PCER0=0x35c00;


    MATRIX_REGS->CCFG_SYSIO = 0x0;
    /* Selected System IO pins are configured as GPIO */
    MATRIX_REGS->CCFG_SYSIO |= 0x10;

    RSWDT_REGS->RSWDT_MR = RSWDT_MR_WDDIS_Msk;	// Disable RSWDT

	WDT_REGS->WDT_MR = WDT_MR_WDDIS_Msk; 		// Disable WDT
}
