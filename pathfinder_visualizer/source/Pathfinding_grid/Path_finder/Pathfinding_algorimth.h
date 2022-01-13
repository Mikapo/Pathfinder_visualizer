#pragma once

#include "Pathfinding_grid/Grid_interface.h"

class Pathfinding_algorimth
{
public:
    void start(Grid_interface* grid, int delay)
    {
        if (on_going)
            return;

        on_going = true;
        grid->reset(); 
        find_path(grid, delay);
        on_going = false;
    }

    void stop() { on_going = false; }
    bool is_on_going() const { return on_going; }

protected:
    virtual void find_path(Grid_interface* grid, int delay) = 0;

    bool on_going = false;
};
