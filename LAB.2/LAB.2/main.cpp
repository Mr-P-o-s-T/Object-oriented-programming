// main file
#include "Scene.h"
#include "glut.h"

Scene scene("meshes/mesh.mesh", "meshes/mesh.mesh");

void initialization(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(200, 25);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("");
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, 1, 0.1, 20);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.3, 0.3, 0.3, 1);
	glEnable(GL_DEPTH_TEST);
}

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene.BuildScene();
	glutSwapBuffers();
}

void timerFunc(int value) {
	glutPostRedisplay();
	glutTimerFunc(500, timerFunc, 0);
}

void keyboardFunc(unsigned char key, int x, int y) {
	scene.keyFunc(key, x, y);
}

int main(int argc, char **argv) {

	scene.meshes[0].first.setPosition(1, 1, 1);
	scene.meshes[0].first.setColor(1, 0, 0);
	scene.meshes[1].first.setPosition(-1, -1, -1);
	scene.meshes[1].first.setColor(0, 0, 1);
	scene.cam = new Camera(-5, 5, 5);
	initialization(argc, argv);

	glutDisplayFunc(renderScene);
	glutKeyboardFunc(keyboardFunc);

	glutTimerFunc(500, timerFunc, 0);

	glutMainLoop();
	return 0;
}