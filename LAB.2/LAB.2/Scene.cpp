#define _USE_MATH_DEFINES

#include "Scene.h"
#include "Vertex.h"
#include "glut.h"
#include <algorithm>
#include <cmath>
using namespace std;

bool clockwiseRot(const Vertex &a, const Vertex &b, const Vertex &c) {
	if (!a.z) return ((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x)) < 0;
	if (!a.y) return ((b.x - a.x) * (c.z - a.z) - (b.z - a.z) * (c.x - a.x)) < 0;
	return ((b.y - a.y) * (c.z - a.z) - (b.z - a.z) * (c.y - a.y)) < 0;
}

void Scene::BuildScene() {
	cam->updateCamera();
	meshes[0].first.drawMesh(meshes[0].second);
	if (meshes[0].second) drawProjections(meshes[0].first);
	meshes[1].first.drawMesh(meshes[1].second);
	if (meshes[1].second) drawProjections(meshes[1].first);
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
	if (currState == None || currState == Scale) {
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
		if (state == GLUT_UP) change = false;
		else {
			change = true;
			px = x;
			py = y;
		}
	}
}

void Scene::mouseMoveFunc(int x, int y) {
	if (change) {
		Mesh::Vector mouseVect(-(x - px) / 400.0, -(y - py) / 400.0, 0.0);
		switch (currState) {
		case Translation: changePosition(mouseVect);
			px = x; py = y;
			break;
		case Rotation: changeRotation(mouseVect);
			px = x; py = y;
			break;
		case Scale: changeScale(mouseVect);
			break;
		}
	}
}

void Scene::drawProjections(Mesh &m) {
	vector<Vertex> OXY = getOXYProj(m), OXZ = getOXZProj(m), OYZ = getOYZProj(m);

	glPushMatrix();
	glTranslated(m.center->x, m.center->y, 0.0);
	glBegin(GL_LINE_LOOP);
	for (auto i: OXY) {
		glVertex3d(i.x, i.y, i.z);
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(m.center->x, 0.0, m.center->z);
	glBegin(GL_LINE_LOOP);
	for (auto i : OXZ) {
		glVertex3d(i.x, i.y, i.z);
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.0, m.center->y, m.center->z);
	glBegin(GL_LINE_LOOP);
	for (auto i : OYZ) {
		glVertex3d(i.x, i.y, i.z);
	}
	glEnd();
	glPopMatrix();
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
		while ((top != set.size()) && clockwiseRot(set[top], set[top - 1], set[top - 2])) set.erase(set.begin() + top - 1);
	}
	return set;
}

vector<Vertex> Scene::getOXZProj(Mesh &m) {
	vector<Vertex> set = m.getVertexesProjectionOXZ();
	for (size_t i = 1; i < set.size(); i++)
		if (set[i].x < set[0].x) swap(set[i], set[0]);
	sort(set.begin() + 1, set.end(), [&set](Vertex a, Vertex b)->bool {
		return ((a.x - set[0].x) * (b.z - set[0].z) - (a.z - set[0].z) * (b.x - set[0].x)) < 0;
	});
	size_t top = 2;
	for (; top < set.size(); top++) {
		while ((top != set.size()) && clockwiseRot(set[top], set[top - 1], set[top - 2])) set.erase(set.begin() + top - 1);
	}
	return set;
}

vector<Vertex> Scene::getOYZProj(Mesh &m) {
	vector<Vertex> set = m.getVertexesProjectionOYZ();
	for (size_t i = 1; i < set.size(); i++)
		if (set[i].y < set[0].y) swap(set[i], set[0]);
	sort(set.begin() + 1, set.end(), [&set](Vertex a, Vertex b)->bool {
		return ((a.y - set[0].y) * (b.z - set[0].z) - (a.z - set[0].z) * (b.y - set[0].y)) < 0;
	});
	size_t top = 2;
	for (; top < set.size(); top++) {
		while ((top != set.size()) && clockwiseRot(set[top], set[top - 1], set[top - 2])) set.erase(set.begin() + top - 1);
	}
	return set;
}

Mesh::Vector Scene::get3DEquivalent(Mesh::Vector &vector) {
	Mesh::Vector camVect = cam->getCameraVector();
	Mesh::Vector oXEqv = Mesh::Vector(0.0, 0.0, 1.0).vectorComposition(camVect), oYEqv = camVect.vectorComposition(oXEqv);
	oXEqv = oXEqv.normalise(); oYEqv = oYEqv.normalise();
	return Mesh::Vector(vector.x * oXEqv.x + vector.y * oYEqv.x, vector.x * oXEqv.y + vector.y * oYEqv.y, vector.x * oXEqv.z + vector.y * oYEqv.z);
}

void Scene::changePosition(Mesh::Vector &moveVect) {
	Mesh::Vector eqv = get3DEquivalent(moveVect);
	if (meshes[0].second) {
		meshes[0].first.changePosition(eqv.x, eqv.y, eqv.z);
	}
	if (meshes[1].second) {
		meshes[1].first.changePosition(eqv.x, eqv.y, eqv.z);
	}
}

void Scene::changeRotation(Mesh::Vector &rotVect) {
	Mesh::Vector eqv = get3DEquivalent(rotVect);
	double R = cam->getCameraVector().length();
	R = 2 * R * R;
	double dphi = eqv.x >= 0.0 ? 1.0 : -1.0, dxi = eqv.y >= 0.0 ? 1.0 : -1.0, dpsi = eqv.z >= 0.0 ? 1.0 : -1.0;
	dphi *= acos(1.0 - abs(Mesh::Vector(eqv.x, eqv.y, 0.0).length()) / R) * 180 / M_PI;
	dxi *= acos(1.0 - abs(Mesh::Vector(eqv.x, 0.0, eqv.z).length()) / R) * 180 / M_PI;
	dpsi *= acos(1.0 - abs(Mesh::Vector(0.0, eqv.y, eqv.z).length()) / R) * 180 / M_PI;
	if (meshes[0].second) {
		meshes[0].first.changeAngles(dphi, dxi, dpsi);
	}
	if (meshes[1].second) {
		meshes[1].first.changeAngles(dphi, dxi, dpsi);
	}
}

void Scene::changeScale(Mesh::Vector &scaleVect) {
	Mesh::Vector eqv = get3DEquivalent(scaleVect), camV = cam->getCameraVector();
	if (meshes[0].second) {
		double R = Mesh::Vector(eqv.x + camV.x - meshes[0].first.center->x, eqv.y + camV.y - meshes[0].first.center->y, eqv.z + camV.z - meshes[0].first.center->z).length() - camV.length();
		static double prevR0 = R - camV.length();
		meshes[0].first.setScale(meshes[0].first.getScale() * R / prevR0);
	}
	if (meshes[1].second) {
		double R = Mesh::Vector(eqv.x + camV.x - meshes[1].first.center->x, eqv.y + camV.y - meshes[1].first.center->y, eqv.z + camV.z - meshes[1].first.center->z).length();
		static double prevR1 = R;
		meshes[1].first.setScale(R / prevR1);
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
