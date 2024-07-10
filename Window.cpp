#include "Window.h"
Window::Window(int width, int height, const std::string& title)
    : width_(width), height_(height), window(nullptr), renderFunction(nullptr)
{
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Using OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // For MacOS compatibility

    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

    InitializeGLAD();
}
GLFWwindow* Window::GetGLFWWindow() const {
    return window;
}
Window::~Window() 
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::Run() {
   

    while (!glfwWindowShouldClose(window)) 
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        if (renderFunction) 
        {
            renderFunction();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
}

void Window::SetRenderFunction(std::function<void()> renderFunc) 
{
    renderFunction = renderFunc;
}

void Window::SetWindowColor(float red, float green, float blue, float alpha) 
{
    glClearColor(red, green, blue, alpha);
}

void Window::SetTitle(const std::string& newTitle) {
    glfwSetWindowTitle(window, newTitle.c_str());
}

void Window::FramebufferSizeCallback(GLFWwindow* window, int width, int height) 
{
    glViewport(0, 0, width, height);
}

void Window::InitializeGLAD() 
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return;
    }
}
