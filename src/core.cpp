/*
 * core.cpp
 *
 *  Created on: Oct 13, 2014
 *      Author: kenaco
 */

#include <iostream>
#include <iomanip> // setprecision
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
//#include "handler.hpp"

const int WIDTH = 800;
const int HEIGHT = 600;


void Core::updateDelta() {
	actTime = SDL_GetTicks();
	delta = actTime - lastTime;
	lastTime = actTime;
}


void Core::updateControls() {
	LOG(info) << "Core_t.updateControls()";

	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_a:
				break;
			case SDLK_d:
				break;
			case SDLK_w:
				LOG(debug) << "W";
				break;
			case SDLK_s:
				LOG(debug) << "S";
				break;
			case SDLK_q:
				if (event.key.keysym.mod & (KMOD_LCTRL | KMOD_RCTRL))
					quit = true;
				break;
			}
			break;
		case SDL_MOUSEMOTION:
			LOG(debug) << "xrel: " << event.motion.xrel
					   << "yrel: " << event.motion.yrel;
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


void Core::updateFpsLog() {
	float fps = 1000.0 / delta;
	LOG(debug) << "FPS: " << setprecision(3) << fps;
}


Core::Core(): quit(false), actTime(0), lastTime(0), delta(0) {
	LOG(info) << "Core::Core()";

	int error = SDL_Init(SDL_INIT_EVERYTHING);
	if (error < 0) {
		LOG(error) << "SDL init fail";
		throw Exception(SDL_GetError());
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	window = SDL_CreateWindow("Demo",
							  SDL_WINDOWPOS_UNDEFINED,
							  SDL_WINDOWPOS_UNDEFINED,
							  WIDTH,
							  HEIGHT,
							  SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | \
							  SDL_WINDOW_RESIZABLE
							  );
	if (window == NULL) {
		LOG(error) << "Create window fail";
		throw Exception("SDL create window failed!");
	}

	renderer = new Renderer(window, "../assets/shader.vert", "../assets/shader.frag", WIDTH, HEIGHT);
	scene = nullptr;
	v = 1;

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
	LOG(info) << "Core.loadAssets()";

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(fileName,
											 aiProcess_Triangulate |
											 aiProcess_JoinIdenticalVertices |
											 aiProcess_SortByPType); /*|
											 aiProcess_PreTransformVertices);*/
	if (!scene) {
		throw LoadException(importer.GetErrorString());
	}

// !!! TODO !!!
//	this->scene = new Scene(scene);
	this->scene = new FakeScene();
	if (this->scene == nullptr)
		throw Exception("Fail to create instance of Scene.");
	renderer->setScene(this->scene);

	LOG(info) << "Core.loadAssets() done";
}


void Core::renderLoop() {
	LOG(info) << "Core_t.renderLoop()";

	while(!quit) {
		updateDelta();
		updateFpsLog();
		updateControls();

		renderer->render();

		SDL_GL_SwapWindow(window);
	} //while

	LOG(info) << "Core_t.renderLoop() done";
}
