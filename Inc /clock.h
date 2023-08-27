/*
 * clock.h
 *
 *  Created on: Aug 14, 2023
 *      Author: berat.yildizer
 */

#ifndef MY_CODES_MY_HEADERS_CLOCK_H_
#define MY_CODES_MY_HEADERS_CLOCK_H_

/*
 * @def_group general purpose macro functions
 */

#define SET(X,Y)       ((X) = (Y))


/*
 * @def_group div_value for PLL_InitTypedef_t
 */

#define DIV_VAL_0     (unsigned char)0x0
#define DIV_VAL_1     (unsigned char)0x1
#define DIV_VAL_2     (unsigned char)0x2
#define DIV_VAL_3     (unsigned char)0x3
#define DIV_VAL_4     (unsigned char)0x4
#define DIV_VAL_5     (unsigned char)0x5
#define DIV_VAL_6     (unsigned char)0x6
#define DIV_VAL_7     (unsigned char)0x7
#define DIV_VAL_8     (unsigned char)0x8
#define DIV_VAL_9     (unsigned char)0x9
#define DIV_VAL_10    (unsigned char)0xA

/*
 * @def_group divsel_value for PLL_InitTypedef_t
 */

#define DIVSEL_VAL_0   (unsigned char)0x0
#define DIVSEL_VAL_1   (unsigned char)0x1
#define DIVSEL_VAL_2   (unsigned char)0x2
#define DIVSEL_VAL_3   (unsigned char)0x3

typedef struct{
    unsigned char div_value;  // @def_group div_value
    unsigned char divsel_value; // @def_group divsel_value
}PLL_InitTypedef_t;

void initPll(PLL_InitTypedef_t* pllHandler);




#endif /* MY_CODES_MY_HEADERS_CLOCK_H_ */
