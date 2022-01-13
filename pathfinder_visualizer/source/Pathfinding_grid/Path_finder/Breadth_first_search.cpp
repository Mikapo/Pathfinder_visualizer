#include "Breadth_first_search.h"

#include <queue>
#include <thread>



void Breadth_first_search::find_path(Grid_interface* grid, int delay)
{
    size_t width;
    size_t height;
    grid->get_dimensions(width, height);
    std::vector<Previous_tile> prev;
    prev.assign(width * height, Previous_tile(-1));

    std::queue<Tile> queue;
    queue.push(grid->get_start());
    while (!queue.empty() && on_going)
    {
        Tile current = queue.front();
        std::vector<Tile> neighbours = grid->get_neighbours(current.column, current.row);

        for (Tile neighbour : neighbours)
        {
            if (!neighbour.checked)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(delay));
                grid->set_checked(neighbour.column, neighbour.row);
                queue.push(neighbour);
                prev[neighbour.column + width * neighbour.row] = Previous_tile(current.column + width * current.row, neighbour);
                if (neighbour.type == Tile_type::goal)
                {
                    color_path(grid, prev[neighbour.column + width * neighbour.row], prev, delay);
                    return;
                }
            }
        }
        queue.pop();
    }
}

void Breadth_first_search::color_path(
    Grid_interface* grid, Previous_tile end, const std::vector<Previous_tile>& prev, int delay)
{
    Previous_tile current = end;
    Tile goal = grid->get_start();

    while (prev[current.previous_index].previous_index != -1)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        grid->set_as_path(current.tile.column, current.tile.row);
        current = prev[current.previous_index]; 

        if (current.tile.column == goal.column && current.tile.row == goal.row)
            return;
    }
}


