/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Rparser.cpp
 * Author: mittala6
 * 
 * Created on October 16, 2017, 9:57 PM
 */

#include "Rparser.h"
#include "Node.h"
#include "Resistor.h"
#include <iomanip>

using namespace std;

//Global Variables
int maxNode; 
int maxResistor; 

int resCount = 0; 

Resistor **resArray; 
Node **nodeArray; 


//checks if nodeId is full
bool nodeIsFull(int nodeId1, int nodeId2){ 
    if((nodeArray[nodeId1]->canAddResistor(nodeId1)) && (nodeArray[nodeId2]->canAddResistor(nodeId2))){
        return false;
    }
    else{ 
        return true; 
    }
}

//checks if there is an existing resistor with the same name
bool exisitingResistorName(string name){ 
    
    for(int i = 0; i < resCount; i++){ 
        if (resArray[i]->getName() == name){ 
            return true; 
        }
    }
    return false; 
    
}

//returns the index of resArray, where name of specified resistor is equal to resArray index
int resPos(string name){ 
    
    int posRes = 0; //position of res in resArray
    
    //increments resPos, until index of specified resistor is found
    while((resArray[posRes]->getName() != name) && (posRes < resCount)){
        posRes += 1; 
    }
    
    return posRes; 
    
}

//delete array
void deleteArrays(){ 
    
    //Delete each object the pointer is pointing to
    //Assign the value of pointer to Null
    delete [] resArray;
    resArray = NULL;
    //Prevent Dangling Pointer
    
    //reset resCount
    resCount = 0; 
    
    //Delete each object the pointer is pointing to
    //Assign the value of pointer to Null
    delete [] nodeArray; 
    //Prevent Dangling Pointer
    nodeArray = NULL; 
    
}

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
    
    //checks to see if the next char is empty 
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

//checks if the node values are in the specified node range
bool outOfRange (int value){ 
    
    if ((value >= MINIMUM_NODE_VALUE) && (value <= maxNode)){ 
        return false; 
    }
    else { 
        return true; 
    }  
}

//checks for repeat node
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
    int nodeArr[2];
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
        cout << "Error: node " << nodeId1 << " is out of permitted range " << MINIMUM_NODE_VALUE << "-" << maxNode << endl; 
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
        cout << "Error: node " << nodeId2 << " is out of permitted range " << MINIMUM_NODE_VALUE << "-" << maxNode << endl; 
        return (0); 
    }
    
    //checks if resistor array is full
    if(resCount >= (maxResistor)){ 
        cout << "Error: resistor array is full" << endl;
        return(0);
    }
    
    //check is node is full
    if(nodeIsFull(nodeId1, nodeId2)){
        cout << "Error: node is full" << endl; 
        return(0);
    }
    
    //check for exisitng resistor name
    if(exisitingResistorName(name)){ 
        cout << "Error: resistor " << name << " already exists" << endl; 
        return(0);
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
        //save node values to local node Array for current resistor
        nodeArr[0] = nodeId1; 
        nodeArr[1] = nodeId2; 
        //instantiate resistor and set value
        resArray[resCount] = new Resistor(resCount,name,resistance,nodeArr);
        //update node value
        nodeArray[nodeId1]->addResistor(resCount);
        nodeArray[nodeId2]->addResistor(resCount);
        
        //increment resCount
        resCount += 1;

        cout << "Inserted: resistor " << name << " " << resistance << " Ohms " << nodeId1 << " -> " << nodeId2 << endl; 
        return(0);
    }
    
}

