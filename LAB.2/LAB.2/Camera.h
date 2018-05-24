#pragma once
#include "Mesh.h"

class Camera {
public:
	Camera();
	Camera(double x, double y, double z);
	~Camera();
private:
	double eX, eY, eZ;
};
