#pragma once

#include <string>

#include <glad/glad.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>


class Shader
{
public:
    Shader(
        const std::string& vertexPath,
        const std::string& fragmentPath
    );

    ~Shader();

    void use() const;

    unsigned int getID() const;

    void setFloat(
        const std::string& name,
        float value
    ) const;

    void setVec2(
        const std::string& name,
        const glm::vec2& value
    ) const;

    void setVec3(
        const std::string& name,
        const glm::vec3& value
    ) const;

private:
    unsigned int ID;

    static std::string readFile(
        const std::string& path
    );

    static unsigned int compileShader(
        unsigned int type,
        const std::string& source
    );
};