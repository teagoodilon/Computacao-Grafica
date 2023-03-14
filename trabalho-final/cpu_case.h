#ifndef CPU_CASE
#define CPU_CASE

#include <GL/glut.h>
#include "cpu_fan.h"

class cpu_case {
private:GLfloat cpuHight = 2., cpuWidth = 1.,cpuLength = 2.5;
		GLfloat cabinetColor[3] = { 0, 0, 0};
		double regionRadius = 2.;
		bool visible = true;
		bool objMove = false;
		point3D move;			// Desenhos do gabinete:
		void draw_front();		// Frente
		void draw_rightSide();	// Lado direito
		void draw_back();		// Traseira
		void draw_bottom();		// Parte de baixo
		void draw_top();		// Topo
		void draw_sidebar();	// Barra lateral
		void draw_rim();		// Bordas
		void draw_legs();		// Pés
		void draw_side_panel(); // painel lateral
		void motionHandle();	// Animação de retirada da tampa lateral

public:	void render();
};

void cpu_case::render() {
	
	glPushMatrix();

	glTranslatef( cpuWidth/2 + 6.6 , 3.5 , -2.7);
	
	draw_front();
	draw_rightSide();
	draw_back();
	draw_bottom();
	draw_top();
	draw_sidebar();
	draw_rim();
	draw_legs();
	draw_side_panel();

	glPopMatrix();

}

void cpu_case::motionHandle() {
	if (((enterPressed && objIndex == REMOVE_SIDE_PANEL) || objMove == true) && !assemble)
	{
		objMove = true;
		move.x -= 0.007;
		if (move.x < disapphereLimit)
		{
			enterPressed = false;
			visible = false;
			objMove = false;
		}

	}
	else if (((enterPressed && objIndex == REMOVE_SIDE_PANEL - 1) || objMove == true) && assemble)
	{
		objMove = true;
		visible = true;
		move.x += 0.007;

		if (move.x >= 0)
		{
			enterPressed = false;
			objMove = false;
		}

	}
}

void cpu_case::draw_side_panel() 
{
	motionHandle();
	if (!visible) return;
	glPushMatrix();
	glTranslatef(move.x, move.y, move.z);
	
	GLfloat ymin = -0.35 * 0.37, ymax = cpuHight;
	GLfloat xmin = -cpuLength, xmax = 0.;
	GLfloat xPos = -0.016;

	GLfloat frameThickness = .1;

	glBegin(GL_POLYGON);
		glVertex3f(xPos, ymin, xmin);
		glVertex3f(xPos, frameThickness, xmin);
		glVertex3f(xPos, frameThickness, xmax);
		glVertex3f(xPos, ymin, xmax);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(xPos, ymin, xmin);
	glVertex3f(xPos, ymax, xmin);
	glVertex3f(xPos, ymax, xmin + frameThickness);
	glVertex3f(xPos, ymin, xmin + frameThickness);
	glEnd();
	
	glBegin(GL_POLYGON);
	glVertex3f(xPos, ymax - frameThickness, xmin);
	glVertex3f(xPos, ymax, xmin);
	glVertex3f(xPos, ymax, xmax);
	glVertex3f(xPos, ymax - frameThickness, xmax);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(xPos, ymin, xmax - cpuLength * .35);
	glVertex3f(xPos, ymax, xmax - cpuLength * .35);
	glVertex3f(xPos, ymax, xmax);
	glVertex3f(xPos, ymin, xmax);
	glEnd();

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glColor4f(0,1, 0, .10);
	glBegin(GL_POLYGON);
	glVertex3f(xPos + 0.001, ymin + frameThickness, xmax - cpuLength * .35);
	glVertex3f(xPos + 0.001, ymax - frameThickness, xmax - cpuLength * .35);
	glVertex3f(xPos + 0.001, ymax - frameThickness, xmin + frameThickness);
	glVertex3f(xPos + 0.001, ymin + frameThickness, xmin + frameThickness);
	glEnd();
	glDisable(GL_BLEND);

	glPopMatrix();
}

