/* Start Header -------------------------------------------------------

Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:	Main.cpp
Purpose:	Contains the main game loop and game processing.
Inspiration: http://www.retrogames.cz/play_213-Atari2600.php
Language:	C++
Platform:	Windows, MS C++ compiler, VS v140
Project:	jcoleman_CS529_maincpp
Author:		Jay Coleman j.coleman 60000217
Creation date: 10/19/2017

- End Header --------------------------------------------------------*/

#include <SDL.h>
#include <glew.h>
#include <freeglut.h>
#include "stdio.h"
#include "Main.h"
#include "MathLibraries\Vector2D.h"
#include "PhysicsManager.h"
#include <SDL_surface.h>
#include <Windows.h>
#include <vector>
#include <fstream>
#include <iostream>
#include "json.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "MathLibraries\Matrix2D.h"


#include "GameObjectManager.h"
#include "Components\Transform.h"
#include "Components\Sprite.h"


bool debugMode = false;
InputManager * inputManager = new InputManager(1, 'k');

FILE _iob[] = { *stdin, *stdout, *stderr };

extern "C" FILE * __cdecl __iob_func(void)
{
	return _iob;
}

#pragma comment(lib, "legacy_stdio_definitions.lib")

#define WINDOW_TITLE_PREFIX "Combat Game Engine"

float FRAME_TIME_CAP = (1.0f / 60.0f) * 1000.0f;

int CurrentWidth = 800,
CurrentHeight = 800,
WindowHandle = 0;



unsigned FrameCount = 0;

GLuint
VertexShaderId,
FragmentShaderId,
ProgramId,
TextProgram,
TextureVertexShaderId,
TextureFragShaderId,
texture_buffer;

GLint atexture_coord;

const char* VertexShader =
"#version 400\n\
	layout(location=0) in vec4 in_Position;\
	layout(location=1) in vec4 in_Color;\
	uniform mat4 modelingMatrix;\
	out vec4 ex_Color;\
	void main(void)\
	{\
	  gl_Position = modelingMatrix*in_Position;\
	  ex_Color = in_Color;\
	}";

const GLchar* FragmentShader =
{
	"#version 400\n"\

	"in vec4 ex_Color;\n"\
	"out vec4 out_Color;\n"\

	"void main(void)\n"\
	"{\n"\
	"  out_Color = ex_Color;\n"\
	"}\n"
};

const char* VertexShaderTexture =
"#version 400\n\
	layout(location=0) in vec4 in_Position;\
	layout(location=1) in vec4 in_Color;\
attribute vec2 texture_coord;\
	uniform mat4 modelingMatrix;\
	uniform mat4 orthographicMatrix;\
	out vec4 ex_Color;\
out vec2 vtexture_coord;\
	void main(void)\
	{\
	  gl_Position = modelingMatrix*in_Position;\
	  ex_Color = in_Color;\
		vtexture_coord = texture_coord;\
	}";

const GLchar* FragmentShaderTexture =
{
	"#version 400\n"\

	"uniform sampler2D usampler;\n" \
	"in vec2 vtexture_coord;\n"\
	"in vec4 ex_Color;\n"\
	"out vec4 out_Color;\n"\

	"void main(void)\n"\
	"{\n"\
	"vec4 diffuse_color = texture(usampler, vtexture_coord);\n"\
	"  out_Color = diffuse_color;\n"\
	"}\n"
};





void ResizeFunction(int, int);
void RenderFunction(void);

void Cleanup(void);
void CreateShaders(void);
void DestroyShaders(void);
void glOrthog(
	const float &b, const float &t, const float &l, const float &r,
	const float &n, const float &f,
	Matrix2D &M);

