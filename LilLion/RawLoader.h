#pragma once

#include <fstream>
#include <string>

#include "RawMethod.h"
#include "Asset.h"

class RawLoader {
private:
	RawMethod* _method;

public:
	RawLoader(RawMethod* method);
	~RawLoader();

	Asset read(const char* path);
};

