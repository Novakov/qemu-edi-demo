#include <cstdarg>
#include <cstdio>
#include <cstring>
#include "ARMCM3.h"
#include "HW.hpp"
#include "edi.h"
#include "edi_device.h"

class QEmuLog : public ILog
{
public:
    explicit QEmuLog(EDI* edi);

    void Initialize(const char* url);
    void Log(const char* fmt, ...) override;

private:
    EDI* _edi;
};

QEmuLog::QEmuLog(EDI* edi) : _edi{edi}
{
}

void QEmuLog::Initialize(const char* url)
{
    edi_communication_mode mode = edi_mode_push;
    edi_device_execute(_edi, edi_command_set_connection_type, &mode, sizeof(mode));
    edi_device_execute(_edi, edi_command_connect, url, strlen(url) + 1);
}

void QEmuLog::Log(const char* fmt, ...)
{
    char buf[200] = {0};

    va_list args;
    va_start(args, fmt);

    auto n = vsniprintf(buf, sizeof(buf), fmt, args);

    edi_device_execute(_edi, edi_command_write, buf, n);

    va_end(args);
}

class QEmuButton : public IButton
{
public:
    explicit QEmuButton(EDI* edi);

    void Initialize(const char* url, IRQn_Type irqn);

    void InterruptHandler();
    void WaitForPress() override;

private:
    EDI* _edi;
    volatile bool _pressed;
};

QEmuButton::QEmuButton(EDI* edi) : _edi{edi}, _pressed{false}
{
}

void QEmuButton::Initialize(const char* url, IRQn_Type irqn)
{
    edi_communication_mode mode = edi_mode_pair;
    edi_device_execute(_edi, edi_command_set_connection_type, &mode, sizeof(mode));
    edi_device_execute(_edi, edi_command_connect, url, strlen(url) + 1);
    edi_enable_interrupt(_edi, irqn);
}

void QEmuButton::InterruptHandler()
{
    _pressed = true;
}

void QEmuButton::WaitForPress()
{
    _pressed = false;
    char c = 'A';
    edi_device_execute(_edi, edi_command_write, &c, 1);

    while(!_pressed)
    {
        asm volatile("wfi");
    }

    edi_device_execute(_edi, edi_command_read, &c, 1);
    edi_device_execute(_edi, edi_command_remove_message, nullptr, 0);
}

class QEmuHardware : public IHardware
{
public:
    void Initialize();
    void ButtonInterruptHandler();
    ILog& Log() override;
    IButton& Button() override;

private:
    QEmuLog _log{EDI1};
    QEmuButton _button{EDI0};
};

void QEmuHardware::Initialize()
{
    _log.Initialize("tcp://127.0.0.1:10001");
    _button.Initialize("tcp://127.0.0.1:10000", Interrupt0_IRQn);
    NVIC_EnableIRQ(Interrupt0_IRQn);
}

void QEmuHardware::ButtonInterruptHandler()
{
    _button.InterruptHandler();
}
ILog& QEmuHardware::Log()
{
    return _log;
}
IButton& QEmuHardware::Button()
{
    return _button;
}

static QEmuHardware& GetQEmuHardware()
{
    static QEmuHardware hw;
    return hw;
}

IHardware& GetHardware()
{
    return GetQEmuHardware();
}

extern "C" void Interrupt0_Handler()
{
    GetQEmuHardware().ButtonInterruptHandler();
}

extern void run();

int main()
{
    printf("Hello World\n");

    GetQEmuHardware().Initialize();

    run();

    return 0;
}