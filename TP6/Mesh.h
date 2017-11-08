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
	
	Point minVertex;
	Point maxVertex;

	Mesh();
	~Mesh();

	bool loadOffFile(std::string fileName);
	void initNormalVertex();
	
	void drawMesh();

};

#endif