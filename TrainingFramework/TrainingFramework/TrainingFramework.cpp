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
#include "GSMachine.h"
#include "GSBase.h"

int KeyPressed = 0;
std::shared_ptr<Object> object;
int Init ( ESContext *esContext ) {
	esContext->running = true;
	ResourceManager::GetInstance()->LoadResource("../Resources/RM.txt");
	SceneManager::GetInstance()->LoadScene("../Resources/SM.txt");
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	///*
	std::shared_ptr<Camera> m_camera = SceneManager::GetInstance()->GetCamera("smth");
	auto model = ResourceManager::GetInstance()->GetModelPointerByID("0");
	auto texture = ResourceManager::GetInstance()->GetTexturePointerByID("2");
	auto shader = ResourceManager::GetInstance()->GetShaderPointerByID("0");
	
	object = std::make_shared<Object>(model, texture, shader);
	object->SetCamera(m_camera);
	object->SetSize(0.05f, 0.05f);
	
	//object->SetPos(Vector3((float)Globals::screenWidth / 2.0, (float)Globals::screenHeight / 2.0f, 0.0f));
	object->SetPos(Vector3(0.0, 0.0, 0.0));
	//*/
	//GSMachine::GetInstance()->PushState(STATE_INTRO);
	return 0;
}

void Draw ( ESContext *esContext ) {
	glClear(GL_COLOR_BUFFER_BIT);
	/*
	if (GSMachine::GetInstance()->IsRunning())
	{
		GSMachine::GetInstance()->Draw();
	}
	GSMachine::GetInstance()->Draw();
	*/
	object->Draw();
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void Update ( ESContext *esContext, float deltaTime ) {
	/*
	esContext->running = GSMachine::GetInstance()->IsRunning();
	//HandleEnvent(deltaTime);
	if (esContext->running)
	{
		GSMachine::GetInstance()->PerformStateChange();
		GSMachine::GetInstance()->Update(deltaTime);
	}
	*/
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
	ResourceManager::FreeInstance();
	SceneManager::FreeInstance();
	GSMachine::FreeInstance();
}

void MouseClick(ESContext* esContext, int x, int y, bool isPressed) 
{
	printf("%d %d\n", x, y);
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


/*
for (const auto& object : objects) {
	if (KeyPressed & 1) {
		object.second->Update(deltaTime, 1);
	}

	if (KeyPressed & (1 << 1)) {
		object.second->Update(deltaTime, 2);
	}

	if (KeyPressed & (1 << 2)) {
		object.second->Update(deltaTime, 3);
	}

	if (KeyPressed & (1 << 3)) {
		object.second->Update(deltaTime, 4);
	}

	if (KeyPressed & (1 << 4)) {
		object.second->Update(deltaTime, 5);
	}

	if (KeyPressed & (1 << 5)) {
		object.second->Update(deltaTime, 6);
	}

	if (KeyPressed & (1 << 6)) {
		object.second->Update(deltaTime, 7);
	}

	if (KeyPressed & (1 << 7)) {
		object.second->Update(deltaTime, 8);
	}
}
*/