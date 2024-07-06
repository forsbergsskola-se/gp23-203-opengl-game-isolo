#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <functional>
#include <string>

class Window 
{
public:
    Window(int width, int height, const std::string& title);
    ~Window();

    void Run();
    void SetRenderFunction(std::function<void()> renderFunc);
    void SetWindowColor(float red, float green, float blue, float alpha);
    void SetTitle(const std::string& newTitle);
    GLFWwindow* GetGLFWWindow() const;
   

private:

    GLFWwindow* window;
    std::function<void()> renderFunction;
    int width_, height_;

    static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
    void InitializeGLAD();
};

#endif // WINDOW_H
