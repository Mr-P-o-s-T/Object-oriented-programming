#include "Mesh.h"
using namespace std;

size_t Mesh::Polygon::n = 0;

Mesh::Mesh(const char *meshPath) {
	loadMesh(meshPath);
}

void Mesh::loadMesh() {
	ifstream file(path, ios::binary);
	size_t n;
	file.read((char *)&n, sizeof(n));
	vertexes.reserve(n);
	for (size_t i = 0; i < vertexes.capacity(); i++) vertexes.push_back(Vertex::loadVertex(file));
	file.read((char *)&n, sizeof(n));
	polygons.reserve(n);
	polygons.push_back(Polygon::loadPolygon(file));
	for (size_t i = 1; i < polygons.capacity(); i++) polygons.push_back(Polygon::loadPolygon(file));
}
