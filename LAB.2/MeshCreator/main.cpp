// main file
#include <iostream>
#include <fstream>
using namespace std;

int main() {
	size_t n;
	cin >> n;
	ofstream meshHolder("../LAB.2/meshes/mesh.mesh");
	meshHolder.write((char *)&n, sizeof(n));
	for (size_t i = 0; i < 3 * n; i++) {
		double coord;
		cin >> coord;
		meshHolder.write((char *)&coord, sizeof(coord));
	}
	cin >> n;
	meshHolder.write((char *)&n, sizeof(n));
	size_t narity;
	cin >> narity;
	meshHolder.write((char *)&narity, sizeof(n));
	for (size_t i = 0; i < narity * n; i++) {
		size_t index;
		cin >> index;
		meshHolder.write((char *)&index, sizeof(index));
	}
	meshHolder.close();
	return 0;
}