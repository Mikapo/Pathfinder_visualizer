#pragma once

#include "Rendering/Renderer.h"
#include "Dimensions.h"
#include "Grid_interface.h"

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

class Grid_renderer
{
public:
  
    void init(const std::string& shader_path);
    void cleanup();
    void render(const Grid_interface* grid, Dimensions window_dimensions) const;

private:
    void draw_tile(Point2d loc, float width, float height, Tile tile) const;
    Grid_color get_color(Tile tile) const;
    

    Shader* shader;
    Renderer renderer;
    std::vector<std::future<void>> threads;

    friend void render_thread(const Grid_renderer* rend, const Grid_interface* grid, int hmin, int hmax);
};
