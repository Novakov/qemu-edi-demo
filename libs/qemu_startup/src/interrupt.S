    .altmacro
    .macro   Process_Interrupt handler, number
        \handler Interrupt\number\()_Handler
    .endm

    .macro   Reference_Interrupt  Handler_Name
        .long    \Handler_Name
    .endm

    .macro Process_Interrupt_List handler
        .set                irq_counter, 0
        .rept               InterruptCount
            Process_Interrupt       \handler, %irq_counter
            .set                    irq_counter, irq_counter + 1
        .endr
    .endm
