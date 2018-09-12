#ifndef LOADINGSCREEN_HPP
#define LOADINGSCREEN_HPP

#include <vector>
#include <Model_Sprite.hpp>
#include <Shaders.hpp>

class LoadingScreen
{
    public:
        LoadingScreen();
        ~LoadingScreen();

        void display();
        void reset();

    private:
        Shaders * _shader;
        void loadModels();
        std::vector<Model_Sprite *> _models;
        size_t _model;
        glm::mat4 _proj;
        glm::mat4 _view;
        glm::vec3 _light;
};

#endif // LOADINGSCREEN_HPP