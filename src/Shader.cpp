// Custom Headers
#include "Shader.h"

// GL Headers
#include <glad/glad.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/gtc/type_ptr.hpp>

// STL Headers
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// CONSTRUCTOR
Shader::Shader (const char* vertexPath, const char* fragmentPath) {

   std::string vertexCode;
   std::string fragmentCode;
   std::ifstream vShaderFile;
   std::ifstream fShaderFile;

   // Make ifstream throw exceptions
   vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
   fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

   // Read Vertex and Fragment shader code from files
   try {

      vShaderFile.open(vertexPath);
      fShaderFile.open(fragmentPath);

      std::stringstream vShaderStream, fShaderStream;

      vShaderStream << vShaderFile.rdbuf();
      fShaderStream << fShaderFile.rdbuf();

      vShaderFile.close();
      fShaderFile.close();

      vertexCode = vShaderStream.str();
      fragmentCode = fShaderStream.str();

   } catch (std::ifstream::failure& e) {
      std::cerr << "ERROR: SHADER COULD NOT READ FILES: " << e.what() << "\n";
   }

   // Transfer to c-like strings
   const char* vShaderCode = vertexCode.c_str();
   const char* fShaderCode = fragmentCode.c_str();

   unsigned int vertex, fragment;

   // Create and compile Vertex shader
   vertex = glCreateShader(GL_VERTEX_SHADER);
   glShaderSource(vertex, 1, &vShaderCode, NULL);
   glCompileShader(vertex);
   checkCompileErrors(vertex, "VERTEX");

   // Create and compile fragment shader
   fragment = glCreateShader(GL_FRAGMENT_SHADER);
   glShaderSource(fragment, 1, &fShaderCode, NULL);
   glCompileShader(fragment);
   checkCompileErrors(fragment, "FRAGMENT");

   // Link shader program
   ID = glCreateProgram();
   glAttachShader(ID, vertex);
   glAttachShader(ID, fragment);
   glLinkProgram(ID);
   checkCompileErrors(ID, "PROGRAM");

   // Clear old shaders
   glDeleteShader(vertex);
   glDeleteShader(fragment);

};

// DESTRUCTOR
Shader::~Shader () {
   glDeleteProgram(ID);
}

// SHADER ACTIVATION
void Shader::use () const {
   glUseProgram(ID);
}

// SET FUNCTIONS
void Shader::setBool (const std::string& name, bool value) const {
   glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt (const std::string& name, int value) const {
   glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat (const std::string& name, float value) const {
   glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec3 (const std::string& name, const glm::vec3& value) const {
   glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setMat4 (const std::string& name, const glm::mat4 &value) const {
   glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

// COMPILATION ERRORS CHECKER
void Shader::checkCompileErrors (unsigned int shader, const std::string& type) const {
   int success;
   char infoLog[1024];

   if (type != "PROGRAM") {
      glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
      if (!success) {
         glGetShaderInfoLog(shader, 1024, NULL, infoLog);
         std::cerr << "ERROR: SHADER COMPILATION ERROR: " << type << "\n" << infoLog << "\n\n";
      }
   } else {
      glGetProgramiv(shader, GL_LINK_STATUS, &success);
      if (!success) {
         glGetProgramInfoLog(shader, 1024, NULL, infoLog);
         std::cerr << "ERROR: PROGRAM LINKING ERROR: " << type << "\n" << infoLog << "\n\n";
      }
   }
}
