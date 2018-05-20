/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ResistorList.cpp
 * Author: mittala6
 * 
 * Created on November 9, 2017, 1:50 PM
 */

#include "ResistorList.h"

ResistorList::ResistorList() {
    head = NULL; 
}

ResistorList::~ResistorList(){
    
    Resistor *current;
    while(head != NULL){ 
        current = head; 
        head = current->next; 
        delete current; 
    }
}

Resistor *ResistorList::findResistor(string label){
    
    //traverses list, starting from head
    //Note: ResistorList class is a friend of Resistor class
    for(Resistor *current = head; current != NULL; current=current->next){ 
        
        if(current->name == label){ 
            //returns pointer to resistor if found
            return current;
        }
    }
    
    //if not found it returns null
    return NULL; 
}

Resistor *ResistorList::getHead(){ 
    return head; 
}

void ResistorList::insertResistor(string name_, double resistance_, int endpoints_[2]){ 
    
    //create new resistor to insert
    Resistor *newResistor = new Resistor(name_, resistance_, endpoints_);
    //create pointer to keep track of where you are in the list
    Resistor *current = head; 
    //create a pointer to keep track of the previous node
    Resistor *previous = NULL; 
    
    while(current != NULL){ 
        //set previous pointer to current pointer
        previous = current; 
        //increment current pointer
        current = current->next;
    }
        //exits when current pointer is null
        //set newResistor next pointer to current
        //if list is empty, or if the end of the list was reached, next would be NULL
        //otherwise, next is set to the appropriate next node based on while loop from above
        newResistor->next = current; 
        if(previous == NULL){ //indication the list was empty and set the value of head to the new node
            head = newResistor; 
        }   
        else{ //otherwise insert in appropriate portion of the list
            previous->next = newResistor; 
        }
    
}

//prints entire of resistor list
void ResistorList::printResistors(){ 
    
    //create pointer to keep track of where you are in the list
    Resistor *current = head; 
    
    //prints resistor, and increments current pointer until the end of the resistor list is reached
    while(current != NULL){ 
        //inserts space before printing resistor information 
        //for printNode function
        cout << " ";
        current->print(); 
        current = current->next; 
    }
    
}

int ResistorList::getNumberOfResistors(){ 
    
    //create pointer to keep track of where you are in the list
    Resistor *current = head; 
    //counter to keep track of the number of resistors
    int counter = 0; 
    
    while(current != NULL){ 
        counter += 1; 
        current = current->next;
    }
    
    return counter; 
    
}

bool ResistorList::deleteResistor(string label){ 
    
    //pointer to keep track of place in the list
    Resistor *current = head;
    //pointer to keep track of the previous node in the list
    Resistor *previous = NULL; 
    
    while((current != NULL) && (current->getName() != label)){
        previous = current; 
        current = current->next; 
    }
    //resistor was not in the list 
    if(current == NULL){ 
        return false; 
    }
    //only 1 item connected to head
    if(previous == NULL){ 
        head = current->next; 
    }
    //set previous value of next to the next value of the resistor getting deleted
    else{
        previous->next = current->next; 
    }
    delete current; 
    return true; 
    
}

void ResistorList::deleteResistorList(){
    
    Resistor *current;
    while(head != NULL){ 
        current = head; 
        head = current->next; 
        delete current; 
    }
}

double ResistorList::sumOfResistors(){ 
    
    double sum = 0.0; //final answer
    double denominatorVoltage = 0.0; //intermediate calculation
    //holding temporary values
    double Ra = 0.0; 
    
    //pointer to keep track of place in list
    Resistor *current = head; 
    
    //checks to see if lust is empty 
    if(head == NULL){
        return 0.0; 
    }
    
    while(current != NULL){ 
        Ra = current->getResistance(); 
        denominatorVoltage = denominatorVoltage + (1/Ra); 
        current = current->next; 
    }
    
    //exits if end of list has been reached 
    sum = (1/denominatorVoltage); 
    
    return sum;
    
}
