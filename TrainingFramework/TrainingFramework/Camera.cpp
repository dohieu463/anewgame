#include "stdafx.h"
#include "Camera.h"
#include "Globals.h"
#include "../Utilities/Math.h"
#include <memory>

Camera::Camera() 
{
	m_position = Vector3(0.0f, 0.0f, 3.0f);
	m_target = Vector3(0.0f, 0.0f, -1.0f); 
	m_up = Vector3(0.0f, 1.0f, 0.0f); 

	m_moveSpeed = 10.0f;
	m_rotateSpeed = 0.5f;
	m_near = 0.1f;
	m_far = 500.0f;
	m_fov = 1.0f;
	m_projectMatrix.SetPerspective(m_fov, (GLfloat)Globals::screenWidth / Globals::screenHeight, m_near, m_far);

	CalculateWorldMatrix();
	CalculateViewMatrix();
}

Camera::Camera(GLfloat nearInfo, GLfloat farInfo, GLfloat fov, GLfloat speed)
{
	m_position = Vector3(0.0f, 0.0f, 3.0f);
	m_target = Vector3(0.0f, 0.0f, -1.0f);
	m_up = Vector3(0.0f, 1.0f, 0.0f);
	
	m_near = nearInfo;
	m_far = farInfo;
	m_fov = fov;
	m_moveSpeed = speed;
	m_rotateSpeed = speed;

	m_projectMatrix.SetPerspective(1.0f, (GLfloat)Globals::screenWidth / Globals::screenHeight, m_near, m_far);

	CalculateWorldMatrix();
	CalculateViewMatrix();
}

Camera::~Camera() 
{
}

void Camera::CalculateWorldMatrix() 
{
	CalculateBasicVector();
	m_worldMatrix.m[0][0] = m_basicVector[0].x;		m_worldMatrix.m[0][1] = m_basicVector[0].y;		m_worldMatrix.m[0][2] = m_basicVector[0].z;		m_worldMatrix.m[0][3] = 0.0f;
	m_worldMatrix.m[1][0] = m_basicVector[1].x;		m_worldMatrix.m[1][1] = m_basicVector[1].y;		m_worldMatrix.m[1][2] = m_basicVector[1].z;		m_worldMatrix.m[1][3] = 0.0f;
	m_worldMatrix.m[2][0] = m_basicVector[2].x;		m_worldMatrix.m[2][1] = m_basicVector[2].y;		m_worldMatrix.m[2][2] = m_basicVector[2].z;		m_worldMatrix.m[2][3] = 0.0f;
	m_worldMatrix.m[3][0] = m_position.x;			m_worldMatrix.m[3][1] = m_position.y;			m_worldMatrix.m[3][2] = m_position.z;			m_worldMatrix.m[3][3] = 1.0f;
};

void Camera::CalculateViewMatrix() 
{
	CalculateBasicVector();
	m_viewMatrix.m[0][0] = m_basicVector[0].x;	m_viewMatrix.m[0][1] = m_basicVector[1].x;	m_viewMatrix.m[0][2] = m_basicVector[2].x;	m_viewMatrix.m[0][3] = 0.0f;
	m_viewMatrix.m[1][0] = m_basicVector[0].y;	m_viewMatrix.m[1][1] = m_basicVector[1].y;	m_viewMatrix.m[1][2] = m_basicVector[2].y;	m_viewMatrix.m[1][3] = 0.0f;
	m_viewMatrix.m[2][0] = m_basicVector[0].z;	m_viewMatrix.m[2][1] = m_basicVector[1].z;	m_viewMatrix.m[2][2] = m_basicVector[2].z;	m_viewMatrix.m[2][3] = 0.0f;
	m_viewMatrix.m[3][0] = -m_position.Dot(m_basicVector[0]);	m_viewMatrix.m[3][1] = -m_position.Dot(m_basicVector[1]);	m_viewMatrix.m[3][2] = -m_position.Dot(m_basicVector[2]);	m_viewMatrix.m[3][3] = 1.0f;
};

void Camera::CalculateBasicVector() 
{
	Vector3 z_axis = (m_position - m_target).Normalize();
	Vector3 x_axis = (m_up.Cross(z_axis)).Normalize();
	Vector3 y_axis = (z_axis.Cross(x_axis)).Normalize();
	m_basicVector[0] = x_axis;
	m_basicVector[1] = y_axis;
	m_basicVector[2] = z_axis;
};

void Camera::Move(GLfloat deltaTime, int typeMove) 
{
	CalculateBasicVector();
	Vector3 deltaMove;
	switch (typeMove)
	{
	case 1: //Forward
		deltaMove = -m_basicVector[2] * deltaTime * m_moveSpeed;
		break;
	case 2: //Backward
		deltaMove = m_basicVector[2] * deltaTime * m_moveSpeed;
		break;
	case 3: //Left
		deltaMove = -m_basicVector[0] * deltaTime * m_moveSpeed;
		break;
	case 4: //Right
		deltaMove = m_basicVector[0] * deltaTime * m_moveSpeed;
		break;
	default:
		break;
	}
	m_position += deltaMove;
	m_target += deltaMove;

	CalculateWorldMatrix();
	CalculateViewMatrix();
};

