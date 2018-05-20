/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Polygon.h
 * Author: mittala6
 *
 * Created on November 29, 2017, 4:06 PM
 */

#ifndef POLYGON_H
#define POLYGON_H


#include "Shape.h"
#include "easygl.h"

class Polygon : public Shape{
private:
    
    t_point verticesP[100]; 
    int nPoint; 
    
    // Private helper functions.
   t_point getVecBetweenPoints (t_point start, t_point end) const;
            
public:
    
    //constructor
    Polygon (string _name, string _colour, float _xcen, float _ycen,
            t_point *_verticesP, int _nPoint);
    
    //destructor
    virtual ~Polygon();

    virtual void print () const;
    virtual void scale (float scaleFac);
    virtual float computeArea () const;
    virtual float computePerimeter () const;
    virtual void draw (easygl* window) const;
    virtual bool pointInside (float x, float y) const;

};

#endif /* POLYGON_H */

