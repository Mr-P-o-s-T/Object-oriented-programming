#pragma once
#include <fstream>

class Vertex {
public:
	double x, y, z;

	Vertex(double x = 0.0, double y = 0.0, double z = 0.0) {
		this->x = x; this->y = y; this->z = z;
	}

	~Vertex() = default;

	void changeCoordinates(double dx, double dy, double dz) {
		x += dx; y += dy; z += dz;
	}

	static Vertex loadVertex(std::ifstream &file) {
		Vertex res;
		file.read((char *)&res, sizeof(res));
		return res;
	}

	void saveVertex(std::ofstream &file) {
		file.write((char *)this, sizeof(this));
	}
};
