#pragma once

#include "UI_observer.h"

class Pathfinding_window;
class UI_event_handler : public UI_observer
{
public:
    UI_event_handler(Pathfinding_window* owner);

    virtual void on_button_event(UI_button_event type) override;

private:
    Pathfinding_window* owner = nullptr;

};
