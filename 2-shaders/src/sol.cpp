#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

float vertices1[] = {
    -0.5f, -0.5f, 0.0f, //Bottom left
    0.5f, -0.5f, 0.0f,  // Bottom right
    -0.5, 0.5, 0.0f,    // Top left
};

float vertices2[] = {
    0.5f, 0.5f, 0.0f,    // Top right
    0.0f, 0.0f, 0.0f,
    0.5f, 0.0f, 0.0f
};

unsigned int indices[] = {
    0, 1, 2,
    1, 2, 3
};

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

const char* fragShaderSource1 = "#version 330 core\n"
                               "out vec4 FragColor;\n"
                               "void main () {\n"
                               " FragColor = vec4(1.0f, 0.5f, 0.0f, 1.0f);\n"
                               "}\0";
const char* fragShaderSource2 = "#version 330 core\n"
                               "out vec4 FragColor;\n"
                               "void main () {\n"
                               " FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
                               "}\0";

int main (){
    char infoLog[512];
    int success;
    /*
     * VBO -> Vertex buffer object
     * VAO -> Vertex array object
     * EBO -> Element buffer object
     */
    unsigned int VBO1, VBO2, VAO1, VAO2;
    unsigned int vertexShader, fragShader1,  fragShader2, shaderProgram1, shaderProgram2;

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


    glGenVertexArrays(1, &VAO1);
    glGenBuffers(1, &VBO1);
    glBindVertexArray(VAO1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);    
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glGenVertexArrays(1, &VAO2);
    glGenBuffers(1, &VBO2);
    glBindVertexArray(VAO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertextShaderSource, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED: " << infoLog << std::endl;
        return -1;
    }

    fragShader1 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader1, 1, &fragShaderSource1, NULL);
    glCompileShader(fragShader1);

    glGetShaderiv(fragShader1, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragShader1, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAG::COMPILATION_FAILED: " << infoLog << std::endl;
        return -1;
    }

    shaderProgram1 = glCreateProgram();
    glAttachShader(shaderProgram1, vertexShader);
    glAttachShader(shaderProgram1, fragShader1);
    glLinkProgram(shaderProgram1);


    glGetProgramiv(shaderProgram1, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(shaderProgram1, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::LINK_FAILED: " << infoLog << std::endl;
        return -1;
    }

    fragShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader2, 1, &fragShaderSource2, NULL);
    glCompileShader(fragShader2);

    glGetProgramiv(fragShader2, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(fragShader2, GL_COMPILE_STATUS, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAG::COMPILATION_FAILED: " << infoLog << std::endl;
    }

    shaderProgram2 = glCreateProgram();
    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram2, fragShader2);
    glLinkProgram(shaderProgram2);

    glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram2, GL_LINK_STATUS, NULL, infoLog);
        std::cout << "ERROR:SHADER::LINK_FAILED: " << infoLog << std::endl;
    }
    
    while (!glfwWindowShouldClose(window)){
        /* Inputs */
        processInput(window);

        /* Render */
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram1);
        glBindVertexArray(VAO1);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glUseProgram(shaderProgram2);
        glBindVertexArray(VAO2);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        /* Poll events and swap buffers */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
exit:
    glfwTerminate();
    return 0;
}