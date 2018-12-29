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
	Window& window =Window::self();
	Mesh* _mesh =nullptr;

public:
	EmptyScene() {
		RawLoader loader(new WavefrontObj());

		const char* path = "C:\\Users\\Usuario\\Documents\\stanfordBunny.obj";
		_mesh =static_cast<Mesh*>(loader.read(path));
	}
	~EmptyScene() override {
		if (_mesh) {
			delete _mesh;
			_mesh =nullptr;
		}
	}

	void update() override {}
	void render(SDL_Surface* surface, ULONG) override {
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClearDepth(1.0);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);

		glDepthFunc(GL_LEQUAL);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		GLfloat LightAmbient[]  ={ 0.5f, 0.5f, 0.5f, 1.0f };
		GLfloat LightDiffuse[]  ={ 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat LightPosition[] ={ 0.0f, 0.0f, -2.0f, 1.0f };

		glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
		glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);

		glPushMatrix();
		glScalef(5.0, 5.0, 5.0);
		_mesh->render();
		glPopMatrix();

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