#include "graphic/mesh/Mesh.h"
#include "manager/manager.hpp"
#include "system/system.hpp"

#include "object/camera/Camera.h"
#include "world/chunk/Chunk.h"
#include "world/chunk/ChunkController.h"

#include <glad/glad.h>
#include <iostream>
#include <thread>

#define WIDTH  1000
#define HEIGHT 1000
#define TITLE  "WINDOW"

float FPS = 1.0f / 40.0f;
float crntTime = glfwGetTime();
float delta_time;

float speed = 40.0f;



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

    //TextureManager::TextureArray::load("BlockNormal", GL_TEXTURE2, GL_RGB, 256, 256, 32);
    //TextureManager::TextureArray::loadTexture("BlockNormal", "\\res\\textures\\BlockNormal.png", 4);

    //TextureManager::TextureArray::load("BlockSpecular", GL_TEXTURE3, GL_RGB, 256, 256, 32);
    //TextureManager::TextureArray::loadTexture("BlockSpecular", "\\res\\textures\\BlockSpecular.png", 4);
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

    glm::ivec3 world_position = glm::ivec3(10000, 20, 0);          // 2 147 483 648
    glm::vec3 world_offset    = glm::vec3(0.0f, 0.0f, 0.0f);
    


    // CAMERA
    Camera camera = Camera(world_position, world_offset, glm::vec3(-90.0f, 0.0f, 0.0f), 80.0f, 0.1f, 10000.0f);

    // CHUNK CONTROLLER
    ChunkController* chunks = new ChunkController(camera.getPosition());
    chunks->build();



    // Настройка
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    while (!Window::isShouldClose()) {
        // std::cout << "Position: " << camera.getPosition().x << " " << camera.getPosition().y << " " << camera.getPosition().z << std::endl;

        // Стабилизация FPS
        {
            delta_time = glfwGetTime() - crntTime;
            if (delta_time < FPS) {
                std::this_thread::sleep_for(std::chrono::milliseconds((int)(1000.0f * (FPS - delta_time))));
                delta_time = glfwGetTime() - crntTime;
            }
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
                camera.move(glm::vec3(0, 0, 1.0f) * delta_time * speed);
            }
            if (Event::Keyboard::isHeld(GLFW_KEY_S)) {
                camera.move(glm::vec3(0, 0, -1.0f) * delta_time * speed);
            }
            if (Event::Keyboard::isHeld(GLFW_KEY_D)) {
                camera.move(glm::vec3(1.0f, 0, 0) * delta_time * speed);
            }
            if (Event::Keyboard::isHeld(GLFW_KEY_A)) {
                camera.move(glm::vec3(-1.0f, 0, 0) * delta_time * speed);
            }
            if (Event::Keyboard::isHeld(GLFW_KEY_SPACE)) {
                camera.move(glm::vec3(0, 1.0f, 0) * delta_time * speed);
            }
            if (Event::Keyboard::isHeld(GLFW_KEY_LEFT_SHIFT)) {
                camera.move(glm::vec3(0, -1.0f, 0) * delta_time * speed);
            }
            if (Event::Mouse::isLocked()) {
                camera.rotate(glm::vec3(
                    -Event::Mouse::getPositionDelta().y,
                    -Event::Mouse::getPositionDelta().x,
                    0.0f
                ) * 0.05f);
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ShaderProgram* shader = ShaderManager::ShaderProgram::get("Main").get();
        shader->use();
        shader->setUniform("projview", camera.getProjection() * camera.getView());
        shader->setUniform("u_texture", 0);

        TextureManager::TextureArray::get("Block")->bind();

        for (size_t i = 0; i < CHUNK_COUNT_X * CHUNK_COUNT_Y * CHUNK_COUNT_Z; i++) {
            Chunk* chunk = chunks->getChunks()[i];
            Mesh* mesh = chunk->getMesh();

            glm::vec3 position = (glm::vec3)(chunk->getPosition() - camera.getPosition()) + chunk->getOffset() - camera.getOffset() - 15.5f;
            glm::mat4 model = glm::translate(glm::mat4(1.0f), position);

            shader->setUniform("model", model);
            mesh->render();
        }

        Window::swapBuffer();
        Event::update();
    }

    delete chunks;

    Terminate();
    return 0;
}