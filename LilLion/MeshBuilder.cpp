#include "MeshBuilder.h"

MeshBuilder::MeshBuilder(unsigned vertex, unsigned face, unsigned normal, unsigned mapping) {
	_mesh._counter[VERTEX_ID] = vertex;
	_mesh._counter[FACE_ID] = face;
	_mesh._counter[NORMAL_ID] = normal;
	_mesh._counter[MAPPING_ID] = mapping;

	int faceHelper = 3; // 3 vertex per face

	_mesh._vertex  = new float[vertex *3];
	if (mapping > 0) {
		_mesh._mapping = new float[mapping *2];
		faceHelper += 3; // 3 uv-vertex per face
	}
	if (normal > 0) {
		_mesh._normal  = new float[normal *3];
		faceHelper++; // 1 normal per face
	}

	_mesh._epf = static_cast<MeshEPF>(faceHelper);
	_mesh._face = new UINT[face *faceHelper];
}

MeshBuilder::~MeshBuilder() {
}

void MeshBuilder::vertexBuffer(float * vertex) {
	memcpy(_mesh._vertex, vertex, _mesh.vertex() *3*sizeof(float));
}

void MeshBuilder::faceBuffer(UINT * face) {
	USHORT faceHelper = static_cast<USHORT>(_mesh._epf);

	memcpy(_mesh._face, face, _mesh.face() *faceHelper*sizeof(UINT));
}

void MeshBuilder::normalBuffer(float * normal) {
	memcpy(_mesh._normal, normal, _mesh.normal() *3*sizeof(float));
}

void MeshBuilder::mappingBuffer(float * mapping) {
	memcpy(_mesh._mapping, mapping, _mesh.mapping() *2*sizeof(float));
}

const Mesh& MeshBuilder::build() const noexcept {
	return _mesh;
}
