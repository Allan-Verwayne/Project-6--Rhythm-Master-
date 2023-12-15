#include "Scene.h"

class Song_1 : public Scene {
public:
    // ————— STATIC ATTRIBUTES ————— //
    float BPM = 200;
    int NOTE_COUNT = 152; //193
    int KEY_COUNT  = 4;
    int LIFE_COUNT = 10;
    
    int SCORE = 0;
    
    int num_hits = 0;
    int num_miss = 0;
    
    GLuint life_texture_id = Utility::load_texture("game_files/DDR WC Life.png");
    
    // ————— CONSTRUCTOR ————— //
    ~Song_1();
    
    // ————— METHODS ————— //
    void initialise() override;
    void update(float delta_time) override;
    void render(ShaderProgram *program) override;
};
