#include "Postprocess.hpp"

using std::function;

constexpr GLfloat canvas_vertices[6*2] = {
        0.0, 0.0,
        1.0, 0.0,
        0.0, 1.0,

        1.0, 0.0,
        1.0, 1.0,
        0.0, 1.0
};

constexpr char vertex_shader[] = "#version 300 es\n"
        "in  highp vec2 in_position;\n"
        "out highp vec2 tex_coord;\n"
        "\n"
        "void main(void){\n"
        "   tex_coord      = in_position;\n"
        "   highp vec2 pos = (in_position - vec2(0.5,0.5))*2.0;\n;"
        "   gl_Position  = vec4(pos,0.0,1.0);\n"
        "}\n";

constexpr char fragment_shader[] = "#version 300 es\n"
        "in  highp vec2 tex_coord;\n"
        "out highp vec4 outColor;\n"
        "uniform highp sampler2D tex;\n"
        "uniform highp float pixel_x;\n"
        "uniform highp float pixel_y;\n"
        "\n"
        "void main(void){\n"
        "    highp vec3 color = vec3(0.0);\n"
        "    for(int x = 0; x < 3; x++){\n"
        "       for(int y = 0; y < 3; y++){\n"
        "           highp float xf = float(x);\n"
        "           highp float yf = float(y);\n"
        "           color += texture(tex, tex_coord + vec2( pixel_x*xf,  pixel_y*yf)).xyz;\n"
        "           color += texture(tex, tex_coord + vec2(-pixel_x*xf,  pixel_y*yf)).xyz;\n"
        "           color += texture(tex, tex_coord + vec2( pixel_x*xf, -pixel_y*yf)).xyz;\n"
        "           color += texture(tex, tex_coord + vec2(-pixel_x*xf, -pixel_y*yf)).xyz;\n"
        "       }\n"
        "    }\n"
        "    color = color/36.0;\n"
        "    outColor = vec4(color,1.0);\n"
        "}\n";

bool Postprocess::initialize(){
    glGenFramebuffers(1, &framebuffer);
    glGenTextures(1, &tex_color_buffer);
    glGenRenderbuffers(1, &renderbuffer);

    glGenVertexArrays(1,&canvas_vao);
    glGenBuffers(1,&canvas_vb);

    glBindVertexArray(canvas_vao);

    glBindBuffer(GL_ARRAY_BUFFER,canvas_vb);
    glBufferData(GL_ARRAY_BUFFER,6*2*sizeof(GLfloat), canvas_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);

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

void Postprocess::resize(int x, int y) {
    glBindTexture(GL_TEXTURE_2D, tex_color_buffer);
    glBindFramebuffer(GL_FRAMEBUFFER,framebuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer);

    glTexImage2D(
            GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL
    );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, x, y);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex_color_buffer,0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer);

    glUseProgram(program);
    GLuint location;
    location = glGetUniformLocation(program, "pixel_x");
    glUniform1f(location, (1.0/(GLfloat)x));
    location = glGetUniformLocation(program, "pixel_y");
    glUniform1f(location, (1.0/(GLfloat)y));

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void Postprocess::render(const function<void()>& drawer){
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    drawer();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Postprocess::draw(){
    GLuint location;

    glUseProgram(program);
    getErr("Postprocess::draw() - enable program");
    glBindVertexArray(canvas_vao);
    getErr("Postprocess::draw() - bind vao");

    glBindBuffer(GL_ARRAY_BUFFER,canvas_vb);
    getErr("Postprocess::draw() - bind vb");
    location = glGetAttribLocation(program, "in_position");
    getErr("Postprocess::draw() - no location for vb");
    glVertexAttribPointer(location, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(location);
    getErr("Postprocess::draw() - get vb");

    glDisable(GL_DEPTH_TEST);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex_color_buffer);
    getErr("Postprocess::draw() - bind texture");

    glDrawArrays(GL_TRIANGLES,0,6);

    getErr("Postprocess::draw() - draw arrays call");

    glBindBuffer(GL_ARRAY_BUFFER,0);
    getErr("Postprocess::draw() - unbind array buffer");
    glBindVertexArray(0);
    getErr("Postprocess::draw() - unbind vao");
    glUseProgram(0);

}