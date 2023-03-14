/* camera.cpp
*
*  abril, 2002 - Luciana Nedel
*  adaptado por Carla Freitas
*  adaptado por Bruno Schneider em marco de 2012
*  modificado por Bruno Schneider em outubro de 2016
*
*  Exemplo para manipulacao de camera em OpenGL
*/

#include <cmath>
#include <iostream>
#include <GL/glut.h>

using namespace std;

bool perspectiva = true;

// estrutura que representa uma camera
typedef struct {
        GLdouble atx;
        GLdouble aty;
        GLdouble atz;
        GLdouble tox;
        GLdouble toy;
        GLdouble toz;
} Observador;

Observador camera;

// Parametros de projecao
GLfloat fAspect;
GLfloat angle = 100;    // angulo de abertura para proj. perspectiva

// limites do volume ortografico (projecao paralela)
GLdouble minX=-100.00;
GLdouble maxX=100.00;
GLdouble minY=-100.00;
GLdouble maxY=100.00;
GLint incremento=0;

// planos near e far para recorte em profundidade
GLdouble near_plane= 2.0;
GLdouble far_plane=240.0;

void ImprimirCamera() {
    cout << "eye: (" << camera.atx << "," << camera.aty << "," << camera.atz
         << ") foco: (" << camera.tox << "," << camera.toy << ","
         << camera.toz << ")" << endl;
}

/* Funcao usada para especificar o volume de visualizacao
*  no caso de projecao perspectiva.
*/
void ComputarProjecaoPerspectiva() {
    // Especifica manipulacao da matriz de projecao
    glMatrixMode(GL_PROJECTION);
    // Inicializa matriz com a identidade
    glLoadIdentity();

    // Especifica a projecao perspectiva
    gluPerspective(angle,fAspect,near_plane,far_plane);

    // Especifica sistema de coordenadas do modelo
    glMatrixMode(GL_MODELVIEW);
    // Inicializa matriz modelview com a identidade
    glLoadIdentity();
    // Especifica posicao do observador e do alvo
    gluLookAt (camera.atx,camera.aty,camera.atz, camera.tox,camera.toy,camera.toz, 0,1,0);
}

/* Funcao usada para especificar o volume de visualizacao
*  no caso de projecao paralela.
*/
void ComputarProjecaoParalela()
{
     // Especifica sistema de coordenadas do modelo
    glMatrixMode(GL_MODELVIEW);
    // Inicializa matriz modelview com a identidade
    glLoadIdentity();
    // Especifica posicao do observador e do alvo
    gluLookAt (camera.atx,camera.aty,camera.atz, camera.tox,camera.toy,camera.toz, 0,1,0);

    // Especifica manipulacao da matriz de projecao
    glMatrixMode(GL_PROJECTION);
    // Inicializa matriz com a identidade
    glLoadIdentity();

    // Especifica a projecao ortografica
    glOrtho(minX-incremento,
            maxX+incremento,
            minY-incremento,
            maxY+incremento,
            near_plane,far_plane);

    glMatrixMode(GL_MODELVIEW);
}

void ComputarProjecao() {
    if (perspectiva) {                 // chamada para atualizar o volume de visualizacao
        ComputarProjecaoPerspectiva(); // no caso de perspectiva
    }
    else {                          // chamada para atualizar o volume de visualizacao
        ComputarProjecaoParalela(); // no caso de proje��o ortogr�fica
    }
}

void InicializarCamera() {
    camera.atx=0.0;
    camera.aty=15.0;
    camera.atz=-100.0;

    camera.tox=0.0;   // olhando para o ponto central da pir�mide
    camera.toy=15.0;
    camera.toz=0.0;
    ComputarProjecao();
}

// Inicializa��o
void SetupRC(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    // Limpa a janela e habilita o teste para eliminar faces posteriores
    glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    // habilita o uso de uma cor por face
    glShadeModel (GL_FLAT);
    InicializarCamera();
}

// Chamada pela GLUT quando a janela e' redimensionada.
void ChangeSize(GLsizei w, GLsizei h) {
    // Para prevenir uma divis�o por zero
    if ( h == 0 )
        h = 1;

    // Especifica o tamanho da viewport
    glViewport(0, 0, w, h);

    // Calcula a corre��o de aspecto
    fAspect = (GLfloat)w/(GLfloat)h;

    ComputarProjecao();
}

