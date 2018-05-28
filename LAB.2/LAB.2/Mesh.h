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
		switch (axis) {
		case None: center->changeCoordinates(dx, dy, dz);						
			break;
		case x: center->changeCoordinates(dx, 0.0, 0.0);
			break;
		case y: center->changeCoordinates(0.0, dy, 0.0);
			break;
		case z: center->changeCoordinates(0.0, 0.0, dz);
			break;
		}
	}

	void setAngles(double phi = 0.0, double xi = 0.0, double psi = 0.0) {
		this->phi = phi; this->xi = xi; this->psi = psi;
	}

	void changeAngles(double dphi, double dxi, double dpsi) {
		switch (axis) {
		case None: this->phi += dphi; 
			this->xi += dxi; 
			this->psi += dpsi;
			break;
		case x: this->phi += dphi;
			break;
		case y: this->xi += dxi;
			break;
		case z: this->psi += dpsi;
			break;
		}
	}

	void setScale(double scale = 1.0) {
		this->scale = scale;
	}

	double getScale() {
		return scale;
	}

	void setColor(float r, float g, float b) {
		static bool pick = false;
		if (pick) colorPick = Color(r, g, b);
		else colorUnpick = Color(r, g, b);
		pick = !pick;
	}

	void loadMesh();
	void loadMesh(const char *meshPath) {
		path = meshPath;
		loadMesh();
	}

	void drawMesh(bool isPick);

	std::vector <Vertex> getVertexesProjectionOXY();
	std::vector <Vertex> getVertexesProjectionOXZ();
	std::vector <Vertex> getVertexesProjectionOYZ();

	class Color {
	public:
		float r = 0.0f, g = 0.0f, b = 0.0f;

		Color() = default;
		Color(float r, float g, float b) {
			this->r = r; this->g = g; this->b = b;
		}
		~Color() = default;
	};

	class Vector : public Vertex {
	public:
		Vector(double x, double y, double z) : Vertex(x, y, z) {}
		~Vector() = default;

		double scalarComposition(const Vector &b) {
			return x * b.x + y * b.y + z * b.z;
		}

		Vector vectorComposition(Vector &b) {
			return Vector(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
		}
		
		double length() {
			return sqrt(scalarComposition(*this));
		}

		Vector normalise() {
			double len = length();
			if (len) return Vector(x / len, y / len, z / len);
			else return Vector(0.0, 0.0, 0.0);
		}
	};
private:
	class Polygon {
	public:
		static size_t n;
		std::vector<size_t> indexes;
	private:
		Polygon() {
			indexes.reserve(n);
		}

		Polygon(size_t n) {
			this->n = n;
			indexes.reserve(n);
		}

	public:
		~Polygon() = default;

		static Polygon loadPolygon(std::ifstream &file) {
			if (!n) {
				size_t n;
				file.read((char *)&n, sizeof(n));
				Polygon polygon(n);
				for (size_t i = 0; i < polygon.indexes.capacity(); i++) {
					size_t ind;
					file.read((char *)&ind, sizeof(ind));
					polygon.indexes.push_back(ind);
				}
				return polygon;
			} 
			else {
				Polygon polygon;
				for (size_t i = 0; i < polygon.indexes.capacity(); i++) {
					size_t ind;
					file.read((char *)&ind, sizeof(ind));
					polygon.indexes.push_back(ind);
				}
				return polygon;
			}
		}
	};

	enum AxisChosen {
		None,
		x, y, z
	} axis = None;

	Color colorPick, colorUnpick;
	
	const char *path = nullptr;
	std::vector<Vertex> vertexes;
	std::vector<Polygon> polygons;
	Vertex *center = nullptr;
	double phi = 0.0, xi = 0.0, psi = 0.0;
	double scale = 1;

	friend class Scene;
};
