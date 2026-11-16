#include <glad/glad.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string.h>
#include <global.h>
#include <io/array.h>
#include <math.h>
#include <render/shader.h>
#include <stb_image.h>
#include <stdbool.h>
#include <types.h>
#include <render/render.h>
#include <render/texture.h>
#include <primatives.h>
#include <block/entities.h>

int RendererInitCube(Render_State_Internal *r){
    glGenVertexArrays(1, &r->VAO);
    glGenBuffers(1, &r->VBO);
    glGenBuffers(1, &r->EBO);
    // bind the Vertex Array Entityfirst, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(r->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, r->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_DYNAMIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, r->EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(obj->indices), obj->indices, GL_DYNAMIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute (uv)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return 0;
}

int texInit(const char * path, u32 * texture, bool flip, bool has_rgba){
    stbi_set_flip_vertically_on_load(flip); 
    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, *texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data){
        if(has_rgba){glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);}
        else{glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);}
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        printf("failed to load texture: %s\n", path);
        stbi_image_free(data);
        return -1;
    }
    stbi_image_free(data);
    return 0;
}

void Translate(vec3 pos, u32 ID){
    mat4 model = GLM_MAT4_IDENTITY_INIT;
    glm_translate(model, pos);
    setMat4("model", model,ID);
}


void render_begin(Camera * c){
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    use(global.state.shader.ID); 
    glBindTexture(GL_TEXTURE_2D, global.state.texture);
    setInt("texture1", 0, global.state.shader.ID);
    setMat4("projection", c->projection, global.state.shader.ID);
    setMat4("view", c->view, global.state.shader.ID);
}

void render_end(){
    glfwSwapBuffers(global.renderer.window);
    glfwPollEvents();  
}