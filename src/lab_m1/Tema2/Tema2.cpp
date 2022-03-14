#include "lab_m1/Tema2/Tema2.h"

#include <vector>
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>

#include "lab_m1/Tema2/Tema2_transform3D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}


void Tema2::Init()
{
    renderCameraTarget = true;
    camera = new implem::Camera();

    positionX = 0;
    positionY = 0.3f;
    positionZ = 0;

    scale1 = 0.3f;
    scale2 = 0.14f;
    scale3 = 0.13f;
    scale4 = 0.25f;
    scale5 = 0.07f;
    scale6 = 0.03f;
    scale7 = 0.02f;

    posCameraX = 0;
    posCameraY = 1;
    posCameraZ = -3;

    index1 = -1;
    index2 = -1;

    mazeNumber = rand() % 10 + 1;
    colisionPlayerWall = false;

    semafor1 = false;
    semafor2 = false;
    semafor3 = false;

    x1 = 0;
    x2 = 0;

    beginPosition = glm::vec3(-10.0f, 0, -10.0f);

    // Initialize tx, ty and tz (the translation steps)
    translateX = 0;
    translateY = 0;
    translateZ = 0;

    distantaMaxima = 5.0f;

    camera->Set(glm::vec3(positionX, positionY + 0.5f, positionZ - 1.5f),
                glm::vec3(positionX , positionY, positionZ),
                glm::vec3(0, positionY + 0.5f, 0));

    coordX = 0;
    coordZ = 0;

    mazeSize = 20.0f;

    cubeSide = 1.0f;

    angularStepFirst = 0;
    angularStepThird = 0;

    CameraSpeed = 2;
    PlayerSpeed = 2;
    EnemySpeed = 2;

    oldTranslateX = 0;
    oldTranslateZ = 0;

    radixProjectile = 0.2f;
    distanceProjectile = 6;
    speedProjectile = 2;

    gameOver = false;
    directionChanged = false;

    h1 = HUD(glm::mat4(1));
    h2 = HUD(glm::mat4(1));
    h3 = HUD(glm::mat4(1));

    // creez un cub pentru a reprezenta parti ale tricoului jucatorului
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 0, 1), glm::vec3(0, 1, 1), glm::vec3(0, 0.9, 0)),
            VertexFormat(glm::vec3(1, 0, 1), glm::vec3(0, 1, 1), glm::vec3(0, 0.9, 0)),
            VertexFormat(glm::vec3(0, 1, 1), glm::vec3(0, 1, 1), glm::vec3(0, 0.9, 0)),
            VertexFormat(glm::vec3(1, 1, 1), glm::vec3(0, 1, 1), glm::vec3(0, 0.9, 0)),
            VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0, 1, 1), glm::vec3(0, 0.9, 0)),
            VertexFormat(glm::vec3(1, 0, 0), glm::vec3(0, 1, 1), glm::vec3(0, 0.9, 0)),
            VertexFormat(glm::vec3(0, 1, 0), glm::vec3(0, 1, 1), glm::vec3(0, 0.9, 0)),
            VertexFormat(glm::vec3(1, 1, 0), glm::vec3(0, 1, 1), glm::vec3(0, 0.9, 0))
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
            1, 3, 2,
            2, 3, 7,
            2, 7, 6,
            1, 7, 3,
            1, 5, 7,
            6, 7, 4,
            7, 5, 4,
            0, 4, 1,
            1, 4, 5,
            2, 6, 4,
            0, 2, 4

        };

        CreateMesh("cube_A", vertices, indices);
    }

    // creez un cub pentru a reprezenta parti ale corpului jucatorului
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 0, 1), glm::vec3(0, 1, 1), glm::vec3(1, 0.878, 0.741)),
            VertexFormat(glm::vec3(1, 0, 1), glm::vec3(0, 1, 1), glm::vec3(1, 0.878, 0.741)),
            VertexFormat(glm::vec3(0, 1, 1), glm::vec3(0, 1, 1), glm::vec3(1, 0.878, 0.741)),
            VertexFormat(glm::vec3(1, 1, 1), glm::vec3(0, 1, 1), glm::vec3(1, 0.878, 0.741)),
            VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0, 1, 1), glm::vec3(1, 0.878, 0.741)),
            VertexFormat(glm::vec3(1, 0, 0), glm::vec3(0, 1, 1), glm::vec3(1, 0.878, 0.741)),
            VertexFormat(glm::vec3(0, 1, 0), glm::vec3(0, 1, 1), glm::vec3(1, 0.878, 0.741)),
            VertexFormat(glm::vec3(1, 1, 0), glm::vec3(0, 1, 1), glm::vec3(1, 0.878, 0.741))
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
            1, 3, 2,
            2, 3, 7,
            2, 7, 6,
            1, 7, 3,
            1, 5, 7,
            6, 7, 4,
            7, 5, 4,
            0, 4, 1,
            1, 4, 5,
            2, 6, 4,
            0, 2, 4

        };

        CreateMesh("cube_B", vertices, indices);
    }

    // creez un cub pentru a reprezenta parti ale pantalonilor jucatorului
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 0, 1), glm::vec3(0, 1, 1), glm::vec3(0, 0.6, 0)),
            VertexFormat(glm::vec3(1, 0, 1), glm::vec3(0, 1, 1), glm::vec3(0, 0.6, 0)),
            VertexFormat(glm::vec3(0, 1, 1), glm::vec3(0, 1, 1), glm::vec3(0, 0.6, 0)),
            VertexFormat(glm::vec3(1, 1, 1), glm::vec3(0, 1, 1), glm::vec3(0, 0.6, 0)),
            VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0, 1, 1), glm::vec3(0, 0.6, 0)),
            VertexFormat(glm::vec3(1, 0, 0), glm::vec3(0, 1, 1), glm::vec3(0, 0.6, 0)),
            VertexFormat(glm::vec3(0, 1, 0), glm::vec3(0, 1, 1), glm::vec3(0, 0.6, 0)),
            VertexFormat(glm::vec3(1, 1, 0), glm::vec3(0, 1, 1), glm::vec3(0, 0.6, 0))
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
            1, 3, 2,
            2, 3, 7,
            2, 7, 6,
            1, 7, 3,
            1, 5, 7,
            6, 7, 4,
            7, 5, 4,
            0, 4, 1,
            1, 4, 5,
            2, 6, 4,
            0, 2, 4

        };

        CreateMesh("cube_C", vertices, indices);
    }

    // creez un cub pentru a reprezenta parul jucatorului
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 0, 1), glm::vec3(0, 1, 1), glm::vec3(0.52, 0.37, 0.26)),
            VertexFormat(glm::vec3(1, 0, 1), glm::vec3(0, 1, 1), glm::vec3(0.52, 0.37, 0.26)),
            VertexFormat(glm::vec3(0, 1, 1), glm::vec3(0, 1, 1), glm::vec3(0.52, 0.37, 0.26)),
            VertexFormat(glm::vec3(1, 1, 1), glm::vec3(0, 1, 1), glm::vec3(0.52, 0.37, 0.26)),
            VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0, 1, 1), glm::vec3(0.52, 0.37, 0.26)),
            VertexFormat(glm::vec3(1, 0, 0), glm::vec3(0, 1, 1), glm::vec3(0.52, 0.37, 0.26)),
            VertexFormat(glm::vec3(0, 1, 0), glm::vec3(0, 1, 1), glm::vec3(0.52, 0.37, 0.26)),
            VertexFormat(glm::vec3(1, 1, 0), glm::vec3(0, 1, 1), glm::vec3(0.52, 0.37, 0.26))
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
            1, 3, 2,
            2, 3, 7,
            2, 7, 6,
            1, 7, 3,
            1, 5, 7,
            6, 7, 4,
            7, 5, 4,
            0, 4, 1,
            1, 4, 5,
            2, 6, 4,
            0, 2, 4

        };

        CreateMesh("cube_D", vertices, indices);
    }

    // creez un cub pentru a reprezenta ochii jucatorului
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 0, 1), glm::vec3(0, 1, 1), glm::vec3(0, 0, 0.7)),
            VertexFormat(glm::vec3(1, 0, 1), glm::vec3(0, 1, 1), glm::vec3(0, 0, 0.7)),
            VertexFormat(glm::vec3(0, 1, 1), glm::vec3(0, 1, 1), glm::vec3(0, 0, 0.7)),
            VertexFormat(glm::vec3(1, 1, 1), glm::vec3(0, 1, 1), glm::vec3(0, 0, 0.7)),
            VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0, 1, 1), glm::vec3(0, 0, 0.7)),
            VertexFormat(glm::vec3(1, 0, 0), glm::vec3(0, 1, 1), glm::vec3(0, 0, 0.7)),
            VertexFormat(glm::vec3(0, 1, 0), glm::vec3(0, 1, 1), glm::vec3(0, 0, 0.7)),
            VertexFormat(glm::vec3(1, 1, 0), glm::vec3(0, 1, 1), glm::vec3(0, 0, 0.7))
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
            1, 3, 2,
            2, 3, 7,
            2, 7, 6,
            1, 7, 3,
            1, 5, 7,
            6, 7, 4,
            7, 5, 4,
            0, 4, 1,
            1, 4, 5,
            2, 6, 4,
            0, 2, 4

        };

        CreateMesh("cube_E", vertices, indices);
    }

    // creez un cub pentru a reprezenta peretii labirintului
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 0, 1), glm::vec3(0, 1, 1), glm::vec3(1, 1, 1)),
            VertexFormat(glm::vec3(1, 0, 1), glm::vec3(0, 1, 1), glm::vec3(1, 1, 1)),
            VertexFormat(glm::vec3(0, 1, 1), glm::vec3(0, 1, 1), glm::vec3(1, 1, 1)),
            VertexFormat(glm::vec3(1, 1, 1), glm::vec3(0, 1, 1), glm::vec3(1, 1, 1)),
            VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0, 1, 1), glm::vec3(1, 1, 1)),
            VertexFormat(glm::vec3(1, 0, 0), glm::vec3(0, 1, 1), glm::vec3(1, 1, 1)),
            VertexFormat(glm::vec3(0, 1, 0), glm::vec3(0, 1, 1), glm::vec3(1, 1, 1)),
            VertexFormat(glm::vec3(1, 1, 0), glm::vec3(0, 1, 1), glm::vec3(1, 1, 1))
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
            1, 3, 2,
            2, 3, 7,
            2, 7, 6,
            1, 7, 3,
            1, 5, 7,
            6, 7, 4,
            7, 5, 4,
            0, 4, 1,
            1, 4, 5,
            2, 6, 4,
            0, 2, 4

        };

        CreateMesh("cube_F", vertices, indices);
    }

    // creez un cub pentru a reprezenta podeaua labirintului
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 0, 1), glm::vec3(0, 1, 1), glm::vec3(0.8, 0.8, 0)),
            VertexFormat(glm::vec3(1, 0, 1), glm::vec3(0, 1, 1), glm::vec3(0.8, 0.8, 0)),
            VertexFormat(glm::vec3(0, 1, 1), glm::vec3(0, 1, 1), glm::vec3(0.8, 0.8, 0)),
            VertexFormat(glm::vec3(1, 1, 1), glm::vec3(0, 1, 1), glm::vec3(0.8, 0.8, 0)),
            VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0, 1, 1), glm::vec3(0.8, 0.8, 0)),
            VertexFormat(glm::vec3(1, 0, 0), glm::vec3(0, 1, 1), glm::vec3(0.8, 0.8, 0)),
            VertexFormat(glm::vec3(0, 1, 0), glm::vec3(0, 1, 1), glm::vec3(0.8, 0.8, 0)),
            VertexFormat(glm::vec3(1, 1, 0), glm::vec3(0, 1, 1), glm::vec3(0.8, 0.8, 0))
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
            1, 3, 2,
            2, 3, 7,
            2, 7, 6,
            1, 7, 3,
            1, 5, 7,
            6, 7, 4,
            7, 5, 4,
            0, 4, 1,
            1, 4, 5,
            2, 6, 4,
            0, 2, 4

        };

        CreateMesh("cube_G", vertices, indices);
    }

    // creez un cub pentru a reprezenta primul dreptunghi al hud-ului
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 0, 1), glm::vec3(0, 1, 1), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(1, 0, 1), glm::vec3(0, 1, 1), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(0, 1, 1), glm::vec3(0, 1, 1), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(1, 1, 1), glm::vec3(0, 1, 1), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0, 1, 1), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(1, 0, 0), glm::vec3(0, 1, 1), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(0, 1, 0), glm::vec3(0, 1, 1), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(1, 1, 0), glm::vec3(0, 1, 1), glm::vec3(0, 0, 0))
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
            1, 3, 2,
            2, 3, 7,
            2, 7, 6,
            1, 7, 3,
            1, 5, 7,
            6, 7, 4,
            7, 5, 4,
            0, 4, 1,
            1, 4, 5,
            2, 6, 4,
            0, 2, 4

        };

        CreateMesh("cube_H", vertices, indices);
    }

    // creez un cub pentru a reprezenta al doilea dreptunghi al hud-ului
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 0, 1), glm::vec3(0, 1, 1), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(1, 0, 1), glm::vec3(0, 1, 1), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(0, 1, 1), glm::vec3(0, 1, 1), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(1, 1, 1), glm::vec3(0, 1, 1), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0, 1, 1), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(1, 0, 0), glm::vec3(0, 1, 1), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(0, 1, 0), glm::vec3(0, 1, 1), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(1, 1, 0), glm::vec3(0, 1, 1), glm::vec3(1, 0, 0))
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
            1, 3, 2,
            2, 3, 7,
            2, 7, 6,
            1, 7, 3,
            1, 5, 7,
            6, 7, 4,
            7, 5, 4,
            0, 4, 1,
            1, 4, 5,
            2, 6, 4,
            0, 2, 4

        };

        CreateMesh("cube_I", vertices, indices);
    }

    // creez un cub pentru a reprezenta al doilea dreptunghi al timpului ramas
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 0, 1), glm::vec3(0, 1, 1), glm::vec3(0, 0, 1)),
            VertexFormat(glm::vec3(1, 0, 1), glm::vec3(0, 1, 1), glm::vec3(0, 0, 1)),
            VertexFormat(glm::vec3(0, 1, 1), glm::vec3(0, 1, 1), glm::vec3(0, 0, 1)),
            VertexFormat(glm::vec3(1, 1, 1), glm::vec3(0, 1, 1), glm::vec3(0, 0, 1)),
            VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0, 1, 1), glm::vec3(0, 0, 1)),
            VertexFormat(glm::vec3(1, 0, 0), glm::vec3(0, 1, 1), glm::vec3(0, 0, 1)),
            VertexFormat(glm::vec3(0, 1, 0), glm::vec3(0, 1, 1), glm::vec3(0, 0, 1)),
            VertexFormat(glm::vec3(1, 1, 0), glm::vec3(0, 1, 1), glm::vec3(0, 0, 1))
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
            1, 3, 2,
            2, 3, 7,
            2, 7, 6,
            1, 7, 3,
            1, 5, 7,
            6, 7, 4,
            7, 5, 4,
            0, 4, 1,
            1, 4, 5,
            2, 6, 4,
            0, 2, 4

        };

        CreateMesh("cube_J", vertices, indices);
    }


    // creez o sfera pentru un proiectil
    {
        Mesh* mesh = new Mesh("sphere");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // creez un tetraedru pentru a reprezenta un inamic
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0.2f, 0, 0.2f), glm::vec3(1, 0, 0.2), glm::vec3(1, 0.1, 0.2)),         
            VertexFormat(glm::vec3(0.8f, 0, 0.2f), glm::vec3(1, 0, 0.2), glm::vec3(1, 0.1, 0.2)),         
            VertexFormat(glm::vec3(0.8f, 0, 0.8f), glm::vec3(1, 0, 0.2), glm::vec3(1, 0.1, 0.2)),         
            VertexFormat(glm::vec3(0.2f, 0, 0.8f), glm::vec3(1, 0, 0.2), glm::vec3(1, 0.1, 0.2)),         
            VertexFormat(glm::vec3(0.625f, 0.425f, 0.625f), glm::vec3(1, 0, 0.2), glm::vec3(0.2, 0.1, 0.2)) 
        };

        vector<unsigned int> indices =
        {
            0, 4, 1,
            1, 4, 2,
            2, 4, 3,
            3, 4, 0,
            0, 1, 2,
            2, 3, 0
        };

        CreateMesh("tetr_A", vertices, indices);
    }

    xMinInamic = 0.2f;
    xMaxInamic = 0.8f;
    yInamic = 0.625f;

    // Create a shader program for drawing face polygon with the color of the normal
    {
        Shader* shader = new Shader("EnemyShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    left = -1;
    right = 1;
    bottom = -1;
    top = 1;
    zNear = 0.01f;
    zFar = 100.0f;

    hudMatrix = glm::ortho(left, right, bottom, top, zNear, zFar);
    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, zNear, zFar);
}

