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
  glutCreateWindow("TP3");

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

void TP3()
{
  //Exercice 1
  /*
  int nbControl = 4;
  int nbU = 15;
  int nbV = 15;
  
  Point tabControl[nbControl];
  
  tabControl[0] = Point(-4,3,0);
  tabControl[1] = Point(-2.5,1,0);
  tabControl[2] = Point(-4,-1,0);
  tabControl[3] = Point(-2.5,-3,0);

  Point p1(-3,3,0);
  Point p2(3,2,0);

  Point *tabP = BezierCurveByBernstein(tabControl, nbControl, nbU);
  Point **tabPointSurfaceCylindrique = bezierSurfaceCylindrique(tabP,p1,p2,nbV,nbU);
  
  for(int i = 0; i < nbU-1; i++)
  {
    for(int j = 0; j < nbV-1; j++)
    {
        glColor3f(0.3,i/(double)nbU,j/(double)nbV);
        drawQuad(tabPointSurfaceCylindrique[i][j],tabPointSurfaceCylindrique[i][j+1],tabPointSurfaceCylindrique[i+1][j+1],tabPointSurfaceCylindrique[i+1][j]);
    }
  }

  glColor3f(253/255.,151/255.,31/255.);
  glLineWidth(3);//grossit la ligne
  DrawCurve(tabP,nbU);
  
  //efface le tableau de points
  for(int i = 0; i < nbU; i++)
    delete [] tabPointSurfaceCylindrique[i];
  
  delete [] tabPointSurfaceCylindrique;

  delete [] tabP;*/


  //Exercice 2
  /*
  int nbControl = 4;
  int nbU = 17;
  int nbV = 15;
  
  Point tabControl1[nbControl];
  
  tabControl1[0] = Point(-3,3,0);
  tabControl1[1] = Point(-2.5,1,0);
  tabControl1[2] = Point(-3,-1,0);
  tabControl1[3] = Point(-2.5,-3,0);


  Point tabControl2[nbControl];
  
  tabControl2[0] = Point(3,3,0);
  tabControl2[1] = Point(2.5,1,0);
  tabControl2[2] = Point(3,-1,0);
  tabControl2[3] = Point(2.5,-3,0);


  Point *tabP1 = BezierCurveByBernstein(tabControl1, nbControl, nbU);
  Point *tabP2 = BezierCurveByBernstein(tabControl2, nbControl, nbU);

  Point **tabPointSurfaceReglee = SurfaceReglee(tabP1,tabP2,nbV,nbU);
  
  for(int i = 0; i < nbU-1; i++)
  {
    for(int j = 0; j < nbV-1; j++)
    {
        glColor3f(0.3,i/(double)nbU,j/(double)nbV);
        drawQuad(tabPointSurfaceReglee[i][j],tabPointSurfaceReglee[i][j+1],tabPointSurfaceReglee[i+1][j+1],tabPointSurfaceReglee[i+1][j]);
    }
  }

  //ligne sur les cotés
  for(int i = 0; i < nbU; i++)
  {
    glColor3f(1,1,0);
    glLineWidth(5);
    DrawCurve(tabP1,nbU);
    DrawCurve(tabP2,nbU);
  }

  for(int i = 0; i < nbU; i++)
  {
    for(int j = 0; j < nbV; j++)
    {
        glColor3f(166/255.,226/255.,46/255.);
        //drawPoint(tabPointSurfaceReglee[i][j]);//colorie les points
    }
    delete [] tabPointSurfaceReglee[i];
  }

  //efface le tableau de points
  delete [] tabPointSurfaceReglee;

  delete [] tabP1;
  delete [] tabP2;*/


  //Exerice 3

  int nbControlU = 3;
  int nbControlV = 3;
  int nbU = 15;
  int nbV = 15;

  Point **tabControlPoint = new Point*[nbControlU];
  for(int i = 0; i < nbControlV; i++)
      tabControlPoint[i] = new Point[nbControlV];

  tabControlPoint[0][0] = Point(-1.5, -1.5, 0);
  tabControlPoint[0][1] = Point(-0.5, -0.5, 5);
  tabControlPoint[0][2] = Point(1.5, -1.5, 1);

  tabControlPoint[1][0] = Point(-1, -0.5, 0);
  tabControlPoint[1][1] = Point(0, 0, -0.5);
  tabControlPoint[1][2] = Point(2, -1.5, 1);

  tabControlPoint[2][0] = Point(-0.5, -0.5, 0);
  tabControlPoint[2][1] = Point(0.5, 0, -0.5);
  tabControlPoint[2][2] = Point(2.5, -1.5, 1);

  /*tabControlPoint[3][0] = Point(0, -1.5, 0);
  tabControlPoint[3][1] = Point(1, -0.5, -0.5);
  tabControlPoint[3][2] = Point(3, -1.5, 1);*/


  Point **tabPointSurfaceCasteljau = bezierSurfaceByCasteljau(tabControlPoint,nbControlU,nbU, nbControlV,nbV);
  
  for(int i = 0; i < nbU-1; i++)
  {
    for(int j=0;j<nbV-1;++j)
    {
        glColor3f(0.3,i/(double)nbU,j/(double)nbV);
        drawQuad(tabPointSurfaceCasteljau[i][j],tabPointSurfaceCasteljau[i][j+1],tabPointSurfaceCasteljau[i+1][j+1],tabPointSurfaceCasteljau[i+1][j]);
    }
  }

  for(int i = 0; i < nbU; i++)
  {
    for(int j = 0; j < nbV; j++)
    {
        glColor3f(1.,1.,1.);
        //drawPoint(tabPointSurfaceCasteljau[i][j]);
    }
    delete [] tabPointSurfaceCasteljau[i];
  }

  delete [] tabPointSurfaceCasteljau;
}
//////////////////////////////////////////////////////////////////////////////////////////
// Fonction que vous allez modifier afin de dessiner
/////////////////////////////////////////////////////////////////////////////////////////
void render_scene()
{
  //Définition de la couleur
  glColor3f(1.0, 1.0, 1.0);

  TP3();
}
