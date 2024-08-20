#include "Window.h"
#include "../../system/console/Console.h"

GLFWwindow* Window::window = nullptr;
int Window::width = 0;
int Window::height = 0;
std::string Window::title = "Window";

bool Window::Init(int width, int height, const std::string& title)
{
    // Инициализация библиотеки GLFW
    if (!glfwInit()) {
        Console::Error("Window system (Init)", {
            "Error initializing window control system. Error initializing GLFM library."
            });
        return false;
    }
    glfwSetErrorCallback([](int error, const char* description) {
        Console::Error("Error initializing window control system.",
            { description });
        });
    Console::Info("Window system (Init)", {
        "Initializing the window control system. Initialization of GLFM library completed successfully."
        });

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

    // Создание окна GLFW
    Window::window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!Window::window) {
        glfwTerminate();
        Console::Error("Window system (Init)", {
            "Error initializing window control system. Error creating application window."
            });
        return false;
    }
    Console::Info("Window system (Init)", {
        "Initializing the window control system. Creation of the application window completed successfully."
        });

    glfwMakeContextCurrent(Window::window);

    // Инициализация библиотеки GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwTerminate();
        Console::Error("Window system (Init)", {
            "Error initializing window control system. Error initializing GLAD library."
            });
        return false;
    }
    Console::Info("Window system (Init)", {
        "Initializing the window control system. Initialization of GLAD library completed successfully."
        });

    glViewport(0, 0, width, height);

    // Установка параметров окна
    Window::width = width;
    Window::height = height;
    Window::title = title;

    Console::Info("Window system (Init)", {
        "Initialization of the window control system completed successfully. Display information about the OpenGL version and renderer.",
        std::string("OpenGL version: ") + reinterpret_cast<const char*>(glGetString(GL_VERSION)),
        std::string("Renderer:       ") + reinterpret_cast<const char*>(glGetString(GL_RENDERER)),
        });
    return true;
}

void Window::Terminate()
{
    glfwTerminate();
    Console::Info("Window system (Terminate)", {
        "Terminating the window control system completed successfully."
        });
}

void Window::swapBuffer()
{
    glfwSwapBuffers(Window::window);
}

int Window::getWidth()
{
    return Window::width;
}

int Window::getHeight()
{
    return Window::height;
}

void Window::setShouldClose(bool flag)
{
    glfwSetWindowShouldClose(Window::window, flag);
}

bool Window::isShouldClose()
{
    return Window::window ? glfwWindowShouldClose(Window::window) : true;
}