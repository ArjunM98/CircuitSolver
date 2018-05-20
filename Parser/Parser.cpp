/* 
 * File:   parser.cpp
 * Author: mittala6
 *
 * Created on October 5, 2017, 5:16 PM
 */

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;

//Constant Defintions 
#define MINIMUM_NODE_VALUE 0
#define MAXIMUM_NODE_VALUE 5000

//Function prototypes
int insertR(stringstream &line);
int modifyR(stringstream &line);
int printR(stringstream &line);
int printNode(stringstream &line);
int deleteR(stringstream &line);

bool keywordAll (string name);
bool typeCheck (stringstream &line); 
bool nextEmptyChar (stringstream &line);
bool negativeResistance (double value); 
bool outOfRange (int value); 
bool repeatNode (int value1, int value2); 

//checks if the value of name is all 
//invalid input of all
bool keywordAll (string name) { 
    
    if (name == "all" || name == "All") { 
        cout << "Error: resistor name cannot be the keyword \"all\"" << endl;
        return true; 
    }
    else { 
        return false; 
    }
}

//checks if the value right after the input parsed is an empty space 
//if empty, the current value is of the right type
bool nextEmptyChar(stringstream &line){ 
    if (line.peek() == 32 || line.peek() == 9 || line.peek() == EOF){ 
        return true; 
    }
    else { 
        return false; 
    }
}

//checks if value parsed is equivalent to the value expected 
bool typeCheck (stringstream &line){
    
    //if parse failed, values don't match
    if(line.fail()){ 
        return false; 
    }
    else {
        //checks if the next char is an empty space
        if (nextEmptyChar(line)) { 
            return true;
        }
        //parse failed cause the next character is of opposite type of the expected value 
        else { 
            return false; 
        }
    }    
}

//checks to see if resistance value is negative 
bool negativeResistance (double value){ 
    
    if (value >= 0){ 
        return false; 
    }
    else { 
        return true; 
    } 
}

bool outOfRange (int value){ 
    
    if ((value >= MINIMUM_NODE_VALUE) && (value <= MAXIMUM_NODE_VALUE)){ 
        return false; 
    }
    else { 
        return true; 
    }  
}

bool repeatNode (int value1, int value2){ 
    
    if (value1 == value2){
        return true;
    }
    else{ 
        return false; 
    }
    
}

//insertR function
int insertR(stringstream &line){
    
    //declaration of arguments 
    string name; 
    int nodeId1 = 0, nodeId2 = 0; 
    double resistance = 0; 
    char c; //empty char to skip white space and check for too many arguments 
    
    //Parses first input
    //first input should be name of resistor 
    line >> name; 
    
    //checks to see a value was saved to name (too few parameters) 
    if (line.fail()) { 
        cout << "Error: too few arguments" << endl; 
        return (0); 
    }
    
    //checks for all argument in name
    else if (keywordAll(name)) { 
        return (0);
    } 
    
    //Parses second input
    //second input should be value of resistance  
    line >> resistance; 
    
    //Checks for missing resistance value
    if (line.fail() && line.eof()) {       
        cout << "Error: too few arguments" << endl; 
        return(0); 
    }
    
    //checks if the type of argument corresponds to the expected double input 
    else if (!typeCheck(line)) { 
        cout << "Error: invalid argument" << endl; 
        return(0);
    }
    
    //checks if the resistance is negative 
    else if (negativeResistance(resistance)){ 
        cout << "Error: negative resistance" << endl; 
        return(0); 
    }
    
    //Parses third input
    //third input should be value of node1  
    line >> nodeId1; 
    
    //Checks for missing node1 value
    if (line.fail() && line.eof()) {
        cout << "Error: too few arguments" << endl; 
        return(0); 
    }
    
    //checks if the type of argument corresponds to the expected integer input 
    else if (!typeCheck(line)) { 
        cout << "Error: invalid argument" << endl; 
        return(0);
    }
    
    //checks if nodeId1 is out of range
    else if (outOfRange(nodeId1)){ 
        cout << "Error: node " << nodeId1 << " is out of permitted range " << MINIMUM_NODE_VALUE << "-" << MAXIMUM_NODE_VALUE << endl; 
        return (0); 
    }
    
    //Parses fourth input
    //fourth input should be value of node1  
    line >> nodeId2; 
    
    //Checks for missing node2 value
    if (line.fail() && line.eof()) {
        cout << "Error: too few arguments" << endl; 
        return(0); 
    }
    
    //checks if the type of argument corresponds to the expected integer input 
    else if (!typeCheck(line)) { 
        cout << "Error: invalid argument" << endl; 
        return(0);
    }
    
    //checks if nodeId2 is out of range
    else if (outOfRange(nodeId2)){ 
        cout << "Error: node " << nodeId2 << " is out of permitted range " << MINIMUM_NODE_VALUE << "-" << MAXIMUM_NODE_VALUE << endl; 
        return (0); 
    }
       
    //checks for keyword "all"
    else if (keywordAll(name)) { 
        return (0);
    }
    
    //checks for a repeated node
    else if(repeatNode(nodeId1, nodeId2)){
        cout << "Error: both terminals of resistor connect to node " << nodeId1 << endl; 
        return (0); 
    }
    
    //Parses fifth input
    //should return eof, otherwise there are too many arguments 
    line >> c; 
    
    //checks if there are more arguments after the theoretical last argument, otherwise prints correct statement of input 
    if (!line.eof()){ 
        cout << "Error: too many arguments" << endl; 
        return(0);
    }
    else { 
        cout << "Inserted: resistor " << name << " " << resistance << " Ohms " << nodeId1 << " -> " << nodeId2 << endl;
        return(0);
    }
    
}

