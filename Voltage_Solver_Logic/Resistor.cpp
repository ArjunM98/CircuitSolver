/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Resistor.cpp
 * Author: mittala6
 * 
 * Created on October 16, 2017, 11:31 PM
 */

#include "Resistor.h"

using namespace std;

Resistor :: Resistor() { 
    //nothing
}

Resistor :: ~Resistor() { 
    //nothing
}

Resistor :: Resistor(string name_,double resistance_,int endpoints_[2]) { 
    
    resistance = resistance_; 
    name = name_; 
    for(int i = 0; i < 2; i++){ 
        endpointNodeIDs[i] = endpoints_[i]; 
    }
    next = NULL;
    
}

string Resistor :: getName() const{ 
    
    return name; 
    
}

double Resistor :: getResistance() const{ 
    
    return resistance; 
    
}

void Resistor :: setResistance (double resistance_){
    
    resistance = resistance_;
    
}

void Resistor :: print(){ 
    
    cout << left << setw(20) << name << " " << right << setw(8) << setprecision(2) << resistance << " Ohms ";
    cout << endpointNodeIDs[0] << " -> " << endpointNodeIDs[1] << endl;
    
}

int Resistor ::get2ndEndPoint(){ 
    
    return endpointNodeIDs[1];
    
}

int Resistor ::get1stEndPoint(){ 
    
    return endpointNodeIDs[0];
    
}

Resistor *Resistor::getNext(){ 
    return next; 
}