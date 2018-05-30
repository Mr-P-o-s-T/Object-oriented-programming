// main file
#define ANIMATION_SPEED 10

#include "Scene.h"
#include "glut.h"
#include <iostream>
using namespace std;

Scene scene("meshes/mesh.mesh", "meshes/mesh.mesh");

void initialization(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(200, 25);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("");
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-3, 3, -3, 3, 0.1, 20);
	gluPerspective(90, 1, 0.1, 20);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);
}

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene.BuildScene();
	glutSwapBuffers();
}

void timerFunc(int value) {
	glutPostRedisplay();
	glutTimerFunc(ANIMATION_SPEED, timerFunc, 0);
}

void keyboardFunc(unsigned char key, int x, int y) {
	scene.keyFunc(key, x, y);
}

void mouseFunc(int button, int state, int x, int y) {
	scene.mouseFunc(button, state, x, y);
}

void mouseMoveFunc(int x, int y) {
	scene.mouseMoveFunc(x, y);
}

int main(int argc, char **argv) {
	char answ;
	do {
		cout << "Want to load scene from file scene.save& (y/n):";
		cin >> answ;
	} while ((answ != 'y') && (answ != 'n'));
	if (answ == 'n') {
		cout << "Set first mesh parameters:\n" << "Position (x, y, z):";
		double x, y, z;
		cin >> x >> y >> z;
		scene.getMesh(true).setPosition(x, y, z);
		cout << "Standart color (r, g, b):";
		cin >> x >> y >> z;
		scene.getMesh(true).setColor(x, y, z);
		cout << "Picked color (r, g, b):";
		cin >> x >> y >> z;
		scene.getMesh(true).setColor(x, y, z);

		cout << "Set second mesh parameters:\n" << "Position (x, y, z):";
		cin >> x >> y >> z;
		scene.getMesh(false).setPosition(x, y, z);
		cout << "Standart color (r, g, b):";
		cin >> x >> y >> z;
		scene.getMesh(false).setColor(x, y, z);
		cout << "Picked color (r, g, b):";
		cin >> x >> y >> z;
		scene.getMesh(false).setColor(x, y, z);
	}
	else scene.Load();

	initialization(argc, argv);

	glutDisplayFunc(renderScene);
	glutKeyboardFunc(keyboardFunc);
	glutMouseFunc(mouseFunc);
	glutMotionFunc(mouseMoveFunc);

	glutTimerFunc(ANIMATION_SPEED, timerFunc, 0);

	glutMainLoop();
	return 0;
}