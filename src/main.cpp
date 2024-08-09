#include "manager/manager.hpp"
#include "system/system.hpp"
#include <thread>

#define WIDTH  1200
#define HEIGHT 800
#define TITLE  "WINDOW"

int main(int argc, char** argv)
{
    ResourceManager::Init(argc, argv);
    ShaderManager::  Init();
    TextureManager:: Init();

    Window::Init(WIDTH, HEIGHT, TITLE);
    Event::Init();

    /*ShaderProgram temp = ShaderProgram(
        "C:/Users/alexb/Desktop/ProjectEngine-Cpp/build/Debug/res/shaders/main_vert.glsl",
        "C:/Users/alexb/Desktop/ProjectEngine-Cpp/build/Debug/res/shaders/main_frag.glsl"
    );*/

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

        Window::swapBuffer();
        Event::update();
    }

    ResourceManager::Terminate();
    ShaderManager::  Terminate();
    TextureManager:: Terminate();

    Window::Terminate();
    Event::Terminate();

    return 0;
}