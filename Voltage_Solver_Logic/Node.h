/* 
 * File:   Node.h
 * Author: JC and VB
 * Author: TSA
 *
 * Updated on August 24, 2016, 01:40 PM
 * Created on October 6, 2013, 12:58 PM
 */

#ifndef NODE_H
#define NODE_H

#define MAX_RESISTORS_PER_NODE 5

#include <string>
#include <iostream>
#include <iomanip>
#include "ResistorList.h"

using namespace std;

class Node
{
private:
    
    int ID = 0; // ID of current node
    double voltage = 0;
    bool setV = false;
    ResistorList list; //Contains head of Resistor List
    Node *next = NULL; //pointer to next node
    
public:
   Node(); 
   ~Node();
   
   //create new node with the specified ID
   Node(int ID_); 
   
   //insert Resistor at the specified nodes
   void insertResistor(string name_,double resistance_,int endpoints_[2]);
   
   //set voltage
   void setVoltage(double voltage_);
   
   void unSetVoltage();
   
   void changeVoltage(double voltage_);
   
   //prints entire node list
   void printResistorList ();
   
   friend class NodeList; 

};

#endif	/* NODE_H */

