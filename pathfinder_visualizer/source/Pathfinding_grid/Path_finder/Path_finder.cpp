#include "Path_finder.h"

#include "A_star_search.h"
#include "Breadth_first_search.h"

#include <thread>

void path_finding_thread(Grid_interface* grid, int delay, Pathfinding_algorimth* alg)
{
    if (alg)
        alg->start(grid, delay);
}

Path_finder::Path_finder() { algorimth = new Breadth_first_search; }

Path_finder::~Path_finder()
{
    if (algorimth)
        delete algorimth;
}

void Path_finder::find_path(Grid_interface* grid, int delay)
{
    if (next_algorimth.has_value())
    {
        set_algorimth(next_algorimth.value());
        next_algorimth.reset();
    }

    if (!is_on_going() && algorimth)
        thread = std::async(std::launch::async, path_finding_thread, grid, delay, algorimth);
}

void Path_finder::stop_finding_path()
{
    if (algorimth && is_on_going())
        algorimth->stop();
}

void Path_finder::set_algorimth(Pathfinding_algorimths new_algorimth)
{
    if (is_on_going())
    {
        next_algorimth = new_algorimth;
        return;
    }
    else
        next_algorimth.reset();

    if (algorimth)
        delete algorimth;

    switch (new_algorimth)
    {
    case Pathfinding_algorimths::Breadth_first_search:
        algorimth = new Breadth_first_search;
        break;

    case Pathfinding_algorimths::Dijkstras_algorithm:
        algorimth = new A_star_search;
        break;
    }
}

bool Path_finder::is_on_going() const
{
    if (!algorimth)
        return false;
    else
        return algorimth->is_on_going();
}
