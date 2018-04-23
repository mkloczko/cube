# Happy cube

The goal of the task is to render a cube (with Phong shading) rendering an image on one of the sides of the cube. 
The program loads images stored in ```frames/``` directory: from ```image-0000.png``` to ```image-0060.png```.

# Build and run instructions

Clone the repository and then:

```bash
$ git submodule init
$ git submodule update
```

Building:

```bash
$ mkdir build
$ cd build
$ cmake ..
$ make Task
```

Running:

```bash
$ ./Task ../frames
```