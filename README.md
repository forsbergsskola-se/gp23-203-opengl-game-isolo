This is an overview of all classes, their variables and functions.

Window Class:
Variables;
int variables are used to store window's width and height.
float variables are used to store the background colors of the window, red, green, blue and alpha.
string variable is used to store the title of our window.

Functions;
The constuctor holds the variables in it's parameters and within it's scope it checks if
glfw initialization was not successful in order to print a message to the console.
Next, the constructor calls the glfwWindowHint functions which are responsible hinting the program which version of GLFW it can use
and which of OpenGL's profile. 
When it's done, the constructor calls glfwCreateWindow function and it's responsible for displaying a window with given width, height and title.
If the creation of window fails, it prints a message to the console and terminates glfw.
When the window is created, glfwWakeContextCurrent function is called and given 'window' as an argument, which means the window that's created is the current content.
glfwSetWindowUserPointer and FragebufferSizeback are also called to set up and enable adjustments to window sizing. 
In the end the Constructor calls InitializeGLAD function to start the created window.

GetGLFWWindow is responsible for returning 'window' as the created window from GLFWwindow.
The destructor then destroys and terminates the created window when it's closed.

Run method runs a while loop saying as long glfwWindowShouldClose is should not close, the colors in the window cleared each frame to prevent colors from stacking on top of each other when they are changed,
The run method also calls the renderer function if it's called, meaning the renderer function gets into the while loop when called with all it's content.
glfwSwapBuffers swaps the first and second buffers for paralell processing of pixels, and then glfwPollEvents function is called to process everything that's happening, like mouse clicks, moving objects, keyboard inputs etc.

SetRendererFunction is just a function that can be called in the main scene and is looped within the Run method's while loop.
SetTitle method calls the glfwSetWindowTitle function to give the user option to choose name of the window.
FramebufferSizeCallback method calls glViewport to set window width, height and is called within the constructor just like InitializeGLAD method which checks if GLAD could be initialized and if not print a message to the console.

Camera Class
Variables;
glm::vec3 position to store the 3D position coordinates, up vectors and the direction of the camera.
float variables to store window's width and height so the camera can match window size.
other float variables stores field of view, camera's speed, mouse sensitivity.
The bool variable is used to check if the first mouse click was made or not.

The Camera constructor stores all the variables within it's parameters, allowing us make a good use of them.
GetViewMatrix function calls the glm::lookAt function and gives it position, the position + orientation and up vector values.
The GetProjectionMatrix returns the glm::perspective calculations, it determines how close and far the camera can show in the world space.
Input method calls bunch glfwGetKey functions for WASD keys, checks if any of the keys are pressed with GLFW_PRESS function and calculates how camera should react based on position, speed and orientation operators.
The Input method also calls the glfwGetMouseButton functions to calculate camera's behavior.

TriangleShader Class
 Variables;
 The variables used in this class are GLuint(unsigned int) they store the id of this shader class.
 other variables are used within the class method parameters to store name, value, color and bool checks.

Functions;
Shader Constructor has char variables pointing at vertex and fargment paths.
It's responsiblity is to set up the vertex and fragments shaders step by step. 
The ReadShaderFile function is called to read the contents of the vertex and fragment shader files from the paths specified by vertexPath and fragmentPath.
The contents of these files are stored in vertexCode and fragmentCode strings.
The c_str() method is used to convert the std::string objects to C-style strings (const char*), which are required by the OpenGL functions.
glCreateShader(GL_VERTEX_SHADER) creates a new vertex shader object and returns it's ID.
glShaderSource sets the source code for the vertex shader.
glCompileShader compiles the vertex shader.
CheckCompileErrors checks for compilation errors and reports any issues. It takes the shader ID and a string describing the type of shader ("VERTEX").
This shader also hold the location for if a texture is to be used to not, which is a bool flag in the fragment shader.

The Destructor calls glDeleteProgram, which deletes the shader program when it's done.
The Activate method glUseProgram for starting this shader program.

Utility functions;
GetUniformLocation method returns glGetUniformLocation, and it's used to get the name of whatever uniform was used and convert the name to string.
GetMat4 method calls glGetUniformLocation, and glUniformMatrix4fv, when Mat4 function is called in other scripts this method sets the given (x, y, z, w) data the the shader program and if the location was not found it returns a message.
other utility functions are for getting and setting glm::vec3, float, int and bool data.
All of them can be called in other classes to give appropriate name and data type, then these functions gets it and sets to the shaders, if any error occurs during this process a message is displayed in the console. 

The CheckCompileErrors method uses glGetShaderiv, GL_COMPILE_STATUS, glGetShaderInfoLog, GL_LINK_STATUS to keep an eye on the proccess, if any compilation or linking errors occurd during the process a message is printed. 
The ReadShaderFile method reads the code in the shader and returns it as string, if anything goes wrong with file reading a message is displayed in the console. 

Texture Class
This class has mainly two variables of type GLuint to store unique id and type of the textures.

