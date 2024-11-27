#version 330 core

in vec3 color;

out vec4 frag_color;

uniform int dims[5];

void main()
{
    float alpha = 0.0;

    vec2 frag_coord = vec2(gl_FragCoord);
    ivec2 center = ivec2(dims[0], dims[1]);
    int width = dims[2];
    int height = dims[3];
    int radius = dims[4];

    vec2 dist_vec = abs(frag_coord - center);
    float dist = length(dist_vec - vec2(width, height) / 2 + radius);


    bool in_rect1 = dist_vec.x < width / 2 && dist_vec.y < height / 2 - radius;
    bool in_rect2 = dist_vec.x < width / 2 - radius && dist_vec.y < height / 2;

    if (dist < radius || in_rect1 || in_rect2) {
        alpha = 1.0;
    }

    frag_color = vec4(color, alpha);
}

