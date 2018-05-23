#pragma once
#include <vector>
#include <fstream>

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

	void setAngles(double phi, double xi, double psi) {
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
private:
	class Vertex {
	public:
		double x, y, z;

	private:
		Vertex() = default;

	public:
		Vertex(double x, double y, double z) {
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
			if (n) {
				size_t n;
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

		~Color() = default;
	} color;
	
	const char *path = nullptr;
	std::vector<Vertex> vertexes;
	std::vector<Polygon> polygons;
	Vertex *center = nullptr;
	double phi, xi, psi;
	double scale = 1;
};
