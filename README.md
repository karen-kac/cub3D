# cub3D

## Project Overview
cub3D is a simple 3D game engine inspired by Wolfenstein 3D. It uses raycasting technology to create a pseudo-3D environment.

## Compilation
The project can be compiled with the following command:

```bash
make
```

Required libraries (libft and MiniLibX) will be compiled automatically.

## Execution
After compilation, run the program with a map file:

```bash
./cub3D maps/map1.cub
```

## Requirements

### Linux
- gcc
- make
- X11 development files (xorg)
- XShm extension (libxext-dev)
- BSD utility functions (libbsd-dev)

Example:
```bash
sudo apt-get install gcc make xorg libxext-dev libbsd-dev
```

### macOS
- Xquartz

```bash
brew install Xquartz
```
Restart is required after installation.

## Map Files
Map files have a `.cub` extension and include:
- Texture paths (for north, south, east, and west walls)
- Floor and ceiling colors (RGB values)
- Map layout

## Controls
- W: Move forward
- S: Move backward
- A: Strafe left
- D: Strafe right
- ←: Rotate left
- →: Rotate right
- ESC: Exit

## Project Structure
- srcs: Source code
  - `init/`: Initialization
  - `input/`: Input handling
  - `parser/`: Map parsing
  - `raycasting/`: Raycasting logic
  - `render/`: Rendering
  - `utils/`: Utility functions
  - `libft/`: Basic C function library
  - `minilibx-linux/`: Graphics library
- includes: Header files
- maps: Sample maps
- textures: Texture files

## Error Handling
The program displays error messages for invalid maps or configurations.
Refer to the provided sample maps for proper map formatting.