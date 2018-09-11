#ifndef OPTIONSMENU_HPP
#define OPTIONSMENU_HPP

#include <Model_Sprite.hpp>
#include <Model_Texture.hpp>
#include <vector>
#include "IMenu.hpp"

class OptionsMenu : public IMenu
{
    public:
        enum Options {WindowSize, WindowMode, Keys, Sound, Volume, Music, Back };
        struct OptionsAction
        {
            Options action;
            Model_Sprite * button;
        };
        OptionsMenu();
        virtual ~OptionsMenu();

        virtual int show(Shaders & shader, Shaders & brightShaders);
    
    private:
        void loadModels();
        void deleteMenu();
        void moveOnScreen(Shaders & shader, float end);
        std::vector<OptionsAction> _action;
        Options _selected;
        
};
#endif