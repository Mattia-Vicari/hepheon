#ifndef __SHADERS_COMPILER_H__
#define __SHADERS_COMPILER_H__

#include <fstream>
#include <sstream>
#include <string>

#include "opengl.h"
#include "error.h"

namespace shaders {

/**
 * Read the source code of a shader from a file.
 * 
 * @param[in] file_path The path to the shader file.
 * @return The source code of the shader.
 */
std::string read_shader_source(const char *file_path);

/**
 * Compile a shader.
 * 
 * @param[in] type The type of the shader.
 * @param[in] source The source code of the shader.
 * @return The shader.
 */
unsigned int compile(int type, const char* source);

/**
 * Create a program from a vertex and a fragment shader.
 * 
 * @param[in] vertex_shader_path The path to the vertex shader.
 * @param[in] fragment_shader_path The path to the fragment shader.
 * @return The program.
 */
unsigned int create_program(const char* vertex_shader_path, const char* fragment_shader_path);

}  // namespace shaders

#endif  // __SHADERS_COMPILER_H__