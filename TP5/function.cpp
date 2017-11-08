#include <math.h>
#include "function.h"


Point* hermiteCubicCurve(Point p0, Point p1, Vector v0, Vector v1, long nbU){
  Point *tabPoints = new Point[nbU];
  
  for(int i=0;i<nbU;++i){
    double u = i*(1/(double)nbU);
    
    double f1 = 2*(u*u*u) - 3*u*u + 1;
    double f2 = -2*u*u*u + 3*u*u;
    double f3 = u*u*u - 2*u*u + u;
    double f4 = u*u*u - u*u;

    tabPoints[i].setX(f1*p0.getX() + f2*p1.getX() + f3*v0.getX() + f4*v1.getX());
    tabPoints[i].setY(f1*p0.getY() + f2*p1.getY() + f3*v0.getY() + f4*v1.getY());
    tabPoints[i].setZ(f1*p0.getZ() + f2*p1.getZ() + f3*v0.getZ() + f4*v1.getZ());
         
  }
  return tabPoints;
}


int factorial(int n)
{
  return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}


Point* bezierCurveByBernstein(Point TabControlPoint[], long nbControlPoint, long nbU){
  Point *tabPoints = new Point[nbU];
  
  
  for(int i=0;i<nbU;++i){
    double u = i*1/(double)nbU;
	
    double x=0;
    double y=0;
    double z=0;

    for(int j=0;j<nbControlPoint;++j){
      
      double B = ( factorial(nbControlPoint-1) /( factorial(j) * factorial(nbControlPoint-1-j) ) ) * pow(u,j) * pow((1-u),(nbControlPoint-1-j));
      
      x+=B*TabControlPoint[j].getX();
      y+=B*TabControlPoint[j].getY();
      z+=B*TabControlPoint[j].getZ();
    }
    
    tabPoints[i].setX(x);
    tabPoints[i].setY(y);
    tabPoints[i].setZ(z);
  }
  return tabPoints;
}


Point* bezierCurveByCasteljau(Point TabControlPoint[], long nbControlPoint, long nbU,int step){
  Point *tabPoints = new Point[nbU];
  double u;

  for(int i=0; i<nbU; ++i){
    u = i / (double)(nbU-1);
    if(i == step % (int)nbU && step != -1){
      tabPoints[i] = getCastelJauPoint(TabControlPoint, nbControlPoint -1, 0, u,true);
      drawPoint(tabPoints[i]);
    }
    else
      tabPoints[i] = getCastelJauPoint(TabControlPoint, nbControlPoint -1, 0, u,false);
  }
  return tabPoints;
}

Point getCastelJauPoint(Point TabControlPoint[],  long k, long i, double u,bool drawStep ){
  if(k == 0) return TabControlPoint[i];

  Point p1 = getCastelJauPoint(TabControlPoint, k-1, i, u,drawStep);
  Point p2 = getCastelJauPoint(TabControlPoint, k-1, i+1, u,drawStep);

  if(drawStep){
    glColor3f(0,0.8,0.8);
  
    drawPoint(p1);
    drawPoint(p2);
  
    drawLine(p1,p2);
  }

  return Point( (double)(1-u)*p1.getX() + u*p2.getX(), (double)(1-u)*p1.getY() + u*p2.getY(), (double)(1-u)*p1.getZ() + u*p2.getZ());  
}



								
Point** bezierSurfaceCylindrique(Point curve[], Point p1, Point p2, long nbV, long nbU){

	Point** tabPoints = new Point*[nbU];

	for(int i=0;i<nbU;i++)
		tabPoints[i] = new Point[nbV]();

 	double u;
 	
  	for(int i=0; i<nbU; ++i){

  		u = i / (double)(nbU-1);

  		for(int j=0; j<nbV; ++j){

  			Point du = p1*u + p2*(1-u);

			Point decalage = du - p1;
			tabPoints[i][j] = curve[j] + decalage;
  		}
  	}
  	return tabPoints;
}

Point** SurfaceReglee(Point curve1[], Point curve2[], long nbV, long nbU)
{
	Point** tabPoints = new Point*[nbU]();
	for(int i=0;i<nbU;i++)
		tabPoints[i] = new Point[nbV]();

	for(int i=0;i<nbU;i++){
		for(int j=0;j<nbV;j++){
			double v = (double)j*(1.0 / (nbV-1.0));
			tabPoints[i][j] = curve1[i]*v + curve2[i]*(1.-v);
		}
	}
	return tabPoints;
}






