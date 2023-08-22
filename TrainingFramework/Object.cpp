#include "stdafx.h"
#include "Object.h"
#include "Vertex.h"
#include <memory>
#include "ResourceManager.h"
#include <vector>

Object::Object() 
{
	m_model = nullptr;
	m_shader = nullptr;
	m_camera = nullptr;
}

Object::~Object() 
{
}

bool Object::Init(
	int objectId, 
	std::shared_ptr<Model> modelPtr, 
	std::vector<std::shared_ptr<Texture>> textureVector, 
	std::shared_ptr<Shaders> shaderPtr
)
{
	m_objectId = objectId;
	m_model = modelPtr;
	m_textureVector = textureVector;
	m_shader = shaderPtr;
	return 0;
}

int Object::GetObjectID() 
{
	return m_objectId;
}

void Object::Draw() 
{
	glUseProgram(m_shader->program);

	glBindBuffer(GL_ARRAY_BUFFER, m_model->getVboId());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_model->getIboId());

	for (const auto& texturePtr : m_textureVector) 
	{
		glBindTexture(GL_TEXTURE_2D, texturePtr->getTextureId());

		if (m_shader->positionAttribute != -1) 
		{
			glEnableVertexAttribArray(m_shader->positionAttribute);
			glVertexAttribPointer(m_shader->positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		}

		if (m_shader->uvAttribute != -1) 
		{
			glEnableVertexAttribArray(m_shader->uvAttribute);
			glVertexAttribPointer(m_shader->uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Vector3));
		}

		if (m_shader->uniformTextureLocation != -1) 
		{
			glActiveTexture(GL_TEXTURE0);
			glUniform1i(m_shader->uniformTextureLocation, 0);
		}

		if (m_shader->uniformWVPLocation != -1) 
		{
			Matrix WVP = CalculateWVP();
			glUniformMatrix4fv(m_shader->uniformWVPLocation, 1, GL_FALSE, WVP.m[0]);
		}

		glEnable(GL_DEPTH_TEST);

		glDrawElements(GL_TRIANGLES, m_model->getNumIndices(), GL_UNSIGNED_INT, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	glBindTexture(GL_TEXTURE_2D, 0);

};

void Object::SetPos(Vector3 pos) 
{
	m_pos = pos;
}

void Object::SetScale(Vector3 scale) 
{
	m_scale = scale;
}

void Object::SetRotate(Vector3 rotate) 
{
	m_rotate = rotate;
}

void Object::Key() 
{
};

void Object::Update(GLfloat deltaTime, int typeMove) 
{
	if (typeMove <= 4) {
		m_camera->Move(deltaTime, typeMove);
	}
		
	else if (4 < typeMove && typeMove <= 8) {
		m_camera->Rotate(deltaTime, (typeMove - 4));
	}
};

Matrix Object::CalculateWVP() 
{
	Matrix Rx, Ry, Rz, R, S, T;
	Rx.SetRotationX(m_rotate.x);
	Ry.SetRotationY(m_rotate.y);
	Rz.SetRotationZ(m_rotate.z);

	R = Rz * Rx * Ry;
	S.SetScale(m_scale);
	T.SetTranslation(m_pos);
	Matrix worldMatrix = S * R * T;

	return worldMatrix * m_camera->GetViewMatrix() * m_camera->GetPerspectiveMatrix();
};

void Object::SetCamera(std::shared_ptr<Camera> cameraPtr) {
	m_camera = cameraPtr;
};