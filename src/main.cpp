#include "graphic/batch/MeshBatch.h"
#include "graphic/batch/LineBatch.h"

#include "manager/manager.hpp"
#include "system/system.hpp"

#include "object/camera/Camera.h"
#include "world/chunk/Chunk.h"
#include "world/chunk/ChunkController.h"
#include "world/voxel/Voxel.hpp"

#include <glad/glad.h>
#include <iostream>
#include <thread>

float FPS = 1.0f / 40.0f;
float crntTime = glfwGetTime();
float delta_time;

float speed = 5.0f;

void Init(int argc, char** argv)
{
    ResourceManager::Init(argc, argv);
    ShaderManager::  Init();
    TextureManager:: Init();

    Window::Init(1000, 1000, "WINDOW");
    Event:: Init();

    // SHADER PROGRAM

    ShaderManager::ShaderProgram::load("Main", "\\res\\shaders\\main_vert.glsl", "\\res\\shaders\\main_frag.glsl");
    ShaderManager::ShaderProgram::load("ShaderLines", "\\res\\shaders\\lines_vert.glsl", "\\res\\shaders\\lines_frag.glsl");
    ShaderManager::ShaderProgram::load("Cursor", "\\res\\shaders\\cursor_vert.glsl", "\\res\\shaders\\cursor_frag.glsl");

    // TEXTURE

    TextureManager::TextureArray::load("Block", 0, GL_RGB, 256, 256, 32);
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

    glm::ivec3 world_position = glm::ivec3(0, 3, 0);
    glm::vec3 world_offset = glm::vec3(0.0f, 0.0f, 0.0f);
    


    // CAMERA
    Camera camera = Camera(world_position, world_offset, glm::vec3(0.0f, 180.0f, 0.0f), 80.0f, 0.1f, 10000.0f);

    // CHUNK CONTROLLER
    ChunkController* chunks = new ChunkController(camera.getPosition());

    // INTERFACE
    LineBatch cursor = LineBatch(glm::ivec3(0), 1.0f);
    cursor.addMesh(
        ObjSPs(glm::ivec3(0)), Mesh<VertexPoint>({
            VertexPoint(glm::vec3(-0.01f, -0.01f, 0.0f), glm::vec4(0.8f, 0.8f, 0.8f, 1.0f)),
            VertexPoint(glm::vec3( 0.01f,  0.01f, 0.0f), glm::vec4(0.8f, 0.8f, 0.8f, 1.0f)),
            VertexPoint(glm::vec3(-0.01f,  0.01f, 0.0f), glm::vec4(0.8f, 0.8f, 0.8f, 1.0f)),
            VertexPoint(glm::vec3( 0.01f, -0.01f, 0.0f), glm::vec4(0.8f, 0.8f, 0.8f, 1.0f)),
            }, { 0, 1, 2, 3 }
    ));
    cursor.build(GL_STATIC_DRAW);

    LineBatch line_batch = LineBatch(camera.getPosition(), 2.5f);
    


    // Настройка
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    while (!Window::isShouldClose()) {

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



                glm::ivec3 ray_iend;
                glm::vec3 ray_end;
                glm::vec3 norm;

                Voxel* voxel = chunks->rayCast(camera.getPosition(), camera.getOffset(), camera.getForward(), 100.0f, ray_iend, ray_end, norm);

                if (voxel != nullptr) {
                    bool flag = true;

                    if (Event::Mouse::isPressed(GLFW_MOUSE_BUTTON_1)) {
                        chunks->setVoxel(ray_iend, 0);
                        flag = false;
                    }
                    if (Event::Mouse::isPressed(GLFW_MOUSE_BUTTON_2)) {
                        chunks->setVoxel(ray_iend + (glm::ivec3)norm, 1);
                        flag = false;
                    }

                    if (flag) {
                        line_batch.addMesh(
                            ObjSPs(ray_iend), Mesh<VertexPoint>({
                                VertexPoint(glm::vec3(-0.01f, 1.01f, 1.01f), glm::vec4(0.8f, 0.8f, 0.8f, 1.0f)),
                                VertexPoint(glm::vec3(-0.01f, 1.01f, -0.01f), glm::vec4(0.8f, 0.8f, 0.8f, 1.0f)),
                                VertexPoint(glm::vec3(-0.01f, -0.01f, 1.01f), glm::vec4(0.8f, 0.8f, 0.8f, 1.0f)),
                                VertexPoint(glm::vec3(-0.01f, -0.01f, -0.01f), glm::vec4(0.8f, 0.8f, 0.8f, 1.0f)),
                                VertexPoint(glm::vec3(1.01f, 1.01f, 1.01f), glm::vec4(0.8f, 0.8f, 0.8f, 1.0f)),
                                VertexPoint(glm::vec3(1.01f, 1.01f, -0.01f), glm::vec4(0.8f, 0.8f, 0.8f, 1.0f)),
                                VertexPoint(glm::vec3(1.01f, -0.01f, 1.01f), glm::vec4(0.8f, 0.8f, 0.8f, 1.0f)),
                                VertexPoint(glm::vec3(1.01f, -0.01f, -0.01f), glm::vec4(0.8f, 0.8f, 0.8f, 1.0f)),
                                VertexPoint(ray_end, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)),
                                VertexPoint(ray_end + 0.5f * norm, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)),
                                }, { 0, 1, 0, 2, 1, 3, 2, 3, 4, 5, 4, 6, 5, 7, 6, 7, 0, 4, 1, 5, 2, 6, 3, 7, 8, 9 }
                        ));
                    }
                    line_batch.build(GL_STATIC_DRAW);
                }
            }
        }

        chunks->build();

        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // CHUNK CONTROLLER
        {
            ShaderProgram* shader = ShaderManager::ShaderProgram::get("Main").get();
            shader->use();

            shader->setUniform("projview", camera.getProjection() * camera.getView());
            shader->setUniform("u_texture", 0);

            TextureManager::TextureArray::get("Block")->bind();

            for (size_t i = 0; i < CHUNK_COUNT_X * CHUNK_COUNT_Y * CHUNK_COUNT_Z; i++) {
                Chunk* chunk = chunks->getChunks()[i];
                std::shared_ptr<Mesh<VertexMesh>> mesh = chunk->getMesh();

                glm::vec3 position = (glm::vec3)(chunk->getPosition() - camera.getPosition()) - camera.getOffset() - glm::vec3(CHUNK_SIZE_X / 2, CHUNK_SIZE_Y / 2, CHUNK_SIZE_Z / 2);
                glm::mat4 model = glm::translate(glm::mat4(1.0f), position);

                shader->setUniform("model", model);
                mesh->render();
            }
        }

        // INTERFACE
        {
            glm::vec3 position = (glm::vec3)(line_batch.getPosition() - camera.getPosition()) - camera.getOffset();
            glm::mat4 model = glm::translate(glm::mat4(1.0f), position);

            ShaderProgram* shader = ShaderManager::ShaderProgram::get("ShaderLines").get();
            shader->use();
            shader->setUniform("projview", camera.getProjection() * camera.getView());
            shader->setUniform("model", model);

            line_batch.render();
            //line_batch_chunks.render();
        }

        ShaderManager::ShaderProgram::get("Cursor")->use();
        cursor.render();

        Window::swapBuffer();
        Event::update();
    }

    Terminate();
    return 0;
}



