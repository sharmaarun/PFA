PFA
===

Implementation of A* path finding algorithm using
irrlicht and vc++


//1st phase create mode
user enters the W x H
[W and H max length allowed : 24]

map is generated (empty one)

user is allowed to choose between two object types : walkable paths and obstacles

	walkable :
		road-tile
		sand-tile
	obstacles:
		tree
		grass - tile
		stone

user creates the map and saves it as .pfm(pathfinding-map) file

[Note : after clicking SAVE button, goto console [in bg] and enter a name for the file there, press enter
        then come back to the GUI . File will be saved.]


//2nd phase : playmode
user loads a map and starts playing it 
	model and maps are loaded. model is put over the map on some random (walkable tile)

user then clicks any place on the map(that is walkable) and the AI algorithm calculates the path to that position

the returned path is followed by the character
