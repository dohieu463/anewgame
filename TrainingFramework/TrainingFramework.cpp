// TrainingFramework.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include "Camera.h"
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include "Object.h"
#include "Model.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include <memory>

int KeyPressed = 0;
std::vector<std::shared_ptr<Object>> objects;
std::shared_ptr<Camera> camera;

int Init ( ESContext *esContext ) {
	glClearColor ( 1.0f, 1.0f, 1.0f, 1.0f );
	ResourceManager::GetInstance()->LoadResource("../Resources/RM.txt");

	// Khởi tạo SceneManager và Load scene từ file
	SceneManager::GetInstance()->LoadScene("../Resources/SM.txt");

	// Truy cập danh sách các đối tượng từ SceneManager
	objects = SceneManager::GetInstance()->GetObjects();
	
	camera = SceneManager::GetInstance()->GetCamera();
	
	for (const auto& object : objects)
	{
		object->SetCamera(camera);
	}
	
	return 0;
}

void Draw ( ESContext *esContext ) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (const auto& object : objects) {
		object->Draw();
	}
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void Update ( ESContext *esContext, float deltaTime ) {
	for (const auto& object : objects) {
		if (KeyPressed & 1) {
			object->Update(deltaTime, 1);
		}

		if (KeyPressed & (1 << 1)) {
			object->Update(deltaTime, 2);
		}

		if (KeyPressed & (1 << 2)) {
			object->Update(deltaTime, 3);
		}

		if (KeyPressed & (1 << 3)) {
			object->Update(deltaTime, 4);
		}

		if (KeyPressed & (1 << 4)) {
			object->Update(deltaTime, 5);
		}

		if (KeyPressed & (1 << 5)) {
			object->Update(deltaTime, 6);
		}

		if (KeyPressed & (1 << 6)) {
			object->Update(deltaTime, 7);
		}

		if (KeyPressed & (1 << 7)) {
			object->Update(deltaTime, 8);
		}
	}
}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed) {
	if (bIsPressed) {
		switch (key) {
		case KEY_UP:
			KeyPressed |= 1;
			break;

		case KEY_DOWN:
			KeyPressed |= 1 << 1;
			break;

		case KEY_LEFT:
			KeyPressed |= 1 << 2;
			break;

		case KEY_RIGHT:
			KeyPressed |= 1 << 3;
			break;
		
		case KEY_MOVE_FORWARD:
			KeyPressed |= 1 << 4;
			break;

		case KEY_MOVE_BACKWARD:
			KeyPressed |= 1 << 5;
			break;

		case KEY_MOVE_LEFT:
			KeyPressed |= 1 << 6;
			break;

		case KEY_MOVE_RIGHT:
			KeyPressed |= 1 << 7;
			break;

		}
	}

	else {
		switch (key) {
		case KEY_UP:
			KeyPressed ^= 1;
			break;

		case KEY_DOWN:
			KeyPressed ^= 1 << 1;
			break;

		case KEY_LEFT:
			KeyPressed ^= 1 << 2;
			break;

		case KEY_RIGHT:
			KeyPressed ^= 1 << 3;
			break;

		case KEY_MOVE_FORWARD:
			KeyPressed ^= 1 << 4;
			break;

		case KEY_MOVE_BACKWARD:
			KeyPressed ^= 1 << 5;
			break;

		case KEY_MOVE_LEFT:
			KeyPressed ^= 1 << 6;
			break;

		case KEY_MOVE_RIGHT:
			KeyPressed ^= 1 << 7;
			break;

		}
	}
}

void CleanUp() {
	//glDeleteBuffers(1, &vboId);
	//glDeleteBuffers(1, &iboId);
}

void MouseClick(ESContext* esContext, int x, int y, bool isPressed) 
{
	
}

void OnMouseMove(ESContext* esContext, GLint x, GLint y) 
{
	
}

int _tmain(int argc, _TCHAR* argv[]) {
	ESContext esContext;

    esInitContext ( &esContext );

	esCreateWindow ( &esContext, "Hello Triangle", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if ( Init ( &esContext ) != 0 )
		return 0;

	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);
	esRegisterMouseFunc(&esContext, MouseClick);
	esRegisterMouseMoveFunc(&esContext, OnMouseMove);

	esMainLoop ( &esContext );

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	//MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}