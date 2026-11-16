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
#include <camera/camera.h>
#include <global.h>
#include <primatives.h>
#include <block/entities.h>

void window_init(Global * global){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    global->renderer.window = glfwCreateWindow(global->renderer.width, global->renderer.height, "Minecraft_Clone", NULL, NULL);
    glfwMakeContextCurrent(global->renderer.window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSetInputMode(global->renderer.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
    glfwSetCursorPosCallback(global->renderer.window, mouse_callback);  
    glViewport(0, 0, global->renderer.width, global->renderer.height);
    setupCamera((vec3){0.0f, 4.0f,  3.0f}, (vec3){0.0f, 0.0f, -1.0f}, (vec3){0.0f, 1.0f,  0.0f}, 0.2, &global->camera, global->renderer.width, global->renderer.height, 0.1f);
    glEnable(GL_DEPTH_TEST);
    
}

void mouse_callback(GLFWwindow* window, f64 xposIn, f64 yposIn){
    f32 xpos = (f32)xposIn; f32 ypos = (f32)yposIn;
    moveCamera(xpos,ypos,&global.camera);
    /*
    float xoffset = xpos - global.camera.lastX;
    float yoffset = global.camera.lastY - ypos; // reversed since y-coordinates go from bottom to top
    global.camera.lastX = xpos;
    global.camera.lastY = ypos;

    xoffset *= global.camera.sensitivity;
    yoffset *= global.camera.sensitivity;

    global.camera.yaw += xoffset;
    global.camera.pitch += yoffset;

    if (global.camera.pitch > 89.0f){
        global.camera.pitch = 89.0f;
    }
    if (global.camera.pitch < -89.0f){
        global.camera.pitch = -89.0f;
    }

    vec3 front = GLM_VEC3_ONE_INIT;
    front[0] = cos(glm_rad(global.camera.yaw)) * cos(glm_rad(global.camera.pitch));
    front[1] = sin(glm_rad(global.camera.pitch));
    front[2] = sin(glm_rad(global.camera.yaw)) * cos(glm_rad(global.camera.pitch));
    glm_normalize(front);
    glm_vec3_copy(front, global.camera.front);
    */
}

