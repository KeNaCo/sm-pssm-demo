/*
 * renderer.h
 *
 *  Created on: Oct 16, 2014
 *      Author: kenaco
 */

#ifndef RENDERER_H_
#define RENDERER_H_

#include <SDL.h>
#include <SDL_video.h>
#include <memory>
#include <assimp/scene.h>

class Renderer_t {
private:
	SDL_GLContext gl;
	const aiScene* scene;

public:
	Renderer_t(SDL_Window* window);
	virtual ~Renderer_t();

	void setScene(const aiScene* scene) { this->scene = scene; };
	void render();
};

#endif /* RENDERER_H_ */
