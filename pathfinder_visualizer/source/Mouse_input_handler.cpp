#include "Mouse_input_handler.h"

#include "Pathfinding_window.h"

#include "glew.h"

#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"

#include <iostream>


void Mouse_input_handler::update(Pathfinding_window* owner) 
{
    if (owner->is_ui_hovered_by_mouse())
        return;

    int result = glfwGetMouseButton(owner->get_window(), GLFW_MOUSE_BUTTON_LEFT);

    double X;
    double Y;
    glfwGetCursorPos(owner->get_window(), &X, &Y);

    if (result == GLFW_PRESS)
    {
        std::cout << "mouse press X: " << X << " Y: " << Y << "\n";
        owner->get_grid()->draw_to_grid(X, Y);
        is_pressed = true;
    }
    else if (result == GLFW_RELEASE && is_pressed)
    {
        std::cout << "mouse release X: " << X << " Y: " << Y << "\n";
        is_pressed = false;
    }
}
