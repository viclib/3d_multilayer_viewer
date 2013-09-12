#include "layer.h"

#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "vector3d.h"
#include <cmath>
#include <iostream>

#include "globals.h"
#include "now.h"
#include "wavy_grid.h"
#include "guide_grid.h"
#include "draw.h"
#include "commands.h"

void draw(){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluPerspective(60.0f,1.0f,0.01f,650.0f);
	gluLookAt(
		0.0, cam_radius, cam_radius,
		0.0, 0.0, 0.0,
		0.0, 0.0, 1.0);
	glRotatef( rotate_x, 1.0, 0.0, 0.0 );
	glRotatef( rotate_y, 0.0, 0.0, 1.0 );

	draw_layers();

	if (show_grid)
		draw_grid(-0.5,-0.5,0.1,0.1,11,11,&guide_z,&guide_col);

	if (show_axis)
		draw_axis();
	
	if (show_wave)
		draw_grid(-1,-1,0.05,0.05,41,41,&wavy_z,&wavy_col);

	glFlush();
	glutSwapBuffers();
}


void tick(int value) {
    glutPostRedisplay();
    glutTimerFunc(0, tick, 0);
}

int main(int argc, char* argv[]){
	layers.push_back(Layer<double>("test1.dat", 1.0, 0.7, 0.7));
	layers.push_back(Layer<double>("test2.dat", 0.7, 1.0, 0.7));
	layers.push_back(Layer<double>("test3.dat", 0.7, 0.7, 1.0));

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800,600);
	glutCreateWindow("graph");
	glEnable(GL_DEPTH_TEST | GL_LINE_SMOOTH);
	glutDisplayFunc(draw);
	glutKeyboardFunc(commands);
	glutTimerFunc(0,tick,0);
	glutMainLoop();
	return 0;
}

