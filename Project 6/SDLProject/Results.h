#include "Scene.h"

class Result : public Scene {
public:
    
    ~Result();
    
    void initialise() override;
    void update(float delta_time) override;
    void render(ShaderProgram *program) override;
};
