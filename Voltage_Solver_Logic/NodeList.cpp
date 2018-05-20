/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NodeList.cpp
 * Author: mittala6
 * 
 * Created on November 9, 2017, 1:50 PM
 */

#include "NodeList.h"
#include "ResistorList.h"
#include <cmath>
#define MIN_ITERATION_VALUE 0.0001

NodeList::NodeList(){
    head = NULL; 
}

NodeList::~NodeList(){
    
    //create pointer to keep track of where you are in the list
    Node *current;
    while(head != NULL){ 
        current = head; 
        head = current->next; 
        delete current; 
    }
    
}

Node *NodeList::findNode(int id){ 
    
    //traverses list, starting from head
    //Note: NodeList class is a friend of Node class
    for(Node *current = head; current != NULL; current = current->next){ 
        if(current->ID == id){ 
            //returns pointer to node it found
            return current;
        }
    }
    
    //if not found it returns null
    return NULL; 
    
}

Node *NodeList::findOrInsertNode(int id){ 
    
    //checks to see if node already exists
    if(findNode(id) != NULL){ 
        //if node with specified id already exists, return a pointer to the existing node
        return findNode(id); 
    }
    //node does not exist
    else{ 
        //create new node to insert
        Node *newNode = new Node(id);
        //create pointer to keep track of where you are in the list
        Node *current = head; 
        //create a pointer to keep track of the previous node
        Node *previous = NULL; 
        
        while((current != NULL) && (current->ID < id)){ 
            //set previous pointer to current pointer
            previous = current; 
            //increment current pointer
            current = current->next; 
        }
        //exits when id is less then current id or current pointer is null
        //set newNode next pointer to current
        //if list is empty, or if the end of the list was reached, next would be NULL
        //otherwise, next is set to the appropriate next node based on while loop from above
        newNode->next = current; 
        //indication the list was empty and set the value of head to the new node
        if(previous == NULL){ 
            head = newNode; 
        }   
        else{ //otherwise insert in appropriate portion of the list
            previous->next = newNode; 
        }
        
        return newNode; 
        
    }
    
}

Resistor *NodeList::findResistor(string label){ 
    
    //traverses list, starting from head
    for(Node *current = head; current != NULL; current=current->next){ 
        if(current->list.findResistor(label) != NULL){ 
            return current->list.findResistor(label);
        }
    }
    
    //if not found it returns null
    return NULL; 
    
}

void NodeList::printEntireList(){ 
    
    //create pointer to keep track of where you are in the list
    Node *current = head; 
    
    //prints resistor, and increments current pointer until the end of the resistor list is reached
    while(current != NULL){ 
        current->printResistorList(); 
        current = current->next;
    }
    
}

void NodeList::modifyResistance(string label, double resistance){ 
    
    //keep track of the number of resistors modified 
    int numberOfResistorsModified = 0; 
    
    //create a pointer to keep track of where you are in the list 
    Node *current = head; 
    
    //Resistor to modify
    Resistor *modifyResistor; 
    
    //function is only called, when we are certain resistor name exists and has been inserted in the list
    //there are 2 copies of the resistor, Exit when numberOfResistors is > 2 or end of list is reached
    while((current != NULL) && (numberOfResistorsModified < 2)){ 
        
        modifyResistor = current->list.findResistor(label);
        if(modifyResistor != NULL){ 
            modifyResistor->setResistance(resistance);
            numberOfResistorsModified += 1; 
        }
        
        current = current->next;
        
    }
    
    
}

void NodeList::deleteResistor(string label){ 
    
    //keep track of the number of resistors modified 
    int numberOfResistorsDeleted = 0; 
    
    //create a pointer to keep track of where you are in the list 
    Node *current = head; 
    
    //Resistor to delete
    Resistor *deleteResistor; 
    
    while((current != NULL) && (numberOfResistorsDeleted < 2)){ 
       
        if(current->list.deleteResistor(label)){ 
            numberOfResistorsDeleted += 1; 
        }
        
        current = current->next; 
        
    }
    
}

void NodeList::deleteAllResistors(){ 
    
    //keep track of position in list
    Node *current = head; 
    
    while(current != NULL){
        current->list.deleteResistorList();
        current = current->next;
    }
    
}

