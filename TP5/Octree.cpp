#include "Octree.hpp"
#include "math.h"
#include <iostream>

static int nbOctree=0;
Octree::Octree( ){}

Octree::Octree(Point c, double l, double res)
{
	nbOctree=1;

	center = c, lenght = l, resolution = res;
	nbChilds = 8;
	drawValue = 1;					
	origin = this;

	childs = NULL;
}

Octree::Octree(Point c, Octree *o, double l, double res)
{
	nbOctree++;
	center = c, lenght = l, origin = o, resolution = res;
	nbChilds = 8;
	drawValue = 1;					

	childs = NULL;
}

Octree::~Octree( )
{
	delete [] childs;
}

void Octree::displaySphereVolumic(double rayon)
{
	r = (center.getX() + rayon)/(rayon*2);
	g = (center.getY() + rayon)/(rayon*2);
	b = (center.getZ() + rayon)/(rayon*2);

	//calcule de la distance entre le centre et le centre de l'octree
	double dist = distance(center,origin->center);

	if( abs (dist - rayon) <= sqrt(lenght/2.*lenght/2. + lenght/2.*lenght/2.)  )
	{
		//si la longeur de l'octree est trop longue
		if( lenght/2. > resolution )
		{
			//on divise l'octree en 8
			divide();
			//pour tous les sous-octree
			for(int i = 0; i < nbChilds; i++){
				childs[i].displaySphereVolumic(rayon);
			}
		}
		//sinon on le dessine
		else
		{
			drawValue = 1;
		}
	}
	//si la distance de l'octree est inférieur au rayon on le dessine
	else if(dist < rayon )
	{
		drawValue = 1;
	}
	//sinon on le dessine pas
	else
	{
		drawValue = -1;
	}
}

void Octree::displayCylinderVolumic(Point axisOrigin, Vector axisVector, double rayon)
{
	r = (center.getX() + rayon)/(rayon*2);
	g = (center.getY() + rayon)/(rayon*2);
	b = (center.getZ() + rayon)/(rayon*2);
	
	Vector BA(axisOrigin, center);

	double d = ( BA.vectoriel(axisVector) ).norme() / axisVector.norme();
	
	double hyp = distance(axisOrigin,center);
	

	if(hyp*hyp - d*d > rayon * 8 )
	{
		if(lenght/2 > resolution)
		{
			divide();
			for(int i = 0; i < nbChilds; i++)
				childs[i].displayCylinderVolumic(axisOrigin, axisVector, rayon);
		}
		else
			drawValue = -1;			
    }
    else if(abs(d - rayon)  <= sqrt(lenght/2.*lenght/2. + lenght/2.*lenght/2.) && lenght/2 > resolution ) 
	{
		divide();
		for(int i = 0; i < nbChilds; i++)
			childs[i].displayCylinderVolumic(axisOrigin, axisVector, rayon);

	}
	else if(d+sqrt(lenght/2.*lenght/2. + lenght/2.*lenght/2.) < rayon)
	{
		double step = lenght/2;
		for(int i = 0; i < 8; i++)
		{
			double offsetX = (((i & 1) == 0) ? step : -step);
			double offsetY = (((i & 2) == 0) ? step : -step);
			double offsetZ = (((i & 4) == 0) ? step : -step);
			Point p(offsetX,offsetY,offsetZ);
			
			Vector _BA(axisOrigin, center+p);

			double _d = ( BA.vectoriel(axisVector) ).norme() / axisVector.norme();
			
			double _hyp = distance(axisOrigin,center+p);

			
			if(_hyp*_hyp - _d*_d   > rayon * 8  && lenght/2 > resolution)
			{
				divide();
				for(int i = 0; i < nbChilds; i++)
					childs[i].displayCylinderVolumic(axisOrigin, axisVector, rayon);
				break;
			}
			else
			{
				drawValue = 1;
			}
		}

	}
	else
	{
		drawValue = -1;
	}
}


