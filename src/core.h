/*
 * core.h
 *
 *  Created on: Oct 13, 2014
 *      Author: kenaco
 */

#ifndef CORE_H_
#define CORE_H_

#include <SDL.h>
#include <SDL_video.h>
#include <glbinding/gl/gl.h>
#include <assimp/Importer.hpp>

#include "renderer.h"


class Core_t {
private:
	SDL_Window* window;
	Assimp::Importer importer;
	Renderer_t* renderer;
	bool quit;

public:
	Core_t();
	virtual ~Core_t();

	void loadAssets(std::string& fileName);
	void updateControls();
	void renderLoop();
};

#endif /* CORE_H_ */
