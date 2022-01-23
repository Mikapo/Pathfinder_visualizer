#include "A_star_search.h"
#include <iostream>
#include <memory>
#include <queue>
#include <thread>

void A_star_search::find_path(Grid_interface* grid, int delay)
{
    Tile start = grid->get_start();
    Tile goal = grid->get_goal();

    auto compare = [](Node* a, Node* b) {
        int a_value = a->distance_to_goal + a->moves * 2;
        int b_value = b->distance_to_goal + b->moves * 2;
        return a_value > b_value;
    };

    std::priority_queue<Node*, std::vector<Node*>, decltype(compare)> queue;

    std::vector<Node*> nodes;
    nodes.emplace_back(new Node(nullptr, start, 0, distance_to_goal(start, goal)));
    queue.push(nodes.back());

    Node* current_node;
    while (on_going)
    {
        current_node = queue.top();
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        auto neighbours = grid->get_neighbours(current_node->tile.column, current_node->tile.row);
        for (Tile neighbor : neighbours)
        {
            if (!neighbor.checked)
            {
                grid->set_checked(neighbor.column, neighbor.row);
                nodes.emplace_back(
                    new Node(current_node, neighbor, current_node->moves + 1, distance_to_goal(neighbor, goal)));
                queue.push(nodes.back());
            }

            if (neighbor.type == Tile_type::goal)
            {
                while (current_node && current_node->tile.type != Tile_type::start)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
                    grid->set_as_path(current_node->tile.column, current_node->tile.row);
                    current_node = current_node->previous;
                }

                for (Node* node : nodes)
                    delete node;
                return;
            }
        }
        queue.pop();
    }

    for (Node* node : nodes)
        delete node;
}

int A_star_search::distance_to_goal(Tile tile, Tile goal)
{
    int column_distance;
    if (tile.column > goal.column)
        column_distance = tile.column - goal.column;
    else
        column_distance = goal.column - tile.column;

    int row_distance;
    if (tile.row > goal.row)
        row_distance = tile.row - goal.row;
    else
        row_distance = goal.row - tile.row;

    return column_distance + row_distance;
}
