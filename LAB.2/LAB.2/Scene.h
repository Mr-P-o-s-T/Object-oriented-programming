#pragma once
#include "Mesh.h"
#include "Camera.h"

class Scene {
public:
	Scene(const char *mesh0, const char *mesh1) {
		meshes[0].first.loadMesh(mesh0);
		meshes[0].second = false;
		meshes[1].first.loadMesh(mesh1);
		meshes[1].second = false;
	}

	void BuildScene();

	void keyFunc(unsigned char key, int x, int y) {
		switch (key) {
		case '1': meshes[0].second = !meshes[0].second;

			break;
		case '3':
		case '2':
			break;
		default:
			break;
		}
	}

	~Scene() = default;
//private:
	std::pair<Mesh, bool> meshes[2];
	Camera *cam;

	std::vector<class Vertex> getOXYProj(Mesh &m);
	std::vector<class Vertex> getOXZProj(Mesh &m);
	std::vector<class Vertex> getOYZProj(Mesh &m);

	void drawAxes();
};
