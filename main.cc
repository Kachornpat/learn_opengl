#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.hh"
#include "camera.hh"
#include "stb_image.h"


void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void inputProcess(GLFWwindow* window, float deltaTime);

Camera *ourCamera = NULL;

float lastFrame = 0.0f;
float lastX = 400, lastY = 800;
float deltaTime = 0.0f;
bool firstMouse = true;

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); 
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glViewport(0, 0, 800, 600);

    glEnable(GL_DEPTH_TEST);
    float vertices[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
         0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
         0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

         0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
         0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
         0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
         0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,

    };



    unsigned int cubeVAO, cubeVBO, lightVAO;
    glGenVertexArrays(1, &cubeVAO);
    glBindVertexArray(cubeVAO);

    glGenBuffers(1, &cubeVBO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // unsigned int textures[2];
    // glGenTextures(2, textures);

    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, textures[0]);

    // int width, height, nrChannels;
    // unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);

    // if (data) {
    //     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    //     glGenerateMipmap(GL_TEXTURE_2D);
    // }
    // else {
    //     std::cout << "Failed to load texture[0]" << std::endl;
    // }
    // stbi_image_free(data);

    // glActiveTexture(GL_TEXTURE1);
    // glBindTexture(GL_TEXTURE_2D, textures[1]);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // stbi_set_flip_vertically_on_load(true);
    // data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
    // if (data) {
    //     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    //     glGenerateMipmap(GL_TEXTURE_2D);
    // }
    // else {
    //     std::cout << "Failed to load texture[1]" << std::endl;
    // }
    // stbi_image_free(data);

    Shader lightShader("shader/lightShader.vs", "shader/lightShader.fs");
    Shader cubeShader("shader/cubeShader.vs", "shader/cubeShader.fs");
    ourCamera = new Camera();

    glm::mat4 model, view, projection;
    unsigned int modelLoc, viewLoc, projectionLoc;
    
    while (!glfwWindowShouldClose(window)) {
	float currentFrame = (float) glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

        inputProcess(window, deltaTime);

        // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // ourShader.setInt("texture1", 0);
        // ourShader.setInt("texture2", 1);

        // ourShader.use();
	    
        view = ourCamera->getView();
        projection = glm::perspective(glm::radians(ourCamera->Fov), 800.0f / 600.0f, 0.1f, 100.0f);

        glm::vec3 lightPos(2.0f, 2.0f, -2.0f);

	// draw cube
        cubeShader.use();
        cubeShader.setVec3("light.position", lightPos);
	cubeShader.setVec3("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
	cubeShader.setVec3("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
	cubeShader.setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
	cubeShader.setVec3("viewPos", ourCamera->Position);
	
	cubeShader.setVec3("material.ambient", glm::vec3(1.0f, 0.5f, 0.31f));
	cubeShader.setVec3("material.diffuse", glm::vec3(1.0f, 0.5f, 0.31f));
	cubeShader.setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
	cubeShader.setFloat("material.shininess", 32.0f);


        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f));
	modelLoc = glGetUniformLocation(cubeShader.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        viewLoc = glGetUniformLocation(cubeShader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
 
        projectionLoc = glGetUniformLocation(cubeShader.ID, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));


        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
	
	// draw light 
        lightShader.use(); 
	model = glm::mat4(1.0f);
	model = glm::translate(model, lightPos);
	model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
	modelLoc = glGetUniformLocation(lightShader.ID, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        viewLoc = glGetUniformLocation(lightShader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        projectionLoc = glGetUniformLocation(lightShader.ID, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &lightVAO);
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteBuffers(1, &cubeVBO);
    // glDeleteBuffers(1, &lightEBO);
    // glDeleteTextures(2, textures);

    glfwTerminate();
    return 0;

}

void inputProcess(GLFWwindow *window, float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    const float cameraSpeed = 1.5f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            ourCamera->Position += cameraSpeed * ourCamera->Up;
        else
            ourCamera->Position += cameraSpeed * ourCamera->Front;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            ourCamera->Position -= cameraSpeed * ourCamera->Up;
        else
            ourCamera->Position -= cameraSpeed * ourCamera->Front;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        ourCamera->Position -= glm::normalize(glm::cross(ourCamera->Front, ourCamera->Up)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        ourCamera->Position += glm::normalize(glm::cross(ourCamera->Front, ourCamera->Up)) * cameraSpeed;

    
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height){
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{

    if (firstMouse)
    {
        lastX = (float) xpos;
        lastY = (float) ypos;
        firstMouse = false;
    }
    float xoffset = (float) xpos - lastX;
    float yoffset = (float) ypos - lastY;
    lastX = (float) xpos;
    lastY = (float) ypos;

    const float sensitivity = 0.5f * deltaTime;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    ourCamera->updateView(yoffset, xoffset);

}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    ourCamera->updateFov((float) yoffset);
}
