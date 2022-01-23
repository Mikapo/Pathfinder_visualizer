#include "Window.h"

#include "UI/UI.h"
#include "UI/UI_event_handler.h"
#include "Mouse_input_handler.h"
#include "Pathfinding_grid/Pathfinding_grid.h"


class Pathfinding_window : public Window
{
public:
    Pathfinding_window();

    bool is_ui_hovered_by_mouse() const { return ui.is_hovered_by_mouse(); }
    Pathfinding_grid* get_grid() { return &grid; };

protected:
    void init() override;
    void update() override;
    void cleanup() override;

private:
    UI ui;
    UI_event_handler ui_event_handler;
    Mouse_input_handler mouse_input_handler;
    Pathfinding_grid grid;
   
};