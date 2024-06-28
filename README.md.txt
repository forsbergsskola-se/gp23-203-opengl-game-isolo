This Project is based on the OpenGL tutorials (https://archive.org/details/learnopengl/mode/1up?view=theater) and could be considered as a very simple Graphics Engine because it can draw 3D Shapes, apply textres to the shapes, manipulate different lighting types and load smaller models into the scene with JSON library, transformation handlers exists and can be used to position, scale and rotate models. 




Overview of Project files.

Camera.h & Camera.cpp:
Variables:

The vector position stores information on where the camera is in 3D space.
The vector orientation variable stores information on which direction the camera is looking.
The vector up variable stores information on camera's Y axiss, it allows the camera to move up, down.

cameraMatrix(mat4) stores the transformation matrix of the camera.

The int variables stores information on width and height of the window.
The float variables stores information on the speed and sensitivity of camera movement.
The boolean variable used as a flag that checks if mouse is clicked first time or not.

The Double variables holds the values for current mouse (X and Y) positions and are used as arguments for glfwGetCursorPos function parameter.

Functions:

The Camera constructor to initialize camera with specified width, height, and position. 

updateMatrix function takes the float parameters for field of view(FOV) in degree, near clipping plane and far clipping plane to create view and projection matrices in the camera.cpp then sets up the view based on camera's position and orientation then sets up the projection matrix (the perspective) based on given FOV, width, height, near and far plane parameters, in the end combines the projection and view matrices to form the camera matrix.

Matrix function sends the camera matrix to the shader by taking a reference to the shader and the name of the uniform as parameters in order to upload the camera matrix to the specified uniform in the shader program. 

Inputs function processes the inputs from keyboard and mouse to control the camera.
WASD:
Depending on which buttons are pressed the function calculates the orientation, speed and new position.
Orientation or -orientation multiplied with speed to determine direction the camera moves when a button is pressed.

Mouse Inputs:
When right mouse button is pressed, the cursor is hidden with glfwSetInputMode function, and if mouse click is made first time
the cursor is centered and boolean flag is set to false.

By calculating width, height, mouse position X or Y and the sensitivty variables the angles are determined.

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

VBO.h & VBO.cpp (Vertex Buffer Object)

The header files of the class is used to create a Vertex struct that defines variables of type vector 3s and vector 2 that holds the values for position, normal, color and texture coordinates. 

The header file also defines the Vertex Buffer Object class with public section where the class ID is defined with variable GLuint, the constructor to generate VBO to fill vertex data is defined, then Bind, Unbind and Delete functions are defined.

The implementations are made in VBO.cpp file by following steps.
Constructor first generates a buffer, then binds it to the target array buffer. 
The constructor also fills the buffer with data, such size of data in bytes pointing to the vertex data and hints the GPU how the data sent should be accessed and used. (In this case GL_STATIC_DRAW, meaning the data in the buffer will specified once but used many times as a source for drawing)

The Bind function binds the VBO to the targeted array buffer, the Unbind function unbinds the any buffer object from the targeted array buffer and lastly the Delete function that deletes the VBO by deallocating it's buffer object.

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

VAO.h & VAO.cpp (Vertex Array Object)
This class is defined in the header file, and in the public section class ID is defined with Open GL's unsigned int variable.
The first function LinkAttrib defined with 6 parameters. 
VBO& VBO reference, GLuint layout to hold attribute location in the shader program.
GLuint numComponents to hold value for how many components each vertex has, like vec3 has 3. 
GLenum type that informs the type of variable, like bool, or float etc. 
GLsizeiptr stride informs the GPU about the byte distance from the start of one set of vertex attributes to the start of the next set.
The last parameter is void pointer offset, in this case it's a pointer that can point to where where attribute within vertex data starts.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EBO.h & EBO.cpp (Element Buffer Object)

Similar to VBO and VAO classes, this class also defines its ID in the header file's public section, defines the constructor,
the Bind, Unbind and Delete functions.
EBO.cpp implements the constructor by generating buffer ID for the EBO with glGenBuffers, then binds the EBO to element buffer array target and allocates memory for initialization of the buffer with provided indices which are size, data for drawing.

Bind function makes sure the EBO is Active so it can be used in rendering.
Unbind function sets current EBO by binding it to 0 to deactivate it.
Delete function removes the buffer with given ID.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Relationship between VBO, VAO & EBO.

When rendering...

VBO stores vertex data (positions, normals, colors, texture coordinates) and is responsible for sending this data to the GPU.
VAO manages multiple VBOs and specifies how vertex attributes are retrieved and used in shaders. It references the VBOs and sets up the necessary attribute pointers.
EBO stores indices for indexed drawing, allowing efficient reuse of vertices stored in the VBO. This minimizes data duplications and optimizes rendering performance.

The VAO binds the VBOs and EBOs it references, ensuring that the correct vertex data and indices are used during rendering. The VBO provides the vertex data, while the EBO provides the indices to draw the vertices. This setup optimizes rendering by efficiently managing vertex attributes and indices, ensuring minimal data redundancy and improved performance.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Shader.h & Shader.cpp

The header file contains the definitions of functions and parameters. The First function in the file is "string get_file_contents" with parameter (const char pointing to filename).
The Shader class is pretty simple one, first defining the class ID with GLuint variable type then the constructor Shader is defined with two parameters, first const char pointing to vertex file and second one is const char pointing to fragment file.

3rd function is Activate, 4th function Delete and within private section 5th function is defined by name compileErros and has two parameters, first unsigned int shader and second const char pointing to type. This last function is to handle compilation errors.

in Shaderp.cpp first thing we do is to get file contents from given file name by getting a file and opening it in binary mode with "ifstream in(filename, ios binary)
if file successfully opened, string is created with name contents to hold the file contents,
and seekg is called to move a pointer to the end of file in bytes, 'tellg' tells where the pointer ended to 'resize' so it can start reading the byte size from given content into a string after 'seekg' is moved to the beginning,
and 'close' the file stream and return 'contents'.
else and error message is thrown. 

The second implementation is the Shader constructor with const char variables pointing to vertex file and fragment file.

This constructor first declares local variables of type string, vertexCode and fragmentCode to read vertex and fragments codes with 'get_file_contents' function from the shader source.
Then declares another two variables of type char with names vertexSource and fragmentSource and converts vertexFile and fragmentFile to c-style string with the c_str functions.

Then GLuint local variable is declared with name vertexShader to create vertex shader object with glCreateShader,
it calls glShaderSource function and attaches vertexSource to vertexShader in order to call glCompileShader function which compiles the vertexShader. If any errors, the message "VERTEX" is thrown.

Next local variable GLuint with name fragmentShader, it works similarly here but instead of vertex shader, it creates, attaches and compiles the fragments from the file and throws error message "FRAGMENT" with 'compileErrors' function if any error happens when compiling.


Then the shader program with ID is created by attaching the vertex, fragment shaders to the program ID and linking the shaders into program with the ID. If any linking errors happens, the program throws "PROGRAM" error message.

After linking both shaders and no longer needed, they are deleted with glDeleteShader (vertexShader / fragmentShader)

The next two functions in this Shader class are Activate and Delete, as the name suggests first function activates the created program ID with glUseProgram and then deletes the ID and associated resources with glDeleteProgram to free memory.

The last function of Shader class is compileErrors with parameters unsigned int shader and const char type, this function has variable to store compilation status and a buffer to store error message. It's responsible for error notifications, where the error is and what kind of error it is. 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Mesh.h & Mesh.cpp

The Mesh class, in spirit of object oriented programming this class has it's vector variables vector variables to store vertices, indices and textures in the public section and VAO is declared so it can be used in the draw function.

Mesh is initialized and the void Draw function defined with 6 parameters which are references to Shader and Camera, then mat4 matrix, vec3 translation, quat rotation, vec3 scale and their float values. 

In the Mesh.cpp, the vertices, indices and textures are specified, the VAO's Bind function is called, the vertex buffer object is generated and linked to the vertices, the element buffer object is generated and linked to indices.

Vertex Array Object's linkAttrib function are called link Vertex Buffer Object attributes such as coordinates and colors to VAO when it's done, we just call VAO's VBO's and EBO's Unbind functions. 


The Mesh's Draw function calls Shader's activate function and VAO's Bind function to bind shader and access uniforms.

Local variables numDiffuse and numSpecular of type unsigned int are declared and set to 0, so the following for-loop can iterate through each texture in the 'textures' vector and increment 'i' after each iteration, the loop also checks the texture type and if certain condition is true, numbers are coverted to string. After the iterations and conversion we Bind the current texture to it's corresponding texture unit, making it active and ready for rendering. 

glUniform3f function is then called and given 4 parameters to take care of the camera matrix, the shader ID, camera's positions x, y and z. to get the location of the camera.
When location is known, the Matrix function sends the camera matrix to the shader.

Then mat4 translation, rotation and scales matrices are initialized and the matrices are transformed to their correct form with translate, mat4_cast and scale functions of glm.

Then the matrices are pushed to the vertex shader with glUniformMatrix4fv functions. 

In the end the actual mesh is drawn with glDrawElements and GL_TRIANGLES. 
///////////////////////////////////////////////////////////////////////////////////////////////
Model.h & Model.cpp

Variables:

This class has 10 variables, starting with 'file' which stores the path ot the model file, 2nd is 'data' and it stores the extracted binary data from the file, 3rd is 'JSON' and it holds the parsed JSON dat from the model file. 
Then we have 'meshes' variable of type vector, it represents the Mesh.
translationsMeshes variable stores the translation vectors for each mesh.
rotationsMeshes stores the rotation quaternions for each mesh.
scalesMeshes stores the scale vectors for each mesh.
matrices Meshes stores the transformation matrices for each mesh.
9th variable is loadedTexName and it keeps trach of the names in loaded textures to avoid duplications.
The last variable is loadedTex of type unsigned int and it stores the actual texture object that have been loaded. 

Functions:
1. Model (const char file) is a constructor and it's function is to initialize the model by loading data from a file by Reading the content of the file and parse it into a JSON object, then retrieve the binary data from the file and start mode traversal from the root node.

2. Draw (Shader& shader, Camera& camera) function draws all the meshes in the model by iterating over each mesh then calculating the transformation matrix by applying translation, rotation and scaling and in the end passes the transformation matrix and other relevant data to the Draw function in the Mesh class.

3. loadMesh (unsigned int indMesh) function loads a single mesh using its index by getting all the accessor indices for positions, normals, texture coordinates and indices then extracts the corresponding data (positions, normals, texture coordinates and indices) in order to assemble the vertex data and textures and in the end creates a Mesh object and adds it to the 'meshes' vector.

4. traverseNode(unsigned int nextNode, glm::mat4 matrix = glm::mat4(1.0f)), this function recursively traverses the node hierarchy to process each node and it's Children by first retrieving the current current node from the JSON then, extract translation, rotation, scale and transformation matrix from the node if they exist in order to initialize matrices and use translation, rotation and scale to change the initialized matrices by running multiplication operations on the data and check if the node contains a mesh and if it does, load it. 
In the end check if the node has Children, and if it does, apply this function to them with the matNextNode.

5. vector<unsigned char> Model::getData() function is to retrieve binary data from the file, by reading the binary data from the specified buffer in the JSON, convert the raw text into a vector of unsigned characters then return the binary data. 

6. vector<float> getFloats(json accessor) extracts float data from a specified accessor by first retrieving the buffer view index, count, byte offset, and type from the accessor then reads the float data from the binary data using specified parameters and returns the float data as a vector.

7. vector<GLuint> getIndices(json accessor) extract index data from a specified accessor by first retrieving the buffer view index, count, byte offset, and type from the accessor then reads the float data from the binary data using specified parameters and returns the float data as a vector.

8. vector<Texture> Model::getTextures() function uses local variables of typ vector and strings, the vector is used to store the textures that are loaded and strings stores the file path and extract the directory path.
This function iterates over all the images array in the JSON object and store the URI of the current texture, check if texture is already loaded and if not load new texture and organize them by type, depending if it's diffuse or specular. 

9. vector<Vertex> Model::assembleVertices() creates a vector of 'Vertex' objects from provided positions, normal, and texture coordinate data with the local vector variables it runs a for-loop sets the position attribute of the vertex to the current element of 'positions' then does the same for normal, color and text UV in order to return vertices.

10. vectorglm::vec2 Model::groupFloatsVec2(std::vector<float> floatVec) Groups a flat vector of floats into a vector of 'glm::vec2' by iterating over the float vector and create vec2 object in-order to return the grouped vectors.

11. vectorglm::vec3 Model::groupFloatsVec3(std::vector<float> floatVec)  Groups a flat vector of floats into a vector of 'glm::vec3' by iterating over the float vector and create vec3 objects.

12. vectorglm::vec4 Model::groupFloatsVec4(std::vector<float> floatVec) Groups a flat vector of floats into a vector of 'glm::vec4' by iterating over the float vector and create vec4 objects.

