#include "Mesh.h"

void Mesh::_clearPointer(void * pointer) noexcept {
	if (not pointer) {
		delete[] pointer;
		pointer = nullptr;
	}
}

Mesh::Mesh() : 
	_counter{0, 0, 0, 0},
	_vertex(nullptr),
	_normal(nullptr),
	_mapping(nullptr),
	_face(nullptr),
	_epf(MeshEPF::NOT_INITIALIZED){}

Mesh::~Mesh() {
	_counter[0] = _counter[1] = _counter[2] = _counter[3] = 0;
	_epf = MeshEPF::NOT_INITIALIZED;
	
	_clearPointer(_vertex);
	_clearPointer(_face);
	_clearPointer(_normal);
	_clearPointer(_mapping);
}

void Mesh::render() const noexcept {
	glBegin(GL_TRIANGLES);
	for (UINT i = 0; i < face(); i++) {
		const UINT id = i * 3;
		const UINT v1 = _face[id];
		const UINT v2 = _face[id +1];
		const UINT v3 = _face[id +2];

		glVertex3fv(_vertex +3*v1);
		glVertex3fv(_vertex +3*v2);
		glVertex3fv(_vertex +3*v3);
	}
	glEnd();
}
