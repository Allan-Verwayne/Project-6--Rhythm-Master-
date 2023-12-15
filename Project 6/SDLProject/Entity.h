#pragma once
enum EntityType { NOTE, KEY };

class Entity {
private:
    // Active Entity
    bool m_is_active = true;
    
    // if a NOTE is hit
    bool note_hit = false;
    
    // if a KEY is active (being pressed)
    bool key_active = false;
    
    // Animation
    int* m_animation_left  = NULL,
       * m_animation_down  = NULL,
       * m_animation_up    = NULL,
       * m_animation_right = NULL;

    // Transformation
    glm::vec3 m_movement;
    glm::vec3 m_position;
    glm::mat4 m_model_matrix;
    
    float m_width  = 0.5f;
    float m_height = 0.99f;

    // AI Type
    EntityType m_entity_type;


public:
    // ————— STATIC VARIABLES ————— //
    static const int    SECONDS_PER_FRAME = 8;
    static const int    LEFT    = 0,
                        DOWN    = 1,
                        UP      = 2,
                        RIGHT   = 3;

    // ————— ANIMATION ————— //
    int** m_animations = new int* [4] {
        m_animation_left,
        m_animation_down,
        m_animation_up,
        m_animation_right
    };

    int m_animation_frames  = 0,
        m_animation_index   = 0,
        m_animation_cols    = 0,
        m_animation_rows    = 0;

    int*    m_animation_indices = NULL;
    float   m_animation_time = 0.0f;

    GLuint    m_texture_id;

    // ————— METHODS ————— //
    Entity();
    ~Entity();

    void draw_sprite_from_texture_atlas(ShaderProgram* program, GLuint texture_id, int index);
    void update(float delta_time, Entity* note, int num_notes, float bpm);
    void ai_update(float delta_time, float bpm);
    void render(ShaderProgram* program);

    bool const check_collision(Entity* other) const;

    void move_down()  { m_movement.y = -1.0f; };

    void activate()   { m_is_active = true;  };
    void deactivate() { m_is_active = false; };
    
    void hit_note()   { note_hit = true; }
    void key_hit()    { key_active = true; }

    // ————— GETTERS ————— //
    EntityType const get_entity_type()    const { return m_entity_type;   };
    glm::vec3  const get_position()       const { return m_position;      };
    glm::vec3  const get_movement()       const { return m_movement;      };
    bool       const get_hit()            const { return note_hit;        };
    bool       const get_key_active()     const { return key_active;      };
    bool       const get_is_active()      const { return m_is_active;     };
    int        const get_width()          const { return m_width;         };
    int        const get_height()         const { return m_height;        };

    // ————— SETTERS ————— //
    void const set_entity_type(EntityType new_entity_type) { m_entity_type = new_entity_type; };
    void const set_position(glm::vec3 new_position)        { m_position = new_position;       };
    void const set_movement(glm::vec3 new_movement)        { m_movement = new_movement;       };
    void const set_width(float new_width)                  { m_width = new_width;             };
    void const set_height(float new_height)                { m_height = new_height;           };
};
