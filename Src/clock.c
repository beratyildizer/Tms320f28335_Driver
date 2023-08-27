/*
 * clock.c
 *
 *  Created on: Aug 14, 2023
 *      Author: berat.yildizer
 */

#include "clock.h"
#include "DSP2833x_Device.h"
#include "DSP2833x_SysCtrl.h"


void initPll(PLL_InitTypedef_t* pllHandler)
{
    if(SysCtrlRegs.PLLSTS.bit.MCLKSTS == 1u){
        EALLOW;
        SET(SysCtrlRegs.PLLSTS.bit.MCLKCLR, 1u);
        EDIS;
    }

    if((SysCtrlRegs.PLLSTS.bit.DIVSEL == DIVSEL_VAL_2) || (SysCtrlRegs.PLLSTS.bit.DIVSEL == DIVSEL_VAL_3)){
        EALLOW;
        SET(SysCtrlRegs.PLLSTS.bit.DIVSEL, DIVSEL_VAL_0);
        EDIS;
    }

    EALLOW;
    SET(SysCtrlRegs.PLLSTS.bit.MCLKOFF, 1u);
    EDIS;

    EALLOW;
    SET(SysCtrlRegs.PLLCR.all, pllHandler->div_value);
    EDIS;

    while(!SysCtrlRegs.PLLSTS.bit.PLLLOCKS);

    EALLOW;
    SET(SysCtrlRegs.PLLSTS.bit.MCLKOFF, 0u);
    EDIS;

    EALLOW;
    SET(SysCtrlRegs.PLLSTS.bit.DIVSEL, pllHandler->divsel_value);
    EDIS;


}