void Tema2::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices)
{
    unsigned int VAO = 0;
    glGenVertexArrays(1, &VAO); // generare VAO
    glBindVertexArray(VAO);     // legare VAO

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Send vertices data into the VBO buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    unsigned int IBO;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    // Send indices data into the IBO buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

    // ========================================================================
    // This section demonstrates how the GPU vertex shader program
    // receives data. It will be learned later, when GLSL shaders will be
    // introduced. For the moment, just think that each property value from
    // our vertex format needs to be sent to a certain channel, in order to
    // know how to receive it in the GLSL vertex shader.

    // Set vertex position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

    // Set vertex normal attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

    // Set texture coordinate attribute
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

    // Set vertex color attribute
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
    // ========================================================================

    // Unbind the VAO
    glBindVertexArray(0);

    // Check for OpenGL errors
    if (GetOpenGLError() == GL_INVALID_OPERATION)
    {
        cout << "\t[NOTE] : For students : DON'T PANIC! This error should go away when completing the tasks." << std::endl;
        cout << "\t[NOTE] : For developers : This happens because OpenGL core spec >=3.1 forbids null VAOs." << std::endl;
    }

    // Mesh information is saved into a Mesh object
    meshes[name] = new Mesh(name);
    meshes[name]->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));
    meshes[name]->vertices = vertices;
    meshes[name]->indices = indices;
}


