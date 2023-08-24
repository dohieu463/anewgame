#include "stdafx.h"
#include "BaseObject.h"
#include "Vertex.h"
#include <memory>
#include "ResourceManager.h"
#include "SceneManager.h"
#include <vector>

BaseObject::BaseObject()
{
	m_camera = SceneManager::GetInstance()->GetCamera("smth");
	m_alpha = 2.0f;
	m_pos = Vector3(0.0f, 0.0f, 0.0f);
	m_scale = Vector3(1.0f, 1.0f, 1.0f);
	m_rotate = Vector3(0.0f, 0.0f, 0.0f);
}

BaseObject::BaseObject(std::shared_ptr<Model> modelPtr, std::shared_ptr<Texture> texturePtr, std::shared_ptr<Shaders> shaderPtr)
{
	m_model = modelPtr;
	m_texture = texturePtr;
	m_shader = shaderPtr;

	m_camera = SceneManager::GetInstance()->GetCamera("smth");
	m_alpha = 2.0f;
	m_pos = Vector3(0.0f, 0.0f, 0.0f);
	m_scale = Vector3(1.0f, 1.0f, 1.0f);
	m_rotate = Vector3(0.0f, 0.0f, 0.0f);
}

BaseObject::~BaseObject()
{
}

void BaseObject::Draw()
{
	glUseProgram(m_shader->program);

	glBindBuffer(GL_ARRAY_BUFFER, m_model->getVboId());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_model->getIboId());
	glBindTexture(GL_TEXTURE_2D, m_texture->getTextureId());

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//finding location of uniforms / attributes
	GLint positionAttribute = glGetAttribLocation(m_shader->program, "a_posL");
	if (positionAttribute != -1)
	{
		glEnableVertexAttribArray(positionAttribute);
		glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	GLint uvAttribute = glGetAttribLocation(m_shader->program, "a_uv");
	if (uvAttribute != -1)
	{
		glEnableVertexAttribArray(uvAttribute);
		glVertexAttribPointer(uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Vector3));
	}

	GLint uniformTextureLocation = glGetUniformLocation(m_shader->program, "u_texture");
	if (uniformTextureLocation != -1)
	{
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(uniformTextureLocation, 0);

	}

	GLint uniformWVPLocation = glGetUniformLocation(m_shader->program, "u_wvp");
	if (uniformWVPLocation != -1)
	{
		Matrix WVP = CalculateWVP();
		glUniformMatrix4fv(uniformWVPLocation, 1, GL_FALSE, WVP.m[0]);
	}

	GLint uniformAlpha = glGetUniformLocation(m_shader->program, "u_alpha");
	if (uniformAlpha != -1)
	{
		glUniform1f(uniformAlpha, m_alpha);
	}

	glDrawElements(GL_TRIANGLES, m_model->getNumIndices(), GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

};

void BaseObject::SetPos(Vector3 pos)
{
	m_pos = pos;
}

void BaseObject::SetScale(Vector3 scale)
{
	m_scale = scale;
}

void BaseObject::SetRotate(Vector3 rotate)
{
	m_rotate = rotate;
}

void BaseObject::Key()
{
};

void BaseObject::Update(GLfloat deltaTime, int typeMove)
{
	if (typeMove <= 4) {
		m_camera->Move(deltaTime, typeMove);
	}

	else if (4 < typeMove && typeMove <= 8) {
		m_camera->Rotate(deltaTime, (typeMove - 4));
	}
};

Matrix BaseObject::CalculateWVP()
{
	Matrix Rx, Ry, Rz, R, S, T;
	Rx.SetRotationX(m_rotate.x);
	Ry.SetRotationY(m_rotate.y);
	Rz.SetRotationZ(m_rotate.z);

	R = Rz * Rx * Ry;
	S.SetScale(m_scale);
	T.SetTranslation(m_pos);
	Matrix worldMatrix = S * R * T;

	return worldMatrix * m_camera->GetViewMatrix() * m_camera->GetProjectMatrix();
};

void BaseObject::SetCamera(std::shared_ptr<Camera> cameraPtr) {
	m_camera = cameraPtr;
};

void BaseObject::SetSize(GLfloat width, GLfloat height)
{
	m_width = width;
	m_height = height;
	SetScale(Vector3(width, height, 1.0f));

}

void BaseObject::SetObjectID(std::string objectID)
{
	m_objectID = objectID;
};

void BaseObject::SetAlpha(GLfloat alpha)
{
	m_alpha = alpha;
};

std::string BaseObject::GetObjectID()
{
	return m_objectID;
};
