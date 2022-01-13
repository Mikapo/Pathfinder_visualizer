#pragma once
#include "UI_data.h"
class UI_observer
{
public:
    virtual void on_button_event(UI_button_event type) = 0;
};
