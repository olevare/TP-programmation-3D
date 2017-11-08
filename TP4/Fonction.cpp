#include <iostream>
#include <stdio.h>      
#include <stdlib.h>     
#include <math.h>
#include "Vector.h"
#include "Point.h"
#include "Fonction.h"

using namespace std;

void DrawCurve(Point TabPointsOfCurve[], long nbPoints)
{
  glBegin(GL_LINE_STRIP);
  for(int i = 0; i < nbPoints; ++i)
    glVertex3f(TabPointsOfCurve[i].getX(), TabPointsOfCurve[i].getY(), TabPointsOfCurve[i].getZ());
  glEnd();
}

Point *HermiteCubicCurve(Point P0, Point P1, Vector V0, Vector V1, long nbU)
{
  //crée le tableau de points
  Point *tabPoints = new Point[nbU];
  
  //pour tous les points à calculer
  for(int i = 0; i < nbU; i++)
  {
    //calcule du p(u)
    double u = i*(1/(double)nbU);
    
    //on applique la formule du cours
    double f1 = 2*(u*u*u) - 3*u*u + 1;
    double f2 = -2*u*u*u + 3*u*u;
    double f3 = u*u*u - 2*u*u + u;
    double f4 = u*u*u - u*u;

    tabPoints[i].setX(f1*P0.getX() + f2*P1.getX() + f3*V0.getX() + f4*V1.getX());
    tabPoints[i].setY(f1*P0.getY() + f2*P1.getY() + f3*V0.getY() + f4*V1.getY());
    tabPoints[i].setZ(f1*P0.getZ() + f2*P1.getZ() + f3*V0.getZ() + f4*V1.getZ());
         
  }
  //retourne le tableau de points
  return tabPoints;
}

Point* BezierCurveByBernstein(Point TabControlPoint[], long nbControlPoint, long nbU)
{
  //crée le tableau de points
  Point *tabPoints = new Point[nbU];
  
  //pour tous les points à calculer
  for(int i = 0; i < nbU; i++)
  {
    //calcule du p(u)
    double u = i*(1/(double)nbU);
	
    //initialise les valeurs à 0
    double x = 0;
    double y = 0;
    double z = 0;

    //pour tous les points de controles
    for(int j = 0; j < nbControlPoint; j++)
    {
      //calcule du polynome
      double B = ( factorial(nbControlPoint-1) /( factorial(j) * factorial(nbControlPoint-1-j) ) ) * pow(u,j) * pow((1-u),(nbControlPoint-1-j));
      
      //multipli le polynome au point de controle j
      x += B*TabControlPoint[j].getX();
      y += B*TabControlPoint[j].getY();
      z += B*TabControlPoint[j].getZ();
    }
    
    tabPoints[i].setX(x);
    tabPoints[i].setY(y);
    tabPoints[i].setZ(z);
  }
  //retourne le tableau de points
  return tabPoints;
}

Point* BezierCurveByCasteljau(Point TabControlPoint[], long nbControlPoint, long nbU)
{
  //crée le tableau de points
  Point *tabPoints = new Point[nbU];

  //pour tous les points à calculer
  for(int i = 0; i < nbU; i++)
  {
    //calcule du p(u)
    double u = i*(1/(double)(nbU-1));

    //calcule du point
    tabPoints[i] = getCastelJauPoint(TabControlPoint, nbControlPoint -1, 0, u);
  }
  //retourne le tableau de points
  return tabPoints;
}

Point getCastelJauPoint(Point TabControlPoint[],  long k, long i, double u)
{
  if(k == 0)
    return TabControlPoint[i];

  //on applique la formule du cours
  Point p1 = getCastelJauPoint(TabControlPoint, k-1, i, u);
  Point p2 = getCastelJauPoint(TabControlPoint, k-1, i+1, u);

  glColor3f(0,0.8,0.8);
  
  drawPoint(p1);
  drawPoint(p2);
  
  drawLine(p1,p2);

  //retourne le point
  return Point( (double)(1-u)*p1.getX() + u*p2.getX(), (double)(1-u)*p1.getY() + u*p2.getY(), (double)(1-u)*p1.getZ() + u*p2.getZ());  
}

Point** bezierSurfaceCylindrique(Point curve[], Point p1, Point p2, long nbV, long nbU)
{
  //cree le tableau de points
  Point** tabPoints = new Point*[nbU];

  for(int i = 0; i < nbU; i++)
    tabPoints[i] = new Point[nbV]();
  
  for(int i = 0; i < nbU; i++)
  {
    //calcule du p(u)
    double u = i*(1/(double)(nbU-1));

    for(int j = 0; j < nbV; j++)
    {
      //calcule du décalage
      Point du = p1*u + p2*(1-u);
      Point decalage = du - p1;

      //ajoute le point décalé
      tabPoints[i][j] = curve[j] + decalage;
    }
  }
  //retourne le tableau de points
  return tabPoints;
}

