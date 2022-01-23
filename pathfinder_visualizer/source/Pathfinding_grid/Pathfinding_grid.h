#pragma once

#include "Grid.h"
#include "Grid_renderer.h"
#include "Path_finder/Path_finder.h"
#include "Grid_drawer.h"

class Pathfinding_grid
{
public:
    Pathfinding_grid();

    void init();
    void cleanup();
    void set_tile(size_t column, size_t row, Tile_type type) { grid.set_tile(column, row, type); }
    void render(Dimensions window_dimensions) { renderer.render(&grid); }
    void switch_path_finding_algorimth(Pathfinding_algorimths alg) { path_finder.set_algorimth(alg); }
    void start_pathfinding();
    void stop_pathfinding();
    void draw_to_grid(int X, int Y);
    void set_draw_mode(Tile_type mode) { drawer.set_mode(mode); }

private:
    Grid grid;
    Grid_renderer renderer;
    Grid_drawer drawer;
    Path_finder path_finder;
};
