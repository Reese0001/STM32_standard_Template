/**
 ******************************************************************************
 * @file    Library/System/delay/Delay.h
 * @author  墨蔚 (MW)
 * @version V1.1
 * @date    2026-05-30
 * @brief   SysTick 阻塞延时
 * @note    依赖: SysTick 时钟 = HCLK = 72MHz
 ******************************************************************************
 */

#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f10x.h"

void Delay_us(uint32_t xus);
void Delay_ms(uint32_t xms);
void Delay_s(uint32_t xs);

#endif /* __DELAY_H */
