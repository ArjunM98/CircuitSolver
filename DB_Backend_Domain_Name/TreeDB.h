#ifndef _TREEDB_H
#define _TREEDB_H

#include "TreeNode.h"
#include "DBentry.h"

class TreeDB {

private:
   TreeNode* root;
   int probesCount;
   
   // You will need to add additional private functions
   
   // Insert helper function 
   // used to recursively call BST
   bool insertHelper(DBentry* newEntry, TreeNode* rootPtr); 
   
   // Find helper function 
   // used to recursively call BST
   TreeNode* findNode(string name, TreeNode* rootPtr); 
   
   // countActive helper function 
   // used to recursively call BST
   void countActiveHelper(TreeNode* rootPtr, int &numActive) const;
   
   // clear helper function 
   // used to recursively call BST
   void clearHelper(TreeNode* rootPtr); 
   
   //find previous node to specified key
   //used as a helper function to remove
   //returns null if either the specified key was not found
   //or the specified key is the root
   TreeNode* findPrevious(string name, TreeNode* rootPtr, TreeNode*  prevNode); 
   
   //finds maximum node in left subtree in reference too root "name"
   //used as a helper function to remove
   //returns null if either the specified key was not found 
   //or the specified key is the root
   TreeNode* findMaxLeft(TreeNode* rootPtr); 
   
public:
   // the default constructor, creates an empty database.
   TreeDB();

   // the destructor, deletes all the entries in the database.
   ~TreeDB();

   // inserts the entry pointed to by newEntry into the database. 
   // If an entry with the same key as newEntry's exists 
   // in the database, it returns false. Otherwise, it returns true.
   bool insert(DBentry* newEntry); 

   // searches the database for an entry with a key equal to name.
   // If the entry is found, a pointer to it is returned.
   // If the entry is not found, the NULL pointer is returned.
   // Also sets probesCount
   DBentry* find(string name);

   // deletes the entry with the specified name (key)  from the database.
   // If the entry was indeed in the database, it returns true.
   // Returns false otherwise.
   bool remove(string name);
	
   // deletes all the entries in the database.
   void clear();
    
   // prints the number of probes stored in probesCount
   void printProbes() const;
   
   // computes and prints out the total number of active entries
   // in the database (i.e. entries with active==true).
   void countActive () const;

   // Prints the entire tree, in ascending order of key/name
   friend ostream& operator<< (ostream& out, const TreeDB& rhs);
}; 

// You *may* choose to implement the function below to help print the 
// tree.  You do not have to implement this function if you do not wish to.
ostream& operator<< (ostream& out, TreeNode* rhs);   
   
#endif 