The Texture class constructor takes 5 arguments, first one for image, second one is for texture type, third one is for slot, fourth argument take the format and last one pixel type in it's parameters, and when this class is initialized in main method they must be filled in.
like following;     Texture planeTexture("blackPaper.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
In the scope of constructor most heavy work is done in following steps;
Stores the texture type (e.g., GL_TEXTURE_2D) in the type member variable.
Declares variables to hold the width, height, and number of color channels of the image.
Sets the image loader to flip the image vertically.
Loads the image from the file specified by image and stores its data in bytes. The image's width, height, and color channels are also stored in the respective variables.
Generates a new texture object and stores its ID in the ID member variable.
Activates the specified texture unit (slot).
Binds the generated texture object to the specified texture type (texType).
Logs the generated texture ID.
GL_TEXTURE_MIN_FILTER and GL_TEXTURE_MAG_FILTER to GL_NEAREST_MIPMAP_LINEAR for the minifying and magnifying filters, respectively.
GL_TEXTURE_WRAP_S and GL_TEXTURE_WRAP_T to GL_REPEAT for the wrap parameters (how the texture repeats).
Specifies a 2D texture image, transferring the image data from the bytes array to the GPU. The texture is configured with the specified format and pixel type.
Generates mipmaps for the texture, which are smaller versions of the texture used for distant rendering to improve performance and visual quality.
Frees the image data that was loaded into memory and then unbinds the texture to prevent accidental modifications.

The SetTextureUnit method takes shader program's reference, uniform and unit in it's parameter.
Calls the glGetUniformLocation function to get the uniform of texture a unit, activates the shader and sets the value of the uniform.

Bind, Unbind and Delete is used to bind the texture type and id, unbind them and delete them when it's no longer needed.

ShapeDefiner Class
This class works like a data storage, it holds vertices, indices and texture coordiantes for different shapes using float and int variables. The texture coordinates are returned only if the bool flag is true.
ShapeGenerator Class a class that can generate different 2D and 3D shapes using the data in ShapeDefiner class.
Variables;
float to store vertices, int to store indices.
GLuint to store VBO, EBO and VAO.
glm::vec3 to store vector position, scale and color of generated objects.
glm::quat to store rotation data.
References;
Window& window and Camera& camera because they are needed to display the shape generated in the window and infront of the camera.

Functions;
Shape generator's constructor initalizes all the needed variables from VBO to shader and camera.
The destructor calls glDeleteVertexArrays, and glDeleteBuffers to delete the VAO, VBO and EBO when it's done.

SetShape method has three variables in it's parameters for vertices, indices and bool to check if the vertices are coming with or without texture coordinates.
SetShape first says vertices and indices is to be kept for later usage and then generates VAO, VBO and EBO.
Binds the Vertex Array, Vertex Buffer and Element Buffer objects and sets them with attribute pointers, enabling vertex array and if there is texture data the previous two calls are repeated.
In the end ubinds the buffer and vertex arrays.

Draw method takes window and camera by reference, also texture by pointer in it's parameter.
declared glm::mat4 member variable to store model matrix, which are translation, rotation and scale.
then the float variable is declared to store aspect ratio, which is width of the window divided by height of the window, so the camera is centered.
3 more glm::mat4 members are declared, first two to store the view and projection matrix from our Camera class and calculate MVP which is result of projection * view * modelMatrix.

Activates the shader by calling the shader class activation method then invokes the SetMat4 and SetColor functions of the shader program to pass MVP and color locations.
if the texture coordinates are applied, texture points to Texture class's Bind method and the flag in shader class is set to true so it's prepared to process even the texture coordinates.
binds the vertex arrays with glBindVertexArray and glDrawElements functions which determines in which order the vertices should be used.
Lastly unbinds the vertex arrays. 

Transformation and SetShapeColor methods stores the position, angle, axis, scale and color matrices using glm.
The CheckGLError function is used to check if there is any OpenGL related errors, it can be called within calss functions anywhere.

Create3D Object Class
This class encapsulates both ShapeDefiner and ShapeGenerator class method into one single method for different shapes, allowing to draw any shape it sets up with a single call in the renderer function of window class in the main class. 
Like this -> (Initialization) Create3Dobject create;           Texture planeTexture("blackPaper.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
and render..
 create.CreatePlane(window, camera, glm::vec4 (0.0f, 0.0f, 1.0f, 1.0f), glm::vec3 (0.0f, -1.0f, 0.0f), glm::vec3 (10.0f), &planeTexture);
 create.CreateCube(window, camera, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f));

CubeTexture & Skybox Classes
These classes work pretty much like Texture and ShapeGenerator classes only difference is...
Unlike Texture class, the CubeTexture class loads 6 images one by another and binds them before passing to the shader.
The SetSkybox method then gets the vertices and indices for a cube from ShapeDefiner just like generator, binds the data, sets them together and unbinds them.
DrawSkybox then sets up the window and camera just like in ShapeGenerator's draw method but this method calls glDepthMask and sets it to false because we want to set the skybox behind everything else.
Activates shaders, invokes it's Set up utility methods and passes data to the Skybox vertex and fragment shaders to process and display. 

Light Class is still work in process but it works pretty much like skybox class, it takes vertices and indices from ShapeDefiner then generates a sphere to represent the light source,
activates shader program to set up and send data to the lightSource vertex and fragment shaders. 
