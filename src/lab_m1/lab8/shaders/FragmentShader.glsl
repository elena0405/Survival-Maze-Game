#version 330

// Input
in vec3 world_position;
in vec3 world_normal;

// Uniforms for light properties
uniform vec3 light_direction;
uniform vec3 light_position;
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

// TODO(student): Declare any other uniforms
uniform vec3 object_color;
uniform int isSpotligth;
uniform float cut_off_angle;

// Output
layout(location = 0) out vec4 out_color;


void main()
{
    vec3 world_position_new = world_position;
    vec3 world_normal_new   = normalize(world_normal);
    
    // TODO(student): Define ambient, diffuse and specular light components
    float ambient_light = 0.25;
    float diffuse_light = 0;
    float specular_light = 0;

    vec3 L = normalize(light_position - world_position_new);
    vec3 V = normalize(eye_position - world_position_new);
    vec3 R = normalize(reflect(L, world_position_new));
    vec3 H = normalize( L + V );

    diffuse_light = material_kd * max(dot(world_normal_new, L), 0);

    // It's important to distinguish between "reflection model" and
    // "shading method". In this shader, we are experimenting with the Phong
    // (1975) and Blinn-Phong (1977) reflection models, and we are using the
    // Phong (1975) shading method. Don't mix them up!
    if (diffuse_light > 0)
    {
        specular_light = material_ks * pow(max(dot(V, R), 0), material_shininess);
    }

    // TODO(student): If (and only if) the light is a spotlight, we need to do
    // some additional things.

    float attenuation_factor = 0;
    float ligth = 0;

    // Fii atenta, Anca! Sa stii ca imi merge taskul 3, doar ca este destul de mica sursa de 
    // lumina. Daca misti putin cu w sursa de lumina, o sa o observi. 

    if (isSpotligth == 1) {
        float spot_light = dot(-L, light_direction);
        float spot_light_limit = cos(radians(cut_off_angle));

        if (spot_light > spot_light_limit) {
            float linear_att = (spot_light - spot_light_limit) / (1.0f - spot_light_limit);
            float light_att_factor = linear_att * linear_att;

            attenuation_factor = light_att_factor;

            ligth = ambient_light + attenuation_factor * (diffuse_light + specular_light);
        } else {
            ligth = ambient_light;
        }
    } else {
        float d = distance(light_position, world_position_new);
        attenuation_factor = 1.0f / max(d * d, 1.0f);
        ligth = ambient_light + attenuation_factor * (diffuse_light + specular_light);
    }

    // TODO(student): Compute the total light. You can just add the components
    // together, but if you're feeling extra fancy, you can add individual
    // colors to the light components. To do that, pick some vec3 colors that
    // you like, and multiply them with the respective light components.

    // TODO(student): Write pixel out color
    vec3 color = object_color * ligth;
    out_color = vec4(color, 1);

}
