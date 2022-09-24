#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "log/Log.h"
#include "MiyaEngine.h"
#include "TriangleImp.h"
namespace MiyaApp {
    void TriangleImp::Render(Miya::Timestep ts){

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shader->use();
        glBindVertexArray(VAO); 
        glDrawArrays(GL_TRIANGLES, 0, 3);

    }
    void TriangleImp::Init()
    {

        shader = new Miya::Shader_("resource/shaders/TriangleImp_V.txt", "resource/shaders/TriangleImp_F.txt");
        

        // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------
        float vertices[] = {
            -0.5f, -0.5f, 0.0f, // left  
             0.5f, -0.5f, 0.0f, // right 
             0.0f,  0.5f, 0.0f  // top   
        };

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);
        shader->use();
    }
    void TriangleImp::Destory()
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteProgram(shaderProgram);
    }

}