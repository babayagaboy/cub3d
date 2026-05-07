*This project has been created as part of the 42 curriculum by myivanov, hgutterr.*

# cub3d

## Description

`cub3d` is a graphic programming project from the 42 curriculum inspired by the
classic game *Wolfenstein 3D*. The goal of the project is to build a simple
3D game engine using the **raycasting** technique and the **MiniLibX** graphical
library.

The program renders a first-person view of a 2D map by projecting walls,
textures, sprites, and interactive elements into a pseudo-3D environment.
The project focuses on low-level graphics programming, mathematical concepts,
event handling, parsing, and optimization.

This implementation includes all mandatory features as well as several bonus
features such as a minimap, doors, animated sprites, mouse rotation, collision
handling, and textured floors and ceilings.

---

# Features

## Mandatory Part

- Raycasting-based 3D rendering
- Wall textures depending on orientation
- Smooth player movement and rotation
- Custom `.cub` map parsing
- Floor and ceiling rendering
- Keyboard controls
- Window management with MiniLibX
- Error handling and map validation

## Bonus Part

- Minimap
- Doors
- Mouse rotation
- Animated sprites
- Collision system
- Textured floors and ceilings
- Mouse click interactions

---

# Instructions

## Requirements

- Linux
- GCC
- Make
- MiniLibX
- X11 development libraries

## Compilation

Clone the repository and compile the project using:

```bash
make
```

To clean object files use:

```bash
make clean
```

To remove all generated files use:

```bash
make fclean
```

to rebuild the project use:

```bash
make re
```

## Execution

Run the program with a valid.cub map:

```bash
./cub3d maps/starWars.cub
```

# Controls

| Key / Input | Action |
|---|---|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Move left |
| `D` | Move right |
| `Mouse Movement` | Rotate camera |
| `Left Click` | Attack animation |
| `Right Click` | Lightsaber deployment |
| `ESC` | Exit the game |

---

# Map Format

The project uses `.cub` configuration files containing:

- Texture paths
- Floor and ceiling information
- The map layout
- Player spawn position and orientation

## Example

```txt
NO textures/north.xpm
SO textures/south.xpm
WE textures/west.xpm
EA textures/east.xpm

F 220,100,0
C 225,30,0

1111111111
1000000001
100N000001
1111111111
```

---

# Technical Overview

## Raycasting

The rendering engine uses the raycasting algorithm to simulate a 3D environment
from a 2D map. Rays are cast from the player's point of view to detect walls
and calculate their projected height on screen.

## Parsing

The parser validates:

- Texture paths
- RGB values
- Map enclosure
- Player position
- Invalid characters
- Map formatting rules

## Graphics

The project uses the MiniLibX graphical library for:

- Window creation
- Image rendering
- Texture handling
- Event management
- Mouse and keyboard hooks

---

# Project Structure

```txt
.
├── inc/
├── src/
├── mlx/
├── textures/
├── maps/
├── assets/
├── Makefile
└── README.md
```

---

# Resources

## Documentation and References

- MiniLibX documentation
- Lode's Computer Graphics Tutorial:  
  https://lodev.org/cgtutor/raycasting.html

- Harm Smits MiniLibX Guide:  
  https://harm-smits.github.io/42docs/libs/minilibx

- 42 Subject PDF

## AI Usage

AI tools were used as an auxiliary resource for:

- General explanations of raycasting concepts
- Clarifying mathematical formulas
- README formatting and writing assistance

All project architecture, implementation, debugging, and core logic were developed manually.