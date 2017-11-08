#ifndef POINT_H_INCLUDE
#define POINT_H_INCLUDE

#include <cstdio>
#include <cstdlib>

#include "Vector.h"

class Vector;

class Point{


 public:
  double x;
  double y;
  double z;
  
  Point();
  Point(double x,double y,double z);
  Point(const Point &p);


  double getX();
  double getY();
  double getZ();

  void setX(double x);
  void setY(double y);
  void setZ(double z);

  Point projectOnLine(Point point1LIne,Point point2Line);
  Point projectOnLine(Vector vecteur, Point pLine);
  Point projectOnPlan(Point pointOnPlane, Vector NormalOfPlane);

  Point operator*(double);
  Point operator=(const Point&);
  Point operator=(Vector);
  Point operator+(const Point&);
  Point operator-(const Point&);

  Point operator-(Vector);
  Point operator+(Vector);
};
#endif
