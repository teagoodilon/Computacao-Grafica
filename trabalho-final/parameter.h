#ifndef PARAM
#define PARAM

#include <math.h>
#include <GL/glut.h>

class point3D {
public:	double x, y, z;
		point3D() {
			x = 0., y = 0., z = 0.;
		}
		point3D(double a, double b, double c) {
			x = a, y = b, z = c;
		}
		void assign(double a, double b, double c) {
			x = a, y = b, z = c;
		}
};

class point2D {

public:double x, y;
	   point2D() {
		   x = 0., y = 0.;
	   }
	   point2D(double a, double b) {
		   x = a, y = b;
	   }
	   void assign(double a, double b) {
		   x = a, y = b;
	   }
};

int width = 1920, hight = 1080;
int page = 0;


// Parâmtros de movimentação
#define UPPER_Y 7.0
#define LOWER_Y	-0.8

float lx = 0.0f, lz = -1.0f;
float zx = 0.0f, zz = 0.0f;
double x = .0f, z = 5.0f, y = 5.0;
bool motion_present = false;
float angle = 0.0f;
int oldTimeSinceStart = 0, deltaTime;
float fraction = 0.3f;
float xmin = -8.5, xmax = 8.5,	// Para restringir a movimentação
zmin = -8.5, zmax = 8.5, bounceVal = 1.;
float motion_gap = 0.0001;

// Conta as texturas
GLuint* textures;
#define NUM_TEXTURE 29

#define WOODEN_FINISH 2
#define MOTHERBOARD_BACK 0
#define MOTHERBOARD_FRONT 1
#define MOTHERBOARD_USB 3
#define STEEL_FINISH 4
#define RAZER_LOGO 5
#define CPU_CASE_SIDEBAR 6
#define CPU_INSIDE_WALL 7
#define MOTHERBOARD_VGA 8
#define FAN_LOGO 9
#define CASE_RIM_RIGHT 10
#define CASE_RIM_LEFT 11
#define CASE_RIM_TOP 12
#define CASE_RIM_BOTTOM 13
#define CASE_BEHIND 14

#define HDD_TOP 15
#define RAMSTICK 16
#define PSU_FRONT 17
#define PSU_TOP 18
#define PSU_LEFT 19
#define CHIPSET 20
#define CHIPSET_BACK 21
#define GPU_FRONT 22
#define GPU_LOWER 23
#define GPU_BACK 24
#define GPU_LEFT 25
#define GPU_SIDE 26
#define WALL 27
#define SPEAKER 36


const char* texPath[] = {			"data/placa_mae_traseira.bmp",
									"data/placa_mae_frente.bmp",
									"data/madeira.bmp",
									"data/placa_mae_usb.bmp",
									"data/aco.bmp",
									"data/logo_razer.bmp",
									"data/gabinete_barra_lateral.bmp",
									"data/parede_dentro.bmp",
									"data/placa_mae_vga.bmp",
									"data/logo_ventoinha.bmp",
									"data/borda_direita.bmp",
									"data/borda_esquerda.bmp",
									"data/borda_topo.bmp",
									"data/borda_baixo.bmp",
									"data/gabinete_tras.bmp",
									"data/hdd.bmp",
									"data/ram.bmp",
									"data/fonte_frente.bmp",
									"data/fonte_cima.bmp",
									"data/fonte_esquerda.bmp" ,
									"data/processador.bmp",
									"data/processador_tras.bmp",
									"data/gpu_frente.bmp",
									"data/gpu_baixo.bmp",
									"data/gpu_esquerda.bmp",
									"data/gpu_tras.bmp",
									"data/gpu_lado.bmp",
									"data/parede_dentro.bmp",
									"data/alto_falante.bmp",
							
};

float deg(float radians) {
	return radians * (180.0 / M_PI);
}

float rad(float degree) {
	return degree * (M_PI / 180);
}

// Remoção de objetos
int objIndex = -1;
bool enterPressed = false;
bool assemble = false;
char choice = '1';
float disXYZ[3] = { 4., 5.,-3.5 }, disLxLyLz[3] = { 1., 0., 0. };
float disapphereLimit = -4.;

#define REMOVE_SIDE_PANEL	0
#define REMOVE_RAM_STICK	2
#define REMOVE_FAN			4
#define REMOVE_PROCESSOR	6
#define REMOVE_PSU			8
#define REMOVE_HDD			10
#define REMOVE_GPU			12
#define REMOVE_MOTHERBOARD	14

point3D objLoc(0., 5., -2.);
point3D viewerLoc(0., 5., 0.);

point3D prevViewerLoc;
point3D prevObjLoc;

#endif PARAM
