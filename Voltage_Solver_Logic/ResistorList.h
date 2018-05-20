/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ResistorList.h
 * Author: mittala6
 *
 * Created on November 9, 2017, 1:50 PM
 */

#ifndef RESISTORLIST_H
#define RESISTORLIST_H

#include "Resistor.h"

class ResistorList {
private:
    
    Resistor *head; //head of resistor list
    
public:
    ResistorList();
    ~ResistorList();
    
    //return a pointer to the resistor with name = label
    //if not found return null
    Resistor *findResistor(string label);
    
    //inserts resistor at the end of the list
    void insertResistor(string name_,double resistance_,int endpoints_[2]);
    
    //Prints entire resistor list 
    void printResistors();
    
    //returns the number of resistors in the list currently
    int getNumberOfResistors();
    
    //returns true if deleted
    //else returns false
    bool deleteResistor(string label);
    
    //deletes Entire List
    void deleteResistorList();
    
    //calculates part a) of equation given in lab
    double sumOfResistors();
    
    //
    Resistor *getHead();
};

#endif /* RESISTORLIST_H */

