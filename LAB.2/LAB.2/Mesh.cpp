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
	Polygon::n = 0;
	file.close();
}

void Mesh::drawMesh(bool isPick) {
	if (center) {
		glPushMatrix();
		glTranslated(center->x, center->y, center->z);

		switch (axis) {
		case x: 
			glBegin(GL_LINES);
			glColor3f(1.0, 0.0, 0.0);
			glVertex3d(-10.0, 0.0, 0.0);
			glVertex3d(10.0, 0.0, 0.0);
			glEnd();
			break;
		case y: 
			glBegin(GL_LINES);
			glColor3f(0.0, 1.0, 0.0);
			glVertex3d(0.0, -10.0, 0.0);
			glVertex3d(0.0, 10.0, 0.0);
			glEnd();
			break;
		case z:	
			glBegin(GL_LINES);
			glColor3f(0.0, 0.0, 1.0);
			glVertex3d(0.0, 0.0, -10.0);
			glVertex3d(0.0, 0.0, 10.0);
			glEnd();
			break;
		}

		glColor3f(0.0f, 0.0f, 0.0f);
		for (auto polgs : polygons) {
			glBegin(GL_LINE_LOOP);
			for (auto ind : polgs.indexes) {
				glVertex3d(vertexes[ind].x * scale, vertexes[ind].y * scale, vertexes[ind].z * scale);
			}
			glEnd();
		}
		if (isPick) glColor3f(colorPick.r, colorPick.g, colorPick.b);
		else glColor3f(colorUnpick.r, colorUnpick.g, colorUnpick.b);
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
	bool cont = false;
	for (auto i: vertexes) {
		for (auto j : res)
			if ((abs(j.x - i.x) < 0.001) && (abs(j.y - i.y) < 0.001)) {
				cont = true;
				break;
			}
		if (!cont) res.push_back(Vector(i.x, i.y, 0.0));
		else cont = false;
	}
	return res;
}

vector<Vertex> Mesh::getVertexesProjectionOXZ() {
	vector<Vertex> res;
	bool cont = false;
	for (auto i : vertexes) {
		for (auto j : res)
			if ((abs(j.x - i.x) < 0.001) && (abs(j.z - i.z) < 0.001)) {
				cont = true;
				break;
			}
		if (!cont) res.push_back(Vertex(i.x, 0.0, i.z));
		else cont = false;
	}
	return res;
}

vector<Vertex> Mesh::getVertexesProjectionOYZ() {
	vector<Vertex> res;
	bool cont = false;
	for (auto i : vertexes) {
		for (auto j : res)
			if ((abs(j.y - i.y) < 0.001) && (abs(j.z - i.z) < 0.001)) {
				cont = true;
				break;
			}
		if (!cont) res.push_back(Vertex(0.0, i.y, i.z));
		else cont = false;
	}
	return res;
}
