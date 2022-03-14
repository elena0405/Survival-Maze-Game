#version 330

// Input
// TODO(student): Get values from vertex shader
in vec3 f_position;
in vec3 f_normal;
in vec3 f_texture;
in vec3 f_color;

// Uniform properties
uniform float time;
uniform bool hit;

// Output
layout(location = 0) out vec4 out_color;

void main()
{
    // TODO(student): Write pixel out color
    out_color = vec4(abs(f_normal * cos(time)), 1);
}
