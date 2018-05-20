/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include "TreeDB.h"
#include "TreeNode.h"

using namespace std; 

//constructor 
TreeDB::TreeDB(){ 
    root = NULL; 
    probesCount = 0; 
}

//destructor 
TreeDB::~TreeDB(){ 
    
    clear(); 
    
}

// inserts the entry pointed to by newEntry into the database. 
// If an entry with the same key as newEntry's exists 
// in the database, it returns false. Otherwise, it returns true.
bool TreeDB::insert(DBentry* newEntry) { 
    
    //basis - tree is empty 
    if (root == NULL){ 
        
        //create new TreeNode to insert into BST
        TreeNode *newTreeNode = new TreeNode(newEntry);  
        
        //set root to newTreeNode
        root = newTreeNode; 
    
        return true; 
    }
    
    //helper function to help facilitate recursion 
    bool temp = insertHelper(newEntry, root);
    return temp; 
        
}

// Insert helper function 
// used to recursively call BST
bool TreeDB::insertHelper(DBentry* newEntry, TreeNode* rootPtr){ 
    
    string entryName = newEntry->getName(); 
    string currentName = rootPtr->getEntry()->getName(); 
    
    //BST already contains entry with the same key as NewEntry
    if(entryName == currentName) { 
        return false; 
    }
    
    //Checks if newEntry has a key smaller than current rootPtr
    else if(entryName < currentName){ 
        
        //Insert to the left of node, if the left of rootPtr is null
        if(rootPtr->getLeft() == NULL){ 
            
            //create new TreeNode to insert into BST
            TreeNode* newTreeNode = new TreeNode(newEntry);
            
            //insert new TreeNode to the left of current rootPtr
            rootPtr->setLeft(newTreeNode); 
            
            return true; 
        }
        
        //recursive call on left side of rootPtr
        else return insertHelper(newEntry, rootPtr->getLeft()); 
        
    }
    
     //checks if newEntry has a key larger than current rootPtr
    else if(entryName > currentName){ 
        
        //Insert to the right of node, if the right of rootPtr is null
        if(rootPtr->getRight() == NULL){ 
            
            //create new TreeNode to insert into BST
            TreeNode* newTreeNode = new TreeNode(newEntry);
            
            //insert new TreeNode to the right of current rootPtr
            rootPtr->setRight(newTreeNode); 
            
            return true; 
        }
        
        //recursive call on right side of rootPtr
        else return insertHelper(newEntry, rootPtr->getRight()); 
        
    }    
}

// searches the database for an entry with a key equal to name.
// If the entry is found, a pointer to it is returned.
// If the entry is not found, the NULL pointer is returned.
// Also sets probesCount
DBentry* TreeDB::find(string name){ 
    
    //set probesCount to 0 at the beginning of every call to find
    TreeNode *findEntry = NULL; 
    probesCount = 0; 
    
    //basis - tree is empty 
    if (root == NULL){ 
        return NULL;
    }
    
    //helper function to help facilitate recursion 
    findEntry = findNode(name, root);
    if (findEntry != NULL){ 
        return findEntry->getEntry();
    } 
    else {
        return NULL; 
    }
    
}

// Find helper function 
// used to recursively call BST
TreeNode* TreeDB::findNode(string name, TreeNode* rootPtr){ 
    
    //end of BST, specified entry not found
    //return null
    //reset probes count if nothing was found
    if(rootPtr == NULL){ 
        probesCount = 0; 
        return NULL; 
    }
    
    else { 
        
        string currentName = rootPtr->getEntry()->getName();
        
        //specified entry found
        //return pointer
        //increments probesCount
        if (name == currentName){ 
            probesCount += 1;             
            return rootPtr; 
        }
        
        //name is less then currentName
        //traverse left side of BST
        //increments probesCount
        else if (name < currentName){ 
            probesCount += 1; 
            return findNode(name, rootPtr->getLeft()); 
        }
        
        //name is greater then currentName
        //traverse right side of BST
        //increments probesCount
        else if (name > currentName){ 
            probesCount += 1; 
            return findNode(name, rootPtr->getRight()); 
        }
        
    }
    
}

