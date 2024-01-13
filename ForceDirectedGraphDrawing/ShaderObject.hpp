#pragma once

#include <glad/glad.h>

#include <cerrno>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

std::string get_file_contents(const char* file_name);

class ShaderObject
{
private:
public:
    GLuint id;

    ShaderObject(const char* vertex_file, const char* fragment_file);

    void activate();
    void cleanup();
};