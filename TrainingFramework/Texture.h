#pragma once
#include<GLES2/gl2.h>
class Texture {
	public:
		Texture();
		~Texture();
		Texture(const char* strTextureFileName);
		GLuint getTextureId();
	private:
		GLuint m_textureID;
};

