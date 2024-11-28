#include "ui/panel.h"


ui::Panel::Panel(
    glm::vec3 pos,
    glm::vec3 color,
    glm::ivec2 size,
    int radius,
    Anchor anchor,
    glm::vec2 framebuffer_size,
    glm::vec2 window_size
) : color(color),
    rel_pos(pos),
    abs_size(size),
    radius(radius),
    framebuffer_size(framebuffer_size) {

    anchor_pos = anchor_map[anchor];
    scale_x = window_size.x / framebuffer_size.x;
    scale_y = window_size.y / framebuffer_size.y;

    compute_rel_size();
    compute_abs_pos();
    setup_buffers();
    compute_screen_pos();
}


void ui::Panel::setup_buffers() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // Bind and set up VBO and VAO
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer), vertex_buffer, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


void ui::Panel::compute_rel_size() {
    rel_size = glm::vec2(
        (float) abs_size.x / framebuffer_size.x, 
        (float) abs_size.y / framebuffer_size.y
    );
}


void ui::Panel::compute_abs_size() {
    abs_size = glm::ivec2(rel_size.x * framebuffer_size.x, rel_size.y * framebuffer_size.y);
}


void ui::Panel::compute_abs_pos() {
    abs_pos = glm::ivec2(
        (rel_pos.x + 1) * framebuffer_size.x / 2,
        (rel_pos.y + 1) * framebuffer_size.y / 2
    );
}


void ui::Panel::compute_screen_pos() {
    screen_pos = glm::ivec2(
        (abs_pos.x - anchor_pos.x * abs_size.x) * scale_x,
        (framebuffer_size.y - (abs_pos.y - anchor_pos.y * abs_size.y)) * scale_y
    );
}


void ui::Panel::compute_vertex_buffer() {
    // top right
    vertex_buffer[0] = rel_pos.x + rel_size.x - anchor_pos.x * rel_size.x;
    vertex_buffer[1] = rel_pos.y + rel_size.y - anchor_pos.y * rel_size.y;
    vertex_buffer[2] = rel_pos.z;
    vertex_buffer[3] = color.r;
    vertex_buffer[4] = color.g;
    vertex_buffer[5] = color.b;

    // top left
    vertex_buffer[6] = rel_pos.x - rel_size.x - anchor_pos.x * rel_size.x;
    vertex_buffer[7] = rel_pos.y + rel_size.y - anchor_pos.y * rel_size.y;
    vertex_buffer[8] = rel_pos.z;
    vertex_buffer[9] = color.r;
    vertex_buffer[10] = color.g;
    vertex_buffer[11] = color.b;

    // bottom left
    vertex_buffer[12] = rel_pos.x - rel_size.x - anchor_pos.x * rel_size.x;
    vertex_buffer[13] = rel_pos.y - rel_size.y - anchor_pos.y * rel_size.y;
    vertex_buffer[14] = rel_pos.z;
    vertex_buffer[15] = color.r;
    vertex_buffer[16] = color.g;
    vertex_buffer[17] = color.b;

    // bottom right
    vertex_buffer[18] = rel_pos.x + rel_size.x - anchor_pos.x * rel_size.x;
    vertex_buffer[19] = rel_pos.y - rel_size.y - anchor_pos.y * rel_size.y;
    vertex_buffer[20] = rel_pos.z;
    vertex_buffer[21] = color.r;
    vertex_buffer[22] = color.g;
    vertex_buffer[23] = color.b;
}


void ui::Panel::compute_uniform_buffer() {
    // center of the panel in absolute coordinates
    uniform_buffer[0] = abs_pos.x - anchor_pos.x * abs_size.x / 2;
    uniform_buffer[1] = abs_pos.y - anchor_pos.y * abs_size.y / 2;

    // size of the panel in absolute coordinates
    uniform_buffer[2] = abs_size.x;
    uniform_buffer[3] = abs_size.y;

    // radius of the panel
    uniform_buffer[4] = radius;
}


void ui::Panel::draw(const GLuint ui_program) {
    // Use the shader program and bind VAO
    glUseProgram(ui_program);

    compute_vertex_buffer();
    compute_uniform_buffer();

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertex_buffer), vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glBindVertexArray(VAO);
    glUniform1iv(glGetUniformLocation(ui_program, "dims"), 5, uniform_buffer);

    // Draw the triangle
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    // Unbind and swap buffers
    glBindVertexArray(0);
}


void ui::Panel::resize(glm::ivec2 window_size, glm::ivec2 framebuffer_size) {
    this->framebuffer_size = framebuffer_size;
    scale_x = (float) window_size.x / framebuffer_size.x;
    scale_y = (float) window_size.y / framebuffer_size.y;

    // keep abs_size and rel_pos fixed
    compute_rel_size();
    compute_abs_pos();
    compute_screen_pos();
}