void Tema2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Sets the screen area where to draw
    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema2::CreareJucator() {
    float dx, dz;

    if (renderCameraTarget == true) {
        dx = translateX - oldTranslateX;
        dz = translateZ - oldTranslateZ;

        coordX += dx * cos(angularStepThird) + dz * sin(angularStepThird);
        coordZ += -dx * sin(angularStepThird) + dz * cos(angularStepThird);

       // Folosesc aceasta matrice de translatie pentru fiecare parte a jucatorului (este comuna)
        glm::mat4 modelMatrixCommon = glm::mat4(1);
        modelMatrixCommon *= transform3D::Translate(coordX, translateY, coordZ);
        modelMatrixCommon *= transform3D::Translate(positionX, positionY, positionZ);
        modelMatrixCommon *= transform3D::RotateOY(angularStepThird);
        modelMatrixCommon *= transform3D::Translate(-(positionX), -positionY, -(positionZ));

        // desenez tricoul jucatorului
        modelMatrix = modelMatrixCommon;
        modelMatrix *= transform3D::Translate(positionX, positionY, positionZ);
        modelMatrix *= transform3D::Scale(scale1, scale1, scale1);

        RenderMesh(meshes["cube_A"], shaders["VertexNormal"], modelMatrix);

        modelMatrix = modelMatrixCommon;
        modelMatrix *= transform3D::Translate(positionX - 0.14f, positionY + 0.12f , 
                                              positionZ + 0.1f);
        modelMatrix *= transform3D::Scale(scale2, scale2, scale2);

        RenderMesh(meshes["cube_A"], shaders["VertexNormal"], modelMatrix);

        modelMatrix = modelMatrixCommon;
        modelMatrix *= transform3D::Translate(positionX + 0.3f, positionY + 0.12f, 
                                              positionZ + 0.1f);
        modelMatrix *= transform3D::Scale(scale2, scale2, scale2);

        RenderMesh(meshes["cube_A"], shaders["VertexNormal"], modelMatrix);

        // desenez capul si mainile jucatorului
        modelMatrix = modelMatrixCommon;
        modelMatrix *= transform3D::Translate(positionX + 0.08f, positionY + 0.3f,
                                              positionZ + 0.1f);
        modelMatrix *= transform3D::Scale(scale2, scale2, scale2);

        RenderMesh(meshes["cube_B"], shaders["VertexNormal"], modelMatrix);

        modelMatrix = modelMatrixCommon;
        modelMatrix *= transform3D::Translate(positionX - 0.14f, positionY - 0.02f,
                                              positionZ + 0.1f);
        modelMatrix *= transform3D::Scale(scale2, scale2, scale2);

        RenderMesh(meshes["cube_B"], shaders["VertexNormal"], modelMatrix);

        modelMatrix = modelMatrixCommon;
        modelMatrix *= transform3D::Translate(positionX + 0.3f, positionY - 0.02f,
                                              positionZ + 0.1f);
        modelMatrix *= transform3D::Scale(scale2, scale2, scale2);

        RenderMesh(meshes["cube_B"], shaders["VertexNormal"], modelMatrix);

        // desenez pantalonii jucatorului
        modelMatrix = modelMatrixCommon;
        modelMatrix *= transform3D::Translate(positionX, positionY - 0.3f , 
                                              positionZ);
        modelMatrix *= transform3D::Scale(scale3, scale1, scale4);

        RenderMesh(meshes["cube_C"], shaders["VertexNormal"], modelMatrix);

        modelMatrix = modelMatrixCommon;
        modelMatrix *= transform3D::Translate(positionX + 0.14, positionY - 0.3f, 
                                              positionZ);
        modelMatrix *= transform3D::Scale(scale3, scale1, scale4);

        RenderMesh(meshes["cube_C"], shaders["VertexNormal"], modelMatrix);

        // desenez parul jucatorului
        modelMatrix = modelMatrixCommon;
        modelMatrix *= transform3D::Translate(positionX + 0.08f, positionY + 0.44f,
                                              positionZ + 0.1f);
        modelMatrix *= transform3D::Scale(scale2, scale5, scale2);

        RenderMesh(meshes["cube_D"], shaders["VertexNormal"], modelMatrix);

        // desenez ochii jucatorului
        modelMatrix = modelMatrixCommon;
        modelMatrix *= transform3D::Translate(positionX + 0.1f, positionY + 0.4f, 
                                              positionZ + 0.25f);
        modelMatrix *= transform3D::Scale(scale6, scale6, scale7);

        RenderMesh(meshes["cube_E"], shaders["VertexNormal"], modelMatrix);

        modelMatrix = modelMatrixCommon;
        modelMatrix *= transform3D::Translate(positionX + 0.16f, positionY + 0.4f, 
                                              positionZ + 0.25f);
        modelMatrix *= transform3D::Scale(scale6, scale6, scale7);

        RenderMesh(meshes["cube_E"], shaders["VertexNormal"], modelMatrix);

        oldTranslateX = translateX;
        oldTranslateZ = translateZ;

        yJucator = 0.8f;
    }
}

