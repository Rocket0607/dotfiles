#ifndef SHADER_H
#define SHADER_H

#include "../include/glad/glad.h"
#include "../include/shader.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_OK 0
#define FILE_NOT_EXIST 1
#define FILE_TOO_LARGE 2
#define FILE_READ_ERROR 3

char *c_read_file(const char *f_name, int *err, size_t *f_size)
{
  char *buffer;
  size_t length;
  FILE *f = fopen(f_name, "rb");
  size_t read_length;

  if (f) {
    fseek(f, 0, SEEK_END);
    length = ftell(f);
    fseek(f, 0, SEEK_SET);

    // 1 GiB; best not to load a whole large file in one string
    if (length > 1073741824) {
      *err = FILE_TOO_LARGE;
      printf("File is too large\n");

      return NULL;
    }

    buffer = (char *)malloc(length + 1);

    if (length) {
      read_length = fread(buffer, 1, length, f);

      if (length != read_length) {
        free(buffer);
        *err = FILE_READ_ERROR;
        printf("There was an issue reading the file\n");

        return NULL;
      }
    }

    fclose(f);

    *err = FILE_OK;
    buffer[length] = '\0';
    *f_size = length;
  }
  else {
    *err = FILE_NOT_EXIST;
    printf("File does not exist \n");
    return NULL;
  }

  return buffer;
}

void checkCompileErrors(unsigned int shader, char *type)
{
  int success;
  char infoLog[1024];
  if (strcmp(type, "PROGRAM") != 0) {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(shader, 1024, NULL, infoLog);
      printf("ERROR::SHADER_COMPILATION_ERROR of type: %s\n%s\n", type,
             infoLog);
    }
  }
  else {
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(shader, 1024, NULL, infoLog);
      printf("ERROR::PROGRAM_LINKING_ERROR of type: %s\n%s\n", type, infoLog);
    }
  }
}

unsigned int ID;

void initialiseShaders(const char *vertexPath, const char *fragmentPath)
{
  const char *vertexShaderCode;
  const char *fragmentShaderCode;
  int err;
  size_t f_size;
  // open files
  vertexShaderCode = c_read_file(vertexPath, &err, &f_size);
  fragmentShaderCode = c_read_file(fragmentPath, &err, &f_size);
  // 2. compile shaders
  unsigned int vertex, fragment;
  // vertex shader
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vertexShaderCode, NULL);
  glCompileShader(vertex);
  checkCompileErrors(vertex, "VERTEX");
  // fragment Shader
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fragmentShaderCode, NULL);
  glCompileShader(fragment);
  checkCompileErrors(fragment, "FRAGMENT");
  // shader Program
  ID = glCreateProgram();
  glAttachShader(ID, vertex);
  glAttachShader(ID, fragment);
  glLinkProgram(ID);
  checkCompileErrors(ID, "PROGRAM");
  // delete the shaders as they're linked into our program now and no longer
  // necessary
  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

void use() { glUseProgram(ID); }

void setBool(const char *name, bool value)
{
  glUniform1i(glGetUniformLocation(ID, name), (int)value);
}

void setInt(const char *name, int value)
{
  glUniform1i(glGetUniformLocation(ID, name), value);
}

void setFloat(const char *name, float value) 
{
  glUniform1f(glGetUniformLocation(ID, name), value);
}

#endif
