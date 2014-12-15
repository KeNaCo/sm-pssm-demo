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

#include "renderer.hpp"
#include "handler.hpp"

/*
 * Controller class
 */
class Core {
private:
	bool quit;

	// Timing
	int actTime;
	int lastTime;
	int delta;

	//Controls
	EventHandler* handler;

	//View classes
	SDL_Window* window;
	Renderer* renderer;

	//Model class
	Scene* scene;


	void updateDelta();
	void updateControls();
	void updateFpsLog();
public:
	Core();
	Core(std::string filename);
	virtual ~Core();

	void loadAssets(std::string fileName);
	void renderLoop();
};

#endif /* CORE_H_ */
