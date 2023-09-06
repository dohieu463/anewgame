#pragma once
#include "BaseObject.h"
class Animation :  public BaseObject
{
public:
	Animation(
		std::shared_ptr<Model> model, 
		std::vector<std::shared_ptr<Texture>> textureVector,
		std::shared_ptr<Shaders> shader,
		std::vector<GLint> numFrames, 
		std::vector<GLint> numActions,
		std::vector<GLint> currentAction,
		std::vector<GLfloat> frameTime
	);

	Animation();
	~Animation() override;
	Vector2 GetSize() const {
		return Vector2(m_width, m_height); 
	}
	void Draw() override;
	void Update(float deltatime) override;
	
private:

	GLint			m_numFrames;
	GLint			m_currentFrame;
	GLfloat			m_frameTime;
	GLfloat			m_currentTime;
	GLint			m_numActions;
	GLint			m_currentAction;

	std::vector<GLint> 			m_numFramesVector;
	std::vector<GLfloat>		m_frameTimeVector;
	std::vector<GLint> 			m_numActionsVector;
	std::vector<GLint> 			m_currentActionVector;
};

