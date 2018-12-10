#pragma once

#include <string.h>

#include "Mesh.h"

class MeshBuilder {
private:
	Mesh _mesh =Mesh();

public:
	MeshBuilder(unsigned vertex, unsigned face, unsigned normal =0, unsigned mapping =0);
	~MeshBuilder();

	void vertexBuffer(float* vertex);
	void faceBuffer(UINT* face);
	void normalBuffer(float* normal);
	void mappingBuffer(float* mapping);

	const Mesh& build() const noexcept;
};

