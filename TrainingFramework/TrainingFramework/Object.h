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

	void Draw();
	void Key();
	void Update(GLfloat deltaTime, int typeMove);

	void SetPos(Vector3 pos);
	void SetScale(Vector3 scale);
	void SetRotate(Vector3 rotate);
	void SetCamera(std::shared_ptr<Camera> cameraPtr);
	void SetSize(GLfloat width, GLfloat height);
	void SetObjectID(std::string objectID);
	void SetAlpha(GLfloat alpha);

	std::string GetObjectID();
	
	Matrix CalculateWVP();

private:
	std::string m_objectID;
	std::shared_ptr <Model> m_model;
	std::shared_ptr<Texture> m_texture;
	std::shared_ptr <Shaders> m_shader;
	std::shared_ptr <Camera> m_camera;

	Vector3 m_pos;// = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 m_scale;// = Vector3(1.0f, 1.0f, 1.0f);
	Vector3 m_rotate;// = Vector3(0.0f, 0.0f, 0.0f);

	GLfloat m_alpha;
	GLfloat m_width;
	GLfloat m_height;
};

