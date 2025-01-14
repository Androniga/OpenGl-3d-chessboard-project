#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H

#include <GL/glew.h>
#include <string>

// Function to load shaders and link a program
GLuint loadShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

#endif // SHADER_LOADER_H