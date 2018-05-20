/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Rparser.h
 * Author: mittala6
 *
 * Created on October 16, 2017, 9:57 PM
 */

#ifndef RPARSER_H
#define RPARSER_H


#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std; 

//Constant Defintions 
#define MINIMUM_NODE_VALUE 0

//Function prototypes
int insertR(stringstream &line);
int modifyR(stringstream &line);
int printR(stringstream &line);
int printNode(stringstream &line);
int deleteR(stringstream &line);
int resPos(string name);

bool keywordAll (string name);
bool typeCheck (stringstream &line); 
bool nextEmptyChar (stringstream &line);
bool negativeResistance (double value); 
bool outOfRange (int value); 
bool repeatNode (int value1, int value2); 
bool exisitingResistorName(string name);
bool nodeIsFull(int nodeId1, int nodeId2);

void maxVal(stringstream &line, bool alreadyCalled);
void deleteArrays(); 
 

#endif /* RPARSER_H */

