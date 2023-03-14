#include <GL/glut.h>
#include <iostream>

bool vcama = false, vcriados = false, vguardaRoupa = false,
  vmesa = false, vcadeira = false;

void cama(){
  glBegin(GL_LINE_LOOP);            //cama
    glVertex2f(-0.3f,0.75f);
    glVertex2f(0.3f,0.75f);
    glVertex2f(0.3f,0.1f);
    glVertex2f(-0.3f,0.1f);    
  glEnd();

  glBegin(GL_LINE_LOOP);            //travesseiro esq
    glVertex2f(-0.25f,0.70f);
    glVertex2f(-0.02f,0.70f);
    glVertex2f(-0.02f,0.60f);
    glVertex2f(-0.25f,0.60f);    
  glEnd();

  glBegin(GL_LINE_LOOP);            //travesseiro dir
    glVertex2f(0.25f,0.70f);
    glVertex2f(0.02f,0.70f);
    glVertex2f(0.02f,0.60f);
    glVertex2f(0.25f,0.60f);    
  glEnd();

  glBegin(GL_LINE_STRIP);           //cobertor
    glVertex2f(-0.3f,0.60f);
    glVertex2f(0.3f,0.60f);
  glEnd();
}

void criados(){
  glBegin(GL_LINE_LOOP);            //criado esq
    glVertex2f(-0.33f,0.75f);
    glVertex2f(-0.5f,0.75f);
    glVertex2f(-0.5f,0.60f);
    glVertex2f(-0.33f,0.60f);     
  glEnd();

  glBegin(GL_LINE_LOOP);            //criado dir
    glVertex2f(0.33f,0.75f);
    glVertex2f(0.5f,0.75f);
    glVertex2f(0.5f,0.60f);
    glVertex2f(0.33f,0.60f);     
  glEnd();
}

void mesa(){
  glBegin(GL_LINE_LOOP);            //mesa
    glVertex2f(0.75f,-0.75f);
    glVertex2f(0.3f,-0.75f);
    glVertex2f(0.3f,-0.60f);
    glVertex2f(0.60f,-0.60f);
    glVertex2f(0.60f,-0.35f);
    glVertex2f(0.75f,-0.35f);    
  glEnd();
}

void cadeira(){
  glBegin(GL_LINE_LOOP);            //cadeira
    glVertex2f(0.45f,-0.55f);
    glVertex2f(0.45f, -0.45f);
    glVertex2f(0.55f,-0.45f);
    glVertex2f(0.55f,-0.55f);    
  glEnd();

  glBegin(GL_LINE_LOOP);            //cadeira cima
    glVertex2f(0.45f,-0.40f);
    glVertex2f(0.45f, -0.43f);
    glVertex2f(0.55f,-0.43f);
    glVertex2f(0.55f,-0.40f);    
  glEnd();

  glBegin(GL_LINES);                //cadeira ligacao
    glVertex2f(0.55f,-0.43f);
    glVertex2f(0.55f,-0.45f);  
    glVertex2f(0.45f,-0.43f);
    glVertex2f(0.45f,-0.45f); 
  glEnd();
}

void guardaRoupa(){
  glBegin(GL_LINE_LOOP);            //guarda roupa
    glVertex2f(-0.75f,-0.75f);
    glVertex2f(-0.45f,-0.75f);
    glVertex2f(-0.45f,-0.15f);
    glVertex2f(-0.75f,-0.15f); 
  glEnd();

  glBegin(GL_LINE_STRIP);            //guarda roupa 
    glVertex2f(-0.47f,-0.75f);
    glVertex2f(-0.47f,-0.15f);
  glEnd();
}

void menu(){
  std::cout << "Bem-vindo ao meu quarto" << std::endl
  << "Digite a tecla desejada para girar os itens" << std::endl
  << "(1) - Cama" << std::endl
  << "(2) - Criados" << std::endl
  << "(3) - Guarda-roupa" << std::endl
  << "(4) - Mesa" << std::endl
  << "(5) - Cadeira" << std::endl
  << "(6) - Resetar" << std::endl;
}


void RenderScene(){
  // Limpa a janela com a cor especificada como cor de fundo
  glClear(GL_COLOR_BUFFER_BIT);
  // forem chamadas deste ponto em diante devem ter a cor vermelha
  glColor3f(1.0f, 0.0f, 0.0f);

  glBegin(GL_LINE_LOOP);              //quadrado base
    glVertex2f(0.8f,-0.8f);
    glVertex2f(0.8f,0.8f);
    glVertex2f(-0.8f,0.8f);
    glVertex2f(-0.8f,-0.8f);
  glEnd();

  glBegin(GL_LINE_STRIP);            //porta
    glVertex2f(-0.2f,-0.8f);
    glVertex2f(-0.2f,-0.83f);
    glVertex2f(0.2f,-0.83f);
    glVertex2f(0.2f,-0.8f);    
  glEnd();

  glBegin(GL_LINE_STRIP);            //janela
    glVertex2f(-0.4f,0.8f);
    glVertex2f(-0.4f,0.83f);
    glVertex2f(0.4f,0.83f);
    glVertex2f(0.4f,0.8f);    
  glEnd();

  glPushMatrix();
  if(vcama){
    glTranslatef(0.30f, -0.15f, 0.f);
    glRotatef(-90.f, 0.f, 0.f, 1.f);
    glTranslatef(-0.35f, -0.3f, -0.f);
  }
  cama();
  glPopMatrix();

  glPushMatrix();
  if(vcriados){
    glTranslatef(0.30f, -0.15f, 0.f);
    glRotatef(-90.f, 0.f, 0.f, 1.f);
    glTranslatef(-0.35f, -0.3f, -0.f);
  }       
  criados();
  glPopMatrix();

  glPushMatrix();
  if(vguardaRoupa){
    glTranslatef(-0.90f, -0.0f, 0.0f);
    glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
  }
  guardaRoupa();
  glPopMatrix();
  
  glPushMatrix();
  if(vmesa){
    glTranslatef(0.50f, 0.50f, 0.0f);
    glRotatef(-90.f, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.50f, 0.50f, 0.0f); 
  }
  mesa();
  glPopMatrix();
  
  glPushMatrix();
  if(vcadeira){
    glTranslatef(0.50f, 0.50f, 0.0f);
    glRotatef(-90.f, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.50f, 0.50f, -0.0f); 
  }
  cadeira();
  glPopMatrix();
  
  glFlush(); 
}

void SetupRC(){
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);  // cor de fundo da janela
}

void KeyboardFunc ( unsigned char key, int x, int y ){
  switch(key){
    case '1':
      vcama = !vcama;
    break;

    case '2':
      vcriados = !vcriados;
    break;

    case '3':
      vguardaRoupa = !vguardaRoupa;
    break;

    case '4':
      vmesa = !vmesa;
    break;

    case '5':
      vcadeira = !vcadeira;
    break;

    case '6':
      vcama = false, vcriados = false,
      vguardaRoupa = false,
      vmesa = false, vcadeira = false;
    break;
  }
  RenderScene();
}

int main(int argc, char* argv[]){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize (500, 500); 
  glutCreateWindow("Quarto Mobiliado");
  menu();
  glutDisplayFunc(RenderScene);
  glutKeyboardFunc(KeyboardFunc);
  SetupRC();
  glutMainLoop();
  return 0;
}
