#ifndef CAMERAVIEW_H_INCLUDED
#define CAMERAVIEW_H_INCLUDED

#include "Camera.h"

class CameraView : public Camera
{
	public:
		CameraView();
		CameraView(double,double,double,double,double,double);
		CameraView(double,double,double,double,double,double,double,double,double);
		CameraView(double,double,double);

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

		void setAngleXY(double);
		void setAngleXZ(double);
		void setZoom(double);

		double getPositionX();
		double getPositionY();
		double getPositionZ();
		double getTargetX();
		double getTargetY();
		double getTargetZ();
		double getAngleX();
		double getAngleY();
		double getAngleZ();

		double getAngleXY();
		double getAngleXZ();
		double getZoom();

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
		double _zoom;

};

#endif