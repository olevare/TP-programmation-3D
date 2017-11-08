#include <iostream>
#include <math.h>
#include "Vector.h"

using namespace std;

    Vector::Vector()
    {
        x = 0;
        y = 0;
        z = 0;
    }

    Vector::Vector(double a, double b, double c)
    {
        x = a;
        y = b;
        z = c;
    }

    Vector::Vector(const Vector &p)
    {
        x = p.x;
        y = p.y;
        z = p.z;
    }

    double Vector::getX()
    {
        return x;
    }

    double Vector::getY()
    {
        return y;
    }

    double Vector::getZ()
    {
        return z;
    }

    void Vector::setX(double a)
    {
        x = a;
    }

    void Vector::setY(double a)
    {
        y = a;
    }

    void Vector::setZ(double a)
    {
        z = a;
    }

    double Vector::Norme()
    {
    	double norme = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));

    	return norme;
    }

    void Vector::Normalize()
    {
    	double norme = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));

    	x = x / norme;
    	y = y / norme;
    	z = z / norme;
    }

    double Vector::Scalar(Vector Vector2)
    {
    	double scal = (x * Vector2.getX()) + (y * Vector2.getY()) + (z * Vector2.getZ());

    	return scal;
    }

    Vector Vector::Vectoriel(Vector Vector2)
    {
    	Vector v;

    	v.setX((y * Vector2.getZ()) - (z * Vector2.getY()));
    	v.setY((z * Vector2.getX()) - (x * Vector2.getZ()));
    	v.setZ((x * Vector2.getY()) - (y * Vector2.getX()));

    	return v;
    }

    double Vector::Angle(Vector Vector2)
    {
    	double scal = this->Scalar(Vector2);

    	double normeun = this->Norme();
    	double normedeux = Vector2.Norme();

    	double cosinus = scal / (normeun * normedeux);

    	double angle = acos(cosinus);

    	return angle;
    }