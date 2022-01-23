
#version 330 core

layout(location = 0) out vec4 color;
in vec2 v_tex_coord;

uniform vec4 u_color;

void main()
{
    color = u_color;   
};