int main(int argc, char* args[])
{
	SDL_Window *pWindow;
	SDL_Surface *windowSurface;
	int error = 0;
	bool appIsRunning = true;
	bool gameOver = false;
	bool youWin = false;

	PhysicsManager physics;
	

	GameObjectManager::goManager = new GameObjectManager();
	ResourceManager::resources = new ResourceManager();
	// Initialize SDL
	if((error = SDL_Init( SDL_INIT_VIDEO )) < 0 )
	{
		printf("Couldn't initialize SDL, error %i\n", error);
		return 1;
	}

	//Initialize(argc, args);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

	pWindow = SDL_CreateWindow("Combat Game Engine",		// window title
		SDL_WINDOWPOS_UNDEFINED,					// initial x position
		SDL_WINDOWPOS_UNDEFINED,					// initial y position
		CurrentWidth,										// width, in pixels
		CurrentHeight,										// height, in pixels
		SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN);

	// Check that the window was successfully made
	if (NULL == pWindow)
	{
		// In the event that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	SDL_GLContext context = SDL_GL_CreateContext(pWindow);

	//To create the console
	if (AllocConsole())
	{
		FILE* file;

		freopen_s(&file, "CONOUT$", "wt", stdout);
		freopen_s(&file, "CONOUT$", "wt", stderr);
		freopen_s(&file, "CONOUT$", "wt", stdin);

		//SetConsoleTitle(L"Game Engine Console Input");
	}

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		// Problem: glewInit failed, something is seriously wrong.
		std::cout << "glewInit failed: " << glewGetErrorString(err) << std::endl;
		std::cout << "INFO: OpenGL Version: " <<
			glGetString(GL_VERSION) << std::endl;
	//	exit(1);
	}

	CreateShaders();
	

	FrameRateController * frameRateController = new FrameRateController(FRAME_TIME_CAP);

	

	std::ifstream inputfile("Resources/level.json");

	nlohmann::json j;


	inputfile >> j;
	

	//Load Start Screen
	windowSurface = SDL_GetWindowSurface(pWindow);
	ResourceManager::resources->Draw(windowSurface, NULL, 0);

	//Update the surface
	SDL_UpdateWindowSurface(pWindow);

	//Pause
	while (inputManager->Update())
	{
		if (inputManager->isP1Action2Pressed())
			debugMode = true;

		if (inputManager->isP1Action1Pressed())
		{
			
			break;
		}
	}

	//Load Level
	GameObjectManager::goManager->LoadLevel(j);
	

	




	// Game loop
#pragma region Game Loop
	while(inputManager->Update())
	{
		glClearColor(0.86f, 0.59f, 0.12f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float dt = frameRateController->getDeltaTime();
		
		//clearing the screen


		//Call Physics Manager Update
		physics.Update(dt);

		//Update all GameObjects
		GameObjectManager::goManager->UpdateAll(dt);

		//update screen
		//ResizeFunction(CurrentWidth, CurrentHeight);
		RenderFunction();
		SDL_GL_SwapWindow(pWindow);

		//wait frames out
		frameRateController->WaitFrames();
		

		if (GameObjectManager::goManager->PlayerDead())
		{
			gameOver = true;
			break;
		}
		if (GameObjectManager::goManager->YouWon())
		{
			youWin = true;
			break;
		}

	}
#pragma endregion Game Loop

	//You Win screen
	if (youWin)
	{
		ResourceManager::resources->Draw(windowSurface, NULL, 1);
		//Update the surface
		SDL_UpdateWindowSurface(pWindow);
		SDL_Delay(5000);
	}

	//Game Over Screen
	if (gameOver)
	{
		ResourceManager::resources->Draw(windowSurface, NULL, 2);
		//Update the surface
		SDL_UpdateWindowSurface(pWindow);
		SDL_Delay(5000);
	}

	//Delete all GameObjects
	delete GameObjectManager::goManager;
	delete ResourceManager::resources;
	// Close if opened
	delete frameRateController;
	delete inputManager;
	Cleanup();


	// Close and destroy the window
	SDL_DestroyWindow(pWindow);

	// Quit SDL subsystems
	SDL_Quit();

	return 0;
}





	void ResizeFunction(int Width, int Height)
	{
		CurrentWidth = Width;
		CurrentHeight = Height;
		glViewport(0, 0, CurrentWidth, CurrentHeight);
	}

	void RenderFunction(void)
	{
		

		Matrix2D orthoMatrix;

		glOrthog(static_cast<float>(CurrentHeight), 0.0f, 0.0f, static_cast<float>(CurrentWidth), 0.1f, 1000.0f, orthoMatrix);

		for (auto gameObject : GameObjectManager::goManager->objects) {
			Sprite* pSprite = static_cast<Sprite*>(gameObject->getComponent(SPRITE));

			if (pSprite) {
				Transform * pTransform = static_cast<Transform *>(pSprite->GetOwner()->getComponent(TRANSFORM));
				
				if (pSprite->skin)
				{
					glUseProgram(TextProgram);
					glUniformMatrix4fv(glGetUniformLocation(TextProgram, "modelingMatrix"), 1, true, &pTransform->modelingMatrix.m[0][0]);
					atexture_coord = glGetAttribLocation(TextProgram, "texture_coord");
					glVertexAttribPointer(atexture_coord, 2, GL_FLOAT, false, 0, 0);
					glEnableVertexAttribArray(atexture_coord);

					// select the texture to use
					glBindTexture(GL_TEXTURE_2D, texture_buffer);
					glAlphaFunc(GL_GREATER, 0.5f);
					glEnable(GL_ALPHA_TEST);

					glEnableVertexAttribArray(0);
					glBindVertexArray(pSprite->VboId);
					glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);

					glEnableVertexAttribArray(atexture_coord);
					glVertexAttribPointer(atexture_coord, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(4*sizeof(GLfloat)));

					glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);
					
					glBindVertexArray(0);
				}
				else
				{
					glUseProgram(ProgramId);
					
					glUniformMatrix4fv(glGetUniformLocation(ProgramId, "modelingMatrix"), 1, true, &pTransform->modelingMatrix.m[0][0]);
					pSprite->Draw();
				}
			}
		}
	}

	// set the OpenGL orthographic projection matrix
	void glOrthog(
		const float &b, const float &t, const float &l, const float &r,
		const float &n, const float &f,
		Matrix2D &M)
	{
		// set OpenGL perspective projection matrix
		M.m[0][0] = 2 / (r - l);
		M.m[0][1] = 0;
		M.m[0][2] = 0;
		M.m[0][3] = 0;

		M.m[1][0] = 0;
		M.m[1][1] = 2 / (t - b);
		M.m[1][2] = 0;
		M.m[1][3] = 0;

		M.m[2][0] = 0;
		M.m[2][1] = 0;
		M.m[2][2] = -2 / (f - n);
		M.m[2][3] = 0;

		M.m[3][0] = -(r + l) / (r - l);
		M.m[3][1] = -(t + b) / (t - b);
		M.m[3][2] = -(f + n) / (f - n);
		M.m[3][3] = 1;
	}



	void Cleanup(void)
	{
		DestroyShaders();
	}

	

	

	void CreateShaders(void)
	{
		GLenum ErrorCheckValue = glGetError();

		VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(VertexShaderId, 1, &VertexShader, NULL);
		glCompileShader(VertexShaderId);

		FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(FragmentShaderId, 1, &FragmentShader, NULL);
		glCompileShader(FragmentShaderId);

		ProgramId = glCreateProgram();
		glAttachShader(ProgramId, VertexShaderId);
		glAttachShader(ProgramId, FragmentShaderId);
		glLinkProgram(ProgramId);
		glUseProgram(ProgramId);

		ErrorCheckValue = glGetError();
		if (ErrorCheckValue != GL_NO_ERROR)
		{
			

		//	exit(-1);
		}

		//Area to load image for texture
		int x, y, n;
		unsigned char* data = stbi_load("Resources/tankSprite.png", &x, &y, &n, STBI_rgb_alpha);
		glGenTextures(1, &texture_buffer);
		glBindTexture(GL_TEXTURE_2D, texture_buffer);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		stbi_image_free(data);

		//Texture coordinates
		GLfloat texTop = 0.f;
		GLfloat texBottom = (GLfloat)y;
		GLfloat texLeft = 0.f;
		GLfloat texRight = (GLfloat)x;



		TextureVertexShaderId = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(TextureVertexShaderId, 1, &VertexShaderTexture, NULL);
		glCompileShader(TextureVertexShaderId);

		TextureFragShaderId = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(TextureFragShaderId, 1, &FragmentShaderTexture, NULL);
		glCompileShader(TextureFragShaderId);

		TextProgram = glCreateProgram();
		glAttachShader(TextProgram, TextureVertexShaderId);
		glAttachShader(TextProgram, TextureFragShaderId);
		glLinkProgram(TextProgram);


		
	}

	void DestroyShaders(void)
	{
		GLenum ErrorCheckValue = glGetError();

		glDeleteTextures(1, &texture_buffer);

		glUseProgram(0);

		glDetachShader(ProgramId, VertexShaderId);
		glDetachShader(ProgramId, FragmentShaderId);

		glDeleteShader(FragmentShaderId);
		glDeleteShader(VertexShaderId);

		glDeleteProgram(ProgramId);

		glDetachShader(TextProgram, TextureVertexShaderId);
		glDetachShader(TextProgram, TextureFragShaderId);

		glDeleteShader(TextureFragShaderId);
		glDeleteShader(TextureVertexShaderId);

		glDeleteProgram(TextProgram);

		ErrorCheckValue = glGetError();
		if (ErrorCheckValue != GL_NO_ERROR)
		{
			

			exit(-1);
		}
	}