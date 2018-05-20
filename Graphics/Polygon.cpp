/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Polygon.cpp
 * Author: mittala6
 * 
 * Created on November 29, 2017, 4:06 PM
 */

#include "Polygon.h"
#include <iostream>
#include <cmath>
#include "easygl.h"

//constructor
Polygon::Polygon (string _name, string _colour, float _xcen, float _ycen,
            t_point *_verticesP, int _nPoint) 
              : Shape (_name, _colour, _xcen, _ycen) {
    
    for(int i = 0; i < _nPoint; i++){ 
        verticesP[i].x = _verticesP[i].x; 
        verticesP[i].y = _verticesP[i].y; 
    }
    
    nPoint = _nPoint; 
    
}

Polygon::~Polygon () {
   // No dynamic memory to delete
}

//print polygon
void Polygon::print () const {
    
    Shape::print();
    cout << "polygon";
    
    for (int i = 0; i < nPoint; i++) {
        cout << " (" << getXcen() + verticesP[i].x << "," << getYcen() + verticesP[i].y << ")";
    }
    cout << endl;
    

}

//scaling polygon
void Polygon::scale (float scaleFac) {
    
    for(int i = 0; i < nPoint; i++){
        verticesP[i].x *= scaleFac;
        verticesP[i].y *= scaleFac;
    } 

}

//computing area 
float Polygon::computeArea () const {
   
    // width * height
    float area = 0.0;
    int previousVertex = nPoint - 1; 
    
    for(int i = 0; i < nPoint; i++){
        area = area + ((verticesP[previousVertex].x + verticesP[i].x) * (verticesP[previousVertex].y - verticesP[i].y)); 
        previousVertex = i; 
    }
    
    return (area / 2.0); 
   
}

//computing perimeter
float Polygon::computePerimeter () const {
    
    float perimeter = 0;
    float sideLength;
    int previousVertex = nPoint - 1; 
    t_point dist, vertexStart, vertexEnd;
   
    for (int i = 0; i < nPoint; i++) {
        vertexStart.x = getXcen() + verticesP[i].x; 
        vertexStart.y = getYcen() + verticesP[i].y; 
        
        vertexEnd.x = getXcen() + verticesP[previousVertex].x; 
        vertexEnd.y = getYcen() + verticesP[previousVertex].y;
        
        dist = getVecBetweenPoints (vertexStart, vertexEnd);
        sideLength = sqrt (dist.x * dist.x + dist.y * dist.y);
        perimeter += sideLength;
        
        previousVertex = i;
    }
   
    return perimeter;
}

bool Polygon::pointInside (float x, float y) const {
   // Make a point that corresponds to where you clicked. Since all my
   // vertices are relative to the triangle center, it is more convenient
   // to also shift the click point so it is an offset from the triangle 
   // center.
   t_point click;
   click.x = x - getXcen();
   click.y = y - getYcen();
   
   // The test is that a horizontal line (ray) from x = -infinity to the click point
   // will cross (intersect) only one side of triangle to the left of the 
   // click point.  If the point is above or below the polygon, the ray will not
   // intersect any sides.
   // if point is inside polygon, ray will intersect odd number of sides
   // if point is outside polygon, ray will intersect an even number of sides
   
   t_point vecOfSide;
   float distanceAlongVector, yDistance;
   int endIndex;
   int sidesToLeft = 0;
   
   for (int istart = 0; istart < nPoint; istart++) {
      endIndex = (istart + 1) % nPoint; // Next vertex after istart
      vecOfSide = getVecBetweenPoints (verticesP[istart], verticesP[endIndex]);
      yDistance = (click.y - verticesP[istart].y);
      if (vecOfSide.y != 0) {
          distanceAlongVector = yDistance / vecOfSide.y;
      }
      else if (yDistance == 0) {
          distanceAlongVector = 0;
      }
      else {
          distanceAlongVector = 1e10; // Really infinity, but this is big enough
      }
      
      // We intersect this side if the distance (scaling) along the side vector to 
      // get to our "click" y point is between 0 and 1.  Count the first 
      // endpoint of the side as being part of the line (distanceAlongVector = 0)
      // but don't count the second endPoint; we'll intersect that point later 
      // when we check the next side.
      if (distanceAlongVector >= 0 && distanceAlongVector < 1) {
         float xIntersection = verticesP[istart].x + vecOfSide.x * distanceAlongVector;
         if (xIntersection <= click.x ) 
             sidesToLeft++;
      }
   }
   
   //returns true if found
   //else returns false
   return (sidesToLeft % 2);
}


void Polygon::draw (easygl* window) const{
    
    t_point coords[nPoint];
    
    for(int i = 0; i < nPoint; i++){ 
      coords[i].x = getXcen() + verticesP[i].x;
      coords[i].y = getYcen() + verticesP[i].y;
    }
    
    window->gl_setcolor(getColour()); 
    window->gl_fillpoly(coords, nPoint); 
    
}

// Return the (x,y) vector between start and end points.
t_point Polygon::getVecBetweenPoints (t_point start, t_point end) const {
   t_point vec;
   vec.x = end.x - start.x;
   vec.y = end.y - start.y;
   return (vec);
}
