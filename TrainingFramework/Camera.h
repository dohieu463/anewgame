#pragma once
#include "../Utilities/Math.h"
#include <memory>
class Camera {
public:
	Camera();
	Camera(float nearInfo, float farInfo, float fov, float speed);
	~Camera();

	void CalculateWorldMatrix();
	void CalculateViewMatrix();
	void CalculateBasicVector();

	void Move(GLfloat deltaTime, int typeMove);
	void Rotate(GLfloat deltaTime, int typeRotate);
	
	void SetTarget(Vector3 target);
	void SetPosition(Vector3 pos);
	
	Matrix GetWorldMatrix();
	Matrix GetViewMatrix();
	Matrix GetPerspectiveMatrix();
private:
	Matrix m_worldMatrix;
	Matrix m_viewMatrix;
	Matrix m_perspectiveMatrix;
	Vector3 m_basicVector[3];
	Vector3 m_position = Vector3(0.0f, 0.0f, 10.0f);
	Vector3 m_target = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 m_up = Vector3(0.0f, 1.0f, 0.0f);

	float m_fov;
	float m_near = 0.1f;
	float m_far = 1000.0f;
	float m_moveSpeed = 3.0f;
};

