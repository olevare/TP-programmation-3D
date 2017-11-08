///////////////////////////////////////////////////////////////////////////////
// Imagina
// ----------------------------------------------------------------------------
// IN - Synthèse d'images - Modélisation géométrique
// Auteur : Gilles Gesquière
// ----------------------------------------------------------------------------
// Base du TP 1
// programme permettant de créer des formes de bases.
// La forme représentée ici est un polygone blanc dessiné sur un fond rouge
///////////////////////////////////////////////////////////////////////////////  

#include <stdio.h>      
#include <stdlib.h>     
#include <math.h>
#include "Point.h"
#include "Vector.h"
#include "Fonction.h"


/* Dans les salles de TP, vous avez généralement accès aux glut dans C:\Dev. Si ce n'est pas le cas, téléchargez les .h .lib ...
Vous pouvez ensuite y faire référence en spécifiant le chemin dans visual. Vous utiliserez alors #include <glut.h>. 
Si vous mettez glut dans le répertoire courant, on aura alors #include "glut.h" 
*/

#include "freeglut-3.0.0/include/GL/glut.h"

// Définition de la taille de la fenêtre
#define WIDTH  480

#define HEIGHT 480

// Définition de la couleur de la fenêtre
#define RED   0
#define GREEN 0
#define BLUE  0
#define ALPHA 1


// Touche echap (Esc) permet de sortir du programme
#define KEY_ESC 27


// Entêtes de fonctions
void init_scene();
void render_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height); 
GLvoid window_key(unsigned char key, int x, int y);

void drawPoint(Point pt);
void drawLine(Point pt1, Point pt2);
void drawLine(Vector v, Point pt);


int main(int argc, char **argv) 
{  
  // initialisation  des paramètres de GLUT en fonction
  // des arguments sur la ligne de commande
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA);

  // définition et création de la fenêtre graphique, ainsi que son titre
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("TP2");

  // initialisation de OpenGL et de la scène
  initGL();  
  init_scene();

  // choix des procédures de callback pour 
  // le tracé graphique
  glutDisplayFunc(&window_display);
  // le redimensionnement de la fenêtre
  glutReshapeFunc(&window_reshape);
  // la gestion des événements clavier
  glutKeyboardFunc(&window_key);

  // la boucle prinicipale de gestion des événements utilisateur
  glutMainLoop();  

  return 1;
}

// initialisation du fond de la fenêtre graphique : noir opaque
GLvoid initGL() 
{
  glClearColor(RED, GREEN, BLUE, ALPHA);        
}

// Initialisation de la scene. Peut servir à stocker des variables de votre programme
// à initialiser
void init_scene()
{
}

// fonction de call-back pour l´affichage dans la fenêtre

GLvoid window_display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

  // C'est l'endroit où l'on peut dessiner. On peut aussi faire appel
  // à une fonction (render_scene() ici) qui contient les informations 
  // que l'on veut dessiner
  render_scene();

  // trace la scène grapnique qui vient juste d'être définie
  glFlush();
}

// fonction de call-back pour le redimensionnement de la fenêtre

GLvoid window_reshape(GLsizei width, GLsizei height)
{  
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // ici, vous verrez pendant le cours sur les projections qu'en modifiant les valeurs, il est
  // possible de changer la taille de l'objet dans la fenêtre. Augmentez ces valeurs si l'objet est 
  // de trop grosse taille par rapport à la fenêtre.
  glOrtho(-4.0, 4.0, -4.0, 4.0, -4.0, 4.0);

  // toutes les transformations suivantes s´appliquent au modèle de vue 
  glMatrixMode(GL_MODELVIEW);
}

// fonction de call-back pour la gestion des événements clavier

GLvoid window_key(unsigned char key, int x, int y) 
{  
  switch (key)
  {    
    case KEY_ESC:  
      exit(1);                    
      break; 
    
    default:
      printf ("La touche %d n´est pas active.\n", key);
      break;
  }     
}

void TP2()
{
  //exercice 1
  /*
  Point p0(-3,3,0);
  Point p1(1,0,0);
  Vector v0(1,1,0);
  Vector v1(1,-1,0);
  long nbU = 100;

  glColor3f(.6, 1.0, .6);
  drawPoint(p0);
  drawPoint(p1);
  
  Point *tabP = HermiteCubicCurve(p0, p1, v0, v1, nbU);

  glColor3f(1.0, 1.0, 1.0);

  DrawCurve(tabP,nbU);

  delete [] tabP;*/

  //exercice 2
  /*
  int nbControl = 5;
  int nbU = 1000;
  
  Point tabControl[nbControl];
  
  tabControl[0] = Point(-3,-3,0);
  tabControl[1] = Point(-2,2,0);
  tabControl[2] = Point(-1,-1,0);
  tabControl[3] = Point(0,-2,0);
  tabControl[4] = Point(2,3,0);



  glColor3f(.6, 1.0, .6);
  drawPoint(tabControl[0]);
  drawPoint(tabControl[1]);
  drawPoint(tabControl[2]);
  drawPoint(tabControl[3]);
  drawPoint(tabControl[4]);

  
  Point *tabP = BezierCurveByBernstein(tabControl,nbControl, nbU);
  
  glColor3f(1.0, 1.0, 1.0);
  DrawCurve(tabP,nbU);

  delete [] tabP;*/

  //exercice 3
  
  int nbControl = 4;
  int nbU = 100;

  
  Point tabControl[nbControl];
  
  tabControl[0] = Point(-3,3,0);
  tabControl[1] = Point(-1,-3,0);
  tabControl[2] = Point(1,3,0);
  tabControl[3] = Point(3,-3,0);

  
  glColor3f(.6, 1.0, .6);
  drawPoint(tabControl[0]);
  drawPoint(tabControl[1]);
  drawPoint(tabControl[2]);
  drawPoint(tabControl[3]);

  glColor3f(0,0.2,0.5);
  drawLine(tabControl[0], tabControl[1]);
  drawLine(tabControl[1], tabControl[2]);
  drawLine(tabControl[2], tabControl[3]);

  Point *tabP = BezierCurveByCasteljau(tabControl, nbControl, nbU);

  drawLine(tabControl[3], tabP[nbU-1]);

  glColor3f(.6, 1.0, .6);
  drawPoint(tabP[nbU-1]);

  glColor3f(1.0, 1.0, 1.0);
  
  DrawCurve(tabP,nbU);

  delete [] tabP;
}
//////////////////////////////////////////////////////////////////////////////////////////
// Fonction que vous allez modifier afin de dessiner
/////////////////////////////////////////////////////////////////////////////////////////
void render_scene()
{
  //Définition de la couleur
  glColor3f(1.0, 1.0, 1.0);

  TP2();
}
