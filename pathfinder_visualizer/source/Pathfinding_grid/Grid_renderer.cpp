#include "Grid_renderer.h"

#include "Grid_interface.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_projection.hpp"
#include "glm/ext/matrix_transform.hpp"

#include "glm/matrix.hpp"
#include <iostream>

#define COORDINATE_SYSTEM_WIDTH 1980.0f
#define COORDINATE_SYSTEM_HEIGHT 1080.0f

void Grid_renderer::init(Grid_interface* grid)
{
    shader = new Shader("shaders/Shader.frag", "shaders/Shader.vert");
    calculate_verices(grid);
}

void Grid_renderer::cleanup() { delete shader; }

void Grid_renderer::render(const Grid_interface* grid)
{
    auto& tiles = grid->get_tiles();

    if (tiles.size() != vertices.size())
    {
        calculate_verices(grid);
    }

    //this is bottleneck
    for (int i = 0; i < tiles.size(); i++)
    {
        unsigned int indices[]{0, 1, 2, 2, 3, 0};
        vertex_array va;
        vertex_buffer vb(vertices[i].positions, sizeof(float) * 4 * 2);
        vertex_buffer_layout layout;
        layout.push<float>(2);
        va.add_buffer(vb, layout);

        index_buffer ib(indices, 6);
        glm::mat4 matrix = glm::ortho(0.0f, COORDINATE_SYSTEM_WIDTH, 0.0f, COORDINATE_SYSTEM_HEIGHT);

        Grid_color grid_color = get_color(tiles[i]);
        shader->set_uniform4f("u_color", grid_color.R, grid_color.G, grid_color.B, grid_color.A);
        shader->set_uniform_mat4f("u_mvp", matrix);

        renderer.draw(va, ib, *shader);
    }
};

void Grid_renderer::calculate_verices(const Grid_interface* grid)
{
    size_t grid_width;
    size_t grid_height;
    grid->get_dimensions(grid_width, grid_height);
    vertices.resize(grid_width * grid_height);

    float box_width = COORDINATE_SYSTEM_WIDTH / (float)grid_width;
    float box_height = COORDINATE_SYSTEM_HEIGHT / (float)grid_height;

    for (float a = 0; a < grid_height; a++)
    {
        float Y = (box_height * a) + (box_height / 2);

        for (float b = 0; b < grid_width; b++)
        {
            float X = (box_width * b) + (box_width / 2);
            Point2d loc = {X, Y};

            const float half_width = ((box_width - 2) / 2);
            const float half_height = ((box_height - 2) / 2);
            loc.Y = COORDINATE_SYSTEM_HEIGHT - loc.Y;

            float positions[]{loc.X - half_width, loc.Y - half_height, loc.X + half_width, loc.Y - half_height,
                              loc.X + half_width, loc.Y + half_height, loc.X - half_width, loc.Y + half_height};

            vertices[b + grid_width * a] = positions;
        }
    }
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
        return {1.0f, 0.0f, 0.0f, 0.0f};

    case Tile_type::start:
        return {1.0f, 0.0f, 0.0f, 0.0f};

    default:
        return {0.0f, 0.0f, 0.0f, 0.0f};
    }
}
