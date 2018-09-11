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

    private:
        Shaders * _shader;
        void loadModels();
        std::vector<Model_Sprite *> _models;
        size_t _model;
        
};

#endif // LOADINGSCREEN_HPP
