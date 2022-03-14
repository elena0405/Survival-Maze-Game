#version 330

// Input
// TODO(student): Get values from vertex shader
in vec3 world_position;
in vec3 world_normal;

// Uniform properties
uniform vec3 light_position;
uniform vec3 eye_position;
uniform float material_kd;
uniform float material_ks;
uniform float material_ke;
uniform int material_shininess;
uniform vec3 object_color;

// Output
layout(location = 0) out vec4 out_color;

void main()
{
    // Write pixel out color
    vec3 ke = object_color;
    vec3 color = ke;
   out_color = vec4(color, 1);
}
