#include "Grid_renderer.h"

#include "Grid_interface.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_projection.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/matrix.hpp"
#include <iostream>

#define COORDINATE_SYSTEM_WIDTH 1980.0f
#define COORDINATE_SYSTEM_HEIGHT 1080.0f

void Grid_renderer::init(const std::string& shader_path) { shader = new Shader(shader_path); }

void Grid_renderer::cleanup() { delete shader; }

std::mutex m;
void render_thread(const Grid_renderer* rend, const Grid_interface* grid, int hmin, int hmax)
{
    size_t grid_width;
    size_t grid_height;
    grid->get_dimensions(grid_width, grid_height);

    float box_width = COORDINATE_SYSTEM_WIDTH / (float)grid_width;
    float box_height = COORDINATE_SYSTEM_HEIGHT / (float)grid_height;

    for (float a = hmin; a < hmax; a++)
    {
        float Y = (box_height * a) + (box_height / 2);

        for (float b = 0; b < grid_width; b++)
        {
            float X = (box_width * b) + (box_width / 2);
            Point2d loc = {X, Y};
            rend->draw_tile(loc, box_width - 2, box_height - 2, grid->get_tile(b, a));
        }
    }
}

void Grid_renderer::render(const Grid_interface* grid, Dimensions window_dimensions) const
{
    render_thread(this, grid, 0, 40);
}

void Grid_renderer::draw_tile(Point2d loc, float width, float height, Tile tile) const
{
    const float half_width = width / 2;
    const float half_height = height / 2;

    float positions[]{loc.X - half_width, loc.Y - half_height, loc.X + half_width, loc.Y - half_height,
                      loc.X + half_width, loc.Y + half_height, loc.X - half_width, loc.Y + half_height};

    unsigned int indices[]{0, 1, 2, 2, 3, 0};
    vertex_array va;
    vertex_buffer vb(positions, sizeof(float) * 4 * 2);
    vertex_buffer_layout layout;
    layout.push<float>(2);
    va.add_buffer(vb, layout);

    index_buffer ib(indices, 6);
    glm::mat4 matrix = glm::ortho(0.0f, COORDINATE_SYSTEM_WIDTH, 0.0f, COORDINATE_SYSTEM_HEIGHT);

    Grid_color grid_color = get_color(tile);
    shader->set_uniform4f("u_color", grid_color.R, grid_color.G, grid_color.B, grid_color.A);
    shader->set_uniform_mat4f("u_mvp", matrix);

    renderer.draw(va, ib, *shader);
}

Grid_color Grid_renderer::get_color(Tile tile) const
{
    if (tile.type != Tile_type::start && tile.type != Tile_type::goal)
    {
        if (tile.is_path)
            return {0.0f, 1.0f, 0.0f, 0.0f};
        else if (tile.checked)
            return {0.0f, 0.5f, 0.5f, 0.0f};
    }
        
    switch (tile.type)
    {
        case Tile_type::empty:
            return {0.7f, 0.7f, 1.0f, 0.0f};

        case Tile_type::wall:
            return {0.0f, 0.0f, 0.0f, 0.0f};

        case Tile_type::goal:
            return{1.0f, 0.0f, 0.0f, 0.0f};

        case Tile_type::start:
            return {1.0f, 0.0f, 0.0f, 0.0f};

        default:
            return {0.0f, 0.0f, 0.0f, 0.0f};
    }
}
