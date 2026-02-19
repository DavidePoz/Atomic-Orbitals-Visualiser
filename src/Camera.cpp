// Custom Headers
#include "Camera.h"

// GLM Headers
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/trigonometric.hpp>

Camera::Camera (float radius, float fov, float aspect, float rMin, float rMax)
   : radius_ {radius}, theta_ {START_THETA}, phi_ {START_PHI},
     fov_ {fov}, aspect_ {aspect}, 
     MIN_R {rMin}, MAX_R {rMax}
{
   updateCamera();
}

void Camera::handleMouseMovement (float xoff, float yoff) {
   theta_ -= xoff * MOUSE_SENS;
   phi_ += yoff * MOUSE_SENS;

   // Prevent camera flips
   if (phi_ > 89.0f) phi_ = 89.0f;
   if (phi_ < -89.0f) phi_ = -89.0f;

   updateCamera();
}

void Camera::handleScroll (float yoff) {
   radius_ -= yoff * ZOOM_SENS;

   if (radius_ < MIN_R) radius_ = MIN_R;
   if (radius_ > MAX_R) radius_ = MAX_R;

   updateCamera();
}

glm::vec3 Camera::getPosition () const {
   return position_;
}

glm::mat4 Camera::getViewMatrix () const {
   return glm::lookAt(getPosition(), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 Camera::getProjMatrix () const {
   return glm::perspective(glm::radians(fov_), aspect_, MIN_R * 0.8f, MAX_R * 1.2f );
}

void Camera::updateCamera () {
   float x = radius_ * glm::cos(glm::radians(phi_)) * glm::sin(glm::radians(theta_));
   float y = radius_ * glm::sin(glm::radians(phi_));
   float z = radius_ * glm::cos(glm::radians(phi_)) * glm::cos(glm::radians(theta_));

   position_ = glm::vec3(x, y, z);
}
