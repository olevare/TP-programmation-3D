#include "./freeglut-3.0.0/include/GL/freeglut.h" 

#include "Point.h"

Point* hermiteCubicCurve(Point p0, Point p1, Vector v0, Vector v1, long nbU);
Point* bezierCurveByBernstein(Point TabControlPoint[], long nbControlPoint, long nbU);

Point* bezierCurveByCasteljau(Point TabControlPoint[], long nbControlPoint, long nbU,int step);
Point getCastelJauPoint(Point TabControlPoint[],  long k, long i, double u,bool drawStep);

int factorial(int n);

void drawPoint(Point p);
void drawLine(Point p1,Point p2);

void drawGrid();

void drawCurve(Point TabPointsOfCurve[], long nbPoints);

void drawQuad(Point p1,Point p2,Point p3,Point p4);
void drawTriangle(Point p1,Point p2,Point p3);


Point** bezierSurfaceCylindrique(Point curve[], Point p1, Point p2, long nbV, long nbU);
Point** SurfaceReglee(Point curve1[], Point curve2[], long nbV, long nbU);

//Point getPointByCasteljau(Point* tabControlPoint, long k, long i, long j,double u,double v,long nbControlPointJ);
Point** bezierSurfaceByCasteljau(Point** tabControlPoint, long nbControlPointU, long nbU, long nbControlPointV, long nbV);


Point** getCylinder(Point p1, Vector normal, int h, int rayon, int nbMeridiens);
Point* getCones(Point sommet, int rayon, int h, int n);
Point** getSphere(Point base,double r,int meridiens,int parallele);
void displayVoxel(Point center, double lenght);

double distance(Point p1,Point p2);

