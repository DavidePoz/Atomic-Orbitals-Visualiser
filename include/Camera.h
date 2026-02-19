#ifndef CAMERA_H
#define CAMERA_H

// GLM Headers
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/vector_float3.hpp"

constexpr float START_THETA = 45.0f;
constexpr float START_PHI   = 30.0f;
constexpr float MOUSE_SENS  = 0.5f;
constexpr float ZOOM_SENS   = 0.5f;

class Camera {

   public:

      /**
       * Initializes a centre-looking camera
       *
       * @param radius distance from the centre of the scene 
       * @param fov camera field of view 
       * @param aspect camera aspect ratio
       * @param rMin minimum distance from the centre of the scene
       * @param rMax maximum distance from the centre of the scene
       */ 
      Camera (float radius, float fov, float aspect, float rMin = 1.0f, float rMax = 50.0f);

      /**
       * Processes mouse movement
       *
       * @param xoff offset in the x direction
       * @param yoff offset in the y direction
       */
      void handleMouseMovement (float xoff, float yoff);

      /**
       * Processes mouse wheel scroll
       *
       * @param yoff offset in the y direction
       */
      void handleScroll (float yoff);

      /**
       * Getter functions to return
       * - The view matrix
       * - The projection matrix
       * - The current camera position
       */
      glm::mat4 getViewMatrix () const;
      glm::mat4 getProjMatrix () const;
      glm::vec3 getPosition () const;

   private:

      float radius_;
      float theta_;
      float phi_;

      glm::vec3 position_;

      float fov_;
      float aspect_;

      const float MIN_R;
      const float MAX_R;

      void updateCamera ();

};

#endif
