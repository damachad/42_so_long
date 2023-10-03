# So_long :star:

## Introduction :rocket:

This project was developed as part of the 42 school curriculum, focusing on game development in 2D. The goal is to create a small game where the player has to collect all the collectibles on a map and then reach the exit. The bonus part adds enemies to avoid. The game utilizes the MiniLibX library for graphical management, enabling rendering, sprites, animations, and more.

## Project Overview :paintbrush:

In this project, you will gain valuable experience and knowledge in various aspects of game development, including:

- Creating 2D games.
- Rendering graphics.
- Managing sprites and animations.
- Implementing game logic and mechanics.

## Getting Started :page_with_curl:

To get started with this project, follow these steps:

1. Clone this repository to your local machine:

   ```sh
   git clone https://github.com/damachad/so_long
   ```
2. Navigate to the project directory:

   ```sh
    cd so_long
   ```
3. Compile the project:

    ```sh
    make
    ```

4. Run the game:

    ```sh
    ./so_long maps/<map>.ber
    ```
    Replace "map" with a valid map name from the maps directory.

## Project Structure :computer:
The project directory is organized as follows:

- 'images/': Contains image files used for sprites and textures.
- 'includes/': Contains header files for the project.
- 'maps/': Contains map files in .ber format that define the game levels.
- 'src/': Contains the source code of the game.
- 'libft/': Contains the library functions used in the project.
- 'mlx/': Contains the MiniLibX library for graphical management.

## Controls 🎮
Use the WASD keys to move the player character.
Collect all collectibles on the map.
Reach the exit to complete the level.

## Acknowledgments :sparkles: 
This project was completed as part of the curriculum at 42 school.
Happy coding, and have fun creating your game!

## Notes 📝
Only the bonus has enemy sprites.   
Run:
```sh
   make bonus
    ./so_long_bonus maps/bonus/<map>.ber
```
⚠️ If you want to use make clean, you need to give execution permission to the configure file in mlx.   
Sample from the game:   

![Sample from so_long](https://github.com/damachad/so_long/assets/128734978/dcf4ebec-8b58-4dc0-92b0-e0c89446f56f)

