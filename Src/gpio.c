/*
 * gpio.c
 *
 *  Created on: Aug 17, 2023
 *      Author: berat.yildizer
 */

#include "gpio.h"
#include "DSP2833x_Device.h"
#include "DSP2833x_Gpio.h"

/**
  * @brief  initGPIO; Configures the port and pin
  *
  * @param  GPIO_InitTypedef_t; User Config Structures
  *
  * @retval int; success value
  */

int initGPIO(GPIO_InitTypedef_t* GPIO_ConfigStruct)
{
    if((GPIO_ConfigStruct->pin_number > (unsigned char)32) || (GPIO_ConfigStruct->port_name == GPIO_C && GPIO_ConfigStruct->pin_number > (unsigned char)23))
        return 0;

    EALLOW;

    switch(GPIO_ConfigStruct->port_name){
        case  GPIO_A : {

                /* Set MUX */ // +++
                if(GPIO_ConfigStruct->pin_number < 16){
                    GpioCtrlRegs.GPAMUX1.all &= ~(0x3 << (GPIO_ConfigStruct->pin_number * 2));
                }else{
                    GpioCtrlRegs.GPAMUX2.all &= ~(0x3 << ((GPIO_ConfigStruct->pin_number - 16) * 2));
                }

                /* Set Pull Up */ // +++
                {
                    Uint32 temp = GpioCtrlRegs.GPAPUD.all;
                GpioCtrlRegs.GPAPUD.all = ((GPIO_ConfigStruct->pull_type == no_pull_up) ?
                        ((1ul << GPIO_ConfigStruct->pin_number) | (temp)) :
                        (~(1ul << GPIO_ConfigStruct->pin_number) & (temp)));
                }

                /* Set Time Period */ // ++
                {
                    Uint32 temp = GpioCtrlRegs.GPACTRL.all;
                GpioCtrlRegs.GPACTRL.all = (((GPIO_ConfigStruct->qualification_time_period << ((GPIO_ConfigStruct->pin_number / 8) * 8))) |
                        (~(0xFFul << ((GPIO_ConfigStruct->pin_number / 8) * 8))) & temp);
                }


                /* Set Number of Sample */ // ++
                if(GPIO_ConfigStruct->pin_number < 16){
                    Uint32 temp =  GpioCtrlRegs.GPAQSEL1.all;
                    GpioCtrlRegs.GPAQSEL1.all = (((unsigned long)GPIO_ConfigStruct->syncro_selection << (GPIO_ConfigStruct->pin_number * 2)) |
                            (~(0xFul << (GPIO_ConfigStruct->pin_number * 2))) &  temp);
                }else{
                    Uint32 temp =  GpioCtrlRegs.GPAQSEL2.all;
                    GpioCtrlRegs.GPAQSEL2.all = (((unsigned long)GPIO_ConfigStruct->syncro_selection << ((GPIO_ConfigStruct->pin_number - 16) * 2)) |
                            (~(0xFul << ((GPIO_ConfigStruct->pin_number - 16) * 2))) &  temp);
                }

                /* Set Pin Direction */ // ++
                {
                    Uint32 temp = GpioCtrlRegs.GPADIR.all;
                GpioCtrlRegs.GPADIR.all = (GPIO_ConfigStruct->pin_direction == input) ?
                        (~((unsigned long)GPIO_ConfigStruct->pin_direction << GPIO_ConfigStruct->pin_number) & (temp)) :
                        (((unsigned long)GPIO_ConfigStruct->pin_direction << GPIO_ConfigStruct->pin_number) | (temp));
                }

                break;
        }
        case GPIO_B : {

            /* Set MUX */ // +++
               if(GPIO_ConfigStruct->pin_number < 16){
                  GpioCtrlRegs.GPBMUX1.all &= ~(0x3 << (GPIO_ConfigStruct->pin_number * 2));
               }else{
                   GpioCtrlRegs.GPBMUX2.all &= ~(0x3 << ((GPIO_ConfigStruct->pin_number - 16) * 2));
                }

            /* Set Pull Up */ // +++
                  {
                      Uint32 temp = GpioCtrlRegs.GPBPUD.all;
                      GpioCtrlRegs.GPBPUD.all = ((GPIO_ConfigStruct->pull_type == no_pull_up) ?
                             ((1ul << GPIO_ConfigStruct->pin_number) | (temp)) :
                             (~(1ul << GPIO_ConfigStruct->pin_number) & (temp)));
                  }

              /* Set Time Period */ // ++
                  {
                     Uint32 temp = GpioCtrlRegs.GPBCTRL.all;
                     GpioCtrlRegs.GPBCTRL.all = (((GPIO_ConfigStruct->qualification_time_period << ((GPIO_ConfigStruct->pin_number / 8) * 8))) |
                              (~(0xFFul << ((GPIO_ConfigStruct->pin_number / 8) * 8))) & temp);
                  }


               /* Set Number of Sample */ // ++
                   if(GPIO_ConfigStruct->pin_number < 16){
                       Uint32 temp =  GpioCtrlRegs.GPBQSEL1.all;
                       GpioCtrlRegs.GPBQSEL1.all = (((unsigned long)GPIO_ConfigStruct->syncro_selection << (GPIO_ConfigStruct->pin_number * 2)) |
                                               (~(0xFul << (GPIO_ConfigStruct->pin_number * 2))) &  temp);
                       }else{
                           Uint32 temp =  GpioCtrlRegs.GPBQSEL2.all;
                           GpioCtrlRegs.GPBQSEL2.all = (((unsigned long)GPIO_ConfigStruct->syncro_selection << ((GPIO_ConfigStruct->pin_number - 16) * 2)) |
                                           (~(0xFul << ((GPIO_ConfigStruct->pin_number - 16) * 2))) &  temp);
                       }

                /* Set Pin Direction */ // ++
                 {
                      Uint32 temp = GpioCtrlRegs.GPBDIR.all;
                      GpioCtrlRegs.GPBDIR.all = (GPIO_ConfigStruct->pin_direction == input) ?
                            (~((unsigned long)GPIO_ConfigStruct->pin_direction << GPIO_ConfigStruct->pin_number) & (temp)) :
                             (((unsigned long)GPIO_ConfigStruct->pin_direction << GPIO_ConfigStruct->pin_number) | (temp));
                 }

            break;
        }
        case GPIO_C : {

            /* Set MUX */ // +++
           if(GPIO_ConfigStruct->pin_number < 16){
              GpioCtrlRegs.GPCMUX1.all &= ~(0x3 << (GPIO_ConfigStruct->pin_number * 2));
           }else{
              GpioCtrlRegs.GPCMUX2.all &= ~(0x3 << ((GPIO_ConfigStruct->pin_number - 16) * 2));
           }

           /* Set Pull Up */ // +++
           {
              Uint32 temp = GpioCtrlRegs.GPCPUD.all;
              GpioCtrlRegs.GPCPUD.all = ((GPIO_ConfigStruct->pull_type == no_pull_up) ?
                       ((1ul << GPIO_ConfigStruct->pin_number) | (temp)) :
                       (~(1ul << GPIO_ConfigStruct->pin_number) & (temp)));
           }

           /* Set Pin Direction */ // ++
           {
              Uint32 temp = GpioCtrlRegs.GPCDIR.all;
              GpioCtrlRegs.GPCDIR.all = (GPIO_ConfigStruct->pin_direction == input) ?
                          (~((unsigned long)GPIO_ConfigStruct->pin_direction << GPIO_ConfigStruct->pin_number) & (temp)) :
                          (((unsigned long)GPIO_ConfigStruct->pin_direction << GPIO_ConfigStruct->pin_number) | (temp));
           }

            break;
        }
        default : return 0;
    }

    EDIS;
    return 1;
}


