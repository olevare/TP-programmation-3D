#include "Mesh.h"
#include <iostream>
#include <math.h>
#include <climits>
#include <fstream>
#include <vector>
#include "Fonction.h"


Mesh::Mesh()
{
	nbPoint = 0;
	nbTriangle = 0;
	nbEdge = 0;

	//position des points en x, y et z
	pointsArray = NULL;

	//indice des points de la face
	indiceArray = NULL;

	//normale des sommets
	normalArray = NULL;

	//indice des points des arrètes
	edgesArray = NULL;

	diedreArray = NULL;
}

Mesh::~Mesh()
{
	if(pointsArray)
		delete [] pointsArray;
	if(indiceArray)
		delete [] indiceArray;
	if(normalArray)
		delete [] normalArray;
	if(edgesArray)
		delete [] edgesArray;
	if(diedreArray)
		delete [] diedreArray;
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
	initNormalVertex();

	return true;
}

void Mesh::initNormalVertex()
{
	if(normalArray)
		delete [] normalArray;

	normalArray = new double[nbPoint*3];

	//initialisation du tableau
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
		
		//somme des normales des faces contenant le sommet
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

	//moyenne des normales des faces
	for(int i = 0; i < nbPoint; i++)
	{
		double norme = sqrt(normalArray[i*3]*normalArray[i*3] + normalArray[i*3+1]*normalArray[i*3+1] + normalArray[i*3+2]*normalArray[i*3+2]);

		normalArray[i*3] = normalArray[i*3]/norme;
		normalArray[i*3+1] = normalArray[i*3+1]/norme;
		normalArray[i*3+2] = normalArray[i*3+2]/norme;
	}	

}

void Mesh::initEdgesArray()
{
	if(edgesArray)
		delete []edgesArray;

	nbEdge = nbTriangle + nbPoint - 2;

	edgesArray = new int[nbEdge*2];

	int cursor = 0;

	for(int i = 0; i < nbTriangle; i++)
	{		
		int j;
		bool e1 = false;
		bool e2 = false;
		bool e3 = false;
		
		for(j = 0; j < cursor; j++)
		{
			if(edgesArray[j*2] == indiceArray[i*3] && edgesArray[j*2+1] == indiceArray[i*3+1] || edgesArray[j*2 + 1] == indiceArray[i*3] && edgesArray[j*2]  == indiceArray[i*3+1])
				e1=true;
			
			if(edgesArray[j*2] == indiceArray[i*3] && edgesArray[j*2+1] == indiceArray[i*3+2] || edgesArray[j*2 + 1] == indiceArray[i*3] && edgesArray[j*2]  == indiceArray[i*3+2])
				e2=true;

			if(edgesArray[j*2] == indiceArray[i*3+2] && edgesArray[j*2+1] == indiceArray[i*3+1] || edgesArray[j*2 + 1] == indiceArray[i*3+2] && edgesArray[j*2]  == indiceArray[i*3+1])
				e3=true;
		}
		
		if(!e1)
		{
			edgesArray[cursor*2] = indiceArray[i*3];
			edgesArray[cursor*2+1] = indiceArray[i*3 + 1];
			cursor++;
		}
		if(cursor > nbEdge)
			break;
		if(!e2)
		{
			edgesArray[cursor*2] = indiceArray[i*3];
			edgesArray[cursor*2+1] = indiceArray[i*3 + 2];

			cursor++;
		}
		if(cursor > nbEdge)
			break;
		if(!e3)
		{
			edgesArray[cursor*2] = indiceArray[i*3 + 1];
			edgesArray[cursor*2+1] = indiceArray[i*3 + 2];
			cursor++;
		}
		if(cursor > nbEdge)
			break;
	}
}

