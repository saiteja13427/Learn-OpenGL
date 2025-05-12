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
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f, 0.0f, 0.0f),
    glm::vec3( 2.0f, 5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3( 2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f, 3.0f, -7.5f),
    glm::vec3( 1.3f, -2.0f, -2.5f),
    glm::vec3( 1.5f, 2.0f, -2.5f),
    glm::vec3( 1.5f, 0.2f, -1.5f),
    glm::vec3(-1.3f, 1.0f, -1.5f)
};

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 10.0f);
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
    // glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
    // glm::mat4 trans = glm::mat4(1.0f);
    // trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
    // vec = trans * vec;
    // std::cout << vec.x << " "  << vec.y << " " << vec.z << " " << vec.w << std::endl;

    char infoLog[512];
    int success, width, height, nRChannels;
    /*
     * VBO -> Vertex buffer object
     * VAO -> Vertex array object
     * EBO -> Element buffer object
     */
    unsigned int VBO, VAO, texture, texture1;

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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    Shader sh1("/home/saiteja/Qualcomm/preparation/opengl/6-camera/shaders/shader-cubes.vs", "/home/saiteja/Qualcomm/preparation/opengl/6-camera/shaders/shader-cubes.frag");
    
    /* Need this otherwise, the images will be rendered vertically reversed. This is because opengl expects y 0 to be at bottom but images have it at top.*/
    stbi_set_flip_vertically_on_load(true);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    unsigned char* texData = stbi_load("/home/saiteja/Qualcomm/preparation/opengl/6-camera/image/container.jpg", &width, &height, &nRChannels, 0);
    
    if(texData){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "ERROR::TEXTURE::LOAD_FAILED: " << std::endl;
    }

    stbi_image_free(texData);

    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    unsigned char* smileData = stbi_load("/home/saiteja/Qualcomm/preparation/opengl/6-camera/image/awesomeface.png", &width, &height, &nRChannels, 0);

    if(smileData){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, smileData);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    /* 
    * Enable depth testing so that the cube is properly rendered and a few triangles are not drawn on each othere
    */
   glEnable(GL_DEPTH_TEST);

   /*
    * CAMERA: Camera pos, target and direction (x,y,z axes)
    */
//    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
//    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);

//    // Get the three axes for camera using Gram-Schmidt proces.
//    glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
//    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
//    glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
//    glm::vec3 cameraUp = glm::normalize(glm::cross(cameraDirection, cameraRight));


    /*
     * MOUSE SCROLL: Move with mouse scroll 
     */
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwSetCursorPosCallback(window, mouseCallBack);
    glfwSetScrollCallback(window, scrollCallback);

    /*
     * Render Loop: Each iteration is called a frame
     */
    while (!glfwWindowShouldClose(window)){
        /* Inputs */
        processInput(window);

        /* Render */
        glClearColor(0.8f, 0.8f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        sh1.use();
        sh1.setInt("inTexture2", 1);
        unsigned int modelLoc = glGetUniformLocation(sh1.ID, "model");
        unsigned int viewLoc = glGetUniformLocation(sh1.ID, "view");
        unsigned int projectionLoc = glGetUniformLocation(sh1.ID, "projection");

        glm::mat4 view;
        view = glm::lookAt(cameraPos, cameraFront + cameraPos, cameraUp);
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(zoom), 800.0f/600.0f, 0.1f, 100.0f);
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(VAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture1);
        for(int i = 0; i < 10; i++){
            /* 
            * Create a transformation matrix
            */
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(cubePositions[i].x, cubePositions[i].y, cubePositions[i].z));
            model = glm::rotate(model, (float)20 * i, glm::vec3(1.0f, 0.3f, 0.5f));
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        glBindVertexArray(0);

        /* Poll events and swap buffers */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
exit:
    glfwTerminate();
    return 0;
}