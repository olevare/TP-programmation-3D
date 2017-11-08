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
#include <iostream>
#include <unistd.h>
#include "function.h"
#include "Octree.hpp"
#include "Camera.h"
#include "CameraFreeFly.h"
using namespace std;
/* Dans les salles de TP, vous avez généralement accès aux glut dans C:\Dev. Si ce n'est pas le cas, téléchargez les .h .lib ...
Vous pouvez ensuite y faire référence en spécifiant le chemin dans visual. Vous utiliserez alors #include <glut.h>. 
Si vous mettez glut dans le répertoire courant, on aura alors #include "glut.h" 
*/


// Définition de la taille de la fenêtre
#define WIDTH  800

#define HEIGHT 600

// Définition de la couleur de la fenêtre
#define RED   1
#define GREEN 0
#define BLUE  0
#define ALPHA 1


// Touche echap (Esc) permet de sortir du programme
#define KEY_ESC 27
bool KEY_Z = false, KEY_Q = false, KEY_S = false, KEY_D = false, KEY_SPACE = false ,MOUSE_MOTION = false;
bool keys[256];
int mouseX, mouseY;

Camera *camera = new CameraFreeFly(7,5,5,1.,0.,4.);


// Entêtes de fonctions
void init_scene();
void render_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height); 
GLvoid window_key(unsigned char key, int x, int y); 
GLvoid onMouseButton(int button, int state, int x, int y);
GLvoid mouseMotion(int x, int y);
GLvoid window_keyUp(unsigned char key, int x, int y);
void closeProgram();
GLint gFramesPerSecond = 0;

void idle();

void TP05();

int main(int argc, char **argv) 
{  
  // initialisation  des paramètres de GLUT en fonction
  // des arguments sur la ligne de commande
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);

  // définition et création de la fenêtre graphique, ainsi que son titre
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("TP prog 3D");

  // initialisation de OpenGL et de la scène
  initGL();  
  init_scene();
  glutIdleFunc(idle);

  glutDisplayFunc(&window_display);
  glutReshapeFunc(&window_reshape);

  glutKeyboardFunc(&window_key);
  glutKeyboardUpFunc(&window_keyUp);

  glutMouseFunc(&onMouseButton);
  glutPassiveMotionFunc(&mouseMotion);

  glutMainLoop();  

  return 1;
}

// initialisation du fond de la fenêtre graphique : noir opaque
GLvoid initGL() 
{
  glClearColor(0.0, 0.0, 0.0, 0.0);
}

// Initialisation de la scene. Peut servir à stocker des variables de votre programme
// à initialiser
void init_scene()
{
}

// fonction de call-back pour l´affichage dans la fenêtre

GLvoid window_display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
  glMatrixMode(GL_MODELVIEW);

  glLoadIdentity();

  render_scene();
  glFlush();
}

// fonction de call-back pour le redimensionnement de la fenêtre

GLvoid window_reshape(GLsizei width, GLsizei height)
{  
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //glOrtho(-4.0, 4.0, -4.0, 4.0, -4.0, 4.0);
  gluPerspective(70,(double)WIDTH/HEIGHT,1,1000);
  glEnable(GL_DEPTH_TEST);

  // toutes les transformations suivantes s´appliquent au modèle de vue 
  glMatrixMode(GL_MODELVIEW);
}

// fonction de call-back pour la gestion des événements clavier

GLvoid window_key(unsigned char key, int x, int y) 
{  
  switch (key) {
  case 'z':
    KEY_Z = true;
    break;
  case 'q':
    KEY_Q = true;
    break;
  case 's':
    KEY_S = true;
    break;
  case 'd':
    KEY_D = true;
    break;
  case ' ':
    KEY_SPACE = true;
    break;
  case '+':
	keys[(int)'+'] = true;
	break;
  case '-':
	keys[(int)'-'] = true;
	break;
  default:
 	keys[(int)key] = true;
    break;
  }     
}

GLvoid window_keyUp(unsigned char key, int x, int y) 
{  
  switch (key) {
  case 'z':
    KEY_Z = false;
    break;
  case 'q':
    KEY_Q = false;
    break;
  case 's':
    KEY_S = false;
    break;
  case 'd':
    KEY_D = false;
    break;
  case ' ':
    KEY_SPACE = false;
    break;
  case '+':
	keys[(int)'+'] = false;
	break;
  case '-':
	keys[(int)'-'] = false;
	break;
  default:
  	keys[(int)key] = false;
    break;
  }     
}

GLvoid mouseMotion(int x, int y)
{	
  mouseX = x;
  mouseY = y;
  MOUSE_MOTION = true;
}


