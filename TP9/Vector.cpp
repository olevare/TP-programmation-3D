#include "Vector.h"
#include <math.h>


Vector::Vector(){
  x=0;
  y=0;
  z=0;
  _norme = sqrt(x*x+y*y+z*z);

}
Vector::Vector(double X, double Y, double Z){
  x=X;
  y=Y;
  z=Z;

  _norme = sqrt(x*x+y*y+z*z);

}
Vector::Vector(const Vector &p){
  x = p.x;
  y = p.y;
  z = p.z;

  _norme = sqrt(x*x+y*y+z*z);
}

Vector::Vector(Point p1,Point p2)
{
	x = p2.getX()-p1.getX();
	y = p2.getY()-p1.getY();
	z = p2.getZ()-p1.getZ();

  _norme = sqrt(x*x+y*y+z*z);

}


double Vector::norme(){
  return _norme;
}
void Vector::normalize(){
  x = x/_norme;
  y = y/_norme;
  z = z/_norme;
}
double Vector::scalar(Vector vector2){
  return x*vector2.x + y*vector2.y + z*vector2.z;
}
Vector Vector::vectoriel(Vector vector2){
  return Vector(y*vector2.getZ()-z*vector2.getY(),
		z*vector2.getX()-x*vector2.getZ(),
		x*vector2.getY()-y*vector2.getX());

  
}
double Vector::angle(Vector vector2){
  return acos( scalar(vector2) / (norme()*vector2.norme()) );

}


double Vector::getX(){
  return x;
}
double Vector::getY(){
  return y;
}
double Vector::getZ(){
  return z;
}

void Vector::setX(double X){
  x = X;
}
void Vector::setY(double Y){
  y = Y;
}
void Vector::setZ(double Z){
  z = Z;
}

Vector Vector::operator+(const Vector& v)
{
  return Vector(x + v.x,y + v.y,z + v.z);
}

Vector Vector::operator-(const Vector& v)
{
  return Vector(x - v.x,y - v.y,z - v.z);
}



Vector Vector::operator*(double n)
{
  return Vector(x*n,y*n,z*n);
}

Vector Vector::operator=(const Vector& v)
{
  x = v.x;
  y = v.y;
  z = v.z;

  return *this;
}

Vector Vector::operator=(Point v)
{
  x = v.getX();
  y = v.getY();
  z = v.getZ();

  return *this;
}

Vector Vector::operator+(Point v)
{
  return Vector(x + v.getX(),y + v.getY(),z + v.getZ());
}