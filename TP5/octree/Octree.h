#ifndef OCTREE_H_INCLUDED
#define OCTREE_H_INCLUDED

#include "Point.h"
#include "Vector.h"
#include "freeglut-3.0.0/include/GL/glut.h"

class Octree
{
private:
		
	Point centre;

	double longeur;
	int draw;
	Octree *enfants;

	float r;
	float g;
	float b;

public:

	Octree();
	Octree(Point c, double l);

	void displayVoxel();
	void displaySphereVolumic(double rayon, double resolution, Point origine);
	void displayCylinderVolumic(double rayon, double resolution, Point origine, Vector v);

	void displayIntersectionSphereCylinder(Point OS, double rayonS, Point OC, Vector vC, double rayonC, double resolution);
	void displaySoustractionSphereCylinder(Point OS, double rayonS, Point OC, Vector vC, double rayonC, double resolution);
	void displayUnionSphereCylinder(Point OS, double rayonS, Point OC, Vector vC, double rayonC, double resolution);

	int intersectionVoxelSphere(double rayon, Point origine);
	int intersectionVoxelCylindre(double rayon, Point origine, Vector v);
	int intersectionVoxelSphereCylindre(Point OS, double rayonS, Point OC, Vector vC, double rayonC);
	int soustractionVoxelSphereCylindre(Point OS, double rayonS, Point OC, Vector vC, double rayonC);
	int unionVoxelSphereCylindre(Point OS, double rayonS, Point OC, Vector vC, double rayonC);

	void division();

	void drawOctree();

};

#endif