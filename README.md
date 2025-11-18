# cub3D

A 3D maze game inspired by Wolfenstein 3D, built with raycasting technology as part of the 42 school curriculum.

## 🎮 Description

cub3D is a first-person 3D maze game that implements raycasting to render a 3D perspective from a 2D map. Navigate through corridors, interact with doors, collect items, avoid hazards, and reach the extraction pod to win!

## ✨ Features

### Core Features
- **Raycasting Engine**: Real-time 3D rendering using raycasting algorithms
- **Textured Walls**: Different textures for North, South, East, and West walls
- **Floor & Ceiling**: Customizable colors for floor and ceiling
- **Smooth Movement**: WASD controls with mouse look (arrow keys supported)

### Bonus Features
- **Interactive Doors**: Open and close doors with animations
- **Enemies (Aliens)**: Hostile characters that chase and attack the player
- **Items & Pickups**: Collect health packs and key items
- **Health System**: Take damage from enemies and lava tiles
- **Minimap**: Real-time minimap showing player position and surroundings
- **Sprites**: Animated characters and objects
- **Audio System**: Background music and sound effects for footsteps, doors, pickups, and combat
- **End Screens**: Victory and defeat screens with audio cues
- **Screen Shake**: Visual feedback when taking damage

## 🎵 Audio

Powered by **miniaudio** library for cross-platform audio:
- Background music
- Footstep sounds
- Door opening sounds
- Item pickup sounds
- Hit/damage effects
- Victory/defeat themes

## 🛠️ Technical Stack

- **Language**: C
- **Graphics**: MLX42 (OpenGL-based graphics library)
- **Audio**: miniaudio
- **Build System**: Makefile
- **Platform Support**: Linux and macOS

## 📋 Requirements

### Linux
- GCC compiler
- GLFW library: `sudo apt-get install libglfw3-dev`
- OpenGL libraries: `sudo apt-get install libgl1-mesa-dev`
- Make

### macOS
- Clang compiler (comes with Xcode Command Line Tools)
- GLFW via Homebrew: `brew install glfw`
- Make

## 🚀 Installation

1. Clone the repository:
```bash
git clone https://github.com/SmVynt/42Cub3D.git
cd 42Cub3D
```
2. Build the project:
```bash
make
```
The Makefile will automatically:

Clone MLX42 if not present
Build MLX42
Compile all source files
Link everything into the cub3D executable

## Usage
```bash
./cub3D <map_file.cub>
```

Example:
```bash
./cub3D maps/00.cub
./cub3D maps/test/test_walls_fade.cub
```

Controls:
**W/A/S/D**: Move forward/left/backward/right
**Arrow Keys**: Look left/right (or use mouse)
**E**: Interact with doors
**ESC**: Exit game
**M**: Toggle minimap (if available)

Map Format (.cub)
Map files define the game environment with the following structure:
```bash
NO ./textures/north_wall.png
SO ./textures/south_wall.png
WE ./textures/west_wall.png
EA ./textures/east_wall.png
F 64,64,64
C 235,206,235

111111
1N0001
100001
111111
```
## 📝 Notes
The game complies with 42 school's norminette coding standard with an exceptopn of audio (which is not allowed by the project's subject)

## 👥 Authors
Natalia Mikula  @NatimiDev
Pavel Smolin    @SmVynt

## 📄 License
This project is part of the 42 school curriculum.

## 🙏 Libraries
MLX42 - Graphics library
miniaudio - Audio library

## 🎵 Audio Credits
Sound effect obtained from [Pixabay](https://pixabay.com/)
- [Dark Cinematic Space Pads Loop] by [Ido Berg]
- [Spaceship Whoosh, Video Game Sound] by [DRAGON-STUDIO]
- [Key] by [Musheran]