void update(){
   if(keys[50]){
		mouseY+=15;
   }
   if(keys[52]){
	   mouseX-=15;
   }
   if(keys[54]){
	   mouseX+=15;
   }
   if(keys[56]){
		mouseY-=15;
   }
   if(keys[KEY_ESC]){
		closeProgram();	   
   }
   
	camera->events(KEY_Q,0.1,KEY_D,0.1,
            KEY_Z ,0.1,KEY_S,0.1,
            KEY_SPACE,0.1,false,0.1,
            false,4.0,
            MOUSE_MOTION,Vector(-mouseX + WIDTH/2,-mouseY + HEIGHT/2,0),0.2);
}

void closeProgram(){
	glutLeaveMainLoop();
}



GLvoid onMouseButton(int button, int state, int x, int y)
{
    int b;
    switch(button) {
      case GLUT_LEFT_BUTTON: glutSetCursor(GLUT_CURSOR_LEFT_ARROW);  break;
      case GLUT_MIDDLE_BUTTON: break;
      case GLUT_RIGHT_BUTTON:  
        glutSetCursor(GLUT_CURSOR_NONE); 
        break;
    }
}

 
void FPS(void) {
  static GLint Frames = 0;         // frames averaged over 1000mS
  static GLuint Clock;             // [milliSeconds]
  static GLuint PreviousClock = 0; // [milliSeconds]
  static GLuint NextClock = 0;     // [milliSeconds]
 
  ++Frames;
  Clock = glutGet(GLUT_ELAPSED_TIME); //has limited resolution, so average over 1000mS
  if ( Clock < NextClock ) return;
 
  gFramesPerSecond = Frames/1; // store the averaged number of frames per second
 
  PreviousClock = Clock;
  NextClock = Clock+1000; // 1000mS=1S in the future
  Frames=0;
}
 
void idle() {
  #define REGULATE_FPS
  #ifdef REGULATE_FPS
  static GLuint PreviousClock=glutGet(GLUT_ELAPSED_TIME);
  static GLuint Clock=glutGet(GLUT_ELAPSED_TIME);
  static GLfloat deltaT;
 
  Clock = glutGet(GLUT_ELAPSED_TIME);
  deltaT=Clock-PreviousClock;
  if (deltaT < 35) {return;} else {PreviousClock=Clock;}
  #endif
  
  FPS(); //only call once per frame loop 
  glutPostRedisplay();
}

void render_scene()
{
	//mouseX = WIDTH/2;//windows bug souris
	//mouseY = HEIGHT/2;//windows bug souris
  glutWarpPointer(WIDTH/2 , HEIGHT/2);

  update();
  
  camera->draw();

  TP05();
}

Octree o;
Octree o1;

void TP05()
{
    //exo sphere
		/*double rayon = 4;
		double length = rayon*4;
		double res = 0.3;
		Point axisOrigin(0,0,0);
		Point sphere(2,0,0);
		Vector axisVector(2	,0, 5);
		o = Octree(axisOrigin,length,res);
    o.displaySphereVolumic(rayon);*/

    //exo cylindre
    /*double rayon = 4;
    double length = rayon*4;
    double res = 0.3;
    Point axisOrigin(0,0,0);
    Point sphere(2,0,0);
    Vector axisVector(2 ,0, 5);
    o = Octree(axisOrigin,length,res);
    o.displayCylinderVolumic(axisOrigin,axisVector,rayon);*/

    //exo intersection
    /*double rayon = 4;
    double length = rayon*4;
    double res = 0.3;
    Point axisOrigin(0,0,0);
    Point sphere(2,0,0);
    Vector axisVector(2 ,0, 5);
    o = Octree(axisOrigin,length,res);
    o.displayIntersectionSphereCylinder(sphere, rayon, axisOrigin, axisVector, rayon, res);*/

    //exo soustraction
    /*double rayon = 4;
    double length = rayon*4;
    double res = 0.3;
    Point axisOrigin(0,0,0);
    Point sphere(2,0,0);
    Vector axisVector(2 ,0, 5);
    o = Octree(axisOrigin,length,res);
    o.displaySoustractionSphereCylinder(axisOrigin, rayon, axisOrigin, axisVector, rayon, res);*/

    //exo union
    double rayon = 4;
    double length = rayon*4;
    double res = 0.3;
    Point axisOrigin(0,0,0);
    Point sphere(2,0,0);
    Vector axisVector(2 ,0, 5);
    o = Octree(axisOrigin,length,res);
    o.displayUnionSphereCylinder(sphere, rayon, axisOrigin, axisVector, rayon, res);

	o.drawOctree();

}