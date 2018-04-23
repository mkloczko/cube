#include <iostream>
#include <string>
#include <vector>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include "WindowLogic.hpp"
#include "IncludeGL.hpp"
#include "LoadFiles.hpp"
#include "Cube.hpp"
#include "Camera.hpp"

using std::cout;
using std::endl;
using std::string;

using Eigen::Matrix4f;
using Eigen::Matrix3f;
using Eigen::Vector3f;
using Eigen::Affine3f;
using Eigen::Translation3f;



int main(int argc, char ** argv){

	// Load frames
	string path = "frames";
	if (argc == 2){
		path = string(argv[1]);
	}

	vector<Image> images = Image::loadImages(path, "image");
	//Check if all files are loaded.
	bool not_loaded = false;
	for(int i = 0; i < 60 && !not_loaded; i++){
		not_loaded = images[i].data == nullptr;
	}

	if(!not_loaded){
		cout << "All images initially loaded." << endl;
	}

	//Initialize OpenGL context.
    if (!glfwInit()) {
        std::cerr << "Could not initalize GLFW context." << endl;
        return 1;
    }


    GLFWwindow * window = glfwCreateWindow(800, 600, "Test task", NULL, NULL);
	//getErr("Visualiser create window");
    if (!window) {
        glfwTerminate();
        std::cerr << "Error: Could not create a GLFW Window." << endl;
        return 2;
    }
	glfwMakeContextCurrent(window);
	getErr("Current context");

    //Set user pointer for handling window logic.
    WindowLogic logic;
    glfwSetWindowUserPointer(window,&logic);

    //Mouse callbacks.
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetCursorPosCallback(window, cursor_callback);
    glfwSetMouseButtonCallback(window, click_callback);
    glfwSetWindowSizeCallback(window, resize_callback);

#ifdef _WIN32
    // Initialize GLEW
	if (glewInit() != GLEW_OK) {
		cerr << "Failed to initialize GLEW" << endl;
		return 2;
	}
	getErr("GLEW");
#endif

    //Initialize the cube, and set it up.
    Cube cube;
    cube.initialize(images);

    CubeProgram cube_program;
    if(!cube_program.initialize()){
        glfwDestroyWindow(window);
        glfwTerminate();
        std::cerr << "Failed to load shaders. Quitting..." << endl;
        return 3;
    }

    double x_ratio = std::max(1.0, logic.xy_ratio);
    double y_ratio = std::min(1.0, logic.xy_ratio);
    Matrix4f proj_matrix = proj_matrix =  projectionMatrix( -0.5*x_ratio, 0.5*x_ratio
            , -0.5/y_ratio, 0.5/y_ratio
            , 0.5, 1000000);
    Matrix4f view_matrix = lookAtMatrix(Vector3f(0,0,3), Vector3f(0,0,0), Vector3f(0,1,0));
    Affine3f translation(Translation3f(-0.5,-0.5,-0.5));

    Matrix4f view_model = view_matrix * logic.scale_matrix
                          * logic.rotation_matrix * translation.matrix();
    Matrix3f normal_matrix = Matrix3f(view_model.block<3,3>(0,0));

    cube_program.updateMatrix(proj_matrix * view_model);
    cube_program.updateNormalMatrix(normal_matrix);

    glViewport(0, 0, logic.width, logic.height);
    glEnable(GL_DEPTH_TEST);
    while(!glfwWindowShouldClose(window)){


        glViewport(0, 0, logic.width, logic.height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.6,0.4,0.3,0);
        cube_program.draw(cube);
        x_ratio = std::max(1.0, logic.xy_ratio);
        y_ratio = std::min(1.0, logic.xy_ratio);
        proj_matrix = projectionMatrix( -0.5*x_ratio, 0.5*x_ratio
                                      , -0.5/y_ratio, 0.5/y_ratio
                                      , 0.5, 1000000);

        view_model = view_matrix * logic.scale_matrix
                              * logic.rotation_matrix * translation.matrix();
        normal_matrix = Matrix3f(view_model.block<3,3>(0,0));

        cube_program.updateMatrix( proj_matrix * view_model);
        cube_program.updateNormalMatrix(normal_matrix);
        glfwSwapBuffers(window);
        glfwPollEvents();
	}

    glfwDestroyWindow(window);
    glfwTerminate();
	return 0;	

}