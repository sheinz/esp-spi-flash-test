#include <stdint.h>
#include "spi_regs.h"

void ets_printf(const char*, ...);
void ets_delay_us(uint32_t us);

#define TEST_ADDR  (0x200000)

// 0-63 bytes read works fine
// 64 bytes read doesn't work
// 64 bytes write works fine
#define SIZE  64

void test_spi_read()
{
    int i;
    uint32_t buf[16];

    SPI(0).ADDR = TEST_ADDR | (SIZE << 24);
    SPI(0).CMD = SPI_CMD_READ;

    while (SPI(0).CMD) {};

    for (i = 0; i < 16; i++) {
        buf[i] = SPI(0).W[i];
    }

    for (i = 0; i < 16; i++) {
        ets_printf("Data[%d]=%x\n", i, buf[i]);
    }
}

void test_spi_write(uint8_t value)
{
    int i;
    uint32_t buf[16];

    for (i = 0; i < SIZE; i++) {
        ((uint8_t*)buf)[i] = value;
    }

    SPI(0).ADDR = TEST_ADDR | (SIZE << 24);
    for (i = 0; i < 16; i++) {
        SPI(0).W[i] = buf[i];
    }

    SPI(0).CMD = SPI_CMD_WRITE_ENABLE;
    while (SPI(0).CMD) {}

    SPI(0).CMD = SPI_CMD_PP;

    while (SPI(0).CMD) {};
}

void call_user_start()
{
    uint8_t value = 0xAA;

    while (1) {
        ets_printf("Start writing\n");
        test_spi_write(value);
        ets_printf("Writing done\n");

        ets_printf("Start reading\n");
        test_spi_read();
        ets_printf("Reading done\n");

        ets_delay_us(1000000);
    }
}
