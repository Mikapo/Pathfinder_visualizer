#include "Grid.h"

Grid::Grid(size_t columns, size_t rows) : columns(columns), rows(rows)
{
    tiles.reserve(columns * rows);
    for (size_t a = 0; a < rows; a++)
        for (size_t b = 0; b < columns; b++)
            tiles.push_back(Tile{ Tile_type::empty, (int)b, (int)a });
}

void Grid::set_tile(size_t column, size_t row, Tile_type type)
{
    if (columns > columns || row > rows)
        throw("too high arguments passed to set_tile function");

    Tile tile = get_tile(column, row);
    if (tile.type == Tile_type::goal || tile.type == Tile_type::start)
        return;

    if (type == Tile_type::start)
    {
        if (start_index != -1)
            tiles[start_index].type = Tile_type::empty;

        int index = column + columns * row;
        start_index = index;
        tiles[index].type = Tile_type::start;
    }
    else if (type == Tile_type::goal)
    {
        if (goal_index != -1)
            tiles[goal_index].type = Tile_type::empty;

        int index = column + columns * row;
        goal_index = index;
        tiles[index].type = Tile_type::goal;
    }
    else
        tiles[column + columns * row].type = type;
}

Tile Grid::get_tile(size_t column, size_t row) const { return tiles[column + columns * row]; }

void Grid::get_dimensions(size_t& out_width, size_t& out_height) const
{
    out_width = columns;
    out_height = rows;
}

std::vector<Tile> Grid::get_neighbours(size_t column, size_t row) const
{
    std::vector<Tile> output;
    output.reserve(4);
    int size = tiles.size();

    // top
    if (is_valid_tile_index(column + columns * (row - 1)))
        if (row != 0 && is_not_wall(column, row - 1))
            output.push_back(get_tile(column, row - 1));

    // botton
    if (is_valid_tile_index(column + columns * (row + 1)))
        if (row < rows && is_not_wall(column, row + 1))
            output.push_back(get_tile(column, row + 1));

    // left
    if (is_valid_tile_index((column - 1) + columns * row))
        if (column != 0 && is_not_wall(column - 1, row))
            output.push_back(get_tile(column - 1, row));

    // right
    if (is_valid_tile_index((column + 1) + columns * row))
        if (column < columns && is_not_wall(column + 1, row))
            output.push_back(get_tile(column + 1, row));

    return output;
}

void Grid::set_checked(size_t column, size_t row) { tiles[column + columns * row].checked = true; }

void Grid::set_as_path(size_t column, size_t row) { tiles[column + columns * row].is_path = true; }

void Grid::reset()
{
    for (Tile& tile : tiles)
    {
        tile.checked = false;
        tile.is_path = false;
    }
}

Tile Grid::get_start() const { return tiles[start_index]; }

Tile Grid::get_goal() const { return tiles[goal_index]; }

bool Grid::is_not_wall(size_t column, size_t row) const { return get_tile(column, row).type != Tile_type::wall; }

bool Grid::is_valid_tile_index(int index) const
{
    int size = tiles.size();
    return index > 0 && index < size - 1;
}
