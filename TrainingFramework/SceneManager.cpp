#include "stdafx.h"
#include "SceneManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
///*
SceneManager::SceneManager() {}

SceneManager::~SceneManager() {}

void SceneManager::LoadScene(char* smFile) {
    std::ifstream file(smFile);
    if (!file.is_open()) {
        std::cout << "Could not open the file.\n";
        return;
    }
    
    std::string type;

    while (file >> type) {
        if (type.find("Objects") != std::string::npos) {
            std::string num;
            file >> num;
            int numModels = std::stoi(num);

            for (int i = 0; i < numModels; i++) {
                int object_id;
                std::string model_id;
                int numTexture;
                std::vector<int> textureIds;
                std::string shader_id;
                Vector3 pos;
                Vector3 rot;
                Vector3 scale;

                file >> type >> object_id >> type >> model_id >> type >> numTexture;
                for (int j = 0; j < numTexture; ++j) {
                    int textureId;
                    file >> type >> textureId;
                    textureIds.push_back(textureId);
                }

                file >> type >> shader_id >> type >> pos.x >> pos.y >> pos.z >> type >> rot.x >> rot.y >> rot.z >> type >> scale.x >> scale.y >> scale.z;
                // Lưu thông tin về object vào đây
                std::shared_ptr<Model> modelPtr = ResourceManager::GetInstance()->GetModelPointer(model_id);
                std::shared_ptr<Shaders> shaderPtr = ResourceManager::GetInstance()->GetShaderPointer(shader_id);
                std::vector<std::shared_ptr<Texture>> textureVector;
                for (int j = 0; j < numTexture; ++j) {
                    std::shared_ptr<Texture> texturePtr = ResourceManager::GetInstance()->GetTexturePointer(std::to_string(textureIds[j]));
                    textureVector.push_back(texturePtr);
                }

                std::shared_ptr<Object> newObject = std::make_shared<Object>();
                newObject->Init(object_id, modelPtr, textureVector, shaderPtr);
                newObject->SetPos(pos);
                newObject->SetRotate(rot);
                newObject->SetScale(scale);
                m_objects.push_back(newObject);
            }
        }
        else if (type.find("CAMERA") != std::string::npos) {
            float nearInfo, farInfo, fov, speed;
            file >> type >> nearInfo >> type >> farInfo >> type >> fov >> type >> speed;
            m_camera = std::make_shared<Camera>(nearInfo, farInfo, fov, speed);
        }
    }
    file.close();
}

void SceneManager::Update(float deltaTime, int typeMove) {
    for (const auto& objectPtr : m_objects) {
        objectPtr->Update(deltaTime, typeMove);
    }
}

void SceneManager::Draw() {
    for (const auto& objectPtr : m_objects) {
        objectPtr->Draw();
    }
}

std::vector<std::shared_ptr<Object>> SceneManager::GetObjects() {
    return m_objects;
}

std::shared_ptr<Camera> SceneManager::GetCamera() {
    return m_camera;
}
//*/