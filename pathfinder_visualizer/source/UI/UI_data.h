#pragma once
#include <string>

enum class UI_button_event
{
	none = 0,
	start_button_pressed,
	stop_button_pressed,
};

struct UI_status
{
    std::string paint_mode;
    std::string algorithm;
};