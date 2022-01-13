#pragma once

#include "Grid_interface.h"

class Grid : public Grid_interface
{
public:
    Grid(size_t columns, size_t rows);

    void set_tile(size_t column, size_t row, Tile_type type) override;
    Tile get_tile(size_t column, size_t row) const override;
    void get_dimensions(size_t& out_width, size_t& out_height) const override;
    std::vector<Tile> get_neighbours(size_t column, size_t row) const override;
    virtual void set_checked(size_t column, size_t row) override;
    virtual void set_as_path(size_t column, size_t row) override;
    virtual void reset() override;
    Tile get_start() const override;
    Tile get_goal() const override;

private:
    bool is_not_wall(size_t column, size_t row) const;
    bool is_valid_tile_index(int index) const;

    std::vector<Tile> tiles;
    const size_t columns;
    const size_t rows;
    int start_index = -1;
    int goal_index = -1;
};
