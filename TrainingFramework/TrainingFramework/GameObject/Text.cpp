#include "../TrainingFramework/stdafx.h"
#include "Text.h"
#include "Font.h"
#include "../TrainingFramework/GameObject/Shaders.h"
#include "../TrainingFramework/GameObject/Camera.h"
#include "../TrainingFramework/GameManager/SceneManager.h"

Text::Text(std::shared_ptr<Shaders> shader, std::shared_ptr<Font> font, std::string text, TextColor color, float size, TextAlign align)
	: m_font(font), m_text(text), m_scale(Vector2(size, size)), m_align(align)
{
	m_pos = Vector3(-1.0f, 1.0f, 1.0f);
	m_shader = shader;
	m_color = EnumToVector(color);
	m_camera = SceneManager::GetInstance()->GetCamera("smth");
	//Init();
}

Text::Text(std::shared_ptr<Shaders> shader, std::shared_ptr<Font> font, std::string text, Vector4 color, float size, TextAlign align)
	: m_font(font), m_text(text), m_scale(Vector2(size, size)), m_align(align)
{
	m_pos = Vector3(-1.0f, 1.0f, 1.0f);
	m_shader = shader;
	m_color = color;
	m_camera = SceneManager::GetInstance()->GetCamera("smth");
	//Init();
}

Text::Text(std::shared_ptr<Shaders> shader, std::shared_ptr<Font> font, std::string text, std::shared_ptr<Texture> texture, float size, TextAlign align)
	: BaseObject(nullptr, texture, shader), m_font(font), m_text(text), m_scale(Vector2(size, size)), m_align(align)
{
	m_pos = Vector3(-1.0f, 1.0f, 1.0f);
	m_camera = SceneManager::GetInstance()->GetCamera("smth");
	//Init();
}

Text::~Text(){}

void Text::Draw()
{
	if (m_camera == nullptr) return;
	GLuint iTempShaderVaribleGLID = -1;

	glUseProgram(m_shader->program);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	GLint positionAttribute = glGetAttribLocation(m_shader->program, "a_posL");
	if (positionAttribute != -1)
	{
		glEnableVertexAttribArray(positionAttribute);
		glVertexAttribPointer(positionAttribute, 4, GL_FLOAT, GL_FALSE, 0, 0);
	}

	GLint uniformColorLocation = glGetUniformLocation(m_shader->program, "u_color");
	//iTempShaderVaribleGLID = m_shader->GetUniformLocation((char*)"u_color");
	if (uniformColorLocation != -1)
		glUniform4fv(uniformColorLocation, 1, &m_color.x);

	/*iTempShaderVaribleGLID = m_shader->GetUniformLocation((char*)"u_texture");*/
	GLint uniformTextureLocation = glGetUniformLocation(m_shader->program, "u_texture");
	if (uniformTextureLocation != -1)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_font->GetFontTextureId());
		glUniform1i(uniformTextureLocation, 0);
	}

	// TODO: implementing text alignment

	float sx = 1.0f / Globals::screenWidth * m_scale.x;
	float sy = 1.0f / Globals::screenHeight * m_scale.y;
	float x = m_pos.x;
	float y = m_pos.y;

	m_vboData.clear();
	for (const char* p = m_text.c_str(); *p; p++)
	{
		GlyphData glyphData;
		if (!m_font->GetGlyphData(*p, &glyphData))
		{
			continue;
		}
		float x2 = x + glyphData.left * sx;
		float y2 = -y - glyphData.top * sy;
		float w = glyphData.width * sx;
		float h = glyphData.height * sy;
		GLfloat box[4][4] = {
			{-1, 1 , glyphData.u0, glyphData.v1},
			{1, 1 ,glyphData.u1, glyphData.v1},
			{-1, -1, glyphData.u0, glyphData.v0},
			{1, -1, glyphData.u1, glyphData.v0},
		};
		m_vboData.push_back(Vertex{ x2, -y2 , glyphData.u0, glyphData.v1 });
		m_vboData.push_back(Vertex{ x2 + w, -y2 , glyphData.u1, glyphData.v1 });
		m_vboData.push_back(Vertex{ x2, -y2 - h, glyphData.u0, glyphData.v0 });
		m_vboData.push_back(Vertex{ x2 + w, -y2 , glyphData.u1, glyphData.v1 });
		m_vboData.push_back(Vertex{ x2, -y2 - h, glyphData.u0, glyphData.v0 });
		m_vboData.push_back(Vertex{ x2 + w, -y2 - h, glyphData.u1, glyphData.v0 });
		x += (glyphData.advanceX >> 6) * sx;
		y += (glyphData.advanceY >> 6) * sy;
	}
	glBufferData(GL_ARRAY_BUFFER, m_vboData.size() * sizeof(Vertex), m_vboData.data(), GL_DYNAMIC_DRAW);
	glDrawArrays(GL_TRIANGLES, 0, m_vboData.size());
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Text::SetFont(std::shared_ptr<Font> font)
{
	m_font = font;
}

void Text::SetText(std::string text) {
	m_text = text;
}

Vector4 Text::EnumToVector(TextColor color)
{
	Vector4 vecColor;
	switch (color)
	{
	case TextColor::BLACK:
		vecColor = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
		break;
	case TextColor::WHITE:
		vecColor = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		break;
	case TextColor::RED:
		vecColor = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		break;
	case TextColor::GREEN:
		vecColor = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		break;
	case TextColor::BLUE:
		vecColor = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		break;
	case TextColor::YELLOW:
		vecColor = Vector4(1.0f, 1.0f, 0.0f, 1.0f);
		break;
	case TextColor::PURPLE:
		vecColor = Vector4(0.5f, 0.0f, 0.5f, 1.0f);
		break;
	case TextColor::CYAN:
		vecColor = Vector4(0.0f, 1.0f, 1.0f, 1.0f);
		break;
	default:
		vecColor = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
		break;
	}
	return vecColor;
}