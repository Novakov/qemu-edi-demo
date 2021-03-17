__attribute__ ((weak, noreturn)) void DefaultInterruptHandler()
{
    for(;;);
}

#ifdef GENERATE_ALIASED_INTERRUPTS
#define GENERATE_INTERRUPT(NAME) __attribute__((weak, alias("DefaultInterruptHandler"), noreturn)) void NAME(void);
#else
#define GENERATE_INTERRUPT(NAME)                                \
        __attribute__((weak, used, noreturn)) void NAME(void)   \
        {                                                       \
            DefaultInterruptHandler();                          \
        }
#endif

GENERATE_INTERRUPT(NMI_Handler)
GENERATE_INTERRUPT(HardFault_Handler)
GENERATE_INTERRUPT(MemManage_Handler)
GENERATE_INTERRUPT(BusFault_Handler)
GENERATE_INTERRUPT(UsageFault_Handler)
GENERATE_INTERRUPT(SVC_Handler)
GENERATE_INTERRUPT(DebugMon_Handler)
GENERATE_INTERRUPT(PendSV_Handler)
GENERATE_INTERRUPT(SysTick_Handler)

GENERATE_INTERRUPT(Interrupt0_Handler)
GENERATE_INTERRUPT(Interrupt1_Handler)
GENERATE_INTERRUPT(Interrupt2_Handler)
GENERATE_INTERRUPT(Interrupt3_Handler)
GENERATE_INTERRUPT(Interrupt4_Handler)
GENERATE_INTERRUPT(Interrupt5_Handler)
GENERATE_INTERRUPT(Interrupt6_Handler)
GENERATE_INTERRUPT(Interrupt7_Handler)
GENERATE_INTERRUPT(Interrupt8_Handler)
GENERATE_INTERRUPT(Interrupt9_Handler)
GENERATE_INTERRUPT(Interrupt10_Handler)
GENERATE_INTERRUPT(Interrupt11_Handler)
GENERATE_INTERRUPT(Interrupt12_Handler)
GENERATE_INTERRUPT(Interrupt13_Handler)
GENERATE_INTERRUPT(Interrupt14_Handler)
GENERATE_INTERRUPT(Interrupt15_Handler)
GENERATE_INTERRUPT(Interrupt16_Handler)
GENERATE_INTERRUPT(Interrupt17_Handler)
GENERATE_INTERRUPT(Interrupt18_Handler)
GENERATE_INTERRUPT(Interrupt19_Handler)
GENERATE_INTERRUPT(Interrupt20_Handler)
GENERATE_INTERRUPT(Interrupt21_Handler)
GENERATE_INTERRUPT(Interrupt22_Handler)
GENERATE_INTERRUPT(Interrupt23_Handler)
GENERATE_INTERRUPT(Interrupt24_Handler)
GENERATE_INTERRUPT(Interrupt25_Handler)
GENERATE_INTERRUPT(Interrupt26_Handler)
GENERATE_INTERRUPT(Interrupt27_Handler)
GENERATE_INTERRUPT(Interrupt28_Handler)
GENERATE_INTERRUPT(Interrupt29_Handler)
GENERATE_INTERRUPT(Interrupt30_Handler)
GENERATE_INTERRUPT(Interrupt31_Handler)
GENERATE_INTERRUPT(Interrupt32_Handler)
GENERATE_INTERRUPT(Interrupt33_Handler)
GENERATE_INTERRUPT(Interrupt34_Handler)
GENERATE_INTERRUPT(Interrupt35_Handler)
GENERATE_INTERRUPT(Interrupt36_Handler)
GENERATE_INTERRUPT(Interrupt37_Handler)
GENERATE_INTERRUPT(Interrupt38_Handler)
GENERATE_INTERRUPT(Interrupt39_Handler)
GENERATE_INTERRUPT(Interrupt40_Handler)
GENERATE_INTERRUPT(Interrupt41_Handler)
GENERATE_INTERRUPT(Interrupt42_Handler)
GENERATE_INTERRUPT(Interrupt43_Handler)
GENERATE_INTERRUPT(Interrupt44_Handler)
GENERATE_INTERRUPT(Interrupt45_Handler)
GENERATE_INTERRUPT(Interrupt46_Handler)
GENERATE_INTERRUPT(Interrupt47_Handler)
GENERATE_INTERRUPT(Interrupt48_Handler)
GENERATE_INTERRUPT(Interrupt49_Handler)
GENERATE_INTERRUPT(Interrupt50_Handler)
GENERATE_INTERRUPT(Interrupt51_Handler)
GENERATE_INTERRUPT(Interrupt52_Handler)
GENERATE_INTERRUPT(Interrupt53_Handler)
GENERATE_INTERRUPT(Interrupt54_Handler)
GENERATE_INTERRUPT(Interrupt55_Handler)
GENERATE_INTERRUPT(Interrupt56_Handler)
GENERATE_INTERRUPT(Interrupt57_Handler)
GENERATE_INTERRUPT(Interrupt58_Handler)
GENERATE_INTERRUPT(Interrupt59_Handler)
GENERATE_INTERRUPT(Interrupt60_Handler)
GENERATE_INTERRUPT(Interrupt61_Handler)
GENERATE_INTERRUPT(Interrupt62_Handler)
GENERATE_INTERRUPT(Interrupt63_Handler)
GENERATE_INTERRUPT(Interrupt64_Handler)
GENERATE_INTERRUPT(Interrupt65_Handler)
GENERATE_INTERRUPT(Interrupt66_Handler)
GENERATE_INTERRUPT(Interrupt67_Handler)
GENERATE_INTERRUPT(Interrupt68_Handler)
GENERATE_INTERRUPT(Interrupt69_Handler)