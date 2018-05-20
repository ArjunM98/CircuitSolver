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

bool Node :: canAddResistor(int rIndex){ 
    
    if (numRes >= MAX_RESISTORS_PER_NODE){
        return false; 
    }
    else{ 
        return true; 
    }
}

void Node :: addResistor(int rIndex){ 
    resIDArray[numRes] = rIndex; 
    numRes += 1; 
}

void Node :: print (int nodeIndex){
    
    cout << "Connections at node " << nodeIndex << ": " << numRes << " resistor(s)" << endl; 
   
}

int Node :: getResIDArray(int index) const{ 
    
    return resIDArray[index]; 
    
}

int Node :: numResConnected() const {
    
    return numRes; 
    
}