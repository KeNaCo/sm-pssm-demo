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

#include "log.hpp"
#include "core.hpp"
#include "renderer.hpp"
#include "exceptions.hpp"
#include "scene.hpp"

const int WIDTH = 800;
const int HEIGHT = 600;

Core::Core(): quit(false) {
	LOG(info) << "Core::Core()";

	int error = SDL_Init(SDL_INIT_EVERYTHING);
	if (error < 0)
		throw Exception(SDL_GetError());

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	window = SDL_CreateWindow("Demo",
							  SDL_WINDOWPOS_UNDEFINED,
							  SDL_WINDOWPOS_UNDEFINED,
							  WIDTH,
							  HEIGHT,
							  SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | \
							  SDL_WINDOW_RESIZABLE
							  );
	renderer = new Renderer(window);
	scene = nullptr;

	LOG(info) << "Core::Core() done";
}


Core::Core(std::string filename): Core() {
	loadAssets(filename);
}


Core::~Core() {
	LOG(info) << "Core::~Core()";

	delete scene;
	delete renderer;

	SDL_DestroyWindow(window);

	LOG(info) << "Core::~Core() done";
}


void Core::loadAssets(std::string fileName) {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(fileName,
											 aiProcess_Triangulate |
											 aiProcess_JoinIdenticalVertices |
											 aiProcess_SortByPType |
											 aiProcess_PreTransformVertices);
	if (!scene) {
		throw LoadException(importer.GetErrorString());
	}

	this->scene = new Scene(scene);
	renderer->setScene(this->scene);
}


void Core::updateControls() {
	LOG(info) << "Core_t.updateControls()";

	Camera* camera = renderer->getActiveCamera();

	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_a:
//				camera->moveX(false);
				break;
			case SDLK_d:
//				camera->moveX(true);
				break;
			case SDLK_w:
				camera->moveForward();
				break;
			case SDLK_s:
				camera->moveY(false);
			default:
				break;
			}
			break;
	    case SDL_WINDOWEVENT_CLOSE:
    		quit = true;
    		break;
		case SDL_QUIT:
			quit = true;
			break;
		default:
			break;
		} //switch
	} //while

	LOG(info) << "Core_t.updateControls() done";
}


void Core::renderLoop() {
	LOG(info) << "Core_t.renderLoop()";

	while(!quit) {
		updateControls();

		renderer->render();

		SDL_GL_SwapWindow(window);
	} //while

	LOG(info) << "Core_t.renderLoop() done";
}
