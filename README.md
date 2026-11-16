# MinecraftCloneC

A small Minecraft-style voxel renderer written in C using OpenGL 3.3, GLFW, glad and cglm.

## Features

- Chunk-based block world that only draws visible faces
- Free-look first-person camera
- Textured blocks (stb_image) with GLSL shaders

## Requirements

- A C compiler (`gcc`) and `make`
- OpenGL 3.3+ capable GPU/driver
- [GLFW](https://www.glfw.org/) and [cglm](https://github.com/recp/cglm)

On Debian/Ubuntu:

```sh
make deps   # runs: sudo apt-get install build-essential pkg-config libglfw3-dev libgl1-mesa-dev libcglm-dev
```

glad and stb_image are bundled in `lib/`.

## Build and run

```sh
make        # build the `game` binary
make run    # build and run (run from the repo root so shaders/ is found)
make clean  # remove build outputs
```

## Project layout

```
src/main.c              entry point and main loop
src/engine/block/       chunks and entities
src/engine/camera/      camera
src/engine/input/       input handling
src/engine/render/      renderer, shaders, textures
src/engine/io/          file and array helpers
shaders/                GLSL shaders and textures
lib/                    glad and stb_image
```
