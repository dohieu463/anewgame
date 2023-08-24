#pragma once
#include <string>
#include <vector>
#include <memory>
#include "ResourceManager.h"
#include "Object.h"
#include "Camera.h"
#include "SingletonClass.h"
#include "Globals.h"

class SceneManager : public SingletonClass<SceneManager> {
public:

    SceneManager();
    ~SceneManager();
    
    void LoadScene(char* smFile);
    void Update(float deltaTime, int typeMove);
    void Draw();

    std::shared_ptr<Object> GetObjectByID(std::string objectID);

    std::shared_ptr<Camera> GetCamera(std::string cameraID);

private:
    std::map<std::string, std::shared_ptr<Object>> m_objects;
    //std::vector<std::shared_ptr<Object>> m_objects;
    std::shared_ptr<Camera> m_camera;
    //std::shared_ptr<Camera> m_camera2D;
    //std::shared_ptr<Camera> m_camera3D;
};