int NodeList::numberOfunSet(){
    
    Node *current = head; 
    int counter = 0; 
    
    while(current != NULL){ 
        if((current->setV) == false){ 
            counter += 1; 
        }
        current = current->next;
    }
    
    return counter; 
    
}

void NodeList::setVoltTo0(){
    
    Node *current = head; 
    
    while(current != NULL){ 
        if((current->setV) == false){ 
            current->voltage = 0; 
        }
        current = current->next;
    }
    
}

void NodeList::unsetAll(){
    
    Node *current = head; 
    
    while(current != NULL){ 
        current->setV = false; 
        current->voltage = 0; 
        current = current->next;
    
    }
    
}

void NodeList::solveNodeVoltages(){ 
    
    //equivalentResistance
    double equivResistance = 0.0; 
    double voltageDivResSum = 0.0;
    double V0 = 0.0;
    
    int lessThenMinValue = 0; 
    double oldVoltage = 0.0;
    int numberOfunSetVal = 0; 
    
    /*Intermediate variable to calculate second part of voltage equation*/
    double voltageDivRes = 0.0;
    double voltage = 0.0; 
    double resistance = 0.0;
    int nodeId1 = 0; 
    int nodeId2 = 0;
    int nodeId = 0;
    /*-----------------------------------------------------------------*/
    
    numberOfunSetVal = numberOfunSet();
    
    //pointer to keep track of place in node list
    Node *current;
    //temporary node to find voltage
    Node *temp; 
    //pointer to keep track of place in resistor list
    Resistor *currentRes; 
    
    //set all unSetValues back to 0
    setVoltTo0();
    
    while(!(lessThenMinValue == numberOfunSetVal)){
        
        current = head;
        lessThenMinValue = 0;
        
        while(current != NULL){ 

            //if voltage has not been set calculate voltage for that specific node
            if(!(current->setV)){ 
                
                //equivResistance = part a) (first part) of equation given in lab
                equivResistance = current->list.sumOfResistors(); 

                //finding second part of equation
                //sets currentRes to head of resistor List
                currentRes = current->list.getHead(); 

                //incrementing through entire resistorList
                while(currentRes != NULL){ 

                    nodeId1 = currentRes->get1stEndPoint();
                    nodeId2 = currentRes->get2ndEndPoint();

                    //determines which node the other side of the resistor is connected to
                    if(nodeId1 == current->ID){ 
                        nodeId = nodeId2; 
                    }
                    else{ 
                        nodeId = nodeId1;
                    }
                    
                    //quick maths
                    temp = findNode(nodeId);
                    voltage = temp->voltage;
                    resistance = currentRes->getResistance();
                    voltageDivRes = voltage/resistance; 

                    voltageDivResSum = voltageDivResSum + voltageDivRes; 

                    //increment currentRes
                    currentRes = currentRes->getNext();

                }

                //exits currentRes while loop after it has computed voltageDivResSum
                V0 = equivResistance * voltageDivResSum;
                oldVoltage = current->voltage; 
                
                //set voltage to new value calculated
                current->changeVoltage(V0);

                //checks if voltage is converging to a specific solution
                if((abs(oldVoltage - V0)) < MIN_ITERATION_VALUE){
                    lessThenMinValue += 1;
                }   
            }

            //increment current
            current = current->next;
            
            /* Resetting Values */
            equivResistance = 0.0; 
            voltageDivResSum = 0.0;
            V0 = 0.0;
    
            oldVoltage = 0.0;
    
            /*Intermediate variable to calculate second part of voltage equation*/
            voltageDivRes = 0.0;
            voltage = 0.0; 
            resistance = 0.0;
            nodeId1 = 0; 
            nodeId2 = 0;
            nodeId = 0;
        }
    }
}

void NodeList::printNodeVoltages(){ 
    
    Node *current = head; 
    
    while (current != NULL){ 
        cout << " ";
        cout << "Node " << current->ID << ": " << current->voltage << " V" << endl;
        current = current->next;
    }
    
}

bool NodeList::setValueExist(){
    
    Node *current = head; 
    
    while(current != NULL){
        if(current->setV){ 
            return true; 
        }
        current = current->next;
    }
    
    return false;
    
}