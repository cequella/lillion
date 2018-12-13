#pragma once

#include "RawMethod.h"
#include "MeshBuilder.h"

class WavefrontObj final : public RawMethod {
private:
	MeshBuilder _builder = MeshBuilder();
	
	void _addVertex(std::string line) noexcept;
	void _addNormal(std::string line) noexcept;
	void _addMapping(std::string line) noexcept;
	void _addFace(std::string line) noexcept;
public:
	WavefrontObj();
	~WavefrontObj();
	
	void onLineRead(std::string line) override;
	void * atEOF() override;
};