void Tema2::CreareHUD() {

    // creez al doilea dreptunghi al healthbar-ului
    h2.modelMatrix = glm::mat4(1);
    h2.modelMatrix *= transform3D::Translate(coordX, translateY, coordZ);
    h2.modelMatrix *= transform3D::Translate(positionX, positionY, positionZ);
    h2.modelMatrix *= transform3D::RotateOY(angularStepThird);
    h2.modelMatrix *= transform3D::Translate(-(positionX), -positionY, -(positionZ));
    h2.modelMatrix *= transform3D::Translate(positionX + 0.3f, 1, positionZ + 0.3f);
    h2.modelMatrix *= transform3D::Scale(h2.scaleX, 0.2, 0);

    if (h2.scaleX > 0) {
        RenderMeshHUD(meshes["cube_I"], shaders["VertexNormal"], h2.modelMatrix);
    }

    // creez primul dreptunghi al healthbar-ului
    h1.modelMatrix = glm::mat4(1);
    h1.modelMatrix *= transform3D::Translate(coordX, translateY, coordZ);
    h1.modelMatrix *= transform3D::Translate(positionX, positionY, positionZ);
    h1.modelMatrix *= transform3D::RotateOY(angularStepThird);
    h1.modelMatrix *= transform3D::Translate(-(positionX), -positionY, -(positionZ));
    h1.modelMatrix *= transform3D::Translate(positionX + 0.3f, 1, positionZ + 0.3f);
    h1.modelMatrix *= transform3D::Scale(h1.scaleX, 0.2, 0);
 
    RenderMeshHUD(meshes["cube_H"], shaders["VertexNormal"], h1.modelMatrix);

    // creez al doilea dreptunghi al timpului ramas
    h3.modelMatrix = glm::mat4(1);
    h3.modelMatrix *= transform3D::Translate(coordX, translateY, coordZ);
    h3.modelMatrix *= transform3D::Translate(positionX, positionY, positionZ);
    h3.modelMatrix *= transform3D::RotateOY(angularStepThird);
    h3.modelMatrix *= transform3D::Translate(-(positionX), -positionY, -(positionZ));
    h3.modelMatrix *= transform3D::Translate(positionX + 0.3f, 0.7f, positionZ + 0.3f);
    h3.modelMatrix *= transform3D::Scale(h3.scaleX, 0.2, 0);

    if (h3.scaleX > 0) {
        RenderMeshHUD(meshes["cube_J"], shaders["VertexNormal"], h3.modelMatrix);
    }

    // creez primul dreptunghi al timpului ramas
    h1.modelMatrix = glm::mat4(1);
    h1.modelMatrix *= transform3D::Translate(coordX, translateY, coordZ);
    h1.modelMatrix *= transform3D::Translate(positionX, positionY, positionZ);
    h1.modelMatrix *= transform3D::RotateOY(angularStepThird);
    h1.modelMatrix *= transform3D::Translate(-(positionX), -positionY, -(positionZ));
    h1.modelMatrix *= transform3D::Translate(positionX + 0.3f, 0.7f, positionZ + 0.3f);
    h1.modelMatrix *= transform3D::Scale(h1.scaleX, 0.2, 0);

    RenderMeshHUD(meshes["cube_H"], shaders["VertexNormal"], h1.modelMatrix);
}

