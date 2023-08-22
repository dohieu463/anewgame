#pragma once
#include<GLES2/gl2.h>

class Model {

	public:
		Model();
		~Model();
		Model(const char* strModelFileName);

		GLuint getVboId();
		GLuint getIboId();
		GLuint getNumIndices();

	private:
		GLuint m_vboId;
		GLuint m_iboId;
		GLuint m_numIndices;
};

