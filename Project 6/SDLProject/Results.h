#include "Scene.h"
#include "Entity.h"

class Result : public Scene {
public:
    
    GLuint miku_lose_texture_id = Utility::load_texture("game_files/Miku 2 nobg.png");
    GLuint miku_win_texture_id = Utility::load_texture("game_files/Miku nobg.png");
    
    Entity miku;
    
    ~Result();
    
    void initialise() override;
    void update(float delta_time) override;
    void render(ShaderProgram *program) override;
};