void Mesh::initDiedreArray()
{
	initEdgesArray();
	
	if(diedreArray)
		delete [] diedreArray;
	
	diedreArray = new double[nbEdge];	
	
	for(int i = 0; i < nbEdge; i++)
	{		
		int index1 = -1;
		int index2 = -1;
		for(int j = 0; j < nbTriangle; j++)
		{
			if(edgesArray[i*2] == indiceArray[j*3] && edgesArray[i*2+1] == indiceArray[j*3+1] || edgesArray[i*2 + 1] == indiceArray[j*3] && edgesArray[i*2]  == indiceArray[j*3+1]
				|| edgesArray[i*2] == indiceArray[j*3] && edgesArray[i*2+1] == indiceArray[j*3+2] || edgesArray[i*2 + 1] == indiceArray[j*3] && edgesArray[i*2]  == indiceArray[j*3+2]
				|| edgesArray[i*2] == indiceArray[j*3+2] && edgesArray[i*2+1] == indiceArray[j*3+1] || edgesArray[i*2 + 1] == indiceArray[j*3+2] && edgesArray[i*2]  == indiceArray[j*3+1])
			{
				if(index1 == -1)
					index1 = j;
				else
				{
					index2=j;
					break;
				}
			}
		}
		if(index2 == -1)
			diedreArray[i]=0;

		else
		{
			Point p1 = Point(pointsArray[indiceArray[index1*3]*3],pointsArray[indiceArray[index1*3]*3+1],pointsArray[indiceArray[index1*3]*3+2]);
			Point p2 = Point(pointsArray[indiceArray[index1*3+1]*3],pointsArray[indiceArray[index1*3+1]*3+1],pointsArray[indiceArray[index1*3+1]*3+2]);
			Point p3 = Point(pointsArray[indiceArray[index1*3+2]*3],pointsArray[indiceArray[index1*3+2]*3+1],pointsArray[indiceArray[index1*3+2]*3+2]);

			Vector v1  = Vector(p2,p1);
			Vector v2  = Vector(p3,p1);

			Vector normal1 = v1.vectoriel(v2);

			p1 = Point(pointsArray[indiceArray[index2*3]*3],pointsArray[indiceArray[index2*3]*3+1],pointsArray[indiceArray[index2*3]*3+2]);
			p2 = Point(pointsArray[indiceArray[index2*3+1]*3],pointsArray[indiceArray[index2*3+1]*3+1],pointsArray[indiceArray[index2*3+1]*3+2]);
			p3 = Point(pointsArray[indiceArray[index2*3+2]*3],pointsArray[indiceArray[index2*3+2]*3+1],pointsArray[indiceArray[index2*3+2]*3+2]);

			v1  = Vector(p2,p1);
			v2  = Vector(p3,p1);
			Vector normal2 = v1.vectoriel(v2);	

			diedreArray[i] = M_PI - normal1.angle(normal2);
		}	
	}
}

