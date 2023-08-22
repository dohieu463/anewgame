#pragma once
#include <string>
#include <vector>
#include <memory>
#include "ResourceManager.h"
#include "Object.h"
#include "Camera.h"
#include "SingletonClass.h"

class SceneManager : public SingletonClass<SceneManager> {
public:

    SceneManager();
    ~SceneManager();
    
    void LoadScene(char* smFile);
    void Update(float deltaTime, int typeMove);
    void Draw();

    std::vector<std::shared_ptr<Object>> GetObjects();
    std::shared_ptr<Camera> GetCamera();

private:
    
    std::vector<std::shared_ptr<Object>> m_objects;
    std::shared_ptr<Camera> m_camera;
};

