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

//TP4 exo3
int meridiens = 8;
int paralleles = 8;


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

void idle();

int main(int argc, char **argv) 
{  
  // initialisation  des paramètres de GLUT en fonction
  // des arguments sur la ligne de commande
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA);// GLUT_RGBA mode "vraies couleurs" 32 bits

  // définition et création de la fenêtre graphique, ainsi que son titre
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition(0, 0);// Position de la fenêtre sur l'écran par rapport au coin haut gauche
  glutCreateWindow("TP4");

  // initialisation de OpenGL et de la scène
  initGL();  
  init_scene();
  glutIdleFunc(&idle);

  // choix des procédures de callback pour 
  // le tracé graphique
  glutDisplayFunc(&window_display);// précise la fonction à utiliser pour l'affichage 

  // le redimensionnement de la fenêtre
  glutReshapeFunc(&window_reshape);// précise la fonction à utiliser pour le redimensionnement 

  // la gestion des événements clavier
  glutKeyboardFunc(&window_key);

  // la boucle prinicipale de gestion des événements utilisateur
  glutMainLoop();// lance le gestionnaire glut

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

void idle()
{
  static GLuint PreviousClock = glutGet(GLUT_ELAPSED_TIME);
  static GLuint Clock = glutGet(GLUT_ELAPSED_TIME);
  static GLfloat deltaT;
 
  Clock = glutGet(GLUT_ELAPSED_TIME);
  deltaT = Clock - PreviousClock;
  if (deltaT < 35)
    return;
  else
    PreviousClock = Clock;
  
  glutPostRedisplay();
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

  // trace la scène graphique qui vient juste d'être définie
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
  glOrtho(-30.0, 30.0, -30.0, 30.0, -30.0, 30.0);

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

    case '+':
      meridiens ++;
      paralleles ++;
      printf("%d \n", meridiens);
      break;

    case '-':
      meridiens --;
      paralleles --;
      printf("%d \n", meridiens);
      break;
    
    default:
      printf ("La touche %d n´est pas active.\n", key);
      break;
  }     
}

void TP4()
{
  //Exercice 1

  //crée le tableau de points
  /*Point ** tabmeridiens;

  int hauteur = 20;
  int rayon = 10;

  tabmeridiens =  facettisationCylindre(hauteur, rayon, meridiens);
  
  for(int i = 0; i < meridiens-1; i++)
  {
    for(int j = 0; j < 1; j++)
    {
      glColor3f(1.0f, 0.0f, 0.0f);//couleur rouge
      drawLine(tabmeridiens[i][j], tabmeridiens[i][j+1]);
      glColor3f(0,0.6,0);//couleur vert
      drawQuad(tabmeridiens[i][j], tabmeridiens[i][j+1], tabmeridiens[i+1][j+1], tabmeridiens[i+1][j]);
    }
  }

  for(int i = 0; i < meridiens; i++)
  {
    //efface le tableau de points
    delete [] tabmeridiens[i];
  }

  //efface le tableau de points
  delete [] tabmeridiens;*/

  //Exercice 2

  //crée le tableau de points
  /*Point *tabmeridiens;

  int hauteur = 20;
  int rayon = 15;

  Point base(0,0,20);

  tabmeridiens =  getCones(rayon, hauteur, meridiens);
  for(int i = 0; i < meridiens-1; i++)
  {
    glColor3f(1.0f, 0.0f, 0.0f);//couleur rouge
    drawTriangle(tabmeridiens[i], tabmeridiens[i+1], base);
  }

  glColor3f(1,1,1);//couleur blanche

  for(int i = 0; i < meridiens; i++)
  {
    drawLine(tabmeridiens[i], base);
    drawPoint(tabmeridiens[i]);
  }
  //efface le tableau de points
  delete [] tabmeridiens;*/
  
  //Exercice3

  int rayon = 20;

  Point ** sphere = getSphere(Point(0,0,0), rayon , meridiens, paralleles);
  for(int i = 0; i < meridiens-1; i++)
  {
    for(int j = 0; j < paralleles-1; j++)
    {
      //collones
      glColor3f(1.0f, 0.0f, 0.0f);//couleur rouge
      drawLine(sphere[i][j], sphere[i][j+1]);

      //lignes
      glColor3f(0.5f, 0.0f, 1.0f);//couleur bleu
      drawLine(sphere[i][j], sphere[i+1][j]);

      //faces
      glColor3f(0,0.6,0);//couleur vert
      drawQuad(sphere[i][j], sphere[i][j+1], sphere[i+1][j+1], sphere[i+1][j]);
    }
  }
  for(int i = 0; i < meridiens; i++)
  {
    //affiche les points
    for(int j = 0; j < paralleles; j++)
    {
        //glColor3f(1.,1.,1.);
        //drawPoint(sphere[i][j]);
    }
    //efface le tableau de points
    delete [] sphere[i];
  }
  //efface le tableau de points
  delete [] sphere;
  
}
//////////////////////////////////////////////////////////////////////////////////////////
// Fonction que vous allez modifier afin de dessiner
/////////////////////////////////////////////////////////////////////////////////////////

void render_scene()
{
  //Définition de la couleur
  glColor3f(1.0, 1.0, 1.0);

  gluLookAt(0.0, 0.0, 0.0, 3.0, 5.0, -10.0, 0.0, 1.0, 0.0);

  TP4();
}