void Tema2::CreareLabirint(string numeFisier) {
    ifstream fin(numeFisier);

    if (!fin)
    {
        cout << "Eroare la citirea din fisier!" << endl;
        return;
    }

    int row = 0, column = 0, value;

    while (row < mazeSize) {
        column = 0;

        while (column < mazeSize) {
            fin >> value;

            if (value == 1) {
                Labirint lab = Labirint(beginPosition.x, beginPosition.z, glm::mat4(1));
                labirint.push_back(lab);
            }
            else if (value == 0) {
                positions.push_back(beginPosition);
                Podea p = Podea(beginPosition.x, beginPosition.z, glm::mat4(1));
                podea.push_back(p);
            }
            else if (value == 2) {
                Inamic inamic = Inamic(0, glm::mat4(1), beginPosition.x, beginPosition.z);
                inamici.push_back(inamic);
                Podea p = Podea(beginPosition.x, beginPosition.z, glm::mat4(1));
                podea.push_back(p);
            }

            if (column == mazeSize - 1) {
                beginPosition = glm::vec3(beginPosition.x - mazeSize + 1, beginPosition.y, beginPosition.z + 1);
            }
            else {
                beginPosition = glm::vec3(beginPosition.x + 1, beginPosition.y, beginPosition.z);
            }
            
            column++;
        }
        
        row++;
    }

    fin.close();
}

void Tema2::GenerareLabirint() {
    for (int i = 0; i < labirint.size(); i++) {

        labirint[i].modelMatrix = glm::mat4(1);
        labirint[i].modelMatrix *= transform3D::Translate(labirint[i].translateX, 0, labirint[i].translateZ);

        RenderMesh(meshes["cube_F"], shaders["VertexNormal"], labirint[i].modelMatrix);
    }
}

