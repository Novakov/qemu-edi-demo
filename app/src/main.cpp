#include "HW.hpp"

void run()
{
    while(true)
    {
        GetHardware().Log().Log("Requesting button press...");
        GetHardware().Button().WaitForPress();
        GetHardware().Log().Log("Button pressed");
    }
}