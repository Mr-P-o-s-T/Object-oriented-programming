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
	std::vector<Mesh::Vertex> getOXYProj();
	std::vector<Mesh::Vertex> getOXZProj();
	std::vector<Mesh::Vertex> getOYZProj();

	Mesh meshes[2];
};