void Octree::displayIntersectionSphereCylinder(Point centerSphere, double rayonSphere, Point axisOriginCylinder, Vector axisVectorCylinder, double  rayonCylinder, double resolution)
{
	r = (center.getX() + rayonSphere)/(rayonSphere*2);
	g = (center.getY() + rayonSphere)/(rayonSphere*2);
	b = (center.getZ() + rayonSphere)/(rayonSphere*2);
	
	double dist = distance(center, centerSphere);
		
	Vector BA(axisOriginCylinder, center);
	double d = ( BA.vectoriel(axisVectorCylinder) ).norme() / axisVectorCylinder.norme();
	
	double hyp = distance(axisOriginCylinder, center);
	/*cylindre*/
	if(hyp*hyp - d*d > rayonCylinder * 8 )
	{
		if(lenght/2 > resolution)
		{
			drawValue = 0;
		}
		else
			drawValue = -1;
	}
	else if(abs(d - rayonCylinder)  <= sqrt(lenght/2.*lenght/2. + lenght/2.*lenght/2.) && lenght/2 > resolution ) 
	{
		drawValue = 0;
	}
	else if(d+sqrt(lenght/2.*lenght/2. + lenght/2.*lenght/2.) < rayonCylinder)
	{
		double step = lenght/2;
		for(int i = 0; i < 8; i++)
		{
			double offsetX = (((i & 1) == 0) ? step : -step);
			double offsetY = (((i & 2) == 0) ? step : -step);
			double offsetZ = (((i & 4) == 0) ? step : -step);
			Point p(offsetX,offsetY,offsetZ);
			
			Vector _BA(axisOriginCylinder, center+p);
			double _d = ( BA.vectoriel(axisVectorCylinder) ).norme() / axisVectorCylinder.norme();
			
			double _hyp = distance(axisOriginCylinder, center+p);

			
			if(_hyp*_hyp - _d*_d   > rayonCylinder * 8  && lenght/2 > resolution)
			{
				drawValue = 0;
				break;
			}
			else
			{
				drawValue = 1;
			}
		}

	}
	else
	{
		drawValue = -1;
	}
	/*Sphere*/
	if(drawValue != -1){
		if( abs (dist - rayonSphere) <= sqrt(lenght/2.*lenght/2. + lenght/2.*lenght/2.)  )
		{
			if( lenght/2 > resolution )
			{
				drawValue = 0;	
			}
			else if(drawValue == 1)
			{
				drawValue = 1;
			}
		}
		else if(dist < rayonSphere)
		{
			if(drawValue == 0)
			{
				drawValue = 0;
			}
			else
			{
				drawValue = 1;
			}
		
		}
		else
		{
			drawValue = -1;
		}
	}
	
	if(drawValue == 0)
	{
		divide();
		for(int i = 0; i < nbChilds; i++)
			childs[i].displayIntersectionSphereCylinder(centerSphere, rayonSphere, axisOriginCylinder, axisVectorCylinder, rayonCylinder, resolution);		
	}
}


void Octree::displaySoustractionSphereCylinder(Point centerSphere, double rayonSphere, Point axisOriginCylinder, Vector axisVectorCylinder, double  rayonCylinder, double resolution)
{
	r = (center.getX() + rayonSphere)/(rayonSphere*2);
	g = (center.getY() + rayonSphere)/(rayonSphere*2);
	b = (center.getZ() + rayonSphere)/(rayonSphere*2);
	
	double dist = distance(center, centerSphere);
		
	Vector BA(axisOriginCylinder, center);
	double d = ( BA.vectoriel(axisVectorCylinder) ).norme() / axisVectorCylinder.norme();
	
	double hyp = distance(axisOriginCylinder, center);
	
	if(hyp*hyp - d*d > rayonCylinder * 8)
	{
		if(lenght/2 > resolution)
		{
			drawValue = 0;
		}
		else
			drawValue = -1;
	}
	else if(abs(d - rayonCylinder)  <= sqrt(lenght/2.*lenght/2. + lenght/2.*lenght/2.) && lenght/2 > resolution ) 
	{
		drawValue = 0;
	}
	else if(d+sqrt(lenght/2.*lenght/2. + lenght/2.*lenght/2.) < rayonCylinder){
		double step = lenght/2;
		for(int i = 0; i < 8; i++)
		{
			double offsetX = (((i & 1) == 0) ? step : -step);
			double offsetY = (((i & 2) == 0) ? step : -step);
			double offsetZ = (((i & 4) == 0) ? step : -step);
			Point p(offsetX,offsetY,offsetZ);

			Vector _BA(axisOriginCylinder, center+p);
			double _d = ( BA.vectoriel(axisVectorCylinder) ).norme() / axisVectorCylinder.norme();
			
			double _hyp = distance(axisOriginCylinder, center+p);

			if(_hyp*_hyp - _d*_d   > rayonCylinder * 8  && lenght/2 > resolution)
			{
				drawValue = 0;
				break;
			}
			else
			{
				drawValue = 1;
			}
		}

	}
	else
	{
		drawValue = -1;
	}

	if(drawValue != 1){
		if( abs (dist - rayonSphere) <= sqrt(lenght/2.*lenght/2. + lenght/2.*lenght/2.)  )
		{
			if( lenght/2 > resolution )
			{
				drawValue = 0;	
			}
			if(drawValue == -1)
				drawValue = 1;
			
		}
		else if(dist < rayonSphere)
		{
			if(drawValue == -1)
				drawValue = 1;
		}
		else
		{
			drawValue = -1;
		}
	}
	else
	{
		drawValue = -1;
	}
		
	if(drawValue == 0)
	{
		divide();
		for(int i = 0; i < nbChilds; i++)
			childs[i].displaySoustractionSphereCylinder(centerSphere, rayonSphere, axisOriginCylinder, axisVectorCylinder, rayonCylinder, resolution);		
	}
}



