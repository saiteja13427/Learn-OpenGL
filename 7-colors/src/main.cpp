#include <iostream>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../libs/shader.h"
#include "../libs/stb_image.h"

float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 7.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float currentFrame = 0.0f;
float lastFrame = 0.0f;
float lastX = 400, lastY = 300;
float yaw = -90.0f;
float pitch = 0;
float zoom = 45.0f;
bool firstMouse = true;

void framebuffer_size_callback (GLFWwindow* window, int width, int height){
    glViewport(0,0,width, height);
}

void processInput (GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }

    /* Calculating speed based on the framerate so that speed and render rate combo balances the actuall speed across systems*/
    currentFrame = glfwGetTime();
    const float deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    const float cameraSpeed = 2.5f * deltaTime;
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        cameraPos += cameraSpeed * cameraFront;
    } else if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        cameraPos -= cameraSpeed * cameraFront;
    } else if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        cameraPos -= cameraSpeed * glm::normalize(glm::cross(cameraFront, cameraUp));
    } else if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        cameraPos += cameraSpeed * glm::normalize(glm::cross(cameraFront, cameraUp));
    } else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        cameraPos += cameraSpeed * cameraUp;
    } else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        cameraPos -= cameraSpeed * cameraUp;
    }
}

/* Changing zoom would change the perspective or projection matrix changing the clip space */
void scrollCallback(GLFWwindow *window, double xpos, double ypos) {
    zoom -= (float)ypos;
    if (zoom < 1.0f) zoom = 1.0f;
    else if(zoom > 45.0f) zoom = 45.0f;
}

void mouseCallBack (GLFWwindow *window, double xpos, double ypos) {
    float xOffset = xpos - lastX;
    float yOffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivityFactor = 0.1f;
    xOffset *= sensitivityFactor;
    yOffset *= sensitivityFactor;

    yaw += xOffset;
    pitch += yOffset;

    // if(pitch > 89.0f) pitch = 89.0f;
    // if(pitch < -89.0f) pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}

int main (){
    
    char infoLog[512];
    int success, width, height, nRChannels;
    /*
     * VBO -> Vertex buffer object
     * VAO -> Vertex array object
     * EBO -> Element buffer object
     */
    unsigned int VBO, VAO, lightVAO;

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
    glGenVertexArrays(1, &lightVAO);
    
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

    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);    
    /* GL_(STATIC/DYNAMIC/STREAM))_DRAW call tells how many times will the data be set and how many times will it be used */
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    /* Tell OpenGL a few things about the vertex data */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    Shader objectShader("/home/saiteja/Qualcomm/preparation/opengl/7-colors/shaders/shader.vs", "/home/saiteja/Qualcomm/preparation/opengl/7-colors/shaders/shader.frag");
    Shader lightSourceShader("/home/saiteja/Qualcomm/preparation/opengl/7-colors/shaders/lighting.vs", "/home/saiteja/Qualcomm/preparation/opengl/7-colors/shaders/lighting.frag");
    
    /* 
    * Enable depth testing so that the cube is properly rendered and a few triangles are not drawn on each othere
    */
   glEnable(GL_DEPTH_TEST);

    /*
    * Render Loop: Each iteration is called a frame
    */
    while (!glfwWindowShouldClose(window)){
        /* Inputs */
        processInput(window);
        glm::vec3 lightPos(1.0f, 1.5f, 2.0f);

        /* Render */
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        objectShader.use();
        objectShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
        objectShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);

        /* 
        * Create a transformation matrix
        */
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), 800.0f/600.0f, 0.1f, 100.0f);

        glm::mat4 view;
        view = glm::lookAt(cameraPos, cameraFront + cameraPos, cameraUp);

        objectShader.setMat4("model", model);
        objectShader.setMat4("view", view);
        objectShader.setMat4("projection", projection);
        objectShader.setVec3("lightPos", lightPos.x, lightPos.y, lightPos.z);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);


        lightSourceShader.use();
        glBindVertexArray(lightVAO);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(lightPos));
        model = glm::scale(model, glm::vec3(0.2f));
        lightSourceShader.setMat4("model", model);
        lightSourceShader.setMat4("view", view);
        lightSourceShader.setMat4("projection", projection);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindVertexArray(0);

        /* Poll events and swap buffers */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
exit:
    glfwTerminate();
    return 0;
}