/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Node.cpp
 * Author: mittala6
 * 
 * Created on October 16, 2017, 11:31 PM
 */

#include "Node.h"

using namespace std;

Node :: Node (){ 
    //nothing
}

Node :: ~Node (){ 
    //nothing   
}

//set value of node to specified ID
Node :: Node (int ID_){ 
    
    ID = ID_; 
    next = NULL; 
}

//inserts Resistor at the end of resistor list
void Node::insertResistor(string name_, double resistance_, int endpoints_[2]){ 
    list.insertResistor(name_, resistance_, endpoints_);
}

void Node::printResistorList(){ 
    
    int numberOfResistors = 0; 
    numberOfResistors = list.getNumberOfResistors(); 
    
    if(numberOfResistors != 0){
        cout << "Connections at node " << ID << ": " << numberOfResistors << " resistor(s)" << endl;
        list.printResistors();
    } 
    
}

void Node::setVoltage(double voltage_){ 
    voltage = voltage_; 
    setV = true; 
}

void Node::unSetVoltage(){ 
    voltage = 0; 
    setV = false; 
}

void Node::changeVoltage(double voltage_){
    voltage = voltage_;
}