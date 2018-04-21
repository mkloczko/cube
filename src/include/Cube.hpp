#ifndef CUBE_GUARD
#define CUBE_GUARD

#include <vector>
#include <Eigen/Core>

#include "IncludeGL.hpp"
#include "LoadFiles.hpp"

using std::vector;

struct Cube{
    GLuint vao = 0;
    GLuint vb  = 0;
    GLuint tb  = 0;

    vector<GLuint> textures = vector<GLuint>();

    bool initialize(const vector<Image> &);
};

struct CubeProgram{


    bool initialize();
    GLuint getProgram();
    void draw(const Cube &);
    void updateMatrix(const Eigen::Matrix4f &matrix);

private:
    GLuint program = 0;
};

#endif

