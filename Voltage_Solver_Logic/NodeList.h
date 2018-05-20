/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NodeList.h
 * Author: mittala6
 *
 * Created on November 9, 2017, 1:50 PM
 */

#ifndef NODELIST_H
#define NODELIST_H

#include "Node.h"
#include "Resistor.h"

class NodeList {
private:
    Node *head; //head of Node List  

public:
    //constructor
    NodeList();
    
    //destructor
    ~NodeList();
    
    //finds node based on specified id
    Node *findNode(int id);
    
    //inserts node based on node id
    //inserts in ascending order of node id 
    Node *findOrInsertNode(int id); 
    
    //looks for resistor with the specified label
    //returns pointer to resistor, else returns null
    Resistor *findResistor(string label); 
    
    //prints entire node list
    void printEntireList();
    
    //modifyResistance
    void modifyResistance(string label, double resistance); 
    
    //delete 1 resistor
    void deleteResistor(string label); 
    
    //delete all resistors in the network
    void deleteAllResistors();
    
    //solves all node voltages
    void solveNodeVoltages(); 
    
    //print Node Voltages
    void printNodeVoltages();
    
    //checks if setV has been called
    bool setValueExist();
    
    int numberOfunSet();
    
    void setVoltTo0();
    
    void unsetAll();
};

#endif /* NODELIST_H */

