#include "Camera.h"
#include "glut.h"

void Camera::updateCamera() {
	glLoadIdentity();
	gluLookAt(camPos->x, camPos->y, camPos->z, camFocus->x, camFocus->y, camFocus->z, 0.0, 0.0, 1.0);
}
