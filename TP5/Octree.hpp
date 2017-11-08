#ifndef OCTREE_H_INCLUDED
#define OCTREE_H_INCLUDED

#include "Point.h"
#include "function.h"



class Octree{

	private:
	
		
		Point center;
		Octree *origin; //point de départ de l'arbre
		double resolution;
		double lenght;
		int drawValue;
		Octree* childs;
		int nbChilds;
		
		float r;
		float g;
		float b;

	public:
		Octree( );
		Octree(Point c,double l,double res);
		Octree(Point c, Octree *o,double l,double res);
		~Octree();
		
		void displaySphereVolumic(double rayon);
		void displayCylinderVolumic(Point axisOrigin,Vector axisVector,double rayon);
		void displayIntersectionSphereCylinder(Point centerSphere, double rayonSphere, Point axisOriginCylinder, Vector axisVectorCylinder, double  rayonCylinder, double resolution);
		void displaySoustractionSphereCylinder(Point centerSphere, double rayonSphere, Point axisOriginCylinder, Vector axisVectorCylinder, double  rayonCylinder, double resolution);
		void displayUnionSphereCylinder(Point centerSphere, double rayonSphere, Point axisOriginCylinder, Vector axisVectorCylinder, double  rayonCylinder, double resolution);

		
		
		void drawOctree();
		void divide();


};


#endif