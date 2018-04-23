#ifndef POSTPROCESS_GUARD
#define POSTPROCESS_GUARD

#include <functional>

#include "IncludeGL.hpp"


struct Postprocess{
    GLuint framebuffer  = 0;
    GLuint renderbuffer = 0;
    GLuint tex_color_buffer = 0;

    bool initialize();
    void resize(int x, int y);
    void render(const std::function<void()>&);
    void draw();

private:
    GLuint program    = 0;
    GLuint canvas_vao = 0;
    GLuint canvas_vb  = 0;

    GLfloat pixel_x = 0;
    GLfloat pixel_y = 0;
};


#endif