void cpu_case::draw_rim() {
	GLfloat thickness = 0.08;
	GLfloat frontSpace = 0.07;

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	
	glBindTexture(GL_TEXTURE_2D, textures[CASE_RIM_LEFT]);
	glColor3f(1., 1., 1.);
	glBegin(GL_POLYGON);
	glTexCoord2f(0., 1.);	glVertex3f(-0.0012, 0., -cpuLength + thickness);
	glTexCoord2f(1., 1.);	glVertex3f(-0.0012, cpuHight, -cpuLength + thickness);
	glTexCoord2f(1., 0.);	glVertex3f(-0.0012, cpuHight, -cpuLength);
	glTexCoord2f(1., 0.);	glVertex3f(-0.0012, 0., -cpuLength);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textures[CASE_RIM_RIGHT]);
	glBegin(GL_POLYGON);
	glTexCoord2f(0., 1.);	glVertex3f(-0.0012, 0., -thickness - frontSpace);
	glTexCoord2f(1., 1.);	glVertex3f(-0.0012, cpuHight, -thickness - frontSpace);
	glTexCoord2f(1., 0.);	glVertex3f(-0.0012, cpuHight, -frontSpace);
	glTexCoord2f(1., 0.);	glVertex3f(-0.0012, 0., -frontSpace);
	glEnd();

	glBegin(GL_POLYGON);
	glBindTexture(GL_TEXTURE_2D, textures[CASE_RIM_TOP]);
	glTexCoord2f(0., 1.);	glVertex3f(-0.0012, cpuHight, -cpuLength);
	glTexCoord2f(0., 0.);	glVertex3f(-0.0012, cpuHight -thickness, -cpuLength);
	glTexCoord2f(1., 0.);	glVertex3f(-0.0012, cpuHight -thickness, -frontSpace);
	glTexCoord2f(1., 1.);	glVertex3f(-0.0012, cpuHight, -frontSpace);
	glEnd();
	
	glBegin(GL_POLYGON);
	glBindTexture(GL_TEXTURE_2D, textures[CASE_RIM_BOTTOM]);
	glTexCoord2f(0., 0.);	glVertex3f(-0.0012, 0., -cpuLength);
	glTexCoord2f(1., 0.);	glVertex3f(-0.0012, 0., -frontSpace);
	glTexCoord2f(1., 1.);	glVertex3f(-0.0012, -thickness, -frontSpace);
	glTexCoord2f(0., 1.);	glVertex3f(-0.0012, -thickness, -cpuLength);
	glEnd();


	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

}

