/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "TreeNode.h"

//constructor 
TreeNode::TreeNode(DBentry* _entryPtr){ 
    left = NULL; 
    right = NULL; 
    entryPtr = _entryPtr; 
}

//destructor 
TreeNode::~TreeNode(){ 
    
    if(entryPtr != NULL){ 
        delete entryPtr; 
    }
    entryPtr = NULL; 
    left = NULL; 
    right = NULL; 

}

// returns a pointer to the DBentry the TreeNode contains. 
DBentry *TreeNode::getEntry() const{ 
    return entryPtr; 
}

// gets the left child of the TreeNode.
TreeNode *TreeNode::getLeft() const{ 
    return left; 
}

// gets the right child of the TreeNode
TreeNode *TreeNode::getRight() const{ 
    return right; 
}

// sets the left child of the TreeNode.
void TreeNode::setLeft(TreeNode* newLeft){ 
    left = newLeft; 
}

// sets the right child of the TreeNode
void TreeNode::setRight(TreeNode* newRight){ 
    right = newRight; 
}