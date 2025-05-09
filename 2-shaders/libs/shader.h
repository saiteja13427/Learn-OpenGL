#ifndef SHADER_H
#define SHADER_H

#include "glad.h"

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

class Shader {
public:
    // Shader program ID
    unsigned int ID;
    Shader(const char* vertexPath, const char* fragmentPath);
    void use();
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
};

#endif