void Mesh::buildCylinder(double rayon, double hauteur, int nbMeridiens)
{
	//+2 égale les sommets 
	nbPoint = nbMeridiens*2 + 2;
	
	nbTriangle = (nbMeridiens * 4);

	if(indiceArray)
		delete [] indiceArray;

	if(pointsArray)
		delete [] pointsArray;

    pointsArray = new double[nbPoint*3];
    indiceArray = new int[nbTriangle*3];

    //pour connaitre la position de la caméra plus tard
	double DBL_MIN = INT_MIN;
	double DBL_MAX = INT_MAX;

	maxVertex = Point(DBL_MIN,DBL_MIN,DBL_MIN);
	minVertex = Point(DBL_MAX,DBL_MAX,DBL_MAX);
	
	//cylindre inférieur (sommet)
	pointsArray[(nbPoint-2)*3] = 0;
	pointsArray[(nbPoint-2)*3+1] = -hauteur/2;
	pointsArray[(nbPoint-2)*3+2] = 0;

	//cylindre supérieur (sommet)
	pointsArray[(nbPoint-1)*3] = 0;
	pointsArray[(nbPoint-1)*3+1] = hauteur/2;
	pointsArray[(nbPoint-1)*3+2] = 0;

	//pour tous les méridiens
    for(int i = 0; i < nbMeridiens ; i++)
    {
    	//calcule de x, y et z
      	double angle = 2 * M_PI * i / (nbMeridiens); 
	
      	double x = rayon * cos(angle);
      	double y = -hauteur/2;
     	double z = rayon * sin(angle); 

     	//on enregistre les points
		pointsArray[i*3] = x;
		pointsArray[i*3+1] = y;
		pointsArray[i*3+2] = z;

		pointsArray[(i+nbMeridiens)*3] = x;
		pointsArray[(i+nbMeridiens)*3+1] = -y;
		pointsArray[(i+nbMeridiens)*3+2] = z;

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

		if(-y > maxVertex.getY())
			maxVertex.setY(-y);
		if(-y < minVertex.getY())
			minVertex.setY(-y);
    }
	
	int cursor = 0;
	int cursor1 = 0;
	int cursor2 = nbMeridiens;
	int i;

	//pour tous les triangles
    for(i = 0; i < nbTriangle-2; i++)
    {
    	//triangle du dessous
		if(cursor < nbMeridiens)
		{
			if(cursor == nbMeridiens-1)
			{
				indiceArray[i*3] = (nbPoint-2);
				indiceArray[i*3+1] = cursor;
				indiceArray[i*3+2] = 0;
			}
			else
			{
				indiceArray[i*3] = (nbPoint-2);
				indiceArray[i*3+1] = cursor;
				indiceArray[i*3+2] = (cursor+1);
			}
			cursor++;
		}
		//triangle du dessus
		else if(cursor < nbMeridiens*2)
		{
			if(cursor == nbMeridiens*2-1)
			{
				indiceArray[i*3] = nbMeridiens;
				indiceArray[i*3+1] = cursor;
				indiceArray[i*3+2] = (nbPoint-1);
			}
			else
			{
				indiceArray[i*3] = (cursor+1);
				indiceArray[i*3+1] = cursor;
				indiceArray[i*3+2] = (nbPoint-1);
			}
			cursor++;
		}
		else
		{
			//triangle du coté
			if(cursor1 == cursor2-nbMeridiens)
			{
				indiceArray[i*3] = cursor1;
				indiceArray[i*3+1] = cursor2;
				indiceArray[i*3+2] = cursor1+1;
				cursor1++;	
			}
			else
			{
				indiceArray[i*3] = cursor1;
				indiceArray[i*3+1] = cursor2;
				indiceArray[i*3+2] = cursor2+1;
				cursor2++;
			}
		}
    }

	indiceArray[(nbTriangle-1)*3] = 0;
	indiceArray[(nbTriangle-1)*3+1] = nbMeridiens*2-1;
	indiceArray[(nbTriangle-1)*3+2] = nbMeridiens;

	indiceArray[(nbTriangle-2)*3] = nbMeridiens-1;
	indiceArray[(nbTriangle-2)*3+1] = nbMeridiens*2-1;
	indiceArray[(nbTriangle-2)*3+2] = 0;

	//pour les normales
	initNormalVertex();
}

