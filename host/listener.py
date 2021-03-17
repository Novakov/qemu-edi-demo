import time

from pynng import nng, Closed

import asyncio


async def main():
    btn_socket = nng.Pair0()
    btn_socket.listen('tcp://127.0.0.1:10000')

    log_socket = nng.Pull0()
    log_socket.listen('tcp://127.0.0.1:10001')

    async def handle_gpio():
        while True:
            try:
                await btn_socket.arecv()
                print('Received button wait request')
                time.sleep(2)
                print('Pressing button')
                await btn_socket.asend(b'ABCD')
            except Closed:
                break

    async def handle_log():
        while True:
            try:
                msg = await log_socket.arecv()
                print('LOG: ' + msg.decode('ascii'))
            except Closed:
                break

    gpio_handler = asyncio.create_task(handle_gpio())
    log_handler = asyncio.create_task(handle_log())

    try:
        while True:
            await asyncio.sleep(delay=1)
    except KeyboardInterrupt:
        pass

    btn_socket.close()
    log_socket.close()

    await gpio_handler
    await log_handler


asyncio.run(main())
