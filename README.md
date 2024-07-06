1. Window Class Overview
Member Variables
  int width_: Stores the window width.
  int height_: Stores the window height.
  GLFWwindow* window: Pointer to the GLFW window.

Constructor: Initializes GLFW, sets OpenGL context hints, creates a GLFW window, sets it as the current context, registers a resize callback, and initializes GLAD.
GetGLFWWindow: Returns the GLFW window pointer.

Destructor: Cleans up by destroying the window and terminating GLFW.
Run: Main loop that clears the screen, calls the custom render function, swaps buffers, and polls events.
SetRenderFunction: Allows setting a custom function for rendering, which is called every frame in the Run method.
SetWindowColor: Configures the background color for the window.
SetTitle: Changes the window title.
FramebufferSizeCallback: Updates the OpenGL viewport when the window is resized.
InitializeGLAD: Loads OpenGL functions using GLAD and handles initialization failure.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
2. Camera Class Overview
Member Variables
  glm::vec3 Position: Stores the camera's position in 3D space.
  glm::vec3 Up: Defines the up direction for the camera (typically (0, 1, 0)).
  glm::vec3 Orientation: Represents the direction the camera is facing.
  float FOV: Field of view angle of the camera (default value used).
  float speed: Speed of camera movement.
  float sensitivity: Sensitivity of camera rotation.
  bool firstClick: Flag to manage initial mouse click state.
  float width: Width of the viewport.
  float height: Height of the viewport.

Constructor:
Initializes the camera with a specified position, sets Up direction, initializes Orientation to face forward (z-axis), sets FOV, speed, sensitivity, and viewport width and height.

GetViewMatrix:
Returns the view matrix used for rendering:
Computes and returns glm::lookAt(Position, Position + Orientation, Up).
Constructs a view matrix that positions the camera at Position, looks towards Position + Orientation, and uses Up as the up direction.

GetProjectionMatrix:
Returns the projection matrix for perspective projection:
Computes and returns glm::perspective(glm::radians(FOV), aspectRatio, 0.1f, 500.0f).
Generates a perspective projection matrix with the given FOV, aspect ratio (width / height), and near (0.1f) and far (500.0f) clipping planes.

Inputs:
Handles user inputs for camera movement and orientation control using glfwGetKey and glfwGetMouseButton:
Keyboard Inputs (W, A, S, D, Space, Left Control, Left Shift):
Adjusts Position based on Orientation and Up vectors.
Toggles speed between slow (0.025f) and fast (0.1f) movement.
Mouse Inputs (Right Mouse Button):
Hides cursor (GLFW_CURSOR_HIDDEN) for free look mode.
Tracks mouse movement to rotate Orientation around Up and current forward axis (Orientation).
Ensures smooth rotation by managing mouse coordinates relative to the screen center (width / 2, height / 2).
Restores cursor visibility (GLFW_CURSOR_NORMAL) and resets state to prevent abrupt camera movements.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TriangleShader Class Overview
This class encapsulates the functionality to manage shader programs in OpenGL, including compilation, linking, setting uniforms, error handling, and shader file reading. It provides convenient methods to interact with shader programs and handle shader-related operations efficiently.

Member Variables
  GLuint shaderProgram: Holds the ID of the compiled shader program.
  GLuint useTextureLocation, debugModeLocation: Uniform locations for useTexture and debugMode.
  
Constructor: TriangleShader(const char vertexPath, const char fragmentPath)**
Reads and compiles vertex and fragment shader source code from files specified by vertexPath and fragmentPath.
Links the compiled shaders into a shader program.
Deletes individual shader objects after linking into the program.
Retrieves uniform locations for useTexture and debugMode.

Destructor: ~TriangleShader()
Deletes the shader program to free GPU resources.

Activate() Method
Sets the shader program as the current active shader in the OpenGL context.

GetUniformLocation(const std::string& name);
Returns the location of the uniform variable specified by name in the shader program.

SetMat4(const std::string& name, const glm::mat4& mat);
Sets a 4x4 matrix uniform variable in the shader program.

SetVec3(const std::string& name, const glm::vec3& value);
Sets a 3-component vector uniform variable in the shader program.

SetColor(const std::string& name, const glm::vec3& color);
Sets a color uniform variable in the shader program using a 3-component vector.

SetFloat(const std::string& name, float value);
Sets a float uniform variable in the shader program.

SetInt(const std::string& name, GLint value);
Sets an integer uniform variable in the shader program.

SetBool(const std::string& name, bool value);
Sets a boolean uniform variable (useTexture or debugMode) in the shader program.

CheckCompileErrors(GLuint shader, std::string type);
Checks for compilation or linking errors in shaders or shader programs and logs errors to std::cerr.

ReadShaderFile(const char shaderPath);
Reads and returns the contents of a shader file specified by shaderPath.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Texture Class
Variables
  ID of type GL unsigned Int, this variable stores the number identity for created texture object.
  type; of type GL unsigned int, this variable which type the texture is, like diffuse or specular.
  
Functions
Constructor loads an image from a file and sets it up as an OpenGL texture.

First it assigns the type of the texture to the texture object, 
then stores the width, height and the number of color channels of the image.
Flips the image so it appears right side up, and then
reads the image from a file and stores it in bytes.

