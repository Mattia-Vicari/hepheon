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
     * 
     * @param[in] pos The relative position of the panel.
     * @param[in] color The color of the panel.
     * @param[in] size The size of the panel in pixels.
     * @param[in] radius The radius of the panel corners.
     * @param[in] anchor The anchor point of the panel.
     * @param[in] window_size The size of the window.
     */
    Panel(
        glm::vec3 pos,
        glm::vec3 color,
        glm::ivec2 size,
        int radius,
        Anchor anchor,
        glm::vec2 window_size
    );

    /**
     * @brief Set up the buffers for the panel.
     */
    void setup_buffers();

    /**
     * @brief Compute the relative size of the panel.
     */
    void compute_rel_size();

    /**
     * @brief Compute the absolute size of the panel.
     */ 
    void compute_abs_size();

    /**
     * @brief Compute the absolute position of the panel.
     */
    void compute_abs_pos();

    /**
     * @brief Compute the screen position of the panel.
     */
    void compute_screen_pos();

    /**
     * @brief Compute the vertex buffer for the panel.
     */
    void compute_vertex_buffer();

    /**
     * @brief Compute the uniform buffer for the panel.
     */
    void compute_uniform_buffer();

    /**
     * @brief Draw the panel.
     * 
     * @param[in] ui_program The program to use for drawing the panel.
     */
    void draw(const GLuint ui_program);

 private:
    float vertex_buffer[24];
    int uniform_buffer[5];
};

}  // namespace ui

#endif  // __UI_PANEL_H__
