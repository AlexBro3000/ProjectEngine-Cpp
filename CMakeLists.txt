# Установка минимальной требуемой версии CMake.
cmake_minimum_required(VERSION 3.27.9 FATAL_ERROR)

# Название проекта.
project(Project-EngineGame)

# Указание стандарта C++17 для компиляции.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Указание исходных файлов и ресурсов.
file(GLOB_RECURSE SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)
file(GLOB_RECURSE RESOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/res/*
)

# Группировка исходных файлов и ресурсов в структурированные каталоги для IDE.
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" PREFIX "Source" FILES ${SOURCES})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/res" PREFIX "Resource" FILES ${RESOURCES})

# Создание исполняемого файла проекта.
add_executable(${PROJECT_NAME} ${SOURCES} ${RESOURCES})

# Установка проекта как основного для Visual Studio.
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

# Установка директории вывода исполняемых файлов.
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)

# Копирование ресурсов после сборки.
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res
)

# Установка параметров для библиотек.
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

# Добавление поддиректорий с библиотеками.
add_subdirectory(lib/glad)
add_subdirectory(lib/glfw)
add_subdirectory(lib/glm)

# Связывание библиотек с проектом.
target_link_libraries(${PROJECT_NAME} glad glfw glm)

# Добавление библиотеки stb как объектной библиотеки и связывание её с проектом.
# add_library(stb INTERFACE)
# target_include_directories(stb INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/lib/stb)
# target_link_libraries(${PROJECT_NAME} stb)