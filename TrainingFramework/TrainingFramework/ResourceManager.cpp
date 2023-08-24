#include "stdafx.h"
#include "ResourceManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

ResourceManager::ResourceManager() 
{
}

ResourceManager::~ResourceManager() 
{
}

void ResourceManager::LoadResource(const char* rmFile)
{
    std::ifstream file(rmFile);
    if (!file.is_open())
    {
        std::cout << "Could not open the file.\n";
        return;
    }

    std::string type;
    while (file >> type) 
    {
        if (type.find("Model") != std::string::npos)
        {
            int numModels;
            file >> numModels;
            for (int i = 0; i < numModels; i++)
            {
                std::string id;
                std::string fileName;
                file >> type >> id >> type >> fileName;
                
                // Lưu thông tin về model vào đây
                std::shared_ptr<Model> newModel = std::make_shared<Model>(fileName.c_str());
                newModel->SetModelID(id);
                m_models.insert(std::make_pair(fileName, newModel));
             }
        }
        else if (type.find("Textures") != std::string::npos) 
        {
            int numTextures;
            file >> numTextures;

            for (int i = 0; i < numTextures; i++) 
            {
                std::string id;
                std::string fileName;
                file >> type >> id >> type >> fileName;
                
                // Lưu thông tin về texture vào đây
                std::shared_ptr<Texture> newTexture = std::make_shared<Texture>(fileName.c_str());
                newTexture->SetTextureID(id);
                m_textures.insert(std::make_pair(fileName, newTexture));
            }
        }
        else if (type.find("Shaders") != std::string::npos) 
        {
            int numShaders;
            file >> numShaders;

            for (int i = 0; i < numShaders; i++) 
            {
                std::string id;
                std::string fileName;
                int numStates;
                file >> type >> id >> type >> fileName;
                
                std::shared_ptr<Shaders> newShader = std::make_shared<Shaders>();
                newShader->Init(fileName.c_str());
                newShader->SetShaderID(id);
                m_shaders.insert(std::make_pair(fileName, newShader));
            }
        }
    }
    file.close();
}

std::shared_ptr<Shaders> ResourceManager::GetShaderPointerByID(const char* shaderID)
{
    for (auto it : m_shaders)
    {
        std::string temp = it.second->GetShaderID();
        if (temp == shaderID)
        {
            return it.second;
        }
    }
    return nullptr; 
}

std::shared_ptr<Texture> ResourceManager::GetTexturePointerByID(const char* textureID)
{
    for (auto it : m_textures)
    {
        if (it.second->GetID() == textureID)
        {
            return it.second;
        }
    }
    return nullptr;
}

std::shared_ptr<Model> ResourceManager::GetModelPointerByID(const char* modelID)
{
    for (auto it : m_models)
    {
        if (it.second->GetModelID() == modelID)
        {
            return it.second;
        }
    }
    return nullptr;
}

std::shared_ptr<Shaders> ResourceManager::GetShaderPointerByName(const char* shaderName)
{
    auto it = m_shaders.find(shaderName);
    if (it != m_shaders.end())
    {
        return it->second;
    }
    return nullptr;
};

std::shared_ptr<Texture> ResourceManager::GetTexturePointerByName(const char* textureName)
{
    auto it = m_textures.find(textureName);
    if (it != m_textures.end())
    {
        return it->second;
    }
    return nullptr;
};

std::shared_ptr<Model> ResourceManager::GetModelPointerByName(const char* modelName)
{
    auto it = m_models.find(modelName);
    if (it != m_models.end())
    {
        return it->second;
    }
    return nullptr;
};