/*Point getPointByCasteljau(Point* tabControlPoint, long k, long i, long j,double u,double v)
{
	if(k == 0)
		return tabControlPoint[i*nbControlPointJ+j];

	Point A = getPointByCasteljau(tabControlPoint, k-1, i, j+1, u, v, nbControlPointJ) * (1-u) + getPointByCasteljau(tabControlPoint, k-1, i+1, j+1, u, v, nbControlPointJ) * u;

	Point B =  getPointByCasteljau(tabControlPoint, k-1, i, j, u, v, nbControlPointJ) * (1-u) +  getPointByCasteljau(tabControlPoint, k-1, i+1, j, u, v, nbControlPointJ) * u;
	
	return Point(B * (1-v) + A * v);
}

Point** bezierSurfaceByCasteljau(Point** tabControlPoint, long nbControlPointI, long nbControlPointJ, long nbU, long nbV)
{
	Point** tabPoints = new Point*[nbU]();
	for(int i=0;i<nbU;i++)
		tabPoints[i] = new Point[nbV]();

	Point tab[nbControlPointI*nbControlPointJ];
	for(int i=0;i<nbControlPointI;i++){
		for(int j=0;j<nbControlPointJ;j++){
			tab[i*nbControlPointJ+j] = tabControlPoint[i][j];
		}
	}

	for(int i=0;i<nbU;i++){
		double u = (double)i*(1.0 / ((double)nbU-1.0));
		for(int j=0;j<nbV;j++){
			double v = (double)j*(1.0 / ((double)nbV-1.0));
			tabPoints[i][j] = getPointByCasteljau(tab,nbControlPointI*nbControlPointJ,0,0,u,v,nbControlPointJ);
		}
	}

	return tabPoints;
}*/


Point** bezierSurfaceByCasteljau(Point** tabControlPoint, long nbControlPointU, long nbU, long nbControlPointV, long nbV)
{
	Point** tabPoints = new Point*[nbU]();
	for(int i=0;i<nbU;i++)
		tabPoints[i] = new Point[nbV]();


	Point* pPoint = new Point[nbControlPointU];

	for(int i=0;i<nbU;i++){
		double u = (double)i*(1.0 / ((double)nbU-1.0));
		for(int j=0;j<nbV;j++){

			double v = (double)j*(1.0 / ((double)nbV-1.0));

			for(int k=0; k<nbControlPointU; ++k){
				pPoint[k] = getCastelJauPoint(tabControlPoint[k],nbControlPointV - 1,0,v,false);
			}
			tabPoints[i][j] = getCastelJauPoint(pPoint,nbControlPointU - 1, 0, u, false);
		}
	}
	delete [] pPoint;
	return tabPoints;
}


Point** getCylinder(Point p1, Vector vd, int h, int rayon, int nbMeridiens){
    Point **meridiens= new Point*[nbMeridiens];
    for(int i = 0; i < nbMeridiens ; ++i){
      double angle = 2 * M_PI * i / (nbMeridiens-1); 
	
      double x = rayon * cos(angle);
	  
      double y = rayon * sin(angle);
      double z = -h/2; 
	
	  
      meridiens[i] = new Point[2];
      //meridiens[i][0] = Point(x,y,z) + p1;   
      //meridiens[i][1] = Point(x,y,-z) + p1; 
	  
	  meridiens[i][0] = Point(x,y,z);
	  
	  meridiens[i][1] = Point(x,y,-z);
	  	  
    }

    return meridiens;
}


Point* getCones(Point sommet, int rayon, int h, int n){
    Point *meridiens= new Point[n];
    for(int i = 0; i < n ; ++i){
      double angle = 2 * M_PI * i / (n-1); 

      double x = rayon * cos(angle);
      double y = rayon * sin(angle);
      double z = -h/2;

      meridiens[i] = Point(x,y,z);   
    }

    return meridiens;
}

Point** getSphere(Point base,double r,int nbM,int nbP)
{
	Point** tabPoints = new Point*[nbM]();

	for(int i=0;i<nbM;i++)
	{
		tabPoints[i] = new Point[nbP]();
		for(int j=0;j<nbP;j++)
		{
			double m = (double)i/(double)(nbM-1) * M_PI * 2.;
			double p = (double)j/(double)(nbP-1) * M_PI - M_PI/2.;
			
			tabPoints[i][j] = Point( r*cos(m)*cos(p) , r*sin(m)*cos(p) , r*sin(p) );
			tabPoints[i][j] = tabPoints[i][j] + base;
		}
	}
	return tabPoints;
}


/*TP5*/


