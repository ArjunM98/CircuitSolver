/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Circle.cpp
 * Author: mittala6
 * 
 * Created on November 29, 2017, 3:34 PM
 */

#include "Circle.h"
#include <iostream>
#include <cmath>
#include "easygl.h"

Circle::Circle (string _name, string _colour, float _xcen, float _ycen,
            float _radius) 
              : Shape (_name, _colour, _xcen, _ycen) {
    
    radius = _radius; 
    
}

Circle::~Circle () {
   // No dynamic memory to delete
}

void Circle::print () const {
    
    Shape::print();
    cout << "circle";
    cout << " radius: " << radius; 
    cout << endl;

}

void Circle::scale (float scaleFac) {
    
    radius *= scaleFac; 

}

float Circle::computeArea () const {
   
    // width * height
    float area = 0.0;
   
    area = PI * pow(radius, 2.0); 
   
    return area;
}

float Circle::computePerimeter () const {
    
    float perimeter = 0.0;
   
    perimeter = 2.0 * PI * radius;
   
    return perimeter;
}


void Circle::draw (easygl* window) const {
             
    window->gl_setcolor(getColour()); 
    window->gl_fillarc(getXcen(), getYcen(), radius, 0, 360); 
}

bool Circle::pointInside (float x, float y) const {
    
    float newRadius  = 0.0; 
    
    newRadius = sqrt(pow(abs(x - getXcen()), 2) + pow(abs(y - getYcen()), 2));
    
    if (radius >= newRadius){ 
        return true; 
    }
    else { 
        return false; 
    }
    
}