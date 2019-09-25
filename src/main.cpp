#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
//#include <iterator>
//#include <chrono>
//#include <thread>
#include <cmath>
#include <string>
#include <vector>

#include "objects.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "game.hpp"
#include "world.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);


int main(){
    int exitCode = 0;

    //initilize the engine and exit if error
    //init glfw
    glfwInit(); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //needed for mac
  
    //create window
    GLFWwindow* window = glfwCreateWindow(600, 600, "Greenfoot++ v0.0.1", NULL, NULL);
    if (window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    //register callback function for viewport
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

    //make sure glad works
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -2;
    }

    //Create Vector containing all the worlds
    std::vector<world*> worlds;
    exitCode = game_init(&worlds);
    if(exitCode < 0){glfwSetWindowShouldClose(window, true);};

    world* activeWorld;
    try{
        activeWorld = worlds.at(exitCode);
    }
    catch(const std::exception& e){
        std::cerr << e.what() << '\n';
        glfwSetWindowShouldClose(window, true);
    }

    //Clear up
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //render loop
    while(!glfwWindowShouldClose(window)){
        //run the game loop
        exitCode = game_loop(window, activeWorld);

        //if egative return exit loop
        if(exitCode < 0){
            break;
        }

        //try setting next World
        try{
            activeWorld = worlds.at(exitCode);
        }
        catch(const std::exception& e){
            std::cerr << e.what() << '\n';
            break;
        }
        
    }

    glfwSetWindowShouldClose(window, true);

    //try clearing up
    try{
        worlds.clear();
    }
    catch(const std::exception& e){
        std::cerr << e.what() << '\n';
    }

    //close the window + clean up
    glfwTerminate();

    return exitCode;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}