#include "WindowLogic.hpp"

#include <iostream>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include "IncludeGL.hpp"

using namespace Eigen;


void WindowLogic::move(double x, double y){
        if(pos_x > 0 || pos_y > 0){
            mouse_delta = true;
            dx = x - pos_x;
            dy = y - pos_y;
        }

        pos_x = x;
        pos_y = y;
}

//Callbacks:
void cursor_callback(GLFWwindow* window, double x, double y){

    WindowLogic * logic = static_cast<WindowLogic*>(glfwGetWindowUserPointer(window));


    if(logic == nullptr){
        return;
    }

    logic->move(x,y);

    if(logic->mouse_delta && logic->mouse_pressed){
        double yaw   = logic->dx/100;
        double pitch = logic->dy/100;
        Affine3f ry(Affine3f(AngleAxisf(yaw, Vector3f::UnitY())));
        Affine3f rx(Affine3f(AngleAxisf(pitch, Vector3f::UnitX())));

        logic->rotation_matrix = rx.matrix() * ry.matrix() * logic->rotation_matrix;
    }

}

void click_callback(GLFWwindow* window, int button, int pressed, int mods ){
    WindowLogic * logic = static_cast<WindowLogic*>(glfwGetWindowUserPointer(window));

    if (button == GLFW_MOUSE_BUTTON_1){
        logic->mouse_pressed = pressed == GLFW_PRESS;
    }

}

void scroll_callback(GLFWwindow * window, double x, double y){
    WindowLogic * logic = static_cast<WindowLogic*>(glfwGetWindowUserPointer(window));


    logic->scale_value = logic->scale_value + y/10;
    logic->scale_value = std::min(2.5, std::max(0.75, logic->scale_value));
    float ratio = logic->scale_value;

    Affine3f scale(Scaling(ratio));

    logic->scale_matrix = scale.matrix();
}

void resize_callback(GLFWwindow* window, int x, int y){
    WindowLogic * logic = static_cast<WindowLogic*>(glfwGetWindowUserPointer(window));

    double fl = ((double)x) / ((double)y);
    logic->width    = x;
    logic->height   = y;
    logic->xy_ratio = fl;
}