// PC13 - LED
// PA9 - USART1 TX
// PB12 - Button (short to GND)

#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include "HW.hpp"
#include "libopencm3/stm32/exti.h"
#include "libopencm3/stm32/gpio.h"
#include "libopencm3/stm32/rcc.h"
#include "libopencm3/stm32/usart.h"
#include "libopencmsis/core_cm3.h"

class GpioButton : public IButton
{
public:
    void InterruptHandler()
    {
        exti_reset_request(EXTI12);
        _pressed = true;
    }
    void WaitForPress() override
    {
        exti_select_source(EXTI12, GPIOB);
        exti_set_trigger(EXTI12, EXTI_TRIGGER_FALLING);
        exti_reset_request(EXTI12);
        _pressed = false;
        exti_enable_request(EXTI12);
        while(!_pressed)
        {
            asm volatile("wfi");
        }
        exti_disable_request(EXTI12);
    }

private:
    volatile bool _pressed{false};
};

class UsartLog : public ILog
{
public:
    explicit UsartLog(std::uint32_t hw);

    void Log(const char* fmt, ...) override;

private:
    std::uint32_t _hw;
};

UsartLog::UsartLog(std::uint32_t hw) : _hw{hw}
{
}

void UsartLog::Log(const char* fmt, ...)
{
    char buf[200] = {0};

    va_list args;
    va_start(args, fmt);

    auto n = vsniprintf(buf, sizeof(buf), fmt, args);

    for(auto p = buf; p != buf + n; p++)
    {
        usart_send_blocking(_hw, *p);
    }
    usart_send_blocking(_hw, '\n');

    va_end(args);
}

class STMHardware : public IHardware
{
public:
    void Initialize();
    void ButtonInterruptHandler();
    ILog& Log() override;
    IButton& Button() override;

private:
    UsartLog _log{USART1};
    GpioButton _button;
};

void STMHardware::Initialize()
{
    rcc_clock_setup_in_hsi_out_24mhz();

    rcc_periph_clock_enable(RCC_GPIOC);
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_GPIOB);
    rcc_periph_clock_enable(RCC_USART1);
    rcc_periph_clock_enable(RCC_AFIO);

    gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO13);

    gpio_set_mode(GPIOB, GPIO_MODE_INPUT, GPIO_CNF_INPUT_PULL_UPDOWN, GPIO12);
    gpio_set(GPIOB, GPIO12);
    nvic_enable_irq(NVIC_EXTI15_10_IRQ);

    gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO9);

    usart_set_baudrate(USART1, 115200);
    usart_set_databits(USART1, 8);
    usart_set_stopbits(USART1, USART_STOPBITS_1);
    usart_set_mode(USART1, USART_MODE_TX);
    usart_set_parity(USART1, USART_PARITY_NONE);
    usart_set_flow_control(USART1, USART_FLOWCONTROL_NONE);
    usart_enable(USART1);
}

void STMHardware::ButtonInterruptHandler()
{
    _button.InterruptHandler();
}

ILog& STMHardware::Log()
{
    return _log;
}

IButton& STMHardware::Button()
{
    return _button;
}

static STMHardware& GetSTMHardware()
{
    static STMHardware hw;
    return hw;
}

IHardware& GetHardware()
{
    return GetSTMHardware();
}

extern "C" void exti15_10_isr()
{
    GetSTMHardware().ButtonInterruptHandler();
}

extern void run();

int main()
{
    GetSTMHardware().Initialize();

    run();

    //    while(true)
    //    {
    //        gpio_clear(GPIOC, GPIO13);
    //        for(int i = 0; i < 400'000; i++)
    //        {
    //            asm volatile("nop");
    //        }
    //        gpio_set(GPIOC, GPIO13);
    //        for(int i = 0; i < 400'000; i++)
    //        {
    //            asm volatile("nop");
    //        }
    //
    //        usart_send_blocking(USART1, 'A');
    //    }
    return 0;
}