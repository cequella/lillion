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

using namespace std;

/*
class EmptyScene final : public Scene {
private:
	Window& window = Window::self();

	const float colorBuffer[12] = {
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0,
		1.0, 0.0, 1.0
	};
	const float vertexBuffer[20] = {
		-0.5f,  0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
	};
	const unsigned faceBuffer[4] = {
		0, 1, 2, 3
	};
public:
	~EmptyScene() override {}

	void update() override {}
	void render(SDL_Surface* surface, ULONG) override {
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glBegin(GL_QUADS);
		for (unsigned i = 0; i < 4; i++) {
			glColor3fv(colorBuffer +3*i);
			glVertex3fv(vertexBuffer +3*i);
		}
		glEnd();

		window.render();

		SDL_Delay(3000);
		window.close();
	}
};
*/

class WavefronOBJLoader final : public RawMethod {
private:
	MeshBuilder _builder =MeshBuilder();

	void _addVertex(std::string line) noexcept {
		float v[3];
		sscanf_s(line.c_str(), "%*c %f %f %f", &v[0], &v[1], &v[2]);

		_builder.addVertex(v[0], v[1], v[2]);
	}
	void _addNormal(std::string line) noexcept {
		float n[3];
		sscanf_s(line.c_str(), "%*c%*c %f %f %f", &n[0], &n[1], &n[2]);

		_builder.addNormal(n[0], n[1], n[2]);
	}
	void _addMapping(std::string line) noexcept {
		float m[3];
		sscanf_s(line.c_str(), "%*c%*c %f %f", &m[0], &m[1]);

		_builder.addMapping(m[0], m[1]);
	}
	void _addFace(std::string line) noexcept {
		UINT f[7];
		sscanf_s(line.c_str(), 
				"%*c %d/%d/%d %d/%d/%*d %d/%d/%*d", 
				&f[1], &f[4], &f[0], &f[2], &f[5], &f[3], &f[6]);

		_builder.addFace(f[0] -1, f[1] -1, f[2] -1,
						 f[3] -1, f[4] -1, f[5] -1,
						 f[6] -1);
	}

public:
	~WavefronOBJLoader() override {}

	void onLineRead(std::string line) override {
		if (line.size() < 2) return;

		char c = line[0];
		if (c =='f') {
			_addFace(line);
		} else if (c =='v') {
			c = line[1];
			
			switch (c) {
			case ' ':
				_addVertex(line);
				break;
			case 'n':
				_addNormal(line);
				break;
			case 't':
				_addMapping(line);
				break;
			}
		}
	}

	void* atEOF() override {
		return _builder.build();
	}
};

int main(int, char**) {
	RawLoader loader(new WavefronOBJLoader());

	const char* path ="C:\\Users\\Usuario\\Documents\\cube.obj";
	Mesh* mesh =static_cast<Mesh*>(loader.read(path));
	
	return 0;
}