#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include "objects.hpp"

class world{
private:
    std::vector <object*> WorldObjects;
    std::vector <shader*> WorldShaders;
    std::vector <texture2D*> WorldTextures;
public:

    world();
    ~world();

    int addShader(shader*);
    int addTexture(texture2D*);
    int addObject(object*);

    shader* getShader(int);
    texture2D* getTexture(int);
    object* getObject(int);

    void tick(GLFWwindow* window);
    int test();
};