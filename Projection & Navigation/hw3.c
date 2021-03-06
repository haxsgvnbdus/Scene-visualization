/*
 * Code skeleton from lecture 
 * Draws a scene with a couple of houses
 *  3D Objects
 *
 *  Demonstrates how to draw objects in 3D.
 *
 *  Key bindings:
 *  a          Toggle axes
 *  arrows     Change view angle
 *  0          Reset view angle
 *  ESC        Exit
 *
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

int th=0;         //  Azimuth of view angle
int ph=-5;         //  Elevation of view angle
double zh=0;      //  Rotation of teapot
int axes=0;       //  Display axes


//  Cosine and Sine in degrees
#define Cos(x) (cos((x)*3.1415927/180))
#define Sin(x) (sin((x)*3.1415927/180))

/*
 *  Convenience routine to output raster text
 *  Use VARARGS to make this more flexible
 */
#define LEN 8192  //  Maximum length of text string
void Print(const char* format , ...)
{
   char    buf[LEN];
   char*   ch=buf;
   va_list args;
   //  Turn the parameters into a character string
   va_start(args,format);
   vsnprintf(buf,LEN,format,args);
   va_end(args);
   //  Display the characters one at a time at the current raster position
   while (*ch)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
}

    
static void drawHouse(double x, double y, double z,
		      double dx, double dy, double dz,
		      double th){
  
  const double rooftop = 2;
  const double roofoff = 1.5;
  const double roofwid = 1.25;
  const double roofbot = .75;
  glPushMatrix();
  
  // Translations
  glTranslated(x, y, z);
  glRotated(th, 0, 1, 0);
  glScaled(dx, dy, dz);

  // Body of house
  glBegin(GL_QUADS);
  //Front
  glColor3f(178,99,0);
  glVertex3f(-1,-1, 1);
  glVertex3f(+1,-1, 1);
  glVertex3f(+1,+1, 1);
  glVertex3f(-1,+1, 1);
  //  Back
  glColor3ub(190,99,0);
  glVertex3f(+1,-1,-1);
  glVertex3f(-1,-1,-1);
  glVertex3f(-1,+1,-1);
  glVertex3f(+1,+1,-1);
  //  Right
  glColor3ub(150,99,0);
  glVertex3f(+1,-1,+1);
  glVertex3f(+1,-1,-1);
  glVertex3f(+1,+1,-1);
  glVertex3f(+1,+1,+1);
  //  Left
  glColor3ub(150,99,0);
  glVertex3f(-1,-1,-1);
  glVertex3f(-1,-1,+1);
  glVertex3f(-1,+1,+1);
  glVertex3f(-1,+1,-1);
  //  Top
  glColor3ub(180,99,0);
  glVertex3f(-1,+1,+1);
  glVertex3f(+1,+1,+1);
  glVertex3f(+1,+1,-1);
  glVertex3f(-1,+1,-1);
  //  Bottom
  glColor3ub(1,1,1);
  glVertex3f(-1,-1,-1);
  glVertex3f(+1,-1,-1);
  glVertex3f(+1,-1,+1);
  glVertex3f(-1,-1,+1);
  glEnd();
  
  // Roof
  glBegin(GL_TRIANGLES);
  // Front
  glColor3ub(30,30,30);
  glVertex3f(+roofoff,+roofbot,+roofwid);
  glVertex3f(-roofoff,+roofbot,+roofwid);
  glVertex3f(0,+rooftop,+roofwid);
  // Back
  glVertex3f(+roofoff,+roofbot,-roofwid);
  glVertex3f(-roofoff,+roofbot,-roofwid);
  glVertex3f(0,+rooftop,-roofwid);
  glEnd();
  // Sides of Roof
  glBegin(GL_QUADS);
  // Right side
  glColor3f(130,60,40);
  glVertex3f(+roofoff,+roofbot,-roofwid);
  glVertex3f(+roofoff,+roofbot,+roofwid);
  glVertex3f(0,+rooftop,+roofwid);
  glVertex3f(0,+rooftop,-roofwid);
  // Left Side
  glColor3ub(140,90,90);
  glVertex3f(-roofoff,+roofbot,-roofwid);
  glVertex3f(-roofoff,+roofbot,+roofwid);
  glVertex3f(0,+rooftop,+roofwid);
  glVertex3f(0,+rooftop,-roofwid);  
  // Bottom
  glColor3ub(90,90,0);
  glVertex3f(+roofoff,+roofbot,-roofwid);
  glVertex3f(+roofoff,+roofbot,+roofwid);
  glVertex3f(-roofoff,+roofbot,+roofwid);
  glVertex3f(-roofoff,+roofbot,-roofwid);
  glEnd();

  // Draw the chimney
  glBegin(GL_QUADS);
  // Left
  glColor3ub(100,20,0);
  glVertex3f(+.5,+1,+.25);
  glVertex3f(+.5,+1,-.25);
  glVertex3f(+.5,+2,-.25);
  glVertex3f(+.5,+2,+.25);
  // Right
  glColor3ub(60,0,0);
  glVertex3f(+1,+1,+.25);
  glVertex3f(+1,+1,-.25);
  glVertex3f(+1,+2,-.25);
  glVertex3f(+1,+2,+.25);
  // Back
  glColor3ub(100,0,0);
  glVertex3f(+.5,+1,-.25);
  glVertex3f(+.5,+2,-.25);
  glVertex3f(+1,+2,-.25);
  glVertex3f(+1,+1,-.25);
  // Front
  glColor3ub(100,0,0);
  glVertex3f(+.5,+1,+.25);
  glVertex3f(+.5,+2,+.25);
  glVertex3f(+1,+2,+.25);
  glVertex3f(+1,+1,+.25);
  // Top
  glColor3ub(10,10,10);
  glVertex3f(+.5,+2,+.25);
  glVertex3f(+.5,+2,-.25);
  glVertex3f(+1,+2,-.25);
  glVertex3f(+1,+2,+.25);
  glEnd();

  // Draw a Door
  glBegin(GL_QUADS);
  glColor3f(50,100,70);

  // Front
  glVertex3f(+.2,-1,-1.1);
  glVertex3f(-.2,-1,-1.1);
  glVertex3f(-.2,0,-1.1);
  glVertex3f(+.2,0,-1.1);
  // Top
  glVertex3f(+.2,0,-1.1);
  glVertex3f(+.2,0,-1.0);
  glVertex3f(-.2,0,-1.0);
  glVertex3f(-.2,0,-1.1);
  // Right
  glVertex3f(+.2,0,-1.1);
  glVertex3f(+.2,-1,-1.1);
  glVertex3f(+.2,-1,-1.0);
  glVertex3f(+.2,0,-1.0);
  // Left
  glVertex3f(-.2,0,-1.1);
  glVertex3f(-.2,-1,-1.1);
  glVertex3f(-.2,-1,-1.0);
  glVertex3f(-.2,0,-1.0);
  glEnd();

  glPopMatrix();
}

