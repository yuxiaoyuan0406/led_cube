#include "cube_data.h"

cube_frame::cube_frame()
{
    auto shit = new uint8_t[8][9];
    this->_data = (data_type)new uint8_t[8 * 9];
    this->_layer_display_time = 146;  // us
    this->clear();
}

void cube_frame::clear()
{
    for (size_t i = 0; i < 8; i++)
    {
        size_t j = 0;
        for(;j < 8; j++)
        {
            this->_data[i][j] = 0x00;
        }
        this->_data[i][j] = 0x01 << i;
    }
}

int cube_frame::set_byte(size_t row, size_t layer, uint8_t dat)
{
    this->_data[layer][row] = dat;
    return dat;
}

cube_frame::~cube_frame()
{
    delete[] (uint8_t*)this->_data;
}
