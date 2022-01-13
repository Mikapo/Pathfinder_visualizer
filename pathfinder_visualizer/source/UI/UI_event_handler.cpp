#include "UI_event_handler.h"

#include "Pathfinding_window.h"
#include <iostream>

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

void UI_event_handler::on_combo_box_event(std::string input, UI_combo_box_event type)
{
    switch (type)
    {
        case UI_combo_box_event::algorimth: 
        {
            if (input == "Breadth first search")
                owner->get_grid()->switch_path_finding_algorimth(Pathfinding_algorimths::Breadth_first_search);
            else if (input == "Dijkstras")
                owner->get_grid()->switch_path_finding_algorimth(Pathfinding_algorimths::Dijkstras_algorithm);
        }
    }
}
