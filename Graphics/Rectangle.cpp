/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Rectangle.cpp
 * Author: mittala6
 * 
 * Created on November 29, 2017, 1:01 PM
 */

#include <iostream>
#include <cmath>
#include "Rectangle.h"
#include "easygl.h"

using namespace std; 

// Constructor. First set up base class (Shape), then store the 
// vertices, which are 4 (x,y) points giving offsets from the Shape center
Rectangle::Rectangle (string _name, string _colour, float _xcen, float _ycen,
            float _width, float _height) 
              : Shape (_name, _colour, _xcen, _ycen) {
    
    width = _width; 
    height = _height; 
    
}

Rectangle::~Rectangle () {
   // No dynamic memory to delete
}

void Rectangle::print () const {
    
    Shape::print();
    cout << "rectangle";
    cout << " width: " << width << " height: " << height; 
    cout << endl;

}

void Rectangle::scale (float scaleFac) {
    
    width *= scaleFac; 
    height *= scaleFac; 

}

float Rectangle::computeArea () const {
   
    // width * height
    float area;
   
    area = width * height; 
   
    return area;
}

float Rectangle::computePerimeter () const {
    
    float perimeter = 0;
   
    perimeter = (width * 2) + (height * 2);
   
    return perimeter;
}

void Rectangle::draw (easygl* window) const {
   
    float xLeft, xRight, yBottom, yTop;
    
    //calculates top right and bottom left coordinates of rectangle 
    xLeft = (getXcen() - (width / 2)); 
    xRight = (getXcen() + (width / 2)); 
    
    yBottom = (getYcen() - (height / 2)); 
    yTop = (getYcen() + (height / 2)); 
             
    window->gl_setcolor(getColour()); 
    window->gl_fillrect(xLeft, yBottom, xRight, yTop); 
}


bool Rectangle::pointInside (float x, float y) const {

    //calculate vertices of rectangle
    float xLeft, xRight, yBottom, yTop; 
    
    xLeft = (getXcen() - (width / 2)); 
    xRight = (getXcen() + (width / 2)); 
    
    yBottom = (getYcen() - (height / 2)); 
    yTop = (getYcen() + (height / 2)); 
   
    if((x >= xLeft) && (x <= xRight) && (y >= yBottom) && (y <= yTop)){ 
        return true; 
    }
    else{
        return false; 
    }
    
}
