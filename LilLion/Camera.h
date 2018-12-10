#pragma once

#include <glm.hpp>
#include <gl.h>
#include <glu.h>

#define GETTER(CLASSNAME, ATTRIBUTE, TYPE) TYPE ATTRIBUTE() const noexcept { return _ ## ATTRIBUTE; }
#define SETTER(CLASSNAME, ATTRIBUTE, TYPE) void ATTRIBUTE(TYPE t ## ATTRIBUTE) noexcept { _ ## ATTRIBUTE = t ## ATTRIBUTE; }

class Camera {
private:
	glm::vec3 _position;
	glm::vec3 _target;
	glm::vec3 _up;

public:
	Camera();
	~Camera();

	GETTER(Camera, position, glm::vec3);
	GETTER(Camera, target, glm::vec3);
	GETTER(Camera, up, glm::vec3);

	SETTER(Camera, position, glm::vec3);
	SETTER(Camera, target, glm::vec3);
	SETTER(Camera, up, glm::vec3);

	void start() const noexcept;
};

