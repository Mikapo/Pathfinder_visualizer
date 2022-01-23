#pragma once

#include "Dimensions.h"
#include "Grid_interface.h"
#include "Rendering/Renderer.h"

#include <future>
#include <vector>

struct Point2d
{
    float X;
    float Y;
};

struct Grid_color
{
    float R;
    float G;
    float B;
    float A;
};


struct Tile_vertex
{
    Tile_vertex() = default;
    Tile_vertex(float positions[8])
    {
        for (size_t i = 0; i < 8; i++)
            this->positions[i] = positions[i];
    }
    float positions[8];
};

class Grid_renderer
{
public:
    void init(Grid_interface* grid);
    void cleanup();
    void render(const Grid_interface* grid);

private:
    void calculate_verices(const Grid_interface* grid);
    Grid_color get_color(Tile tile) const;

    Shader* shader;
    Renderer renderer;
    std::vector<Tile_vertex> vertices;
};
