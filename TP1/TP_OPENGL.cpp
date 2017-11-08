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
  glutCreateWindow("TP1");

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
  glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);

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



//////////////////////////////////////////////////////////////////////////////////////////
// Fonction que vous allez modifier afin de dessiner
/////////////////////////////////////////////////////////////////////////////////////////
void render_scene()
{
  //Définition de la couleur
  glColor3f(1.0, 1.0, 1.0);

  Point B(-1,2,0);
  Point C( 1,1,0);

  Point A( 0.5,1.5,0);  

  glColor3f(1.0, 1.0, 0.0);
  drawPoint(A);

  glColor3f(1.0, 1.0, 1.0);
  drawLine(B,C);
  
  glColor3f(0.0, 0.0, 1.0);
  drawPoint(A.ProjectOnLine(B,C));

  // Test ProjectOnLine(V,Pt)

  Vector v(2.0,-1.0,0);
  Point D( -1,0.5,0);

  Point E( 0.5,0.5,0);  

  glColor3f(1.0, 1.0, 0.0);
  drawPoint(E);

  glColor3f(1.0, 1.0, 1.0);
  drawLine(v,D);
  
  glColor3f(0.0, 0.0, 1.0);
  drawPoint(E.ProjectOnLine(v,D));

  // Test ProjectOnPlan(Pt,V)

  Vector n(0.2,0.5,0);
  Point P( -1.2,-1.2,0);

  Point M( -0.3,-0.8,0);
  
  glColor3f(1.0, 1.0, 0.0);
  drawPoint(M);

  glColor3f(0.0, 1.0, 0.0);
  drawLine(n,P);
  glColor3f(1.0, 1.0, 1.0);
  drawLine(Vector(-n.getY(),n.getX(),n.getZ()),P);
  drawLine(Vector(n.getY()*2.0,-n.getX()*2.0,n.getZ()),P);

  glColor3f(0.0, 0.0, 1.0);
  drawPoint(M.ProjectOnPlan(P,n));
  glEnd();
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
