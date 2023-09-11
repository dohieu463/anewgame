#pragma once

#include "../TrainingFramework/stdafx.h"
#include <string>
#include <memory>
#include "Object.h"
#include "Shaders.h"
#include "Vertex.h"
#include <SDL.h>
#include <SDL_ttf.h>

class Text : public Object
{
public:
	Text();
	~Text();

	int Init(std::string path);
	void Draw();
	void Update(float deltaTime);
private:

	Vector2 m_Pos;
	std::string m_Text;
	SDL_Color m_Color = SDL_Color({0,0,0,255});
	int m_Size;

	TTF_Font* font = nullptr;
	SDL_Surface* sFont = nullptr;
	GLuint m_TextTextureID;
public:

	Vector2& GetTextPosition() { return m_Pos; }
	std::string& GetTextMessage() { return m_Text; }
	int& GetTextSize() { return m_Size; }
	SDL_Color& GetTextColor() { return m_Color; }
};