void cpu_case::draw_back() {

	glPushMatrix();
	glLineWidth(5.0);
	glColor3fv(cabinetColor);
	glTranslatef(0.1, 1.1, -cpuLength);
	glScalef(0.2, 0.2, 1.);
	for (GLfloat i = 0; i <= 8; i = i+0.3) {
		if (i <= 4) {
			glPushMatrix();
			glBegin(GL_LINES);
			glVertex3f(i, 0., -0.02 );
			glVertex3f(0., i, -0.02 );
			glEnd();
			glPopMatrix();
			glPushMatrix();
			glBegin(GL_LINES);
			glVertex3f(0., 4.-i, -0.02 );
			glVertex3f(i, 4, -0.02 );
			glEnd();
			glPopMatrix();
		}
		else {
			glPushMatrix();
			glBegin(GL_LINES);
			glVertex3f(4, i - 4., -0.02);
			glVertex3f(i-4. , 4., -0.02);
			glEnd();
			glPopMatrix();
			glPushMatrix();
			glBegin(GL_LINES);
			glVertex3f(i-4., 0., -0.02);
			glVertex3f(4., 4. - abs(i-4.), -0.02);
			glEnd();
			glPopMatrix();
		}
	}
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0., 0., -cpuLength);

	glColor3fv(cabinetColor);
	glBegin(GL_POLYGON);
		glVertex3f(0., 2.,0.);
		glVertex3f(.15, 2., 0.);
		glVertex3f(.15, 1.2, 0.);
		glVertex3f(0., 1.2, 0.);
	glEnd();
		
	glBegin(GL_POLYGON);
	glVertex3f(1., 2., 0.);
	glVertex3f(1-.15, 2., 0.);
	glVertex3f(1-.15, 1.2, 0.);
	glVertex3f(1., 1.2, 0.);
	glEnd();
	
	glBegin(GL_POLYGON);
		glVertex3f(0., 2., 0.);
		glVertex3f(1., 2., 0.);
		glVertex3f(1., 1.85, 0.);
		glVertex3f(0., 1.85, 0.);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0., 1.2, 0.);
	glVertex3f(1., 1.2, 0.);
	glVertex3f(1., .4, 0.);
	glVertex3f(0., .4, 0.);
	glEnd();

	GLfloat thickness = .04;
	glBegin(GL_POLYGON);
	
	glColor3fv(cabinetColor);

	glVertex3f(0., 2., -thickness);
	glVertex3f(.15, 2., -thickness);
	glVertex3f(.15, 0., -thickness);
	glVertex3f(0., 0., -thickness);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(1., 2., -thickness);
	glVertex3f(1 - .15, 2., -thickness);
	glVertex3f(1 - .15, 0., -thickness);
	glVertex3f(1., 0., -thickness);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0., 2., -thickness  );
	glVertex3f(1., 2., -thickness  );
	glVertex3f(1., 1.85, -thickness  );
	glVertex3f(0., 1.85, -thickness  );
	glEnd();

	glEnable(GL_TEXTURE_2D);
	glColor3f(1., 1., 1.);
	glBindTexture(GL_TEXTURE_2D, textures[CASE_BEHIND]);
	glBegin(GL_POLYGON);
		glTexCoord2f(0., 1.);	glVertex3f(.15, 1.2, -thickness);
		glTexCoord2f(1., 1.);	glVertex3f(1. - .15, 1.2, -thickness  );
		glTexCoord2f(1., 0.);	glVertex3f(1. - .15, .27, -thickness  );
		glTexCoord2f(0., 0.);	glVertex3f(.15, .27, -thickness  );
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glColor3fv(cabinetColor);
	glBegin(GL_QUAD_STRIP);
		glVertex3f(0., 0., 0.  );
		glVertex3f(0., 0., -thickness  );
		glVertex3f(cpuWidth, 0., 0.  );
		glVertex3f(cpuWidth, 0., -thickness  );
		glVertex3f(cpuWidth, cpuHight, 0.  );
		glVertex3f(cpuWidth, cpuHight, -thickness  );
		glVertex3f(0., cpuHight, 0.  );
		glVertex3f(0., cpuHight, -thickness  );
		glVertex3f(0., 0., 0.);
		glVertex3f(0., 0., -thickness);
	glEnd();

	glPopMatrix();
}

