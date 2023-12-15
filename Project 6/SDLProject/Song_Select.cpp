#include "Song_Select.h"
#include "Utility.h"


Song_Select::~Song_Select() {}

void Song_Select::initialise() {    
    font_texture_id = Utility::load_texture("game_files/font1.png");
}

void Song_Select::update(float delta_time) {}


void Song_Select::render(ShaderProgram *program) {
    Utility::draw_text(program, font_texture_id, "Press 1 to play 'Hibana'", 0.4f, 0.0001f, glm::vec3(-4.0f, -0.0f, 0.0f));
//    Utility::draw_text(program, font_texture_id, "Press 2 to play """, 0.4f, 0.0001f, glm::vec3(-4.0f, -1.0f, 0.0f));
}
