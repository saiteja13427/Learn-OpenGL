#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

float vertices[] = {
    -0.5f, -0.5f, 0.0f, //Bottom left
    0.5f, -0.5f, 0.0f,  // Bottom right
    -0.5, 0.5, 0.0f,    // Top left
    // 0.5f, 0.5f, 0.0f    // Top right
};

// unsigned int indices[] = {
//     0, 1, 2,
//     1, 2, 3
// };

void framebuffer_size_callback (GLFWwindow* window, int width, int height){
    glViewport(0,0,width, height);
}

void processInput (GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}

const char* vertextShaderSource = "#version 330 core\n"
                                   "layout (location = 0) in vec3 aPos;\n"
                                   "void main ()\n"
                                   "{\n"
                                   " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                   "}\0";

const char* fragShaderSource = "#version 330 core\n"
                               "out vec4 FragColor;\n"
                               "void main () {\n"
                               " FragColor = vec4(1.0f, 0.5f, 0.0f, 1.0f);\n"
                               "}\0";

int main (){
    char infoLog[512];
    int success;
    /*
     * VBO -> Vertex buffer object
     * VAO -> Vertex array object
     * EBO -> Element buffer object
     */
    unsigned int VBO, VAO;
    unsigned int vertexShader, fragShader, shaderProgram;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Learn OpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)){
        std::cout << "Failed to init glad" << std::endl;
        return -1;
    }

    glViewport(0,0,800,600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    glGenVertexArrays(1, &VAO);
    
    /* Generate a buffer, bind it to GL_ARRAY_BUFFER type required by a VBO and copy the vertices into this buffer */
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);    
    /* GL_(STATIC/DYNAMIC/STREAM))_DRAW call tells how many times will the data be set and how many times will it be used */
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    /* Tell OpenGL a few things about the vertex data */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    /*
     * Vertex shader creation and compilation and status check
     */
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertextShaderSource, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED: " << infoLog << std::endl;
        return -1;
    }

    /*
     * Fragment shader creation, compilation and status check
     */
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, & fragShaderSource, NULL);
    glCompileShader(fragShader);

    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAG::COMPILATION_FAILED: " << infoLog << std::endl;
        return -1;
    }

    /*
     * Creation, attaching and activating a shader program
     */
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragShader);
    glLinkProgram(shaderProgram);


    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::LINK_FAILED: " << infoLog << std::endl;
        return -1;
    }
    
    

    /* After linking the shaders with shader program, we no more need the shader objects */
    // glDeleteShader(vertexShader);
    // glDeleteShader(fragShader);


    /*
     * Render Loop: Each iteration is called a frame
     */
    while (!glfwWindowShouldClose(window)){
        /* Inputs */
        processInput(window);

        /* Render */
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0,3);
        glBindVertexArray(0);

        /* Poll events and swap buffers */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
exit:
    glfwTerminate();
    return 0;
}