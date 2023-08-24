#pragma once
#include "../Utilities/Math.h"
#include <memory>
#include <string>
class Camera {
public:
	Camera();
	Camera(
		GLfloat fNear, 
		GLfloat fFar, 
		GLfloat fov, 
		GLfloat speed);

	~Camera();

	void CalculateWorldMatrix();
	void CalculateViewMatrix();
	void CalculateBasicVector();

	void Move(GLfloat deltaTime, int typeMove);
	void Rotate(GLfloat deltaTime, int typeRotate);
	
	void SetTarget(Vector3 target);
	void SetPosition(Vector3 pos);
	void SetCameraID(std::string cameraID);
	std::string GetCameraID();
	
	Matrix GetWorldMatrix();
	Matrix GetViewMatrix();
	Matrix GetPerspectiveMatrix();
	Matrix GetProjectMatrix();
private:
	Matrix m_worldMatrix;
	Matrix m_viewMatrix;
	Matrix m_perspectiveMatrix;
	Matrix m_projectMatrix;

	Vector3 m_basicVector[3];
	Vector3 m_position;		// = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 m_target;		// = Vector3(0.0f, 0.0f, -1.0f);
	Vector3 m_up;			// = Vector3(0.0f, 1.0f, 0.0f);

	float m_fov;
	float m_near = 0.1f;
	float m_far = 1000.0f;
	float m_moveSpeed = 3.0f;
	float m_rotateSpeed = 3.0f;
	std::string m_cameraID;
};

/*
Camera(
	Vector3 position,
	Vector3 target,
	Vector3 up,
	GLfloat fov,
	GLfloat fNear,
	GLfloat fFar,
	GLfloat moveSpeed,
	GLfloat rotateSpeed
);

Camera(
	GLfloat fov,
	GLfloat fNear,
	GLfloat fFar,
	GLfloat moveSpeed,
	GLfloat rotateSpeed
);

Camera(
	GLfloat left,
	GLfloat right,
	GLfloat top,
	GLfloat bottom,
	GLfloat fNear,
	GLfloat fFar,
	GLfloat fSpeed
);
*/