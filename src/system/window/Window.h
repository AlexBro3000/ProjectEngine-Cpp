#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Window
{
private:
    static GLFWwindow* window;
    static int width;
    static int height;
    static std::string title;

    friend class Event;

public:
    static bool Init(int width, int height, const std::string& title);
    static void Terminate();
    static void swapBuffer();

    static int getWidth();
    static int getHeight();

    static void setShouldClose(bool flag);

    static bool isShouldClose();

private:
    Window()  = delete;
    ~Window() = delete;
};