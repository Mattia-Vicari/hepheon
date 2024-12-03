#include "shaders/compiler.h"

std::string shaders::read_shader_source(const char *file_path) {
    std::ifstream shader_file(file_path);
    std::stringstream shader_stream;
    shader_stream << shader_file.rdbuf();
    shader_file.close();

    return shader_stream.str();
}


unsigned int shaders::compile(int type, const char* source) {
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    // Check for compilation errors
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        char info_log[512];
        glGetShaderInfoLog(shader, 512, NULL, info_log);
        logger::error("Shader compilation failed", info_log);
    }

    return shader;
}


unsigned int shaders::create_program(const char* vertex_shader_path, const char* fragment_shader_path) {
    unsigned int program;
    std::string vertex_code  = read_shader_source(vertex_shader_path);
    std::string fragment_code = read_shader_source(fragment_shader_path);

    unsigned int vertex_shader = compile(GL_VERTEX_SHADER, vertex_code.c_str());
    unsigned int fragment_shader = compile(GL_FRAGMENT_SHADER, fragment_code.c_str());

    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    // Check for linking errors
    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char info_log[512];
        glGetProgramInfoLog(program, 512, NULL, info_log);
        logger::error("Shader linking failed", info_log);
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return program;
}