#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "includes/utils.h"
#include "includes/shader_s.h"

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

    const char* vertexPath = "/Users/bytedance/Documents/OpenGL/project/src/shaders/texture.vs";
    const char* fragmentPath = "/Users/bytedance/Documents/OpenGL/project/src/shaders/texture.fs";
    Shader ourShader = Shader(vertexPath, fragmentPath);

    float vertices[] = {
        // 每行的前3个参数是位置，中间3个参数是颜色，后2个参数是纹理坐标
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,     // 右上角
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,    // 右下角
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,   // 左下角
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f     // 左上角
    };
    unsigned int indices[] = {
        0, 1, 3,    // 第一个三角形
        1, 2, 3     // 第二个三角形
    };
    unsigned int* objects = Utils::initObjects(vertices, sizeof(vertices), indices, sizeof(indices));
    unsigned int VAO = objects[0];
    unsigned int VBO = objects[1];
    unsigned int EBO = objects[2];
    std::cout << "VAO = " << VAO << std::endl;
    std::cout << "VBO = " << VBO << std::endl;
    std::cout << "EBO = " << EBO << std::endl;

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) nullptr);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    unsigned int texture = Utils::initTexture("/Users/bytedance/Documents/OpenGL/project/textures/container.jpeg", true);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindTexture(GL_TEXTURE_2D, texture);

        ourShader.use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}