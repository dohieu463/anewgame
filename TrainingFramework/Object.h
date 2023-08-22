#pragma once
#include "Model.h"
#include "Texture.h"
#include "Shaders.h"
#include "Camera.h"
#include <memory>
#include <vector>
class Object {

public:
	Object();
	~Object();

	bool Init(
		int objectId, 
		std::shared_ptr<Model> modelPtr, 
		std::vector<std::shared_ptr<Texture>> textureVector, 
		std::shared_ptr<Shaders> shaderPtr
	);

	void Draw();
	void Key();
	void Update(GLfloat deltaTime, int typeMove);
	void SetPos(Vector3 pos);
	void SetScale(Vector3 scale);
	void SetRotate(Vector3 rotate);
	void SetCamera(std::shared_ptr<Camera> cameraPtr);

	//void Move(GLfloat deltaTime, int typeMove);
	//void Rotate(GLfloat deltaTime, int typeMove);

	int GetObjectID();
	
	Matrix CalculateWVP();

private:
	int m_objectId;
	std::shared_ptr <Model> m_model;
	std::vector<std::shared_ptr<Texture>> m_textureVector;
	std::shared_ptr <Shaders> m_shader;
	std::shared_ptr <Camera> m_camera;

	Vector3 m_pos = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 m_scale = Vector3(1.0f, 1.0f, 1.0f);
	Vector3 m_rotate = Vector3(0.0f, 0.0f, 0.0f);
};

