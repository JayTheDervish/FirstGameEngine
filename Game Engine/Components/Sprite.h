/* Start Header -------------------------------------------------------

Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:	Sprite.h
Purpose:	Contains the declaration for the Sprite class.
Language:	C++
Platform:	Windows, MS C++ compiler, VS v140
Project:	jcoleman_CS529_spriteh
Author:		Jay Coleman j.coleman 60000217
Creation date: 10/26/2017

- End Header --------------------------------------------------------*/
#pragma once

#ifndef Sprite_H
#define Sprite_H

#include <SDL_surface.h>
#include <glew.h>
#include <freeglut.h>
#include "Transform.h"

class GameObject;

class Sprite : public Component
{
public:
	Sprite(SDL_Surface * sprite);
	~Sprite();

	void Initialize(GameObject* parent);

	void Update(float dt);
	void Draw();

	SDL_Surface * surface;

	void Serialize(nlohmann::json j);

	GameObject * GetOwner();

private:
	GameObject * daddy;

	GLuint
		VertexShaderId,
		FragmentShaderId,
		ProgramId,
		TextProgram,
		TextureVertexShaderId,
		TextureFragShaderId,
		VaoId,
		VboId,
		texture_buffer,
		texcoord_buffer,
		atexture_coord,
		ColorBufferId;

	void CreateVBO();

	void DestroyVBO();
};

#endif // !Sprite_H



