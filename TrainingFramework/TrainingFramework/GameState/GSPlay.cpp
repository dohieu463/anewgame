#include "../TrainingFramework/stdafx.h"
#include "GSPlay.h"

float animationX = 50;
float animationY = (float)Globals::screenHeight / 2; 
std::vector<int> Globals::topScores;

GSPlay::GSPlay()
{
	m_stateType = STATE_PLAY;
}

GSPlay::~GSPlay()
{
}

void GSPlay::Init()
{
	m_playBackground = SceneManager::GetInstance()->GetObjectByID("play_background");
	m_base = SceneManager::GetInstance()->GetObjectByID("human_base");
	m_loadingAnimation = SceneManager::GetInstance()->GetAnimationByID("loading_animation");
	auto buttonPause = SceneManager::GetInstance()->GetButtonByID("button_pause");
	m_buttonList.push_back(buttonPause);
	auto buttonResume = SceneManager::GetInstance()->GetButtonByID("button_resume");
	m_buttonList.push_back(buttonResume);
	
	alienCount = 0;
	m_time = 1;
	lives = 3;
	alienSpawned = 0;
	score = 0;
	m_mobAlienRate = 100;
	m_medAlienRate = 0;
	m_highAlienRate = 0;
	m_bullets = 10;
	m_gunReloadTime = 2.0f;
	m_reloadTime = 2.0f;
	isBulletOut = false;
}

void GSPlay::Exit()
{
}

void GSPlay::Pause()
{
	
}

void GSPlay::Resume()
{
}

void GSPlay::GunUpdate(float deltaTime) 
{
	if (isBulletOut) {
		m_reloadTime -= deltaTime;
		if (m_reloadTime <= 0) {
			m_reloadTime = m_gunReloadTime;
			m_bullets = 10;
			isBulletOut = false;
		}
	}
	else 
	{
		if (m_bullets == 0)	isBulletOut = true;
	}
}

void GSPlay::Update(float deltaTime)
{
	SpawnByDifficult(deltaTime);
	UpdateDifficult();
	GunUpdate(deltaTime);
	std::vector<std::shared_ptr<BaseAlien>> aliveAlien;
	float difficult = (10.0 + alienSpawned % 10) / 10;
	for (auto& alien : m_alien) {
		if (alien->GetAliveStatus()) 
		{
			alien->UpdatePos(deltaTime, difficult);
			if (alien->GetPos().x > Globals::screenWidth - 60) {
				alienCount--;
				lives--;
			}

			else aliveAlien.push_back(alien);
		}
		else 
		{
			alien->m_destroyedTime += deltaTime;
			if (alien->m_destroyedTime <= 0.5f) 
				aliveAlien.push_back(alien);
		}
		alien->Update(deltaTime);
	}	
	m_alien = aliveAlien;

	if (lives == 0)
	{
		UpdateScore(Globals::topScores, score);
		GSMachine::GetInstance()->PushState(StateType::STATE_GAMEOVER);
	}
}

void GSPlay::Draw()
{
	m_playBackground->Draw();
	m_base->Draw();
	for (auto& alien : m_alien)
		alien->Draw();
	if (isBulletOut) m_loadingAnimation->Draw();
	for (auto& button : m_buttonList)
		button->Draw();
}


void GSPlay::HandleEvents()
{
}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSPlay::HandleTouchEvents(float x, float y, bool bIsPressed)
{	
	if(!isBulletOut) 
	{
		m_bullets-= 0.5f;
		for (auto& alien : m_alien)
		{
			if (alien->HandleTouchEvent(x, y, bIsPressed))
			{
				alienCount--;
				score += alien->GetScore();
			}
		}
	}

	for (auto& button : m_buttonList) {
		if (button->HandleTouchEvent(x, y, bIsPressed))
		{
			switch (button->m_type)
			{
			case BUTTON_PAUSE:
				GSMachine::GetInstance()->Pause();
				button->SetAlpha(0.5f);
				break;
			case BUTTON_RESUME:
				GSMachine::GetInstance()->Resume();
				for (auto& btn : m_buttonList)
					btn->SetAlpha(1.0f);
				break;
			}
		};
	}
}

void GSPlay::HandleMouseMoveEvents(float x, float y)
{
	for (auto& button : m_buttonList)
	{
		button->HandleMoveEvent(x, y);
	}
}

void GSPlay::Spawn(const char* type) 
{
	if (alienCount == 10) return;
	std::string difficult(type);
	int randomAlien = rand() % 4 + 1;
	std::string alienName = difficult + "Alien" + std::to_string(randomAlien);
	
	auto new_alien = SceneManager::GetInstance()->GetAlienByID(alienName.c_str());
	auto alien = std::make_shared<BaseAlien>(*new_alien);
	float animationX = 50;
	float animationY = (float)Globals::screenHeight / 2 + (rand() % 5) * 120 - 240;
	alien->Set2DPos(animationX, animationY);

	m_alien.push_back(alien);
	alienCount++;
	alienSpawned++;
}

void GSPlay::UpdateDifficult()
{
	if (alienSpawned == 200) return;
	m_mobAlienRate = 100 - alienSpawned / 2.0;
	m_medAlienRate = 0 + alienSpawned / 3.0;
	m_highAlienRate = 0 + alienSpawned / 6.0;
}

void GSPlay::SpawnByDifficult(float deltaTime) {
	m_time -= deltaTime;
	if (m_time <= 0) {
		m_time += 1;
		int randomNum = rand() % 100;
		const char* difficult = nullptr;
		if (randomNum <= m_mobAlienRate) difficult = "mob";
		else if (randomNum <= m_mobAlienRate + m_medAlienRate) difficult = "med";
		else difficult = "high";
		Spawn(difficult);
	}
}

void UpdateScore(std::vector<int>& scores, int currentScore) {
	std::ifstream inputFile("high_scores.txt");
	if (inputFile.is_open()) {
		scores.clear(); 
		std::string line;
		while (std::getline(inputFile, line)) {
			if (line == "###") {
				break; 
			}

			try {
				int score = std::stoi(line);
				scores.push_back(score); // Thêm điểm vào vector
			}
			catch (const std::invalid_argument& e) {
				std::cerr << "Lỗi định dạng tệp tin: " << e.what() << std::endl;
			}
		}

		inputFile.close();
	}
	else {
		std::cerr << "Không thể mở tệp tin." << std::endl;
		return; 
	}
	scores.push_back(currentScore);
	std::sort(scores.rbegin(), scores.rend());

	if (scores.size() > 5) {
		scores.resize(5);
	}

	std::ofstream outputFile("high_scores.txt");
	if (outputFile.is_open()) {
		for (const int score : scores) {
			outputFile << score << std::endl;
		}
		outputFile << "###" << std::endl; 
		outputFile.close();
	}
	else {
		std::cerr << "Không thể ghi tệp tin." << std::endl;
		return; 
	}
}