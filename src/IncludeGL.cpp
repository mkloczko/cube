#include "IncludeGL.hpp"
#include <iostream>



void getErr (const char * msg){
    using std::cerr;
    using std::endl;

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