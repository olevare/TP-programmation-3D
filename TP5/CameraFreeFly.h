#ifndef CameraFreeFly_H_INCLUDED
#define CameraFreeFly_H_INCLUDED

#include "Camera.h"

#include <iostream>

using namespace std;

class CameraFreeFly : public Camera
{
	public:
		CameraFreeFly();
		CameraFreeFly(double,double,double,double,double,double);
		CameraFreeFly(double,double,double,double,double,double,double,double,double);

		void draw();

		void setPosition(double,double,double);
		void setPositionX(double);
		void setPositionY(double);
		void setPositionZ(double);
		void setTarget(double,double,double);
		void setTargetX(double);
		void setTargetY(double);
		void setTargetZ(double);
		void setAngle(double,double,double);
		void setAngleX(double);
		void setAngleY(double);
		void setAngleZ(double);

		double getPositionX();
		double getPositionY();
		double getPositionZ();
		double getTargetX();
		double getTargetY();
		double getTargetZ();
		double getAngleX();
		double getAngleY();
		double getAngleZ();

		void move(Vector);

		void events(bool,double,bool,double,bool,double,bool,double,bool,double,bool,double,bool,double);
		void events(bool,double,bool,double,bool,double,bool,double,bool,double,bool,double,bool,double,bool,Vector,double);
	protected:
		double _pos_x;
		double _pos_y;
		double _pos_z;
		double _tar_x;
		double _tar_y;
		double _tar_z;
		double _ang_x;
		double _ang_y;
		double _ang_z;

		double _angleXY;
		double _angleXZ;

};

#endif