/**
 *  @file       uint28_t.h
 *  @author     Damian Smela <damian.a.smela@gmail.com>
 *  @date       27.05.2018
 *  @brief      fixed length 28 bit data type implementation
 */

#ifndef UINT28_T_H
#define UINT28_T_H

#include "stdint.h"

#define UINT28_MAX 0x0FFFFFFF

typedef unsigned int uint28_t;

#define UINT28_SET(uint28_var, uint28_val) (uint28_var) = (0x0FFFFFFFu & (unsigned)(uint28_val))
#define UINT28_SET_BIT(uint28_var, bit_num) (uint28_var) |= ((1UL) << (unsigned)((bit_num) - 1))
#define UINT28_CLEAR_BIT(uint28_var, bit_num) (uint28_var) &= ~((1UL) << (unsigned)((bit_num) - 1))

#endif //UINT28_T_H
