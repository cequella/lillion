#pragma once

#define VERTEX_ID  0
#define FACE_ID    1
#define NORMAL_ID  2
#define MAPPING_ID 3

#include <iostream>
#include <string.h>

#include <gl.h>

#include "CustomTypes.h"
#include "Asset.h"

/*
	Elements per face: 
	- 3 : only vertex;
	- 4 : vertex and normal;
	- 6 : vertex and mapping;
	- 7 : vertex, normal and mapping.
*/
enum class MeshEPF : USHORT {
	NOT_INITIALIZED           =0,
	ONLY_VERTEX               =3,
	VERTEX_AND_NORMAL         =4,
	VERTEX_AND_MAPPING        =6,
	VERTEX_NORMAL_AND_MAPPING =7
};

class Mesh final : public Asset {
private:
	friend class MeshBuilder;
	friend class Prop3D;

	UINT    _counter[4];
	float*  _vertex;
	float*  _normal;
	float*  _mapping;
	UINT*   _face;
	MeshEPF _epf; 

	void _clearPointer(void* pointer) noexcept;
public:
	Mesh();
	~Mesh();

	UINT vertex()  const noexcept { return _counter[VERTEX_ID]; }
	UINT face()    const noexcept { return _counter[FACE_ID]; }
	UINT normal()  const noexcept { return _counter[NORMAL_ID]; }
	UINT mapping() const noexcept { return _counter[MAPPING_ID]; }

	void render() const noexcept;
};

