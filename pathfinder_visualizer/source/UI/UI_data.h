#pragma once
#include <string>

enum class UI_button_event
{
	none = 0,
	start_button_pressed,
	stop_button_pressed,
};

enum class UI_combo_box_event
{
	none = 0,
	algorimth
};

struct UI_status
{
    std::string paint_mode;
    std::string algorithm;
};