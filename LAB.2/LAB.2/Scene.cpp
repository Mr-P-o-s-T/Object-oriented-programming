#include "Scene.h"
#include <algorithm>
using namespace std;

bool clockwiseRot(const Mesh::Vertex &a, const Mesh::Vertex &b, const Mesh::Vertex &c) {
	return ((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x)) < 0;
}

vector<Mesh::Vertex> Scene::getOXYProj() {
	vector<Mesh::Vertex> set = meshes[0].getVertexesProjectionOXY();
	for (size_t i = 1; i < set.size(); i++)
		if (set[i].x < set[0].x) swap(set[i], set[0]);
	sort(set.begin() + 1, set.end(), [&set](Mesh::Vertex a, Mesh::Vertex b)->bool {
		return ((a.x - set[0].x) * (b.y - set[0].y) - (a.y - set[0].y) * (b.x - set[0].x)) < 0;
	});
	size_t top = 2;
	for (; top < set.size(); top++) {
		while (clockwiseRot(set[top], set[top - 1], set[top - 2])) set.erase(set.begin() + top - 1);
		top++;
	}
	return set;
}

vector<Mesh::Vertex> Scene::getOXZProj() {
	vector<Mesh::Vertex> set = meshes[0].getVertexesProjectionOXY();
	for (size_t i = 1; i < set.size(); i++)
		if (set[i].x < set[0].x) swap(set[i], set[0]);
	sort(set.begin() + 1, set.end(), [&set](Mesh::Vertex a, Mesh::Vertex b)->bool {
		return ((a.x - set[0].x) * (b.z - set[0].z) - (a.z - set[0].z) * (b.x - set[0].x)) < 0;
	});
	size_t top = 2;
	for (; top < set.size(); top++) {
		while (clockwiseRot(set[top], set[top - 1], set[top - 2])) set.erase(set.begin() + top - 1);
		top++;
	}
	return set;
}

vector<Mesh::Vertex> Scene::getOYZProj() {
	vector<Mesh::Vertex> set = meshes[0].getVertexesProjectionOXY();
	for (size_t i = 1; i < set.size(); i++)
		if (set[i].x < set[0].x) swap(set[i], set[0]);
	sort(set.begin() + 1, set.end(), [&set](Mesh::Vertex a, Mesh::Vertex b)->bool {
		return ((a.x - set[0].x) * (b.y - set[0].y) - (a.y - set[0].y) * (b.x - set[0].x)) < 0;
	});
	size_t top = 2;
	for (; top < set.size(); top++) {
		while (clockwiseRot(set[top], set[top - 1], set[top - 2])) set.erase(set.begin() + top - 1);
		top++;
	}
	return set;
}
