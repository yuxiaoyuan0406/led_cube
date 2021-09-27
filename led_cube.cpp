#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hc595/hc595.h"
// #include "cube/cube_data.h"

int main()
{
    // stdio_init_all();
    uart_init(uart0, 115200);
    gpio_set_function(0, GPIO_FUNC_UART);
    gpio_set_function(1, GPIO_FUNC_UART);

    uart_puts(uart0, "hello world\r\n");

    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);

    uint DS = 3,        // MOSI
         SHCLK = 2,     // SCK
         STCLK = 5;     // CS
    size_t count = 1;

    uint8_t frams[][2] = {
        0x00, 0x01,
        0x00, 0x01<<1,
        0x00, 0x01<<2,
        0x00, 0x01<<3,
        0x00, 0x01<<4,
        0x00, 0x01<<5,
        0x00, 0x01<<6,
        0x00, 0x01<<7,
        0x01, 0x00,
        0x01<<1, 0x00,
        0x01<<2, 0x00,
        0x01<<3, 0x00,
        0x01<<4, 0x00,
        0x01<<5, 0x00,
        0x01<<6, 0x00,
        0x01<<7, 0x00,
        };

    hc595 led(spi0, DS, SHCLK, STCLK, count);
    multicore_launch_core1([]{
        while (1)
        {
            gpio_put(25, 1);
            sleep_ms(50);
            gpio_put(25, 0);
            sleep_ms(300);
        }
    });

    while (1)
    {
        for (int i = 0; i < 8; i++)
        {
            uint8_t val = 0x01 << i;
            // gpio_put(25, 1);
            // led.clear();
            led.write(&val);
            // sleep_ms(20);
            // gpio_put(25, 0);
            // sleep_ms(10);
        }
        // led.clear();
        // sleep_ms(100);
    }

    return 0;
}
