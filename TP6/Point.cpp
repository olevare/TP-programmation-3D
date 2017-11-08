#include "Point.h"
#include "math.h"


Point::Point(){}
Point::Point(double X, double Y, double Z){
  x=X;
  y=Y;
  z=Z;
}
Point::Point(const Point &p){
  x = p.x;
  y = p.y;
  z = p.z;
}


Point Point::projectOnLine(Point point1Line, Point point2Line){
  Point p;
  //bc
  double ux = (point2Line.x - point1Line.x);
  double uy = (point2Line.y - point1Line.y);
  double uz = (point2Line.z - point1Line.z);

  double bax = (x - point1Line.x);
  double bay = (y - point1Line.y);
  double baz = (z - point1Line.z);
  
  Vector v1(bax,bay,baz);
  
  Vector v2(ux,uy,uz);
  
  v2.normalize();
  
  double dist = v1.scalar(v2)/(v2.norme());
    
  p.x = point1Line.x + ux * dist;
  p.y = point1Line.y + uy * dist;
  p.z = point1Line.z + uz * dist;

  return p;
}

Point Point::projectOnLine(Vector vecteur, Point pLine){
  return projectOnLine(pLine,Point(pLine.getX()+vecteur.getX(),pLine.getY()+vecteur.getY(),pLine.getZ()+vecteur.getZ()));
}


Point Point::projectOnPlan(Point pointOnPlane, Vector normalOfPlane){
  
  Point p;//M'
  
  double maX = x-pointOnPlane.x;
  double maY = y-pointOnPlane.y;
  double maZ = z-pointOnPlane.z;
  Vector ma(maX,maY,maZ);

  normalOfPlane.normalize();
  
  double normeMP = ma.scalar(normalOfPlane)/normalOfPlane.norme();
  
  p.x = x - normalOfPlane.getX()*normeMP;
  p.y = y - normalOfPlane.getY()*normeMP;
  p.z = z - normalOfPlane.getZ()*normeMP;


  return p;
}






double Point::getX(){
  return x;
}
double Point::getY(){
  return y;
}
double Point::getZ(){
  return z;
}

void Point::setX(double X){
  x = X;
}
void Point::setY(double Y){
  y = Y;
}
void Point::setZ(double Z){
  z = Z;
}


Point Point::operator*(double n)
{
  return Point(x*n,y*n,z*n);
}

Point Point::operator+(const Point& v)
{
  return Point(x + v.x,y + v.y,z + v.z);
}

Point Point::operator-(const Point& v)
{
  return Point(x - v.x,y - v.y,z - v.z);
}

Point Point::operator+(Vector v)
{
  return Point(x + v.getX(),y + v.getY(),z + v.getZ());
}

Point Point::operator-(Vector v)
{
  return Point(x - v.getX(),y - v.getY(),z - v.getZ());
}

Point Point::operator=(const Point& v)
{
  x = v.x;
  y = v.y;
  z = v.z;

  return *this;
}

Point Point::operator=(Vector v)
{
  x = v.getX();
  y = v.getY();
  z = v.getY();

  return *this;
}

