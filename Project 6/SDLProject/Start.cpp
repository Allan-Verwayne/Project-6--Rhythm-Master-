#include "Start.h"
#include "Utility.h"


Start_Menu::~Start_Menu() {
    Mix_FreeMusic(m_state.music);
}

void Start_Menu::initialise() {
    
    font_texture_id = Utility::load_texture("game_files/font.png");
    bg_texture_id = Utility::load_texture("game_files/Era.jpg");
    
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    
    m_state.music = Mix_LoadMUS("game_files/In the Light of the Setting Sun.mp3");
    Mix_PlayMusic(m_state.music, -1);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 16.0f);
    
    m_state.next_scene_id = 1;
    
}

void Start_Menu::update(float delta_time) {}


void Start_Menu::render(ShaderProgram *program) {
    Utility::draw_object(program, bg_texture_id, glm::vec3(0.0f), glm::vec3(10.0f, 8.0f, 0.0f));
    
    Utility::draw_text(program, font_texture_id, "RHYTHM", 2.0f, -1.0f, glm::vec3(-3.5f,  1.1f, 0.0f));
    Utility::draw_text(program, font_texture_id, "MASTER!", 2.0f, -1.0f, glm::vec3(-2.5f,  0.0f, 0.0f));
    Utility::draw_text(program, font_texture_id, "Press enter to start", 0.50f, -0.25f, glm::vec3(-2.5f, -2.0f, 0.0f));
}
