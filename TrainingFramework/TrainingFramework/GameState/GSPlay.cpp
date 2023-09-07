#include "../TrainingFramework/stdafx.h"
#include "GSPlay.h"
#include "../TrainingFramework/stdafx.h"
#include "../TrainingFramework/GameManager/SceneManager.h"
#include "../TrainingFramework/GameManager/ResourceManager.h"
#include "../TrainingFramework/Globals.h"
#include "../TrainingFramework/GameState/GSMachine.h"
#include<cstdlib>
#include <algorithm>

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
	printf("This is play\n");
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

void GSPlay::Update(float deltaTime)
{
	///*
	m_time -= deltaTime;
	if (m_time <= 0) {
		m_time += 1;
		Spawn();
	}

	std::vector<std::shared_ptr<BaseAlien>> aliveAlien;

	for (auto& alien : m_alien) {
		float animationX = alien->GetPos().x;
		float animationY = alien->GetPos().y;
		
		if (alien->GetAliveStatus()) 
		{
			float difficult = (10 + alienSpawned % 10) / 10;
			animationX += alien->GetSpeed() * deltaTime * difficult;

			int random_number = rand();

			if (random_number % 2 == 0)
			{
				animationY += 5;
				if (animationY >= 600) animationY -= 5;
			}
			
			else 
			{
				animationY -= 5;
				if (animationY <= 120) animationY += 5;
			}
			
			if (animationX > Globals::screenWidth - 60) {
				alienCount--;
				lives--;
				if (lives == 0) 
				{
					GSMachine::GetInstance()->PushState(StateType::STATE_GAMEOVER);
					printf("Your score: %d\n", score);

					UpdateScore(Globals::topScores, score);

					/*
					Globals::topScores.push_back(score); // Thêm điểm số mới vào cuối danh sách

					// Sắp xếp danh sách theo thứ tự giảm dần
					std::sort(Globals::topScores.begin(), Globals::topScores.end(), std::greater<int>());

					// Giới hạn danh sách chỉ lấy 5 điểm số lớn nhất
					if (Globals::topScores.size() > 5) {
						Globals::topScores.resize(5);
					}
					*/
				}
			}

			else
			{
				alien->Set2DPos(animationX, animationY);
				alien->Update(deltaTime);
				aliveAlien.push_back(alien);
			}

		}
		else 
		{
			alien->m_destroyedTime += deltaTime;
			alien->Update(deltaTime);
			if (alien->m_destroyedTime <= 0.5f) 
				aliveAlien.push_back(alien);
		}
	}	
	m_alien = aliveAlien;
	//*/
}

void GSPlay::Draw()
{
	m_playBackground->Draw();
	m_base->Draw();
	for (auto& alien : m_alien)
		alien->Draw();
}


void GSPlay::HandleEvents()
{
}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSPlay::HandleTouchEvents(float x, float y, bool bIsPressed)
{
	for (auto& alien : m_alien) 
	{
		if (alien->HandleTouchEvent(x, y, bIsPressed)) 
		{
			alienCount--;
			score += alien->GetScore();
		}
	}
}

void GSPlay::HandleMouseMoveEvents(float x, float y)
{
}

void GSPlay::Spawn() 
{
	if (alienCount == 10) return;
	int randomAlien = rand() % 4 + 1;
	std::string alienName = "mobAlien" + std::to_string(randomAlien);
	
	auto new_alien = SceneManager::GetInstance()->GetAlienByID(alienName.c_str());
	auto alien = std::make_shared<BaseAlien>(*new_alien);
	float animationX = 50;
	float animationY = (float)Globals::screenHeight / 2 + (rand() % 5) * 120 - 240;
	alien->Set2DPos(animationX, animationY);

	m_alien.push_back(alien);
	alienCount++;
	alienSpawned++;

}

void UpdateScore(std::vector<int>& scores, int currentScore) {
	// Đọc điểm số từ tệp tin
	std::ifstream inputFile("high_scores.txt");
	if (inputFile.is_open()) {
		scores.clear(); // Xóa toàn bộ điểm số trong vector

		std::string line;
		while (std::getline(inputFile, line)) {
			if (line == "###") {
				break; // Đọc đến kí hiệu ### thì dừng
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
		return; // Lỗi mở tệp tin
	}

	// Thêm điểm số hiện tại vào vector
	scores.push_back(currentScore);

	// Sắp xếp vector giảm dần
	std::sort(scores.rbegin(), scores.rend());

	if (scores.size() > 5) {
		scores.resize(5);
	}

	// Ghi đè điểm số mới vào tệp tin
	std::ofstream outputFile("high_scores.txt");
	if (outputFile.is_open()) {
		for (const int score : scores) {
			outputFile << score << std::endl;
		}
		outputFile << "###" << std::endl; // Ghi kí hiệu kết thúc tệp
		outputFile.close();
	}
	else {
		std::cerr << "Không thể ghi tệp tin." << std::endl;
		return; // Lỗi ghi tệp tin
	}
}