#include "Scene.h"

class Song_Select : public Scene {
public:
    
    ~Song_Select();
    
    void initialise() override;
    void update(float delta_time) override;
    void render(ShaderProgram *program) override;
};
