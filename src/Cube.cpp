
#include "Cube.hpp"

constexpr GLfloat cube_vertices[6*2*3*3] = {

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

constexpr GLfloat cube_normals[6*2*3*3] = {

        //X-
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,

        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,

        //X+
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        //Y-
        0.0f,-1.0f, 0.0f,
        0.0f,-1.0f, 0.0f,
        0.0f,-1.0f, 0.0f,

        0.0f,-1.0f, 0.0f,
        0.0f,-1.0f, 0.0f,
        0.0f,-1.0f, 0.0f,

        //Y+
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,

        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,

        //Z-
        0.0f, 0.0f,-1.0f,
        0.0f, 0.0f,-1.0f,
        0.0f, 0.0f,-1.0f,

        0.0f, 0.0f,-1.0f,
        0.0f, 0.0f,-1.0f,
        0.0f, 0.0f,-1.0f,

        //Z+
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f
};

constexpr GLfloat crop_value = ((1920.0-1080.0)/1920.0)/2.0;

constexpr GLfloat cube_texCoords[6*2*3*2] = {

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

        //The cropping is implemented here

        //Z+
        0.0f + crop_value, 1.0f,
        0.0f + crop_value, 0.0f,
        1.0f - crop_value, 1.0f,


        1.0f - crop_value, 1.0f,
        0.0f + crop_value, 0.0f,
        1.0f - crop_value, 0.0f
};


bool Cube::initialize(const vector<Image> & imgs){
    if (vao != 0){
        return false;
    }
    glGenVertexArrays(1, &vao);
    getErr("Cube::initializeCube gen vao");
    glGenBuffers(1, &vb);
    getErr("Cube::initializeCube gen vb");
    glGenBuffers(1, &nb);
    getErr("Cube::initializeCube gen nb");
    glGenBuffers(1, &tb);
    getErr("Cube::initializeCube gen tb");

    GLuint location;

    glBindVertexArray(vao);
    getErr("Cube::initializeCube vao");

    glBindBuffer(GL_ARRAY_BUFFER, vb);
    glBufferData(GL_ARRAY_BUFFER, 6*2*3*3*sizeof(GLfloat), cube_vertices, GL_STATIC_DRAW);
    getErr("Cube::initializeCube vb");

    glBindBuffer(GL_ARRAY_BUFFER, nb);
    glBufferData(GL_ARRAY_BUFFER, 6*2*3*3*sizeof(GLfloat), cube_normals, GL_STATIC_DRAW);
    getErr("Cube::initializeCube vb");

    glBindBuffer(GL_ARRAY_BUFFER, tb);
    glBufferData(GL_ARRAY_BUFFER, 6*2*3*2*sizeof(GLfloat), cube_texCoords, GL_STATIC_DRAW);
    getErr("Cube::initializeCube tb");

    glBindBuffer(GL_ARRAY_BUFFER,0);
    getErr("Cube::initializeCube unbind tb");
    glBindVertexArray(0);
    getErr("Cube::initializeCube unbind vao");

    //Load textures.
    textures = vector<GLuint>(imgs.size(),0);
    for(unsigned int i = 0; i < imgs.size(); i++) {
        textures[i] = imgs[i].toTexture();
        getErr("Cube::initializeCube create texture");
    }

}


constexpr char vertex_shader[] = "#version 300 es\n"
        "in  highp vec3 in_position;\n"
        "in  highp vec3 in_normal;\n"
        "in  highp vec2 in_texCoord;\n"
        "out highp vec3 position;\n"
        "out highp vec3 normal;\n"
        "out highp vec3 raw_normal;\n"
        "out highp vec2 texCoord;\n"
        "uniform highp mat4 matrix;\n"
        "uniform highp mat3 normal_matrix;\n"
        "\n"
        "void main(void){\n"
        "   texCoord = in_texCoord;\n"
        "   normal   = normalize(normal_matrix * in_normal);\n"
        "   raw_normal = in_normal;\n"
        "   position = in_position;\n"
        "   gl_Position  = matrix * vec4(in_position,1);\n"
        "}\n";

constexpr char fragment_shader[] = "#version 300 es\n"
        "in  highp vec3 position;\n"
        "in  highp vec3 normal;\n"
        "in  highp vec3 raw_normal;\n"
        "in  highp vec2 texCoord;\n"
        "out highp vec4 outColor;\n"
        "uniform highp sampler2D tex;\n"
        "\n"
        "\n"
        "vec3 calcReflection(highp vec3 v, highp vec3 along){\n"
        "    v     = normalize(v);\n"
        "    along = normalize(along);\n"
        "    return (2.0*dot(v,along)*along) - v;\n"
        "}"
        "\n"
        "vec3 calcPositional(highp vec3 n, highp vec3 p, highp vec3 ambient_part){\n"
        "    highp vec3 light_v = normalize(vec3(2.0,1.0,3.0) - p);\n"
        "    highp vec3 view_v  = normalize(vec3(0.0,0.0,3.0) - p);\n"
        "    highp vec3 refl_v  = calcReflection(light_v, n);\n"
        "\n"
        "    highp vec3 diff_part = 0.50 * ambient_part * max(dot(normal, light_v),0.0);\n"
        "    highp vec3 spec_part = 0.10 * vec3(0.8,0.8 ,0.8) * max(dot(refl_v, view_v),0.0);\n"
        "    return (0.4 * ambient_part) + diff_part + spec_part;"
        "}\n"
        "\n"
        "void main(void){\n"
        "    highp vec3 side_color = vec3(0.0);\n;"
        "    if((texCoord.x < 0.0) || (texCoord.y < 0.0)){\n"
        "        side_color = (raw_normal + vec3(1.0,1.0,1.0))/2.0;\n"
        "    } else {\n"
        "        side_color = texture(tex, texCoord).xyz;\n"
        "    }\n"
        "    outColor = vec4(calcPositional(normal, position, side_color),1.0);\n"
        "}\n";

bool CubeProgram::initialize(){
    if(program == 0){
        program = setShaders(vertex_shader,fragment_shader);

        //Set texture positions
        GLuint texture_id;
        texture_id = glGetUniformLocation(program, "tex");
        glUniform1i(texture_id, 0);
        glUseProgram(0);
        return program != 0;
    }
    return true;
}

GLuint CubeProgram::getProgram(){
    return program;
}
void CubeProgram::draw(const Cube & cube, unsigned int i){
    GLuint location;
    glUseProgram(program);
    getErr("CubeProgram::draw() - enable program");
    glBindVertexArray(cube.vao);

    getErr("CubeProgram::draw() - bind vao");

    glBindBuffer(GL_ARRAY_BUFFER, cube.vb);
    location = glGetAttribLocation(program, "in_position");
    glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(location);
    getErr("CubeProgram::draw() - get vb");

    glBindBuffer(GL_ARRAY_BUFFER, cube.nb);
    location = glGetAttribLocation(program, "in_normal");
    glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(location);
    getErr("CubeProgram::draw() - get nb");

    glBindBuffer(GL_ARRAY_BUFFER, cube.tb);
    location = glGetAttribLocation(program, "in_texCoord");
    glVertexAttribPointer(location, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(location);
    getErr("CubeProgram::draw() - get tb");

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, cube.textures[i]);
    getErr("CubeProgram::draw() - set texture");

    glDrawArrays(GL_TRIANGLES, 0, 6*2*3);
    getErr("CubeProgram::draw() - draw call");


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    getErr("CubeProgram::draw() - unbind buffer");
    glBindVertexArray(0);
    getErr("CubeProgram::draw() - unbind vao");

    glUseProgram(0);
    getErr("CubeProgram::draw() - disable program");
}

void CubeProgram::updateMatrix(const Eigen::Matrix4f &matrix){
    glUseProgram(program);
    GLuint proj_id = glGetUniformLocation(program, "matrix");
    glUniformMatrix4fv(proj_id, 1, GL_FALSE, matrix.data());
    glUseProgram(0);
}

void CubeProgram::updateNormalMatrix(const Eigen::Matrix3f &matrix){
    glUseProgram(program);
    GLuint proj_id = glGetUniformLocation(program, "normal_matrix");
    glUniformMatrix3fv(proj_id, 1, GL_FALSE, matrix.data());
    glUseProgram(0);
}