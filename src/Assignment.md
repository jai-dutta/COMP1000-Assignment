
## UCP Assignment

### Author: Jai Dutta   
### Student ID: 22073372


---

### Development  
I believe all required features have been implemented correctly.

### Compilation  
To compile the game:  
make  

For dark mode:  
make dark  

To reset to light mode:  
make clean  
make dark  

### Usage  
Run the game with a map file:  
Copy./treasure <map_file.txt>  

### Controls  
'w': Move up  
's': Move down  
'a': Move left  
'd': Move right  
'u': Undo last move  

### Gameplay  
  
Navigate the player 'P' to the treasure '$'  
Avoid the snake '~'  
Pick up the lantern '@' to increase visibility in dark mode  
Game ends when you reach the treasure or get caught by the snake  

### Files  

main.c: Main game loop and initialization  
game.c: Game logic and movement  
input.c: User input handling  
map.c: Map creation and management  
linkedList.c: Linked list (for undo feature)
random.c: Random number generation for snake movement  
