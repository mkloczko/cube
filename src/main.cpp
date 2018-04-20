#include <iostream>
#include <string>
#include <vector>

#include "LoadFiles.hpp"

using std::cout;
using std::endl;
using std::string;

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

    glEnable(GL_BLEND);
	glViewport(0, 0, 800, 600);
	while(!glfwWindowShouldClose(window)){

		glClearColor(0.9,0.3,0.3,0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwSwapBuffers(window);
	}

    glfwDestroyWindow(window);
    glfwTerminate();
	return 0;	

}