void Tema2::GenerarePodea() {
    for (int i = 0; i < podea.size(); i++) {
        podea[i].modelMatrix = glm::mat4(1);
        podea[i].modelMatrix *= transform3D::Translate(podea[i].translateX, 0, podea[i].translateZ);
        podea[i].modelMatrix *= transform3D::Scale(1, 0, 1);

        RenderMesh(meshes["cube_G"], shaders["VertexNormal"], podea[i].modelMatrix);
    }
}

void Tema2::CreareInamici(float deltaTimeSeconds, int index) {
    for (int i = 0; i < inamici.size(); i++) {

        inamici[i].angle += deltaTimeSeconds * EnemySpeed;

        inamici[i].modelMatrix = glm::mat4(1);
        inamici[i].modelMatrix *= transform3D::Translate(inamici[i].translateX, 0, inamici[i].translateZ);
        
        if (index != i) {
            inamici[i].modelMatrix *= transform3D::Translate(0.5f, 0, 0.5f);
            inamici[i].modelMatrix *= transform3D::RotateOY(inamici[i].angle);
            inamici[i].modelMatrix *= transform3D::Translate(-0.5f, 0, -0.5f);
        }
        

        if (inamici[i].colisionProjectile == false) {
            if (index != -1 && i == index) {
                RenderMeshInamic(meshes["tetr_A"], shaders["EnemyShader"], inamici[i].modelMatrix, true);
            }
            else {
                RenderMeshInamic(meshes["tetr_A"], shaders["EnemyShader"], inamici[i].modelMatrix, false);
            }
        }
    }
}

bool Tema2::ColiziuneJucatorPereteHarta() {
    float aMinX, aMaxX, aMinY, aMaxY, aMinZ, aMaxZ, bMinX, bMaxX, bMinY, bMaxY, bMinZ, bMaxZ;

    // cubul a este jucatorul
    aMinX = positionX + coordX - scale2;
    aMaxX = positionX + coordX + scale1 + scale2;

    aMinZ = positionZ + coordZ;
    aMaxZ = positionZ + coordZ + scale1;

    aMinY = 0;
    aMaxY = yJucator;

    glm::mat4 matrix1 = glm::mat4(1);
    matrix1 *= transform3D::Translate(aMinX, aMinY, aMinZ);
    glm::mat4 matrix2 = glm::mat4(1);
    matrix2 *= transform3D::Translate(aMaxX, aMaxY, aMaxZ);

    RenderMesh(meshes["sphere"], shaders["VertexNormal"], matrix1);
    RenderMesh(meshes["sphere"], shaders["VertexNormal"], matrix2);

    for (int i = 0; i < labirint.size(); i++) {
        // cubul b este un perete al labirintului

        bMinX = labirint[i].translateX;
        bMaxX = labirint[i].translateX + 1;

        bMinY = 0;
        bMaxY = 1;

        bMinZ = labirint[i].translateZ;
        bMaxZ = labirint[i].translateZ + 1;

        if ((aMinZ <= bMaxZ && aMaxZ >= bMinZ) &&
            (aMinX <= bMaxX && aMaxX >= bMinX) &&
            (aMinY <= bMaxY && aMaxY >= bMinY)) {

            return true;
        }
    }

    return false;
}

int Tema2::ColiziuneProiectilInamici(Proiectil proiectil) {
    float pointX, pointY, pointZ;
    float minX, maxX, minY, maxY, minZ, maxZ;

    pointX = proiectil.center.x + proiectil.translateX;
    pointY = proiectil.center.y + proiectil.radix;
    pointZ = proiectil.center.z + proiectil.translateZ;

    for (int i = 0; i < inamici.size(); i++) {
        minX = xMinInamic + inamici[i].translateX;
        maxX = xMaxInamic + inamici[i].translateX;

        minY = 0.0f;
        maxY = yInamic;

        minZ = xMinInamic + inamici[i].translateZ;
        maxZ = xMaxInamic + inamici[i].translateZ;

        if (((pointX + proiectil.radix >= minX && pointX + proiectil.radix <= maxX)
            || (pointX - proiectil.radix >= minX && pointX - proiectil.radix <= maxX)) &&
            (pointY >= minY && pointY <= maxY) &&
            ((pointZ + proiectil.radix >= minZ && pointZ + proiectil.radix <= maxZ)
                || (pointZ - proiectil.radix >= minZ && pointZ - proiectil.radix <= maxZ))) {

            return i;
        }
    }

    return -1;
}

int Tema2::ColiziuneJucatorInamici() {
    float aMinX, aMaxX, aMinY, aMaxY, aMinZ, aMaxZ, bMinX, bMaxX, bMinY, bMaxY, bMinZ, bMaxZ;

    // cubul a este jucatorul
    aMinX = positionX + coordX - scale2;
    aMaxX = positionX + coordX + scale1 + scale2;

    aMinZ = positionZ + coordZ;
    aMaxZ = positionZ + coordZ + scale1;

    aMinY = 0;
    aMaxY = yJucator;

    for (int i = 0; i < inamici.size(); i++) {
        bMinX = inamici[i].translateX + xMinInamic;
        bMaxX = inamici[i].translateX + xMaxInamic;

        bMinY = 0;
        bMaxY = yInamic;

        bMinZ = inamici[i].translateZ + xMinInamic;
        bMaxZ = inamici[i].translateZ + xMaxInamic;

        if ((aMinZ <= bMaxZ && aMaxZ >= bMinZ) &&
            (aMinX <= bMaxX && aMaxX >= bMinX) &&
            (aMinY <= bMaxY && aMaxY >= bMinY)) {
            
            return i;
        }
    }

    return -1;
}

