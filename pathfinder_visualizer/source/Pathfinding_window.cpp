#include "Pathfinding_window.h"
#include <iostream>

    Pathfinding_window::Pathfinding_window() : ui_event_handler(this) {}

    void Pathfinding_window::init()
    {
        super::init();
        ui.init(get_window());
        ui.add_observer(&ui_event_handler);
        grid.init();
    }

    void Pathfinding_window::update()
    {
        grid.render(get_window_dimensions());
        ui.update();
        mouse_input_handler.update(this);
    }

    void Pathfinding_window::cleanup()
    {
        super::cleanup();
        ui.cleanup();
        grid.cleanup();
    }
