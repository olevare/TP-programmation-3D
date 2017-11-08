#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "./freeglut-3.0.0/include/GL/freeglut.h" 
#include "Vector.h"

class Camera
{
	public:
		Camera();
		Camera(double,double,double,double,double,double);
		Camera(double,double,double,double,double,double,double,double,double);

		virtual void draw();

		virtual void setPosition(double,double,double);
		virtual void setPositionX(double);
		virtual void setPositionY(double);
		virtual void setPositionZ(double);
		virtual void setTarget(double,double,double);
		virtual void setTargetX(double);
		virtual void setTargetY(double);
		virtual void setTargetZ(double);
		virtual void setAngle(double,double,double);
		virtual void setAngleX(double);
		virtual void setAngleY(double);
		virtual void setAngleZ(double);

		virtual double getPositionX();
		virtual double getPositionY();
		virtual double getPositionZ();
		virtual double getTargetX();
		virtual double getTargetY();
		virtual double getTargetZ();
		virtual double getAngleX();
		virtual double getAngleY();
		virtual double getAngleZ();

		virtual void move(Vector);

		virtual double getAngleXY();
		virtual double getAngleXZ();
		virtual double getZoom();
		virtual void setAngleXY(double);
		virtual void setAngleXZ(double);
		virtual void setZoom(double);

		virtual void events(bool,double,bool,double,bool,double,bool,double,bool,double,bool,double,bool,double);
		virtual void events(bool,double,bool,double,bool,double,bool,double,bool,double,bool,double,bool,double,bool,Vector,double);
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
};

#endif