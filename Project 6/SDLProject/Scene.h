#pragma once
#define GL_SILENCE_DEPRECATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1
#include <SDL_mixer.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"
#include "Utility.h"
#include "Entity.h"

struct State {
    // Objects
    Entity* notes;
    Entity* keys;
    
    // Music
    Mix_Music *music;
    Mix_Chunk *tap;

    int next_scene_id;
};

class Scene {
public:
    
    State m_state;
    
    GLuint font_texture_id;
    GLuint bg_texture_id;
    
    int lives = 10;

    virtual void initialise() = 0;
    virtual void update(float delta_time) = 0;
    virtual void render(ShaderProgram* program) = 0;

    State const get_state() const { return m_state; }
};
