# ESP8266 SPI flash read/write test

This is an experimental project to test low level SPI flash access.

It doesn't link any SDK to eliminate it's influence.
It only uses SPI register definition file from esp-open-rtos.
This file is included.

To build the project only xtensa-lx106 toolchain is needed.

## Problem
SPI register region contains DATA buffer. (W0-W15)
This buffer is used to write/read to/from SPI.
This DATA region consists of 16 4-byte registers.
So, the lotal length is 64 byte.

I assume that 64 bytes is the maximum block length that can be read or written
with SPI.
For writing it is the case, but for reading operation hangs if attempt to read
64 bytes.

Espressif code inside ESP8266 bootrom uses 32 bytes block SPI access.
They might know something...

In my test reading with blocks 0-63 bytes works fine. But 64 bytes read hangs.
Writing on the other hand is fine for the whole range (0-64).

If anyone can shed some lite on this issue, please let me know.

