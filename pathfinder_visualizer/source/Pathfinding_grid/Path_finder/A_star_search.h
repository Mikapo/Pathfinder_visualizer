#pragma once

#include "Pathfinding_algorimth.h"

class A_star_search : public Pathfinding_algorimth
{
public:
    void find_path(Grid_interface* grid, int delay) override;

private:
    int distance_to_goal(Tile tile, Tile goal);

    struct Node
    {
        Node(Node* previous, Tile tile, int moves, int distance_to_goal)
            : previous(previous), tile(tile), moves(moves), distance_to_goal(distance_to_goal)
        {
        }

        bool operator<(const Node& other)
        {
            int a_value = distance_to_goal + moves;
            int b_value = other.distance_to_goal + other.moves;
            return a_value < b_value;
        }
        bool operator>(const Node& other)
        {
            int a_value = distance_to_goal + moves;
            int b_value = other.distance_to_goal + other.moves;
            return a_value > b_value;
        }

        Node* previous;
        Tile tile;
        int moves;
        int distance_to_goal;
    };
};
