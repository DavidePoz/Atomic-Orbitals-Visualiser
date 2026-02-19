#ifndef SHADER_H
#define SHADER_H

// STL Headers
#include <string>

// GLM Headers 
#include <glm/glm.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>

class Shader {

   public:

      unsigned int ID;

      Shader (const char* vertexPath, const char* fragmentPath);
      ~Shader ();

      void use () const;

      void setBool (const std::string& name, bool value) const;
      void setInt (const std::string& name, int value) const;
      void setFloat (const std::string& name, float value) const;

      void setVec3 (const std::string& name, const glm::vec3& value) const;
      void setMat4 (const std::string& name, const glm::mat4& value) const;

   private:
      
      void checkCompileErrors (unsigned int shader, const std::string& type) const;

};

#endif
