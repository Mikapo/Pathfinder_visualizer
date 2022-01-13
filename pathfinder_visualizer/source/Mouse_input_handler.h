#pragma once
class Mouse_input_handler
{
public:
    void update(class Pathfinding_window* owner);

private:
    bool is_pressed = false;
};