void cpu_case::draw_rightSide() {
	GLfloat rightV[][3] = { {1., 0., 0.},
	{1., cpuHight, 0.},
	{1., cpuHight, -cpuLength},
	{1., 0, -cpuLength} };

	glPushMatrix();
	glColor3fv(cabinetColor);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 4; i++)
		glVertex3fv(rightV[i]);
	glEnd();

	glColor3fv(cabinetColor);
	glBegin(GL_POLYGON);
	GLfloat thickness = 0.04;
	for (int i = 0; i < 4; i++)
		glVertex3f(rightV[i][0] - thickness, rightV[i][1], rightV[i][2]);
	glEnd();
	
	glColor3fv(cabinetColor);
	glBegin(GL_QUAD_STRIP);
	for (int i = 0; i < 4; i++) {
		glVertex3fv(rightV[i]);
		glVertex3f(rightV[i][0]- thickness, rightV[i][1], rightV[i][2]);
	}
	glEnd();

	GLfloat nearZ = cpuLength * 0.28;
	GLfloat lowBound = 0.35;

	glEnable(GL_TEXTURE_2D);
	glColor3f(1., 1., 1.);
	glBindTexture(GL_TEXTURE_2D, textures[CPU_INSIDE_WALL]);
	glBegin(GL_POLYGON);
	glTexCoord2i(0, 0);		glVertex3f(cpuWidth - thickness - 0.01, lowBound, -cpuLength + 0.08);
	glTexCoord2i(1, 0);		glVertex3f(cpuWidth - thickness - 0.01, lowBound, -nearZ);
	glTexCoord2i(1, 1);		glVertex3f(cpuWidth - thickness - 0.01, cpuHight - 0.04, -nearZ);
	glTexCoord2i(0, 1);		glVertex3f(cpuWidth - thickness - 0.01, cpuHight - 0.04, -cpuLength + 0.08);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void cpu_case::draw_front() {

	glColor3f(0., 0., 0.);

	GLfloat v[6][3] = { {0., 0., 0},
							{0., 1.9, 0},
							{0.5, 1.9, 0},
							{ 0.7, 2., 0 },
							{ 1., 2., 0 },
							{1., 0., 0 }};
	
	glPushMatrix();
	glBegin(GL_POLYGON);
	for (int i = 0; i < 6; i++)
		glVertex3fv(v[i]);
	glEnd();

	GLfloat thickness = 0.04;
	glBegin(GL_POLYGON);
	for (int i = 0; i < 6; i++)
		glVertex3f(v[i][0], v[i][1], v[i][2]-thickness);
	glEnd();

	glBegin(GL_QUAD_STRIP);
	for (int i = 0; i < 6; i++)
	{
		glVertex3fv(v[i]);
		glVertex3f(v[i][0], v[i][1], v[i][2]-thickness);
	}
	glEnd();

	// Logo da razer
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[RAZER_LOGO]);
	glColor3f(0., 1., 0.);
	glBegin(GL_POLYGON);
		glTexCoord2f(0., 0.);	glVertex3f(0.+.25, 0.+.75, 0.001);
		glTexCoord2f(0., 1.);	glVertex3f(0.+.25, .5+.75, 0.001);
		glTexCoord2f(1., 1.);	glVertex3f(.5+.25, .5+.75, 0.001);
		glTexCoord2f(1., 0.);	glVertex3f(.5+.25, 0.+.75, 0.001);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glPushMatrix();
	glColor3f(0., 0., 0.);
	glBegin(GL_POLYGON);
		glVertex3f(0., 0., -thickness - 0.01);
		glVertex3f(cpuWidth, 0., -thickness - 0.01);
		glVertex3f(cpuWidth, cpuHight, -thickness - 0.01);
		glVertex3f(0., cpuHight, -thickness - 0.01);
	glEnd();
	glPopMatrix();

	glPopMatrix();
}

void cpu_case::draw_bottom() {
	GLfloat thickness = 0.35;
	GLfloat ymin = -thickness * 0.37;

	glPushMatrix();
	glColor3f(0., 0., 0.);
	glBegin(GL_POLYGON);
		glVertex3f(0.001, ymin, 0.);
		glVertex3f(0.001, ymin, -cpuLength - 0.04);
		glVertex3f(cpuWidth - 0.001, ymin, -cpuLength - 0.04);
		glVertex3f(cpuWidth - 0.001, ymin, 0.);
	glEnd();


	glBegin(GL_POLYGON);
		glVertex3f(0.001, thickness, 0.);
		glVertex3f(0.001, thickness, -cpuLength - 0.04);
		glVertex3f(cpuWidth, thickness, -cpuLength - 0.04);
		glVertex3f(cpuWidth, thickness, 0.);
	glEnd();
	
	glBegin(GL_POLYGON);
		glVertex3f(0.001, ymin, 0.);
		glVertex3f(0.001, thickness, 0.);
		glVertex3f(0.001, thickness, -cpuLength - 0.04);
		glVertex3f(0.001, ymin, -cpuLength - 0.04);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(cpuWidth - 0.001, ymin, 0.);
	glVertex3f(cpuWidth - 0.001, thickness, 0.);
	glVertex3f(cpuWidth - 0.001, thickness, -cpuLength - 0.04);
	glVertex3f(cpuWidth - 0.001, ymin, -cpuLength - 0.04);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0.001, 0., 0.);
	glVertex3f(cpuWidth, 0., 0.);
	glVertex3f(cpuWidth, ymin, 0.);
	glVertex3f(0.001, ymin, 0.);
	glEnd();
	
	glBegin(GL_POLYGON);
	glVertex3f(0.001, 0., -cpuLength);
	glVertex3f(cpuWidth, 0., -cpuLength);
	glVertex3f(cpuWidth, ymin, -cpuLength);
	glVertex3f(0.001, ymin, -cpuLength);
	glEnd();

	// logo da fonte
	glEnable(GL_TEXTURE_2D);
	glColor3f(0., 1., 0.);
	glBindTexture(GL_TEXTURE_2D, textures[RAZER_LOGO]);
	glBegin(GL_POLYGON);
	glTexCoord2f(1., 1.); glVertex3f(-0.001, 0., -cpuLength * 0.15 -cpuLength / 2 - thickness / 2);
	glTexCoord2f(1., 0.); glVertex3f(-0.001, 0., -cpuLength * 0.15 -cpuLength / 2 + thickness / 2);
	glTexCoord2f(0., 0.); glVertex3f(-0.001, thickness, -cpuLength * 0.15 -cpuLength / 2 + thickness / 2);
	glTexCoord2f(0., 1.); glVertex3f(-0.001, thickness, -cpuLength * 0.15 -cpuLength / 2 - thickness / 2);
	glEnd();

	glDisable(GL_TEXTURE_2D);


	glPopMatrix();
}

