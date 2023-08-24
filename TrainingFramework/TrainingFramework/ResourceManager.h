#pragma once
#include "SingletonClass.h"
#include "Shaders.h"
#include "Texture.h"
#include "Model.h"
#include<string>
#include<map>
#include "Camera.h"

class ResourceManager : public SingletonClass<ResourceManager> {
public:
    
    ResourceManager();
    ~ResourceManager();

    void LoadResource(const char* rmFile);

    std::shared_ptr<Shaders> GetShaderPointerByID(const char* shaderID);
    std::shared_ptr<Texture> GetTexturePointerByID(const char* textureID);
    std::shared_ptr<Model> GetModelPointerByID(const char* modelID);

    std::shared_ptr<Shaders> GetShaderPointerByName(const char* shaderName);
    std::shared_ptr<Texture> GetTexturePointerByName(const char* textureName);
    std::shared_ptr<Model> GetModelPointerByName(const char* modelName);

private:
    
    std::map<std::string, std::shared_ptr<Shaders>> m_shaders;
    std::map<std::string, std::shared_ptr<Texture>> m_textures;
    std::map<std::string, std::shared_ptr<Model>> m_models;

};

