# cub3D - My First RayCaster with MiniLibX

> A 3D graphics project inspired by the classic **Wolfenstein 3D**, built using ray-casting and `MiniLibX`.  
> Developed as part of the 42 school curriculum (Version 11.0).

---

## 🕹️ Project Overview

`cub3D` is a simple first-person raycasting engine built in C, allowing you to explore a 3D maze from a 2D map, similar to early FPS games like Wolfenstein 3D. The core objective is to simulate a 3D environment using 2D calculations via raycasting techniques.

This project demonstrates fundamental concepts in:
- Math & trigonometry (for ray casting and perspective)
- Graphics programming (via MiniLibX)
- Event handling (keyboard inputs, window management)
- Parsing (custom `.cub` map format)

---

## 📸 Screenshots

| Basic Rendering | Bonus Features |
|-----------------|----------------|
| ![Mandatory View](./screenshots/mandatory.png) | ![Minimap](./screenshots/minimap.png) |

---

## 📦 Features

### ✅ Mandatory Features
- [x] First-person 3D rendering using raycasting
- [x] Textured walls based on wall orientation (N, S, E, W)
- [x] Movement: `W`, `A`, `S`, `D` for moving, arrows for rotation
- [x] Map parsing from `.cub` files
- [x] Floor and ceiling color rendering
- [x] Graceful handling of program exit (`ESC` key, red cross, errors)

### 🗺️ `.cub` Scene File Format

The scene file describes:
- Texture paths for all wall directions (NO, SO, WE, EA)
- Floor and ceiling colors (`F`, `C`)
- A 2D map using characters: `1` (wall), `0` (empty), `N/S/E/W` (player start position)

Example:
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm
F 220,100,0
C 225,30,0

111111
100001
1000N1
111111

### ❗ Error Handling
- The program exits with `Error\n` and a clear message for:
  - Invalid or malformed maps
  - Unclosed walls
  - Incorrect file format or missing assets

---

## 🚀 Bonus Features (If Implemented)

> Bonuses are only evaluated if the mandatory part is perfect.

- [ ] Wall collisions
- [ ] Minimap system
- [ ] Doors (open/close)
- [ ] Animated sprites (e.g. enemies or collectibles)
- [ ] Mouse look (rotate using mouse)
- [ ] HUD, weapon system, health bar, shadow effects

---

## 🔧 Build Instructions

### Requirements
- Unix-like OS (Linux or macOS)
- `gcc`, `make`
- `MiniLibX` library (included or system-installed)
- `libft` (included in `./libft/`)

### Compile the Project

```bash
make
Run the Game
./cub3D path/to/map.cub
Clean Project

make clean      # remove object files
make fclean     # remove object files and binary
make re         # rebuild everything
🧠 Learning Objectives
Deepen understanding of 2D to 3D projection

Apply math and geometry in real-time applications

Manage event-driven programming

Improve code organization, error handling, and memory management

👨‍💻 Author
Your Name - Your GitHub

Project developed at 42 Network

📄 License
This project is for educational purposes as part of the 42 curriculum and follows fair use principles for any referenced material.


---

### ✅ Tips:
- Make sure you update the `Author`, `License`, and screenshot paths (`./screenshots/mandatory.png`) if you use actual images in your repo.
- Include your `.cub` test maps and a `maps/` folder if you want to provide examples.
- If you implemented any bonuses, list them clearly with checkboxes.

