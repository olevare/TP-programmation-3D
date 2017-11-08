#include "CameraView.h"
#include <math.h>

CameraView::CameraView()
{
	_pos_x = 1;
	_pos_y = 1;
	_pos_z = 0;
	_tar_x = 0;
	_tar_y = 0;
	_tar_z = 0;
	_ang_x = 0;
	_ang_y = 0;
	_ang_z = 1;

	_angleXY = 0;
	_angleXZ = 0;
	_zoom = 1;
}

CameraView::CameraView(double axy,double axz,double z)
{
	_pos_x = 1;
	_pos_y = 1;
	_pos_z = 0;
	_tar_x = 0;
	_tar_y = 0;
	_tar_z = 0;
	_ang_x = 0;
	_ang_y = 0;
	_ang_z = 1;

	_angleXY = axy;
	_angleXZ = axz;
	_zoom = z;
}

CameraView::CameraView(double px,double py,double pz,double tx,double ty,double tz)
{
	_pos_x = px;
	_pos_y = py;
	_pos_z = pz;
	_tar_x = tx;
	_tar_y = ty;
	_tar_z = tz;
	_ang_x = 0;
	_ang_y = 0;
	_ang_z = 1;

	_angleXY = 0;
	_angleXZ = 0;
	_zoom = 1;
}

CameraView::CameraView(double px,double py,double pz,double tx,double ty,double tz,double ax,double ay,double az)
{
	_pos_x = px;
	_pos_y = py;
	_pos_z = pz;
	_tar_x = tx;
	_tar_y = ty;
	_tar_z = tz;
	_ang_x = ax;
	_ang_y = ay;
	_ang_z = az;

	_angleXY = 0;
	_angleXZ = 0;
	_zoom = 1;
}


void CameraView::draw()
{
	_pos_x = _zoom * cos(_angleXZ * M_PI / 180.)*cos(_angleXY * M_PI / 180.);
	_pos_y = _zoom * cos(_angleXZ * M_PI / 180.)*sin(_angleXY * M_PI / 180.);
	_pos_z = _zoom * sin(_angleXZ * M_PI / 180.);

	gluLookAt(_pos_x,_pos_y,_pos_z,_tar_x,_tar_y,_tar_z,_ang_x,_ang_y,_ang_z);
}


void CameraView::setPosition(double px,double py,double pz)
{
	_pos_x = px;
	_pos_y = py;
	_pos_z = pz;
}

void CameraView::setPositionX(double px)
{
	_pos_x = px;
}

void CameraView::setPositionY(double py)
{
	_pos_y = py;
}

void CameraView::setPositionZ(double pz)
{
	_pos_z = pz;
}

void CameraView::setTarget(double tx,double ty,double tz)
{
	_tar_x = tx;
	_tar_y = ty;
	_tar_z = tz;
}

void CameraView::setTargetX(double tx)
{
	_tar_x = tx;
}

void CameraView::setTargetY(double ty)
{
	_tar_y = ty;
}

void CameraView::setTargetZ(double tz)
{
	_tar_z = tz;
}

void CameraView::setAngle(double ax,double ay,double az)
{
	_ang_x = ax;
	_ang_y = ay;
	_ang_z = az;
}

void CameraView::setAngleX(double ax)
{
	_ang_x = ax;
}

void CameraView::setAngleY(double ay)
{
	_ang_y = ay;
}

void CameraView::setAngleZ(double az)
{
	_ang_z = az;
}

void CameraView::setAngleXY(double a)
{
	_angleXY = a;
}

void CameraView::setAngleXZ(double a)
{
	_angleXZ = a;
}

void CameraView::setZoom(double z)
{
	_zoom = z;
}

double CameraView::getPositionX()
{
	return _pos_x;
}

double CameraView::getPositionY()
{
	return _pos_y;
}

double CameraView::getPositionZ()
{
	return _pos_z;
}

double CameraView::getTargetX()
{
	return _tar_x;
}

double CameraView::getTargetY()
{
	return _tar_y;
}

double CameraView::getTargetZ()
{
	return _tar_z;
}

double CameraView::getAngleX()
{
	return _ang_x;
}

double CameraView::getAngleY()
{
	return _ang_y;
}

double CameraView::getAngleZ()
{
	return _ang_z;
}

double CameraView::getAngleXY()
{
	return _angleXY;
}

double CameraView::getAngleXZ()
{
	return _angleXZ;
}

double CameraView::getZoom()
{
	return _zoom;
}

void CameraView::move(Vector v)
{
	_pos_x += v.getX();
	_pos_y += v.getY();
	_pos_z += v.getZ();
}

void CameraView::events(bool left,double v_left,bool right,double v_right,bool up,double v_up,bool down,double v_down,bool fw,double v_fw,bool bw,double v_bw,bool speed,double v_speed)
{
	double max_vertical_angle = 89;

	double boost = 1.;
	if(speed)
		boost = v_speed;

	if(left)
		_angleXY += v_left * boost;
	if(right)
		_angleXY -= v_right * boost;

	if(up)
		_angleXZ += v_up * boost;
	if(down)
		_angleXZ -= v_down * boost;

	if(fw)
		_zoom += v_fw * boost;
	if(bw)
		_zoom -= v_fw * boost;

	if(_angleXZ > max_vertical_angle)
		_angleXZ = max_vertical_angle;
	if(_angleXZ < -max_vertical_angle)
		_angleXZ = -max_vertical_angle;
}

void CameraView::events(bool left,double v_left,bool right,double v_right,bool up,double v_up,bool down,double v_down,bool fw,double v_fw,bool bw,double v_bw,bool speed,double v_speed,bool mv,Vector v_mv,double mv_ratio)
{
	events(left,v_left,right,v_right,up,v_up,down,v_down,fw,v_fw,bw,v_bw,speed,v_speed);
}