#include "Results.h"
#include "Utility.h"


Result::~Result() {
    Mix_FreeMusic(m_state.music);
}

void Result::initialise() {
    // Text
    font_texture_id = Utility::load_texture("game_files/font.png");
    
    // Background
    bg_texture_id = Utility::load_texture("game_files/Stage.png");
    
    // Music
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    
    m_state.music = Mix_LoadMUS("game_files/In the Light of the Setting Sun.mp3");
    Mix_PlayMusic(m_state.music, -1);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 16.0f);
    
    
    miku.set_entity_type(OBJECT);
    miku.move_down();
    
    if (lives == 0 ) {
        miku.m_texture_id = miku_lose_texture_id;
        miku.m_animations[miku.DOWN]  = new int[3] { 0, 1, 2 };
        miku.m_animation_indices = miku.m_animations[miku.DOWN];
        miku.m_animation_frames = 6;
        miku.m_animation_index  = 0;
        miku.m_animation_time   = 0.0f;
        miku.m_animation_cols   = 3;
        miku.m_animation_rows   = 1;
    }
    else {
        miku.m_texture_id = miku_win_texture_id;
        miku.m_animations[miku.DOWN]  = new int[12] { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
        miku.m_animation_indices = miku.m_animations[miku.DOWN];
        miku.m_animation_frames = 12;
        miku.m_animation_index  = 0;
        miku.m_animation_time   = 0.0f;
        miku.m_animation_cols   = 12;
        miku.m_animation_rows   = 1;
    }
    
    miku.set_position(glm::vec3(0, -1.0f, 0.0f));
    
}

void Result::update(float delta_time) {
    miku.update(delta_time, 0, 0, 0);
}


void Result::render(ShaderProgram *program) {
    
    Utility::draw_object(program, bg_texture_id, glm::vec3(0.0f), glm::vec3(8.0f));
    miku.render(program);
    if (lives == 0) {
        Utility::draw_text(program, font_texture_id, "FAILED...", 1.0f, -0.3f, glm::vec3(-3.0f,  1.0f, 0.0f));
    }
    else {
        Utility::draw_text(program, font_texture_id, "SONG CLEAR!", 1.0f, -0.3f, glm::vec3(-3.5f,  1.0f, 0.0f));
    }
    
}
