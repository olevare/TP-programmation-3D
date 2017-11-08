#include "CameraFreeFly.h"
#include <math.h>
CameraFreeFly::CameraFreeFly()
{
	_pos_x = -1;
	_pos_y = 0;
	_pos_z = 0;
	_tar_x = 0;
	_tar_y = 0;
	_tar_z = 0;
	_ang_x = 0;
	_ang_y = 0;
	_ang_z = 1;

	_angleXY = 0;
	_angleXZ = 0;
}

CameraFreeFly::CameraFreeFly(double px,double py,double pz,double tx,double ty,double tz)
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

	_angleXY = 90. + 180. / M_PI * (Vector(tx,ty,0)-Vector(px,py,0)).angle(Vector(1,0,0));
	_angleXZ = -180. / M_PI * (Vector(tx,0,tz)-Vector(px,0,pz)).angle(Vector(-1,0,0));
}

CameraFreeFly::CameraFreeFly(double px,double py,double pz,double tx,double ty,double tz,double ax,double ay,double az)
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

	_angleXY = 90. + 180. / M_PI * (Vector(tx,ty,0)-Vector(px,py,0)).angle(Vector(1,0,0));
	_angleXZ = -180. / M_PI * (Vector(tx,0,tz)-Vector(px,0,pz)).angle(Vector(-1,0,0));
}


void CameraFreeFly::draw()
{
	gluLookAt(_pos_x,_pos_y,_pos_z,_tar_x,_tar_y,_tar_z,_ang_x,_ang_y,_ang_z);
}


void CameraFreeFly::setPosition(double px,double py,double pz)
{
	_pos_x = px;
	_pos_y = py;
	_pos_z = pz;
}

void CameraFreeFly::setPositionX(double px)
{
	_pos_x = px;
}

void CameraFreeFly::setPositionY(double py)
{
	_pos_y = py;
}

void CameraFreeFly::setPositionZ(double pz)
{
	_pos_z = pz;
}

void CameraFreeFly::setTarget(double tx,double ty,double tz)
{
	_tar_x = tx;
	_tar_y = ty;
	_tar_z = tz;
}

void CameraFreeFly::setTargetX(double tx)
{
	_tar_x = tx;
}

void CameraFreeFly::setTargetY(double ty)
{
	_tar_y = ty;
}

void CameraFreeFly::setTargetZ(double tz)
{
	_tar_z = tz;
}

void CameraFreeFly::setAngle(double ax,double ay,double az)
{
	_ang_x = ax;
	_ang_y = ay;
	_ang_z = az;
}

void CameraFreeFly::setAngleX(double ax)
{
	_ang_x = ax;
}

void CameraFreeFly::setAngleY(double ay)
{
	_ang_y = ay;
}

void CameraFreeFly::setAngleZ(double az)
{
	_ang_z = az;
}

double CameraFreeFly::getPositionX()
{
	return _pos_x;
}

double CameraFreeFly::getPositionY()
{
	return _pos_y;
}

double CameraFreeFly::getPositionZ()
{
	return _pos_z;
}

double CameraFreeFly::getTargetX()
{
	return _tar_x;
}

double CameraFreeFly::getTargetY()
{
	return _tar_y;
}

double CameraFreeFly::getTargetZ()
{
	return _tar_z;
}

double CameraFreeFly::getAngleX()
{
	return _ang_x;
}

double CameraFreeFly::getAngleY()
{
	return _ang_y;
}

double CameraFreeFly::getAngleZ()
{
	return _ang_z;
}

void CameraFreeFly::move(Vector v)
{
	_pos_x += v.getX();
	_pos_y += v.getY();
	_pos_z += v.getZ();
}

void CameraFreeFly::events(bool left,double v_left,bool right,double v_right,bool up,double v_up,bool down,double v_down,bool fw,double v_fw,bool bw,double v_bw,bool speed,double v_speed)
{
	events(left,v_left,right,v_right,up,v_up,down,v_down,fw,v_fw,bw,v_bw,speed,v_speed,false,Vector(0,0,0),0.);
}

void CameraFreeFly::events(bool left,double v_left,bool right,double v_right,bool up,double v_up,bool down,double v_down,bool fw,double v_fw,bool bw,double v_bw,bool speed,double v_speed,bool mv,Vector v_mv,double mv_ratio)
{
	double max_vertical_angle = 89;

	double aXY,aXZ;

	Vector pos(_pos_x,_pos_y,_pos_z);
	Vector tar(_tar_x,_tar_y,_tar_z);

	Vector dir = (tar - pos);

	Vector d(dir.getX(),dir.getY(),dir.getZ());
	Vector n(-dir.getY(),dir.getX(),0);
	Vector z(0,0,1);

	d.normalize();
	n.normalize();

	double boost = 1.;
	if(speed)
		boost = v_speed;

	if(left)
	{
		pos = pos + n * v_left * boost;
		tar = tar + n * v_left * boost;
	}
	if(right)
	{
		pos = pos - n * v_right * boost;
		tar = tar - n * v_right * boost;
	}
	if(up)
	{
		pos = pos + d * v_up * boost;
		tar = tar + d * v_up * boost;
	}
	if(down)
	{
		pos = pos - d * v_down * boost;
		tar = tar - d * v_down * boost;
	}
	if(fw)
	{
		pos = pos + z * v_fw * boost;
		tar = tar + z * v_fw * boost;
	}
	if(bw)
	{
		pos = pos - z * v_bw * boost;
		tar = tar - z * v_bw * boost;
	}
	if(mv)
	{
		aXY = v_mv.getX() * mv_ratio * boost;
		aXZ = v_mv.getY() * mv_ratio * boost;

		if(aXZ + _angleXZ > max_vertical_angle)
			aXZ = max_vertical_angle - _angleXZ;

		if(aXZ + _angleXZ < -max_vertical_angle)
			aXZ = - max_vertical_angle - _angleXZ;


		tar.setX(pos.getX() + cos(-_angleXY * M_PI / 180.)   * cos(-_angleXZ * M_PI / 180.));
		tar.setY(pos.getY() + sin(-_angleXY * M_PI / 180.)   * cos(-_angleXZ * M_PI / 180.));
		tar.setZ(pos.getZ() + sin(-_angleXZ * M_PI / 180.)  );

		_angleXY += aXY;
		_angleXZ += aXZ;

		tar.setX(pos.getX() + cos(_angleXY * M_PI / 180.)   * cos(_angleXZ * M_PI / 180.));
		tar.setY(pos.getY() + sin(_angleXY * M_PI / 180.)   * cos(_angleXZ * M_PI / 180.));
		tar.setZ(pos.getZ() + sin(_angleXZ * M_PI / 180.)  );

		if(_angleXY > 360) 
			_angleXY-=360.;
		if(_angleXY < 0) 
			_angleXY+=360.;
	}

	_pos_x = pos.getX();
	_pos_y = pos.getY();
	_pos_z = pos.getZ();

	_tar_x = tar.getX();
	_tar_y = tar.getY();
	_tar_z = tar.getZ();
}