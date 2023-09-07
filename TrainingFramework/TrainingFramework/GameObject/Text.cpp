#include "../TrainingFramework/stdafx.h"
#include "Text.h"
#include <iostream>

Text::Text()
{
	if(TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
	}
}

Text::~Text()
{
	
}

void Text::Init(std::string path)
{
	font = TTF_OpenFont(path.c_str(), m_Size);
	sFont = TTF_RenderUTF8_Blended(font, m_Text.c_str(), m_Color);

	SDL_Surface* convertedSurface = SDL_CreateRGBSurfaceWithFormat(0, sFont->w, sFont->h, 32, SDL_PIXELFORMAT_RGBA32);
	SDL_BlitSurface(sFont, NULL, convertedSurface, NULL);

	glGenTextures(1, &m_TextTextureID);
	glBindTexture(GL_TEXTURE_2D, m_TextTextureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, )


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, convertedSurface->w, convertedSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, convertedSurface->pixels);


	glBindTexture(GL_TEXTURE_2D, 0);
	m_TextSprite = std::make_shared<BaseObject>(m_TextTextureID);
	m_TextSprite->Set2DPosition(m_Pos);
	m_TextSprite->SetSize(sFont->w,sFont->h);

	SDL_FreeSurface(convertedSurface);
	SDL_FreeSurface(sFont);
	TTF_CloseFont(font);

	TTF_Quit();
}

void Text::Draw()
{
	m_TextSprite->Draw();
}

void Text::Update(float deltaTime)
{

}
