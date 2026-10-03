///////////////////////////////////////////////////////////
//
// 文件功能：使用 SysTick 实现微秒/毫秒/秒级阻塞延时
// 版本：V1.1
// 作者：墨蔚（MW）
// 修改时间：2026/05/30
//
// 注意事项：
//   1. 调用前需确保 SysTick 时钟已配置 (HCLK = 72MHz)
//   2. 延时函数为阻塞模式，不释放 CPU
//   3. Delay_us 单次最大延时约 233015 us (SysTick 24位)
//
///////////////////////////////////////////////////////////

#include "Delay.h"

/**
  * @brief  微秒级延时 (阻塞)
  * @param  xus: 延时微秒数, 范围 0~233015
  * @retval None
  */
void Delay_us(uint32_t xus)
{
    SysTick->LOAD = 72 * xus;                   // 设置定时器重装值 (72MHz 时钟, 每us=72个周期)
    SysTick->VAL  = 0x00;                       // 清空当前计数值
    SysTick->CTRL = 0x00000005;                 // 设置时钟源为 HCLK, 启动定时器
    while (!(SysTick->CTRL & 0x00010000));      // 等待计数到 0 (COUNTFLAG 置位)
    SysTick->CTRL = 0x00000004;                 // 关闭定时器
}

/**
  * @brief  毫秒级延时 (阻塞)
  * @param  xms: 延时毫秒数, 范围 0~4294967295
  * @retval None
  */
void Delay_ms(uint32_t xms)
{
    while (xms--)
    {
        Delay_us(1000);
    }
}

/**
  * @brief  秒级延时 (阻塞)
  * @param  xs: 延时秒数, 范围 0~4294967295
  * @retval None
  */
void Delay_s(uint32_t xs)
{
    while (xs--)
    {
        Delay_ms(1000);
    }
}
