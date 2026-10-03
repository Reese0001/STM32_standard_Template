/**
 ******************************************************************************
 * @file    User/stm32f10x_it.c
 * @author  MCD Application Team (modified by Template)
 * @version V3.5.0
 * @date    2026-05-30
 * @brief   中断服务函数 & 异常处理器
 *
 * 故障指示: 每个 Fault Handler 会以 LED 闪烁模式指示故障类型.
 *          默认使用 PC13 (常见板载 LED), 可修改 FAULT_LED_PORT / FAULT_LED_PIN.
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* --- 故障指示 LED 配置 (可修改为你的板载 LED 引脚) --- */
#define FAULT_LED_PORT     GPIOC
#define FAULT_LED_PIN      GPIO_Pin_13
#define FAULT_LED_RCC      RCC_APB2Periph_GPIOC

/* --- 每个故障类型的闪烁次数 --- */
#define FAULT_HARD         (1)
#define FAULT_MEMMANAGE    (2)
#define FAULT_BUS          (3)
#define FAULT_USAGE        (4)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void Fault_Blink(uint8_t code);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  故障 LED 闪烁指示
  * @param  code: 故障代码 (闪烁次数), 0 表示常亮
  * @retval None
  *
  * 注: 默认使用 PC13 作为故障指示灯 (低电平点亮).
  *     如果你的板子不同, 修改上面的 FAULT_LED_* 宏即可.
  *     如果你不需要 LED 指示, 直接删除 Fault_Blink 的实现即可.
  */
static void Fault_Blink(uint8_t code)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    volatile uint32_t delay;

    /* 使能 LED 所在 GPIO 时钟 */
    RCC_APB2PeriphClockCmd(FAULT_LED_RCC, ENABLE);

    /* 配置为推挽输出 */
    GPIO_InitStructure.GPIO_Pin   = FAULT_LED_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(FAULT_LED_PORT, &GPIO_InitStructure);

    while (1)
    {
        if (code == 0)
        {
            /* 常亮 */
            GPIO_ResetBits(FAULT_LED_PORT, FAULT_LED_PIN);
        }
        else
        {
            uint8_t i;
            /* 闪烁 code 次后长灭 */
            for (i = 0; i < code; i++)
            {
                GPIO_ResetBits(FAULT_LED_PORT, FAULT_LED_PIN);  /* 亮 */
                for (delay = 0; delay < 1000000; delay++);
                GPIO_SetBits(FAULT_LED_PORT, FAULT_LED_PIN);    /* 灭 */
                for (delay = 0; delay < 500000; delay++);
            }
        }
        /* 长间隔后再重复 */
        for (delay = 0; delay < 5000000; delay++);
    }
}

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

void NMI_Handler(void)
{
    /* NMI: 不可屏蔽中断, 通常由外部硬件触发 */
}

/**
  * @brief  Hard Fault Handler
  *         - 非法内存访问
  *         - 未对齐访问
  *         - 总线错误升级
  */
void HardFault_Handler(void)
{
    Fault_Blink(FAULT_HARD);
}

/**
  * @brief  MemManage Fault Handler
  *         - MPU 违规访问
  *         - 执行不可执行区域
  */
void MemManage_Handler(void)
{
    Fault_Blink(FAULT_MEMMANAGE);
}

/**
  * @brief  Bus Fault Handler
  *         - 预取中止
  *         - 数据访问中止
  */
void BusFault_Handler(void)
{
    Fault_Blink(FAULT_BUS);
}

/**
  * @brief  Usage Fault Handler
  *         - 未定义指令
  *         - 协处理器访问错误
  *         - 除零
  *         - 非对齐访问
  */
void UsageFault_Handler(void)
{
    Fault_Blink(FAULT_USAGE);
}

void SVC_Handler(void)
{
}

void DebugMon_Handler(void)
{
}

void PendSV_Handler(void)
{
}

/**
  * @brief  SysTick Handler (1ms 中断)
  *
  * 用法: 在你的 User 代码中重写此函数即可.
  *       例如: 全局 tick 计数, 任务调度, 按键扫描等.
  *
  * 注意: delay.c 使用 SysTick 硬件进行阻塞延时 (不依赖中断),
  *       因此 SysTick_Handler 为空不会影响 Delay_us / Delay_ms / Delay_s.
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/******************************************************************************/

/**
  * @brief  外设中断服务函数模板
  *
  * 在 startup_stm32f10x_hd.s 中查找 ISR 名称, 复制到此处即可.
  * 示例:
  * void USART1_IRQHandler(void)
  * {
  *     if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  *     {
  *         uint8_t data = USART_ReceiveData(USART1);
  *     }
  * }
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
