//#include "../TrainingFramework/stdafx.h"
//#include "Text.h"
//#include <iostream>
//
//Text::Text()
//{
//	if(TTF_Init() == -1)
//	{
//		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
//	}
//}
//
//Text::~Text()
//{
//	
//}
//
//void Text::Init(std::string path)
//{
//	font = TTF_OpenFont(path.c_str(), m_Size);
//	sFont = TTF_RenderUTF8_Blended(font, m_Text.c_str(), m_Color);
//
//	SDL_Surface* convertedSurface = SDL_CreateRGBSurfaceWithFormat(0, sFont->w, sFont->h, 32, SDL_PIXELFORMAT_RGBA32);
//	SDL_BlitSurface(sFont, NULL, convertedSurface, NULL);
//
//	glGenTextures(1, &m_TextTextureID);
//	glBindTexture(GL_TEXTURE_2D, m_TextTextureID);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	//glTexParameteri(GL_TEXTURE_2D, )
//
//
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, convertedSurface->w, convertedSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, convertedSurface->pixels);
//
//
//	glBindTexture(GL_TEXTURE_2D, 0);
//	m_TextSprite = std::make_shared<Object>();
//	m_TextSprite->Set2DPosV(m_Pos);
//	m_TextSprite->SetSize(sFont->w,sFont->h);
//
//	SDL_FreeSurface(convertedSurface);
//	SDL_FreeSurface(sFont);
//	TTF_CloseFont(font);
//
//	TTF_Quit();
//}
//
//void Text::Draw()
//{
//	m_TextSprite->Draw();
//}
//
//void Text::Update(float deltaTime)
//{
//
//}
#include "../TrainingFramework/stdafx.h"
#include "Text.h"
#include <iostream>

Text::Text()
{
    m_Pos = Vector2(0.0f, 0.0f);
    m_Text = "DefaultText";
    m_Color = { 255, 0, 0, 255 };
    m_Size = 24; // Kích thước mặc định

    if (TTF_Init() == -1)
    {
        std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
    }
}

Text::~Text()
{
    TTF_Quit();
}

void Text::Init(std::string path)
{
    // Load font từ đường dẫn và kích thước
    font = TTF_OpenFont(path.c_str(), m_Size);
    if (!font)
    {
        std::cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return;
    }

    // Tạo SDL_Surface chứa văn bản
    sFont = TTF_RenderText_Solid(font, m_Text.c_str(), m_Color);
    if (!sFont)
    {
        std::cout << "Failed to render text! SDL_ttf Error: " << TTF_GetError() << std::endl;
        TTF_CloseFont(font);
        return;
    }

    // Chuyển đổi SDL_Surface thành texture (sử dụng OpenGL)
    glGenTextures(1, &m_TextTextureID);
    glBindTexture(GL_TEXTURE_2D, m_TextTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sFont->w, sFont->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, sFont->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Giải phóng bộ nhớ của SDL_Surface
    SDL_FreeSurface(sFont);

    // Đóng font sau khi đã tạo texture
    TTF_CloseFont(font);
}

void Text::Draw()
{
    if (m_TextTextureID == 0)
    {
        // Texture chưa được khởi tạo, không thể vẽ
        return;
    }

    // Bật chế độ sử dụng blending để hỗ trợ vẽ đối tượng có độ trong suốt
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Sử dụng texture của văn bản
    glBindTexture(GL_TEXTURE_2D, m_TextTextureID);

    // Tạo một VAO để lưu trữ dữ liệu vị trí và texture coordinates
   /* GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);*/

    // Tạo một VBO để lưu trữ dữ liệu vị trí và texture coordinates
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Định nghĩa dữ liệu vị trí và texture coordinates
    GLfloat vertices[] = {
        0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Định nghĩa cách sử dụng dữ liệu vị trí và texture coordinates
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

    // Vẽ đối tượng bằng VAO và VBO
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // Giải phóng VAO và VBO
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    //glBindVertexArray(0);
    glDeleteBuffers(1, &vbo);
    //glDeleteVertexArrays(1, &vao);

    // Kết thúc vẽ đối tượng
    glBindTexture(GL_TEXTURE_2D, 0);

    // Vô hiệu hóa chế độ blending sau khi đã vẽ xong
    glDisable(GL_BLEND);
}


void Text::Update(float deltaTime)
{
    // Có thể thêm logic cập nhật vị trí, màu sắc, văn bản, hoặc kích thước ở đây nếu cần
}

