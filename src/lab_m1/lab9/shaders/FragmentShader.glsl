#version 330

// Input
in vec2 texcoord;

// Uniform properties
uniform sampler2D texture_1;
uniform sampler2D texture_2;

// TODO(student): Declare various other uniforms
uniform int mixed;
uniform int trans1;
uniform int trans2;
uniform float time;

// Output
layout(location = 0) out vec4 out_color;


void main()
{
    // TODO(student): Calculate the out_color using the texture2D() function.
    vec2 new_coord = texcoord;
    if (trans1 == 1) {
        new_coord.x += time;
    }

    if (trans2 == 1) {
        new_coord.y += 30.0f;
    }
  
    vec4 color1 = texture2D(texture_1, new_coord);   
    vec4 color2 = texture2D(texture_2, new_coord); 
    vec4 color;
    
    if (mixed == 1) {
        color = mix(color1, color2, 0.5f); 
        if (color.a <= 0.5f) {
        discard;
    }
    } else {
        color = color1;
        if (color.a <= 0.5f) {
        discard;
    }
    }

	out_color = color;

}
