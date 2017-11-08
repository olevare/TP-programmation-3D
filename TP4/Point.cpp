#include <iostream>
#include <math.h>
#include "Vector.h"
#include "Point.h"

using namespace std;

    Point::Point()
    {
        x = 0;
        y = 0;
        z = 0;
    }

    Point::Point(double a, double b, double c)
    {
        x = a;
        y = b;
        z = c;
    }

    Point::Point(const Point &p)
    {
        x = p.x;
        y = p.y;
        z = p.z;
    }

    double Point::getX()
    {
        return x;
    }

    double Point::getY()
    {
        return y;
    }

    double Point::getZ()
    {
        return z;
    }

    void Point::setX(double a)
    {
        x = a;
    }

    void Point::setY(double a)
    {
        y = a;
    }

    void Point::setZ(double a)
    {
        z = a;
    }

    Point Point::ProjectOnLine(Point Point1Line, Point Point2Line)
    {
        Vector BA(x - Point1Line.getX(), y - Point1Line.getY(), z - Point1Line.getZ());
        Vector BC(Point2Line.getX() - Point1Line.getX(), Point2Line.getY() - Point1Line.getY(), Point2Line.getZ() - Point1Line.getZ());

        BC.Normalize();

        double BAprime = BA.Scalar(BC) / BC.Norme();

        return Point(Point1Line.getX() + BC.getX()*BAprime,
                    Point1Line.getY() + BC.getY()*BAprime,
                    Point1Line.getZ() + BC.getZ()*BAprime);
    }

    Point Point::ProjectOnLine(Vector vecteur, Point PLine)
    {
        return ProjectOnLine(PLine,Point(PLine.getX()+vecteur.getX(),PLine.getY()+vecteur.getY(),PLine.getZ()+vecteur.getZ()));
    }

    Point Point::ProjectOnPlan(Point PointOnPlane, Vector NormalOfPlane)
    {
        Vector MA(PointOnPlane.getX() - x, PointOnPlane.getY() - y, PointOnPlane.getZ() - z);

        NormalOfPlane.Normalize();

        double mmprime = MA.Scalar(NormalOfPlane) / NormalOfPlane.Norme();

        return Point(x + (NormalOfPlane.getX() * mmprime),
                    y + (NormalOfPlane.getY() * mmprime),
                    z + (NormalOfPlane.getZ() * mmprime));
    }

    Point Point::operator*(double n)
    {
        return Point(x*n,y*n,z*n);
    }

    Point Point::operator=(const Point& v)
    {
        x = v.x;
        y = v.y;
        z = v.z;

        return *this;
    }

    Point Point::operator+(const Point& v)
    {
        return Point(x + v.x,y + v.y,z + v.z);
    }

    Point Point::operator-(const Point& v)
    {
        return Point(x - v.x,y - v.y,z - v.z);
    }