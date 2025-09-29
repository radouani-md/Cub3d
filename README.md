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

The scene file describes:<br>
- Texture paths for all wall directions (NO, SO, WE, EA)<br>
- Floor and ceiling colors (`F`, `C`)<br>
- A 2D map using characters: `1` (wall), `0` (empty), `N/S/E/W` (player start position)<br>

Example:<br>
NO ./textures/north.xpm<br>
SO ./textures/south.xpm<br>
WE ./textures/west.xpm<br>
EA ./textures/east.xpm<br>
F 220,100,0<br>
C 225,30,0<br>

111111<br>
100001<br>
1000N1<br>
111111<br>

### ❗ Error Handling
- The program exits with `Error\n` and a clear message for:
  - Invalid or malformed maps
  - Unclosed walls
  - Incorrect file format or missing assets

---

## 🚀 Bonus Features (If Implemented)

> Bonuses are only evaluated if the mandatory part is perfect.<br>

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

### 🧠 Learning Objectives
Deepen understanding of 2D to 3D projection<br>

Apply math and geometry in real-time applications<br>

Manage event-driven programming<br>

Improve code organization, error handling, and memory management<br>

### 👨‍💻 Authors
Mohammed Radouani<br>
Youssef Bahmaz<br>


Project developed at 42 Network<br>

📄 License
This project is for educational purposes as part of the 42 curriculum and follows fair use principles for any referenced material.

### Compile & Run The Project

```bash
make && ./cub3D path/to/map.cub
```
### Clean Project
```bash
make clean      # remove object files
make fclean     # remove object files and binary
make re         # rebuild everything
