#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "includes/utils.h"
#include "includes/shader_s.h"
#include "includes/values.h"
#include "includes/glm/glm.hpp"
#include "includes/glm/gtc/matrix_transform.hpp"
#include "includes/glm/gtc/type_ptr.hpp"

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main() {
    GLFWwindow* window = Utils::initOpenGL();
    if (window == nullptr) {
        return -1;
    }

    const char* vertexPath = "/Users/bytedance/Documents/OpenGL/project/src/shaders/coordinates.vs";
    const char* fragmentPath = "/Users/bytedance/Documents/OpenGL/project/src/shaders/texture.fs";
    Shader ourShader = Shader(vertexPath, fragmentPath);

    unsigned int* objects = Utils::initObjects(
        Values::cubeVertices,
        sizeof(Values::cubeVertices)
    );
    unsigned int VAO = objects[0];
    unsigned int VBO = objects[1];
    std::cout << "VAO = " << VAO << std::endl;
    std::cout << "VBO = " << VBO << std::endl;

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) nullptr);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int texture = Utils::initTexture("/Users/bytedance/Documents/OpenGL/project/textures/container.jpeg", true);

    // 启用深度测试
    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindTexture(GL_TEXTURE_2D, texture);

//        // 模型矩阵
//        glm::mat4 model;
//        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
//        // 观察矩阵
//        glm::mat4 view;
//        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
//        // 投影矩阵
//        glm::mat4 projection;
//        projection = glm::perspective(glm::radians(45.0f), 4.0f/3.0f, 0.1f, 100.0f);
//        // 传入着色器
//        ourShader.use();
//        int modelLoc = glGetUniformLocation(ourShader.ID, "model");
//        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//        int viewLoc = glGetUniformLocation(ourShader.ID, "view");
//        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
//        int projectionLoc = glGetUniformLocation(ourShader.ID, "projection");
//        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 10; i++) {
            glm::mat4 model;
            model = glm::translate(model, Values::cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle) + (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(1.0f, 0.3f, 0.5f));

            glm::mat4 view;
            view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

            glm::mat4 projection;
            projection = glm::perspective(glm::radians(45.0f), 4.0f/3.0f, 0.1f, 100.0f);

            ourShader.use();
            ourShader.setMat4("model", model);
            ourShader.setMat4("view", view);
            ourShader.setMat4("projection", projection);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}