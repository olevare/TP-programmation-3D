#include "Octree.h"
#include "math.h"

Octree::Octree( )
{}

Octree::Octree(Point c, double l)
{
	centre = c;
	longeur = l;
	draw = 1;
	enfants = NULL;		
}

void Octree::displaySphereVolumic(double rayon, double resolution, Point origine)
{
	r = (centre.getX() + rayon)/(rayon*2);
	g = (centre.getY() + rayon)/(rayon*2);
	b = (centre.getZ() + rayon)/(rayon*2);

	int inter = intersectionVoxelSphere(rayon, origine);
	//S'il est à l'intérieur
	if(inter == 1)
	{
		//si la résolution n'est pas atteinte
		if(longeur > resolution)
		{
			draw = -1;
			division();
			for(int i = 0 ; i < 8 ; i++)
				enfants[i].displaySphereVolumic(rayon, resolution, origine);
		}
	}
	//s'il n'est pas a l'intérieur
	else
	{
		//si la résolution n'est pas atteinte
		if(longeur > resolution)
		{
			draw = -1;
			division();
			for(int i = 0 ; i < 8 ; i++)
				enfants[i].displaySphereVolumic(rayon, resolution, origine);
		}
		else
			draw = -1;
	}
}

int Octree::intersectionVoxelSphere(double rayon, Point origine)
{
	//calcul si le voxel se trouve dans le cercle
	int d2 = (centre.getX() - origine.getX())*(centre.getX() - origine.getX()) 
			+ (centre.getY() - origine.getY())*(centre.getY() - origine.getY()) 
			+ (centre.getZ() - origine.getZ())*(centre.getZ() - origine.getZ());
	//si le point est dans le cercle
	if(d2 <= rayon*rayon)
		return 1;
	//s'il ne se trouve pas dans le cercle
	else
		return 0;
}

void Octree::displayCylinderVolumic(double rayon, double resolution, Point origine, Vector v)
{
	r = (centre.getX() + rayon)/(rayon*2);
	g = (centre.getY() + rayon)/(rayon*2);
	b = (centre.getZ() + rayon)/(rayon*2);

	int inter = intersectionVoxelCylindre(rayon, origine, v);

	//S'il est à l'intérieur
	if(inter == 1)
	{
		//si la résolution n'est pas atteinte
		if(longeur > resolution)
		{
			draw = -1;
			division();
			for(int i = 0 ; i < 8 ; i++)
				enfants[i].displayCylinderVolumic(rayon, resolution, origine, v);
		}
	}
	//s'il n'est pas a l'intérieur
	else
	{
		//si la résolution n'est pas atteinte
		if(longeur > resolution)
		{
			draw = -1;
			division();
			for(int i = 0 ; i < 8 ; i++)
				enfants[i].displayCylinderVolumic(rayon, resolution, origine, v);
		}
		else
			draw = -1;
	}
}

int Octree::intersectionVoxelCylindre(double rayon, Point origine, Vector v)
{
	Point axis(origine.getX() + v.getX(), origine.getY() + v.getY(), origine.getZ() + v.getZ());
	Point P;
	P = centre.ProjectOnLine(origine, axis);

	//Vérification distance centre < rayon
	double d = (P.getX() - centre.getX())*(P.getX() - centre.getX()) + 
			(P.getY() - centre.getY())*(P.getY() - centre.getY()) + 
			(P.getZ() - centre.getZ())*(P.getZ() - centre.getZ());

	//Verification de l'appartenance de P (projeté) au segment axisOaxis1
	Vector vAxisOP(P.getX() - origine.getX(), P.getY() - origine.getY(), P.getZ() - origine.getZ());
	Vector vPAxis1(axis.getX() - P.getX(), axis.getY() - P.getY(), axis.getZ() - P.getZ());
	double AxisOP = vAxisOP.Scalar(v);
	double PAxis1 = vPAxis1.Scalar(v);

	//si le point est dans le cylindre
	if(d < rayon*rayon && AxisOP >= 0 && PAxis1 >= 0)
		return 1;
	//s'il ne se trouve pas dans le cylindre
	else
		return 0;
}

