#include "lab_m1/Tema3/Tema3.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema3::Tema3()
{
}


Tema3::~Tema3()
{
}


void Tema3::Init()
{

    generarePodea = false;
    
    {
        Mesh* mesh = new Mesh("box");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("sphere");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // Create a shader program for drawing face polygon with the color of the normal
    {
        Shader *shader = new Shader("Tema3Shader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    // Light & material properties
    {
        lightPosition = glm::vec3(0, 1, 1);
        materialShininess = 30;
        materialKd = 0.5;
        materialKs = 0.5;
        materialKe = 0.5;
    }
}


void Tema3::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema3::GenerarePodea() {
    glm::vec3 pozitieCurenta = glm::vec3(-2.0f, 0.0f, -2.0f);
    float coltStangaJosPodea = pozitieCurenta.z;
    glm::vec3 culoare;

    for (float i = 0; i < 8; i++) {
        for (float j = 0; j < 8; j++) {
            culoare = glm::vec3(rand() % 2, rand() % 2, rand() % 2);
            if (culoare.x != 0 && culoare.y != 0 && culoare.z != 0) {
                culoriPodea.push_back(culoare);
            }
            else {
                while (culoare.x == 0 && culoare.y == 0 && culoare.z == 0) {
                    culoare = glm::vec3(rand() % 2, rand() % 2, rand() % 2);
                }
                culoriPodea.push_back(culoare);
            }
            pozitieCurenta = glm::vec3(pozitieCurenta.x, pozitieCurenta.y, coltStangaJosPodea + j * 0.5f);
            pozitiiPodea.push_back(pozitieCurenta);
        }
        pozitieCurenta = glm::vec3(pozitieCurenta.x + 0.5f, pozitieCurenta.y, coltStangaJosPodea);
    }
}

void Tema3::CrearePodea() {
    for (int i = 0; i < pozitiiPodea.size(); i++) {
        PodeaRing patrat = PodeaRing(pozitiiPodea[i].x, pozitiiPodea[i].y, pozitiiPodea[i].z, 1, 0, 1, glm::mat4(1));

        patrat.modelMatrix *= glm::scale(patrat.modelMatrix, glm::vec3(patrat.scaleX, patrat.scaleY, patrat.scaleZ));
        patrat.modelMatrix *= glm::translate(patrat.modelMatrix, glm::vec3(patrat.translateX + 0.25f, patrat.translateY, patrat.translateZ + 0.25f));
        RenderSimpleMesh(meshes["box"], shaders["Tema3Shader"], patrat.modelMatrix, culoriPodea[i]);
    }
}

void Tema3::GenerarePereteStang() {
    glm::vec3 pozitieCurenta = glm::vec3(-1.0f, 0.0f, -1.0f);
    float coltStangaJosPereteStang = pozitieCurenta.y;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 5; j++) {
            pozitieCurenta = glm::vec3(pozitieCurenta.x, coltStangaJosPereteStang + j * 0.25f, pozitieCurenta.z);
            pozitiiPereteStang.push_back(pozitieCurenta);
        }

        pozitieCurenta = glm::vec3(pozitieCurenta.x, coltStangaJosPereteStang, pozitieCurenta.z + 0.25f);
    }

}

void Tema3::CrearePereteStang() {
    for (int i = 0; i < pozitiiPereteStang.size(); i++) {
        Perete perete = Perete(pozitiiPereteStang[i].x, pozitiiPereteStang[i].y, pozitiiPereteStang[i].z, 0, 1, 1, glm::mat4(1));

        perete.modelMatrix *= glm::translate(perete.modelMatrix, glm::vec3(perete.translateX - 1, perete.translateY, perete.translateZ + 0.1f));
        perete.modelMatrix *= glm::scale(perete.modelMatrix, glm::vec3(perete.scaleX, perete.scaleY, perete.scaleZ));
        RenderSimpleMesh(meshes["box"], shaders["Tema3Shader"], perete.modelMatrix, glm::vec3(0, 0, 0));
    }
}

void Tema3::GenerarePereteDrept() {
    glm::vec3 pozitieCurenta = glm::vec3(3.0f, 0.0f, -1.0f);
    float coltStangaJosPereteStang = pozitieCurenta.y;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 5; j++) {
            pozitieCurenta = glm::vec3(pozitieCurenta.x, coltStangaJosPereteStang + j * 0.25f, pozitieCurenta.z);
            pozitiiPereteDrept.push_back(pozitieCurenta);
        }

        pozitieCurenta = glm::vec3(pozitieCurenta.x, coltStangaJosPereteStang, pozitieCurenta.z + 0.25f);
    }
}

void Tema3::CrearePereteDrept() {
    for (int i = 0; i < pozitiiPereteDrept.size(); i++) {
        Perete perete = Perete(pozitiiPereteDrept[i].x, pozitiiPereteDrept[i].y, pozitiiPereteDrept[i].z, 0, 1, 1, glm::mat4(1));

        perete.modelMatrix *= glm::translate(perete.modelMatrix, glm::vec3(perete.translateX - 1, perete.translateY, perete.translateZ + 0.1f));
        perete.modelMatrix *= glm::scale(perete.modelMatrix, glm::vec3(perete.scaleX, perete.scaleY, perete.scaleZ));
        RenderSimpleMesh(meshes["box"], shaders["Tema3Shader"], perete.modelMatrix, glm::vec3(0, 0, 0));
    }
}

