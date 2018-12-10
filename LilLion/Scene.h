#pragma once

#include <SDL.h>

#include "CustomTypes.h"

class Scene {
public:
	virtual ~Scene() {}

	virtual void update() = 0;
	virtual void render(SDL_Surface*, ULONG) = 0;
};

