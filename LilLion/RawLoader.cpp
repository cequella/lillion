#include "RawLoader.h"

RawLoader::RawLoader(RawMethod* method) : _method(method) {
}

RawLoader::~RawLoader() {
	if (_method) {
		delete _method;
		_method =nullptr;
	}
}

Asset RawLoader::read(const char * path) {
	if (not path) return Asset();

	std::ifstream file;
	file.open(path);

	std::string line;
	while (std::getline(file, line)) {
		_method->onLineRead(line);
	}
	file.close();

	return _method->atEOF();
}
