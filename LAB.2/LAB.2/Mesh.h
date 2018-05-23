#pragma once
#include <vector>
#include <fstream>

class Mesh {
public:
	Mesh() = default;
	Mesh(const char *meshPath);
	~Mesh() = default;

	void loadMesh();
	void loadMesh(const char *meshPath) {
		path = meshPath;
		loadMesh();
	}


private:
	class Vertex {
	public:
		double x, y, z;

	private:
		Vertex() = default;

		Vertex(double x, double y, double z) {
			this->x = x; this->y = y; this->z = z;
		}

	public:
		~Vertex() = default;

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
	
	const char *path = nullptr;
	std::vector<Vertex> vertexes;
	std::vector<Polygon> polygons;
	Vertex *center = nullptr;
	double phi, xi, psi;
	double size;
};
