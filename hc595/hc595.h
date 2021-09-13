#pragma once
#include <stddef.h>
#include "pico/types.h"
#include "pico.h"
#include "pico/stdlib.h"

#ifndef i2c_default
#define i2c_default i2c0
#endif
#ifndef PICO_DEFAULT_I2C_SDA_PIN
#define PICO_DEFAULT_I2C_SDA_PIN 4
#endif
#ifndef PICO_DEFAULT_I2C_SCL_PIN
#define PICO_DEFAULT_I2C_SCL_PIN 5
#endif

class hc595
{
private:
    size_t _link_count; //how many 595 chips are linked
    uint _ser;          // data serial
    uint _srclk;        // shift register clock input
    uint _rclk;         // register clock input
    /*! \brief  write the buffer to 595. It takes 3*sleep_time us to send every byte of data. In this case, 6 us/B
    * \param src buffer to write
    */
    inline void _write_raw(const uint8_t *src);
    /*! \brief  send a rise to rclk, move the data to output
    */
    inline void _out();

public:
    /*! \brief  Create a 74hc595 link object on a specified i2c port. 
    * \param ser GPIO number to ser pin on 595. default = PICO_DEFAULT_I2C_SDA_PIN
    * \param srclk GPIO number to srclk pin on 595. default = PICO_DEFAULT_I2C_SCL_PIN
    * \param rclk GPIO number to RCLK pin on 595. default = 3
    * \param count The count of 595 link. default = 1
    */
    hc595(uint ser = PICO_DEFAULT_I2C_SDA_PIN,
          uint srclk = PICO_DEFAULT_I2C_SCL_PIN,
          uint rclk = 3,
          size_t count = 1);
    /*! \brief  Write data to 595 from the buffer
    * \param buf Pointer to data array. Note: the size of the buffer MUST be longer than the count of the 595 chip in the link, or could lead to memory leak. 
    */
    void write(const uint8_t *buf);
    /*! \brief  Clear all 595s
    */
    void clear(void);
    ~hc595();
};
