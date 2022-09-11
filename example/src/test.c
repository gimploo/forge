// To compile with gcc:  (tested on Ubuntu 14.04 64bit):
//	 g++ sdl2_opengl.cpp -lSDL2 -lGL
// To compile with msvc: (tested on Windows 7 64bit)
//   cl sdl2_opengl.cpp /I C:\sdl2path\include /link C:\path\SDL2.lib C:\path\SDL2main.lib /SUBSYSTEM:CONSOLE /NODEFAULTLIB:libcmtd.lib opengl32.lib

#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <poglib/basic.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

typedef int32_t i32;
typedef uint32_t u32;
typedef int32_t b32;

#define WinWidth 1000
#define WinHeight 1000

int sdl_main (void)
{
    u32 WindowFlags = SDL_WINDOW_OPENGL;
    SDL_Window *Window = SDL_CreateWindow("OpenGL Test", 0, 0, WinWidth, WinHeight, WindowFlags);
    assert(Window);

    SDL_GL_CreateContext(Window);

    /*int *foo = NULL;*/
    printf("Prinf says hello\n");
    SDL_Log("SDL_Log says hello\n");

    b32 Running = 1;
    b32 FullScreen = 0;
    while (Running)
    {
        SDL_Event Event;
        while (SDL_PollEvent(&Event))
        {
            if (Event.type == SDL_KEYDOWN)
            {
                switch (Event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        Running = 0;
                        break;
                        case 'f':
                        FullScreen = !FullScreen;
                        if (FullScreen)
                            SDL_SetWindowFullscreen(Window, WindowFlags | SDL_WINDOW_FULLSCREEN_DESKTOP);
                        else
                            SDL_SetWindowFullscreen(Window, WindowFlags);
                    break;
                    default:
                    break;
                }
            }
            else if (Event.type == SDL_QUIT)
            {
                Running = 0;
            }
        }

        glViewport(0, 0, WinWidth, WinHeight);
        glClearColor(1.f, 0.f, 1.f, 0.f);
        glClear(GL_COLOR_BUFFER_BIT);

        SDL_GL_SwapWindow(Window);
    }
    return 1;
}

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}
 
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int glfw_main(void)
{
 
    GLFWwindow* window;
    GLuint vertex_buffer, vertex_shader, fragment_shader, program;
    GLint mvp_location, vpos_location, vcol_location;
 
    glfwSetErrorCallback(error_callback);
 
    if (!glfwInit())
        exit(EXIT_FAILURE);
 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
 
    window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
 
    glfwSetKeyCallback(window, key_callback);
 
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
 
 
    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;
 
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;
 
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
 
 
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
 
    glfwDestroyWindow(window);
 
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

int main(const int argc, const char *argv[])
{
    /*sdl_main();*/
    glfw_main();
    return 0;
}
