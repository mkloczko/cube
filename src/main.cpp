#include <iostream>
#include <string>
#include <vector>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include "IncludeGL.hpp"
#include "LoadFiles.hpp"
#include "Cube.hpp"
#include "Camera.hpp"

using std::cout;
using std::endl;
using std::string;

using Eigen::Matrix4f;
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
        std::cerr << "Failed to load shaders. Quitting..." << endl;
        return 3;
    }

    Matrix4f proj_matrix = orthoMatrix(-0.5,0.5,-0.5,0.5,0.25,100000);
    Matrix4f view_matrix = lookAtMatrix(Vector3f(1.5,2,1.5), Vector3f(0,0,0), Vector3f(0,1,0));
    Affine3f translation(Translation3f(-1,-0.5,0));

    Matrix4f ident = Matrix4f::Identity();

    cube_program.updateMatrix(proj_matrix*view_matrix);
//    cube_program.updateMatrix();

    glEnable(GL_BLEND);
    glViewport(0, 0, 800, 600);
    int ix = -1000;
    while(!glfwWindowShouldClose(window)){

//        translation = Eigen::Affine3f(Eigen::Translation3f(0,0,ix*0.1));
//        cube_program.updateMatrix(translation.matrix() * proj_matrix);

		glClearColor(0.6,0.4,0.3,0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        cube_program.draw(cube);
        glfwSwapBuffers(window);
        glfwPollEvents();
        ix++;
	}

    glfwDestroyWindow(window);
    glfwTerminate();
	return 0;	

}