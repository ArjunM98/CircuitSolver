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
#include "NodeList.h"

using namespace std; 

//Constant Defintions 
#define MINIMUM_NODE_VALUE 0

//Function prototypes
int insertR(stringstream &line, NodeList &list);
int modifyR(stringstream &line, NodeList &list);
int printR(stringstream &line, NodeList &list);
int printNode(stringstream &line, NodeList &list);
int deleteR(stringstream &line, NodeList &list);
int setV(stringstream &line, NodeList &list);
int unsetV(stringstream &line, NodeList &list);
int solve(NodeList &list);

bool keywordAll (string name);
bool typeCheck (stringstream &line); 
bool nextEmptyChar (stringstream &line);
bool negativeResistance (double value); 
bool repeatNode (int value1, int value2); 

 

#endif /* RPARSER_H */