void Tema3::GenerarePereteSpate() {
    glm::vec3 pozitieCurenta = glm::vec3(-1.0f, 0.0f, -2.0f);
    float coltStangaJosPereteStang = pozitieCurenta.y;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 5; j++) {
            pozitieCurenta = glm::vec3(pozitieCurenta.x, coltStangaJosPereteStang + j * 0.25f, pozitieCurenta.z);
            PozitiiPereteSpate.push_back(pozitieCurenta);
        }

        pozitieCurenta = glm::vec3(pozitieCurenta.x + 0.25f, coltStangaJosPereteStang, pozitieCurenta.z);
    }
}

void Tema3::CrearePereteSpate() {
    for (int i = 0; i < PozitiiPereteSpate.size(); i++) {
        Perete perete = Perete(PozitiiPereteSpate[i].x, PozitiiPereteSpate[i].y, PozitiiPereteSpate[i].z, 1, 1, 0, glm::mat4(1));

        perete.modelMatrix *= glm::translate(perete.modelMatrix, glm::vec3(perete.translateX + 0.12f, perete.translateY, perete.translateZ));
        perete.modelMatrix *= glm::scale(perete.modelMatrix, glm::vec3(perete.scaleX, perete.scaleY, perete.scaleZ));
        RenderSimpleMesh(meshes["box"], shaders["Tema3Shader"], perete.modelMatrix, glm::vec3(0, 0, 0));
    }
}

void Tema3::Update(float deltaTimeSeconds)
{

    // Render the point light in the scene
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, lightPosition);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3f));
        RenderMesh(meshes["sphere"], shaders["Simple"], modelMatrix);
    }

    if (generarePodea == false) {
        GenerarePodea();
        GenerarePereteStang();
        GenerarePereteDrept();
        GenerarePereteSpate();
        generarePodea = true;
    }
    
    CrearePodea();
    CrearePereteStang();
    CrearePereteDrept();
    CrearePereteSpate();

}


void Tema3::FrameEnd()
{
    DrawCoordinateSystem();
}


void Tema3::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, const glm::vec3 &color)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    // Set shader uniforms for light & material properties
    // Set light position uniform
    GLint light_location = glGetUniformLocation(shader->program, "light_position");
    glUniform3fv(light_location, 1, glm::value_ptr(lightPosition));
    glm::vec3 eyePosition = GetSceneCamera()->m_transform->GetWorldPosition();

    // Set eye position (camera position) uniform
    GLint eye_location = glGetUniformLocation(shader->program, "eye_position");
    glUniform3fv(eye_location, 1, glm::value_ptr(eyePosition));

    // Set material property uniforms (shininess, kd, ks, object color)
    // Set material shininess
    GLint material_location = glGetUniformLocation(shader->program, "material_shininess");
    glUniform1i(material_location, materialShininess);

    // Set material_kd
    GLint kd_location = glGetUniformLocation(shader->program, "material_kd");
    glUniform1f(kd_location, materialKd);

    // Set material_ks
    GLint ks_location = glGetUniformLocation(shader->program, "material_ks");
    glUniform1f(ks_location, materialKs);

    // Set material_ke
    GLint ke_location = glGetUniformLocation(shader->program, "material_ke");
    glUniform1f(ke_location, materialKe);

    // Set color
    GLint color_location = glGetUniformLocation(shader->program, "object_color");
    glUniform3fv(color_location, 1, glm::value_ptr(color));

    // Bind model matrix
    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Bind view matrix
    glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // Bind projection matrix
    glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}

/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema3::OnInputUpdate(float deltaTime, int mods)
{
    float speed = 2;

    if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        glm::vec3 up = glm::vec3(0, 1, 0);
        glm::vec3 right = GetSceneCamera()->m_transform->GetLocalOXVector();
        glm::vec3 forward = GetSceneCamera()->m_transform->GetLocalOZVector();
        forward = glm::normalize(glm::vec3(forward.x, 0, forward.z));

        // Control light position using on W, A, S, D, E, Q
        if (window->KeyHold(GLFW_KEY_W)) lightPosition -= forward * deltaTime * speed;
        if (window->KeyHold(GLFW_KEY_A)) lightPosition -= right * deltaTime * speed;
        if (window->KeyHold(GLFW_KEY_S)) lightPosition += forward * deltaTime * speed;
        if (window->KeyHold(GLFW_KEY_D)) lightPosition += right * deltaTime * speed;
        if (window->KeyHold(GLFW_KEY_E)) lightPosition += up * deltaTime * speed;
        if (window->KeyHold(GLFW_KEY_Q)) lightPosition -= up * deltaTime * speed;
    }
}


void Tema3::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema3::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Tema3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Tema3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema3::OnWindowResize(int width, int height)
{
}