bool Tema2::ColisiuneProiectilPereteHarta(Proiectil proiectil) {
    float pointX, pointY, pointZ;
    float minX, maxX, minY, maxY, minZ, maxZ;

    pointX = proiectil.center.x + proiectil.translateX;
    pointY = proiectil.center.y + proiectil.radix;
    pointZ = proiectil.center.z + proiectil.translateZ;

    for (int i = 0; i < labirint.size(); i++) {
        minX = labirint[i].translateX;
        maxX = labirint[i].translateX + 1;

        minY = 0.0f;
        maxY = 1;

        minZ =labirint[i].translateZ;
        maxZ = labirint[i].translateZ + 1;

        if (((pointX + proiectil.radix >= minX && pointX + proiectil.radix <= maxX)
            || (pointX - proiectil.radix >= minX && pointX - proiectil.radix <= maxX)) &&
            (pointY >= minY && pointY <= maxY) &&
            ((pointZ + proiectil.radix >= minZ && pointZ + proiectil.radix <= maxZ)
                || (pointZ - proiectil.radix >= minZ && pointZ - proiectil.radix <= maxZ))) {
            return true;
        }
    }

    return false;
}

void Tema2::LansareProiectile(float deltaTimeSeconds) {
    int i;
    bool coliziunePereteHarta = false;
    float distanta;

    for (i = 0; i < proiectile.size(); i++) {
        proiectile[i].modelMatrix = glm::mat4(1);
        proiectile[i].modelMatrix *= transform3D::Translate(proiectile[i].translateX, proiectile[i].translateY, proiectile[i].translateZ);
        proiectile[i].modelMatrix *= transform3D::Scale(0.2f, 0.2f, 0.2f);

        if (index2 == -1) {
            proiectile[i].translateX += speedProjectile * proiectile[i].direction.x * deltaTimeSeconds;
            proiectile[i].translateZ += speedProjectile * proiectile[i].direction.z * deltaTimeSeconds;
        }

        index2 = ColiziuneProiectilInamici(proiectile[i]);
        coliziunePereteHarta = ColisiuneProiectilPereteHarta(proiectile[i]);
        distanta = sqrt(pow(proiectile[i].translateX - (positionX + coordX), 2) + pow(proiectile[i].translateZ - (positionZ + coordZ), 2));

        if (index2 != -1) {
            coliziuneInamic = true;
            if (x2 > 60 * deltaTimeSeconds) {
                proiectile.erase(proiectile.begin() + i);
                inamici.erase(inamici.begin() + index2);
                coliziuneInamic = false;
                x2 = 0;
                index2 = -1;
            }
            else {
                x2 += deltaTimeSeconds;
            }
        }
        else if (coliziunePereteHarta == true) {
            proiectile.erase(proiectile.begin() + i);
        }
        else if (distanta >= distantaMaxima) {
            proiectile.erase(proiectile.begin() + i);
        }
        else {
            RenderMesh(meshes["sphere"], shaders["VertexNormal"], proiectile[i].modelMatrix);
        }
    }
}

void Tema2::Update(float deltaTimeSeconds)
{
    beginPosition = glm::vec3(-10.0f, 0, -10.0f);
    
    glLineWidth(3);
    glPointSize(5);

    if ((h3.scaleX <= 0 || h2.scaleX - 0.1f <= 0 
        || positionX + coordX < -10.0f || positionX + coordX > 10.0f
        || positionZ + coordZ < -10.0f || positionZ + coordZ > 10.0f) && (semafor3 == false)) {
        gameOver = true;
        cout << "++++++++++++++" << endl;
        cout << "+ GAME OVER! +" << endl;
        cout << "++++++++++++++" << endl;
        semafor3 = true;
        return;
    }

    if (semafor2 == false) {
        switch (mazeNumber) {
        case 1: CreareLabirint("src/lab_m1/Tema2/Labirint1.txt");
            break;
        case 2: CreareLabirint("src/lab_m1/Tema2/Labirint2.txt");
            break;
        case 3: CreareLabirint("src/lab_m1/Tema2/Labirint3.txt");
            break;
        case 4: CreareLabirint("src/lab_m1/Tema2/Labirint4.txt");
            break;
        case 5: CreareLabirint("src/lab_m1/Tema2/Labirint5.txt");
            break;
        case 6: CreareLabirint("src/lab_m1/Tema2/Labirint6.txt");
            break;
        case 7: CreareLabirint("src/lab_m1/Tema2/Labirint7.txt");
            break;
        case 8: CreareLabirint("src/lab_m1/Tema2/Labirint8.txt");
            break;
        case 9: CreareLabirint("src/lab_m1/Tema2/Labirint9.txt");
            break;
        case 10: CreareLabirint("src/lab_m1/Tema2/Labirint10.txt");
            break;
        default: break;
        }

        semafor2 = true;
    }

    GenerareLabirint();

    GenerarePodea();

    if (semafor1 == false) {
        posNumber = rand() % positions.size();
        semafor1 = true;

        positionX = positions[posNumber].x + 0.5f;
        positionY = positions[posNumber].y + 0.3f;
        positionZ = positions[posNumber].z + 0.5f;

        camera->Set(glm::vec3(positionX, positionY + 0.5f, positionZ - 1),
            glm::vec3(positionX, positionY, positionZ),
            glm::vec3(0, positionY + 0.5f, 0));

        float dz = -1;
        float dx = 0;
        float dy = 0.5f;

        float distanceCameraTraget = sqrt(pow(dz, 2) + pow(dy, 2) + pow(dx, 2));

        camera->distanceToTarget = distanceCameraTraget;
    }

    if (gameOver == false) {
        CreareJucator();
    }

    if (index1 != -1) {
        CreareInamici(deltaTimeSeconds, index1);
    }
    else if (index2 != -1) {
        CreareInamici(deltaTimeSeconds, index2);
    }
    else {
        CreareInamici(deltaTimeSeconds, index1);
    }

    CreareHUD();

    if (h3.scaleX > 0) {
        h3.scaleX -= 0.0001f;
    }

    if (h2.scaleX > 0) {
        index1 = ColiziuneJucatorInamici();
        if (index1 != -1) {
            coliziuneInamic = true;
            if (x1 > 60 * deltaTimeSeconds) {
                inamici.erase(inamici.begin() + index1);
                h2.scaleX -= 0.1f;
                x1 = 0;
                coliziuneInamic = false;
                index1 = -1;
            }
            else {
                x1 += deltaTimeSeconds;
            }

        }
    }

    LansareProiectile(deltaTimeSeconds);
}


