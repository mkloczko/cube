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

## Nix build

It is now also possible to build the project using nix, which will also handle dependencies. Although submodules will have to be loaded manually.

```bash
$ git submodule init
$ git submodule update
```

To build:

```bash
$ nix-build install.nix    
```

To install the project, use:

```bash
$ nix-env -i -f install.nix
```

To try it locally, use:

```bash
$ nix-shell install.nix
$ mkdir build
$ cd build
$ cmake ..
$ make
$ ./Task
```