//prints the probe count generated from find function 
void TreeDB::printProbes() const{ 
    cout << probesCount << endl; 
}

//overloaded << operator for TreeDB
ostream& operator<< (ostream& out, const TreeDB& rhs){ 
    
    //if tree is not empty, call the overloaded << operator for TreeNode
    if (rhs.root != NULL){ 
        
        out << rhs.root;
        
    } 
    
}

//overloaded << operator for TreeNode
ostream& operator<< (ostream& out, TreeNode* rhs){ 
    
    //recursively print all nodes
    //go to the left most node
    if(rhs->getLeft() != NULL){ 
        operator<<(out, rhs->getLeft()); 
    }
    
    //print value
    out << *(rhs->getEntry()); 
    
    //traverse right side of tree
    if(rhs->getRight() != NULL){ 
        operator<<(out, rhs->getRight());
    }
}

// computes and prints out the total number of active entries
// in the database (i.e. entries with active==true).
void TreeDB::countActive() const{ 
    
    //keeps track of the number of active nodes
    int numActive = 0; 
    
    //calls helper function 
    if(root != NULL){
        countActiveHelper(root, numActive);
    } 
    
    cout << numActive << endl; 
}

// countActive helper function 
// used to recursively call BST
void TreeDB::countActiveHelper(TreeNode* rootPtr, int &numActive) const{ 
    
    //go to left most node
    if(rootPtr->getLeft() != NULL){ 
        countActiveHelper(rootPtr->getLeft(), numActive); 
    }
    
    //if status is active, increment counter
    if(rootPtr->getEntry()->getActive()){ 
       numActive += 1; 
    } 
     
    //traverse right side of tree
    if(rootPtr->getRight() != NULL){ 
        countActiveHelper(rootPtr->getRight(), numActive);
    }
        
}

// deletes all the entries in the database.
void TreeDB::clear(){ 
    
    clearHelper(root); 
    root = NULL; 
    
}

// clear helper function 
// used to recursively call BST
void TreeDB::clearHelper(TreeNode* rootPtr){ 
    
    // basis - nothing to do, tree empty
    if(rootPtr == NULL){ 
        return; 
    }
    
    // delete left subtree
    clearHelper(rootPtr->getLeft()); 
    
    // delete right subtree
    clearHelper(rootPtr->getRight()); 
    
    // delete the node
    delete rootPtr; 
    
}

//find previous node to specified key
//used as a helper function to remove
//returns null if either the specified key was not found
//or the specified key is the root
TreeNode* TreeDB::findPrevious(string name, TreeNode* rootPtr, TreeNode* prevNode){ 
        
    //specified key not found
    if(rootPtr == NULL){ 
        return NULL; 
    }
    
    else { 
        
        string currentName = rootPtr->getEntry()->getName();
        
        //specified entry found
        //return pointer
        if (name == currentName){ 
            return prevNode; 
        }
        
        //name is less then currentName
        //traverse left side of BST
        else if (name < currentName){ 
            prevNode = rootPtr; 
            return findPrevious(name, rootPtr->getLeft(), prevNode); 
        }
        
        //name is greater then currentName
        //traverse right side of BST
        else if (name > currentName){ 
            prevNode = rootPtr; 
            return findPrevious(name, rootPtr->getRight(), prevNode); 
        }
        
    }
    
    
}

//find previous node to specified key
//used as a helper function to remove
//returns null if either the specified key was not found
//or the specified key is the root
TreeNode* TreeDB::findMaxLeft(TreeNode* rootPtr){
    
    //Key does not exist
    if(rootPtr == NULL){
        return NULL; 
    }
    
    //traverse right BST, till you reach the end
    else{
        
        if(rootPtr->getRight() == NULL){
            return rootPtr; 
        }
        
        return findMaxLeft(rootPtr->getRight()); 
        
    }
    
}

