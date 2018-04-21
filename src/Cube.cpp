
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

        //Z+
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,


        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f
};


bool Cube::initialize(const vector<Image> & imgs){
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

    glBindVertexArray(vao);
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


constexpr char vertex_shader[] = "#version 300 es\n"
        "in  highp vec3 in_position;\n"
        "in  highp vec2 in_texCoord;\n"
        "out highp vec2 out_texCoord;\n"
        "uniform highp mat4 matrix;\n"
        "\n"
        "void main(void){\n"
        "   out_texCoord = in_texCoord;\n"
        "   gl_Position  = matrix * vec4(in_position,1);\n"
        "}\n";

constexpr char fragment_shader[] = "#version 300 es\n"
        "in  highp vec2 out_texCoord;\n"
        "out highp vec4 outColor;\n"
        "\n"
        "void main(void){\n"
        "    if((out_texCoord.x < 0.0) || (out_texCoord.y < 0.0)){\n"
        "        outColor = vec4(0.6,0.6,0.7,1.0);\n"
        "    } else {\n"
        "        outColor = vec4(out_texCoord,0.7,1.0);\n"
        "        \n"
        "    }\n"
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
void CubeProgram::draw(const Cube & cube){
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

    glBindBuffer(GL_ARRAY_BUFFER, cube.tb);
    location = glGetAttribLocation(program, "in_texCoord");
    glVertexAttribPointer(location, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(location);
    getErr("CubeProgram::draw() - get tb");

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