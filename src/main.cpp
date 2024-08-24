#include "graphic/mesh/Mesh.h"
#include "manager/manager.hpp"
#include "system/system.hpp"
#include "object/camera/Camera.h"
#include <glad/glad.h>
#include <thread>

#define WIDTH  1000
#define HEIGHT 1000
#define TITLE  "WINDOW"

void Init(int argc, char** argv)
{
    ResourceManager::Init(argc, argv);
    ShaderManager::  Init();
    TextureManager:: Init();

    Window::Init(WIDTH, HEIGHT, TITLE);
    Event:: Init();

    // SHADER PROGRAM

    ShaderManager::ShaderProgram::load("Main");
    ShaderManager::ShaderProgram::loadShader("Main", "\\res\\shaders\\main_vert.glsl", "\\res\\shaders\\main_frag.glsl");

    // TEXTURE

    TextureManager::TextureArray::load("Block", GL_TEXTURE0, GL_RGB, 256, 256, 32);
    TextureManager::TextureArray::loadTexture("Block", "\\res\\textures\\Block.png", 4);
}

void Terminate()
{
    ResourceManager::Terminate();
    ShaderManager  ::Terminate();
    TextureManager ::Terminate();

    Window::Terminate();
    Event ::Terminate();
}

int main(int argc, char** argv)
{
    Init(argc, argv);

    // SHADER PROGRAM //
    ShaderProgram* shader = ShaderManager::ShaderProgram::get("Main").get();

    // TEXTURE //
    TextureArray* texture = TextureManager::TextureArray::get("Block").get();

    // MESH
    Mesh mesh;
    mesh.build(
        {
            Vertex({-0.25f, -0.25f, 0.0f}, {0.0f, 0.0f}, 0),
            Vertex({ 0.25f, -0.25f, 0.0f}, {1.0f, 0.0f}, 0),
            Vertex({ 0.25f,  0.25f, 0.0f}, {1.0f, 1.0f}, 0),
            Vertex({-0.25f,  0.25f, 0.0f}, {0.0f, 1.0f}, 0),
        }, {
            0, 1, 2,
            0, 2, 3,
        }, GL_STATIC_DRAW);

    // CAMERA
    Camera camera = Camera(glm::vec3(0.0f, 0.0f, 1.0f), glm::ivec3(0), glm::vec3(0.0f), 80.0f, 0.1f, 100.0f);

    //auto stoneBlock = BlockRegistry::CreateBlock("stone");
    //if (stoneBlock) {
    //    Console::Info("Block name.", { stoneBlock->GetName() });;
    //}

    glm::mat4 model = glm::mat4(1.0f);

    float FPS = 1.0f / 100.0f;
    float crntTime = glfwGetTime();
    float delta_time;

    glEnable(GL_CULL_FACE);  // Отбражение лицевой стороны

    while (!Window::isShouldClose()) {

        // Стабилизация FPS
        {
            delta_time = glfwGetTime() - crntTime;
            if (delta_time < FPS)
                std::this_thread::sleep_for(std::chrono::milliseconds((int)(1000.0f * (FPS - delta_time))));
            crntTime += delta_time;
        }

        // Управление
        {
            if (Event::Keyboard::isPressed(GLFW_KEY_ESCAPE)) {
                Window::setShouldClose(true);
            }
            if (Event::Keyboard::isPressed(GLFW_KEY_TAB)) {
                if (Event::Mouse::isLocked())
                    Event::Mouse::lock(false);
                else
                    Event::Mouse::lock(true);
            }

            if (Event::Keyboard::isHeld(GLFW_KEY_W)) {
                camera.move(glm::vec3(0, 0, 1.0f) * delta_time);
            }
            if (Event::Keyboard::isHeld(GLFW_KEY_S)) {
                camera.move(glm::vec3(0, 0, -1.0f) * delta_time);
            }
            if (Event::Keyboard::isHeld(GLFW_KEY_D)) {
                camera.move(glm::vec3(1.0f, 0, 0) * delta_time);
            }
            if (Event::Keyboard::isHeld(GLFW_KEY_A)) {
                camera.move(glm::vec3(-1.0f, 0, 0) * delta_time);
            }
            if (Event::Keyboard::isHeld(GLFW_KEY_SPACE)) {
                camera.move(glm::vec3(0, 1.0f, 0) * delta_time);
            }
            if (Event::Keyboard::isHeld(GLFW_KEY_LEFT_SHIFT)) {
                camera.move(glm::vec3(0, -1.0f, 0) * delta_time);
            }
            if (Event::Mouse::isLocked()) {
                camera.rotate(glm::vec3(
                    -Event::Mouse::getPositionDelta().y,
                    -Event::Mouse::getPositionDelta().x,
                    0.0f
                ) * 0.05f);
            }
        }

        glClear(GL_COLOR_BUFFER_BIT);

        shader->use();
        shader->setUniform("model", model);
        shader->setUniform("projview", camera.getProjection() * camera.getView());

        texture->bind();
        mesh.render();

        Window::swapBuffer();
        Event::update();
    }

    Terminate();
    return 0;
}