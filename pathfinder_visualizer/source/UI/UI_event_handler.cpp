#include "UI_event_handler.h"

#include <iostream>
#include "Pathfinding_window.h"

UI_event_handler::UI_event_handler(Pathfinding_window* owner) { this->owner = owner; }

void UI_event_handler::on_button_event(UI_button_event type)
{
    switch (type)
    {
        case UI_button_event::start_button_pressed:
            owner->get_grid()->start_pathfinding();
        break;

        case UI_button_event::stop_button_pressed:
            owner->get_grid()->stop_pathfinding();
        break;
    }
}
