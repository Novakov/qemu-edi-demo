#pragma once

struct ILog
{
    virtual void Log(const char* fmt, ...) = 0;
};

struct IButton
{
    virtual void WaitForPress() = 0;
};

struct IHardware
{
    virtual ILog& Log() = 0;
    virtual IButton& Button() = 0;
};

IHardware& GetHardware();