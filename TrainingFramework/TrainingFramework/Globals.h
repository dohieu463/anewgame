#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

class Globals
{
public:
	static const int screenWidth = 1280;
	static const int screenHeight = 960;
	static std::vector<int> topScores;
	
};
#define KEY_UP				VK_UP
#define KEY_DOWN			VK_DOWN
#define KEY_LEFT			VK_LEFT
#define KEY_RIGHT			VK_RIGHT
#define KEY_MOVE_FORWARD	'W'
#define KEY_MOVE_BACKWARD	'S'
#define KEY_MOVE_LEFT		'A'
#define KEY_MOVE_RIGHT		'D'