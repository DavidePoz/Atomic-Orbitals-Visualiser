#ifndef WINDOW_H
#define WINDOW_H

// STL Headers
#include <string>

/*
 * BOILERPLATE TO HANDLE GLFW Windows
 */ 

struct GLFWwindow;

class Window {

   public:

      Window (int width, int height, const std::string& title);
      ~Window ();

      bool isOpen () const;
      void listenEvents () const;
      void swapBuffers () const;
      void clear (float r, float g, float b, float a) const;    

      int getWidth () const;
      int getHeight () const;
      GLFWwindow* getNatWindow () const;

   private:

      GLFWwindow* window_;
      int width_;
      int height_;

};

#endif
