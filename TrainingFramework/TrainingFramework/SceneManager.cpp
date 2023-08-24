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
                std::string object_id;
                std::string model_id;
                int numTexture;
                std::vector<std::string> textureIds;
                std::string shader_id;
                Vector3 pos;
                Vector3 rot;
                Vector3 scale;

                file >> type >> object_id >> type >> model_id >> type >> numTexture;
                for (int j = 0; j < numTexture; ++j) {
                    std::string textureId;
                    file >> type >> textureId;
                    textureIds.push_back(textureId);
                }

                file >> type >> shader_id >> type >> 
                    pos.x >> pos.y >> pos.z >> type >> 
                    rot.x >> rot.y >> rot.z >> type >> 
                    scale.x >> scale.y >> scale.z;
                // Lưu thông tin về object vào đây
                std::shared_ptr<Model> modelPtr = ResourceManager::GetInstance()->GetModelPointerByID(model_id.c_str());
                std::shared_ptr<Shaders> shaderPtr = ResourceManager::GetInstance()->GetShaderPointerByID(shader_id.c_str());
                std::vector<std::shared_ptr<Texture>> textureVector;
                std::shared_ptr<Texture> texturePtr = std::make_shared<Texture>();
                for (int j = 0; j < numTexture; ++j) {
                    texturePtr = ResourceManager::GetInstance()->GetTexturePointerByID(textureIds[j].c_str());
                    textureVector.push_back(texturePtr);
                }

                std::shared_ptr<Object> newObject = std::make_shared<Object>(modelPtr, texturePtr, shaderPtr);
                newObject->SetPos(pos);
                newObject->SetRotate(rot);
                newObject->SetScale(scale);
                newObject->SetObjectID(object_id);
                m_objects.insert(std::make_pair(object_id, newObject));
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
        objectPtr.second->Update(deltaTime, typeMove);
    }
}

void SceneManager::Draw() {
    for (const auto& objectPtr : m_objects) {
        objectPtr.second->Draw();
    }
}

std::shared_ptr<Object> SceneManager::GetObjectByID(std::string objectID) {
    for (auto& it : m_objects) 
    {
        if (it.first == objectID)
        {
            return it.second;
        }
    }
    return nullptr;
}

std::shared_ptr<Camera> SceneManager::GetCamera(std::string cameraID) {
    /*
    if (cameraID == "2D") 
    {
        return m_camera2D;
    }

    else if (cameraID == "3D") 
    {
        return m_camera3D;
    }

    else
    {
    */
        return m_camera;
    //}
}
//*/