/**
  * @brief  writeGPIO; Writes the port and pin 0 or 1
  *
  * @param  port_name; port name @def_group port name
  *
  * @param  pin_number; it should be less than 32
  *
  * @param  state; GPIO pin set or reset
  *
  * @retval void;
  */

void writeGPIO(unsigned char port_name, unsigned char pin_number, GPIO_PinState_t state)
{

    if((pin_number > (unsigned char)32) || (port_name == GPIO_C && pin_number > (unsigned char)23))
           return;

       EALLOW;

       switch(port_name){


       case GPIO_A :{
           Uint32 temp = GpioDataRegs.GPADAT.all;
           GpioDataRegs.GPADAT.all = state == GPIO_pin_reset ? (~(0x1ul << pin_number) & temp) :
                   ((0x1ul << pin_number) | temp);
           break;

       }

       case GPIO_B :{
           Uint32 temp = GpioDataRegs.GPBDAT.all;
           GpioDataRegs.GPBDAT.all = state == GPIO_pin_reset ? (~(0x1ul << pin_number) & temp) :
                    ((0x1ul << pin_number) | temp);
           break;
       }

       case GPIO_C :{
           Uint32 temp = GpioDataRegs.GPCDAT.all;
           GpioDataRegs.GPCDAT.all = state == GPIO_pin_reset ? (~(0x1ul << pin_number) & temp) :
                    ((0x1ul << pin_number) | temp);
           break;
       }

   }

}

/**
  * @brief  writeGPIO; Writes the port and pin 0 or 1
  *
  * @param  port_name; port name @def_group port name
  *
  * @param  pin_number; it should be less than 32
  *
  * @retval GPIO_PinState_t; it can be GPIO_pin_set or GPIO_pin_reset
  */

GPIO_PinState_t readGPIO(unsigned char port_name, unsigned char pin_number)
{
    if((pin_number > (unsigned char)32) || (port_name == GPIO_C && pin_number > (unsigned char)23))
              return GPIO_pin_reset;

    switch(port_name){
    case GPIO_A:  return ((0x1ul << pin_number) & GpioDataRegs.GPADAT.all) ? GPIO_pin_set : GPIO_pin_reset;
    case GPIO_B:  return ((0x1ul << pin_number) & GpioDataRegs.GPBDAT.all) ? GPIO_pin_set : GPIO_pin_reset;
    case GPIO_C:  return ((0x1ul << pin_number) & GpioDataRegs.GPCDAT.all) ? GPIO_pin_set : GPIO_pin_reset;
    default: return GPIO_pin_reset;
    }
}


/**
  * @brief  writeGPIO; Writes the port and pin 0 or 1
  *
  * @param  port_name; port name @def_group port name
  *
  * @param  pin_number; it should be less than 32
  *
  * @retval void;
  */

void toggleGPIO(unsigned char port_name, unsigned char pin_number)
{
    if((pin_number > (unsigned char)32) || (port_name == GPIO_C && pin_number > (unsigned char)23))
        return;

    switch(port_name){
    case GPIO_A:{
        GpioDataRegs.GPATOGGLE.all |= (0x1ul << pin_number);
        break;
    }
    case GPIO_B:{
        GpioDataRegs.GPBTOGGLE.all |= (0x1ul << pin_number);
        break;
    }
    case GPIO_C:{
        GpioDataRegs.GPCTOGGLE.all |= (0x1ul << pin_number);
        break;
    }
    }


}
