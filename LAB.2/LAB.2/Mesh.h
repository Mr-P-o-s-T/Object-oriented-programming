#pragma once
#include "Vertex.h"
#include <vector>

class Mesh {
public:
	Mesh() = default;

	Mesh(const char *meshPath) {
		createMesh(meshPath);
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

	void changeAngles(double dphi, double dxi, double dpsi) {
		switch (axis) {
		case None: rotateOXY(dphi); 
			rotateOXZ(dxi); 
			rotateOYZ(dpsi);
			break;
		case x: rotateOYZ(dpsi);
			break;
		case y: rotateOXZ(dxi);
			break;
		case z: rotateOXY(dphi);
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

	void createMesh();
	void createMesh(const char *meshPath) {
		path = meshPath;
		createMesh();
	}

	void saveMesh(std::ofstream &file);
	void loadMesh(std::ifstream &file);

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
	double scale = 1;

	void rotateOXY(double dphi) {
		for (size_t i = 0; i < vertexes.size(); i++) {
			Vertex tmp(vertexes[i].x * cos(dphi / 90) - vertexes[i].y * sin(dphi / 90), vertexes[i].x * sin(dphi / 90) + vertexes[i].y * cos(dphi / 90), vertexes[i].z);
			vertexes[i].x = tmp.x; vertexes[i].y = tmp.y;
		}
	}

	void rotateOXZ(double dxi) {
		for (size_t i = 0; i < vertexes.size(); i++) {
			Vertex tmp(vertexes[i].x * cos(dxi / 90) - vertexes[i].z * sin(dxi / 90), vertexes[i].y, vertexes[i].x * sin(dxi / 90) + vertexes[i].z * cos(dxi / 90));
			vertexes[i].x = tmp.x; vertexes[i].z = tmp.z;
		}
	}

	void rotateOYZ(double dpsi) {
		for (size_t i = 0; i < vertexes.size(); i++) {
			Vertex tmp(vertexes[i].x, vertexes[i].y * cos(dpsi / 90) - vertexes[i].z * sin(dpsi / 90), vertexes[i].y * sin(dpsi / 90) + vertexes[i].z * cos(dpsi / 90));
			vertexes[i].y = tmp.y; vertexes[i].z = tmp.z;
		}
	}

	friend class Scene;
};
