/* Start Header -------------------------------------------------------

Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:	Main.cpp
Purpose:	Contains the main game loop and game processing.
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
#include "InputManager.h"
#include "ResourceManager.h"
#include "FrameRateController.h"
#include "GameObjectManager.h"
#include "MathLibraries\Vector2D.h"
#include <SDL_surface.h>
#include <Windows.h>
#include <vector>
#include <fstream>
#include <iostream>
#include "json.hpp"

FILE _iob[] = { *stdin, *stdout, *stderr };

extern "C" FILE * __cdecl __iob_func(void)
{
	return _iob;
}

#pragma comment(lib, "legacy_stdio_definitions.lib")

#define WINDOW_TITLE_PREFIX "Combat Game Engine"

float FRAME_TIME_CAP = (1.0f / 60.0f) * 1000.0f;

int CurrentWidth = 800,
CurrentHeight = 600,
WindowHandle = 0;

unsigned FrameCount = 0;

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
ColorBufferId;

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
	"vec3 diffuse_color = texture(usampler, vtexture_coord).xyz;\n"\
	"  out_Color = vec4(diffuse_color, 1);\n"\
	"}\n"
};

// read a 24-bit color bitmap image file
//   Note: caller is responsible for deallocating the
//         RGB data
unsigned char* loadBitmapFile(const char *fname, int *width, int *height) {
	std::fstream in(fname, std::ios_base::in | std::ios_base::binary);
	char header[38];
	in.read(header, 38);
	unsigned offset = *reinterpret_cast<unsigned*>(header + 10);
	int W = *reinterpret_cast<int*>(header + 18),
		H = *reinterpret_cast<int*>(header + 22),
		S = 3 * W;
	S += (4 - S % 4) % 4;
	int size = S*H;
	in.seekg(offset, std::ios_base::beg);
	unsigned char *data = new unsigned char[size];
	in.read(reinterpret_cast<char*>(data), size);
	if (!in) {
		delete[] data;
		return 0;
	}

	for (int j = 0; j < H; ++j) {
		for (int i = 0; i < W; ++i) {
			int index = S*j + 3 * i;
			std::swap(data[index + 0], data[index + 2]);
		}
	}

	*width = W;
	*height = H;
	return data;
}


InputManager * inputManager = new InputManager(1, 'k');
ResourceManager resources;
GameObjectManager * goManager = new GameObjectManager();

//TODO: Put in Renderer
void Initialize(int, char*[]);
//void InitWindow(int, char*[]);
void ResizeFunction(int, int);
void RenderFunction(void);
void TimerFunction(int);
void IdleFunction(void);

void Cleanup(void);
void CreateVBO(void);
void DestroyVBO(void);
void CreateShaders(void);
void DestroyShaders(void);

int main(int argc, char* args[])
{
	SDL_Window *pWindow;
	int error = 0;
	bool appIsRunning = true;




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

//	SDL_Surface * pWindowSurface = SDL_GetWindowSurface(pWindow);

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
	CreateVBO();
	glClearColor(0.86f, 0.59f, 0.12f, 1.0f);

	FrameRateController * frameRateController = new FrameRateController(FRAME_TIME_CAP);

	

	std::ifstream inputfile("Resources/level.json");

	nlohmann::json j;

	

	inputfile >> j;
	

	//Load Level
	goManager->LoadLevel(j);


	// Game loop
#pragma region Game Loop
	while(true == appIsRunning)
	{
		

		float dt = frameRateController->getDeltaTime();
		
		//clearing the screen
//		SDL_FillRect(pWindowSurface, NULL, 0);


		SDL_Event e;
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				appIsRunning = false;
			}

		}

		//Update all GameObjects
		goManager->UpdateAll(dt);

		//update screen buffer

		
		for (auto go : goManager->objects)
		{
			SDL_Rect * rect = new SDL_Rect();
			
			Transform * pTransform = (Transform *)go->getComponent(TRANSFORM);
			Sprite * pSprite = (Sprite *)go->getComponent(SPRITE);

			if (pTransform && pSprite) {
				rect->x = pTransform->postion2d.x;
				rect->y = pTransform->postion2d.y;

				rect->h = pSprite->surface->h;
				rect->w = pSprite->surface->w;

			//	SDL_BlitSurface(pSprite->surface, NULL, pWindowSurface, rect);
			}
		}


		//update screen
		ResizeFunction(CurrentWidth, CurrentHeight);
		RenderFunction();
		SDL_GL_SwapWindow(pWindow);

		//wait frames out
		frameRateController->WaitFrames();
		
	}
#pragma endregion Game Loop


	//Delete all GameObjects
	delete goManager;

	// Close if opened
	delete frameRateController;
	delete inputManager;
	Cleanup();

	// Close and destroy the window
	SDL_DestroyWindow(pWindow);

	// Quit SDL subsystems
	SDL_Quit();
	
	exit(EXIT_SUCCESS);

	return 0;
}


void Initialize(int argc, char* argv[])
{

	fprintf(
		stdout,
		"INFO: OpenGL Version: %s\n",
		glGetString(GL_VERSION)
	);


	CreateShaders();
	CreateVBO();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}


	void ResizeFunction(int Width, int Height)
	{
		CurrentWidth = Width;
		CurrentHeight = Height;
		glViewport(0, 0, CurrentWidth, CurrentHeight);
	}

	void RenderFunction(void)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (auto gameObject : goManager->objects) {
			Transform* pTransform = static_cast<Transform*>(gameObject->getComponent(TRANSFORM));

			if (pTransform && !pTransform->skin) {
				glUseProgram(ProgramId);
				glUniformMatrix4fv(glGetUniformLocation(ProgramId, "modelingMatrix"), 1, true, (float*)&pTransform->modelingMatrix.m[0][0]);
			}
			else if (pTransform && pTransform->skin) {
				glUseProgram(TextProgram);
				glUniformMatrix4fv(glGetUniformLocation(TextProgram, "modelingMatrix"), 1, true, (float*)&pTransform->modelingMatrix.m[0][0]);
			}


			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
	}

	void IdleFunction(void)
	{
		glutPostRedisplay();
	}

	void TimerFunction(int Value)
	{
		if (0 != Value) {
			char* TempString = (char*)
				malloc(512 + strlen(WINDOW_TITLE_PREFIX));

			sprintf(
				TempString,
				"%s: %d Frames Per Second @ %d x %d",
				WINDOW_TITLE_PREFIX,
				FrameCount * 4,
				CurrentWidth,
				CurrentHeight
			);

			glutSetWindowTitle(TempString);
			free(TempString);
		}

		FrameCount = 0;
		glutTimerFunc(250, TimerFunction, 1);
	}

	void Cleanup(void)
	{
		DestroyShaders();
		DestroyVBO();
	}

	void CreateVBO(void)
	{
		GLfloat Vertices[] = {
			-0.8f, 0.8f, 0.0f, 1.0f,
			0.8f, 0.8f, 0.0f, 1.0f,
			-0.8f, -0.8f, 0.0f, 1.0f,

			-0.8f, -0.8f, 0.0f, 1.0f,
			0.8f,  0.8f, 0.0f, 1.0f,
			0.8f, -0.8f, 0.0f, 1.0f
		};

		GLfloat Colors[] = {
			0.0f, 0.0f, 1.0f, 1.0f,
			0.0f, 0.0f, 1.0f, 1.0f,
			0.0f, 0.0f, 1.0f, 1.0f,

			0.0f, 0.0f, 1.0f, 1.0f,
			0.0f, 0.0f, 1.0f, 1.0f,
			0.0f, 0.0f, 1.0f, 1.0f
		};

		GLenum ErrorCheckValue = glGetError();

		glGenVertexArrays(1, &VaoId);
		glBindVertexArray(VaoId);

		glGenBuffers(1, &VboId);
		glBindBuffer(GL_ARRAY_BUFFER, VboId);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glGenBuffers(1, &ColorBufferId);
		glBindBuffer(GL_ARRAY_BUFFER, ColorBufferId);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		ErrorCheckValue = glGetError();
		if (ErrorCheckValue != GL_NO_ERROR)
		{
			fprintf(
				stderr,
				"ERROR: Could not create a VBO: %s \n",
				gluErrorString(ErrorCheckValue)
			);

		//	exit(-1);
		}
	}

	void DestroyVBO(void)
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
			fprintf(
				stderr,
				"ERROR: Could not destroy the VBO: %s \n",
				gluErrorString(ErrorCheckValue)
			);

			exit(-1);
		}
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
			fprintf(
				stderr,
				"ERROR: Could not create the shaders: %s \n",
				gluErrorString(ErrorCheckValue)
			);

		//	exit(-1);
		}

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
		//glUseProgram(TextProgram);

		int width, height;
		unsigned char *rgbdata = loadBitmapFile("image.bmp", &width, &height);
		glGenTextures(1, &texture_buffer);
		glBindTexture(GL_TEXTURE_2D, texture_buffer);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, rgbdata);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	void DestroyShaders(void)
	{
		GLenum ErrorCheckValue = glGetError();

		glUseProgram(0);

		glDetachShader(ProgramId, VertexShaderId);
		glDetachShader(ProgramId, FragmentShaderId);

		glDeleteShader(FragmentShaderId);
		glDeleteShader(VertexShaderId);

		glDeleteProgram(ProgramId);

		ErrorCheckValue = glGetError();
		if (ErrorCheckValue != GL_NO_ERROR)
		{
			fprintf(
				stderr,
				"ERROR: Could not destroy the shaders: %s \n",
				gluErrorString(ErrorCheckValue)
			);

			exit(-1);
		}
	}