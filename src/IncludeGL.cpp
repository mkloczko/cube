#include "IncludeGL.hpp"
#include <iostream>

using std::cerr;
using std::endl;

void getErr (const char * msg){

    GLuint err = glGetError();
    if(err != 0){
        cerr << "Error!: " << msg << " ";
        if (err == GL_INVALID_OPERATION) {
            cerr << "Invalid operation" << endl;
        } else if( err == GL_INVALID_VALUE){
            cerr << "Invalid value" << endl;
        } else {
            cerr << err << endl;
        }
    }
}

void printShaderInfoLog(GLuint obj, const char *fn)
{
    GLint infologLength = 0;
    GLint charsWritten  = 0;
    char *infoLog;

    glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

    if (infologLength > 2)
    {
        infoLog = new char[infologLength];
        glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
        cerr << "From " << fn << ":";
        cerr <<  infoLog << endl;
        delete infoLog;
    }
}

void printProgramInfoLog(GLuint obj, const char *vfn, const char *ffn)
{
    GLint infologLength = 0;
    GLint charsWritten  = 0;
    char *infoLog;

    glGetProgramiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

    if (infologLength > 2)
    {

        infoLog = new char[infologLength];
        glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
        cerr << "From " << vfn << " and " << ffn << ":";
        cerr <<  infoLog << endl;
        delete infoLog;
    }
}

GLuint setShaders(const char * vs, const char * fs){
    GLuint v,f,p;

    v = glCreateShader(GL_VERTEX_SHADER);
    f = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(v, 1, &vs, NULL);
    glShaderSource(f, 1, &fs, NULL);
    glCompileShader(v);
    glCompileShader(f);

    GLenum err = GL_NO_ERROR;
    while((err = glGetError()) != GL_NO_ERROR)
    {
        cerr << "Error:" << err << endl;
        //Process/log the error.
    }

    p = glCreateProgram();
    glAttachShader(p,v);
    glAttachShader(p,f);


    glLinkProgram(p);
    glUseProgram(p);

    printShaderInfoLog(v, "Vertex shader");
    printShaderInfoLog(f, "Fragment shader");
    printProgramInfoLog(p,"Vertex","Fragment");
    return p;
}