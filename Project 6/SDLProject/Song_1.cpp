#include "Song_1.h"
#include "Utility.h"

Song_1::~Song_1() {
    delete [] m_state.notes;
    delete [] m_state.keys;
    Mix_FreeMusic(m_state.music);
    Mix_FreeChunk(m_state.tap);
}

void Song_1::initialise() {
    // Music
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    
    m_state.music = Mix_LoadMUS("game_files/Hibana_-Reloaded-_game_size.mp3");
    
    Mix_PlayMusic(m_state.music, 1);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 16.0f);
    
    m_state.tap = Mix_LoadWAV("game_files/01_button1.wav");
    Mix_VolumeChunk(m_state.tap, MIX_MAX_VOLUME / 50.0f);
    
    // Font
    font_texture_id = Utility::load_texture("game_files/font.png");
    
    // Background
    bg_texture_id = Utility::load_texture("game_files/Hibana_-Reloaded-.png");
    
    // Keys Existing
    GLuint key_texture_id = Utility::load_texture("game_files/Arrow.png");
    
    m_state.keys = new Entity[KEY_COUNT];
    for (int k = 0; k < KEY_COUNT; k++) {
        m_state.keys[k].set_entity_type(KEY);
        m_state.keys[k].m_texture_id = key_texture_id;
        m_state.keys[k].set_position(glm::vec3(k - 1.5f, -2.5f, 0.0f));
        
        m_state.keys[k].m_animation_frames = 4;
        m_state.keys[k].m_animation_index  = 0;
        m_state.keys[k].m_animation_time   = 0.0f;
        m_state.keys[k].m_animation_cols   = 8;
        m_state.keys[k].m_animation_rows   = 4;
    }
    
    m_state.keys[0].m_animations[m_state.keys[0].LEFT]  = new int[1] { 16 };
    m_state.keys[0].m_animation_indices = m_state.keys[0].m_animations[m_state.keys[0].LEFT];
    
    m_state.keys[1].m_animations[m_state.keys[1].DOWN]  = new int[1] { 17 };
    m_state.keys[1].m_animation_indices = m_state.keys[1].m_animations[m_state.keys[1].DOWN];
    
    m_state.keys[2].m_animations[m_state.keys[2].UP]    = new int[1] { 18 };
    m_state.keys[2].m_animation_indices = m_state.keys[2].m_animations[m_state.keys[2].UP];
    
    m_state.keys[3].m_animations[m_state.keys[3].RIGHT]  = new int[1] { 19 };
    m_state.keys[3].m_animation_indices = m_state.keys[3].m_animations[m_state.keys[3].RIGHT];
    
    // Notes Existing
    GLuint note_texture_id = Utility::load_texture("game_files/Arrow.png");
    
    m_state.notes = new Entity[NOTE_COUNT];
    for (int n = 0; n < NOTE_COUNT; n++) {
        m_state.notes[n].set_entity_type(NOTE);
        m_state.notes[n].m_texture_id = note_texture_id;
        float x;
        int dir = rand() % 4;
        
        if (dir == 0) {
            m_state.notes[n].m_animations[m_state.notes[n].LEFT]  = new int[4] { 0, 4, 8, 12 };
            m_state.notes[n].m_animation_indices = m_state.notes[n].m_animations[m_state.notes[n].LEFT];
            x = -1.5;
        }
        else if (dir == 1) {
            m_state.notes[n].m_animations[m_state.notes[n].DOWN]  = new int[4] { 1, 5, 9, 13 };
            m_state.notes[n].m_animation_indices = m_state.notes[n].m_animations[m_state.notes[n].DOWN];
            x = -0.5;
        }
        else if (dir == 2) {
            m_state.notes[n].m_animations[m_state.notes[n].UP]    = new int[4] { 2, 6, 10, 14 };
            m_state.notes[n].m_animation_indices = m_state.notes[n].m_animations[m_state.notes[n].UP];
            x =  0.5;
        }
        else {
            m_state.notes[n].m_animations[m_state.notes[n].RIGHT] = new int[4] { 3, 7, 11, 15 };
            m_state.notes[n].m_animation_indices = m_state.notes[n].m_animations[m_state.notes[n].RIGHT];
            x =  1.5;
        }
        
        m_state.notes[n].set_position(glm::vec3(x, (2.0f * n) + 6.0f, 0.0f));
        m_state.notes[n].m_animation_frames = 4;
        m_state.notes[n].m_animation_index  = 0;
        m_state.notes[n].m_animation_time   = 0.0f;
        m_state.notes[n].m_animation_cols   = 8;
        m_state.notes[n].m_animation_rows   = 4;
    }
    
    m_state.next_scene_id = 0;
}

void Song_1::update(float delta_time) {
    if (lives == 0) {
        Mix_HaltMusic();
        return;
    }
    
    if (Mix_PausedMusic()) return;
    
    // Keys
    for (int k = 0; k < KEY_COUNT; k++) {
        m_state.keys[k].update(delta_time, m_state.notes, NOTE_COUNT, BPM);
    }
    // Notes
    for (int n = 0; n < NOTE_COUNT; n++) {
        m_state.notes[n].update(delta_time, m_state.keys, NOTE_COUNT, BPM);
        if (m_state.notes[n].get_hit() && !m_state.notes[n].get_is_active()) { num_hits += 1; }
        else if (!m_state.notes[n].get_hit() && !m_state.notes[n].get_is_active()) {
            num_miss += 1;
        }
    }
    
    lives = LIFE_COUNT - num_miss;
    SCORE = num_hits;
    num_miss = 0;
    num_hits = 0;
}

void Song_1::render(ShaderProgram *program) {
    
    Utility::draw_object(program, bg_texture_id, glm::vec3(0.0f), glm::vec3(8.0f));
    
    // Lives
    for (int l = 0; l < lives; l++) {
        Utility::draw_object(program, life_texture_id, glm::vec3(4.5f, (0.5 * l) - 2.0f, 0.0f), glm::vec3(0.5f));
    }
    
    // Score
    Utility::draw_text(program, font_texture_id, std::to_string(SCORE), 1.0f, -1.0f, glm::vec3(3.5f,  3.0f, 0.0f));
    
    // Keys
    for (int k = 0; k < KEY_COUNT; k++) {
        m_state.keys[k].render(program);
    }
    
    // Notes
    for (int n = 0; n < NOTE_COUNT; n++) {
        m_state.notes[n].render(program);
    }
    
    if (Mix_PausedMusic()) {
        Utility::draw_text(program, font_texture_id, "Paused", 2.0f, -1.0f, glm::vec3(-2.5,  1.0f, 0.0f));
    }
    
}