Point** SurfaceReglee(Point curve1[], Point curve2[], long nbV, long nbU)
{
  //cree le tableau de points
  Point** tabPoints = new Point*[nbU];

  for(int i = 0; i < nbU; i++)
    tabPoints[i] = new Point[nbV];

  for(int i = 0; i < nbU; i++)
  {
    for(int j = 0; j < nbV; j++)
    {
      //calcule de p(v)
      double v = (double)j*(1.0 / (nbV-1.0));

      //on applique la formule du cours
      tabPoints[i][j] = curve1[i]*v + curve2[i]*(1.-v);
    }
  }
  //retourne le tableau de points
  return tabPoints;
}

Point** bezierSurfaceByCasteljau(Point** tabControlPoint, long nbControlPointU, long nbU, long nbControlPointV, long nbV)
{
  //cree le tableau de points
  Point** tabPoints = new Point*[nbU];

  for(int i = 0; i < nbU; i++)
    tabPoints[i] = new Point[nbV];

  //cree un second tableau de points
  Point* pPoint = new Point[nbControlPointU];

  for(int i = 0; i < nbU; i++)
  {
    //calcule du p(u)
    double u = (double)i*(1.0 / ((double)nbU-1.0));

    for(int j = 0; j < nbV; j++)
    {
      //calcule du p(v)
      double v = (double)j*(1.0 / ((double)nbV-1.0));

      //pour tous les points de controle
      for(int k = 0; k < nbControlPointU; k++)
        pPoint[k] = getCastelJauPoint(tabControlPoint[k],nbControlPointU - 1, 0, v);

      tabPoints[i][j] = getCastelJauPoint(pPoint,nbControlPointV - 1, 0, u);
    }
  }
  delete [] pPoint;
  
  //retourne le tableau de points
  return tabPoints;
}

Point** facettisationCylindre(int hauteur, int rayon, int nbMeridiens)
{
  //cree le tableau de points
  Point **meridiens = new Point*[nbMeridiens];

  for(int i = 0; i < nbMeridiens; i++)
  {
    //calcule de l'angle
    double angle = 2 * M_PI * i / (nbMeridiens-1); 
  
    double x = rayon * cos(angle);
    double y = rayon * sin(angle);
    double z = hauteur/2; 
  
    meridiens[i] = new Point[2];
    
    meridiens[i][0] = Point(x,y,z);
    
    meridiens[i][1] = Point(x,y,-z);
        
  }
  //retourne le tableau de points
  return meridiens;
}


Point* getCones(int rayon, int hauteur, int meridiens)
{
  //cree le tableau de points
  Point *tabmeridiens = new Point[meridiens];

  for(int i = 0; i < meridiens; i++)
  {
    double angle = 2 * M_PI * i / (meridiens-1); 

    double x = rayon * cos(angle);
    double y = rayon * sin(angle);
    double z = -hauteur;

    tabmeridiens[i] = Point(x,y,z);   
  }
  //retourne le tableau de points
  return tabmeridiens;
}

Point** getSphere(Point base,double rayon,int meridiens,int paralleles)
{
  //cree le tableau de points
  Point** tabPoints = new Point*[meridiens];

  for(int i = 0; i < meridiens; i++)
  {
    //cree le tableau de points
    tabPoints[i] = new Point[paralleles];

    for(int j = 0; j < paralleles; j++)
    {
      double m = (double)i/(double)(meridiens-1) * M_PI * 2.;
      double p = (double)j/(double)(paralleles-1) * M_PI - M_PI/2.;
      
      tabPoints[i][j] = Point( rayon*cos(m)*cos(p) , rayon*sin(m)*cos(p) , rayon*sin(p) );
      tabPoints[i][j] = tabPoints[i][j] + base;
    }
  }
  //retourne le tableau de points
  return tabPoints;
}

int factorial(int n)
{
  if(n == 1 || n == 0)
    return 1;
  else
    factorial(n - 1) * n;
}

void drawPoint(Point pt)
{
  glPointSize(5);
  glBegin(GL_POINTS);
    glVertex3f(pt.getX(),pt.getY(),pt.getZ());
  glEnd();
}

void drawLine(Point pt1, Point pt2)
{
  glBegin(GL_LINES);
    glVertex3f(pt1.getX(),pt1.getY(),pt1.getZ());
    glVertex3f(pt2.getX(),pt2.getY(),pt2.getZ());
  glEnd();
}

void drawLine(Vector v, Point pt)
{
  drawLine(pt,Point(pt.getX()+v.getX(),pt.getY()+v.getY(),pt.getZ()+v.getZ()));
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
