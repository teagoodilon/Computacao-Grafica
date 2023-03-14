#ifndef MOTION
#define MOTION

#include "parameter.h"
#include "objects.h"

bool escape_pressed = false;

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
}

void processNormalKeys(unsigned char key, int x, int y)
{
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
	case 'Y':choice = 'y'; break;

	case 'n':
	case 'N':choice = 'n'; break;
	case 27:escape_pressed = true;
			if (!motion_present && choice == 'y') {
				motion_present = true;
			}
			else
				exit(0);
	}
}

void mouseLeftButton(int _x, int _y);
void mouseLeftButtonRealeaseEvent();

//iniciando as variaveis de rotacao
/*float angle;

bool has_rotation_started;
int start_x;
int start_y;
*/
#endif MOTION