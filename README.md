# Description

This is demo for emBO++ 2021 talk "QEmu in-the-loop development" by Maciej Nowak.

* Structure application into two runner (HW and QEmu)
* Use EDI to interact with external simulators

# Build

1. Copy `local-example.cmake` as `.local/local.cmake`
2. Modify `.local/local.cmake` to include correct paths to toolchain (arm-none-eabi), QEmu and OpenOCD
3. Generate CMake build: `cmake -DLOCAL_CFG=<src>/.local/local.cmake <src>`
4. Build project (`cmake --build <build-dir>` or `make`/`ninja` in build directory)

# HW

1. Get Blue Pill (STM32F103 board)
2. Connect USB<->UART adapter to Blue pill (STM32's TX on PA9 pin to RX of adapter)
3. Connect button between PB12 and GND
4. UART adapter will receive logs (baudrate 115200)
5. Pressing button will be recognized by software and trigger some logs

# QEMU

1. Create venv `<build>/venv`
2. Install requirements `<build>/venv/Scripts/pip install -r requirements.txt`
3. Start listener `<build>/venv/Scripts/python <src>/host/listener.py`
4. Start
   QEMU: `qemu-system-arm -machine virt_cortex_m -semihosting -semihosting-config enable=on,target=native -monitor null -kernel <build>\app\qemu_runner\app_qemu.elf -device kp-edi-group`
5. Listener will receive logs from firmware and simulate button press every few seconds