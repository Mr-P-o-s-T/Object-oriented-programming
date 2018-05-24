#pragma once
#include "Vertex.h"
#include <vector>

class Mesh {
public:
	Mesh() = default;

	Mesh(const char *meshPath) {
		loadMesh(meshPath);
	}

	~Mesh() {
		if (center) delete center;
	}

	void setPosition(double x, double y, double z) {
		if (center) delete center;
		center = new Vertex(x, y, z);
	}

	void changePosition(double dx, double dy, double dz) {
		center->changeCoordinates(dx, dy, dz);
	}

	void setAngles(double phi = 0.0, double xi = 0.0, double psi = 0.0) {
		this->phi = phi; this->xi = xi; this->psi = psi;
	}

	void changeAngles(double dphi, double dxi, double dpsi) {
		this->phi += dphi; this->xi += dxi; this->psi += dpsi;
	}

	void setScale(double scale = 1.0) {
		this->scale = scale;
	}

	double getScale() {
		return scale;
	}

	void loadMesh();
	void loadMesh(const char *meshPath) {
		path = meshPath;
		loadMesh();
	}

	void drawMesh();

	std::vector<Vertex> getVertexesProjectionOXY();
	std::vector <Vertex> getVertexesProjectionOXZ();
	std::vector <Vertex> getVertexesProjectionOYZ();
private:
	class Polygon {
	public:
		static uint64_t n;
		std::vector<uint64_t> indexes;
	private:
		Polygon() {
			indexes.reserve(n);
		}

		Polygon(uint64_t n) {
			this->n = n;
			indexes.reserve(n);
		}

	public:
		~Polygon() = default;

		static Polygon loadPolygon(std::ifstream &file) {
			if (n) {
				uint64_t n;
				file.read((char *)&n, sizeof(n));
				Polygon polygon(n);
				file.read((char *) polygon.indexes.data(), polygon.indexes.capacity());
				return polygon;
			} 
			else {
				Polygon polygon;
				file.read((char *)polygon.indexes.data(), polygon.indexes.capacity());
				return polygon;
			}
		}
	};

	class Color	{
	public:
		float r = 0.0f, g = 0.0f, b = 0.0f;

		Color() = default;
		Color(float r, float g, float b) {
			this->r = r; this->g = g; this->b = b;
		}
		~Color() = default;
	} color;
	
	const char *path = nullptr;
	std::vector<Vertex> vertexes;
	std::vector<Polygon> polygons;
	Vertex *center = nullptr;
	double phi = 0.0, xi = 0.0, psi = 0.0;
	double scale = 1;
};