void cpu_case::draw_top() {

	GLfloat thickness = 0.05;
	glPushMatrix();
	glColor3fv(cabinetColor);

	glBegin(GL_POLYGON);
	glVertex3f(0.7, cpuHight, -.04);
	glVertex3f(0.5, cpuHight, 0.);
	glVertex3f(0., cpuHight, 0.);
	glVertex3f(0., cpuHight, -cpuLength - 0.04);
	glVertex3f(cpuWidth, cpuHight, -cpuLength - 0.04);
	glVertex3f(cpuWidth, cpuHight, -.04);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0.7, thickness + cpuHight, -.04);
	glVertex3f(0.5, thickness + cpuHight, 0.);
	glVertex3f(0., thickness+ cpuHight, 0.);
	glVertex3f(0., thickness+ cpuHight, -cpuLength - 0.04);
	glVertex3f(cpuWidth, thickness+ cpuHight, -cpuLength - 0.04);
	glVertex3f(cpuWidth, thickness+ cpuHight, -.04);
	glEnd();

	glColor3fv(cabinetColor);
	glBegin(GL_POLYGON);
	glVertex3f(0., cpuHight, 0.);
	glVertex3f(0., thickness+ cpuHight, 0.);
	glVertex3f(0., thickness+ cpuHight, -cpuLength - 0.04);
	glVertex3f(0., cpuHight, -cpuLength - 0.04);
	glEnd();
	
	glColor3fv(cabinetColor);
	glBegin(GL_POLYGON);
	glVertex3f(cpuWidth, cpuHight, -.1);
	glVertex3f(cpuWidth, thickness + cpuHight, -.1);
	glVertex3f(cpuWidth, thickness + cpuHight, -cpuLength - 0.04);
	glVertex3f(cpuWidth, cpuHight, -cpuLength - 0.04);
	glEnd();

	glBegin(GL_QUAD_STRIP);
	glVertex3f(0., cpuHight, 0.);
	glVertex3f(0., cpuHight + thickness, 0.);
	glVertex3f(0.5, cpuHight, 0.);
	glVertex3f(0.5, cpuHight+thickness, 0.);
	glVertex3f(0.7, cpuHight, -.04);
	glVertex3f(0.7, cpuHight + thickness, -.04);
	glVertex3f(cpuWidth, cpuHight, -.04);
	glVertex3f(cpuWidth, cpuHight + thickness, -.04);
	glEnd();

	glBegin(GL_QUAD_STRIP);
	glVertex3f(0., cpuHight, -cpuLength - 0.04);
	glVertex3f(0., cpuHight + thickness, -cpuLength - 0.04);
	glVertex3f(cpuWidth, cpuHight, -cpuLength - 0.04);
	glVertex3f(cpuWidth, cpuHight + thickness, -cpuLength - 0.04);
	glEnd();

	glPopMatrix();
}

