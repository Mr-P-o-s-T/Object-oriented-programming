#pragma once

class Mesh {
public:
	Mesh(double x, double y, double z);
	~Mesh();
private:
	double x, y, z;
	double size;
};

