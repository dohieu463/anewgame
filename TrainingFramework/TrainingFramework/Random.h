#include "../TrainingFramework/stdafx.h"
#include <random>

std::random_device rd;
// Sử dụng seed để khởi tạo generator ngẫu nhiên
std::mt19937 generator(rd());

// Định nghĩa phạm vi của số ngẫu nhiên
std::uniform_int_distribution<int> distribution(1, 1000); // Từ 1 đến 1000