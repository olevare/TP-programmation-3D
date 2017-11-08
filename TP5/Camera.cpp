#include "Camera.h"

Camera::Camera()
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
}

Camera::Camera(double px,double py,double pz,double tx,double ty,double tz)
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
}

Camera::Camera(double px,double py,double pz,double tx,double ty,double tz,double ax,double ay,double az)
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
}


void Camera::draw()
{
	gluLookAt(_pos_x,_pos_y,_pos_z,_tar_x,_tar_y,_tar_z,_ang_x,_ang_y,_ang_z);
}


void Camera::setPosition(double px,double py,double pz)
{
	_pos_x = px;
	_pos_y = py;
	_pos_z = pz;
}

void Camera::setPositionX(double px)
{
	_pos_x = px;
}

void Camera::setPositionY(double py)
{
	_pos_y = py;
}

void Camera::setPositionZ(double pz)
{
	_pos_z = pz;
}

void Camera::setTarget(double tx,double ty,double tz)
{
	_tar_x = tx;
	_tar_y = ty;
	_tar_z = tz;
}

void Camera::setTargetX(double tx)
{
	_tar_x = tx;
}

void Camera::setTargetY(double ty)
{
	_tar_y = ty;
}

void Camera::setTargetZ(double tz)
{
	_tar_z = tz;
}

void Camera::setAngle(double ax,double ay,double az)
{
	_ang_x = ax;
	_ang_y = ay;
	_ang_z = az;
}

void Camera::setAngleX(double ax)
{
	_ang_x = ax;
}

void Camera::setAngleY(double ay)
{
	_ang_y = ay;
}

void Camera::setAngleZ(double az)
{
	_ang_z = az;
}

double Camera::getPositionX()
{
	return _pos_x;
}

double Camera::getPositionY()
{
	return _pos_y;
}

double Camera::getPositionZ()
{
	return _pos_z;
}

double Camera::getTargetX()
{
	return _tar_x;
}

double Camera::getTargetY()
{
	return _tar_y;
}

double Camera::getTargetZ()
{
	return _tar_z;
}

double Camera::getAngleX()
{
	return _ang_x;
}

double Camera::getAngleY()
{
	return _ang_y;
}

double Camera::getAngleZ()
{
	return _ang_z;
}

void Camera::move(Vector v)
{
	_pos_x += v.getX();
	_pos_y += v.getY();
	_pos_z += v.getZ();
}

void Camera::setZoom(double z)
{

}

void Camera::setAngleXY(double a)
{

}

void Camera::setAngleXZ(double a)
{

}

double Camera::getAngleXY()
{
	
}

double Camera::getAngleXZ()
{
	
}

double Camera::getZoom()
{
	
}

void Camera::events(bool left,double v_left,bool right,double v_right,bool up,double v_up,bool down,double v_down,bool fw,double v_fw,bool bw,double v_bw,bool speed,double v_speed)
{

}

void Camera::events(bool left,double v_left,bool right,double v_right,bool up,double v_up,bool down,double v_down,bool fw,double v_fw,bool bw,double v_bw,bool speed,double v_speed,bool mv,Vector v_mv,double mv_ratio)
{
	
}