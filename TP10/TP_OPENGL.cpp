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
#include "Fonction.h"
#include "Camera.h"
#include "CameraFreeFly.h"
#include "CameraView.h"
#include "Mesh.h"
#include <vector>

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

CameraFreeFly *camera = new CameraFreeFly(0.1,0.1,0.5,0,0,0);

//TP7
int meridiens = 10;


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
void update();
GLint gFramesPerSecond = 0;

void idle();

int main(int argc, char **argv) 
{  
  // initialisation  des paramètres de GLUT en fonction
  // des arguments sur la ligne de commande
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);

  // définition et création de la fenêtre graphique, ainsi que son titre
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition(0, 0);// Position de la fenêtre sur l'écran par rapport au coin haut gauche
  glutCreateWindow("TP10");

  // initialisation de OpenGL et de la scène
  initGL();  
  init_scene();
  glutIdleFunc(idle);

  // choix des procédures de callback pour 
  // le tracé graphique
  glutDisplayFunc(&window_display);// précise la fonction à utiliser pour l'affichage 

  // le redimensionnement de la fenêtre
  glutReshapeFunc(&window_reshape);// précise la fonction à utiliser pour le redimensionnement 

  // la gestion des événements clavier
  glutKeyboardFunc(&window_key);
  glutKeyboardUpFunc(&window_keyUp);

  // la gestion des événements souris
  glutMouseFunc(&onMouseButton);
  glutPassiveMotionFunc(&mouseMotion);

  // la boucle prinicipale de gestion des événements utilisateur
  glutMainLoop();// lance le gestionnaire glut

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
	//SMOOTH FLAT
	glShadeModel(GL_FLAT); 

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
 
  GLfloat light_ambient[] = { 0.686, 0.933, 0.933, 1.0 };
	GLfloat light_diffuse[] = { 0.686, 0.933, 0.933, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);

  //vision a travers l'objet ou pas
	glEnable(GL_CULL_FACE);
}

// fonction de call-back pour l´affichage dans la fenêtre

GLvoid window_display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;

  glLoadIdentity();
  glutWarpPointer(WIDTH/2 , HEIGHT/2);//pour une souris moins sensible

  update();

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

  gluPerspective(70,WIDTH/HEIGHT,0.01,1000); 
  glEnable(GL_DEPTH_TEST);

  // toutes les transformations suivantes s´appliquent au modèle de vue 
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

}


// fonction de call-back pour la gestion des événements clavier

GLvoid window_key(unsigned char key, int x, int y) 
{  
  switch (key)
  {
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
    meridiens ++;
    printf("%d \n", meridiens);
    break;
  case '-':
    keys[(int)'-'] = true;
    meridiens --;
    printf("%d \n", meridiens);
    break;
  default:
 	  keys[(int)key] = true;
    break;
  }     
}

GLvoid window_keyUp(unsigned char key, int x, int y) 
{  
  switch (key)
  {
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


void update()
{
  if(keys[KEY_ESC])
    closeProgram();	   
   

	camera->events(KEY_Q,KEY_D,
            KEY_Z ,KEY_S,
            KEY_SPACE,false,
            MOUSE_MOTION,Vector(-mouseX + WIDTH/2,-mouseY + HEIGHT/2,0));
  MOUSE_MOTION = false;
  if(keys[(int)'l'])
  {
		if(glIsEnabled(GL_LIGHTING))
			glDisable(GL_LIGHTING);
		else
			glEnable(GL_LIGHTING);

		keys[(int)'l'] = false;
	 }
}

void closeProgram()
{
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
  static GLuint Clock = glutGet(GLUT_ELAPSED_TIME);
  static GLfloat deltaT;
 
  Clock = glutGet(GLUT_ELAPSED_TIME);
  deltaT = Clock - PreviousClock;
  if (deltaT < 35) {return;} else {PreviousClock = Clock;}
  #endif
  
  FPS(); //only call once per frame loop 
  glutPostRedisplay();
}

Mesh mesh;
Mesh mesh2;
int load = 0;
double resolution = 1;
vector<Point> v;

void TP10()
{
  if(load == 0)
  {
    //exercice 1
    mesh.loadOffFile("OFF_Model/trice(12).off");

    double m = max(max( mesh.maxVertex.getX() - mesh.minVertex.getX(),
                    mesh.maxVertex.getY() - mesh.minVertex.getY()),
                    mesh.maxVertex.getZ() - mesh.minVertex.getZ());
    double d = sqrt(pow(mesh.minVertex.getX()-mesh.maxVertex.getX(),2)+pow(mesh.minVertex.getY()-mesh.maxVertex.getY(),2)+pow(mesh.minVertex.getZ()-mesh.maxVertex.getZ(),2));    

    mesh.simplificationParGrille(d+m, resolution, v);
    
    mesh2.loadOffFile("OFF_Model/trice(12).off");

    mesh.initColorDistance(mesh2);


    double diam = sqrt(pow(mesh.minVertex.getX()-mesh.maxVertex.getX(),2)+pow(mesh.minVertex.getY()-mesh.maxVertex.getY(),2)+pow(mesh.minVertex.getZ()-mesh.maxVertex.getZ(),2));
    double x = (mesh.minVertex.getX()+mesh.maxVertex.getX())/2.;
    double y = (mesh.minVertex.getY()+mesh.maxVertex.getY())/2.;
    double z = (mesh.minVertex.getZ()+mesh.maxVertex.getZ())/2.;

    Point c;
    c = Point(x,y,z); 

    camera->setSpeed(diam/100);

    camera->setPosition(c.getX()+(diam)/(tan(M_PI*70/180)/2),c.getY(),-(diam)/(tan(M_PI*70/180)/2));
    camera->setTarget(c.getX(),c.getY(),c.getZ());
    camera->setAngle(0,1,0);

    load = 1;
  }

  float LightPos1[4] = {mesh.minVertex.getX(),mesh.minVertex.getY(),mesh.minVertex.getZ(),1.};
  float LightPos0[4] = {mesh.maxVertex.getX(),mesh.maxVertex.getY(),mesh.maxVertex.getZ(),1.};

  glLightfv(GL_LIGHT0, GL_POSITION, LightPos0);
  glLightfv(GL_LIGHT1, GL_POSITION, LightPos1);

  GLfloat color_back[] = { 1.0, 0.0, 0.0, 1.0 };
  GLfloat color_front[] = { 1.0, 1.0, 1, 1.0 };


  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                 
  glCullFace(GL_FRONT);
  glColor4fv(color_front);

  mesh.drawMesh();

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                           
  glCullFace(GL_BACK);
  glColor4fv(color_back);
  
  mesh.drawMesh();


}

void render_scene()
{
  //Définition de la couleur
  //glColor3f(1.0, 1.0, 1.0);

  camera->draw();

  TP10();
}