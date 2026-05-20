# Tomb of the Mask

A desktop version of the popular mobile game **Tomb of the Mask**, written entirely in C using the **SDL2** library. This project is for the Programming 1 course, focusing on software architecture, memory management, and event-driven programming.

## Game Concept
The goal of the game is to navigate a yellow character through various labyrinth levels to reach the destination. The core mechanic mimics the original game: the character slides continuously from wall to wall. Quick reflexes and strategic path planning are key to completing the maps.

<img width="1077" height="740" alt="image" src="https://github.com/user-attachments/assets/4604695e-1bfe-4475-933e-6e109ab8b5c1" />


## Features
- **5 Unique Levels:** Maps loaded dynamically from external text files (`palya1.txt`, etc.).
- **Wall-to-Wall Sliding Physics:** Authentic movement controls matching the mobile version.
- **Persistent Statistics:** Automatically tracks total play time and completed levels.
  <img width="367" height="120" alt="image" src="https://github.com/user-attachments/assets/9ed71359-4f5f-4659-be2b-137b03c4eafc" />


## Technical Architecture & Implementation Details

The development prioritized modularity, strict separation of concerns, and robust resource management. The system is built on an event-driven architecture and a State Machine.

### 1. Dynamic Memory Management & Map Handling (`beolvas.h`, `beolvas.c`)
Levels are stored in external text files and loaded dynamically at runtime, allowing for scalable map sizes without hardcoded limits.
* **Data Encapsulation:** The `matrix` struct binds together map metadata (rows, columns), a dynamically allocated 2D array (`int **matriksz`), and the player's current state (`karakter player`).
* **Two-Phase Loading Protocol:**
  1. *Dimension parsing:* The program reads the file to determine the grid size and allocates the exact required memory using an array of pointers.
  2. *Data population:* A second pass fills the allocated 2D structure with entity codes (walls, paths, finish line).
* **Resource Cleanup:** To prevent memory leaks, a dedicated cleanup function (`matrix_felszabadit`) explicitly frees the memory blocks row by row upon exit or level change. The `debugmalloc.h` library is integrated to guarantee memory safety.

### 2. State Machine & Event Loop (`main.c`, `menu.h`, `iranyitas.h`)
The game flow is controlled by a central event loop and with a State Machine.
* **State Management:** The current context (Main Menu, Level Selection, Active Gameplay) is defined by the `menuk` enum. A central `switch-case` block dictates rendering and logic branches based on this state.
* **Event-Driven Synchronization:** Utilizing `SDL_WaitEvent`, the main loop is entirely event-driven, minimizing idle CPU usage.
* **Fixed Timestep Physics (`ablak.h`):** An `SDL_AddTimer` generates custom events every 20ms. This decouples the sliding physics from frame rendering, ensuring consistent movement speed regardless of hardware performance.

### 3. UI Abstraction & Interaction (`alakzatok.h`)
Graphical User Interface elements are implemented using an object-oriented approach in C.
* **Button Struct:** Interactive elements are encapsulated within a `gombok` struct containing geometric data (X, Y, Width, Height), text labels, and functional IDs.

### 4. Data Persistence (`statisztika.h`)
User performance is tracked and stored persistently via file I/O operations.
* The system records UNIX timestamps upon launch and safe exit.
* Playtime and completion metrics are formatted and exported to `statisztika.txt` at the end of each session.

### Main Menu
<img width="1071" height="713" alt="image" src="https://github.com/user-attachments/assets/64770437-5324-4f2c-aa69-b3803dd171d6" />


### Level Selection
<img width="1073" height="713" alt="image" src="https://github.com/user-attachments/assets/b586fe0d-4c64-4ac0-b178-a5936ff275d5" />

## Project Structure
- `main.c` - Entry point, main game loop, and SM.
- `ablak.h` / `.c` - Window handling and SDL timer configurations.
- `beolvas.h` / `.c` - Map reading, 2D matrix allocation, and rendering.
- `alakzatok.h` / `.c` - UI components, text rendering.
- `iranyitas.h` / `.c` - Handling player input and sliding logic.
- `menu.h` / `.c` - Rendering logic for different game states.
- `statisztika.h` / `.c` - Tracking game stats and file I/O.
