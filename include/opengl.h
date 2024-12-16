#ifndef __OPENGL_H__
#define __OPENGL_H__

#if defined (__APPLE_CC__)
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>
#else
#include <GL/glew.h> 
#endif

#endif  // __OPENGL_H__
