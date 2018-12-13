#define SDL_MAIN_HANDLED main

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdio>

#include <SDL.h>
#include <SDL_opengl.h>
#include <glm.hpp>

#include "Scene.h"
#include "Window.h"
#include "RawMethod.h"
#include "RawLoader.h"
#include "Mesh.h"
#include "MeshBuilder.h"
#include "WavefrontObj.h"

using namespace std;

class EmptyScene final : public Scene {
private:
	Window& window = Window::self();
	Mesh* _cube = nullptr;

public:
	EmptyScene() {
		RawLoader loader(new WavefrontObj());

		const char* path = "C:\\Users\\Usuario\\Documents\\cube.obj";
		_cube = static_cast<Mesh*>(loader.read(path));
	}
	~EmptyScene() override {
		if (_cube) {
			delete _cube;
			_cube = nullptr;
		}
	}

	void update() override {}
	void render(SDL_Surface* surface, ULONG) override {
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		_cube->render();

		window.render();

		SDL_Delay(3000);
		window.close();
	}
};

int main(int, char**) {
	Window& window = Window::self();
	EmptyScene empty;

	window.changeScene(empty);
	window.start("Teste", 800, 600);

	return 0;
}