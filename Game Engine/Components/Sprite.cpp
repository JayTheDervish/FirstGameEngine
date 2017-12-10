/* Start Header -------------------------------------------------------

Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:	Sprite.h
Purpose:	Contains the definition for the Sprite class.
Language:	C++
Platform:	Windows, MS C++ compiler, VS v140
Project:	jcoleman_CS529_spritecpp
Author:		Jay Coleman j.coleman 60000217
Creation date: 10/26/2017

- End Header --------------------------------------------------------*/

#include "Sprite.h"
#include "GameObject.h"

Sprite::Sprite(SDL_Surface * sprite)
{
	surface = sprite;
	CreateVBO();

	skin = false;
}

Sprite::~Sprite()
{
	DestroyVBO();
}

void Sprite::Initialize(GameObject * parent)
{
	//this->Transform = GetOwner()->has(Transform);
	daddy = parent;
}

void Sprite::Update(float dt)
{
}


void Sprite::Draw() 
{
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glBindVertexArray(0);
}

void Sprite::Serialize(nlohmann::json j)
{
}

void Sprite::HandleEvents(EventType events)
{
}

GameObject * Sprite::GetOwner()
{
	return daddy;
}

void Sprite::CreateVBO(void)
{
	GLfloat Vertices[] = {
		-0.5f, -0.5f, -1.0f, 1.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -1.0f, 1.0f, 1.0f, 1.0f,
		0.5f,  0.5f, -1.0f, 1.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, -1.0f, 1.0f, 0.0f, 0.0f
	};

	GLuint indexData[] = { 0,1,2,3 };

	GLfloat Colors[] = {
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,

		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f
	};

	GLenum ErrorCheckValue = glGetError();

	glGenBuffers(1, &VaoId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER ,VaoId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData, GL_STATIC_DRAW);

	glGenBuffers(1, &VboId);
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);


	//glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	//glEnableVertexAttribArray(0);

	//glGenBuffers(1, &ColorBufferId);
	//glBindBuffer(GL_ARRAY_BUFFER, ColorBufferId);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
	//glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
	//glEnableVertexAttribArray(1);

	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
	}




}

void Sprite::DestroyVBO(void)
{
	GLenum ErrorCheckValue = glGetError();

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &ColorBufferId);
	glDeleteBuffers(1, &VboId);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);

	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{


		exit(-1);
	}
}