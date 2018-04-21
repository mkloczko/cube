
#include "Cube.hpp"

constexpr GLfloat Cube::cube_vertices[] = {

        //X-
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,


        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f,

        //X+
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f,

        1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 0.0f,

        //Y-
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f,

        1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,

        //Y+
        0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f,

        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f,
        //Z-
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,

        //Z+
        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f,

        1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f
};

constexpr GLfloat Cube::cube_texCoords[] = {

        //X-
        -1.0f, -1.0f,
        -1.0f, -1.0f,
        -1.0f, -1.0f,


        -1.0f, -1.0f,
        -1.0f, -1.0f,
        -1.0f, -1.0f,

        //X+
        -1.0f, -1.0f,
        -1.0f, -1.0f,
        -1.0f, -1.0f,


        -1.0f, -1.0f,
        -1.0f, -1.0f,
        -1.0f, -1.0f,

        //Y-
        -1.0f, -1.0f,
        -1.0f, -1.0f,
        -1.0f, -1.0f,


        -1.0f, -1.0f,
        -1.0f, -1.0f,
        -1.0f, -1.0f,

        //Y+
        -1.0f, -1.0f,
        -1.0f, -1.0f,
        -1.0f, -1.0f,


        -1.0f, -1.0f,
        -1.0f, -1.0f,
        -1.0f, -1.0f,

        //Z-
        -1.0f, -1.0f,
        -1.0f, -1.0f,
        -1.0f, -1.0f,


        -1.0f, -1.0f,
        -1.0f, -1.0f,
        -1.0f, -1.0f,

        //Z+
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,


        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f
};

bool Cube::initializeCube(const vector<Image> & imgs){
    if (vao != 0){
        return false;
    }
    glGenVertexArrays(1, &vao);
    getErr("Cube::initializeCube gen vao");
    glGenBuffers(1, &vb);
    getErr("Cube::initializeCube gen vb");
    glGenBuffers(1, &tb);
    getErr("Cube::initializeCube gen tb");

    GLuint location;

    glBindVertexArray(cube_vao);
    getErr("Cube::initializeCube vao");

    glBindBuffer(GL_ARRAY_BUFFER, vb);
    glBufferData(GL_ARRAY_BUFFER, 6*2*3*3*sizeof(GLfloat), cube_vertices, GL_STATIC_DRAW);
    getErr("Cube::initializeCube vb");

    glBindBuffer(GL_ARRAY_BUFFER, tb);
    glBufferData(GL_ARRAY_BUFFER, 6*2*3*2*sizeof(GLfloat), cube_texCoords, GL_STATIC_DRAW);
    getErr("Cube::initializeCube tb");

    glBindBuffer(GL_ARRAY_BUFFER,0);
    getErr("Cube::initializeCube unbind tb");
    glBindVertexArray(0);
    getErr("Cube::initializeCube unbind vao");
}