#pragma once

#include "Mesh.h"

class Prop3D {
private:
	Mesh _mesh;

public:
	Prop3D();
	~Prop3D();

	void render() const noexcept;
};

