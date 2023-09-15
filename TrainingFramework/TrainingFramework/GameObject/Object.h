#pragma once
#include "Model.h"
#include "Texture.h"
#include "Shaders.h"
#include "Camera.h"
#include <memory>
#include <vector>
#include <string>

class Object {

public:
	Object();
	~Object();

	Object(
		std::shared_ptr<Model> modelPtr,
		std::shared_ptr<Texture> texturePtr,
		std::shared_ptr<Shaders> shaderPtr
	);

	Object(
		const char* modelName,
		const char* textureName,
		const char* shaderName
	);

	void Draw();
	void Key();
	void Update(GLfloat deltaTime);

	void SetPos(Vector3 pos);
	void SetScale(Vector3 scale);
	void SetRotate(Vector3 rotate);
	void SetCamera(std::shared_ptr<Camera> cameraPtr);
	void SetSize(GLfloat width, GLfloat height);
	void SetObjectID(std::string objectID);
	void SetAlpha(GLfloat alpha);
	void Set2DPos(GLfloat x, GLfloat y);
	void Set2DPosV(Vector2 m_Pos);
	Vector2 GetPos() { return Vector2(m_pos.x, m_pos.y); }

	std::string GetObjectID();
	
	Matrix CalculateWVP();

protected:
	std::string m_objectID;
	std::shared_ptr <Model> m_model;
	std::shared_ptr<Texture> m_texture;
	std::shared_ptr <Shaders> m_shader;
	std::shared_ptr <Camera> m_camera;

	Vector3 m_pos;
	Vector3 m_scale;
	Vector3 m_rotate;

	GLfloat m_alpha;
	GLfloat m_width;
	GLfloat m_height;
};

