#include "Scene.h"
#include "Vertex.h"
#include "glut.h"
#include <algorithm>
using namespace std;

bool clockwiseRot(const Vertex &a, const Vertex &b, const Vertex &c) {
	if (!a.z) return ((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x)) < 0;
	if (!a.y) return ((b.x - a.x) * (c.z - a.z) - (b.z - a.z) * (c.x - a.x)) < 0;
	return ((b.y - a.y) * (c.z - a.z) - (b.z - a.z) * (c.y - a.y)) < 0;
}

void Scene::BuildScene() {
	cam->updateCamera();
	meshes[0].first.drawMesh(meshes[0].second);
	meshes[1].first.drawMesh(meshes[1].second);
	drawAxes();
}

void Scene::keyFunc(unsigned char key, int x, int y) {
	switch (key) {
	case '1': meshes[0].second = !meshes[0].second;
		break;
	case '2': meshes[1].second = !meshes[1].second;
		break;
	case 't': 
		if (currState == Translation) currState = None;
		else currState = Translation;
		break;
	case 'r':
		if (currState == Rotation) currState = None;
		else currState = Rotation;
		break;
	case 's':
		if (currState == Scale) currState = None;
		else currState = Scale;
		break;
	case 'x':
		if (meshes[0].first.axis == Mesh::x) meshes[0].first.axis = Mesh::None;
		else meshes[0].first.axis = Mesh::x;
		if (meshes[1].first.axis == Mesh::x) meshes[1].first.axis = Mesh::None;
		else meshes[1].first.axis = Mesh::x;
		break;
	case 'y':
		if (meshes[0].first.axis == Mesh::y) meshes[0].first.axis = Mesh::None;
		else meshes[0].first.axis = Mesh::y;
		if (meshes[1].first.axis == Mesh::y) meshes[1].first.axis = Mesh::None;
		else meshes[1].first.axis = Mesh::y;
		break;
	case 'z':
		if (meshes[0].first.axis == Mesh::z) meshes[0].first.axis = Mesh::None;
		else meshes[0].first.axis = Mesh::z;
		if (meshes[1].first.axis == Mesh::z) meshes[1].first.axis = Mesh::None;
		else meshes[1].first.axis = Mesh::z;
		break;
	}
	if (!(meshes[0].second || meshes[1].second)) currState = None;
	if (currState == None) {
		meshes[0].first.axis = Mesh::None;
		meshes[1].first.axis = Mesh::None;
	}
	else {
		if (!meshes[0].second) meshes[0].first.axis = Mesh::None;
		if (!meshes[1].second) meshes[1].first.axis = Mesh::None;
	}
}

void Scene::mouseFunc(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_UP) {
			change = false;
		}
		else {
			change = true;
		}
	}
}

void Scene::mouseMoveFunc(int x, int y) {

	if (change) {
		switch (currState) {
		case Translation: 
			break;
		case Rotation: 
			break;
		case Scale: 
			break;
		}
	}
}

vector<Vertex> Scene::getOXYProj(Mesh &m) {
	vector<Vertex> set = m.getVertexesProjectionOXY();
	for (size_t i = 1; i < set.size(); i++)
		if (set[i].x < set[0].x) swap(set[i], set[0]);
	sort(set.begin() + 1, set.end(), [&set](Vertex a, Vertex b)->bool {
		return ((a.x - set[0].x) * (b.y - set[0].y) - (a.y - set[0].y) * (b.x - set[0].x)) < 0;
	});
	size_t top = 2;
	for (; top < set.size(); top++) {
		while (clockwiseRot(set[top], set[top - 1], set[top - 2])) set.erase(set.begin() + top - 1);
		top++;
	}
	return set;
}

vector<Vertex> Scene::getOXZProj(Mesh &m) {
	vector<Vertex> set = m.getVertexesProjectionOXY();
	for (size_t i = 1; i < set.size(); i++)
		if (set[i].x < set[0].x) swap(set[i], set[0]);
	sort(set.begin() + 1, set.end(), [&set](Vertex a, Vertex b)->bool {
		return ((a.x - set[0].x) * (b.z - set[0].z) - (a.z - set[0].z) * (b.x - set[0].x)) < 0;
	});
	size_t top = 2;
	for (; top < set.size(); top++) {
		while (clockwiseRot(set[top], set[top - 1], set[top - 2])) set.erase(set.begin() + top - 1);
		top++;
	}
	return set;
}

vector<Vertex> Scene::getOYZProj(Mesh &m) {
	vector<Vertex> set = m.getVertexesProjectionOXY();
	for (size_t i = 1; i < set.size(); i++)
		if (set[i].x < set[0].x) swap(set[i], set[0]);
	sort(set.begin() + 1, set.end(), [&set](Vertex a, Vertex b)->bool {
		return ((a.y - set[0].y) * (b.z - set[0].z) - (a.z - set[0].z) * (b.y - set[0].y)) < 0;
	});
	size_t top = 2;
	for (; top < set.size(); top++) {
		while (clockwiseRot(set[top], set[top - 1], set[top - 2])) set.erase(set.begin() + top - 1);
		top++;
	}
	return set;
}

Vertex Scene::get3DEquivalent(Vertex &vector) {
	Vertex camVect = cam->getCameraVector();
	Vertex oXEqv(-camVect.y, camVect.x), oYEqv(-camVect.x * camVect.z, -camVect.y * camVect.z, camVect.x * camVect.x + camVect.y * camVect.y);
	return Vertex(vector.x * oXEqv.x + vector.y * oYEqv.x, vector.x * oXEqv.y + vector.y * oYEqv.y, vector.x * oXEqv.z + vector.y * oYEqv.z);
}

void Scene::changePosition(Vertex &moveVect) {
	Vertex eqv = get3DEquivalent(moveVect);
	if (meshes[0].second) {
		meshes[0].first.changePosition(eqv.x, eqv.y, eqv.z);
	}
	if (meshes[1].second) {
		meshes[1].first.changePosition(eqv.x, eqv.y, eqv.z);
	}
}

void Scene::changeRotation(Vertex &moveVect) {
	if (meshes[0].second) {

	}
	if (meshes[1].second) {

	}
}

void Scene::changeScale(Vertex &moveVect) {
	if (meshes[0].second) {

	}
	if (meshes[1].second) {

	}
}

void Scene::drawAxes() {
	glPushMatrix();
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3d(-10.0, 0.0, 0.0);
	glColor3f(1.0, 0, 0.0);
	glVertex3d(10.0, 0.0, 0.0);

	glColor3f(0.0, 0.0, 0.0);
	glVertex3d(0.0, -10.0, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3d(0.0, 10.0, 0.0);

	glColor3f(0.0, 0.0, 0.0);
	glVertex3d(0.0, 0.0, -10.0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3d(0.0, 0.0, 10.0);
	glEnd();
	glPopMatrix();
}