void Octree::displayIntersectionSphereCylinder(Point OS, double rayonS, Point OC, Vector vC, double rayonC, double resolution)
{

	r = (centre.getX() + rayonS)/(rayonS*2);
	g = (centre.getY() + rayonS)/(rayonS*2);
	b = (centre.getZ() + rayonS)/(rayonS*2);

	int inter = intersectionVoxelSphereCylindre(OS, rayonS, OC, vC, rayonC);

	//S'il est à l'intérieur
	if(inter == 1)
	{
		//si la résolution n'est pas atteinte
		if(longeur > resolution)
		{
			draw = -1;
			division();
			for(int i = 0 ; i < 8 ; i++)
				enfants[i].displayIntersectionSphereCylinder(OS, rayonS, OC, vC, rayonC, resolution);
		}
	}
	//s'il n'est pas a l'intérieur
	else
	{
		//si la résolution n'est pas atteinte
		if(longeur > resolution)
		{
			draw = -1;
			division();
			for(int i = 0 ; i < 8 ; i++)
				enfants[i].displayIntersectionSphereCylinder(OS, rayonS, OC, vC, rayonC, resolution);
		}
		else
			draw = -1;
	}

}

int Octree::intersectionVoxelSphereCylindre(Point OS, double rayonS, Point OC, Vector vC, double rayonC)
{

	int d2 = (centre.getX() - OS.getX())*(centre.getX() - OS.getX()) 
			+ (centre.getY() - OS.getY())*(centre.getY() - OS.getY()) 
			+ (centre.getZ() - OS.getZ())*(centre.getZ() - OS.getZ());

	Point axis1(OC.getX() + vC.getX(), OC.getY() + vC.getY(), OC.getZ() + vC.getZ());
	Point P;
	P = centre.ProjectOnLine(OC, axis1);

	//Vérification distance pVoxels[i]P < rayon
	double d = (P.getX() - centre.getX())*(P.getX() - centre.getX()) + 
			(P.getY() - centre.getY())*(P.getY() - centre.getY()) + 
			(P.getZ() - centre.getZ())*(P.getZ() - centre.getZ());

	//Verification de l'appartenance de P (projeté) au segment axisOaxis1
	Vector vAxisOP(P.getX() - OC.getX(), P.getY() - OC.getY(), P.getZ() - OC.getZ());
	Vector vPAxis1(axis1.getX() - P.getX(), axis1.getY() - P.getY(), axis1.getZ() - P.getZ());
	double AxisOP = vAxisOP.Scalar(vC);
	double PAxis1 = vPAxis1.Scalar(vC);

	if(d < rayonC*rayonC && AxisOP >= 0 && PAxis1 >= 0 && d2 < rayonS*rayonS)
		return 1;
	else
		return 0;
}

void Octree::displaySoustractionSphereCylinder(Point OS, double rayonS, Point OC, Vector vC, double rayonC, double resolution)
{

	r = (centre.getX() + rayonS)/(rayonS*2);
	g = (centre.getY() + rayonS)/(rayonS*2);
	b = (centre.getZ() + rayonS)/(rayonS*2);

	int inter = soustractionVoxelSphereCylindre(OS, rayonS, OC, vC, rayonC);

	//S'il est à l'intérieur
	if(inter == 1)
	{
		//si la résolution n'est pas atteinte
		if(longeur > resolution)
		{
			draw = -1;
			division();
			for(int i = 0 ; i < 8 ; i++)
				enfants[i].displaySoustractionSphereCylinder(OS, rayonS, OC, vC, rayonC, resolution);
		}
	}
	//s'il n'est pas a l'intérieur
	else
	{
		//si la résolution n'est pas atteinte
		if(longeur > resolution)
		{
			draw = -1;
			division();
			for(int i = 0 ; i < 8 ; i++)
				enfants[i].displaySoustractionSphereCylinder(OS, rayonS, OC, vC, rayonC, resolution);
		}
		else
			draw = -1;
	}
}

int Octree::soustractionVoxelSphereCylindre(Point OS, double rayonS, Point OC, Vector vC, double rayonC)
{

	int d2 = (centre.getX() - OS.getX())*(centre.getX() - OS.getX()) 
			+ (centre.getY() - OS.getY())*(centre.getY() - OS.getY()) 
			+ (centre.getZ() - OS.getZ())*(centre.getZ() - OS.getZ());

	//CYLINDRE
	Point axis1(OC.getX() + vC.getX(), OC.getY() + vC.getY(), OC.getZ() + vC.getZ());
	Point P;
	P = centre.ProjectOnLine(OC, axis1);

	//Vérification distance centre < rayon
	double d = (P.getX() - centre.getX())*(P.getX() - centre.getX()) + 
			(P.getY() - centre.getY())*(P.getY() - centre.getY()) + 
			(P.getZ() - centre.getZ())*(P.getZ() - centre.getZ());

	//Verification de l'appartenance de P (projeté) au segment axisOaxis1
	Vector vAxisOP(P.getX() - OC.getX(), P.getY() - OC.getY(), P.getZ() - OC.getZ());
	Vector vPAxis1(axis1.getX() - P.getX(), axis1.getY() - P.getY(), axis1.getZ() - P.getZ());
	double AxisOP = vAxisOP.Scalar(vC);
	double PAxis1 = vPAxis1.Scalar(vC);

	if(d2 < rayonS*rayonS)//le point appartient à la sphère
	{
		if(!(AxisOP > 0 && PAxis1 > 0 && d < rayonC*rayonC))//il n'appartient pas au cylindre
		{				
			return 1;
		}
	}
	else
		return 0;
}