// deletes the entry with the specified name (key)  from the database.
// If the entry was indeed in the database, it returns true.
// Returns false otherwise.
bool TreeDB::remove(string name){ 
    
    TreeNode* temp; 
    TreeNode* removeEntry = findNode(name, root); 
    temp = removeEntry; 
    TreeNode* prevNode = NULL; 
    prevNode =  findPrevious(name, root, prevNode); 
    
    //entry not found
    if(removeEntry == NULL){
        return false; 
    }
    //begin remove function 

    else {

        //node is a leaf 
        if((removeEntry->getLeft() == NULL) && (removeEntry->getRight() == NULL)){ 

            if(prevNode!= NULL){
                //sets pointer of prevNode left/right appropriately
                if(prevNode->getEntry()->getName() > removeEntry->getEntry()->getName()){
                    prevNode->setLeft(NULL); 
                }
                else{ 
                    prevNode->setRight(NULL); 
                }
            }
            
            //only 1 node in leaf
            else {
                root = NULL;              
            }
           
            delete removeEntry; 
            return true; 
           
        }

        //contains only one child on the right
        if((removeEntry->getLeft() == NULL) && (removeEntry->getRight() != NULL)){

            if(prevNode != NULL){
                if(prevNode->getEntry()->getName() > removeEntry->getEntry()->getName()){
                    prevNode->setLeft(removeEntry->getRight()); 
                }
                else{ 
                    prevNode->setRight(removeEntry->getRight()); 
                }
            }
            
            else{
                root = removeEntry->getRight(); 
            }

            delete removeEntry; 
            return true; 

        }

        //contains only one child on the left
        if((removeEntry->getLeft() != NULL) && (removeEntry->getRight() == NULL)){

            if(prevNode != NULL){
                if(prevNode->getEntry()->getName() > removeEntry->getEntry()->getName()){
                    prevNode->setLeft(removeEntry->getLeft()); 
                }
                else{ 
                    prevNode->setRight(removeEntry->getLeft()); 
                }
            }
            
            else{
                root = removeEntry->getLeft(); 
            }

            delete removeEntry; 
            return true;

        }


        //contains two children
        if((removeEntry->getLeft() != NULL) && (removeEntry->getRight() != NULL)){

            //save values of largest node in left subtree
            TreeNode* maxLeftNode = findMaxLeft(removeEntry->getLeft()); 

            string maxName = maxLeftNode->getEntry()->getName(); 
            unsigned int maxIPaddress = maxLeftNode->getEntry()->getIPaddress(); 
            bool maxActive = maxLeftNode->getEntry()->getActive(); 

            //delete max right node in left subtree
            removeEntry = findNode(maxName, root); 
            prevNode = NULL;
            prevNode =  findPrevious(maxName, root, prevNode);
            
            //left node of maxVal is empty
            if(removeEntry->getLeft() == NULL){
                
         
                if(prevNode->getEntry()->getName() > removeEntry->getEntry()->getName()){
                    prevNode->setLeft(NULL); 
                }
                else{ 
                    prevNode->setRight(NULL); 
                }
            
            }
            
            //if left node of max val is not empty, copy those values to the right pointer of previous node
            else{
                
                if(prevNode->getEntry()->getName() > removeEntry->getEntry()->getName()){
                    prevNode->setLeft(removeEntry->getLeft()); 
                }
                else{ 
                    prevNode->setRight(removeEntry->getLeft()); 
                }
                
            }

            delete removeEntry; 

            //copy over max left node into node being removed 
            temp->getEntry()->setName(maxName); 
            temp->getEntry()->setIPaddress(maxIPaddress); 
            temp->getEntry()->setActive(maxActive); 

            return true;



        }

        
    }
    
    
}