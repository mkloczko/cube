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
    GLuint nb  = 0;
    GLuint tb  = 0;

    GLuint texture = 0;

    bool initialize();
};

struct CubeProgram{


    bool initialize();
    GLuint getProgram();
    void draw(const Cube &, const Image & img);
    void updateMatrix(const Eigen::Matrix4f &matrix);
    void updateNormalMatrix(const Eigen::Matrix3f &matrix);

private:
    GLuint program = 0;
    GLuint pbo = 0;
};

#endif

