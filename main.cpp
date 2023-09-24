//  Copyright © 2019 Shinernd. All rights reserved.

#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#define numVAOs 1

// GLuint : unsigned int
GLuint renderingProgram;
GLuint vao[numVAOs];

using namespace std;

// displays the contents of OpenGL's log when GLSL compilation failed
void printShaderLog(GLuint shader) {
    int len = 0;
    int chWrittn = 0;
    char* log;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
    if (len > 0) {
        log = (char*)malloc(len);
        glGetShaderInfoLog(shader, len, &chWrittn, log);
        cout << "Shader Info Log: " << log << endl;
        free(log);
    }
}

// displays the contents of OpenGL's log when GLSL linking failed
void printProgramLog(int prog) {
    int len = 0;
    int chWrittn = 0;
    char* log;
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
    if (len > 0) {
        log = (char*)malloc(len);
        glGetProgramInfoLog(prog, len, &chWrittn, log);
        cout << "Program Info Log: " << log << endl;
        free(log);
    }
}

// checks the OpenGL error flag for the occurrrence of an OpenGL error
// detects both GLSL compilation errors and OpenGL runtime errors
bool checkOpenGLError() {
    bool foundError = false;
    int glErr = glGetError();
    while (glErr != GL_NO_ERROR) {
        cout << "glError: " << glErr << endl;
        foundError = true;
        glErr = glGetError();
    }
    return foundError;
}

string readShaderSource(const char *filePath) {
    string content = "";
    ifstream fileStream(filePath, ios::in);
//    cerr << "Error: " << strerror(errno) << endl;  // No such file or directory
//    cout << fileStream.is_open() << endl;  // 0
    string line = "";
    while (!fileStream.eof()) {
        getline(fileStream, line);
        content.append(line + "\n");
    }
    fileStream.close();
    return content;
}



GLuint createShaderProgram() {

    string vertShaderStr = readShaderSource("vertShader.glsl");
    string fragShaderStr = readShaderSource("fragShader.glsl");

    const char* vertShaderSrc = vertShaderStr.c_str();
    const char* fragShaderSrc = fragShaderStr.c_str();

    // glCreateShader : generates the two shaders of types GL_VERTEX_SHADER and GL_FRAGMENT_SHADER
    // OpenGL creates each shader object, and returns an integer ID for each
    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

    // loads the GLSL code from the strings into the empty shader objects
    // glShaderSource(ShaderObject, NumberOfStrings : 1, ArrayOfPointers, -)
    glShaderSource(vShader, 1, &vertShaderSrc, nullptr);
    glShaderSource(fShader, 1, &fragShaderSrc, nullptr);

    // the shaders are each compiled
    glCompileShader(vShader);
    glCompileShader(fShader);

    // the integer ID of a program object
    GLuint vfProgram = glCreateProgram();

    // attatches each of the shaders to the program object
    glAttachShader(vfProgram, vShader);
    glAttachShader(vfProgram, fShader);

    // requests that the GLSL compiler ensure that the shaders are compatible
    glLinkProgram(vfProgram);

    return vfProgram;
}


void init (GLFWwindow* window) {
    renderingProgram = createShaderProgram();

    // VAO : Vertex Array Objects, OpenGL requires at least one VAO
    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);
}

void display(GLFWwindow* window, double currentTime) {

    // loads the program containing the two compiled shaders into the OpenGL pipeline stages (onto the GPU)
    glUseProgram(renderingProgram);

    glPointSize(30.0f);

    // initiates pipeline processing
    // mode: GL_POINTS, from 0, one (point)
    glDrawArrays(GL_POINTS, 0, 1);
}

int main(void) {
    if (!glfwInit()) {exit(EXIT_FAILURE);}
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // I don't know what this does
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // and neither this
    GLFWwindow* window = glfwCreateWindow(600, 600, "Chapter2 - program2", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) {exit(EXIT_FAILURE);}                // without the line 80 or 81, this makes an error
    glfwSwapInterval(1);

    init(window);

    while (!glfwWindowShouldClose(window)) {
        display(window, glfwGetTime());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}