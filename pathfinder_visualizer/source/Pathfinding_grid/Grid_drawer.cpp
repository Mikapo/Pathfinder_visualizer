#include "Grid_drawer.h"

#include <cmath>
#include <iostream>

#define COORDINATE_SYSTEM_WIDTH 1980.0f
#define COORDINATE_SYSTEM_HEIGHT 1080.0f

void Grid_drawer::draw_to(Grid_interface* grid, int X, int Y) 
{ 
	size_t grid_width;
    size_t grid_height;
    grid->get_dimensions(grid_width, grid_height);

    float box_width = (COORDINATE_SYSTEM_WIDTH - 61) / (float)grid_width;
    float box_height = (COORDINATE_SYSTEM_HEIGHT - 26)/ (float)grid_height;

    float column =  std::floor(X / box_width);
    float row = std::floor(Y / box_height);

    grid->reset();
    grid->set_tile(column, row, mode);
}

void Grid_drawer::set_mode(Tile_type mode) { this->mode = mode; }
