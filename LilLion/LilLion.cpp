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
	std::vector<float> _vertex  = {};
	std::vector<float> _normal  = {};
	std::vector<float> _mapping = {};
	std::vector<UINT>  _face    = {};

	void _addVertex(std::string line) noexcept {
		/*
		std::string s;
		float v[3];

		std::ostringstream stream(line);
		stream << s << v[0] << v[1] << v[2];
		*/
		float v[3];
		sscanf_s(line.c_str(), "%*s %f %f %f", &v[0], &v[1], &v[2]);

		_vertex.push_back(v[0]);
		_vertex.push_back(v[1]);
		_vertex.push_back(v[2]);
	}
	void _addNormal(std::string line) noexcept {
		/*
		std::string s;
		float n[3];

		std::ostringstream stream(line);
		stream << s << n[0] << n[1] << n[2];
		*/
		float n[3];
		sscanf_s(line.c_str(), "%*s %f %f %f", &n[0], &n[1], &n[2]);

		_normal.push_back(n[0]);
		_normal.push_back(n[1]);
		_normal.push_back(n[2]);
	}
	void _addMapping(std::string line) noexcept {
		/*
		std::string s;
		float m[2];

		std::ostringstream stream(line);
		stream << s << m[0] << m[1];
		*/
		float m[3];
		sscanf_s(line.c_str(), "%*s %f %f", &m[0], &m[1]);

		_mapping.push_back(m[0]);
		_mapping.push_back(m[1]);
	}
	void _addFace(std::string line) noexcept {
		UINT f[7];
		sscanf_s(line.c_str(), 
				"%*s %d//%d//%d %d//%d//%*d %d//%d//%*d", 
				&f[1], &f[4], &f[0], &f[2], &f[5], &f[3], &f[6]);

		_face.push_back(f[0]);
		_face.push_back(f[1]);
		_face.push_back(f[2]);
		_face.push_back(f[3]);
		_face.push_back(f[4]);
		_face.push_back(f[5]);
		_face.push_back(f[6]);
	}

public:
	~WavefronOBJLoader() override {}

	void onLineRead(std::string line) override {
		if (line.size() < 2) return;

		if (line[0]=='f') {
			_addFace(line);
		}
		else {
			switch (line[1]) {
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

	Asset atEOF() override {
		MeshBuilder builder(_vertex.size()/3, _face.size()/3);
		builder.vertexBuffer(_vertex.data());
		builder.faceBuffer(_face.data());

		return builder.build();
	}
};

int main(int, char**) {
	RawLoader loader(new WavefronOBJLoader());

	const char* path ="C:\\Users\\Usuario\\Documents\\cube.obj";
	loader.read(path);
	//Mesh mesh( static_cast<const Mesh&>(loader.read(path)) );
	
	return 0;
}