#include <iostream>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../libs/shader.h"

float vertices[] = {
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, //Bottom left
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // Bottom right
    0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f    // Top Center
};


void framebuffer_size_callback (GLFWwindow* window, int width, int height){
    glViewport(0,0,width, height);
}

void processInput (GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}

int main (){
    char infoLog[512];
    int success;
    /*
     * VBO -> Vertex buffer object
     * VAO -> Vertex array object
     * EBO -> Element buffer object
     */
    unsigned int VBO, VAO;

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

    int nAttribs;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nAttribs);
    std::cout << "Attribss: " << nAttribs << std::endl;


    glGenVertexArrays(1, &VAO);
    
    /* Generate a buffer, bind it to GL_ARRAY_BUFFER type required by a VBO and copy the vertices into this buffer */
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);    
    /* GL_(STATIC/DYNAMIC/STREAM))_DRAW call tells how many times will the data be set and how many times will it be used */
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    /* Tell OpenGL a few things about the vertex data */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    Shader sh1("/home/saiteja/Qualcomm/preparation/opengl/shaders/shaders/shader.vs", "/home/saiteja/Qualcomm/preparation/opengl/shaders/shaders/shader.frag");
    

    /*
     * Render Loop: Each iteration is called a frame
     */
    while (!glfwWindowShouldClose(window)){
        /* Inputs */
        processInput(window);

        /* Render */
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(VAO);
        sh1.use();
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