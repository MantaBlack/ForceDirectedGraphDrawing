#include "ShaderObject.hpp"

static const GLsizei LOG_SIZE = 512;

std::string get_file_contents(const char* file_name)
{
    std::ifstream file_stream(file_name);

    if (!file_stream.is_open())
    {
        throw std::string("Failed to read file: " + std::string(file_name));
    }

    std::stringstream buffer;
    buffer << file_stream.rdbuf();

    return std::string(buffer.str());
}

ShaderObject::ShaderObject(const char* vertex_file, const char* fragment_file)
{
    std::string vertex_code = get_file_contents(vertex_file);
    std::string fragment_code = get_file_contents(fragment_file);

    const char* vertex_source = vertex_code.c_str();
    const char* fragment_source = fragment_code.c_str();

    // specify and compile the vertex shader
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_source, NULL);
    glCompileShader(vertex_shader);

    GLint status = 0;
    char info_log[LOG_SIZE];

    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &status);

    if (!status)
    {
        glGetShaderInfoLog(vertex_shader, LOG_SIZE, NULL, info_log);
        throw std::string("Failed to compile vertex shader" + std::string(info_log));
    }

    // specify and compile the fragment shader
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_source, NULL);
    glCompileShader(fragment_shader);

    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &status);

    if (!status)
    {
        glGetShaderInfoLog(fragment_shader, LOG_SIZE, NULL, info_log);
        throw std::string("Failed to compile fragment shader" + std::string(info_log));
    }

    // create a program to use the shaders
    id = glCreateProgram();
    glAttachShader(id, vertex_shader);
    glAttachShader(id, fragment_shader);

    glLinkProgram(id);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

void ShaderObject::activate()
{
    glUseProgram(id);
}

void ShaderObject::cleanup()
{
    glDeleteProgram(id);
}
