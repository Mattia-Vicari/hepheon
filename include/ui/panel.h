#ifndef __UI_PANEL_H__
#define __UI_PANEL_H__

#include <map>
#include <glm/glm.hpp>

#include "opengl.h"
namespace ui {

enum class Anchor {
    TOP_LEFT,
    TOP,
    TOP_RIGHT,
    LEFT,
    CENTER,
    RIGHT,
    BOTTOM_LEFT,
    BOTTOM,
    BOTTOM_RIGHT
};

static std::map<Anchor, glm::vec2> anchor_map = {
    {Anchor::TOP_LEFT, glm::vec2(-1, 1)},
    {Anchor::TOP, glm::vec2(0, 1)},
    {Anchor::TOP_RIGHT, glm::vec2(1, 1)},
    {Anchor::LEFT, glm::vec2(-1, 0)},
    {Anchor::CENTER, glm::vec2(0, 0)},
    {Anchor::RIGHT, glm::vec2(1, 0)},
    {Anchor::BOTTOM_LEFT, glm::vec2(-1, -1)},
    {Anchor::BOTTOM, glm::vec2(0, -1)},
    {Anchor::BOTTOM_RIGHT, glm::vec2(1, -1)}
};

class Panel {
 public:
    GLuint VBO;
    GLuint VAO;

    glm::vec3 color;

    glm::vec3 rel_pos;  // Needed for shaders
    glm::vec2 rel_size;  // Needed for shaders
    glm::ivec2 abs_pos;  // Needed for shaders 
    glm::ivec2 abs_size;  // Needed for shaders

    int radius;
    glm::vec2 anchor_pos;

    glm::vec2 window_size;  // This is actually the framebuffer size
    glm::ivec2 screen_pos;  // Needed for hit detection
        
    float scale_x = 0.5;  // should be computed as window_width / framebuffer_width 
    float scale_y = 0.5;  // should be computed as window_height / framebuffer_height

    /**
     * @brief Construct a new Panel object with relative position and absolute size
     */
    Panel(
        glm::vec3 pos,
        glm::vec3 color,
        glm::ivec2 size,
        int radius,
        Anchor anchor,
        glm::vec2 window_size
    ) : color(color), rel_pos(pos), abs_size(size), radius(radius), window_size(window_size) {
        anchor_pos = anchor_map[anchor];
        compute_rel_size();
        compute_abs_pos();
        setup_buffers();
        compute_screen_pos();
    }

    void setup_buffers() {
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

    void compute_abs_pos() {
        abs_pos = glm::ivec2(
            (rel_pos.x + 1) * window_size.x / 2,
            (rel_pos.y + 1) * window_size.y / 2
        );
    }

    void compute_abs_size() {
        abs_size = glm::ivec2(rel_size.x * window_size.x, rel_size.y * window_size.y);
    }

    void compute_rel_size() {
        rel_size = glm::vec2((float) abs_size.x / window_size.x, (float) abs_size.y / window_size.y);
    }

    void compute_screen_pos() {
        screen_pos = glm::ivec2(
            (abs_pos.x - anchor_pos.x * abs_size.x) * scale_x,
            window_size.y * scale_y - (abs_pos.y - anchor_pos.y * abs_size.y) * scale_y
        );
    }

    void compute_vertex_buffer() {
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

    void compute_uniform_buffer() {
        // center of the panel in absolute coordinates
        uniform_buffer[0] = abs_pos.x - anchor_pos.x * abs_size.x / 2;
        uniform_buffer[1] = abs_pos.y - anchor_pos.y * abs_size.y / 2;

        // size of the panel in absolute coordinates
        uniform_buffer[2] = abs_size.x;
        uniform_buffer[3] = abs_size.y;

        // radius of the panel
        uniform_buffer[4] = radius;
    }
    
    void draw(const GLuint ui_program) {
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
    };
 private:
    float vertex_buffer[24];
    int uniform_buffer[5];
};

}  // namespace ui

#endif  // __UI_PANEL_H__