//modifyR function
int modifyR(stringstream &line){
    
    //declaration of arguments 
    string name; 
    double resistance = 0; 
    char c; //empty char to skip white space and check for too many arguments 
    
    //Parses first input
    //first input should be name of resistor 
    line >> name; 
    
    //checks to see a value was saved to name (too few parameters) 
    if (line.fail()) { 
        cout << "Error: too few arguments" << endl; 
        return (0); 
    }
    
    //checks for all argument in name
    else if (keywordAll(name)) { 
        return (0);
    } 
    
    //Parses second input
    //second input should be value of resistance  
    line >> resistance; 
    
    //Checks for missing resistance value
    if (line.fail() && line.eof()) {       
        cout << "Error: too few arguments" << endl; 
        return(0); 
    }
    
    //checks if the type of argument corresponds to the expected double input 
    else if (!typeCheck(line)) { 
        cout << "Error: invalid argument" << endl; 
        return(0);
    }
    
    //checks if the resistance is negative 
    else if (negativeResistance(resistance)){ 
        cout << "Error: negative resistance" << endl; 
        return(0); 
    }
    
    //Parses fifth input
    //should return eof, otherwise there are too many arguments 
    line >> c; 
    
    //checks if there are extra arguments, or prints the correct result 
    if (!line.eof()){ 
        cout << "Error: too many arguments" << endl; 
        return(0);
    }
    else { 
        cout << "Modified: resistor " << name << " to " << resistance << " Ohms " << endl; 
        return(0);
    }
    
}

//deleteR function
int deleteR(stringstream &line){
    
     //declaration of arguments 
    string name; 
    char c; //empty char to skip white space and check for too many arguments 

    
    //Parses first input
    //first input should be name of resistor 
    line >> name; 
    
    //checks to see a value was saved to name (too few parameters) 
    if (line.fail()) { 
        cout << "Error: too few arguments" << endl; 
        return (0); 
    }
    
    //Parses fifth input
    //should return eof, otherwise there are too many arguments 
    line >> c; 
    
    //checks if there are extra arguments,
    if (!line.eof()){ 
        cout << "Error: too many arguments" << endl; 
        return(0);
    }

    //outputs the result
    if(name == "all"){ 
        cout << "Deleted: all resistors " << endl; 
        return(0);
    }
    else { 
        cout << "Deleted: resistor " << name << endl;
        return(0); 
    }
    
}

