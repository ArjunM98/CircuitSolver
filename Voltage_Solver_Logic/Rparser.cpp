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
#include "ResistorList.h"
#include "NodeList.h"
#include <iomanip>

using namespace std;


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
int insertR(stringstream &line, NodeList &list){
    
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
    
    //check for exisitng resistor name
    if(list.findResistor(name) != NULL){ 
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
        
        //checks to see if the nodes exist returning a pointer
        //if the node does not exist, insert and return a pointer
        Node *node1 = list.findOrInsertNode(nodeId1); 
        Node *node2 = list.findOrInsertNode(nodeId2); 
        
        //inserts Resistor at both the specified nodes
        node1->insertResistor(name, resistance, nodeArr); 
        node2->insertResistor(name, resistance, nodeArr);

        cout << "Inserted: resistor " << name << " " << resistance << " Ohms " << nodeId1 << " -> " << nodeId2 << endl; 
        return(0);
    }
    
}

//printR function
int printR(stringstream &line, NodeList &list){
    
    //declaration of arguments 
    string name; 
    int posRes = 0; //pos of Resistor in array
    char c; //empty char to skip white space and check for too many arguments 

    //Parses first input
    //first input should be name of resistor 
    line >> name; 
    
    //checks if name exists
    if(list.findResistor(name) == NULL){ 
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
    
    cout << "Print: " << endl; 
    Resistor *printRes = list.findResistor(name);
    printRes->print(); 
    return(0); 

}

//printNODE function
int printNode(stringstream &line, NodeList &list){
    
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
    //failed - output error
    else {
        cout << "Error: too few arguments" << endl; 
        return(0); 
    }
    
    //Parses first input
    //first input should be all of type string or name of type int
    //check for name first of type int
    line >> nodeID; 
    
    //value is present, but parse still fails 
    //check if it is the word all 
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
       
        //correct input 1 : input = all
        else {
            cout << "Print: " << endl; 
            
            //prints entire node list with all the resistors
            list.printEntireList();
            
            return(0);
        }
    }
    
    else if (!nextEmptyChar(line)){ 
        cout << "Error: invalid argument" << endl;
        return(0);
    }
    
    //should return eof, otherwise there are too many arguments 
    line >> c1; 
    
    //too many arguments, as c did not return eof
    if (!line.eof()){ 
        cout << "Error: too many arguments" << endl; 
        return(0);
    }
    
    //correct input 2
    else {
        cout << "Print: " << endl; 
        
        Node *printNode = list.findNode(nodeID); 
        if(printNode != NULL){
            printNode->printResistorList();
        }
        
        return (0);

    }
      
}

//modifyR function
int modifyR(stringstream &line, NodeList &list){
    
    //declaration of arguments 
    string name; 
    double resistance = 0; 
    double oldResistance = 0; 
    int posRes = 0; //position of resistor to be modified
    char c; //empty char to skip white space and check for too many arguments 
    
    //Parses first input
    //first input should be name of resistor 
    line >> name; 
    
    if(list.findResistor(name) == NULL){ 
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
        
        oldResistance = list.findResistor(name)->getResistance(); 
        list.modifyResistance(name, resistance);
        
        cout << "Modified: resistor " << name << " from " << oldResistance << " Ohms to " << resistance << " Ohms" << endl; 
        return(0);
    }
    
}

//deleteR function
int deleteR(stringstream &line, NodeList &list){
    
     //declaration of arguments 
    string name; 
    char c; //empty char to skip white space and check for too many arguments 

    //Parses first input
    //first input should be name of resistor 
    line >> name; 
    
    if((name != "all") && (list.findResistor(name) == NULL)){ 
        cout << "Error: resistor " << name << " not found" << endl; 
        return (0);
    }
    
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
        list.deleteAllResistors();
        list.unsetAll();
        cout << "Deleted: all resistors " << endl; 
        return(0);
    }
    else { 
        list.deleteResistor(name);
        cout << "Deleted: resistor " << name << endl;
        return(0); 
    }
    
}

//setV function
int setV(stringstream &line, NodeList &list){ 
    
    int NodeId; 
    double voltage;
     
    //Parses first input
    //first input should be name of node 
    line >> NodeId; 
    
    //Parses second input
    //second input should be voltage of node
    line >> voltage; 
    
    Node *setVol = list.findNode(NodeId);
    
    if(setVol == NULL){ 
        cout << "Error: node " << NodeId << " not found" << endl; 
        return (0);
    }
    
    setVol->setVoltage(voltage);
    cout << "Set: node " << NodeId << " to " << voltage << " Volts" << endl; 
    return(0);
    
}

//unsetV function
int unsetV(stringstream &line, NodeList &list){ 
    
    int NodeId; 
     
    //Parses first input
    //first input should be name of node 
    line >> NodeId; 
    
    Node *unsetVol = list.findNode(NodeId);
    
    if(unsetVol == NULL){ 
        cout << "Error: node " << NodeId << " not found" << endl; 
        return (0);
    }
    
    unsetVol->unSetVoltage();
    cout << "Unset: the solver will determine the voltage of node " << NodeId << endl;  
    return(0);
    
}

//solve function
int solve(NodeList &list){ 
    
    if(list.setValueExist() == false){
        cout << "Error: no nodes have their voltage set" << endl;
    }
    else {
        cout << "Solve: " << endl;
        list.solveNodeVoltages();
        list.printNodeVoltages();
    }
}