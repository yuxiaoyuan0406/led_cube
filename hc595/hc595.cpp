#include "hc595.h"
#include <stdio.h>

#ifdef _DEBUG
#include <stdio.h>
#endif // _DEBUG

static uint default_baudrate = 400 * 1000;
static uint sleep_time = 2;

hc595::hc595(uint ser, uint srclk, uint rclk, size_t count) : _link_count(count), _ser(ser), _srclk(srclk), _rclk(rclk)
{
    //     if (this->_i2c_port->hw->enable == 0)
    //     {
    // #ifdef _DEBUG
    //         printf("I2C port initializing...\r\n");
    // #endif // _DEBUG
    //         i2c_init(this->_i2c_port, default_baudrate);
    //         gpio_set_function(this->_ser, GPIO_FUNC_I2C);
    //         gpio_set_function(this->_srclk, GPIO_FUNC_I2C);
    //         gpio_pull_up(this->_ser);
    //         gpio_pull_up(this->_srclk);
    //     }
    // #ifdef _DEBUG
    //     else
    //     {
    //         printf("I2C port already initialized.\r\n");
    //     }
    // #endif // _DEBUG
    gpio_init(this->_ser);
    gpio_init(this->_srclk);
    gpio_set_dir(this->_ser, GPIO_OUT);
    gpio_set_dir(this->_srclk, GPIO_OUT);
    gpio_put(this->_ser, 0);
    gpio_put(this->_srclk, 0);

    gpio_init(this->_rclk);
    gpio_set_dir(this->_rclk, GPIO_OUT);
    gpio_put(this->_rclk, 0);

    // this->clear();
}

void hc595::write(const uint8_t *buf)
{
    gpio_put(this->_rclk, 0);
    this->_write_raw(buf);
    this->_out();
}

inline void hc595::_write_raw(const uint8_t *src)
{
    for (size_t i = 0; i < this->_link_count; i++)
    {
        uint8_t val = *(src + i);
        // char buffer[32];
        // sprintf(buffer, "Writing 0x%02X\r\n", val);
        // uart_puts(uart0, buffer);
        // printf("Writing 0x%02X\n", val);
        for (size_t j = 0; j < 8; j++)
        {
            gpio_put(this->_ser, val >> 7);
            val = val << 1;
            sleep_us(sleep_time);

            gpio_put(this->_srclk, 1); // rise
            sleep_us(sleep_time);
            gpio_put(this->_srclk, 0);
            sleep_us(sleep_time);
        }
    }
}

void hc595::clear()
{
    // uart_puts(uart0, "Clearing\r\n");
    gpio_put(this->_rclk, 0);
    for (size_t i = 0; i < 1 + 8 * this->_link_count; i++)
    {
        gpio_put(this->_ser, 0);
        sleep_us(sleep_time);

        gpio_put(this->_srclk, 1); // rise
        sleep_us(sleep_time);
        gpio_put(this->_srclk, 0);
        sleep_us(sleep_time);
    }
    this->_out();
}

inline void hc595::_out()
{
    // sleep_us(sleep_time);
    gpio_put(this->_rclk, 1); // rise
    sleep_us(sleep_time);
    gpio_put(this->_rclk, 0);
}

hc595::~hc595()
{
}
