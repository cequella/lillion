#include "WavefrontObj.h"

WavefrontObj::WavefrontObj() {
}


WavefrontObj::~WavefrontObj() {
}


void WavefrontObj::_addVertex(std::string line) noexcept {
	float v[3];
	sscanf_s(line.c_str(), "%*c %f %f %f", &v[0], &v[1], &v[2]);

	_builder.addVertex(v[0], v[1], v[2]);
}
void WavefrontObj::_addNormal(std::string line) noexcept {
	float n[3];
	sscanf_s(line.c_str(), "%*c%*c %f %f %f", &n[0], &n[1], &n[2]);

	_builder.addNormal(n[0], n[1], n[2]);
}
void WavefrontObj::_addMapping(std::string line) noexcept {
	float m[3];
	sscanf_s(line.c_str(), "%*c%*c %f %f", &m[0], &m[1]);

	_builder.addMapping(m[0], m[1]);
}
void WavefrontObj::_addFace(std::string line) noexcept {
	UINT f[7];
	sscanf_s(
		line.c_str(),
		"%*c %d/%d/%d %d/%d/%*d %d/%d/%*d",
		&f[1], &f[4], &f[0], &f[2], &f[5], &f[3], &f[6]);

	_builder.addFace(
		f[0] - 1, f[1] - 1, f[2] - 1,
		f[3] - 1, f[4] - 1, f[5] - 1,
		f[6] - 1
	);
}

void WavefrontObj::onLineRead(std::string line) {
	if (line.size() < 2) return;

	char c = line[0];
	if (c == 'f') {
		_addFace(line);
	}
	else if (c == 'v') {
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
void* WavefrontObj::atEOF() {
	return _builder.build();
}