void Octree::displayUnionSphereCylinder(Point OS, double rayonS, Point OC, Vector vC, double rayonC, double resolution)
{

	r = (centre.getX() + rayonS)/(rayonS*2);
	g = (centre.getY() + rayonS)/(rayonS*2);
	b = (centre.getZ() + rayonS)/(rayonS*2);

	int inter = unionVoxelSphereCylindre(OS,rayonS, OC, vC, rayonC);

	//S'il est à l'intérieur
	if(inter == 1)
	{
		//si la résolution n'est pas atteinte
		if(longeur > resolution)
		{
			draw = -1;
			division();
			for(int i = 0 ; i < 8 ; i++)
				enfants[i].displayUnionSphereCylinder(OS, rayonS, OC, vC, rayonC, resolution);
		}
	}
	//s'il n'est pas a l'intérieur
	else
	{
		//si la résolution n'est pas atteinte
		if(longeur > resolution)
		{
			draw = -1;
			division();
			for(int i = 0 ; i < 8 ; i++)
				enfants[i].displayUnionSphereCylinder(OS, rayonS, OC, vC, rayonC, resolution);
		}
		else
			draw = -1;
	}
}

int Octree::unionVoxelSphereCylindre(Point OS, double rayonS, Point OC, Vector vC, double rayonC)
{

	int d2 = (centre.getX() - OS.getX())*(centre.getX() - OS.getX()) 
			+ (centre.getY() - OS.getY())*(centre.getY() - OS.getY()) 
			+ (centre.getZ() - OS.getZ())*(centre.getZ() - OS.getZ());


	Point axis1(OC.getX() + vC.getX(), OC.getY() + vC.getY(), OC.getZ() + vC.getZ());
	Point P;
	P = centre.ProjectOnLine(OC, axis1);

	//Vérification distance centre < rayon
	double d = (P.getX() - centre.getX())*(P.getX() - centre.getX()) + 
			(P.getY() - centre.getY())*(P.getY() - centre.getY()) + 
			(P.getZ() - centre.getZ())*(P.getZ() - centre.getZ());

	//Verification de l'appartenance de P (projeté) au segment axisOaxis1
	Vector vAxisOP(P.getX() - OC.getX(), P.getY() - OC.getY(), P.getZ() - OC.getZ());
	Vector vPAxis1(axis1.getX() - P.getX(), axis1.getY() - P.getY(), axis1.getZ() - P.getZ());
	double AxisOP = vAxisOP.Scalar(vC);
	double PAxis1 = vPAxis1.Scalar(vC);

	if((d2 < rayonS*rayonS) || (AxisOP >= 0 && PAxis1 >= 0 && d < rayonC*rayonC))
		return 1;
	else
		return 0;
}

void Octree::division()
{
	enfants = new Octree[8];
	double l = longeur/2;

	enfants[0] = Octree(Point(centre.getX() - l, centre.getY() - l, centre.getZ() - l), l);
    enfants[1] = Octree(Point(centre.getX() + l, centre.getY() - l, centre.getZ() - l), l);
    enfants[2] = Octree(Point(centre.getX() - l, centre.getY() + l, centre.getZ() - l), l);
    enfants[3] = Octree(Point(centre.getX() + l, centre.getY() + l, centre.getZ() - l), l);
    enfants[4] = Octree(Point(centre.getX() - l, centre.getY() - l, centre.getZ() + l), l);
    enfants[5] = Octree(Point(centre.getX() + l, centre.getY() - l, centre.getZ() + l), l);
    enfants[6] = Octree(Point(centre.getX() - l, centre.getY() + l, centre.getZ() + l), l);
    enfants[7] = Octree(Point(centre.getX() + l, centre.getY() + l, centre.getZ() + l), l);
}

void Octree::drawOctree()
{
	if(draw == 1)
	{
		glColor3f(r,g,b);
		displayVoxel();
	}
		
	if(enfants != NULL)
	{
		for(int i = 0; i < 8; i++)
			enfants[i].drawOctree();
	}	
}

