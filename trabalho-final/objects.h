#ifndef OBJECTS 
#define OBJECTS 

#include <GL/glut.h>
#include <GL/freeglut.h> 
#include "bmpLoader.h"

#include "cpu_fan.h"
#include "cpu_motherboard.h"
#include "cpu_case.h"
#include "cpu_ram.h"
#include "cpu_chipset.h"
#include "cpu_gpu.h"
#include "cpu_psu.h"
#include "cpu_harddisk.h"

cpu_fan fan_;
cpu_motherboard motherboard_;
cpu_case case_;
cpu_ramstick ram_;
cpu_chipset chipset_;
cpu_gpu gpu_;
cpu_psu psu_;
cpu_harddisk harddisk_;

void drawCPU(bool onOff) {
	fan_.render(onOff); // Desenha a ventoinha
	motherboard_.render();
	ram_.render(8., 4.845, -4.296);
	ram_.render(8., 4.845, -4.268);
	ram_.render(8., 4.845, -4.235);
	chipset_.render();
	gpu_.render();
	psu_.render();
	harddisk_.render();
	case_.render();
}

#endif OBJECTS