void displayVoxel(Point center, double lenght){

  double l = lenght/2;

  	glBegin(GL_QUADS);

    glVertex3f(center.getX()+l,center.getY()+l,center.getZ()+l);
    glVertex3f(center.getX()+l,center.getY()+l,center.getZ()-l);
    glVertex3f(center.getX()+l,center.getY()-l,center.getZ()-l);
    glVertex3f(center.getX()+l,center.getY()-l,center.getZ()+l);


    glVertex3f(center.getX()+l,center.getY()+l,center.getZ()+l);
    glVertex3f(center.getX()-l,center.getY()+l,center.getZ()+l);
    glVertex3f(center.getX()-l,center.getY()-l,center.getZ()+l);
    glVertex3f(center.getX()+l,center.getY()-l,center.getZ()+l);

    glVertex3f(center.getX()+l,center.getY()+l,center.getZ()-l);
    glVertex3f(center.getX()+l,center.getY()-l,center.getZ()-l);
    glVertex3f(center.getX()-l,center.getY()-l,center.getZ()-l);
    glVertex3f(center.getX()-l,center.getY()+l,center.getZ()-l);

    glVertex3f(center.getX()+l,center.getY()+l,center.getZ()+l);
    glVertex3f(center.getX()+l,center.getY()+l,center.getZ()-l);
    glVertex3f(center.getX()-l,center.getY()+l,center.getZ()-l);
    glVertex3f(center.getX()-l,center.getY()+l,center.getZ()+l);

    glVertex3f(center.getX()+l,center.getY()-l,center.getZ()+l);
    glVertex3f(center.getX()+l,center.getY()-l,center.getZ()-l);
    glVertex3f(center.getX()-l,center.getY()-l,center.getZ()-l);
    glVertex3f(center.getX()-l,center.getY()-l,center.getZ()+l);

    glVertex3f(center.getX()-l,center.getY()+l,center.getZ()+l);
    glVertex3f(center.getX()-l,center.getY()+l,center.getZ()-l);
    glVertex3f(center.getX()-l,center.getY()-l,center.getZ()-l);
    glVertex3f(center.getX()-l,center.getY()-l,center.getZ()+l);
	glEnd();

}



void drawPoint(Point p){
  glPointSize(5);
  glBegin(GL_POINTS);
   glVertex3f(p.getX(), p.getY(), p.getZ());
  glEnd();
}

void drawLine(Point p1,Point p2){
  glBegin(GL_LINES);
   glVertex3f(p1.getX(), p1.getY(), p1.getZ());
   glVertex3f(p2.getX(), p2.getY(), p2.getZ());
  glEnd();
}

void drawGrid(){
  int xmax = 4;
  int xmin = -4;
  int ymin = -4;
  int ymax = 4;

  for(int i=xmin; i<xmax ;++i){
    if(i == 0){
      glColor3f(.0, .7, .0);
    }else{
      glColor3f(0.4, .4, .4);
    }
    glBegin(GL_LINES);
     glVertex3f(i, ymin, 0);
     glVertex3f(i, ymax, 0);
    glEnd();
  }

  for(int i=ymin; i<ymax ;++i){
    if(i == 0){
      glColor3f(.7, 0, 0);
    }else{
      glColor3f(0.4, .4, .4);
    }

    glBegin(GL_LINES);
     glVertex3f(xmin, i, 0);
     glVertex3f(xmax, i, 0);
    glEnd();
  }

}

void drawCurve(Point TabPointsOfCurve[], long nbPoints){
  
  glBegin(GL_LINE_STRIP);
  for(int i=0; i<nbPoints; ++i){
    glVertex3f(TabPointsOfCurve[i].getX(), TabPointsOfCurve[i].getY(), TabPointsOfCurve[i].getZ());
  }
  glEnd();
}

void drawQuad(Point p1,Point p2,Point p3,Point p4)
{
	glBegin(GL_POLYGON);
		glVertex3f(p1.getX(),p1.getY(),p1.getZ());
		glVertex3f(p2.getX(),p2.getY(),p2.getZ());
		glVertex3f(p3.getX(),p3.getY(),p3.getZ());
		glVertex3f(p4.getX(),p4.getY(),p4.getZ());
	glEnd();
}

void drawTriangle(Point p1,Point p2,Point p3)
{
  glBegin(GL_TRIANGLES);
    glVertex3f(p1.getX(),p1.getY(),p1.getZ());
    glVertex3f(p2.getX(),p2.getY(),p2.getZ());
    glVertex3f(p3.getX(),p3.getY(),p3.getZ());
  glEnd();
}

double distance(Point p1,Point p2)
{
	return sqrt(pow(p1.getX()-p2.getX(),2)+pow(p1.getY()-p2.getY(),2)+pow(p1.getZ()-p2.getZ(),2));
}