/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
   const double len=1.5;  //  Length of axes
   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);
   //  Undo previous transformations
   glLoadIdentity();
   glOrtho(-3, 3, -3, 3, -10, 10);
   
   //  Set view angle
   glRotatef(ph,1,0,0);
   glRotatef(th,0,1,0);
   drawHouse(-4,0,0 , 1,1,1 , -30);
   drawHouse(0,0,0 , 1.5,1,1, 0);
   drawHouse(4,0,0 , 1,1,1 , 30);
   
   // Draw plane ground underneath 
   glColor3f(0,57,0);
   glBegin(GL_QUADS);
   glVertex3f(-100,-2,-100);
   glVertex3f(-100,-2,100);
   glVertex3f(100,-2,100);
   glVertex3f(100,-2,-100);
   glEnd();


   //  Draw axes
   if (axes)
   {
      glBegin(GL_LINES);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(len,0.0,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,len,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,0.0,len);
      glEnd();
      //  Label axes
      glRasterPos3d(len,0.0,0.0);
      Print("X");
      glRasterPos3d(0.0,len,0.0);
      Print("Y");
      glRasterPos3d(0.0,0.0,len);
      Print("Z");
   }
   //  Five pixels from the lower left corner of the window
   glWindowPos2i(5,5);
   //  Print the text string
   Print("Angle=%d,%d",th,ph);
   //  Render the scene
   glFlush();
   //  Make the rendered scene visible
   glutSwapBuffers();
}


/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{
   //  Right arrow key - increase angle by 5 degrees
   if (key == GLUT_KEY_RIGHT)
      th += 5;
   //  Left arrow key - decrease angle by 5 degrees
   else if (key == GLUT_KEY_LEFT)
      th -= 5;
   //  Up arrow key - increase elevation by 5 degrees
   else if (key == GLUT_KEY_UP)
      ph += 5;
   //  Down arrow key - decrease elevation by 5 degrees
   else if (key == GLUT_KEY_DOWN)
      ph -= 5;
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch,int x,int y)
{
   //  Exit on ESC
   if (ch == 27)
      exit(0);
   //  Reset view angle
   else if (ch == '0'){
      th = 0;
      ph = 5;
   }
   //  Toggle axes
   else if (ch == 'a' || ch == 'A')
      axes = 1-axes;
   
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
   const double dim=2.5;
   //  Ratio of the width to the height of the window
   double w2h = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, width,height);
   //  Tell OpenGL we want to manipulate the projection matrix
   glMatrixMode(GL_PROJECTION);
   //  Undo previous transformations
   glLoadIdentity();
   //  Orthogonal projection
   glOrtho(-w2h*dim,+w2h*dim, -dim,+dim, -dim,+dim);
   //  Switch to manipulating the model matrix
   glMatrixMode(GL_MODELVIEW);
   //  Undo previous transformations
   glLoadIdentity();
}

/*
 *  GLUT calls this routine when there is nothing else to do
 */
void idle()
{
   double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
   zh = fmod(90*t,360);
   glutPostRedisplay();
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
   //  Initialize GLUT and process user parameters
   glutInit(&argc,argv);
   //  Request double buffered, true color window with Z buffering at 600x600
   glutInitWindowSize(600,600);
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   //  Create the window
   glutCreateWindow("Domenic Murtari: Assignment 3");
   //  Tell GLUT to call "idle" when there is nothing else to do
   glutIdleFunc(idle);
   //  Tell GLUT to call "display" when the scene should be drawn
   glutDisplayFunc(display);
   //  Tell GLUT to call "reshape" when the window is resized
   glutReshapeFunc(reshape);
   //  Tell GLUT to call "special" when an arrow key is pressed
   glutSpecialFunc(special);
   //  Tell GLUT to call "key" when a key is pressed
   glutKeyboardFunc(key);
   //  Pass control to GLUT so it can interact with the user
   glutMainLoop();
   return 0;
}