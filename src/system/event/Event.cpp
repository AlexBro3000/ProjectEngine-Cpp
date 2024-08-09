#include "Event.h"
#include "../../system/console/Console.h"
#include "../../system/window/Window.h"

glm::vec2 Event::mouse_position = glm::vec2(0.0f);
glm::vec2 Event::mouse_position_delta = glm::vec2(0.0f);
glm::vec2 Event::mouse_scroll = glm::vec2(0.0f);

std::array<bool, MOUSE_BUTTON_SIZE> Event::mouse_button = { false };
std::array<bool, MOUSE_BUTTON_SIZE> Event::mouse_button_frame = { false };
std::list<int> Event::mouse_button_stack;

std::array<bool, KEY_BUTTON_SIZE> Event::key_button = { false };
std::array<bool, KEY_BUTTON_SIZE> Event::key_button_frame = { false };
std::list<int> Event::key_button_stack;

bool Event::mouse_locked  = false;
bool Event::mouse_started = false;

bool Event::Init()
{
	glfwSetCursorPosCallback(Window::window, funcCursorPosCallback);
	glfwSetScrollCallback(Window::window, funcScrollCallback);
	glfwSetMouseButtonCallback(Window::window, funcMouseButtonCallback);
	glfwSetKeyCallback(Window::window, funcKeyButtonCallback);
	glfwSetWindowSizeCallback(Window::window, funcWindowSizeCallback);

	Console::Info("Initialization of the event system completed successfully.",
		{ "The event system has initialized." });
	return true;
}

void Event::Terminate()
{
	Console::Info("Terminating the event system.",
		{ "The event system has terminated." });
}

void Event::update()
{
	for (int button : Event::mouse_button_stack) { Event::mouse_button_frame[button] = false; }
	Event::mouse_button_stack.clear();

	for (int key : Event::key_button_stack) { Event::key_button_frame[key] = false; }
	Event::key_button_stack.clear();

	Event::mouse_position_delta = glm::vec2(0.0f);
	Event::mouse_scroll = glm::vec2(0.0f);

	glfwPollEvents();
}

void Event::funcCursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
    glm::vec2 position = glm::vec2(static_cast<float>(xpos), static_cast<float>(ypos));
    if (Event::mouse_started) {
        Event::mouse_position_delta += position - Event::mouse_position;
    }
    else {
        Event::mouse_started = true;
    }
    Event::mouse_position = position;
}

void Event::funcScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	Event::mouse_scroll = glm::vec2(static_cast<float>(xoffset), static_cast<float>(yoffset));
}

void Event::funcMouseButtonCallback(GLFWwindow* window, int button, int action, int mode)
{
	if (action == GLFW_PRESS) {
		Event::mouse_button[button] = true;
		Event::mouse_button_frame[button] = true;
		Event::mouse_button_stack.push_back(button);
	}
	else if (action == GLFW_RELEASE) {
		Event::mouse_button[button] = false;
		Event::mouse_button_frame[button] = true;
		Event::mouse_button_stack.push_back(button);
	}
}

void Event::funcKeyButtonCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (action == GLFW_PRESS) {
        Event::key_button[key] = true;
        Event::key_button_frame[key] = true;
        Event::key_button_stack.push_back(key);
    }
    else if (action == GLFW_RELEASE) {
        Event::key_button[key] = false;
        Event::key_button_frame[key] = true;
        Event::key_button_stack.push_back(key);
    }
}

void Event::funcWindowSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    Window::width = width;
    Window::height = height;
}

////////////////////////////////////////////////////////////////////////////////
/////   EVENT :: MOUSE                                                     /////
////////////////////////////////////////////////////////////////////////////////

glm::vec2 Event::Mouse::getPosition()
{
	return Event::mouse_position;
}

glm::vec2 Event::Mouse::getPositionDelta()
{
	return Event::mouse_position_delta;
}

glm::vec2 Event::Mouse::getScroll()
{
	return Event::mouse_scroll;
}

bool Event::Mouse::isPressed(int button)
{
	if (isValidButton(button))
		return Event::mouse_button[button] && Event::mouse_button_frame[button];
	return false;
}

bool Event::Mouse::isReleased(int button)
{
    if (isValidButton(button))
        return !Event::mouse_button[button] && Event::mouse_button_frame[button];
	return false;
}

bool Event::Mouse::isHeld(int button)
{
    if (isValidButton(button))
        return Event::mouse_button[button];
	return false;
}

void Event::Mouse::lock(bool lock)
{
    Event::mouse_locked = lock;
    if (lock) {
        glfwSetInputMode(Window::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    else {
        glfwSetInputMode(Window::window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

bool Event::Mouse::isLocked()
{
    return Event::mouse_locked;
}

bool Event::Mouse::isValidButton(int button)
{
    return button >= 0 && button < MOUSE_BUTTON_SIZE;
}

////////////////////////////////////////////////////////////////////////////////
/////   EVENT :: KEYBOARD                                                  /////
////////////////////////////////////////////////////////////////////////////////

bool Event::Keyboard::isPressed(int key)
{
    if (isValidKey(key))
        return Event::key_button[key] && Event::key_button_frame[key];
	return false;
}

bool Event::Keyboard::isReleased(int key)
{
    if (isValidKey(key))
        return !Event::key_button[key] && Event::key_button_frame[key];
	return false;
}

bool Event::Keyboard::isHeld(int key)
{
    if (isValidKey(key))
        return Event::key_button[key];
	return false;
}

bool Event::Keyboard::isValidKey(int key)
{
    return key >= 0 && key < KEY_BUTTON_SIZE;
}