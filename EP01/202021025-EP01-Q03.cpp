#include <GL/glut.h>
#include <iostream>

bool perspectiva = true;
GLfloat fAspect;
  
void RenderScene(void) { 
  glClearColor(0.0f,0.0f,0.0f,0.0f); 
  glClear( GL_COLOR_BUFFER_BIT ); 
  glBegin( GL_LINES ); 
    glColor3f(0.0f,0.0f,1.0f); 
    glVertex3f(0.0f,0.0f,0.0f); 
    glVertex3f(0.7f,0.0f,0.0f); 
    glColor3f(1.0f,0.0f,0.0f); 
    glVertex3f(0.0f,0.0f,0.0f); 
    glVertex3f(0.0f,0.5f,0.0f); 
    glColor3f(0.0f,1.0f,0.0f); 
    glVertex3f(0.0f,0.0f,0.0f); 
    glVertex3f(0.0f,0.0f,0.7f); 
  glEnd(); 
  glBegin( GL_POLYGON ); 
    glColor3f(1.0f,0.0f,0.0f); 
    glVertex3f(0.0f,0.0f,0.0f); 
    glVertex3f(0.0f,0.2f,0.0f); 
    glVertex3f(0.2f,0.3f,0.0f); 
    glVertex3f(0.4f,0.2f,0.0f); 
    glVertex3f(0.4f,0.0f,0.0f); 
  glEnd(); 
  glBegin( GL_QUADS ); 
    glColor3f(0.0f,0.0f,1.0f); 
    glVertex3f(0.0f,0.0f,0.0f); 
    glVertex3f(0.0f,0.0f,0.4f); 
    glVertex3f(0.0f,0.2f,0.4f); 
    glVertex3f(0.0f,0.2f,0.0f); 
  glEnd(); 
  glBegin( GL_QUAD_STRIP ); 
    glColor3f(0.0f,1.0f,0.0f); 
    glVertex3f(0.0f,0.2f,0.0f); 
    glVertex3f(0.0f,0.2f,0.4f); 
    glVertex3f(0.2f,0.3f,0.0f); 
    glVertex3f(0.2f,0.3f,0.4f); 
    glVertex3f(0.4f,0.2f,0.0f); 
    glVertex3f(0.4f,0.2f,0.4f); 
  glEnd(); 
  glColor3f(1.0f,1.0f,1.0f); 
  glBegin( GL_LINE_STRIP ); 
    glVertex3f(0.0f,0.0f,0.4f); 
    glVertex3f(0.4f,0.0f,0.4f); 
    glVertex3f(0.4f,0.0f,0.0f); 
  glEnd();
  glBegin( GL_LINES ); 
    glVertex3f(0.4f,0.0f,0.4f); 
    glVertex3f(0.4f,0.2f,0.4f); 
  glEnd(); 
  glBegin( GL_LINE_STRIP ); 
    glVertex3f(0.15f,0.0f,0.4f); 
    glVertex3f(0.15f,0.18f,0.4f); 
    glVertex3f(0.25f,0.18f,0.4f);
    glVertex3f(0.25f,0.0f,0.4f); 
  glEnd();
  glFlush(); 
} 
  
void ProjecaoParalela(void){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-0.7, 0.7, -0.7, 0.7, -400.0, 400.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1,1,1, 0,0,0, 0,1,0);
}

void ProjecaoPerspectiva(void){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60,fAspect,0.5,500);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1,1,1, 0,0,0, 0,1,0);
}

void ChangeSize(GLsizei width,GLsizei height) { 
  if ( height == 0 ) height = 1;
  glViewport(0,0,width,height);  
  fAspect = (GLfloat)width/(GLfloat)height;
  ProjecaoParalela();
}

void CallbackTeclado(unsigned char key, int x, int y) {
    switch (key){ 
      case 'p':
        perspectiva = !perspectiva;
        if(!perspectiva){
          ProjecaoPerspectiva();
          std::cout<<"Projecao atual: Perspectiva"<<std::endl;
        } else {
          ProjecaoParalela();
          std::cout<<"Projecao atual: Peralela"<<std::endl;
        }
        break;
    }
    glutPostRedisplay();
}
  
int main(int argc, char* argv[]) { 
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
  glutInitWindowSize (500, 500); 
  glutInitWindowPosition (100, 100); 
  glutCreateWindow("OpenGL - Poligonos"); 
  glutDisplayFunc(RenderScene);
  glutReshapeFunc(ChangeSize);
  glutKeyboardFunc(CallbackTeclado); 
  glutMainLoop(); 
  return 0;
} 
