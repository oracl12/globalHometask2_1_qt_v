# Requirements:
Standard: **c++17**
Compliler: **g++**
OS: **Windows > 8.1; Linux**
Soft: **Qt libs || Qt Creator last-v** -> **Qt > 6**
Maker: **cmake**

# Diagram:
https://miro.com/app/board/uXjVNXtyeGg=/?share_link_id=520974767279

# Description of classes:
## Main:
Start point of app, includes basic libs and starts general services
## MainWindow:
Main class of window, which handles all the ui elements on screen
## MainWindowUi:
Set of predefined buttons and other ui elements
## Conf:
Storage class for most variables and constants, also shared for threads vars
## Enemy:
Class that acts as storage for matrix of another istance of program(your enemy)/bot; allows bot to use its matrix as well
## Bot:
Class that inherits from enemy its storage variables, have much bigger func as generating matrix, shooting etc...
## Game:
Kernel of program, handles window visibility, it's events and has a role of connection between different modules at one place
## Input:
Small size class to increase readibility of code
## Player:
Class of actual player; contains functionality which allows user to manipulate with ships&with matrix of enemy(shooting); 
Few of its methods: removeShip, placeShip, makeShot etc
## Renderer:
Class responsible for rendering most of stuff we see on window; allows to draw different rects of different colors with borders or without
## Ship:
Class that contains most logic for ships, check if ship at point, resize ship, change its direction; as well as all ships that we can move


## Other:
Small size header that contains function which is not compatible on all OS's
