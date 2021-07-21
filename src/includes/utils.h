#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace Utils {
    /**
     * @return 成功时返回window，失败时返回nullptr
     */
    GLFWwindow* initOpenGL();

    /**
     * @return 一个数组，内含三个参数，分别对应VAO、VBO、EBO
     */
    unsigned int* initObjects(
        float* vertices,
        int verticesSize,
        unsigned int* indices,
        int indicesSize
    );

    /**
     * @param path 图片文件名
     * @param verticalFlip 载入图片时是否翻转y轴
     * @return texture
     */
    unsigned int initTexture(
        const char* path,
        bool verticalFlip = false
    );
}
