#pragma once

#ifdef _WIN32
    #include <GL/glew.h>
#else
    #include <GL/gl.h>
    #include <GL/glext.h>
#endif


#include<GLFW/glfw3.h>

void getErr (const char * msg);