void Octree::displayVoxel()
{
  double l = longeur;

  	glBegin(GL_QUADS);

    glVertex3f(centre.getX() + l, centre.getY() + l, centre.getZ() + l);
    glVertex3f(centre.getX() + l, centre.getY() + l, centre.getZ() - l);
    glVertex3f(centre.getX() + l, centre.getY() - l, centre.getZ() - l);
    glVertex3f(centre.getX() + l, centre.getY() - l, centre.getZ() + l);

    glVertex3f(centre.getX() + l, centre.getY() + l, centre.getZ() + l);
    glVertex3f(centre.getX() - l, centre.getY() + l, centre.getZ() + l);
    glVertex3f(centre.getX() - l, centre.getY() - l, centre.getZ() + l);
    glVertex3f(centre.getX() + l, centre.getY() - l, centre.getZ() + l);

    glVertex3f(centre.getX() + l, centre.getY() + l, centre.getZ() - l);
    glVertex3f(centre.getX() + l, centre.getY() - l, centre.getZ() - l);
    glVertex3f(centre.getX() - l, centre.getY() - l, centre.getZ() - l);
    glVertex3f(centre.getX() - l, centre.getY() + l, centre.getZ() - l);

    glVertex3f(centre.getX() + l, centre.getY() + l, centre.getZ() + l);
    glVertex3f(centre.getX() + l, centre.getY() + l, centre.getZ() - l);
    glVertex3f(centre.getX() - l, centre.getY() + l, centre.getZ() - l);
    glVertex3f(centre.getX() - l, centre.getY() + l, centre.getZ() + l);

    glVertex3f(centre.getX() + l, centre.getY() - l, centre.getZ() + l);
    glVertex3f(centre.getX() + l, centre.getY() - l, centre.getZ() - l);
    glVertex3f(centre.getX() - l, centre.getY() - l, centre.getZ() - l);
    glVertex3f(centre.getX() - l, centre.getY() - l, centre.getZ() + l);

    glVertex3f(centre.getX() - l, centre.getY() + l, centre.getZ() + l);
    glVertex3f(centre.getX() - l, centre.getY() + l, centre.getZ() - l);
    glVertex3f(centre.getX() - l, centre.getY() - l, centre.getZ() - l);
    glVertex3f(centre.getX() - l, centre.getY() - l, centre.getZ() + l);
	glEnd();

	/*glBegin(GL_LINES);

	//carre droite
	glVertex3f(centre.getX() + l, centre.getY() + l, centre.getZ() + l);
    glVertex3f(centre.getX() + l, centre.getY() + l, centre.getZ() - l);

    glVertex3f(centre.getX() + l, centre.getY() + l, centre.getZ() - l);
    glVertex3f(centre.getX() + l, centre.getY() - l, centre.getZ() - l);

    glVertex3f(centre.getX() + l, centre.getY() - l, centre.getZ() - l);
    glVertex3f(centre.getX() + l, centre.getY() - l, centre.getZ() + l);

    glVertex3f(centre.getX() + l, centre.getY() - l, centre.getZ() + l);
    glVertex3f(centre.getX() + l, centre.getY() + l, centre.getZ() + l);

    //carre arrière
    glVertex3f(centre.getX() + l, centre.getY() + l, centre.getZ() + l);
    glVertex3f(centre.getX() - l, centre.getY() + l, centre.getZ() + l);

    glVertex3f(centre.getX() - l, centre.getY() + l, centre.getZ() + l);
    glVertex3f(centre.getX() - l, centre.getY() - l, centre.getZ() + l);

    glVertex3f(centre.getX() - l, centre.getY() - l, centre.getZ() + l);
    glVertex3f(centre.getX() + l, centre.getY() - l, centre.getZ() + l);

    //carre avant
    glVertex3f(centre.getX() - l, centre.getY() - l, centre.getZ() - l);
    glVertex3f(centre.getX() - l, centre.getY() + l, centre.getZ() - l);

    glVertex3f(centre.getX() - l, centre.getY() + l, centre.getZ() - l);
    glVertex3f(centre.getX() + l, centre.getY() + l, centre.getZ() - l);

    glVertex3f(centre.getX() - l, centre.getY() - l, centre.getZ() - l);
    glVertex3f(centre.getX() + l, centre.getY() - l, centre.getZ() - l);

    //carre gauche
    glVertex3f(centre.getX() - l, centre.getY() - l, centre.getZ() - l);
    glVertex3f(centre.getX() - l, centre.getY() - l, centre.getZ() + l);

    glVertex3f(centre.getX() - l, centre.getY() + l, centre.getZ() - l);
    glVertex3f(centre.getX() - l, centre.getY() + l, centre.getZ() + l);

	glEnd();*/
}