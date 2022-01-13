#include "Pathfinding_grid.h"

Pathfinding_grid::Pathfinding_grid() : grid(80, 40)
{
    grid.set_tile(3, 3, Tile_type::start);
    grid.set_tile(20, 3, Tile_type::goal);
   
}

void Pathfinding_grid::init() { renderer.init("shaders/Shader.shader"); }

void Pathfinding_grid::cleanup() { renderer.cleanup(); }

void Pathfinding_grid::start_pathfinding() { path_finder.find_path(&grid, 10); }

void Pathfinding_grid::stop_pathfinding()
{
    if (path_finder.is_on_going())
    {
        path_finder.stop_finding_path();
    }
}
