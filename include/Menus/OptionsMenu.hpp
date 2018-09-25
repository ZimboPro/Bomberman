#ifndef OPTIONSMENU_HPP
#define OPTIONSMENU_HPP

#include <Model_Sprite.hpp>
#include <Model_Texture.hpp>
#include <ModelGroup.hpp>
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
        void loadOptions();
        void deleteMenu();
        void loadActions(char * path);
        void moveOnScreen(Shaders & shader, float end);
        void setOptionsPositions();
        void setShader(Shaders & shader, glm::mat4 & projection);
        void changeSettings();
        void addModels(int index, int start, int end);
        void loadTexture(char * path);
        void drawSettings(Shaders & shader);
        void drawSelectedSetting(Shaders & shader);
        void drawNotSelectedSetting(Shaders & shader);
        void setGroupPositions(int groupIndex, int heightIndex);
        void showKeyBindMenu();

        std::vector<OptionsAction> _action;
        Options _selected;
        std::vector<Model_Texture *> _options;
        std::vector<ModelGroup *> _groups;
        IAudioProvider * _sound;
        
};
#endif