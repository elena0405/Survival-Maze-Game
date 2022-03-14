#pragma once

#include "components/simple_scene.h"
#include "components/transform.h"


namespace m1
{
    class PodeaRing {
    public:
        float scaleX, scaleY, scaleZ;
        glm::mat4 modelMatrix;
        float translateX, translateY, translateZ;

        PodeaRing() {};

        PodeaRing(float tx, float ty, float tz, float sx, float sy, float sz, glm::mat4 modelMatrix) {
            this->translateX = tx;
            this->translateY = ty;
            this->translateZ = tz;
            this->scaleX = sx;
            this->scaleY = sy;
            this->scaleZ = sz;
            this->modelMatrix = modelMatrix;
        }

        ~PodeaRing() {};
    };

    class Perete {
    public:
        float scaleX, scaleY, scaleZ;
        glm::mat4 modelMatrix;
        float translateX, translateY, translateZ;

        Perete() {};

        Perete(float tx, float ty, float tz, float sx, float sy, float sz, glm::mat4 modelMatrix) {
            this->translateX = tx;
            this->translateY = ty;
            this->translateZ = tz;
            this->scaleX = sx;
            this->scaleY = sy;
            this->scaleZ = sz;
            this->modelMatrix = modelMatrix;
        }

        ~Perete() {};
    };
    
    class Tema3 : public gfxc::SimpleScene
    {
     public:
        Tema3();
        ~Tema3();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix, const glm::vec3 &color = glm::vec3(1));

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        void GenerarePodea();
        void GenerarePereteStang();
        void GenerarePereteDrept();
        void GenerarePereteSpate();
        void CrearePereteStang();
        void CrearePereteDrept();
        void CrearePereteSpate();
        void CrearePodea();

        std::vector<glm::vec3> pozitiiPodea;
        std::vector<glm::vec3> culoriPodea;
        std::vector<glm::vec3> pozitiiPereteStang, pozitiiPereteDrept, PozitiiPereteSpate;

        bool generarePodea;

        glm::vec3 lightPosition;
        unsigned int materialShininess;
        float materialKd;
        float materialKs;
        float materialKe;
    };
}   // namespace m1
