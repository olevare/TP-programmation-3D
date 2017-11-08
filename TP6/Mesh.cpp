#include "Mesh.h"
#include <iostream>
#include <math.h>
#include <climits>
#include <fstream>


Mesh::Mesh()
{
	nbPoint = 0;
	nbTriangle = 0;
	nbEdge = 0;

	pointsArray = NULL;
	indiceArray = NULL;
	normalArray = NULL;
}

Mesh::~Mesh()
{
	if(pointsArray)
		delete [] pointsArray;
	if(indiceArray)
		delete [] indiceArray;
	if(normalArray)
		delete [] normalArray;
}

bool Mesh::loadOffFile(std::string fileName)
{
	//charge le fichier
	std::ifstream file(fileName.c_str());

	//ouvre le fichier
	if(!file.is_open())
		return false;

	//lis la première ligne
	std::string line;
	getline(file,line);

	//enregistre le nombre de points, de triangles, d'arètes
	file >> nbPoint >> nbTriangle >> nbEdge;

	indiceArray = new int[nbTriangle*3];
	pointsArray = new double[nbPoint*3];

	//pour enregistrer les coordonnées du point
	double x,y,z;

	//pour connaitre la position de la caméra plus tard
	double DBL_MIN = INT_MIN;
	double DBL_MAX = INT_MAX;

	maxVertex = Point(DBL_MIN,DBL_MIN,DBL_MIN);
	minVertex = Point(DBL_MAX,DBL_MAX,DBL_MAX);

	//pour tous les points
	for(int i = 0; i < nbPoint; i++)
	{
		//on enregistre x, y et z
		file >> x >> y >> z;

		pointsArray[i*3] = x;
		pointsArray[i*3+1] = y;
		pointsArray[i*3+2] = z;

		//regarde les coordonnées du points pour la position de la caméra plus tard
		if(x > maxVertex.getX())
			maxVertex.setX(x);
		if(y > maxVertex.getY())
			maxVertex.setY(y);
		if(z > maxVertex.getZ())
			maxVertex.setZ(z);
		if(x < minVertex.getX())
			minVertex.setX(x);
		if(y < minVertex.getY())
			minVertex.setY(y);
		if(z < minVertex.getZ())
			minVertex.setZ(z);
	}

	int nbFaceVertex;

	for(int i = 0; i < nbTriangle; i++)
	{
		file >> nbFaceVertex;

		if(nbFaceVertex != 3)		
			return false;

		file >> indiceArray[i*3] >> indiceArray[i*3+1] >> indiceArray[i*3+2];
	}

	//ferme le fichier
	file.close();

	//pour les normales
	//initNormalVertex();

	return true;
}

void Mesh::drawMesh()
{
	//pour les normales
	/*for(int i =0;i<nbPoint;++i)
	{
		drawLine(Point(pointsArray[i *3],
        pointsArray[i *3+1],
        pointsArray[i *3+2]),
		
		Point(pointsArray[i *3] + normalArray[i *3] * 2,
        pointsArray[i *3+1] + normalArray[i *3+1] * 2,
        pointsArray[i *3+2]+ normalArray[i *3+2] * 2));
	}*/

	//active le tableau de points
	glEnableClientState(GL_VERTEX_ARRAY);

	//active le tableau de normales
    //glEnableClientState(GL_NORMAL_ARRAY);

	//lis le tableau de points
    glVertexPointer(3, GL_DOUBLE, 0, pointsArray);

    //lis le tableau de normales
    //glNormalPointer(GL_DOUBLE, 0, normalArray);
    
    //on trace le maillage
    glDrawElements(GL_TRIANGLES, nbTriangle*3, GL_UNSIGNED_INT, indiceArray);

    //on desactive le tableau de points
	glDisableClientState(GL_VERTEX_ARRAY);

	//on desactive le tableau de normales
    //glDisableClientState(GL_NORMAL_ARRAY);
}















































void Mesh::initNormalVertex()
{
	if(normalArray) delete [] normalArray;
	normalArray = new double[nbPoint*3];

	for(int i = 0; i < nbPoint; i++)
	{
		normalArray[i*3] = 0;
		normalArray[i*3+1] = 0;
		normalArray[i*3+2] = 0;
	}

	for(int i = 0; i < nbTriangle; i++)
	{

		Point p1 = Point(pointsArray[indiceArray[i*3]*3],pointsArray[indiceArray[i*3]*3+1],pointsArray[indiceArray[i*3]*3+2]);
		Point p2 = Point(pointsArray[indiceArray[i*3+1]*3],pointsArray[indiceArray[i*3+1]*3+1],pointsArray[indiceArray[i*3+1]*3+2]);
		Point p3 = Point(pointsArray[indiceArray[i*3+2]*3],pointsArray[indiceArray[i*3+2]*3+1],pointsArray[indiceArray[i*3+2]*3+2]);

		Vector v1  = Vector(p2,p1);
		Vector v2  = Vector(p3,p1);

		Vector normal = v1.vectoriel(v2);
		
		Vector BA = Vector(p1,p2);
		Vector u = Vector(p3,p2);

		u.normalize();

		double h = (BA+u).norme() / u.norme();

		double area = distance(p2,p3)*h/2;
		

		normalArray[indiceArray[i*3]*3+0] += normal.getX()*area;
		normalArray[indiceArray[i*3]*3+1] += normal.getY()*area;
		normalArray[indiceArray[i*3]*3+2] += normal.getZ()*area;

		normalArray[indiceArray[i*3+1]*3+0] += normal.getX()*area;
		normalArray[indiceArray[i*3+1]*3+1] += normal.getY()*area;
		normalArray[indiceArray[i*3+1]*3+2] += normal.getZ()*area;

		normalArray[indiceArray[i*3+2]*3+0] += normal.getX()*area;
		normalArray[indiceArray[i*3+2]*3+1] += normal.getY()*area;
		normalArray[indiceArray[i*3+2]*3+2] += normal.getZ()*area;

	}

	for(int i = 0; i < nbPoint; i++)
	{
		double norme = sqrt(normalArray[i*3]*normalArray[i*3] + normalArray[i*3+1]*normalArray[i*3+1] + normalArray[i*3+2]*normalArray[i*3+2]);

		normalArray[i*3] = normalArray[i*3]/norme;
		normalArray[i*3+1] = normalArray[i*3+1]/norme;
		normalArray[i*3+2] = normalArray[i*3+2]/norme;
	}	

}