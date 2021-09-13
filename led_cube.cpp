#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hc595/hc595.h"
#include "cube/cube_data.h"

int main()
{
    // stdio_init_all();
    uart_init(uart0, 115200);
    gpio_set_function(0, GPIO_FUNC_UART);
    gpio_set_function(1, GPIO_FUNC_UART);

    uart_puts(uart0, "hello world\r\n");

    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);

    uint SER = 4,
         SRCLK = 5,
         RCLK = 3;
    size_t count = 2;

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

    hc595 led(SER, SRCLK, RCLK, count);
    multicore_launch_core1([]{
        while (1)
        {
            gpio_put(25, 1);
            sleep_ms(100);
            gpio_put(25, 0);
            sleep_ms(300);
        }
    });

    while (1)
    {
        for (int i = 0; i < 16; i++)
        {
            // gpio_put(25, 1);
            // led.clear();
            led.write(frams[i]);
            // sleep_ms(20);
            // gpio_put(25, 0);
            sleep_ms(10);
        }
        // led.clear();
        // sleep_ms(100);
    }

    return 0;
}
