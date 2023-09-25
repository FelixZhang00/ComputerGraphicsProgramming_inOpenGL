//  Copyright © 2019 Shinernd. All rights reserved.

#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#define numVAOs 1
#include "Utils.h"

// GLuint : unsigned int
GLuint renderingProgram;
GLuint vao[numVAOs];
// location of triangle on x axis
float x = 0.0f;
// offset for moving the triangle
float inc = 0.01f;

using namespace std;


void init (GLFWwindow* window) {
    renderingProgram = Utils::createShaderProgram("../vertShader.glsl","../fragShader.glsl");
    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);
}

void display(GLFWwindow* window, double currentTime) {
    // clear the background to black, each time
    glClear(GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(renderingProgram);

    // move the triangle along x axis
    x += inc;
    // switch to moving the triangle to the left
    if (x > 1.0f) inc = -0.01f;
    // switch to moving the triangle to the right
    if (x < -1.0f) inc = 0.01f;

    // get ptr to "offset"
    GLuint offsetLoc = glGetUniformLocation(renderingProgram, "offset");

    glProgramUniform1f(renderingProgram, offsetLoc, x);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}

int main(void) {
    if (!glfwInit()) {exit(EXIT_FAILURE);}
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // I don't know what this does
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // and neither this
    GLFWwindow* window = glfwCreateWindow(600, 600, "Chapter2 - program2", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) {exit(EXIT_FAILURE);}
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