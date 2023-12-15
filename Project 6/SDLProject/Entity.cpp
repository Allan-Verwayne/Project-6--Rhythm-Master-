#define GL_SILENCE_DEPRECATION
#define STB_IMAGE_IMPLEMENTATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1
#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"
#include "Entity.h"

Entity::Entity() {
    // ––––– TRANSLATION ––––– //
    m_model_matrix = glm::mat4(1.0f);
    m_movement     = glm::vec3(0.0f);
    m_position     = glm::vec3(0.0f);
}

Entity::~Entity() {
    delete[] m_animation_left;
    delete[] m_animation_down;
    delete[] m_animation_up;
    delete[] m_animation_right;
    delete[] m_animations;
}

void Entity::ai_update(float delta_time, float bpm) {
    move_down();
    m_position.y += m_movement.y * ((bpm) / 60.0f) * delta_time;
    if (m_position.y <= -4.0f) {
        note_hit = false;
        deactivate();
    }
}

void Entity::update(float delta_time, Entity* note, int num_notes, float bpm) {
    // If note is inactive, don't do anything
    if (!m_is_active) return;
    
    // Animation
    if (m_animation_indices != NULL) {
        if (glm::length(m_movement) != 0) {
            m_animation_time += delta_time;
            float frames_per_second = (float)1 / SECONDS_PER_FRAME;
            
            if (m_animation_time >= frames_per_second) {
                m_animation_time = 0.0f;
                m_animation_index++;
                
                if (m_animation_index >= m_animation_frames) {
                    m_animation_index = 0;
                }
            }
        }
    }

    // Translation of AI
    m_model_matrix = glm::mat4(1.0f);
    
    if (m_entity_type == NOTE) { ai_update(delta_time, bpm); }
    
    m_model_matrix = glm::translate(m_model_matrix, m_position);
    
    // Check for collision with note
    for (int n = 0; n < num_notes; n++) {
        Entity* c_entity = &note[n];
        // If key is pressed while the note is colliding
        if (m_entity_type == KEY && check_collision(c_entity) && key_active) {
            c_entity->hit_note();
            c_entity->deactivate();
        }
    }
    
    // Key press
    if (key_active && m_entity_type == KEY) {
        key_active = false;
    }
}

void Entity::render(ShaderProgram* program) {
    //if note is inactive, don't do anything
    if (!m_is_active) return;
    
    program->set_model_matrix(m_model_matrix);

    if (m_animation_indices != NULL) {
        draw_sprite_from_texture_atlas(program, m_texture_id, m_animation_indices[m_animation_index]);
        return;
    }

    float vertices[] = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
    float tex_coords[] = { 0.0,  1.0, 1.0,  1.0, 1.0, 0.0,  0.0,  1.0, 1.0, 0.0,  0.0, 0.0 };

    glBindTexture(GL_TEXTURE_2D, m_texture_id);

    glVertexAttribPointer(program->get_position_attribute(), 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(program->get_position_attribute());
    glVertexAttribPointer(program->get_tex_coordinate_attribute(), 2, GL_FLOAT, false, 0, tex_coords);
    glEnableVertexAttribArray(program->get_tex_coordinate_attribute());

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(program->get_position_attribute());
    glDisableVertexAttribArray(program->get_tex_coordinate_attribute());
}


bool const Entity::check_collision(Entity* other) const {
    if (other == this) return false;
    
    // If either entity is inactive, there shouldn't be any collision
    if (!m_is_active || !other->m_is_active) return false;

    float x_distance = fabs(m_position.x - other->m_position.x) - ((m_width + other->m_width) / 2.0f);
    float y_distance = fabs(m_position.y - other->m_position.y) - ((m_height + other->m_height) / 2.0f);

    return x_distance < 0.0f && y_distance < 0.0f;
}

void Entity::draw_sprite_from_texture_atlas(ShaderProgram* program, GLuint texture_id, int index) {
    // Step 1: Calculate the UV location of the indexed frame
    float u_coord = (float)(index % m_animation_cols) / (float)m_animation_cols;
    float v_coord = (float)(index / m_animation_cols) / (float)m_animation_rows;

    // Step 2: Calculate its UV size
    float width = 1.0f / (float)m_animation_cols;
    float height = 1.0f / (float)m_animation_rows;

    // Step 3: Just as we have done before, match the texture coordinates to the vertices
    float tex_coords[] = {
        u_coord, v_coord + height, u_coord + width, v_coord + height, u_coord + width, v_coord,
        u_coord, v_coord + height, u_coord + width, v_coord, u_coord, v_coord
    };

    float vertices[] = {
        -0.5, -0.5, 0.5, -0.5,  0.5, 0.5,
        -0.5, -0.5, 0.5,  0.5, -0.5, 0.5
    };

    // Step 4: And render
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glVertexAttribPointer(program->get_position_attribute(), 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(program->get_position_attribute());

    glVertexAttribPointer(program->get_tex_coordinate_attribute(), 2, GL_FLOAT, false, 0, tex_coords);
    glEnableVertexAttribArray(program->get_tex_coordinate_attribute());

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(program->get_position_attribute());
    glDisableVertexAttribArray(program->get_tex_coordinate_attribute());
}
