#pragma once

#include <string>
#include <stdexcept>
#include <memory>

#include <SDL.h>

#include "CustomTypes.h"
#include "Scene.h"

#define DEFAULT_FRAMERATE 60

class Window {
private:
	Scene* _scene =nullptr;

	SDL_Window*   _window  = nullptr;
	SDL_GLContext _context = nullptr;
	bool          _running = true;
	UINT          _fps     = 0;
	ULONG         _mspf    = 0;

	static std::unique_ptr<Window> _instance;

	Window();

	void _dtor();
public:
	Window(const Window&) =delete;
	void operator = (const Window&) = delete;

	static Window& self() noexcept {
		if (not _instance) _instance = std::unique_ptr<Window>(new Window());
		return *_instance;
	}
 
	void start(const char* title, UINT width, UINT height) throw(std::runtime_error);
	void changeScene(Scene&) noexcept;
	void render() const noexcept;
	void close() noexcept;
	void fps(UINT) noexcept;
};

