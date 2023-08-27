/*
 * gpio.h
 *
 *  Created on: Aug 16, 2023
 *      Author: berat.yildizer
 */

#ifndef MY_CODES_MY_HEADERS_GPIO_H_
#define MY_CODES_MY_HEADERS_GPIO_H_


/*
 * @def_group port name for GPIO_InitTypedef_t and other functions
 */

#define GPIO_A   (unsigned char)0x0
#define GPIO_B   (unsigned char)0x1
#define GPIO_C   (unsigned char)0x2

typedef enum{
    input = 0x0,
    output = !input
}GPIO_PinMode_t;

typedef enum{
    pull_up = 0x0,
    no_pull_up = !pull_up
}GPIO_PinPullType_t;

typedef enum{
    syncro_to_sysclkout = 0x0,
    using_3_samples,
    using_6_samples,
    no_syncro
}GPIO_SyncroSelection_t;

typedef enum
{
    GPIO_pin_reset = 0x0U,
    GPIO_pin_set = !GPIO_pin_reset,
}GPIO_PinState_t;

typedef struct{
    unsigned char port_name;  // @def_group port name
    unsigned char pin_number;
    unsigned long qualification_time_period;
    GPIO_PinMode_t pin_direction;
    GPIO_PinPullType_t pull_type;
    GPIO_SyncroSelection_t syncro_selection;
}GPIO_InitTypedef_t;

int initGPIO(GPIO_InitTypedef_t* GPIO_ConfigStruct);
void writeGPIO(unsigned char port_name, unsigned char pin_number, GPIO_PinState_t state);
GPIO_PinState_t readGPIO(unsigned char port_name, unsigned char pin_number);
void toggleGPIO(unsigned char port_name, unsigned char pin_number);


#endif /* MY_CODES_MY_HEADERS_GPIO_H_ */
