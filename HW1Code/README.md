# Advanced-topics-in-programming

Names:
- Mohammad Daadusch -212001192
- jad Mahajne - 318978152

Explanation of the Input File
The input file for your vacuum cleaner simulation contains critical information about the house layout, the vacuum cleaner's docking station, battery capacity, and maximum allowed steps. Below is a detailed explanation of each part of the input file:
1.	Docking Station Coordinates:
    -	Format: x, y
    -	Description: This line specifies the coordinates of the docking station in the house matrix. The docking station is the starting point for the vacuum cleaner and is always clean (i.e., it does not contain any dirt). The coordinates are given in the format x,y where x is the row index and y is the column index.
    -	Example: 2,3 indicates that the docking station is located at row 2, column 3 in the house matrix.
2.	Maximum Battery Steps:
    -	Format: A single integer or float value.
    -	Description: This line specifies the maximum number of steps the vacuum cleaner can take before its battery is exhausted. This value determines how long the vacuum can operate before it died.
    -	Example: 100 indicates that the vacuum cleaner has 100 steps worth of battery life.
3.	Maximum Steps Allowed:
    -	Format: A single integer value.
    -	Description: This line specifies the maximum number of steps the vacuum cleaner is allowed to take during the simulation. 
    -	Example: 1000 indicates that the vacuum cleaner can take up to 1000 steps in the simulation.
4.	House Matrix:
    -	Format: A matrix of integers.
    -  	Description: The remaining lines of the input file describe the layout of the house as a matrix. Each element in the matrix can have one of the following values:
        -	1-9: Indicates the amount of dirt present at that location. Higher values represent more dirt.
        -   -1: Indicates a wall or out-of-bound area where the vacuum cleaner cannot pass through.
        -	0: Indicates a clean, navigable area with no dirt.
        -	The house matrix may or may not be surrounded by walls initially. If it is not surrounded by walls, the program will check and add walls around the matrix to ensure it is enclosed.


*	Example:
With walls:
-1  -1   -1   -1   -1   -1  -1  -1
-1   5   -1   -1   -1   -1  -1  -1
-1   0   -1    0   -1    5   5  -1
-1   0   -1   -1   -1    0   1  -1
-1   2    5    3    4    0   6  -1
-1  -1   -1  - 1   -1   -1  -1  -1

Without walls (the same example):
5  -1  -1  -1 -1  -1              
0  -1   0  -1  5   5 
0  -1  -1  -1  0   1 
2   5   3   4  0   6

In this example:
-	The matrix represents a house layout with 4 rows and 6 columns.
-	1, 2, and 3 indicate dirt levels at their respective positions.
-	-1 indicates walls or out-of-bound areas.
-	0 indicates clean areas with no dirt.

Example Input File:
Here is an example of how the input file might look:
2,3
50
200
5  -1  -1  -1  -1  -1
0  -1   0  -1   5   5
0  -1  -1  -1   0   1
2   5   3   4   0   6

Explanation of the Output format:

The output file generated by the program contains detailed information about the vacuum cleaner's operation during the simulation. The format is structured as follows:

1. "Steps Performed by the Vacuum Cleaner: " + all the steps that the vacuum performed  : this section lists each movement the vacuum cleaner made in the order they were performed. The movements are represented by direction keywords (UP, DOWN, LEFT, RIGHT, STAY).
    for example:
         Steps performed by the vacuum cleaner: UP, STAY, STAY, STAY, STAY, STAY, DOWN

2. "Total Number of Steps Performed:" + int : indicates the total count of movements the vacuum cleaner made during the simulation.
    for example:
        Total number of steps performed: 100

3. "Amount of Dirt Left in the House:" + int : Shows the remaining dirt level in the house after the vacuum cleaner has completed its run.
    for example: 
        Amount of dirt left in the house: 0

4. "Is the vacuum cleaner dead (battery exhausted):" + "Yes"/"No" : Indicates whether the vacuum cleaner's battery has been exhausted by the end of the simulation.
    for example:
        Is the vacuum cleaner dead (battery exhausted): Yes
5. "Is the mission succeeded: " + "Yes"/"No" : Shows whether the cleaning mission was successful, which means all the dirt was cleaned and the vacuum returned to the docking station.
    for example: 
        Is the mission succeeded: Yes 

Algorithm:

The algorithm decides the next step randomly, ensuring the chosen direction is free of walls and the vacuum cleaner has enough battery to proceed, which means the vacuum cleaner continues cleaning as long as the battery level is greater than the number of blocks visited. For example, if the vacuum has visited 10 blocks, it will only continue cleaning if the battery level is more than 10; otherwise, it returns to the docking station to recharge(fully), while the get back step is chosen from the stack that we saved. (the stack has all the directions, without stay- which means the vacuum moved from one block to another).
At the docking station, we check if the mission is complete. If the mission is complete, we return the appropriate outputs; otherwise, we continue cleaning the house after fully recharging while tha vacuum did not reach the maximum number of steps.

Running the Program:
there is 2 ways:
  a.  in line 29 write the "input_FileName.txt" name that you want to run, and then:
      1. write "make"
      2. write "make run"
      you will see an output file with the format: "out_inout_FileName.txt"
  
  b. 
    1. write : g++ -o myrobot Algorithm.cpp Direction.cpp House.cpp Simulator.cpp Vacuum.cpp
    2. write : ./myrobot input_FileName.txt   
    you will see an output file with the format: "out_inout_FileName.txt"



