# cub3D  
## 3D Raycasting Project from 42

cub3D is a simple 3D game engine project created at 42 coding academy. The core of the project is built around raycasting, using the **DDA (Digital Differential Analizer)** algorithm to render a 3D view from a 2D map. The program loads a map file (with the `.cub` extension), parses it, and then renders the scene with walls and player movement — all using your CPU, no fancy GPU tricks.

### How to Compile  
Open a terminal in the project directory and run:  
```
make
```
This will compile the program and generate the executable `cub3D`.

### How to Run  
Run the program by specifying a valid map file:  
```
./cub3D map.cub
```

Make sure the map file follows the correct format required by the project. The map attached in this repo works fine.

### What to Expect  
- A first-person 3D view rendered with raycasting and the DDA algorithm.  
- Smooth player movement with collision detection.  
- Map parsing that interprets walls and spaces.

Feel free to browse through the code to see how the raycasting works or how the map is parsed. Try running the program with your own maps or tweak the code to add your own features.

Enjoy exploring 3D graphics from scratch!

