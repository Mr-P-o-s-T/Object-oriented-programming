#pragma once
#include "Mesh.h"
#include "Camera.h"

class Scene {
public:
	Scene(const char *mesh0, const char *mesh1) {
		meshes[0].first.createMesh(mesh0);
		meshes[0].second = false;
		meshes[1].first.createMesh(mesh1);
		meshes[1].second = false;
		cam = new Camera(5, 5, 5);
	}

	void BuildScene();

	void Save();
	void Load();

	void keyFunc(unsigned char key, int x, int y);

	void mouseFunc(int button, int state, int x, int y);

	void mouseMoveFunc(int x, int y);

	Mesh &getMesh(bool first) {
		if (first) return meshes[0].first;
		return meshes[1].first;
	}

	~Scene() = default;
private:
	std::pair<Mesh, bool> meshes[2];
	Camera *cam;

	enum State {
		None,
		Translation,
		Rotation,
		Scale
	} currState = None;

	bool change = false;
	double px = 0, py = 0;

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
