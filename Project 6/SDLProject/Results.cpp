#include "Results.h"
#include "Utility.h"


Result::~Result() {
    Mix_FreeMusic(m_state.music);
}

void Result::initialise() {
    font_texture_id = Utility::load_texture("game_files/font.png");
    
    // Background
    bg_texture_id = Utility::load_texture("game_files/Stage.png");
    
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    
    m_state.music = Mix_LoadMUS("game_files/In the Light of the Setting Sun.mp3");
    Mix_PlayMusic(m_state.music, -1);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 16.0f);
    
}

void Result::update(float delta_time) {}


void Result::render(ShaderProgram *program) {
    Utility::draw_object(program, bg_texture_id, glm::vec3(0.0f), glm::vec3(8.0f));
    if (lives == 0) {
        Utility::draw_text(program, font_texture_id, "FAILED...", 1.0f, -0.3f, glm::vec3(-3.0f,  1.0f, 0.0f));
    }
    else {
        Utility::draw_text(program, font_texture_id, "SONG CLEAR!", 1.0f, -0.3f, glm::vec3(-3.5f,  1.0f, 0.0f));
    }
    
}
