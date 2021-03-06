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

#endif
