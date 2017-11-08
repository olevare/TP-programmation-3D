#ifndef VECTOR_H_INCLUDE
#define VECTOR_H_INCLUDE

#include <cstdio>
#include <cstdlib>
#include "Point.h"

class Point;

class Vector{
 private:
  double x;
  double y;
  double z;
  double _norme;
 public:
  Vector();
  Vector(double x, double y, double z);
  Vector(const Vector &v);
  Vector(Point p1,Point p2);
	
  double norme();
  void normalize();
  double scalar(Vector vector2);
  Vector vectoriel(Vector vector2);
  double angle(Vector vector2);
  
  double getX();
  double getY();
  double getZ();

  void setX(double x);
  void setY(double y);
  void setZ(double z);


  Vector operator+(const Vector&);
  Vector operator-(const Vector&);
  Vector operator*(double);
  Vector operator=(const Vector&);

  Vector operator+(Point);
  Vector operator=(Point);

};

#endif