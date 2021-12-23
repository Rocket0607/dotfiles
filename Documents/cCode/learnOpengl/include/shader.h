#ifndef SHADER_H
#define SHADER_H

#include "glad/glad.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_OK 0
#define FILE_NOT_EXIST 1
#define FILE_TO_LARGE 2
#define FILE_READ_ERROR 3


void initialiseShaders(const char *vertexPath, const char *fragmentPath);
void use();
void setBool(const char *name, bool value);
void setInt(const char *name, int value);
void setFloat(const char *name, float value);
#endif
