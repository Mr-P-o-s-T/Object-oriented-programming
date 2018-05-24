#include "Mesh.h"
#include "glut.h"
using namespace std;

size_t Mesh::Polygon::n = 0;

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

void Mesh::drawMesh() {
	if (center) {
		glPushMatrix();

		glTranslated(center->x, center->y, center->z);
		glColor3f(color.r, color.g, color.b);

		glRotated(phi, 1.0, 0.0, 0.0);
		glRotated(xi, 0.0, 1.0, 0.0);
		glRotated(psi, 0.0, 0.0, 1.0);

		for (auto polgs : polygons) {
			glBegin(GL_POLYGON);
			for (auto ind : polgs.indexes) {
				glVertex3d(vertexes[ind].x * scale, vertexes[ind].y * scale, vertexes[ind].z * scale);
			}
			glEnd();
		}

		glPopMatrix();
	}
}

vector<Vertex> Mesh::getVertexesProjectionOXY() {
	vector<Vertex> res;
	for (auto i: vertexes) {
		res.push_back(Vertex(i.x, i.y, 0.0));
	}
	return res;
}

vector<Vertex> Mesh::getVertexesProjectionOXZ() {
	vector<Vertex> res;
	for (auto i : vertexes) {
		res.push_back(Vertex(i.x, 0.0, i.z));
	}
	return res;
}

vector<Vertex> Mesh::getVertexesProjectionOYZ() {
	vector<Vertex> res;
	for (auto i : vertexes) {
		res.push_back(Vertex(0.0, i.y, i.z));
	}
	return res;
}
