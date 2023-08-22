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

    std::shared_ptr<Shaders> GetShaderPointer(const std::string& shaderID);
    std::shared_ptr<Texture> GetTexturePointer(const std::string& textureID);
    std::shared_ptr<Model> GetModelPointer(const std::string& modelID);

private:
    
    std::map<std::string, std::shared_ptr<Shaders>> m_shaders;
    std::map<std::string, std::shared_ptr<Texture>> m_textures;
    std::map<std::string, std::shared_ptr<Model>> m_models;

};

