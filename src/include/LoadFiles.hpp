#pragma once

#include <vector>
#include <string>

#include "IncludeGL.hpp"

using std::vector;
using std::string;

struct Image{
    unsigned char * data = nullptr;
    int   width = 0;
    int   height= 0;

    Image(){};

    Image(const string & path);

    static constexpr char dir_sep = '/';

    static vector<Image> loadImages(const string & dir, const string & name);
};

