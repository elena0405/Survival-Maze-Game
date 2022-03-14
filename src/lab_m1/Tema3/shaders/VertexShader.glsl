#version 330

// Input
// TODO(student): Get vertex attributes from each location
layout(location = 0) in vec3 v_position;
layout(location = 3) in vec3 v_normal;
layout(location = 2) in vec3 v_texture_coord;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

// Output
// TODO(student): Output values to fragment shader
out vec3 world_position;
out vec3 world_normal;


void main()
{
    vec3 world_pos = (Model * vec4(v_position,1)).xyz;
    vec3 world_normal = normalize(mat3(Model) * v_normal);
    
    gl_Position = Projection * View * Model * vec4(world_pos, 1.0);
}
