# Установка минимальной требуемой версии CMake.
cmake_minimum_required(VERSION 3.27.9 FATAL_ERROR)

# Название проекта.
project(Project-EngineGame)

# Создание исполняемого файла проекта.
add_executable(${PROJECT_NAME} src/main.cpp)

# Указание стандарта C++17 для компиляции.
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
# Установка проекта как основного для Visual Studio.
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

# Установка параметров GLFW.
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

# Добавление поддиректории с библиотекой GLAD и связывание её с проектом.
add_subdirectory(lib/glad)
target_link_libraries(${PROJECT_NAME} glad)
# Добавление поддиректории с библиотекой GLFW и связывание её с проектом.
add_subdirectory(lib/glfw)
target_link_libraries(${PROJECT_NAME} glfw)