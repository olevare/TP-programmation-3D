#ifndef Fonction_h
#define Fonction_h

#include "Vector.h"
#include "Point.h"
#include "freeglut-3.0.0/include/GL/glut.h"

void DrawCurve(Point TabPointsOfCurve[], long nbPoints);
Point *HermiteCubicCurve(Point P0, Point P1, Vector V0, Vector V1, long nbU);
Point* BezierCurveByBernstein(Point TabControlPoint[], long nbControlPoint, long nbU);
Point* BezierCurveByCasteljau(Point TabControlPoint[], long nbControlPoint, long nbU);
Point getCastelJauPoint(Point TabControlPoint[],  long k, long i, double u);

int factorial(int n);
void drawPoint(Point pt);
void drawLine(Point pt1, Point pt2);
void drawLine(Vector v, Point pt);

void drawQuad(Point p1,Point p2,Point p3,Point p4);

void drawTriangle(Point p1,Point p2,Point p3);

Point** bezierSurfaceCylindrique(Point curve[], Point p1, Point p2, long nbV, long nbU);
Point** SurfaceReglee(Point curve1[], Point curve2[], long nbV, long nbU);
Point** bezierSurfaceByCasteljau(Point** tabControlPoint, long nbControlPointU, long nbU, long nbControlPointV, long nbV);

Point** facettisationCylindre(int hhauteur, int rayon, int nbMeridiens);
Point* getCones(int rayon, int hauteur, int meridiens);
Point** getSphere(Point base,double rayon,int meridiens,int paralleles);

double distance(Point p1,Point p2);

#endif
