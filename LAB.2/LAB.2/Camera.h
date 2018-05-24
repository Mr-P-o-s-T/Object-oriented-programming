#pragma once
#include "Mesh.h"

class Camera {
public:
	Camera(double x, double y, double z) {
		if (camPos) delete camPos;
		camPos = new Vertex(x, y, z);
		if (camFocus) delete camFocus;
		camFocus = new Vertex();
	}
	~Camera() {
		if (camPos) delete camPos;
		if (camFocus) delete camFocus;
	}

	void updateCamera();
private:
	class Vertex *camPos = nullptr, *camFocus = nullptr;
};
