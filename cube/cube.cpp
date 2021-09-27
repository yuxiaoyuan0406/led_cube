#include "cube.h"
#include "pico/time.h"

cube::cube(spi_inst_t *spi, uint ds, uint shclk, uint stclk)
    : hc595(spi, ds, shclk, stclk, 9), cube_frame()
{
    this->cube_frame::clear();
    this->hc595::clear();
    this->_render_lock = false;
}

cube::~cube()
{
}

void cube::render()
{
    for (size_t i = 0; i < 8; i++)
    {
        if (this->_render_lock)
        {
            continue;
        }
        this->_render_lock = true;
        this->hc595::write(this->cube_frame::_data[i]);
        this->_render_lock = true;
        sleep_us(this->cube_frame::_layer_display_time);
    }
}
