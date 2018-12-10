#include "Window.h"

std::unique_ptr<Window> Window::_instance = std::unique_ptr<Window>(nullptr);

Window::Window() {
	fps(DEFAULT_FRAMERATE);
}

void Window::_dtor(){
	SDL_GL_DeleteContext(_context);
	SDL_DestroyWindow(_window);
	SDL_Quit();

	_context = nullptr;
	_window  = nullptr;
}

void Window::start(const char* title, UINT width, UINT height) throw(std::runtime_error) {
	if (not _scene) throw std::runtime_error("Scene not defined!");

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		throw std::runtime_error("SDL video subsystem not initialized");
	}

	_window = SDL_CreateWindow(
		title,
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		width, height,
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
	);
	if (not _window) {
		throw std::runtime_error("Window SDL not initialized");
	}

	_context = SDL_GL_CreateContext(_window);
	if (not _context) {
		throw std::runtime_error("OpenGL context could not be created");
	}

	ULONG currentTimer = 0;
	ULONG oldTick = SDL_GetTicks();
	ULONG currentTick;

	SDL_Surface* screen = SDL_GetWindowSurface(_window);
	do {
		do {
			_scene->update();
			currentTick = SDL_GetTicks();
			currentTimer += currentTick - oldTick;
			oldTick = currentTick;
		} while (currentTimer <_mspf);

		currentTimer -= _mspf;
		_scene->render(screen, currentTimer/ _mspf);
	} while (_running);
	SDL_FreeSurface(screen);
	_dtor();
}

void Window::changeScene(Scene& scene) noexcept {
	_scene = const_cast<Scene*>(&scene);
}

void Window::render() const noexcept {
	SDL_GL_SwapWindow(_window);
}

void Window::close() noexcept {
	_running = false;
}

void Window::fps(UINT framerate) noexcept{
	_fps = framerate;
	_mspf = 1000 / framerate;
}
