#pragma once
#include "cube_data.h"
#include "../hc595/hc595.h"

class cube : private hc595, private cube_frame
{
private:
    // todo
    volatile bool _render_lock;

public:
    cube(spi_inst_t *spi,
         uint ds = PICO_DEFAULT_SPI_MOSI,
         uint shclk = PICO_DEFAULT_SPI_SCK,
         uint stclk = PICO_DEFAULT_SPI_CS);
    ~cube();
    void render();
    // todo
};
