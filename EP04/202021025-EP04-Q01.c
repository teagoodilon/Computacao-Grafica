#include <GL/glut.h>
#include <stdio.h>
#include <cstdlib>
#include <chrono>
#include <thread>

GLint x0,y0,x1,y1;

void init(){
    glClearColor(0,0,0,0.0);
    glColor3f(1.0f,1.0f,1.0f);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,600.0,0.0,600.0);
}

void addLine(GLint xcoordinate, GLint ycoordinate){
    glBegin(GL_POINTS);
    glVertex2i(xcoordinate,ycoordinate);
    glEnd();
    glFlush();
}

void create(GLint x0,GLint y0,GLint x1,GLint y1){
    GLint dx = x1-x0;
    GLint dy = y1-y0;
    GLint steps,k;
    steps=dx;
    GLint x,y,p0=(2*dy)-dx;
    x=x0;
    y=y0;
    for(k=0;k<steps;k++){
        if(p0<0){
            p0=p0+(2*dy);
            x+=1;
        }
        else{
            p0=p0+(2*dy)-(2*dx);
            x+=1;
            y+=1;
        }
		addLine(x,y);
    }
}
void KeyboardFunc (unsigned char key, int x, int y){
	switch(key) {
		default:
			exit(0);
		break;
	}
	glutPostRedisplay();
}
void Display(void){
		x0= rand() % 600;
		y0= rand() % 600;
		x1= rand() % 600;
		y1= rand() % 600;
		create(x0,y0,x1,y1);
}
void IdleFunc(void) {
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	Display();
}
int main(int argc,char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Salva Tela");
	glutKeyboardFunc(KeyboardFunc);
    glutDisplayFunc(Display);
	init();
	glutIdleFunc(IdleFunc);
    glutMainLoop();
    return 0;
}