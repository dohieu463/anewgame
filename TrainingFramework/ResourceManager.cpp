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
                m_models.insert(std::make_pair(id, newModel));
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
                std::string tilingType;
                file >> type >> id >> type >> fileName >> type >> tilingType;
                
                // Lưu thông tin về texture vào đây
                std::shared_ptr<Texture> newTexture = std::make_shared<Texture>(fileName.c_str());
                //Ở đây chưa xử lí TILING, sẽ bổ sung sau
                m_textures.insert(std::make_pair(id, newTexture));
            }
        }
        else if (type.find("Shaders") != std::string::npos) 
        {
            int numShaders;
            file >> numShaders;

            for (int i = 0; i < numShaders; i++) 
            {
                std::string id;
                std::string vsFileName, fsFileName;
                int numStates;
                file >> type >> id >> type >> vsFileName >> type >> fsFileName >> type >> numStates;
                
                for (int j = 0; j < numStates; j++) 
                {
                    std::string state;
                    file >> type >> state;
                    // Lưu thông tin về shader và các state vào đây
                }
                 
                std::shared_ptr<Shaders> newShader = std::make_shared<Shaders>();
                char vsFileNameCStr[256]; 
                char fsFileNameCStr[256]; 

                strcpy(vsFileNameCStr, vsFileName.c_str()); 
                strcpy(fsFileNameCStr, fsFileName.c_str()); 
                newShader->Init(vsFileNameCStr, fsFileNameCStr);
                m_shaders.insert(std::make_pair(id, newShader));
                
            }
        }
    }

    file.close();
}

std::shared_ptr<Shaders> ResourceManager::GetShaderPointer(const std::string& shaderID) 
{
    auto shaderIter = m_shaders.find(shaderID);
    if (shaderIter != m_shaders.end()) 
    {
        return shaderIter->second;
    }
    return nullptr; 
}

std::shared_ptr<Texture> ResourceManager::GetTexturePointer(const std::string& textureID)
{
    auto textureIter = m_textures.find(textureID);
    if (textureIter != m_textures.end())
    {
        return textureIter->second;
    }
    return nullptr; 
}

std::shared_ptr<Model> ResourceManager::GetModelPointer(const std::string& modelID) 
{
    auto modelIter = m_models.find(modelID);
    if (modelIter != m_models.end()) 
    {
        return modelIter->second;
    }
    return nullptr; 
}
