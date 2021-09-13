#pragma once
#include <stdint.h>
#include <stddef.h>

class cube_frame
{
public:
    cube_frame();
    ~cube_frame();
    void clear();
    int set_byte(size_t row, size_t layer, uint8_t dat);

protected:
    typedef uint8_t (*data_type)[9];
    data_type _data;
    uint32_t _layer_display_time;

private:
};
