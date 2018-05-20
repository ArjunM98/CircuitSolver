/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: mittala6
 *
 * Created on November 17, 2017, 9:34 AM
 */

#include <cstdlib>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

#include "TreeDB.h"

using namespace std;

/*
 * 
 */
void insert(stringstream &lineStream, TreeDB &root){ 
    
    // parse an insert command
    string key; 
    unsigned int ipAddress; 
    string strStatus; 
    bool boolStatus; 

    lineStream >> key; 
    lineStream >> ipAddress; 
    lineStream >> strStatus; 
    
    if (strStatus == "active"){ 
        boolStatus = true; 
    }
    else{ 
        boolStatus = false; 
    }

    //create new DBentry
    DBentry* newEntry = new DBentry(key, ipAddress, boolStatus); 

    //insert new DBentry
    //returns true if entry was inserted
    //returns false if entry was not inserted 
    if(root.insert(newEntry)) { 
        cout << "Success" << endl; 
    }
    
    //delete entry since it was not inserted 
    else { 
        delete newEntry;
        cout << "Error: entry already exists" << endl; 
    }
    
}

void find(stringstream &lineStream, TreeDB &root){ 
    
    //parse a find command
    string key; 
    DBentry *findEntry; 
    
    lineStream >> key; 
    
    //returns pointer to a DBentry if found
    //returns null if specified entry was not found
    findEntry = root.find(key); 
    
    //entry not found
    if(findEntry == NULL){ 
        cout << "Error: entry does not exist" << endl; 
    }
    
    //using overloaded operator in DBentry
    else { 
        cout << *findEntry;
    }
    
}

void printprobes(stringstream &lineStream, TreeDB &root){ 
    
    //parse a find command
    string key; 
    DBentry *findEntry; 
    
    lineStream >> key; 
    
    //returns pointer to a DBentry if found
    //returns null if specified entry was not found
    findEntry = root.find(key); 
    
    //entry not found
    if(findEntry == NULL){ 
        cout << "Error: entry does not exist" << endl; 
    }
    
    //else print number of probes visited
    else { 
        root.printProbes();
    }
    
}

void printall(TreeDB &root){ 
    
    //calls overloaded root operator
    cout << root; 
    
}

void countactive(TreeDB &root){ 
    
    root.countActive(); 
    
}

void updateStatus(stringstream &lineStream, TreeDB &root){ 
    
    //parses update status command 
    string key;
    string strStatus;
    bool boolStatus; 
    DBentry *updateEntry; 
    
    lineStream >> key; 
    lineStream >> strStatus; 
    
    //checks if specified key is in the BST
    updateEntry = root.find(key); 
    
    //returns error message if not found
    if(updateEntry == NULL){ 
        cout << "Error: entry does not exist" << endl; 
    }
    
    //updates DBentry if specified key is found
    //outputs success message
    else{
        
        if (strStatus == "active"){ 
            boolStatus = true; 
        }
        else{ 
            boolStatus = false; 
        }       
        
        updateEntry->setActive(boolStatus); 
        cout << "Success" << endl; 
    }
    
}

void removeAll(TreeDB &root){ 
    
    root.clear(); 
    cout << "Success" << endl; 
    
}

void remove(stringstream &lineStream, TreeDB &root){ 
    
    //execute remove command
    string key; 

    lineStream >> key; 

    if(root.remove(key)){
        cout << "Success" << endl;
    }
    else { 
        cout << "Error: entry does not exists" << endl; 
    }
 
    
}

int main() {
        
    //root of binary search tree
    TreeDB root; 
    string line, command;
    
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
        if (command == "insert") {
            
            //execute insert function
            insert(lineStream, root); 
            
        }
        
        else if (command == "find") { 
            
            //execute find command
            find(lineStream, root); 
            
        }
        
        else if (command == "remove") {
            
            remove(lineStream, root);
            
        }
        
        else if (command == "printall") {
            
            //execute printall command 
            printall(root);
            
        }
        
        else if (command == "printprobes") {
            
            //execute printprobes function
            printprobes(lineStream, root); 
            
        }
        
        else if (command == "removeall") {
            
            //execute removeall command
            removeAll(root);
        }
        
        else if (command == "countactive") {
            
            //execute countactive command 
            countactive(root); 
            
        }
        
        else if (command == "updatestatus") {
            
            //execute updatestatus command 
            updateStatus(lineStream, root); 
                    
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