Generates an OpenGL texture object and assignts the texture to a Texture unit.
Configures the type of algorithm that is used to make the image smaller or bigger,
configures the way the texture repeats if it does at all
then loads texture data to GPU, generates mipmap and frees the image when texture initialization is complete for image.

SetTextureUnit method connects a texture to a specific part of the shader program by,
getting the location of the unifom.
Activates invokes the TriangleShader's Activate() funtion.
Sets the value of the uniform.

Bind(), Unbind(), and Delete()
Binds the texture, then unbinds the texture and deletes it. 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CubeTexture Class
Variable
  GLuint textureID: Stores the number identity for created texture.

Constructor loads an image from a file and sets it up as OpenGL texture.
The for loop in constructor iterates over a vector of image file pahts. For each path, it loads the correcponding iamge, uploads it to a specific face of a cube map textute, 
until all six faces of the cube map texture are initialized and ready for use in rendering.
Configures the type of algorithm that is used to make the image smaller or bigger,
configures the way the texture repeats if it does at all
then loads texture data to GPU, generates mipmap and frees the image when texture initialization is complete for image.

In the end unbinds the texture cube map just to avoid unintended actions.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ShapeDefiner Class
Works as a data storage for different shapes, for different shapes like Triangle, Cube, Pyramid, Plane and Sphere.
Example:
std::vector<float> GetTriangleVertices(bool texCoordWanted);
Holds float data for vertices and texture coordinates, if bool is set to true, it sends both vertices and texture coordinates for the Triangle.
std::vector<unsigned int> GetTriangleIndices();
Hold indices data in unsigned int, it determines in which order the texture coordinates and/or vertices should be used when drawing the shapes.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ShapeGenerator Class
Variables:
  ShapeVBO (GLuint): Stores vertex data on the GPU using Vertex Buffer Objects (VBOs).
  ShapeEBO (GLuint): Stores index data on the GPU using Element Buffer Objects (EBOs).
  ShapeVAO (GLuint): Encapsulates vertex attribute configurations and bindings.

  std::vector<float> vertices;
  std::vector<unsigned int> indices;

  position (glm::vec3): Defines the position of the shape in 3D space.
  rotation (glm::quat): Represents the orientation of the shape using quaternions.
  scale (glm::vec3): Scales the size of the shape.
  color (glm::vec3): Specifies the color of the shape.
  
Functions and Methods:

Constructor (ShapeGenerator()):
Prepares the Open GL buffers and initializes shape attributes position, rotation, scale, and default color.

Destructor (~ShapeGenerator()):
Cleans up OpenGL resources by deleting OpenGL buffers and ShapeVAO, ShapeVBO, and ShapeEBO.

SetShape() and SetCubeShape():
Accepts vertices, indices, and a flag for texture coordinates. 
Generates VAO, VBO and EBO accordingly.
Binds VAO, then binds VBO and sets data, and then binds EBO and sets data.
Depending on if the accepted data includes texture coordinates or not.
Lastly unbinds the VBO and VAO freeing the memory.

SetCubeShape: Does same thing as SetShape but works only with setting cube vertices and indices.

Rendering Methods Draw() and DrawCubemap():
Starts with setting up the initial model matrix as an identity matrix, which is a baseline for transformations,
meaning no transformation is applied in the beginning and changes to translation, rotation and scaling will be on top of the initial point.

Calculates MVP matrix (model=view*projection) to make sure the created shape is moved from it's local space to world space correctly and is in front of the camera.
Then invokes the TriangleShader's Activate(); and SetMat4 functions to pass the model matrix, view, projection and MVP data to the shader program, and also the colors.
If the shape is being drawn with the texture flag set to true, it invokes the binding function for the texture and sets the useTexture flag to true.
Else it sets the useTexture to false for the shader program.
Binds the vertex arrays with elements and then unbinds them.

The DrawCubemap() method does same thing as the Draw method but only works with drawing a cube.
The difference between these methods are, one works with Texture class and the other one with the CubeTexture class.

Transformation()
Holds the position, angle, axis and scale values and is used to change the initial transformation.

SetColor()
Holds the color variables and can easily be used to change the color in the shader when called in the main scene.

CheckGLError()
A method to check if any GL errors shows up in the places where this method is called, it prints information to the console with location and error code.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
The MAIN

This is a place where everything other classes done is presented.
First Window class is initialized with custom width, height and a title. 
Then the Camera is initialized with vec3 values that changes cameras xy and z positions, window width and height so the camera matches window size.
Then TriangleShader class is initialized with vertex and fragment shaders.

GL Depth test is enabled, depth functions are set.

ShapeDefiner is initialized allowing use of the data it contains.
ShapeGenerator is initialized and it's SetShape, Transformation and SetColor methods are called and set.
Texture class is initialized and the image to be displayed is given to it's parameters.
CubeTexture class is initialized to and six images loaded in an vector string array.  
ShapeGenerator is initialized again just to call the SetCubeShape function and cubeVertices, cubeIndices are passed to it's parameter.

window.SetRendererFunction is set and ready to loop all of the above and the draw calls from ShapeGenerator class.
window.Run() called to start the renderer function then destory the window when it's closed.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
This project is still ongoing process and there are few more things I can image myself doing to improve and develop this into a decent Shader Engine in the future.
