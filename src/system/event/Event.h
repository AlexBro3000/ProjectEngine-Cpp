#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <array>
#include <list>

constexpr int MOUSE_BUTTON_SIZE = 8;
constexpr int KEY_BUTTON_SIZE = 512;

class Event
{
private:
    static glm::vec2 mouse_position;
    static glm::vec2 mouse_position_delta;
    static glm::vec2 mouse_scroll;

    // MOUSE BUTTON
    static std::array<bool, MOUSE_BUTTON_SIZE> mouse_button;
    static std::array<bool, MOUSE_BUTTON_SIZE> mouse_button_frame;
    static std::list<int> mouse_button_stack;

    // KEYBOARD BUTTON
    static std::array<bool, KEY_BUTTON_SIZE> key_button;
    static std::array<bool, KEY_BUTTON_SIZE> key_button_frame;
    static std::list<int> key_button_stack;

    static bool mouse_locked;
    static bool mouse_started;

public:
    static bool Init();
    static void Terminate();
    static void update();

    class Mouse
    {
    public:
        static glm::vec2 getPosition();
        static glm::vec2 getPositionDelta();
        static glm::vec2 getScroll();

        static bool isPressed(int button);
        static bool isReleased(int button);
        static bool isHeld(int button);

        static void lock(bool lock);
        static bool isLocked();

    private:
        Mouse() = delete;
        ~Mouse() = delete;

        static bool isValidButton(int button);
    };

    class Keyboard
    {
    public:
        static bool isPressed(int key);
        static bool isReleased(int key);
        static bool isHeld(int key);

    private:
        Keyboard() = delete;
        ~Keyboard() = delete;

        static bool isValidKey(int key);
    };

private:
    Event() = delete;
    ~Event() = delete;

    static void funcCursorPosCallback(GLFWwindow* window, double xpos, double ypos);
    static void funcScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    static void funcMouseButtonCallback(GLFWwindow* window, int button, int action, int mode);
    static void funcKeyButtonCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
    static void funcWindowSizeCallback(GLFWwindow* window, int width, int height);
};