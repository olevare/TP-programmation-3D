#ifndef Vector_h
#define Vector_h

class Vector
{
private:

	double x;
	double y;
	double z;	

public:

	Vector();
	Vector(double x, double y, double z);
	Vector(const Vector &v);
		
	double getX();
	double getY();
	double getZ();
	void setX(double d);
	void setY(double d);
	void setZ(double d);
		
	double Norme();
	void Normalize();
	double Scalar (Vector Vector2);
	Vector Vectoriel(Vector Vector2);
	double Angle(Vector Vector2);
};

#endif