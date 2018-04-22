cmake_minimum_required(VERSION 3.3)
project(EigenTut)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -std=c++14 -pthread")

# Windows specific things
# ~~~~~~~~~~~~~~~~~~~~~~~

#Under windows: cmake .. -G 'Visual Studio 15 2017' -T'LLVM-vs2014'

if(WIN32)
	include_directories("windows/glew-2.1.0/include")
	set (GLEW_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/windows/glew-2.1.0/lib/Release/Win32/glew32s.lib")
endif()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glfw/)

find_package(OpenGL REQUIRED)

include_directories("stb/")
include_directories("eigen-git-mirror/")
include_directories("src/include")




set(SOURCE_FILES "src/main.cpp" "src/IncludeGL.cpp" "src/LoadFiles.cpp"
		         "src/Cube.cpp" "src/Camera.cpp" "src/WindowLogic.cpp")
add_executable(Task ${SOURCE_FILES})



target_link_libraries(Task glfw ${GLFW_LIBRARIES})
target_link_libraries(Task ${OPENGL_LIBRARY})
if(WIN32)
	target_link_libraries(Task ${GLEW_LIBRARY})
endif()
if(MSVC)
	set_target_properties(Task PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:CONSOLE")
	set_target_properties(Task PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE")
	target_compile_definitions(Task PRIVATE GLEW_STATIC HIGH)
endif()
target_compile_definitions(Task PRIVATE GL_GLEXT_PROTOTYPES HIGH)


