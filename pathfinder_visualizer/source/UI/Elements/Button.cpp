#include "Button.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

void Button::update()
{
    if (ImGui::Button(name.c_str()))
    {
        for (auto observer : observers)
            observer->on_button_event(button_event_on_clicked);
    }
}
