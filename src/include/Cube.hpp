#ifndef CUBE_INCL
#define CUBE_INCL

#include "IncludeGL.hpp"

struct Cube{

    GLuint vao = 0;
    GLuint vb  = 0;
    GLuint tb  = 0;

    vector<GLuint> textures = vector<GLuint>();

    bool initializeCube(const vector<Image> & imgs);
    void draw

    static GLuint getProgram();

private:
    constexpr static GLfloat cube_vertices[];
    constexpr static GLfloat cube_texCoords[];
    constexpr static char vertex_shader[];
    constexpr static char fragment_shader[];

    static GLuint program = 0;
};


#endif

