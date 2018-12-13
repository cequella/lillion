#include "MeshBuilder.h"

MeshBuilder::MeshBuilder() {
}

MeshBuilder::~MeshBuilder() {
}

void MeshBuilder::addVertex(float v1, float v2, float v3) {
	_vertex.push_back(v1);
	_vertex.push_back(v2);
	_vertex.push_back(v3);
}

void MeshBuilder::addFace(UINT v1, UINT v2, UINT v3) {
	_face.push_back(v1);
	_face.push_back(v2);
	_face.push_back(v3);
}

void MeshBuilder::addFace(UINT v1, UINT v2, UINT v3, UINT n) {
	_face.push_back(v1);
	_face.push_back(v2);
	_face.push_back(v3);
	_face.push_back(n);
}

void MeshBuilder::addFace(UINT v1, UINT v2, UINT v3, UINT t1, UINT t2, UINT t3) {
	_face.push_back(v1);
	_face.push_back(v2);
	_face.push_back(v3);
	_face.push_back(t1);
	_face.push_back(t2);
	_face.push_back(t3);
}

void MeshBuilder::addFace(UINT v1, UINT v2, UINT v3, UINT t1, UINT t2, UINT t3, UINT n) {
	_face.push_back(v1);
	_face.push_back(v2);
	_face.push_back(v3);
	_face.push_back(t1);
	_face.push_back(t2);
	_face.push_back(t3);
	_face.push_back(n);
}

void MeshBuilder::addNormal(float n1, float n2, float n3) {
	_normal.push_back(n1);
	_normal.push_back(n2);
	_normal.push_back(n3);
}

void MeshBuilder::addMapping(float t1, float t2) {
	_mapping.push_back(t1);
	_mapping.push_back(t2);
}

void MeshBuilder::clear() noexcept {
	_vertex.clear();
	_face.clear();
	_normal.clear();
	_mapping.clear();
}

Mesh* MeshBuilder::build() const noexcept {
	Mesh* mesh =new Mesh();

	const int COORD_PER_VERTEX  = 3;
	const int COORD_PER_MAPPING = 2;
	const int COORD_PER_NORMAL  = 3;
	int       ELEMENTS_PER_FACE = 3; // Initially, 3 vertex per face

	mesh->_vertex = new float[_vertex.size()];
	memcpy(mesh->_vertex, _vertex.data(), _vertex.size() *sizeof(float));
	
	mesh->_face = new UINT[_face.size()];
	memcpy(mesh->_face, _face.data(), _face.size() *sizeof(UINT));

	if (not _mapping.empty()) {
		ELEMENTS_PER_FACE += 3; // 3 uv-vertex per face
		mesh->_mapping = new float[_mapping.size()];
		memcpy(mesh->_mapping, _mapping.data(), _mapping.size() * sizeof(float));
	}
	if (not _normal.empty()) {
		ELEMENTS_PER_FACE++; // 1 normal per face
		mesh->_normal = new float[_normal.size()];
		memcpy(mesh->_normal, _normal.data(), _normal.size() * sizeof(float));
	}

	mesh->_epf = static_cast<MeshEPF>(ELEMENTS_PER_FACE);
	mesh->_counter[VERTEX_ID]  = _vertex.size()/COORD_PER_VERTEX;
	mesh->_counter[FACE_ID]    = _face.size()/ ELEMENTS_PER_FACE;
	mesh->_counter[NORMAL_ID]  = _normal.size()/COORD_PER_NORMAL;
	mesh->_counter[MAPPING_ID] = _mapping.size()/COORD_PER_MAPPING;

	return mesh;
}