//modifyR function
int modifyR(stringstream &line){
    
    //declaration of arguments 
    string name; 
    double resistance = 0; 
    double oldResistance = 0; 
    int posRes = 0; //position of resistor to be modified
    char c; //empty char to skip white space and check for too many arguments 
    
    //Parses first input
    //first input should be name of resistor 
    line >> name; 
    
    if(!exisitingResistorName(name)){ 
        cout << "Error: resistor " << name << " not found" << endl; 
        return (0);
    }
    
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
    //should return eof, otherwise there are too many arguments 
    line >> c; 
    
    //checks if there are extra arguments, or prints the correct result 
    if (!line.eof()){ 
        cout << "Error: too many arguments" << endl; 
        return(0);
    }
    else {
        posRes = resPos(name); //index of resArray where resistor is stored
        oldResistance = resArray[posRes]->getResistance(); //gets old resistance
        resArray[posRes]->setResistance(resistance);
        
        cout << "Modified: resistor " << name << " from " << oldResistance << " Ohms to " << resistance << " Ohms" << endl; 
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
        //delete everything
        deleteArrays();
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
    int posRes = 0; //pos of Resistor in array
    char c; //empty char to skip white space and check for too many arguments 

    //Parses first input
    //first input should be name of resistor 
    line >> name; 
    
    //checks if name exists
    if((name != "all") && (!exisitingResistorName(name))){ 
        cout << "Error: resistor " << name << " not found" << endl; 
        return (0);
    }
    
    //checks to see a value was saved to name (too few parameters) 
    if (line.fail()) { 
        cout << "Error: too few arguments" << endl; 
        return (0); 
    }
    
    //Parses second input
    //should return eof, otherwise there are too many arguments 
    line >> c; 
    
    //checks if there are extra arguments,
    if (!line.eof()){ 
        cout << "Error: too many arguments" << endl; 
        return(0);
    }

    //outputs the result
    if(name == "all"){
        cout << "Print: " << endl; 
        for(int i = 0; i < resCount; i++){ 
            resArray[i]->print();
        }
        return(0);
    }
    else {
        cout << "Print: " << endl;         
        posRes = resPos(name);
        resArray[posRes]->print(); 
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
            cout << "Print: " << endl; 
            for(int i = 0; i <= maxNode; i++){ 
                //prints first line
                nodeArray[i]->print(i);
                
                //prints resistors in the node
                 for(int j = 0; j < (nodeArray[i]->numResConnected()); j++){
                    cout << "  ";
                    resArray[nodeArray[i]->getResIDArray(j)]->print();
                }
            }
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
        cout << "Error: node " << nodeID << " is out of permitted range " << MINIMUM_NODE_VALUE << "-" << maxNode << endl; 
        return (0); 
    }
    
    //too many arguments, as c did not return eof
    else if (!line.eof()){ 
        cout << "Error: too many arguments" << endl; 
        return(0);
    }
    
    //correct input 2
    else {
        cout << "Print: " << endl; 
        //prints first line
        nodeArray[nodeID]->print(nodeID);

        //prints resistors in the node
        for(int i = 0; i < (nodeArray[nodeID]->numResConnected()); i++){
            cout << "  ";
            resArray[nodeArray[nodeID]->getResIDArray(i)]->print();
        }
        
        return (0);

    }
      
}

void maxVal(stringstream &line, bool alreadyCalled){
   
    //declaration of arguments 
    int maxNodeNumber; 
    int maxResistors; 
    
    //Parses first input
    line >> maxNodeNumber;
    //Parses second input
    line >> maxResistors;
    
    //checks to see if maxVal has already been called 
    if ((alreadyCalled) && (maxNodeNumber > 0) && (maxResistors > 0)){ 
        deleteArrays(); 
    }
    
    //Checks if the value of maxNodeNumber and maxResistors are greater than 0
    if((maxNodeNumber > 0) && (maxResistors > 0)){ 
        cout << "New network: max node number is " << maxNodeNumber << "; max resistors is " << maxResistors << endl; 
        
        //Assign to Global Variable 
        maxNode = maxNodeNumber; 
        maxResistor = maxResistors; 
        
        //dynamically allocate arrays for number of nodes and arrays
        resArray = new Resistor* [maxResistor]; 
        nodeArray = new Node* [maxNodeNumber];
        
        //instantiate all node pointers to objects 
        for(int i = 0; i <= maxNode; i++){ 
            nodeArray[i] = new Node;
        }
    }
    else {
        cout << "Error: maxVal arguments must be greater than 0" << endl; 
    }
}