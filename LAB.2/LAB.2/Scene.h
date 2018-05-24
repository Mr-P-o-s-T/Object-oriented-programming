#pragma once
#include "Mesh.h"

class Scene {
public:
	Scene(const char *mesh0, const char *mesh1) {
		meshes[0].loadMesh(mesh0);
		meshes[1].loadMesh(mesh1);
	}

	~Scene() = default;
private:
	std::vector<class Vertex> getOXYProj();
	std::vector<class Vertex> getOXZProj();
	std::vector<class Vertex> getOYZProj();

	Mesh meshes[2];
};