// Minha fun��o de desenho
void RenderScene() {
    // Limpa a janela
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

/* Minha Callback para gerenciar eventos do mouse
 * Devolve o bot�o pressionado, o estado do bot�o e
 * posi��o do cursor, relativa � janela.
*/
// A especifica��o da GLUT traz os demais detalhes desse tratamento

void HandleMouse(int button, int state, int x, int y) {
    // o bot�o esquerdo diminui o angulo (perspectiva)
    // ou a largura do volume ortogr�fico
    if (button == GLUT_LEFT_BUTTON)
        if (state == GLUT_DOWN) {
            // Zoom-in
            if (perspectiva) {
                if (angle >= 10)
                     angle -= 5;
            }
            else {
                incremento-=10; // veja o que acontece se fica negativo!!
            }
        }
    // o bot�o direito aumenta o angulo (perspectiva)
    // ou a largura do volume ortogr�fico
    if (button == GLUT_RIGHT_BUTTON)
        if (state == GLUT_DOWN) {
            // Zoom out
            if (perspectiva) {
                if (angle <= 130)
                    angle += 5;
            }
            else {
                incremento+=10;
            }
        }
    if (perspectiva)
        ComputarProjecaoPerspectiva();
    else
        ComputarProjecaoParalela();
    glutPostRedisplay();
}

// Girar a camera em torno do seu eixo vertical.
// Os comandos comentados servem para dar uma ideia do que fazer.
void GirarCamera(GLdouble radianos) {
//    clTransformacao trans;
//    clPonto posObservador(camera.atx,camera.aty,camera.atz,1);
//    clPonto foco(camera.tox,camera.toy,camera.toz,1);
//    clPonto novoFoco;

//    trans.CarregarRotacao(posObservador, clPonto(0,1,0,0), radianos);
//    novoFoco = trans * foco;
//    camera.tox = novoFoco.X();
//    camera.toy = novoFoco.Y();
//    camera.toz = novoFoco.Z();
    ComputarProjecao();
}

void TransladarCamera(GLdouble distancia) {
    GLdouble direcao[3];
    GLdouble norma;

    direcao[0] = camera.tox - camera.atx;
    direcao[1] = camera.toy - camera.aty;
    direcao[2] = camera.toz - camera.atz;
    norma = sqrt(direcao[0]*direcao[0]+direcao[1]*direcao[1]+direcao[2]*direcao[2]);
    direcao[0] /= norma;
    direcao[1] /= norma;
    direcao[2] /= norma;
    camera.atx += direcao[0]*distancia;
    camera.aty += direcao[1]*distancia;
    camera.atz += direcao[2]*distancia;
    camera.tox += direcao[0]*distancia;
    camera.toy += direcao[1]*distancia;
    camera.toz += direcao[2]*distancia;
    ComputarProjecao();
}

void CallbackTeclado(unsigned char key, int x, int y) {
    switch (key)
    {
        case 'a':
            GirarCamera(0.05);
            break;
        case 'd':
            GirarCamera(-0.05);
            break;
        case 'w':
            TransladarCamera(0.3);
            break;
        case 's':
            TransladarCamera(-0.3);
            break;
        case 'i':
            InicializarCamera();
            break;
        case 'p': // trocar tipo de projecao
            perspectiva = !perspectiva;
            if (perspectiva)
                cout << "Usando projecao perspectiva.\n";
            else
                cout << "Usando projecao paralela.\n";
            ComputarProjecao();
            break;
        case 27: // tecla ESCAPE
            exit(0);
        default:
            // Nao redesenhar a tela
            return;
    }
    glutPostRedisplay();
}

int main(int argc, char* argv[]) {
    // Procedimento de inicializacao da GLUT
    glutInit(&argc, argv);
    cout << "Coloque a mao esquerda nas teclas asdw.\n";
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400,350);
    glutCreateWindow("Controle da Camera");
    glutKeyboardFunc(CallbackTeclado);
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutMouseFunc(HandleMouse);
    SetupRC();
    cout << "Comandos do teclado:\n"
         << "a: girar para esquerda\n"
         << "d: girar para direita\n"
         << "w: andar para frente\n"
         << "s: andar para tras\n"
         << "i: voltar para posicao inicial\n"
         << "p: trocar o tipo de projecao (paralela/perspectiva)\n"
         << "ESC: terminar a execucao\n";
    glutMainLoop();
    return 0;
}

