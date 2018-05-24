#pragma once
#include "Mesh.h"
#include "Camera.h"

class Scene {
public:
	Scene(const char *mesh0, const char *mesh1) {
		meshes[0].loadMesh(mesh0);
		meshes[1].loadMesh(mesh1);
	}

	void BuildScene();

	~Scene() = default;
private:
	Mesh meshes[2];
	Camera cam;

	std::vector<class Vertex> getOXYProj(Mesh &m);
	std::vector<class Vertex> getOXZProj(Mesh &m);
	std::vector<class Vertex> getOYZProj(Mesh &m);

	void drawAxes();
};
