#pragma once

#include <string.h>
#include <string>
#include "components/simple_scene.h"
#include "lab_m1/Tema2/Tema2_lab_camera.h"


namespace m1
{
    class Proiectil {
    public:
        glm::vec3 center;
        glm::vec3 direction;
        float radix;
        float translateX, translateY, translateZ;
        float distanceProjectile;
        glm::mat4 modelMatrix;
        int isRunning;

        Proiectil() {}

        Proiectil(glm::vec3 center, glm::vec3 direction, glm::mat4 modelMatrix, float radix, float tX, float tY, float tZ, 
            float distance, int isRunning) {
            this->center = center;
            this->direction = direction;
            this->distanceProjectile = distance;
            this->radix = radix;
            this->translateX = tX;
            this->translateY = tY;
            this->translateZ = tZ;
            this->isRunning = isRunning;
        }

        ~Proiectil() {}
    };

    class Labirint {
    public:
        float translateX, translateZ;
        glm::mat4 modelMatrix;

        Labirint() {}

        Labirint(float translateX, float translateZ, glm::mat4 modelMatrix) {
            this->modelMatrix = modelMatrix;
            this->translateX = translateX;
            this->translateZ = translateZ;
        }

        ~Labirint() {}
    };

    class Podea {
    public:
        float translateX, translateZ;
        glm::mat4 modelMatrix;

        Podea() {}

        Podea(float translateX, float translateZ, glm::mat4 modelMatrix) {
            this->modelMatrix = modelMatrix;
            this->translateX = translateX;
            this->translateZ = translateZ;
        }

        ~Podea() {}
    };

    class HUD {
    public:
        glm::mat4 modelMatrix;
        float scaleX;

        HUD() {}

        HUD(glm::mat4 modelMatrix) {
            this->scaleX = 0.6f;
            this->modelMatrix = modelMatrix;
        }

        ~HUD() {}
    };

    class Inamic {
    public:
        float angle;
        glm::mat4 modelMatrix;
        float translateX, translateZ;
        bool colisionProjectile;

        Inamic() {}

        Inamic(float angle, glm::mat4 modelMatrix, float tX, float tZ) {
            this->translateX = tX;
            this->translateZ = tZ;
            this->angle = angle;
            this->modelMatrix = modelMatrix;
            this->colisionProjectile = false;
        }

        ~Inamic() {}
    };
    
    class Tema2 : public gfxc::SimpleScene
    {
     public:
        Tema2();
        ~Tema2();

        void Init() override;

     private:
        void CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices);
        void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix) override;
        void RenderMeshHUD(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix);
        void RenderMeshInamic(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, bool coliziuneInamic);

        void CreareHUD();
        void CreareJucator();
        void LansareProiectile(float deltaTimeSeconds);
        void CreareLabirint(std::string name);
        void CreareInamici(float deltaTimeSeconds, int index);
        void GenerareLabirint();
        void GenerarePodea();

        int ColiziuneJucatorInamici();
        bool ColiziuneJucatorPereteHarta();
        int ColiziuneProiectilInamici(Proiectil proiectil);
        bool ColisiuneProiectilPereteHarta(Proiectil proiectil);

        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

     protected:
        implem::Camera* camera;
        glm::mat4 projectionMatrix;
        glm::mat4 hudMatrix;
        bool renderCameraTarget;

        std::vector<Proiectil> proiectile;
        std::vector<Inamic> inamici;
        std::vector<Labirint> labirint;
        std::vector<Podea> podea;
        std::vector<glm::vec3> positions;

        glm::mat4 modelMatrix;

        glm::vec3 beginPosition;

        HUD h1, h2, h3;

        float distantaMaxima;
        float translateX, translateY, translateZ, oldTranslateX, oldTranslateZ;
        float positionX, positionY, positionZ;
        float posCameraX, posCameraY, posCameraZ;
        float coordX, coordZ;
        float scale1, scale2, scale3, scale4, scale5, scale6, scale7;
        float CameraSpeed, PlayerSpeed, EnemySpeed;
        float left, right, top, bottom, zNear, zFar;
        float angularStepThird, angularStepFirst;
        float cubeSide;
        float xMinInamic, xMaxInamic, yInamic, yJucator;
        float radixProjectile, distanceProjectile, speedProjectile;
        float mazeSize, x1, x2;
        int  mazeNumber, posNumber, index1, index2;
        bool semafor1, semafor2, semafor3, colisionPlayerWall, directionChanged, isHud, gameOver, coliziuneInamic;
    };
}   // namespace m1
