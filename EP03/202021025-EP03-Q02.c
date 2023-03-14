/*
 * Copyright (c) 1993-1997, Silicon Graphics, Inc.
 * ALL RIGHTS RESERVED 
 * Permission to use, copy, modify, and distribute this software for 
 * any purpose and without fee is hereby granted, provided that the above
 * copyright notice appear in all copies and that both the copyright notice
 * and this permission notice appear in supporting documentation, and that 
 * the name of Silicon Graphics, Inc. not be used in advertising
 * or publicity pertaining to distribution of the software without specific,
 * written prior permission. 
 *
 * THE MATERIAL EMBODIED ON THIS SOFTWARE IS PROVIDED TO YOU "AS-IS"
 * AND WITHOUT WARRANTY OF ANY KIND, EXPRESS, IMPLIED OR OTHERWISE,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY OR
 * FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL SILICON
 * GRAPHICS, INC.  BE LIABLE TO YOU OR ANYONE ELSE FOR ANY DIRECT,
 * SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY
 * KIND, OR ANY DAMAGES WHATSOEVER, INCLUDING WITHOUT LIMITATION,
 * LOSS OF PROFIT, LOSS OF USE, SAVINGS OR REVENUE, OR THE CLAIMS OF
 * THIRD PARTIES, WHETHER OR NOT SILICON GRAPHICS, INC.  HAS BEEN
 * ADVISED OF THE POSSIBILITY OF SUCH LOSS, HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE
 * POSSESSION, USE OR PERFORMANCE OF THIS SOFTWARE.
 * 
 * US Government Users Restricted Rights 
 * Use, duplication, or disclosure by the Government is subject to
 * restrictions set forth in FAR 52.227.19(c)(2) or subparagraph
 * (c)(1)(ii) of the Rights in Technical Data and Computer Software
 * clause at DFARS 252.227-7013 and/or in similar or successor
 * clauses in the FAR or the DOD or NASA FAR Supplement.
 * Unpublished-- rights reserved under the copyright laws of the
 * United States.  Contractor/manufacturer is Silicon Graphics,
 * Inc., 2011 N.  Shoreline Blvd., Mountain View, CA 94039-7311.
 *
 * OpenGL(R) is a registered trademark of Silicon Graphics, Inc.
 */

/*
 * material.c
 * This program demonstrates the use of the GL lighting model.
 * Several objects are drawn using different material characteristics.
 * A single light source illuminates the objects.
 */
#include <stdlib.h>
#include <GL/glut.h>

bool trocaLuz1 = false, trocaLuz2 = false;

/*  Initialize z-buffer, projection matrix, light source, 
 *  and lighting model.  Do not specify a material property here.
 */
void init(void){
  GLfloat spec[] = {0.8, 0.5, 0.5, 1.0};
  GLfloat shin[] = {50.0};
  GLfloat pos[] = {1.0, 0.9, 1.0, 0.0};
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_SMOOTH);
  if(trocaLuz1){
    glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
  }
  if(trocaLuz2){
    glMaterialfv(GL_FRONT, GL_SHININESS, shin);
  }
  if( trocaLuz1 || trocaLuz2){
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
  } else {
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
  }
  glLightfv(GL_LIGHT0, GL_POSITION, pos);

  glEnable(GL_DEPTH_TEST);  
  glEnable(GL_COLOR_MATERIAL);
}

static void draws(void){
  glPushMatrix ();
    glTranslatef (-0.80, 0.35, 0.0); 
    glColor4f(1.0, 1.0, 0.0, 1.0);
    glRotatef (100.0, 1.0, 0.0, 0.0);
    glScalef(2.0, 2.0, 2.0);
    glutSolidTorus (0.275, 0.85, 16, 16);
  glPopMatrix ();

  glPushMatrix ();
    glTranslatef (0.75, 0.60, 0.0); 
    glColor4f(1.0, 0.0, 1.0, 1.0);
    glRotatef (30.0, 1.0, 0.0, 0.0);
    glScalef(2.0, 2.0, 2.0);
    glutSolidTorus (0.275, 0.85, 16, 16);
  glPopMatrix ();
}

void display(void){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  draws();
  glFlush();
}

void reshape(int w, int h){
   glViewport(0, 0, w, h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (w <= (h * 2))
      glOrtho (-6.0, 6.0, -3.0*((GLfloat)h*2)/(GLfloat)w, 
         3.0*((GLfloat)h*2)/(GLfloat)w, -10.0, 10.0);
   else
      glOrtho (-6.0*(GLfloat)w/((GLfloat)h*2), 
         6.0*(GLfloat)w/((GLfloat)h*2), -3.0, 3.0, -10.0, 10.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         exit(0);
         break;
      case 'p':
        trocaLuz1 = !trocaLuz1; 
        break;
      case 'o':
        trocaLuz2 = !trocaLuz2; 
        break;
   }
   init();
   display();
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (600, 450);
   glutCreateWindow(argv[0]);
   init();
   glutReshapeFunc(reshape);
   glutDisplayFunc(display);
   glutKeyboardFunc (keyboard);
   glutMainLoop();
   return 0; 
}

