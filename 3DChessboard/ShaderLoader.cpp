#include "ShaderLoader.h"
#include "libs.h"

GLuint loadShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
    // Add debug prints
    std::cout << "Loading vertex shader from: " << vertexShaderPath << std::endl;
    std::cout << "Loading fragment shader from: " << fragmentShaderPath << std::endl;

    // Helper to read shader source code
    auto readFile = [](const std::string& filePath) -> std::string {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            std::cerr << "Failed to open shader file: " << filePath << std::endl;
            return "";
        }
        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string content = buffer.str();
        std::cout << "Shader content length: " << content.length() << std::endl;
        return content;
        };

    // Read vertex and fragment shaders
    std::string vertexCode = readFile(vertexShaderPath);
    std::string fragmentCode = readFile(fragmentShaderPath);

    if (vertexCode.empty()) {
        std::cerr << "Vertex shader is empty!" << std::endl;
        return 0;
    }
    if (fragmentCode.empty()) {
        std::cerr << "Fragment shader is empty!" << std::endl;
        return 0;
    }

    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    // Compile vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, nullptr);
    glCompileShader(vertexShader);

    // Check vertex shader compilation
    GLint success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "Vertex Shader Compilation Error:\n" << infoLog << std::endl;
        return 0;
    }
    else {
        std::cout << "Vertex shader compiled successfully" << std::endl;
    }

    // Compile fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
    glCompileShader(fragmentShader);

    // Check fragment shader compilation
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "Fragment Shader Compilation Error:\n" << infoLog << std::endl;
        return 0;
    }
    else {
        std::cout << "Fragment shader compiled successfully" << std::endl;
    }

    // Link shaders
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check linking
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "Shader Program Linking Error:\n" << infoLog << std::endl;
        return 0;
    }
    else {
        std::cout << "Shader program linked successfully" << std::endl;
    }

    // Clean up
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}