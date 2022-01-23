#pragma once

#include "Grid_interface.h"

class Grid_drawer
{
public:
    void draw_to(class Grid_interface* grid, int X, int Y);
    void set_mode(Tile_type mode);

private:
    Tile_type mode = Tile_type::empty;
};
