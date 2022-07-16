#include "LoadFiles.hpp"

#include <vector>
#include <string>
#include <iostream>

#include "IncludeGL.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

using std::vector;
using std::string;

Image::Image(const string & path){
    int channels;
    data = stbi_load(path.c_str(), &width, &height, &channels, 3);

    if(data == nullptr){
    	std::cerr << "Failed to load file: " << path << std::endl;
    } else if(channels != 3){
        std::cerr << "Loaded " << channels << " instead of 3." << std::endl;
    } 
}

vector<Image> Image::loadImages(const string & dir, const string & name){
    //For now, have a hard coded version. Later on perhaps do something with parsing.
    vector<Image> ret(60);

    for(int i = 1; i <  10; i++){
        string number = "000" + std::to_string(i);
        string path   = dir + dir_sep + name + '-' + number + ".png";
        ret[i-1] = Image(path);
    }

    for(int i = 10; i <= 60; i++){
        string number = "00" + std::to_string(i);
        string path   = dir + dir_sep + name + '-' + number + ".png";
        ret[i-1] = Image(path);
    }

    return ret;
}

GLuint Image::toTexture() const{
    if(data == nullptr){
        return 0;
    }

    GLuint texID;
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D,0);
    return texID;
}

