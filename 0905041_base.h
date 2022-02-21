//import c++ header files
#include<bits/stdc++.h>
#include<stdio.h>
#include <iostream>
#include <math.h>
#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include "bitmap_image.hpp"


//create 3D Point Class

class Point3D
{
public:
    double x, y, z;
    Point3D(double x, double y, double z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    Point3D()
    {
        this->x = 0;
        this->y = 0;
        this->z = 0;
    }
    Point3D operator+(Point3D p)
    {
        return Point3D(this->x + p.x, this->y + p.y, this->z + p.z);
    }
    Point3D operator-(Point3D p)
    {
        return Point3D(this->x - p.x, this->y - p.y, this->z - p.z);
    }
    Point3D operator*(double d)
    {
        return Point3D(this->x * d, this->y * d, this->z * d);
    }
    Point3D operator/(double d)
    {
        return Point3D(this->x / d, this->y / d, this->z / d);
    }
    double operator*(Point3D p)
    {
        return this->x * p.x + this->y * p.y + this->z * p.z;
    }
    Point3D operator^(Point3D p)
    {
        return Point3D(this->y * p.z - this->z * p.y, this->z * p.x - this->x * p.z, this->x * p.y - this->y * p.x);
    }
    double length()
    {
        return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
    }
    Point3D normalize()
    {
        double l = this->length();
        return Point3D(this->x / l, this->y / l, this->z / l);
    }
    Point3D cross(Point3D p)
    {
        return Point3D(this->y * p.z - this->z * p.y, this->z * p.x - this->x * p.z, this->x * p.y - this->y * p.x);
    }
    double dot(Point3D p)
    {
        return this->x * p.x + this->y * p.y + this->z * p.z;
    }

};

//create Color class
class Color
{
public:
    double r, g, b;
    Color(double r, double g, double b)
    {
        this->r = r;
        this->g = g;
        this->b = b;
    }
    Color()
    {
        this->r = 0;
        this->g = 0;
        this->b = 0;
    }
};


//declare object class 

class Object
{
public:
    Point3D reference_point;
    Point3D normal;
    Color color;
    double coEfficients[4];
    double height, width, length;
    int shine;

    Object(){}

    virtual void draw(){}
    void setColor(){}
    void setShine(){}
    void setCoefficients(){}
    

};

//create Ray class
class Ray
{
public:
    Point3D start;
    Point3D direction;
    Ray(Point3D start, Point3D direction)
    {
        this->start = start;
        this->direction = direction;
    }
};