#include "Camera.h"

Camera::Camera() {
}

Camera::~Camera() {
}

void Camera::start() const noexcept {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluLookAt(
		_position.x, _position.y, _position.z,
		_target.x, _target.y, _target.z,
		_up.x, _up.y, _up.z
	);

	glMatrixMode(GL_MODELVIEW);
}
