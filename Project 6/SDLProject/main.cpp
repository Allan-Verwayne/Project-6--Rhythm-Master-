/*
 * Author: Allan Verwayne
 * Assignment: Rhythm Master
 * Date due: 2023-12-15, 3:00pm
 * I pledge that I have completed this assignment without
 * collaborating with anyone else, in conformance with the
 * NYU School of Engineering Policies and Procedures on
 * Academic Misconduct.
 */

#define GL_SILENCE_DEPRECATION
#define GL_GLEXT_PROTOTYPES 1
#define FIXED_TIMESTEP 0.0166666f

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#include <SDL_mixer.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"
#include "cmath"
#include <ctime>
#include <vector>
#include "Entity.h"
#include "Utility.h"
#include "Scene.h"
#include "Start.h"
//#include "Song_Select.h"
#include "Song_1.h"
#include "Results.h"
//#include "Effects.h"

// Constants
const int WINDOW_WIDTH  = 640, // 640, 1280, 1920
          WINDOW_HEIGHT = 480; // 480, 960, 1080

const float BG_RED      = 0.0f, //0.150f
            BG_GREEN    = 0.0f,
            BG_BLUE     = 0.0f, //0.250f
            BG_OPACITY  = 1.0f;

const int VIEWPORT_X = 0,
          VIEWPORT_Y = 0,
          VIEWPORT_WIDTH = WINDOW_WIDTH,
          VIEWPORT_HEIGHT = WINDOW_HEIGHT;

const char V_SHADER_PATH[] = "shaders/vertex_textured.glsl",
           F_SHADER_PATH[] = "shaders/fragment_textured.glsl";

const float MILLISECONDS_IN_SECOND = 1000.0;

// Globals
Scene*  g_current_scene;
Start_Menu* g_start_screen;
Song_1* g_song;

Result* g_result;

SDL_Window* g_display_window;
bool g_game_is_running = true;

ShaderProgram g_program;
glm::mat4 g_view_matrix, g_projection_matrix;

float g_previous_ticks = 0.0f;
float g_accumulator = 0.0f;

int num_lives;

void switch_to_scene(Scene* scene) {
    g_current_scene = scene;
    g_current_scene->initialise();
}

void initialise() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    g_display_window = SDL_CreateWindow("RHYTHM MASTER",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_OPENGL);

    SDL_GLContext context = SDL_GL_CreateContext(g_display_window);
    SDL_GL_MakeCurrent(g_display_window, context);

#ifdef _WINDOWS
    glewInit();
#endif

    glViewport(VIEWPORT_X, VIEWPORT_Y, VIEWPORT_WIDTH, VIEWPORT_HEIGHT);

    g_program.load(V_SHADER_PATH, F_SHADER_PATH);

    g_view_matrix = glm::mat4(1.0f);
    g_projection_matrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);

    g_program.set_projection_matrix(g_projection_matrix);
    g_program.set_view_matrix(g_view_matrix);

    glUseProgram(g_program.get_program_id());

    glClearColor(BG_RED, BG_GREEN, BG_BLUE, BG_OPACITY);
    
    g_start_screen = new Start_Menu();
    g_song = new Song_1();
    g_result = new Result();
    
    switch_to_scene(g_start_screen);

    // enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void process_input() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            // End game
            case SDL_QUIT:
            case SDL_WINDOWEVENT_CLOSE:
                g_game_is_running = false;
                break;
                
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        if (g_current_scene == g_song) {
                            g_current_scene->m_state.keys[0].key_hit();
                            Mix_PlayChannel(-1, g_current_scene->m_state.tap, 0);
                        }
                        break;
                        
                        // Down Input
                    case SDLK_DOWN:
                        if (g_current_scene == g_song) {
                            g_current_scene->m_state.keys[1].key_hit();
                            Mix_PlayChannel(-1, g_current_scene->m_state.tap, 0);
                        }
                        break;
                        
                    case SDLK_UP:
                        if (g_current_scene == g_song) {
                            g_current_scene->m_state.keys[2].key_hit();
                            Mix_PlayChannel(-1, g_current_scene->m_state.tap, 0);
                        }
                        break;
                        
                        
                    case SDLK_RIGHT:
                        if (g_current_scene == g_song) {
                            g_current_scene->m_state.keys[3].key_hit();
                            Mix_PlayChannel(-1, g_current_scene->m_state.tap, 0);
                        }
                        break;
                        
                    case SDLK_q:
                        // Quit the game with a keystroke
                        g_game_is_running = false;
                        break;
                        
                        // Pause Game
                    case SDLK_p:
                        if (Mix_PausedMusic()) {
                            Mix_ResumeMusic();
                        }
                        else {
                            Mix_PauseMusic();
                        }
                        break;

                        // Start Game
                    case SDLK_RETURN:
                        switch_to_scene(g_song);
                        break;
                        
                    default:
                        break;
                }
                
            default:
                break;
        }
    }

//    const Uint8* key_state = SDL_GetKeyboardState(NULL);

    if (g_current_scene != g_start_screen) {
//        if (key_state[SDL_SCANCODE_LEFT]) {
//        }
//        else if (key_state[SDL_SCANCODE_DOWN]) {
//        }
//        else if (key_state[SDL_SCANCODE_UP]) {
//        }
//        else if (key_state[SDL_SCANCODE_RIGHT]) {
//        }
        
//        if (g_current_scene->m_state.keys[0].get_key_active()) {
//            std::cout << "active" << std::endl;
//        }
//        else { std::cout << "not active" << std::endl; }
//        if (g_current_scene->m_state.keys[0].check_collision(g_current_scene->m_state.notes)) {
//            std::cout << "collided" << std::endl;
//        }
    }

}

void update() {
    float ticks = (float)SDL_GetTicks() / MILLISECONDS_IN_SECOND;
    float delta_time = ticks - g_previous_ticks;
    g_previous_ticks = ticks;

    delta_time += g_accumulator;

    if (delta_time < FIXED_TIMESTEP) {
        g_accumulator = delta_time;
        return;
    }

    while (delta_time >= FIXED_TIMESTEP) {
        // update scene
        g_current_scene->update(FIXED_TIMESTEP);

        delta_time -= FIXED_TIMESTEP;
    }

    g_accumulator = delta_time;

    // Prevent the camera from showing anything outside of the "edge" of the level
    g_view_matrix = glm::mat4(1.0f);
    
    g_result->lives = g_current_scene->lives;
    
}

void render() {
    g_program.set_view_matrix(g_view_matrix);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(g_program.get_program_id());
    // render scene
    g_current_scene->render(&g_program);

    SDL_GL_SwapWindow(g_display_window);
}

void shutdown() {
    SDL_Quit();
    delete g_start_screen;
    delete g_song;
    delete g_result;
}

// ––––– DRIVER GAME LOOP ––––– //
int main(int argc, char* argv[]) {
    initialise();

    while (g_game_is_running) {
        process_input();
        update();
        if (!Mix_PlayingMusic()) {
            switch_to_scene(g_result);
        }
        render();
    }

    shutdown();
    return 0;
}
