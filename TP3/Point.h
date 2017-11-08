#ifndef Point_h
#define Point_h

#include "Vector.h"

class Point 
{
private:

	double x;
	double y;
	double z;

public:

	Point();
	Point(double x, double y, double z);
	Point(const Point &p);
		
	double getX();
	double getY();
	double getZ();
	void setX(double d);
	void setY(double d);
	void setZ(double d);
		
	Point ProjectOnLine(Point Point1Line, Point Point2Line);
	Point ProjectOnLine(Vector vecteur, Point PLine);
	Point ProjectOnPlan(Point PointOnPlane, Vector NormalOfPlane);

	Point operator*(double);
  	Point operator=(const Point&);
  	Point operator+(const Point&);
  	Point operator-(const Point&);

};

#endif