#include "shader.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>


Shader::Shader(
    const std::string& vertexPath,
    const std::string& fragmentPath
)
{
    // 1. Read shader source files
    const std::string vertexSource = readFile(vertexPath);
    const std::string fragmentSource = readFile(fragmentPath);

    // 2. Compile shaders
    const unsigned int vertexShader =
        compileShader(GL_VERTEX_SHADER, vertexSource);

    const unsigned int fragmentShader =
        compileShader(GL_FRAGMENT_SHADER, fragmentSource);

    // 3. Create shader program
    ID = glCreateProgram();

    // 4. Attach compiled shaders to the program
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);

    // 5. Link the program
    glLinkProgram(ID);

    // Check linking errors
    int success;
    char infoLog[512];

    glGetProgramiv(ID, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(
            ID,
            sizeof(infoLog),
            nullptr,
            infoLog
        );

        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << infoLog
                  << '\n';

        glDeleteProgram(ID);

        throw std::runtime_error(
            "Failed to link shader program."
        );
    }

    // The individual shader objects are no longer needed
    // after the program has been successfully linked.
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}


Shader::~Shader()
{
    glDeleteProgram(ID);
}


void Shader::use() const
{
    glUseProgram(ID);
}


unsigned int Shader::getID() const
{
    return ID;
}


std::string Shader::readFile(const std::string& path)
{
    std::ifstream file(path);

    if (!file.is_open())
    {
        throw std::runtime_error(
            "Failed to open shader file: " + path
        );
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}


unsigned int Shader::compileShader(
    unsigned int type,
    const std::string& source
)
{
    // Create an empty shader object
    const unsigned int shader = glCreateShader(type);

    // Give OpenGL the GLSL source code
    const char* sourceCode = source.c_str();

    glShaderSource(
        shader,
        1,
        &sourceCode,
        nullptr
    );

    // Compile GLSL -> GPU shader object
    glCompileShader(shader);

    // Check compilation result
    int success;
    char infoLog[512];

    glGetShaderiv(
        shader,
        GL_COMPILE_STATUS,
        &success
    );

    if (!success)
    {
        glGetShaderInfoLog(
            shader,
            sizeof(infoLog),
            nullptr,
            infoLog
        );

        std::cerr
            << "ERROR::SHADER::COMPILATION_FAILED\n"
            << infoLog
            << '\n';

        glDeleteShader(shader);

        throw std::runtime_error(
            "Failed to compile shader."
        );
    }

    return shader;
}

void Shader::setFloat(
    const std::string& name,
    float value
) const
{
    const int location =
        glGetUniformLocation(
            ID,
            name.c_str()
        );

    glUniform1f(
        location,
        value
    );
}


void Shader::setVec2(
    const std::string& name,
    const glm::vec2& value
) const
{
    const int location =
        glGetUniformLocation(
            ID,
            name.c_str()
        );

    glUniform2f(
        location,
        value.x,
        value.y
    );
}


void Shader::setVec3(
    const std::string& name,
    const glm::vec3& value
) const
{
    const int location =
        glGetUniformLocation(
            ID,
            name.c_str()
        );

    glUniform3f(
        location,
        value.x,
        value.y,
        value.z
    );
}