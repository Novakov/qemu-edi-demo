#include "arm.h"

/* Now the SWI numbers and reason codes for RDI (Angel) monitors.  */
#define AngelSWI_ARM 0x123456
#ifdef __thumb__
#    define AngelSWI 0xAB
#else
#    define AngelSWI AngelSWI_ARM
#endif
/* For thumb only architectures use the BKPT instruction instead of SWI.  */
#ifdef THUMB_V7M_V6M
#    define AngelSWIInsn "bkpt"
#    define AngelSWIAsm bkpt
#else
#    define AngelSWIInsn "swi"
#    define AngelSWIAsm swi
#endif

/* The reason codes:  */
#define AngelSWI_Reason_Open 0x01
#define AngelSWI_Reason_Close 0x02
#define AngelSWI_Reason_WriteC 0x03
#define AngelSWI_Reason_Write0 0x04
#define AngelSWI_Reason_Write 0x05
#define AngelSWI_Reason_Read 0x06
#define AngelSWI_Reason_ReadC 0x07
#define AngelSWI_Reason_IsTTY 0x09
#define AngelSWI_Reason_Seek 0x0A
#define AngelSWI_Reason_FLen 0x0C
#define AngelSWI_Reason_TmpNam 0x0D
#define AngelSWI_Reason_Remove 0x0E
#define AngelSWI_Reason_Rename 0x0F
#define AngelSWI_Reason_Clock 0x10
#define AngelSWI_Reason_Time 0x11
#define AngelSWI_Reason_System 0x12
#define AngelSWI_Reason_Errno 0x13
#define AngelSWI_Reason_GetCmdLine 0x15
#define AngelSWI_Reason_HeapInfo 0x16
#define AngelSWI_Reason_EnterSVC 0x17
#define AngelSWI_Reason_Exit 0x18
#define ADP_Stopped_ApplicationExit ((2 << 16) + 38)
#define ADP_Stopped_RunTimeError ((2 << 16) + 35)

#if defined(ARM_RDI_MONITOR) && !defined(__ASSEMBLER__)

static inline int do_AngelSWI(int reason, void* arg)
{
    int value;
    asm volatile("mov r0, %1; mov r1, %2; " AngelSWIInsn " %a3; mov %0, r0"
                 : "=r"(value)                          /* Outputs */
                 : "r"(reason), "r"(arg), "i"(AngelSWI) /* Inputs */
                 : "r0", "r1", "r2", "r3", "ip", "lr", "memory", "cc"
                 /* Clobbers r0 and r1, and lr if in supervisor mode */);
    /* Accordingly to page 13-77 of ARM DUI 0040D other registers
       can also be clobbered.  Some memory positions may also be
       changed by a system call, so they should not be kept in
       registers. Note: we are assuming the manual is right and
       Angel is respecting the APCS.  */
    return value;
}

#endif