void Mesh::buildSphere(double rayon,int nbParalleles, int nbMeridiens)
{
	nbPoint = nbParalleles * nbMeridiens;
	nbTriangle = nbParalleles * nbMeridiens * 2 - nbMeridiens*2;
	
	if(indiceArray)
		delete [] indiceArray;
	if(pointsArray)
		delete [] pointsArray;

    pointsArray = new double[nbPoint*3];
    indiceArray = new int[nbTriangle*3];
	normalArray = new double[nbPoint*3]; 
	
	int iter = 0;
	int m;
	int p;
	
    for(p = 0; p < nbParalleles; p++)
    {
    	for(m = 0; m < nbMeridiens; m++)
    	{
			double theta = (double)m/(double)(nbMeridiens-1) * M_PI * 2.;
			double phi = (double)p/(double)(nbParalleles-1) * M_PI - M_PI/2.;
		
        	double const z = cos(phi)*cos(theta);
        	double const y = sin(theta)*cos(phi);
        	double const x = sin(phi);

        	pointsArray[iter *3] = x * rayon;
        	pointsArray[iter *3+1] = y * rayon;
        	pointsArray[iter *3+2] = z * rayon;

			iter ++;
		
		if(x*rayon > maxVertex.getX())
			maxVertex.setX(x*rayon);
		if(y*rayon > maxVertex.getY())
			maxVertex.setY(y*rayon);
		if(z*rayon > maxVertex.getZ())
			maxVertex.setZ(z*rayon);
		
		if(x*rayon < minVertex.getX())
			minVertex.setX(x*rayon);
		if(y*rayon < minVertex.getY())
			minVertex.setY(y*rayon);
		if(z*rayon < minVertex.getZ())
			minVertex.setZ(z*rayon);
		}
    }

	iter = 0;
	for(p = 0; p < nbParalleles; p++)
	{
		for(m = 0; m < nbMeridiens; m++)
		{
			if(p == 0)
			{
				//triangle du dessous
				if(m == nbMeridiens-1)
				{
					indiceArray[iter *3] = p * nbMeridiens + m;
					indiceArray[iter *3+1] = (p+1) * nbMeridiens + m;
					indiceArray[iter *3+2] = (p+1) * nbMeridiens + 0;
				}
				else
				{
					indiceArray[iter *3] = p * nbMeridiens + m;
					indiceArray[iter *3+1] = (p+1) * nbMeridiens + m;
					indiceArray[iter *3+2] = (p+1) * nbMeridiens + (m+1);
				}
				iter++;

			}
			else if(p == nbParalleles-1)
			{
				if(m == nbMeridiens-1)
				{
					indiceArray[iter *3] = p * nbMeridiens + m;
					indiceArray[iter *3+1] = 0 * nbMeridiens + 0;
					indiceArray[iter *3+2] = p * nbMeridiens + 0;
				}
				else
				{
					indiceArray[iter *3] = p * nbMeridiens + m;
					indiceArray[iter *3+1] = 0 * nbMeridiens + (m+1);
					indiceArray[iter *3+2] = p * nbMeridiens + (m+1);
				}
			iter++;

			}
			else if(m == nbMeridiens-1)
			{
				indiceArray[iter *3] = p * nbMeridiens + m;
				indiceArray[iter *3+1] = (p+1) * nbMeridiens + 0;
				indiceArray[iter *3+2] = p * nbMeridiens + 0;
		
				iter++;

				indiceArray[iter *3] = p * nbMeridiens + m;
				indiceArray[iter *3+1] = (p+1) * nbMeridiens + m;
				indiceArray[iter *3+2] = (p+1) * nbMeridiens + 0;
		
				iter++;
			}
			else
			{
				indiceArray[iter *3] = p * nbMeridiens + m;
				indiceArray[iter *3+1] = (p+1) * nbMeridiens + (m+1);
				indiceArray[iter *3+2] = p * nbMeridiens + (m+1);
		
				iter++;

				indiceArray[iter *3] = p * nbMeridiens + m;
				indiceArray[iter *3+1] = (p+1) * nbMeridiens + m;
				indiceArray[iter *3+2] = (p+1) * nbMeridiens + (m+1);
		
				iter++;
			}
		}
	}

	//pour les normales
	initNormalVertex();
}

void Mesh::fusion(int point1, int point2)
{	
	//pour tous les triangles
	for(int i = 0; i < nbTriangle*3; i++)
	{
		//si on recontre le point a fusionner on le remplace
		if(indiceArray[i] == point1)
			indiceArray[i] = point2;
	}
}

void Mesh::simplificationParGrille(double size, double res, std::vector<Point> &v)
{
	std::vector<int> c;

	int cpt = 0;
	int max = pow((int)(size*2. / (res*2.)),2);

	//pour tous les X
	for(double i = -size; i < size; i += res*2)
	{
		//pour tous les Y
		for(double j = -size; j < size; j += res*2)
		{
			//compteur pourcentage
			std::cout << 100*cpt/max << "\% \r";
			cpt++;

			//pour tous les Z
			for(double k = -size; k < size; k += res*2)
			{
				//on nettoie le vecteur
				c.clear();

				//pour tous les points
				for(int m = 0; m < nbPoint; m++)
				{
					//si le point se trouve dans le cube
					if(isInCube(i, j, k, res, Point(pointsArray[m*3], pointsArray[m*3+1], pointsArray[m*3+2])))
					{
						//on l'ajoute au vecteur
						c.push_back(m);
					};
				}

				//pour tous les points se trouvant dans le vecteur
				for(int m = 1; m < c.size(); m++)
				{
					//on les fusionne entre eux
					fusion(c[m], c[0]);
				}

				v.push_back(Point(i, j, k));
			}
		}
	}
}

