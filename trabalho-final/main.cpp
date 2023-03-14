#include <GL/glut.h>
#include <iostream>

#include "parameter.h"
#include "objects.h"
#include "light.h"

bool onOff =  false;//boleano de ligar e desligar
bool light = false;
int scene = 1;

bool escape_pressed = false;//controle tecla

GLfloat angle1, fAspect;
GLfloat deslocamentoX, deslocamentoY, deslocamentoZ;


void loadTexture(GLuint texture, const char* filename) {
	BmpLoader image(filename);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, image.iWidth, image.iHeight, GL_RGB, GL_UNSIGNED_BYTE, image.data);
}

void textureInit() {
	// Create Texture.
	textures = new GLuint[NUM_TEXTURE];
	glGenTextures(NUM_TEXTURE, textures);

	// Load the Texture.
	for (int i = 0; i < NUM_TEXTURE; i++)
		loadTexture(textures[i], texPath[i]);
}

void view(void)
{
	
	glMatrixMode(GL_PROJECTION);
	
	glLoadIdentity();

	gluPerspective(angle1,fAspect,0.5,500);

	
	glMatrixMode(GL_MODELVIEW);
	
	glLoadIdentity();

	gluLookAt(0+deslocamentoX,0+deslocamentoY,150+deslocamentoZ, 
		0+deslocamentoX,0+deslocamentoY,0+deslocamentoZ, 
		0,1,0);
}

void change_size(int w, int h) {

	if ( h == 0 ) h = 1;

	glViewport(0, 0, w, h);

	fAspect = (GLfloat)w/(GLfloat)h;

	view();
}

void renderScene()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glLoadIdentity();
	x = disXYZ[0];	lx = disLxLyLz[0];	
	z = disXYZ[2];	lz = disLxLyLz[2];
	gluLookAt(x, 5.0f, z,
		x + lx, y, z + lz,
		0.0f, 1.0f, 0.0f);
	
	
	if(scene== 2){
		glRotatef(40,0,1,0);
		glTranslatef(2,2,8);
	}
	
	drawCPU(onOff);
	

	glutSwapBuffers();
}



void processSpecialKeys(int key, int xx, int yy)
{
	float fraction = 0.001f;
	float fraction_rotate = 0.001f;
	
	if (!motion_present)
		return;
	switch (key) {
	case GLUT_KEY_HOME:
		angle -= deltaTime * fraction_rotate;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case GLUT_KEY_END:
		angle += deltaTime * fraction_rotate;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case GLUT_KEY_PAGE_UP:
		y < 1.4f ? y += deltaTime * fraction_rotate * 0.5 : y = 1.4f;
		break;
	case GLUT_KEY_PAGE_DOWN:
		y > -0.8f ? y -= deltaTime * fraction_rotate * 0.5 : y = -0.8f;
		break;

	}
	view();
	glutPostRedisplay();
}

void zoom(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN) {  // zoom in
			if (angle1 >= 10) angle1 -= 5;
		}
	if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN) {  // zoom out
			if (angle1 <= 130) angle1 += 5;
		}
	view();
	glutPostRedisplay();
}

void processNormalKeys(unsigned char key, int x, int y){
	switch (key) {
	case 13:if (page == 0) 
				motion_present = true;
			if (page == 1) {
				enterPressed = true;
				assemble = false;
				objIndex > REMOVE_MOTHERBOARD? objIndex:objIndex++;
			}
			 page = 1;			 
			 break;
	case 8:if (page == 1) {
			enterPressed = true;
			assemble = true;
			objIndex < -1 ? objIndex : objIndex--;
		   }
		   break;
	
	case 'y':
	case 'Y':choice = 'y'; 
	break;

	case 'n':
	case 'N':choice = 'n'; 
	break;

	case 'o': 
		onOff = false; 
		
	break;

	case 'i': 
		onOff = true;
	break;
	
	case 'l':
		if(light){
			light = false;
			show_light_effect(true);
		}else{
			show_light_effect(false);
			light = true;
		}
	break;

	case '1':
		scene = 1;
	break;

	case '2':
		scene = 2;
	break;
	
	case 27:escape_pressed = true;
			if (!motion_present && choice == 'y') {
				motion_present = true;
			}
			else
				exit(0);
	}
}

void opengl_init(void) {

	angle1=80;


	deslocamentoX = 0.0f;
	deslocamentoY = 0.0f;
	deslocamentoZ = 0.0f;

	glEnable(GL_DEPTH_TEST);
	textureInit();
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(change_size);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
	// Registra a fun��o callback que gerencia os eventos do mouse   
	glutMouseFunc(zoom);
	//glutPassiveMotionFunc(mouse_follow);

}


void setDeltaTime() {
	int timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = (timeSinceStart - oldTimeSinceStart) * 0.2f;
	oldTimeSinceStart = timeSinceStart;
}

int main(int argc, char ** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(width, hight);
	glutCreateWindow("Trabalho FInal Computação Gráfica");
	opengl_init();
	glutFullScreen();
	setDeltaTime();
	glutMainLoop();
	getchar();
	return 0;
}
