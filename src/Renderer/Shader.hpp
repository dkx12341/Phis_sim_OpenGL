#pragma once

#include <string>

#include <glad/glad.h>

class Shader
{
public:
    Shader(const std::string& vertexPath,
           const std::string& fragmentPath);

    ~Shader();

    void use() const;

    unsigned int getID() const;

private:
    unsigned int ID;

    static std::string readFile(const std::string& path);

    static unsigned int compileShader(
        unsigned int type,
        const std::string& source
    );
};