#pragma once

#include <vector>

enum class Tile_type 
{
	empty,
	goal,
	start,
	wall,
	expensive1,
	expensive2,
	expensive3
};

struct Tile
{
    Tile_type type;
    int column;
    int row;
    bool checked = false;
    bool is_path = false;
};

class Grid_interface
{
public:
    virtual void set_tile(size_t column, size_t row, Tile_type type) = 0;
    virtual Tile get_tile(size_t column, size_t row) const = 0;
    virtual void get_dimensions(size_t& out_width, size_t& out_height) const = 0;
    virtual std::vector<Tile> get_neighbours(size_t column, size_t row) const = 0;
    virtual void set_checked(size_t column, size_t row) = 0;
    virtual void set_as_path(size_t column, size_t row) = 0;
    virtual void reset() = 0;
    virtual Tile get_start() const = 0;
    virtual Tile get_goal() const = 0;
};
