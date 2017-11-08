#ifndef MESH_H_INCLUDED
#define MESH_H_INCLUDED

#include <string>
#include "Point.h"
#include "Fonction.h"
#include <vector>
//#include "PointOctree.hpp"

class Mesh
{
	
public:
	int nbPoint;
	int nbTriangle;
	int nbEdge;
	
	double * pointsArray;
	int * indiceArray;	
	double *normalArray;
	int * edgesArray;
	double * diedreArray;

	float *colorsArray;
	
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

	void fusion(int point1,int point2);
	void simplificationParGrille(double size, double resolution, std::vector<Point> &v);
	bool isInCube(double i, double j, double k, double res, Point pt);

	double getDistance(int index, Point pointOnPlane);

	void normalizeColorsArray(float maxDistance);
	void initColorDistance(Mesh& mesh);

};

#endif