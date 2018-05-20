/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: mittala6
 *
 * Created on October 16, 2017, 9:48 PM
 */

#include "Rparser.h"
#include "Node.h"
#include "Resistor.h"
#include "NodeList.h"
#include "ResistorList.h"

using namespace std;

/*
 * 
 */

int main() {
    
    NodeList list; 
    string line, command;
    string everything = "everything";
    bool maxValCalled = false; 
    std::cout << std::fixed; 
    std::cout << setprecision(2); 
        
    //Output ready for user commands: 
    cout << "> "; 
    
    getline (cin, line); // Get a line from standard input
    
    while ( !cin.eof () ) {
        
        // Put the line in a stringstream for parsing
        // Making a new stringstream for each line so flags etc. are in a known state
        stringstream lineStream (line);
        
        //Parses first word to determine command
        lineStream >> command;
        
        //Analyzes Command 
        if (command == "insertR") {
            // parse an insertR command
            insertR(lineStream, list); 
        }
        else if (command == "solve"){ 
            //execute solve command
            solve(list);
        }
        else if (command == "setV"){
            //parse a setV command
            setV(lineStream, list);
        }
        else if (command == "unsetV"){
            //parse a setV command
            unsetV(lineStream, list);
        }
        else if (command == "modifyR") {
            //parse a modifyR command
            modifyR(lineStream, list);
        }
        
        else if (command == "deleteR") {
            //parse a deleteR command 
            deleteR(lineStream, list);
        }
        else if (command == "printR") {
            //parse a printR command
            printR(lineStream, list);
        }
        
        else if (command == "printNode") {
            //parse a printNode command
            printNode(lineStream, list);
        }
        else {
            cout << "Error: invalid command" << endl; 
        }
        
        
        //reset command string
        command = ""; 
        
        //ready for new user input 
        cout << "> "; 
        
        //Get new input line after analysis
        getline (cin, line);
        
    } // End input loop until EOF.
    
    return 0;
}

