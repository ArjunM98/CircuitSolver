/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "DBentry.h"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

using namespace std; 

//default constructor
DBentry::DBentry(){ 
    
}

//destructor
DBentry::~DBentry(){ 
    
}

//constructor
DBentry::DBentry(string _name, unsigned int _IPaddress, bool _active){ 
    name = _name; 
    IPaddress = _IPaddress; 
    active = _active; 
}

// returns whether or not this entry is active.
bool DBentry::getActive() const { 
    return active; 
}

// returns the IPaddress data.
unsigned int DBentry::getIPaddress() const { 
    return IPaddress; 
}

// returns the name.
string DBentry::getName() const { 
    return name; 
}

// sets whether or not this entry is active.
void DBentry::setActive(bool _active) { 
    active = _active; 
}

// sets the IPaddress data.
void DBentry::setIPaddress(unsigned int _IPaddress) { 
    IPaddress = _IPaddress; 
}

// sets the domain name, which we will use as a key.
void DBentry::setName(string _name) { 
    name = _name; 
}

//friend function
ostream& operator<<(ostream& out, const DBentry& rhs){ 
    
    out << rhs.name << " : " << rhs.IPaddress << " : "; 
    
    //checks status of node
    if(rhs.active){
        cout << "active" << endl; 
    }
    else if (!(rhs.active)){
        cout << "inactive" << endl; 
    }
    
}