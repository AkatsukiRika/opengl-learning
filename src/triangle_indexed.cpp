#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

/** 函数声明 START **/
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow *window);
void initGlfw();
GLFWwindow* createWindow();
bool initGlad();
unsigned int buildVertexShader();
unsigned int buildFragmentShader();
unsigned int linkShaders(unsigned int vertexShader, unsigned int fragmentShader);
std::vector<unsigned int> configureVertex();
/** 函数声明 END **/

/** 常量定义 START **/
const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\0";
float vertices[] = {
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f
};
unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
};
/** 常量定义 END **/

int main() {
    initGlfw();

    GLFWwindow* window = createWindow();

    if (!initGlad()) {
        return -1;
    }

    unsigned int vertexShader = buildVertexShader();

    unsigned int fragmentShader = buildFragmentShader();

    unsigned int shaderProgram = linkShaders(vertexShader, fragmentShader);

    std::vector<unsigned int> vector = configureVertex();
    unsigned int VAO = vector[0];
    unsigned int VBO = vector[1];
    unsigned int EBO = vector[2];

    // 创建渲染循环
    while (!glfwWindowShouldClose(window)) {
        // 处理输入
        process_input(window);

        // 渲染指令
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 绘制三角形
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        int vertexCount = 6;
        glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, nullptr);

        // 检查并调用事件
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 释放资源
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    // 结束程序
    glfwTerminate();
    return 0;
}

/** 函数定义 START **/
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void initGlfw() {
    // 初始化GLFW
    glfwInit();
    // 配置GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 使用核心模式
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);    // macOS系统使用
#endif
}

GLFWwindow* createWindow() {
    // 创建窗口对象
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    // 当窗口调整大小时，改变viewport大小
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    return window;
}

/**
 * @return 初始化成功返回true，否则返回false
 */
bool initGlad() {
    // 初始化GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    } else {
        return true;
    }
}

unsigned int buildVertexShader() {
    // 创建顶点着色器对象
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    // 检查编译错误
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return vertexShader;
}

unsigned int buildFragmentShader() {
    // 创建片段着色器对象
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    // 检查编译错误
    int success;
    char infoLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return fragmentShader;
}

unsigned int linkShaders(unsigned int vertexShader, unsigned int fragmentShader) {
    // 创建着色器程序对象
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // 检测链接着色器程序是否失败
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
    }

    // 删除着色器对象
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

/**
 * @return 一个Vector，第一个参数是VAO，第二个参数是VBO，第三个参数是EBO
 */
std::vector<unsigned int> configureVertex() {
    // 顶点数组对象：Vertex Array Object (VAO)
    // 顶点缓冲对象: Vertex Buffer Object (VBO)
    // 索引缓冲对象：Element Buffer Object (EBO)
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    std::vector<unsigned int> vector;
    vector.push_back(VAO);
    vector.push_back(VBO);
    vector.push_back(EBO);
    return vector;
}
/** 函数定义 END **/
