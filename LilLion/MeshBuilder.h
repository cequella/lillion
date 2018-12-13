#pragma once

#include <iostream>
#include <vector>
#include <string.h>

#include "Mesh.h"

class MeshBuilder {
private:
	std::vector<float> _vertex  = {};
	std::vector<float> _normal  = {};
	std::vector<float> _mapping = {};
	std::vector<UINT>  _face    = {};

public:
	MeshBuilder();
	~MeshBuilder();

	void addVertex(float v1, float v2, float v3);
	void addFace(UINT v1, UINT v2, UINT v3);
	void addFace(UINT v1, UINT v2, UINT v3, UINT n);
	void addFace(UINT v1, UINT v2, UINT v3, UINT t1, UINT t2, UINT t3);
	void addFace(UINT v1, UINT v2, UINT v3, UINT t1, UINT t2, UINT t3, UINT n);
	void addNormal(float n1, float n2, float n3);
	void addMapping(float t1, float t2);
	void clear() noexcept;

	Mesh* build() const noexcept;
};