bool Mesh::isInCube(double i, double j, double k, double res, Point pt)
{
	return (i-res <= pt.getX() && pt.getX() <= i+res && j-res <= pt.getY() && pt.getY() <= j+res && 
		k-res <= pt.getZ() && pt.getZ() <= k+res);
}

double Mesh::getDistance(int index, Point pointOnPlane)
{
	Point pointToProject(pointsArray[index*3],pointsArray[index*3+1],pointsArray[index*3+2]);

	return distance(pointOnPlane, pointToProject);
}

void Mesh::normalizeColorsArray(float maxDistance)
{
	if(maxDistance == 0)
		maxDistance = 1;
	
	for(int i = 0; i < nbPoint; i++)
	{
		colorsArray[i*3] = colorsArray[i*3+2]*0.586/maxDistance;
		colorsArray[i*3+1] = 0.449 + colorsArray[i*3+1]*0.633/maxDistance; 
		colorsArray[i*3+2] = .70 - colorsArray[i*3+1]*(.7000-0.633)/maxDistance;
	}
}

void Mesh::initColorDistance(Mesh& mesh)
{
	double distance;
	double minDistance;
	double maxDistance = -1;
	double planDistance;

	if(colorsArray)
		delete [] colorsArray;

	//on crée le tableau
	colorsArray = new float[nbPoint*3];
	
	clock_t time = clock();
	
	//pour tous les points de "simplifié"
	for(int i = 0; i < nbPoint; i++)
	{
		//on teste la distance du 1er point de "simplifié" avec le 1er point de "non simplifié"
		minDistance = getDistance(i, Point(mesh.pointsArray[0], mesh.pointsArray[1], mesh.pointsArray[2]));

		//pour tous les points de "non simplifié"
		for(int j = 1; j < mesh.nbPoint; j++)
		{
			//on teste la distance du 1er point de "simplifié" avec les autres points de "non simplifié"
			distance = getDistance(i, Point(mesh.pointsArray[j*3], mesh.pointsArray[j*3+1], mesh.pointsArray[j*3+2]));

			if(distance < minDistance)
				minDistance = distance;

			if(distance > maxDistance)
				maxDistance = distance;
		}
	}
	
	normalizeColorsArray(maxDistance);
	
	time = clock() - time;
	int ms = double(time)  / CLOCKS_PER_SEC * 1000;
	std::cout << "Couleur initialisée en " << ms << "ms" << std::endl;
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

void Mesh::drawEdgesDiedre(double angle)
{
	for(int i = 0; i < nbEdge; i++)
	{
		glLineWidth(8);		
		glColor3f(0.545, 0.000, 0.000);
		if(abs(diedreArray[i] * 180 / M_PI - angle ) < 1 )
			drawLine(Point(pointsArray[edgesArray[i*2]*3], pointsArray[edgesArray[i*2]*3+1], pointsArray[edgesArray[i*2]*3+2]), Point(pointsArray[edgesArray[i*2+1]*3], pointsArray[edgesArray[i*2+1]*3+1], pointsArray[edgesArray[i*2+1]*3+2]));
	}
}

void Mesh::drawImageGaussian(int rayon)
{
	int nbPM = 30;

	//crée la sphère
	Point ** sphere = getSphere(Point(0,0,0), rayon, nbPM, nbPM);

	//dessine la sphère
	for(int i = 0; i < nbPM-1; i++)
	{
		for(int j = 0; j< nbPM-1; j++)
		{
			glColor4f(0.6,0.6,0.6,0.6);
			drawQuad(sphere[i][j], sphere[i][j+1], sphere[i+1][j+1], sphere[i+1][j]);
		}
	}

	glColor3f(1,0,0);
	glPointSize(5);
	glBegin(GL_POINTS);

	for(int i = 0; i < nbPoint; i++)
		//translation du centre avec le normale du sommet
		glVertex3f(rayon*normalArray[i*3], 
		 	rayon*normalArray[i*3+1], rayon*normalArray[i*3+2]);

	glEnd();
}