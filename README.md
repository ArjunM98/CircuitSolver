# CircuitSolver

This repo contains the logic required to build a command line circuit solver. The user has the ability to add a variety of resistors and voltage sources via the command line. The simulator can then solve the rest of the circuit for the remaining votlages at each node not specified by the user. 

### Parser

Textual input interface for interacting with circuit - UI. Queries backend to modify, add, print, or delete resistors/voltage sources.
[More details about how the interface works can be found here.](Parser/lab2_handout.pdf)

### DB_Backend_Nodes

Used dynamically allocated arrays to store both layout and components of circuit including resistors and voltage sources. Can create, insert, modify, delete, and print circuits. [More details about how circuit information is stored can be found here.](DB_Backend_Nodes/lab3_handout.pdf)

### Voltage_Solver_Logic

Modified backend logic to store layout and components of circuit using linked lists instead of arrays. User can specify voltages of certain nodes within the circuit. For all other nodes with an unknown voltage, the simulator solves for the voltage using an iterative process. [More details about the algorithm used to solve for unknown voltages can be found here.](Voltage_Solver_Logic/lab4_handout.pdf)

### DB_Backend_Domain_Name

Created a binary search tree used to store circuit names (Domain Names). Allowed for fast look up based on user entered input string.
[More details about the implemention can be found here.](DB_Backend_Domain_Name/lab5_handout.pdf)

### Graphics

Using the easyGL library in C++, I created a simple interface for the user to modify, add, and delete basic shapes which could be used to build a bread board, and the corresponding components of a circuit. [More details about the easyGL library, along with my implementation can be found here.](Graphics/lab6_handout.pdf)
