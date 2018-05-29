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

	void keyFunc(unsigned char key, int x, int y);

	void mouseFunc(int button, int state, int x, int y);

	void mouseMoveFunc(int x, int y);

	~Scene() = default;
//private:
	std::pair<Mesh, bool> meshes[2];
	Camera *cam;

	enum State {
		None,
		Translation,
		Rotation,
		Scale
	} currState = None;

	bool change = false;
	int px = 0, py = 0;

	void drawProjections(Mesh &m);

	std::vector<class Vertex> getOXYProj(Mesh &m);
	std::vector<class Vertex> getOXZProj(Mesh &m);
	std::vector<class Vertex> getOYZProj(Mesh &m);

	Mesh::Vector get3DEquivalent(Mesh::Vector &vector);

	void changePosition(Mesh::Vector &moveVect);
	void changeRotation(Mesh::Vector &moveVect);
	void changeScale(Mesh::Vector &moveVect);

	void drawAxes();
};
