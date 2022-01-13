#pragma once

#include "Pathfinding_algorimth.h"

class Breadth_first_search : public Pathfinding_algorimth
{
public:
    void find_path(Grid_interface* grid, int delay) override;

private:
    struct Previous_tile
    {
        Previous_tile(int prev)
        {
            tile = {Tile_type::wall, -1 - 1};
            previous_index = prev;
        }
        Previous_tile(int prev, Tile tile)
        {
            this->tile = tile;
            previous_index = prev;
        }

        Tile tile;
        int previous_index;
        bool is_goal = false;
    };

    void color_path(Grid_interface* grid, Previous_tile end, const std::vector<Previous_tile>& prev, int delay);
};