void Tema2::FrameEnd()
{
    DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}

void Tema2::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
    if (!mesh || !shader || !shader->program)
        return;

    // Render an object using the specified shader and the specified position
    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
}

void Tema2::RenderMeshHUD(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
    if (!mesh || !shader || !shader->program)
        return;

    // Render an object using the specified shader and the specified position
    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(hudMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
}

void Tema2::RenderMeshInamic(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, bool coliziuneInamic)
{
    if (!mesh || !shader || !shader->program)
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    // Get shader location for uniform mat4 "Model"
    int location1 = glGetUniformLocation(shader->GetProgramID(), "Model");

    // Set shader uniform "Model" to modelMatrix
    glUniformMatrix4fv(location1, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Get shader location for uniform mat4 "View"
    int location2 = glGetUniformLocation(shader->GetProgramID(), "View");

    // Set shader uniform "View" to viewMatrix
    glm::mat4 viewMatrix = camera->GetViewMatrix();
    glUniformMatrix4fv(location2, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // Get shader location for uniform mat4 "Projection"
    int location3 = glGetUniformLocation(shader->GetProgramID(), "Projection");

    // Set shader uniform "Projection" to projectionMatrix
    glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
    glUniformMatrix4fv(location3, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    float time = Engine::GetElapsedTime();
    int location4 = glGetUniformLocation(shader->GetProgramID(), "time");
    glUniform1f(location4, time);

    int location5 = glGetUniformLocation(shader->GetProgramID(), "hit");
    glUniform1f(location5, coliziuneInamic);

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}

/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema2::OnInputUpdate(float deltaTime, int mods)
{  
    
    if (window->KeyHold(GLFW_KEY_W)) {
        if (renderCameraTarget == true) {
            colisionPlayerWall = ColiziuneJucatorPereteHarta();
           
            if (colisionPlayerWall == false || (colisionPlayerWall == true && directionChanged == true)) {
                translateZ += PlayerSpeed * deltaTime;
                camera->MoveForward(CameraSpeed * deltaTime);
                directionChanged = false;
            }
        }
    }

    if (window->KeyHold(GLFW_KEY_3)) {
        if (renderCameraTarget == true) {
            angularStepThird += deltaTime * PlayerSpeed;
            camera->RotateThirdPerson_OY(CameraSpeed * deltaTime);
        }
        else {
            angularStepFirst += deltaTime * PlayerSpeed;
            camera->RotateFirstPerson_OY(CameraSpeed * deltaTime);
        }
    }

    if (window->KeyHold(GLFW_KEY_4)) {
        if (renderCameraTarget == true) {
            angularStepThird -= deltaTime * PlayerSpeed;
            camera->RotateThirdPerson_OY(-CameraSpeed * deltaTime);
        }
        else {
            angularStepFirst -= deltaTime * PlayerSpeed;
            camera->RotateFirstPerson_OY(-CameraSpeed * deltaTime);
        }
    }
}


void Tema2::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (key == GLFW_KEY_LEFT_CONTROL) {
        renderCameraTarget = !renderCameraTarget;
        if (renderCameraTarget == false) {
            camera->MoveForward(camera->distanceToTarget);
        }
        else {
            camera->RotateFirstPerson_OY(-angularStepFirst);
            camera->MoveForward(-(camera->distanceToTarget));
            angularStepFirst = 0;
        }
    }

    if (key == GLFW_KEY_SPACE) {
        glm::vec3 translate = glm::vec3(positionX + coordX, positionY, positionZ + coordZ);
        glm::vec3 direction = glm::vec3(sin(angularStepFirst + angularStepThird), 1, cos(angularStepFirst + angularStepThird));
        Proiectil proiectil = Proiectil(glm::vec3(0, 0, 0), direction, glm::mat4(1), radixProjectile,
            translate.x, translate.y, translate.z, distanceProjectile, 0);
        proiectile.push_back(proiectil);
    }

    if (key == GLFW_KEY_A) {
        if (renderCameraTarget == true) {
            angularStepThird += M_PI / 2.0f;
            camera->RotateThirdPerson_OY(M_PI / 2.0f);
        }
        else {
            angularStepFirst += M_PI / 2.0f;
            camera->RotateFirstPerson_OY(M_PI / 2.0f);
        }

        directionChanged = true;
    }

    if (key == GLFW_KEY_D) {
        if (renderCameraTarget == true) {
            angularStepThird += -M_PI / 2.0f;
            camera->RotateThirdPerson_OY(-M_PI / 2.0f);
        }
        else {
            angularStepFirst += -M_PI / 2.0f;
            camera->RotateFirstPerson_OY(-M_PI / 2.0f);
        }
        
        directionChanged = true;
    }

    if (key == GLFW_KEY_S) {
        if (renderCameraTarget == true) {
            angularStepThird += M_PI;
            camera->RotateThirdPerson_OY(M_PI);
        }
        else {
            angularStepFirst += M_PI;
            camera->RotateFirstPerson_OY(M_PI);
        } 

        directionChanged = true;
    }

}


void Tema2::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event

}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}
