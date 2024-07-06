#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>

class Input 
{
public:
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};
#endif // !INPUT_H