void cpu_case::draw_sidebar() {
	GLfloat lowerBound = 0.;
	GLfloat thickness = 0.04;
	GLfloat frontSpace = 0.07;

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[CPU_CASE_SIDEBAR]);
	glColor3f(1., 1., 1.);
	glBegin(GL_POLYGON);
	glTexCoord2f(1., 0.);	glVertex3f(0., lowerBound, -frontSpace);
	glTexCoord2f(0., 0.);	glVertex3f(0., lowerBound, -cpuLength * 0.3 - frontSpace);
	glTexCoord2f(0., 1.);	glVertex3f(0., cpuHight - 0.01, -cpuLength * 0.3 - frontSpace);
	glTexCoord2f(1., 1.);	glVertex3f(0., cpuHight - 0.01, -frontSpace);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glBegin(GL_POLYGON);
	glColor3fv(cabinetColor);
	glVertex3f(0., cpuHight - 0.01, -cpuLength * 0.3);
	glVertex3f(thickness, cpuHight - 0.01, -cpuLength * 0.3);
	glVertex3f(0., lowerBound, -cpuLength * 0.3);
	glVertex3f(thickness, lowerBound, -cpuLength * 0.3);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3b(0, 1, 0);
	glVertex3f(0., lowerBound, 0.);
	glVertex3f(0., lowerBound, -frontSpace);
	glVertex3f(0., cpuHight - 0.01, -frontSpace);
	glVertex3f(0., cpuHight - 0.01, 0.);
	glEnd();

	glPopMatrix();
}

void cpu_case::draw_legs() {
	GLfloat padding = 0.2;

	glPushMatrix();
	glColor3f(0., 0., 0.);
	glTranslatef(0.05, -.215, -0.15);
	glScalef(0.1, 0.1, 0.1);
	glBegin(GL_QUAD_STRIP);
		glVertex3f(padding, 0., 0.);
		glVertex3f(0., 1., 0.);
		glVertex3f(1. - padding, 0., 0.);
		glVertex3f(1. , 1., 0.);
		glVertex3f(1. - padding, 0., -1.);
		glVertex3f(1 , 1., -1.);
		glVertex3f(padding, 0., -1.);
		glVertex3f(0., 1., -1.);
		glVertex3f(padding, 0., 0.);
		glVertex3f(0.,1., 0.);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0., 0., 0.);
	glTranslatef(cpuWidth - .1, -.215, -0.1);
	glScalef(0.1, 0.1, 0.1);
	glBegin(GL_QUAD_STRIP);
		glVertex3f(padding, 0., 0.);
		glVertex3f(0., 1., 0.);
		glVertex3f(1. - padding, 0., 0.);
		glVertex3f(1. , 1., 0.);
		glVertex3f(1. - padding, 0., -1.);
		glVertex3f(1 , 1., -1.);
		glVertex3f(padding, 0., -1.);
		glVertex3f(0., 1., -1.);
		glVertex3f(padding, 0., 0.);
		glVertex3f(0.,1., 0.);
	glEnd();
	glPopMatrix();

	glPushMatrix();
		glColor3f(0., 0., 0.);
		glTranslatef(cpuWidth -.1, -.215, -cpuLength + 0.1);
		glScalef(0.1, 0.1, 0.1);
		glBegin(GL_QUAD_STRIP);
			glVertex3f(padding, 0., 0.);
			glVertex3f(0., 1., 0.);
			glVertex3f(1. - padding, 0., 0.);
			glVertex3f(1., 1., 0.);
			glVertex3f(1. - padding, 0., -1.);
			glVertex3f(1, 1., -1.);
			glVertex3f(padding, 0., -1.);
			glVertex3f(0., 1., -1.);
			glVertex3f(padding, 0., 0.);
			glVertex3f(0., 1., 0.);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glColor3f(0., 0., 0.);
		glTranslatef( .05, -.215, -cpuLength+0.1);
		glScalef(0.1, 0.1, 0.1);
		glBegin(GL_QUAD_STRIP);
			glVertex3f(padding, 0., 0.);
			glVertex3f(0., 1., 0.);
			glVertex3f(1. - padding, 0., 0.);
			glVertex3f(1., 1., 0.);
			glVertex3f(1. - padding, 0., -1.);
			glVertex3f(1, 1., -1.);
			glVertex3f(padding, 0., -1.);
			glVertex3f(0., 1., -1.);
			glVertex3f(padding, 0., 0.);
			glVertex3f(0., 1., 0.);
		glEnd();
	glPopMatrix();

}

#endif