#ifndef INCLUDEGL_GUARD
#define INCLUDEGL_GUARD
#ifdef _WIN32

    #include <GL/glew.h>
#else
#include <GL/gl.h>
#include <GL/glext.h>
#endif
#include<GLFW/glfw3.h>


void getErr (const char * msg);
bool printShaderInfoLog(GLuint obj, const char *fn);
bool printProgramInfoLog(GLuint obj, const char *vfn, const char *ffn);
GLuint setShaders(const char * vs, const char * fs);

#endif
