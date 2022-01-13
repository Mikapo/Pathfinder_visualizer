#pragma once

#include "UI/UI_observer.h"
#include <unordered_set>

class UI_element
{
public:
    virtual void update() = 0;
    void add_observer(UI_observer* observer) { observers.insert(observer); }
    void remove_observer(UI_observer* observer) { observers.erase(observer); }

protected:
    std::unordered_set<UI_observer*> observers;
};
