#include "Scene.h"

class Start_Menu : public Scene {
public:
    
    ~Start_Menu();
    
    void initialise() override;
    void update(float delta_time) override;
    void render(ShaderProgram *program) override;
};
