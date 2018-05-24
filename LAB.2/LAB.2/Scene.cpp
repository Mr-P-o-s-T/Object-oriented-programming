#include "Scene.h"
#include "Vertex.h"
#include <algorithm>
using namespace std;

bool clockwiseRot(const Vertex &a, const Vertex &b, const Vertex &c) {
	if (!a.z) return ((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x)) < 0;
	if (!a.y) return ((b.x - a.x) * (c.z - a.z) - (b.z - a.z) * (c.x - a.x)) < 0;
	if (!a.x) return ((b.y - a.y) * (c.z - a.z) - (b.z - a.z) * (c.y - a.y)) < 0;
}

vector<Vertex> Scene::getOXYProj() {
	vector<Vertex> set = meshes[0].getVertexesProjectionOXY();
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

vector<Vertex> Scene::getOXZProj() {
	vector<Vertex> set = meshes[0].getVertexesProjectionOXY();
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

vector<Vertex> Scene::getOYZProj() {
	vector<Vertex> set = meshes[0].getVertexesProjectionOXY();
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
