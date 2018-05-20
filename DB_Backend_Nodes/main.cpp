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

using namespace std;

/*
 * 
 */
int main() {
    
    string line, command;
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
        if (command == "maxVal") {
            //parse a maxVal command
            maxVal(lineStream, maxValCalled);
            maxValCalled = true; 
        }
        else if (command == "insertR") {
            // parse an insertR command
            insertR(lineStream); 
        }
        else if (command == "modifyR") {
            //parse a modifyR command
            modifyR(lineStream);
        }
        else if (command == "deleteR") {
            //parse a deleteR command 
            deleteR(lineStream);
        }
        else if (command == "printR") {
            //parse a printR command
            printR(lineStream);
        }
        else if (command == "printNode") {
            //parse a printNode command
            printNode(lineStream);
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

