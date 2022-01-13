#pragma once
#include "Pathfinding_grid/Grid_interface.h"
#include "Pathfinding_algorimth.h"

#include <future>

enum class Pathfinding_algorimths
{
    Breadth_first_search,
    Dijkstras_algorithm
};

class Path_finder
{
public:
    Path_finder();

    void find_path(Grid_interface* grid, int delay);
    void stop_finding_path();
    void set_algorimth(Pathfinding_algorimths new_algorimth);
    bool is_on_going() const;

private:
    Pathfinding_algorimth* algorimth = nullptr;
    std::future<void> thread;
};