void Camera::Rotate(GLfloat deltaTime, int typeRotate) 
{
	Vector4 localTarget = Vector4(0, 0, -(m_position - m_target).Length(), 1);
	Vector4 localNewTarget;
	Vector4 worldNewTarget;
	Matrix rotationMatrix;
	switch (typeRotate)
	{
	case 1: //Up
		rotationMatrix.SetRotationX(deltaTime * m_rotateSpeed);
		localNewTarget = localTarget * rotationMatrix;
		worldNewTarget = localNewTarget * m_worldMatrix;
		// Update m_target with the new target expressed in world coordinates
		m_target = Vector3(worldNewTarget.x, worldNewTarget.y, worldNewTarget.z);

		break;
	case 2: //Down
		rotationMatrix.SetRotationX(-deltaTime * m_rotateSpeed);
		localNewTarget = localTarget * rotationMatrix;
		worldNewTarget = localNewTarget * m_worldMatrix;
		// Update m_target with the new target expressed in world coordinates
		m_target = Vector3(worldNewTarget.x, worldNewTarget.y, worldNewTarget.z);

		break;
	case 3: //Left 
		rotationMatrix.SetRotationY(deltaTime * m_rotateSpeed);
		localNewTarget = localTarget * rotationMatrix;
		worldNewTarget = localNewTarget * m_worldMatrix;
		// Update m_target with the new target expressed in world coordinates
		m_target = Vector3(worldNewTarget.x, worldNewTarget.y, worldNewTarget.z);

		break;
	case 4: //Right
		rotationMatrix.SetRotationY(-deltaTime * m_rotateSpeed);
		localNewTarget = localTarget * rotationMatrix;
		worldNewTarget = localNewTarget * m_worldMatrix;
		// Update m_target with the new target expressed in world coordinates
		m_target = Vector3(worldNewTarget.x, worldNewTarget.y, worldNewTarget.z);

		break;
	default:
		break;
	}

	CalculateWorldMatrix();
	CalculateViewMatrix();
};

void Camera::SetPosition(Vector3 position)
{
	m_position = position;
}

void Camera::SetTarget(Vector3 target)
{
	m_target = target;
}

Matrix Camera::GetWorldMatrix() 
{
	return m_worldMatrix;
};

Matrix Camera::GetViewMatrix()
{
	return m_viewMatrix;
};

Matrix Camera::GetPerspectiveMatrix()
{
	return m_perspectiveMatrix;
};

Matrix Camera::GetProjectMatrix() 
{
	return m_projectMatrix;
};

void Camera::SetCameraID(std::string cameraID)
{
	m_cameraID = cameraID;
};
std::string Camera::GetCameraID()
{
	return m_cameraID;
};

/*Camera::Camera(
	Vector3 position,
	Vector3 target,
	Vector3 up,
	GLfloat fov,
	GLfloat fNear,
	GLfloat fFar,
	GLfloat moveSpeed,
	GLfloat rotateSpeed
) :
	m_position(position),
	m_target(target),
	m_up(up),
	m_fov(fov),
	m_near(fNear),
	m_far(fFar),
	m_moveSpeed(moveSpeed),
	m_rotateSpeed(rotateSpeed)
{
	m_projectMatrix.SetPerspective(m_fov, (GLfloat)Globals::screenWidth / Globals::screenHeight, m_near, m_far);

	CalculateWorldMatrix();
	CalculateViewMatrix();
}

Camera::Camera(
	GLfloat fov,
	GLfloat fNear,
	GLfloat fFar,
	GLfloat moveSpeed,
	GLfloat rotateSpeed
) :
	m_fov(fov),
	m_near(fNear),
	m_far(fFar),
	m_moveSpeed(moveSpeed),
	m_rotateSpeed(rotateSpeed)
{
	m_position = Vector3(0.0f, 0.0f, 0.0f);
	m_target = Vector3(0.0f, 0.0f, -1.0f);
	m_up = Vector3(0.0f, 1.0f, 0.0f);
	m_projectMatrix.SetPerspective(m_fov, (GLfloat)Globals::screenWidth / Globals::screenHeight, m_near, m_far);

	CalculateWorldMatrix();
	CalculateViewMatrix();
}

Camera::Camera(
	GLfloat left,
	GLfloat right,
	GLfloat top,
	GLfloat bottom,
	GLfloat fNear,
	GLfloat fFar,
	GLfloat fSpeed)
{
	m_moveSpeed = fSpeed;
	m_rotateSpeed = fSpeed;

	m_position = Vector3(0.0f, 0.0f, 0.0f);
	m_target = Vector3(0.0f, 0.0f, -1.0f);
	m_up = Vector3(0.0f, 1.0f, 0.0f);

	m_projectMatrix.SetOrtho(left, right, bottom, top, fNear, fFar);
	CalculateWorldMatrix();
	CalculateViewMatrix();
}
*/