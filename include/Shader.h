#ifndef SHADER_H
#define SHADER_H

// STL Headers
#include <string>

// GLM Headers 
#include <glm/glm.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>

/**
 * Class to handle glsl shader files
 */ 
class Shader {

   public:
      
      /** Shader ID */
      unsigned int ID;

      Shader (const char* vertexPath, const char* fragmentPath);
      ~Shader ();

      /** Sets current shader program in use */
      void use () const;

      /** Set parameters in the shaders */
      void setBool (const std::string& name, bool value) const;
      void setInt (const std::string& name, int value) const;
      void setFloat (const std::string& name, float value) const;
      void setVec3 (const std::string& name, const glm::vec3& value) const;
      void setMat4 (const std::string& name, const glm::mat4& value) const;

   private:
      
      /** Internal helper: checks for compilation errors and prints them */
      void checkCompileErrors (unsigned int shader, const std::string& type) const;

};

#endif