void Octree::displayUnionSphereCylinder(Point centerSphere, double rayonSphere, Point axisOriginCylinder, Vector axisVectorCylinder, double  rayonCylinder, double resolution)
{
	r = (center.getX() + rayonSphere)/(rayonSphere*2);
	g = (center.getY() + rayonSphere)/(rayonSphere*2);
	b = (center.getZ() + rayonSphere)/(rayonSphere*2);
	
	double dist = distance(center, centerSphere);
		
	Vector BA(axisOriginCylinder, center);
	double d = ( BA.vectoriel(axisVectorCylinder) ).norme() / axisVectorCylinder.norme();
	
	double hyp = distance(axisOriginCylinder, center);
	
	if(hyp*hyp - d*d > rayonCylinder * 8)
	{
		if(lenght/2 > resolution)
		{
			drawValue = 0;
		}
		else
			drawValue = -1;
	}
	else if(abs(d - rayonCylinder)  <= sqrt(lenght/2.*lenght/2. + lenght/2.*lenght/2.) && lenght/2 > resolution ) 
	{
		drawValue = 0;
	}
	else if(d+sqrt(lenght/2.*lenght/2. + lenght/2.*lenght/2.) < rayonCylinder)
	{
		double step = lenght/2;
		for(int i = 0; i < 8; i++)
		{
			double offsetX = (((i & 1) == 0) ? step : -step);
			double offsetY = (((i & 2) == 0) ? step : -step);
			double offsetZ = (((i & 4) == 0) ? step : -step);
			Point p(offsetX,offsetY,offsetZ);
			
			Vector _BA(axisOriginCylinder, center+p);
			double _d = ( BA.vectoriel(axisVectorCylinder) ).norme() / axisVectorCylinder.norme();
			
			double _hyp = distance(axisOriginCylinder, center+p);
				
			if(_hyp*_hyp - _d*_d   > rayonCylinder * 8  && lenght/2 > resolution)
			{
				drawValue = 0;
				break;
			}
			else
			{
				drawValue = 1;
			}
		}

	}
	else
	{
		drawValue = -1;
	}
	
	/*Check sphere*/
	if( abs (dist - rayonSphere) <= sqrt(lenght/2.*lenght/2. + lenght/2.*lenght/2.)  )
	{
		if( lenght/2 > resolution )
		{
			drawValue = 0;	
		}
		if(drawValue != 0)
			drawValue = 1;
		
	}
	else if(dist < rayonSphere)
	{
		if(drawValue != 0)
			drawValue = 1;
	}
	
	if(drawValue == 0)
	{
		divide();
		for(int i = 0; i < nbChilds; i++)
			childs[i].displayUnionSphereCylinder(centerSphere, rayonSphere, axisOriginCylinder, axisVectorCylinder, rayonCylinder, resolution);		
	}
}



void Octree::drawOctree()
{
	if(drawValue > 0){
		glColor3f(r,g,b);
		displayVoxel(center,lenght);
	}
		
	if(childs != NULL){
		for(int i = 0; i < nbChilds; i++)
			childs[i].drawOctree();
	}	
}

void Octree::divide()
{
	childs = new Octree[nbChilds];
	drawValue = -1;
	double step = lenght/4;
	for(int i = 0; i < nbChilds; i++)
	{

		double offsetX = (((i & 1) == 0) ? step : -step);
        double offsetY = (((i & 2) == 0) ? step : -step);
        double offsetZ = (((i & 4) == 0) ? step : -step);
		
		Point p(offsetX,offsetY,offsetZ);
		Octree o(center + p ,origin,lenght/2.,resolution);
		childs[i] = o;
	}
}
