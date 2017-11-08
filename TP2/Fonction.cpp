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

  //retourne le point
  return Point( (double)(1-u)*p1.getX() + u*p2.getX(), (double)(1-u)*p1.getY() + u*p2.getY(),0);  
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