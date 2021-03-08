#include <iostream>
#include <GLFW/glfw3.h>

int main() {

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(640, 480, "OpenGL", NULL, NULL);
    if (!window)
    {

        glfwTerminate();
        exit(EXIT_FAILURE);
    }
   
    

    while (!glfwWindowShouldClose(window))
    {

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}