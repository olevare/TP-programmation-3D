#ifndef MESH_H_INCLUDED
#define MESH_H_INCLUDED

#include <string>
#include "Point.h"
#include "Fonction.h"



class Mesh{
	
public:
	int nbPoint;
	int nbTriangle;
	int nbEdge;
	
	double * pointsArray;
	int * indiceArray;	
	double *normalArray;
	int * edgesArray;
	double * diedreArray;
	
	Point minVertex;
	Point maxVertex;

	Mesh();
	~Mesh();

	bool loadOffFile(std::string fileName);
	void initNormalVertex();
	void initEdgesArray();
	void initDiedreArray();

	void buildCylinder(double rayon, double hauteur, int nbMeridiens);
	void buildSphere(double rayon,int parallele, int nbMeridiens);
	
	void drawMesh();
	void drawImageGaussian(int rayon);
	void drawEdgesDiedre(double angle);

};

#endif