#pragma once
#include <glad/glad.h>
#include <map>
#include <memory>
#include <string>

#include "../../graphic/shader/ShaderProgram.h"

class ShaderManager {
private:
    using ShaderProgramMap = std::map<std::string, std::shared_ptr<::ShaderProgram>>;
    static ShaderProgramMap shader_programs;

public:
    static bool Init();
    static void Terminate();

    class ShaderProgram {
    public:
        static bool load(const std::string& name, const std::string& path_vert, const std::string& path_frag);
        static void unload(const std::string& name);
        static std::shared_ptr<::ShaderProgram> get(const std::string& name);

    private:
        ShaderProgram() = delete;
        ~ShaderProgram() = delete;
    };

private:
    ShaderManager() = delete;
    ~ShaderManager() = delete;
};