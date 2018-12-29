#include "Prop3D.h"

Prop3D::Prop3D() {
}

Prop3D::~Prop3D() {
}

void Prop3D::mesh(const Mesh & t_mesh) noexcept {
	_mesh = const_cast<Mesh*>(&t_mesh);
}

// TODO - Only working with 7-parameters per face object
void Prop3D::render() const noexcept {
	glBegin(GL_TRIANGLES);

	const USHORT epf = static_cast<UINT>(MeshEPF::VERTEX_NORMAL_AND_MAPPING);
	for (UINT i = 0; i < _mesh->face(); i++) {
		const UINT faceId = i * epf;

		const UINT v1 = _mesh->_face[faceId +0];
		const UINT v2 = _mesh->_face[faceId +1];
		const UINT v3 = _mesh->_face[faceId +2];
		const UINT t1 = _mesh->_face[faceId +3];
		const UINT t2 = _mesh->_face[faceId +4];
		const UINT t3 = _mesh->_face[faceId +5];
		const UINT n  = _mesh->_face[faceId +6];

		glNormal3fv(_mesh->_normal +n*3);

		glTexCoord2fv(_mesh->_mapping + t1 * 2);
		glVertex3fv(_mesh->_vertex +v1*3);
		
		glTexCoord2fv(_mesh->_mapping + t2 * 2);
		glVertex3fv(_mesh->_vertex +v2*3);
		
		glTexCoord2fv(_mesh->_mapping + t3 * 2);
		glVertex3fv(_mesh->_vertex +v3*3);
	}

	glEnd();
}
