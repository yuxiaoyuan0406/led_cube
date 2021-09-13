#pragma once
#include "cube_data.h"
#include "../hc595/hc595.h"

class cube : private hc595, private cube_frame
{
private:
    // todo
    volatile bool _render_lock;

public:
    cube(uint ser = PICO_DEFAULT_I2C_SDA_PIN,
         uint srclk = PICO_DEFAULT_I2C_SCL_PIN,
         uint rclk = 3);
    ~cube();
    void render();
    // todo
};
