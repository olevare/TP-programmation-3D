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
#include "tga.h"

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
  glutCreateWindow("TP11");

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
	//glEnable(GL_CULL_FACE);
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

void House(double size_x,double size_y,double size_z,double h_roof)
{
  //on active le placage de texture
  glEnable(GL_TEXTURE_2D);

  //image de la facade
  BYTE *img_facade;
  int largeur_facade;
  int hauteur_facade;

  //image du mur
  BYTE *img_mur;
  int largeur_mur;
  int hauteur_mur;

  //image du toit
  BYTE *img_toit;
  int largeur_toit;
  int hauteur_toit;

  //génère indice de texture
  GLuint texture;
  glGenTextures(3, &texture);

  img_facade = load_tga("facade.tga", &largeur_facade, &hauteur_facade);
  img_mur = load_tga("mur.tga", &largeur_mur, &hauteur_mur);
  img_toit = load_tga("toit.tga", &largeur_toit, &hauteur_toit);

  //on bind
  glBindTexture(GL_TEXTURE_2D, texture);

  //en faire une texture
  glTexImage2D(GL_TEXTURE_2D, 0, 3, largeur_mur, hauteur_mur, 0, GL_RGB, GL_UNSIGNED_BYTE, img_mur);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  //sol
  glBegin(GL_QUADS);
    glTexCoord2d(1,1);
    glVertex3d(-size_x,-size_y,0);
    glTexCoord2d(0,1);
    glVertex3d(-size_x, size_y,0);
    glTexCoord2d(0,0);
    glVertex3d( size_x, size_y,0);
    glTexCoord2d(1,0);
    glVertex3d( size_x,-size_y,0);
  glEnd();

  //murs
  glBegin(GL_QUADS);
    glNormal3d(0,-1,0);
    glTexCoord2d(1,1);
    glVertex3d( size_x,-size_y,0);
    glTexCoord2d(0,1);
    glVertex3d(-size_x,-size_y,0);
    glTexCoord2d(0,0);
    glVertex3d(-size_x,-size_y,size_z);
    glTexCoord2d(1,0);
    glVertex3d( size_x,-size_y,size_z);
  glEnd();

  glBegin(GL_QUADS);
    glNormal3d(0,1,0);
    glTexCoord2d(1,1);
    glVertex3d( size_x, size_y,0);
    glTexCoord2d(0,1);
    glVertex3d(-size_x, size_y,0);
    glTexCoord2d(0,0);
    glVertex3d(-size_x, size_y,size_z);
    glTexCoord2d(1,0);
    glVertex3d( size_x, size_y,size_z);
  glEnd();

  glBegin(GL_QUADS);
    glNormal3d(-1,0,0);
    glTexCoord2d(1,1);
    glVertex3d(-size_x, size_y,0);
    glTexCoord2d(0,1);
    glVertex3d(-size_x,-size_y,0);
    glTexCoord2d(0,0);
    glVertex3d(-size_x,-size_y,size_z);
    glTexCoord2d(1,0);
    glVertex3d(-size_x, size_y,size_z);
  glEnd();

  //triangle du toit
  glBegin(GL_TRIANGLES);
    glNormal3d(0,-1,0);
    glTexCoord2d(0,1);
    glVertex3d(-size_x,-size_y,size_z);
    glTexCoord2d(0.5, 1.0 - h_roof/size_z );
    glVertex3d(0,-size_y,size_z+h_roof);
    glTexCoord2d(1,1);
    glVertex3d( size_x,-size_y,size_z);
  glEnd();

  glBegin(GL_TRIANGLES);
    glNormal3d(0,1,0);
    glTexCoord2d(0,1);
    glVertex3d(-size_x, size_y,size_z);
    glTexCoord2d(0.5,1.0 - h_roof/size_z);
    glVertex3d(0, size_y,size_z+h_roof);
    glTexCoord2d(1,1);
    glVertex3d( size_x, size_y,size_z);
  glEnd();

  //on fait la texture avec la porte
  glTexImage2D(GL_TEXTURE_2D,0,3,largeur_facade,hauteur_facade,0,GL_RGB,GL_UNSIGNED_BYTE,img_facade);

  //mur avec porte
  glBegin(GL_QUADS);
    glNormal3d(1,0,0);
    glTexCoord2d(1,1);
    glVertex3d( size_x, size_y,0);
    glTexCoord2d(0,1);
    glVertex3d( size_x,-size_y,0);
    glTexCoord2d(0,0);
    glVertex3d( size_x,-size_y,size_z);
    glTexCoord2d(1,0);
    glVertex3d( size_x, size_y,size_z);
  glEnd();

  //on fait la texture du toit
  glTexImage2D(GL_TEXTURE_2D,0,3,largeur_toit,hauteur_toit,0,GL_RGB,GL_UNSIGNED_BYTE,img_toit);

  //toit
  glBegin(GL_QUADS);
    glNormal3d(-1,0,0);
    glTexCoord2d(1,1);
    glVertex3d(-size_x, size_y,size_z);
    glTexCoord2d(0,1);
    glVertex3d(-size_x,-size_y,size_z);
    glTexCoord2d(0,0);
    glVertex3d(0,-size_y,size_z+h_roof);
    glTexCoord2d(1,0);
    glVertex3d(0, size_y,size_z+h_roof);
  glEnd();

  glBegin(GL_QUADS);
    glNormal3d(1,0,0);
    glTexCoord2d(1,1);
    glVertex3d( size_x, size_y,size_z);
    glTexCoord2d(0,1);
    glVertex3d( size_x,-size_y,size_z);
    glTexCoord2d(0,0);
    glVertex3d( 0,-size_y,size_z+h_roof);
    glTexCoord2d(1,0);
    glVertex3d( 0, size_y,size_z+h_roof);
  glEnd();

  //on désactive le placage de texture
  glDisable(GL_TEXTURE_2D);
}

int load = 0;

Point c;
double maxX = 0;
double maxY = 10;
double maxZ = 10;

void TP11()
{

  House(4,5,5,3);

  if(load == 0)
  {

    double diam = sqrt(pow(-maxX-maxX,2)+pow(-maxY-maxY,2)+pow(-maxZ-maxZ,2));
    double x = 0;
    double y = 0;
    double z = 0;
    c = Point(x,y,z);         

    camera->setSpeed(diam/100);
    camera->setSensi(0.09);

    camera->setPosition(c.getX()+(diam)/(tan(M_PI*70/180)/2),c.getY(),-(diam)/(tan(M_PI*70/180)/2));
    camera->setTarget(c.getX(),c.getY(),c.getZ());
    camera->setAngle(1, 1, 1);

    load = 1;
  }

}

void render_scene()
{
  //Définition de la couleur
  //glColor3f(1.0, 1.0, 1.0);

  camera->draw();

  TP11();
}
