#ifndef WINDOWLOGIC_GUARD
#define WINDOWLOGIC_GUARD

#include <Eigen/Core>

#include "IncludeGL.hpp"

using Eigen::Matrix4f;

struct WindowLogic {
    //Rotation matrix
    Matrix4f rotation_matrix = Matrix4f::Identity();
    //Scale matrix
    Matrix4f scale_matrix    = Matrix4f::Identity();
    double scale_value = 1;

    //Resizing
    double width    = 800;
    double height   = 600;
    double xy_ratio = 800/600;

    //Mouse clicks and movements
    bool mouse_pressed = false;
    bool mouse_delta   = false;



    double pos_x = -1, pos_y = -1;
    double dx    = -1, dy    = -1;

    void move(double x, double y);
};

void cursor_callback(GLFWwindow* window, double x, double y);
void click_callback(GLFWwindow* window, int button, int pressed, int mods );
void scroll_callback(GLFWwindow* window, double x, double y);
void resize_callback(GLFWwindow* window, int x, int y);

#endif