//line_batch.addMesh(
//    SimpleObject(glm::ivec3(0), glm::vec3(0.0f)),
//    Mesh<VertexPoint>({
//        VertexPoint(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)),
//        VertexPoint(glm::vec3(10000.0f, 0.0f, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)),
//        VertexPoint(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)),
//        VertexPoint(glm::vec3(0.0f, 10000.0f, 0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)),
//        VertexPoint(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)),
//        VertexPoint(glm::vec3(0.0f, 0.0f, 10000.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f))
//        }, { 0, 1, 2, 3, 4, 5 }
//));

//MeshBatch mesh_batch = MeshBatch(camera.getPosition(), glm::vec3(0.0f));
//{
//    for (size_t i = 0; i < CHUNK_COUNT_X * CHUNK_COUNT_Y * CHUNK_COUNT_Z; i++) {
//        Chunk* chunk = chunks->getChunks()[i];
//        auto* mesh = chunk->getMesh();
//        mesh_batch.addMesh(SimpleObject(chunk->getPosition(), chunk->getOffset()), *mesh);
//    }
//}
//mesh_batch.build(GL_DYNAMIC_DRAW, true);
// 
// 
// 
//ShaderProgram* shader = ShaderManager::ShaderProgram::get("Main").get();
//shader->use();
//glm::vec3 position = (glm::vec3)(mesh_batch.getPosition() - camera.getPosition()) + mesh_batch.getOffset() - camera.getOffset();
//glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
//shader->setUniform("projview", camera.getProjection() * camera.getView());
//shader->setUniform("model", model);
//shader->setUniform("u_texture", 0);
//TextureManager::TextureArray::get("Block")->bind();
//mesh_batch.render();