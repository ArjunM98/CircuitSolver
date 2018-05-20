/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Rectangle.h
 * Author: mittala6
 *
 * Created on November 29, 2017, 1:01 PM
 */

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"
#include "easygl.h"

class Rectangle : public Shape {
private: 
   
   float width, height; 
    
public:
    //constructor 
    Rectangle (string _name, string _colour, float _xcen, float _ycen,
            float width, float height);
    
    //destructor
    virtual ~Rectangle();
    
    virtual void print () const;
    virtual void scale (float scaleFac);
    virtual float computeArea () const;
    virtual float computePerimeter () const;
    virtual void draw (easygl* window) const;
    virtual bool pointInside (float x, float y) const;

};

#endif /* RECTANGLE_H */

