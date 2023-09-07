#pragma once

#include "../TrainingFramework/stdafx.h"
#include <string>
#include <memory>
#include "BaseObject.h"
#include "Shaders.h"
#include "SDL_ttf.h"
/*
 *first set : text pos
 *			  text size
 *			  text color
 *			  text message
 *then call init(std::string path);
*/

class Text 
{
public:
	Text();
	~Text();

	void Init(std::string path);
	void Draw();
	void Update(float deltaTime);
private:

	Vector2 m_Pos;
	std::string m_Text ;
	SDL_Color m_Color = SDL_Color({255,0,0,255});
	int m_Size;

	std::shared_ptr<Shaders> m_Shader;
	TTF_Font* font;
	SDL_Surface* sFont;
	GLuint m_TextTextureID;
	std::shared_ptr<BaseObject> m_TextSprite;


public:

	Vector2& GetTextPosition() { return m_Pos; }
	std::string& GetTextMessage() { return m_Text; }
	int& GetTextSize() { return m_Size; }
	SDL_Color& GetTextColor() { return m_Color; }
};

