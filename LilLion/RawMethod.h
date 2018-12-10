#pragma once

#include <string>

#include "Asset.h"

class RawMethod {
public:
	virtual ~RawMethod();

	virtual void  onLineRead(std::string) =0;
	virtual Asset atEOF() =0;
};

