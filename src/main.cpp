#include "graphic/buffer/VAO.h"
#include "graphic/buffer/VBO.h"
#include "manager/manager.hpp"
#include "system/system.hpp"
#include <glad/glad.h>
#include <thread>

#define WIDTH  1000
#define HEIGHT 1000
#define TITLE  "WINDOW"

float vertices[] = {
    // x    y     z     u     v
   -0.25f,-0.25f, 0.0f, 0.0f, 0.0f,
    0.25f,-0.25f, 0.0f, 1.0f, 0.0f,
   -0.25f, 0.25f, 0.0f, 0.0f, 1.0f,

    0.25f,-0.25f, 0.0f, 1.0f, 0.0f,
    0.25f, 0.25f, 0.0f, 1.0f, 1.0f,
   -0.25f, 0.25f, 0.0f, 0.0f, 1.0f,
};

int main(int argc, char** argv)
{
    ResourceManager::Init(argc, argv);
    ShaderManager::  Init();
    TextureManager:: Init();

    Window::Init(WIDTH, HEIGHT, TITLE);
    Event:: Init();

    // SHADER PROGRAM

    ShaderManager::ShaderProgram::load("Main", "\\res\\shaders\\main_vert.glsl", "\\res\\shaders\\main_frag.glsl");
    ShaderProgram* shader = ShaderManager::ShaderProgram::get("Main").get();

    // TEXTURE

    TextureManager::Texture::load("Brick", "\\res\\textures\\brick.png", GL_TEXTURE0, GL_RGBA, GL_RGB, GL_UNSIGNED_BYTE);
    Texture* texture = TextureManager::Texture::get("Brick").get();

    // MESH

    VAO vao = VAO();
    VBO vbo = VBO();

    vao.bind();
    vbo.bind();
    vbo.setData(vertices, sizeof(vertices), GL_STATIC_DRAW);

    vao.linkAttrib(vbo, 0, 3, GL_FLOAT, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
    vao.linkAttrib(vbo, 1, 2, GL_FLOAT, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

    vao.unbind();
    vbo.unbind();



    float FPS = 1.0f / 40.0f;
    float crntTime = glfwGetTime();
    float delta_time;

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
        }

        glClear(GL_COLOR_BUFFER_BIT);

        shader->use();
        texture->bind();

        vao.bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        Window::swapBuffer();
        Event::update();
    }

    ResourceManager::Terminate();
    ShaderManager::  Terminate();
    TextureManager:: Terminate();

    Window::Terminate();
    Event:: Terminate();

    return 0;
}