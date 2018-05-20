/* 
 * File:   Node.h
 * Author: JC and VB
 * Author: TSA
 *
 * Updated on August 24, 2016, 01:40 PM
 * Created on October 6, 2013, 12:58 PM
 */

#ifndef RESISTOR_H
#define RESISTOR_H

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

class Resistor
{
private:
   string name; // C++ string holding the label
   double resistance=0.0; // resistance (in Ohms)
   int endpointNodeIDs[2]; // IDs of nodes it attaches to
   Resistor *next; //pointer to next resistor node

public:
    Resistor();
   // empty constructor

   Resistor(string name_,double resistance_,int endpoints_[2]);
   // rIndex_ is the index of this resistor in the resistor array
   // endpoints_ holds the node indices to which this resistor connects

   //destructor
   ~Resistor(); 
   
   //returns name
   string getName() const; // returns the name
   
   //returns resistance
   double getResistance() const; // returns the resistance

   //sets the resistance to specific value
   void setResistance (double resistance_);

   // you *may* create either of the below to print your resistor
   void print ();
   
   //returns 2nd endpoint
   int get2ndEndPoint();
      
   //returns 2nd endpoint
   int get1stEndPoint();
   
   Resistor *getNext();
   
   friend class ResistorList; 
};

#endif	/* RESISTOR_H */

