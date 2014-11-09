/*
 * core.cpp
 *
 *  Created on: Oct 13, 2014
 *      Author: kenaco
 */

#include <iostream>
#include <SDL.h>
#include <SDL_events.h>
#include <SDL_video.h>
#include <memory>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "log.h"
#include "core.h"
#include "renderer.h"
#include "exceptions.h"

const int WIDTH = 800;
const int HEIGHT = 600;


Core_t::Core_t(): quit(false) {
	LOG(info) << "Core_t constructor";

	int error;
	error = SDL_Init(SDL_INIT_EVERYTHING); //TODO maybe change

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	window = SDL_CreateWindow("Demo",
							  SDL_WINDOWPOS_UNDEFINED,
							  SDL_WINDOWPOS_UNDEFINED,
							  WIDTH,
							  HEIGHT,
							  SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL|\
							  SDL_WINDOW_RESIZABLE
							  );
	renderer = new Renderer_t(window);

	LOG(info) << "Core_t constructor done";
}


Core_t::~Core_t() {
	LOG(info) << "Core_t destructor";
	delete renderer;
	SDL_DestroyWindow(window);

	LOG(info) << "Core_t destructor done";
}


void Core_t::loadAssets(std::string fileName) {
	const aiScene* scene = importer.ReadFile(fileName, aiProcess_Triangulate |
											 aiProcess_JoinIdenticalVertices |
											 aiProcess_SortByPType);
	if (!scene) {
		throw LoadException(importer.GetErrorString());
	}
	renderer->setScene(scene);
}


void Core_t::updateControls() {
	LOG(info) << "Core_t.updateControls()";

	SDL_Event event;
	while(SDL_PollEvent(&event)) {
	    if (event.type == SDL_WINDOWEVENT) {
	    	switch (event.window.event) {
	    	case SDL_WINDOWEVENT_CLOSE:
	    		quit = true;
	    		break;
	    	default:
	    		break;
	    	}
	    }

		switch(event.type) {
		case SDL_QUIT:
			quit = true;
			break;
		default:
			break;
		} //switch
	} //while

	LOG(info) << "Core_t.updateControls() done";
}


void Core_t::renderLoop() {
	LOG(info) << "Core_t.renderLoop()";

	while(!quit) {
		updateControls();

		renderer->render();

		SDL_GL_SwapWindow(window);
	} //while

	LOG(info) << "Core_t.renderLoop() done";
}