//printR function
int printR(stringstream &line){
    
    //declaration of arguments 
    string name; 
    char c; //empty char to skip white space and check for too many arguments 

    //Parses first input
    //first input should be name of resistor 
    line >> name; 
    
    //checks to see a value was saved to name (too few parameters) 
    if (line.fail()) { 
        cout << "Error: too few arguments" << endl; 
        return (0); 
    }
    
    //Parses fifth input
    //should return eof, otherwise there are too many arguments 
    line >> c; 
    
    //checks if there are extra arguments,
    if (!line.eof()){ 
        cout << "Error: too many arguments" << endl; 
        return(0);
    }

    //outputs the result
    if(name == "all"){ 
        cout << "Print: all resistors " << endl; 
        return(0);
    }
    else { 
        cout << "Print: resistor " << name << endl;
        return(0); 
    }
}

//printNODE function
int printNode(stringstream &line){
    
    //declaration of arguments 
    int nodeID; 
    string node; 
    char c, c1; //empty char to skip white space and check for too many arguments 
    
    //Parses first input
    line >> c; 
    
    //checks if its empty
    if (!line.fail()){ 
        line.putback(c);
    }
    else {
        cout << "Error: too few arguments" << endl; 
        return(0); 
    }
    
    //Parses first input
    //first input should be all or name
    line >> nodeID; 
    
    //value is present, but parse still fails 
    if (line.fail()){ 
        
        //clear flags 
        line.clear();
        //parse into string variable 
        line >> node; 
        
        //fails again = value is present but of wrong type
        if(line.fail()){ 
            cout << "Error: invalid argument" << endl; 
            return(0);
        }
        
        //should return eof, otherwise there are too many arguments 
        line >> c1; 
        
        //value does not equal all
        if (node != "all"){ 
            cout << "Error: invalid argument" << endl; 
            return(0);
        }
        
        //too many arguments, as c did not return eof
        else if (!line.eof()){ 
            cout << "Error: too many arguments" << endl; 
            return(0);
        }
       
        //correct input 1
        else {
            cout << "Print: all nodes" << endl; 
            return(0);
        }
    }
    else if (!nextEmptyChar(line)){ 
        cout << "Error: invalid argument" << endl;
        return(0);
    }
    
    //should return eof, otherwise there are too many arguments 
    line >> c1; 
    
    if (outOfRange(nodeID)){ 
        cout << "Error: node " << nodeID << " is out of permitted range " << MINIMUM_NODE_VALUE << "-" << MAXIMUM_NODE_VALUE << endl; 
        return (0); 
    }
    
    //too many arguments, as c did not return eof
    else if (!line.eof()){ 
        cout << "Error: too many arguments" << endl; 
        return(0);
    }
    
    //correct input 2
    else { 
        cout << "Print: node " << nodeID << endl;
        return (0);
    }
      
}

/*
 * Main Parser Function 
 */
int main() {
    
    string line, command;
    std::cout << std::fixed; 
    std::cout << setprecision(2); 
    
    //Output ready for user commands: 
    cout << "> "; 
    
    getline (cin, line); // Get a line from standard input
    
    while ( !cin.eof () ) {
        
        // Put the line in a stringstream for parsing
        // Making a new stringstream for each line so flags etc. are in a known state
        stringstream lineStream (line);
        
        //Parses first word to determine command
        lineStream >> command;
        
        //Analyzes Command 
        if (command == "insertR") {
            // parse an insertR command
            insertR(lineStream); 
        }
        else if (command == "modifyR") {
            //parse a modifyR command
            modifyR(lineStream);
        }
        else if (command == "deleteR") {
            //parse a deleteR command 
            deleteR(lineStream);
        }
        else if (command == "printR") {
            //parse a printR command
            printR(lineStream);
        }
        else if (command == "printNode") {
            //parse a printNode command
            printNode(lineStream);
        }
        else {
            cout << "Error: invalid command" << endl; 
        }
        
        //reset command string
        command = ""; 
        
        //ready for new user input 
        cout << "> "; 
        
        //Get new input line after analysis
        getline (cin, line);
        
    } // End input loop until EOF.
    
    return 0;
}